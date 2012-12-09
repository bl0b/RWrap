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
#include "gen_method_wrap.h"


namespace Rwrap {



template <typename T> struct is_void { enum { value=true }; };
template <> struct is_void<void> { enum { value=false }; };


#define _FT(_func) boost::add_pointer<BOOST_TYPEOF(_func) >::type


template <typename F>
struct reg_helper {
    typedef FuncTraits<F> T;
    typedef gen<T> G;
};

template <class C, typename F>
struct reg_method_helper {
    typedef FuncTraits<F> T;
    typedef gen_meth<C, T> G;
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

struct WrapperSettings {
    const char* r_name;
    std::vector<Argument> args;
    std::string wrap_result_prefix, wrap_result_suffix;
    bool auto_glue;

    WrapperSettings()
        : args()
        , wrap_result_prefix()
        , wrap_result_suffix()
        , auto_glue(false)
    {}

    WrapperSettings(const WrapperSettings& w)
        : args(w.args)
        , wrap_result_prefix(w.wrap_result_prefix)
        , wrap_result_suffix(w.wrap_result_suffix)
        , auto_glue(w.auto_glue)
    {}

    void _glue_args(std::ostream& glue, int argc, bool decl) const
    {
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

    void gen_glue(std::ostream& glue,
                  const char* package, const char* rname, const char* cname,
                  int argc, const char* assign=" <- ",
                  const char* decl_sep="") const
    {
        /*const char* fname = routines_.back().name;*/
        /*int argc = routines_.back().numArgs;*/
        /*std::ostringstream buf;*/
        glue << rname << assign << "function(";
        _glue_args(glue, argc, true);
        glue << ") " << wrap_result_prefix
             << ".Call(" << cname;
        _glue_args(glue, argc, false);
        glue <<  ", PACKAGE='" << package << "')"
             << wrap_result_suffix << decl_sep << std::endl;
        glue.flush();
    }
};

template <class Der>
struct RWrap_base {
    const char* name;
    std::vector<R_CallMethodDef> routines_;
    std::vector<const char*> routine_names;
    std::vector<WrapperSettings> settings;

    RWrap_base(const char* name_)
        : name(name_)
        , routines_()
        , routine_names()
        , settings()
    {}
    RWrap_base(const RWrap_base& r)
        : name(r.name)
        , routines_(r.routines_)
        , routine_names(r.routine_names)
        , settings(r.settings)
    {}
    virtual ~RWrap_base() {}

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

    Der& arg(const char* n, const char* v=NULL) {
        settings.back().args.push_back(Argument(n, v, false));
        return *dynamic_cast<Der*>(this);
    }

    Der& implicit_arg(const char* expr) {
        settings.back().args.push_back(Argument(expr, NULL, true));
        return *dynamic_cast<Der*>(this);
    }

    Der& wrap_result(const char* pfx, const char* sfx) {
        settings.back().wrap_result_prefix = pfx;
        settings.back().wrap_result_suffix = sfx;
        return *dynamic_cast<Der*>(this);
    }

    Der& auto_glue() {
        settings.back().auto_glue = true;
        return *dynamic_cast<Der*>(this);
    }

    Der& _reg(const char* rname, const char* cname, int argc, DL_FUNC wrapper) {
        printf("Registering new routine :\n");
        printf("   - name: %s\n", cname);
        printf("   - argc: %i\n", argc);
        /*printf("   - wrap: %p\n", wrapper);*/
        R_CallMethodDef def = {cname, wrapper, argc};
        routines_.push_back(def);
        routine_names.push_back(rname);
        settings.push_back(WrapperSettings());
        return *dynamic_cast<Der*>(this);
    }

    void gen_glue(std::ostream& glue, const char* package,
                  const char* assign=" <- ", const char* decl_sep="",
                  const char* last_decl_sep="") const
    {
        std::vector<R_CallMethodDef>::const_iterator ri = routines_.begin(),
                                                     rj = routines_.end();
        std::vector<WrapperSettings>::const_iterator si = settings.begin(),
                                                     sj = settings.end();
        std::vector<const char*>::const_iterator ni = routine_names.begin(),
                                                 nj = routine_names.end();
        if (ri != rj) {
            --rj;
        }
        while(ri != rj && si != sj) {
            si->gen_glue(glue, package, *ni, ri->name, ri->numArgs, assign, decl_sep);
            ++si;
            ++ri;
            ++ni;
        }
        si->gen_glue(glue, package, *ni, ri->name, ri->numArgs, assign, last_decl_sep);
    }
};


class Class : public RWrap_base<Class> {
public:
    std::vector<Argument> ctor_args;

    Class(const char* name_)
        : RWrap_base<Class>(name_)
        , ctor_args()
    {}
    Class(const Class& c)
        : RWrap_base<Class>(c)
        , ctor_args(c.ctor_args)
    {}

    void gen_glue(std::ostream& glue, const char* package) const
    {
        glue << name << " <- setRefClass('" << name
             << "', fields=c('this.ptr'), methods=list(" << std::endl
             << "initialize=function(ptr) { this.ptr <<- ptr }," << std::endl;
        RWrap_base<Class>::gen_glue(glue, package, " = ", ",", "");
        glue << "))" << std::endl;
    }

    Class& ctor_arg(const char* name, const char* default_value=NULL) {
        ctor_args.push_back(Argument(name, default_value, false));
    }

    Class& ctor_implicit_arg(const char* name, const char* default_value=NULL) {
        ctor_args.push_back(Argument(name, default_value, true));
    }
};

class Module : public RWrap_base<Module> {
    std::vector<Class*> classes;
    Exports exports;
    S3Methods s3methods;
    const char* exportpattern;

public:
    Module(const char* name_)
        : RWrap_base<Module>(name_)
        , classes()
        , exports()
        , s3methods()
        , exportpattern(0)
    {}

    Module(const Module& m)
        : RWrap_base<Module>(m)
        , classes(m.classes)
        , exports(m.exports)
        , s3methods(m.s3methods)
        , exportpattern(m.exportpattern)
    {}

    Module& add_class_(Class& c) {
        routines_.insert(routines_.end(), c.routines_.begin(), c.routines_.end());
        settings.insert(settings.end(), c.settings.begin(), c.settings.end());
        routine_names.insert(routine_names.end(), c.routine_names.begin(), c.routine_names.end());
        std::cout << "Adding class " << c.name << std::endl;
        classes.push_back(&c);
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

    void export_routines(std::ostream& ns, const std::vector<R_CallMethodDef>& rvec) const {
        std::vector<R_CallMethodDef>::const_iterator i, j = rvec.end();
        std::vector<const char*>::const_iterator ni = routine_names.begin(),
                                                 nj = routine_names.end();
        /*std::cerr << "Have " << rvec.size() << " C/C++ exports" << std::endl;*/
        for (i = rvec.begin(); i != j; ++i, ++ni) {
            /*ns << "export('" << i->name << "')" << std::endl;*/
            ns << "export('" << (*ni) << "')" << std::endl;
        }
    }

    void generate_namespace() const {
        std::ofstream ns("NAMESPACE");
        ns << "useDynLib(" << name;
        ns << ", .registration=TRUE" << std::endl;
        ns << ")" << std::endl;
        export_routines(ns, routines_);
        std::vector<Class*>::const_iterator ci = classes.begin(),
                                            cj = classes.end();
        while(ci != cj) {
            export_routines(ns, (*ci)->routines_);
            ns << "export(" << (*ci)->name << ')' << std::endl;
            ++ci;
        }
        if (exportpattern) {
            ns << "exportPattern('" << exportpattern << "')" << std::endl;
        }
        /*std::cerr << "Have " << exports.size() << " exports" << std::endl;*/
        Exports::const_iterator ei, ej = exports.end();
        for (ei = exports.begin(); ei != ej; ++ei) {
            ns << "export(" << (*ei) << ')' << std::endl;
        }
        S3Methods::const_iterator si, sj = s3methods.end();
        /*std::cerr << "Have " << s3methods.size() << " S3 methods" << std::endl;*/
        for (si = s3methods.begin(); si != sj; ++si) {
            ns << "S3method(" << si->first << ", " << si->second << ')' << std::endl;
        }
        /*ns << ")" << std::endl;*/
    }

    void generate_glue() const {
        /*printf("glue code:\n%s\n", glue.str().c_str());*/
        ::mkdir("R", 0755);
        std::ofstream g("R/glue.R");
        gen_glue(g, name);
        std::vector<Class*>::const_iterator ci = classes.begin(),
                                            cj = classes.end();
        while(ci != cj) {
            std::cout << "got class " << (*ci)->name << std::endl;
            (*ci)->gen_glue(g, name);
            ++ci;
        }
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


#define CLASS(_kls) \
struct _kls##name { static const char* name; }; \
const char* _kls##name::name = #_kls; \
namespace Rwrap { \
    template <> \
    struct Value<_kls*> \
        : public ClassWrap<_kls, _kls##name> \
    {}; \
} \
Rwrap::Class _rwrap_class_##_kls = Rwrap::Class(#_kls)


#define _RH(_x) Rwrap::reg_helper<_FT(_x)>
#define _rhG(_x) _RH(_x)::G
#define _rhT(_x) _RH(_x)::T

#define _RMH(_k, _m) Rwrap::reg_method_helper<_k, BOOST_TYPEOF(&_k::_m)>
#define _rmhG(_k, _m) _RMH(_k, _m)::G
#define _rmhT(_k, _m) _RMH(_k, _m)::T

#define _reg_helper(_rname, _cname, _func) _reg(_rname, _cname, _rhT(_func)::ArgCount, (DL_FUNC) _rhG(_func)::_w<_func>::_)
#define _reg_meth_helper(_rname, _cname, _kls, _meth) _reg(_rname, _cname, _rmhT(_kls, _meth)::ArgCount + 1, (DL_FUNC) _rmhG(_kls, _meth)::_w<&_kls::_meth>::_)

#define reg_name(_rname, _cname, _func) _reg_helper(_rname, _cname, _func)
#define reg(_func) reg_name(#_func, #_func "_", _func)

#define reg_meth_name(_rname, _cname, _kls, _meth) _reg_meth_helper(_rname, _cname, _kls, _meth).implicit_arg("this.ptr")
#define reg_meth(_kls, _meth) reg_meth_name(#_meth, "." #_meth "." #_kls "_", _kls, _meth)

#define add_class(_k) add_class_(_rwrap_class_##_k)

#endif
