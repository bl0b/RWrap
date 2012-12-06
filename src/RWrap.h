/* RWrap
 *
 * Copyright (C) 2012 Damien "bl0b" Leroux
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef _RWRAP_H_
#define _RWRAP_H_

#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <boost/type_traits.hpp>
#include <boost/typeof/std/utility.hpp>

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Parse.h>

#include "Value.h"
#include "FuncTraits.h"
#include "gen_wrap.h"


namespace Rwrap {



template <typename T> struct is_void { enum { value=true }; };
template <> struct is_void<void> { enum { value=false }; };


#define _FT(_func) boost::add_pointer<BOOST_TYPEOF(_func) >::type


template <typename F>
struct reg_helper {
    typedef FuncTraits<F> T;
    typedef gen<T> G;
};


struct Argument {
    const char* name;
    const char* default_value;
    bool implicit;
    Argument(const char* n, const char* def, bool impl)
        : name(n)
        , default_value(def)
        , implicit(impl)
    {}
};


typedef std::vector<const char*> Exports;
typedef std::vector<std::pair<const char*, const char*> > S3Methods;


class Module {
    const char* name;
    std::vector<R_CallMethodDef> routines_;
    std::ostringstream glue;
    std::vector<Argument> args;
    std::string wrap_result_prefix, wrap_result_suffix;
    Exports exports;
    S3Methods s3methods;
    const char* exportpattern;

public:
    Module(const char* name_)
        : name(name_)
        , routines_()
        , glue()
        , args()
        , wrap_result_prefix()
        , wrap_result_suffix()
        , exports()
        , s3methods()
        , exportpattern(0)
    {}

    Module(const Module& m)
        : name(m.name)
        , routines_(m.routines_)
        , glue(m.glue.str())
        , args(m.args)
        , wrap_result_prefix(m.wrap_result_prefix)
        , wrap_result_suffix(m.wrap_result_suffix)
        , exports(m.exports)
        , s3methods(m.s3methods)
        , exportpattern(m.exportpattern)
    {}

    Module& _reg(const char* name, int argc, DL_FUNC wrapper) {
        /*printf("Registering new routine :\n");*/
        /*printf("   - name: %s\n", name);*/
        /*printf("   - argc: %i\n", argc);*/
        /*printf("   - wrap: %p\n", wrapper);*/
        R_CallMethodDef def = {name, wrapper, argc};
        routines_.push_back(def);
        args.clear();
        wrap_result_prefix.clear();
        wrap_result_suffix.clear();
        return *this;
    }

    void parse_and_eval(const char* cmd) {
        SEXP cmdSexp, cmdexpr, ans = R_NilValue;
        ParseStatus status;
        PROTECT(cmdSexp = allocVector(STRSXP, 1));
        SET_STRING_ELT(cmdSexp, 0, mkChar(cmd));
        cmdexpr = PROTECT(R_ParseVector(cmdSexp, -1, &status, R_NilValue));
        if (status != PARSE_OK) {
            UNPROTECT(2);
            error("invalid call %s", cmd);
        }
        /* Loop is needed here as EXPSEXP will be of length > 1 */
        for(R_len_t i = 0; i < length(cmdexpr); i++) {
            ans = eval(VECTOR_ELT(cmdexpr, i), R_GlobalEnv);
        }
        UNPROTECT(2);
    }

    Module& arg(const char* n, const char* v=NULL) {
        args.push_back(Argument(n, v, false));
        return *this;
    }

    Module& implicit_arg(const char* expr) {
        args.push_back(Argument(expr, NULL, true));
        return *this;
    }

    Module& wrap_result(const char* pfx, const char* sfx) {
        wrap_result_prefix = pfx;
        wrap_result_suffix = sfx;
        return *this;
    }

    void _glue_args(int argc, bool decl) {
        if (argc == 0) {
            return;
        }
        if (!decl) {
            glue << ',';
        }
        if (args.size() == argc) {
            for (int i = 0; i < args.size(); ++i) {
                if(decl && args[i].implicit) {
                    continue;
                }
                glue << args[i].name;
                if (decl && args[i].default_value) {
                    glue << '=' << args[i].default_value;
                }
                if ((i + 1) < argc) {
                    glue << ',';
                }
            }
        } else {
            glue << 'a';
            for (int i = 1; i < argc; ++i) {
                glue << ',' << (char)('a' + i);
            }
        }
    }

    Module& auto_glue() {
        const char* fname = routines_.back().name;
        int argc = routines_.back().numArgs;
        /*std::ostringstream buf;*/
        glue << fname << " <- function(";
        _glue_args(argc, true);
        glue << ") " << wrap_result_prefix
             << ".Call('" << fname << '\'';
        _glue_args(argc, false);
        glue <<  ", PACKAGE='" << name << "')"
             << wrap_result_suffix << std::endl;
        glue.flush();
        return *this;
    }

    Module& exportPattern(const char* pat) {
        exportpattern = pat;
        return *this;
    }

    Module& add_export(const char* name) {
        exports.push_back(name);
        /*std::cerr << "registered export #" << exports.size() << ' ' << name << std::endl;*/
        return *this;
    }

    Module& add_s3method(const char* generic, const char* impl) {
        s3methods.push_back(std::pair<const char*, const char*>(generic, impl));
        /*std::cerr << "registered S3 method #" << s3methods.size() << ' ' << generic << '.' << impl << std::endl;*/
        return *this;
    }

    void commit(DllInfo* info) {
        R_CallMethodDef null = {NULL, NULL, 0};
        routines_.push_back(null);
        R_registerRoutines(info, NULL, &routines_[0], NULL, NULL);
        /*parse_and_eval(buf.str().c_str());*/
    }

    void generate_namespace() const {
        std::ofstream ns("NAMESPACE");
        ns << "useDynLib(" << name;
        //<< ", .registration=TRUE)" << std::endl;
        ns << ")" << std::endl;
        std::vector<R_CallMethodDef>::const_iterator i, j = routines_.end();
        std::cerr << "Have " << routines_.size() << " C/C++ exports" << std::endl;
        for (i = routines_.begin(); i != j; i++) {
            /*ns << ", " << i->name;*/
            ns << "export('" << i->name << "')" << std::endl;
        }
        if (exportpattern) {
            ns << "exportPattern('" << exportpattern << "')" << std::endl;
        }
        std::cerr << "Have " << exports.size() << " exports" << std::endl;
        Exports::const_iterator ei, ej = exports.end();
        for (ei = exports.begin(); ei != ej; ++ei) {
            ns << "export(" << (*ei) << ')' << std::endl;
        }
        S3Methods::const_iterator si, sj = s3methods.end();
        std::cerr << "Have " << s3methods.size() << " S3 methods" << std::endl;
        for (si = s3methods.begin(); si != sj; ++si) {
            ns << "S3method(" << si->first << ", " << si->second << ')' << std::endl;
        }
        /*ns << ")" << std::endl;*/
    }

    void generate_glue() const {
        /*printf("glue code:\n%s\n", glue.str().c_str());*/
        ::mkdir("R", 0755);
        std::ofstream g("R/glue.R");
        g << glue.str() << std::endl;
        g.flush();
    }

    void generate_files() const {
        generate_namespace();
        generate_glue();
    }
};

}

#define MODULE(name__) \
extern Rwrap::Module M##name__; \
extern "C" void R_init_##name__(DllInfo* info) { M##name__.commit(info); } \
extern "C" void Rwrap_gen() { M##name__.generate_files(); } \
Rwrap::Module M##name__ = Rwrap::Module(#name__)

#define reg_name(_name, _func) _reg(_name, Rwrap::reg_helper<_FT(_func)>::T::ArgCount, (DL_FUNC) Rwrap::reg_helper<_FT(_func)>::G::_w<_func>::_)
#define reg(_func) reg_name(#_func, _func)


#endif
