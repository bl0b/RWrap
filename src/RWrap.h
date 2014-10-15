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

/*#include <boost/type_traits.hpp>*/
/*#include <boost/typeof/std/utility.hpp>*/

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Parse.h>

#include "Value.h"
#include "FuncTraits.h"

namespace Rwrap {
    struct NullPtrError : public std::exception {
        const char* what() const throw() { return "Attempting to invoke a method on a NULL instance"; }
    };
}

#define HANDLE_EXCEPTION(_e) do { \
        SEXP stop; \
        PROTECT(stop = allocList(2)); \
        SET_TYPEOF(stop, LANGSXP); \
        SETCAR(stop, install("stop")); \
        SETCADR(stop, Value<const char*>::coerceToR(_e.what())); \
        return eval(stop, R_GlobalEnv); \
    } while (0)

#define NO_RET
#define SANDBOXED(_expr_, RET_TYPE) \
    try { RET_TYPE _expr_; } catch (Error e) { HANDLE_EXCEPTION(e); } catch (NullPtrError e) { HANDLE_EXCEPTION(e); }


#define SANDBOXED_NORET(_expr_) do { SANDBOXED(_expr_, NO_RET); return R_NilValue; } while (0)
#define SANDBOXED_RET(_expr_) SANDBOXED(_expr_, return)

#include "gen_wrap.h"
#include "gen_method_wrap.h"
#include "static_ctor.h"


namespace Rwrap {



template <typename T> struct is_void { enum { value=true }; };
template <> struct is_void<void> { enum { value=false }; };


/*template <typename X>*/
/*struct remove_class {*/
    /*typedef X type;*/
/*};*/


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
        settings.back().wrap_result_prefix += pfx;
        settings.back().wrap_result_suffix = sfx + settings.back().wrap_result_suffix;
        return *dynamic_cast<Der*>(this);
    }

    Der& auto_glue() {
        settings.back().auto_glue = true;
        return *dynamic_cast<Der*>(this);
    }

    Der& _reg(const char* rname, const char* cname, int argc, DL_FUNC wrapper) {
        /*printf("Registering new routine :\n");*/
        /*printf("   - name: %s\n", cname);*/
        /*printf("   - argc: %i\n", argc);*/
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
    std::vector<unsigned int> ctors;
    /*std::vector<WrapperSettings*> ctors;*/
    /*std::vector<R_CallMethodDef*> ctor_syms;*/

    Class(const char* name_)
        : RWrap_base<Class>(name_)
        , ctors()
    {}
    Class(const Class& c)
        : RWrap_base<Class>(c)
        , ctors(c.ctors)
    {}

    void gen_glue(std::ostream& glue, const char* package) const
    {
        glue << name << " <- setRefClass('" << name
             << "', fields=c('this.ptr'), methods=list(" << std::endl
             << "initialize=function(...) { "
                << "args <- list(...); l <- length(args); n <- names(args); "
                /*<< "print(args); "*/
                << "if (l == 1 && '.ptr' %in% n) { this.ptr <<- args$.ptr }";
        std::vector<unsigned int>::const_iterator ctori, ctorj = ctors.end();
        for(ctori = ctors.begin(); ctori != ctorj; ++ctori) {
            const WrapperSettings& ws = settings[*ctori];
            const R_CallMethodDef& routine = routines_[*ctori];
            glue << " else if (l == " << ws.args.size();
            std::cout << " else if (l == " << ws.args.size();
            std::vector<Argument>::const_iterator ai, aj = ws.args.end();
            for(ai = ws.args.begin(); ai != aj; ++ai) {
                glue << " && '" << ai->name << "' %in% n";
                std::cout << " && '" << ai->name << "' %in% n";
            }
            glue << ") { this.ptr <<- .Call(" << routine.name;
            std::cout << ") { this.ptr <<- .Call(" << routine.name;
            for(ai = ws.args.begin(); ai != aj; ++ai) {
                glue << ", args$" << ai->name;
                std::cout << ", args$" << ai->name;
            }
            glue << ", PACKAGE='" << package << "') }";
            std::cout << ", PACKAGE='" << package << "') }" << std::endl;
        }
        glue << " else stop(\"Couldn't construct object\") }," << std::endl;
        RWrap_base<Class>::gen_glue(glue, package, " = ", ",", "");
        glue << "))" << std::endl;
    }
};

template <class C>
struct dtor {
    std::string dn;
    dtor(const char* name) {
        dn = name;
        dn += ".dtor_";
    }
    static void _(C* ptr) { if (ptr) { delete ptr; } else { throw NullPtrError(); } }
};


#define SAFE_METHOD_INVOCATION_PFX "{ if (is.null(this.ptr)) stop('This instance has already been destroyed'); "
#define SAFE_METHOD_INVOCATION_SFX " }"
#define SAFE_METHOD_INVOCATION_WRAP SAFE_METHOD_INVOCATION_PFX, SAFE_METHOD_INVOCATION_SFX

template <class C>
class BoundClass : public Class {
public:
    template <typename RET,
              typename A1=void, typename A2=void, typename A3=void,
              typename A4=void, typename A5=void, typename A6=void,
              typename A7=void, typename A8=void, typename A9=void,
              typename A10=void, typename A11=void, typename A12=void>
    struct _gen : public _gen_meth_<C, RET, A1, A2, A3,  A4,  A5,  A6,
                                            A7, A8, A9, A10, A11, A12>
    {
        using _gen_meth_<C, RET, A1, A2, A3,  A4,  A5,  A6,
                                 A7, A8, A9, A10, A11, A12>::_w;
    };

    BoundClass(const char* name_)
        : Class(name_)
    {
        /* register automatic dtor */
        typedef dtor<C> DTOR;
        static DTOR d(name);
        typedef gen<FuncTraits<_FT(DTOR::_)> > G;
        _reg("delete", d.dn.c_str(), 1, (DL_FUNC) G::template _w<DTOR::_>::_);
        implicit_arg("this.ptr");
        wrap_result(SAFE_METHOD_INVOCATION_PFX, "; this.ptr <<- NULL" SAFE_METHOD_INVOCATION_SFX);
    }
    BoundClass(const Class& c)
        : Class(c)
    {}

    BoundClass<C>& arg(const char* n, const char* v=NULL) {
        Class::arg(n, v);
        return *this;
    }

    BoundClass<C>& implicit_arg(const char* expr) {
        Class::implicit_arg(expr);
        return *this;
    }

    BoundClass<C>& wrap_result(const char* pfx, const char* sfx) {
        Class::wrap_result(pfx, sfx);
        return *this;
    }

    BoundClass<C>& auto_glue() {
        Class::auto_glue();
        return *this;
    }

    template <typename SIG>
    struct regger {
        BoundClass<C>& this_;
        regger(BoundClass<C>& c) : this_(c) {}
        template <SIG F>
        BoundClass<C>& _(const char* rname, const char* cname) {
            typedef typename remove_ptr<SIG>::type FSIG;
            typedef gen_meth<C, FuncTraits<FSIG> > M;
            this_._reg(rname, cname, M::FT::ArgCount + 1,
                       (DL_FUNC) (M::template _w<F>::_)).implicit_arg("this.ptr").wrap_result(SAFE_METHOD_INVOCATION_WRAP);
            return this_;
        }
    };

    template <typename SIG>
    regger<SIG> make_regger(SIG F) {
        return regger<SIG>(*this);
    }

    BoundClass<C> ctor() {
        typedef static_ctor<C*()> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 0,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return *this;
    }

    template <typename A1>
    BoundClass<C> ctor(const char* a1) {
        typedef static_ctor<C*(A1)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 1,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1);
    }

    template <typename A1, typename A2>
    BoundClass<C> ctor(const char* a1, const char* a2) {
        typedef static_ctor<C*(A1, A2)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 2,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2);
    }

    template <typename A1, typename A2, typename A3>
    BoundClass<C> ctor(const char* a1, const char* a2, const char* a3) {
        typedef static_ctor<C*(A1, A2, A3)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 3,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2).arg(a3);
    }

    template <typename A1, typename A2, typename A3, typename A4>
    BoundClass<C> ctor(const char* a1, const char* a2, const char* a3,
                       const char* a4) {
        typedef static_ctor<C*(A1, A2, A3, A4)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 4,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2).arg(a3).arg(a4);
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5>
    BoundClass<C> ctor(const char* a1, const char* a2, const char* a3,
                       const char* a4, const char* a5) {
        typedef static_ctor<C*(A1, A2, A3, A4, A5)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 5,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2).arg(a3).arg(a4).arg(a5);
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6>
    BoundClass<C> ctor(const char* a1, const char* a2, const char* a3,
                       const char* a4, const char* a5, const char* a6) {
        typedef static_ctor<C*(A1, A2, A3, A4, A5, A6)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 6,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6);
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7>
    BoundClass<C> ctor(const char* a1, const char* a2, const char* a3,
                       const char* a4, const char* a5, const char* a6,
                       const char* a7) {
        typedef static_ctor<C*(A1, A2, A3, A4, A5, A6, A7)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 7,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7);
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8>
    BoundClass<C> ctor(const char* a1, const char* a2, const char* a3,
                       const char* a4, const char* a5, const char* a6,
                       const char* a7, const char* a8) {
        typedef static_ctor<C*(A1, A2, A3, A4, A5, A6, A7, A8)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 8,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7).arg(a8);
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9>
    BoundClass<C> ctor(const char* a1, const char* a2, const char* a3,
                       const char* a4, const char* a5, const char* a6,
                       const char* a7, const char* a8, const char* a9) {
        typedef static_ctor<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 9,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7).
               arg(a8).arg(a9);
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10>
    BoundClass<C> ctor(const char* a1, const char* a2, const char* a3,
                       const char* a4, const char* a5, const char* a6,
                       const char* a7, const char* a8, const char* a9,
                       const char* a10) {
        typedef static_ctor<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 10,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7).
               arg(a8).arg(a9).arg(a10);
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10,
              typename A11>
    BoundClass<C> ctor(const char* a1, const char* a2, const char* a3,
                       const char* a4, const char* a5, const char* a6,
                       const char* a7, const char* a8, const char* a9,
                       const char* a10, const char* a11) {
        typedef static_ctor<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,
                               A11)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 11,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7).
               arg(a8).arg(a9).arg(a10).arg(a11);
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5,
              typename A6, typename A7, typename A8, typename A9, typename A10,
              typename A11, typename A12>
    BoundClass<C> ctor(const char* a1, const char* a2, const char* a3,
                       const char* a4, const char* a5, const char* a6,
                       const char* a7, const char* a8, const char* a9,
                       const char* a10, const char* a11, const char* a12) {
        typedef static_ctor<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,
                               A11, A12)> CTOR;
        static CTOR with_name(name);
        _reg(with_name.rname.c_str(), with_name.cname.c_str(), 12,
             (DL_FUNC) CTOR::G::template _w<CTOR::new_>::_);
        ctors.push_back(routines_.size() - 1);
        return arg(a1).arg(a2).arg(a3).arg(a4).arg(a5).arg(a6).arg(a7).
               arg(a8).arg(a9).arg(a10).arg(a11).arg(a12);
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
        /*std::cout << "Adding class " << c.name << std::endl;*/
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
Rwrap::BoundClass<_kls> _rwrap_class_##_kls = Rwrap::BoundClass<_kls>(#_kls)


#define _RH(_x) Rwrap::reg_helper<_FT(_x)>
#define _rhG(_x) _RH(_x)::G
#define _rhT(_x) _RH(_x)::T

#define _RMH(_k, _m) Rwrap::reg_method_helper<_k, _MT(&_k::_m)>
#define _rmhG(_k, _m) _RMH(_k, _m)::G
#define _rmhT(_k, _m) _RMH(_k, _m)::T

#define _reg_helper(_rname, _cname, _func) _reg(_rname, _cname, _rhT(_func)::ArgCount, (DL_FUNC) _rhG(_func)::_w<_func>::_)

#define reg_name(_rname, _cname, _func) _reg_helper(_rname, _cname, _func)
#define reg(_func) reg_name(#_func, #_func "_", _func)

#if 0
#define _reg_meth_helper(_rname, _cname, _kls, _meth) _reg(_rname, _cname, _rmhT(_kls, _meth)::ArgCount + 1, (DL_FUNC) _rmhG(_kls, _meth)::_w<&_kls::_meth>::_)
#define reg_meth_name(_rname, _cname, _kls, _meth) _reg_meth_helper(_rname, _cname, _kls, _meth).implicit_arg("this.ptr")
#define reg_meth(_kls, _meth) reg_meth_name(#_meth, "." #_meth "." #_kls "_", _kls, _meth)
#endif


#define method_name(_rname, _cname, _kls, _meth) make_regger(&_kls::_meth)._<&_kls::_meth>(_rname, _cname)
#define method(_kls, _meth) method_name(#_meth, "." #_meth "." #_kls "_", _kls, _meth)

#define add_class(_k) add_class_(_rwrap_class_##_k)

#endif
