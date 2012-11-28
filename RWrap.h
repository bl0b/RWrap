#ifndef _RWRAP_H_
#define _RWRAP_H_

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#include <iostream>

#include <vector>

#include "Value.h"
#include "gen_wrap.h"

namespace Rwrap {



template <typename T> struct is_void { enum { value=true }; };
template <> struct is_void<void> { enum { value=false }; };

struct wrapper_impl {
    template <typename T>
    struct _wrapper {};

    template <typename RET, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    static DL_FUNC wrap(RET (*f)(A1, A2, A3, A4, A5, A6));

    template <typename RET, typename A1, typename A2, typename A3>
    static DL_FUNC wrap(RET (*f)(A1, A2, A3)) {
        return (DL_FUNC) _gen_<RET, A1, A2, A3>:: template _w<f>::_;
    }

    template <typename A1, typename A2, typename A3>
    static DL_FUNC wrap(void (*f)(A1, A2, A3)) {
        return (DL_FUNC) _gen_<void, A1, A2, A3>:: template _w<f>::_;
    }

    template <typename RET, typename A1, typename A2>
    static DL_FUNC wrap(RET (*f)(A1, A2)) {
        return (DL_FUNC) _gen_<RET, A1, A2>:: template _w<f>::_;
    }

    template <typename A1, typename A2>
    static DL_FUNC wrap(void (*f)(A1, A2)) {
        return (DL_FUNC) _gen_<void, A1, A2>:: template _w<f>::_;
    }

    template <typename RET, typename A1>
    static DL_FUNC wrap(RET (*f)(A1)) {
        return (DL_FUNC) _gen_<RET, A1>:: template _w<f>::_;
    }

    template <typename A1>
    static DL_FUNC wrap(void (*f)(A1)) {
        return (DL_FUNC) _gen_<void, A1>:: template _w<f>::_;
    }

    template <typename RET>
    static DL_FUNC wrap(RET (*f)()) {
        return (DL_FUNC) _gen_<RET>:: template _w<f>::_;
    }

    /*static DL_FUNC wrap(void (*f)()) {*/
        /*return (DL_FUNC) _gen_<void, void, void, void, void, void, void>::_w<f>::_;*/
    /*}*/
};


template <typename Function>
struct FuncTraits;

template <typename RET, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
struct FuncTraits<RET (*)(A1, A2, A3, A4, A5, A6)> {
    enum { ArgCount=6 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef A6 a6_t;
};

template <typename RET, typename A1, typename A2, typename A3, typename A4, typename A5>
struct FuncTraits<RET (*) (A1, A2, A3, A4, A5)> {
    enum { ArgCount=5 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef void a6_t;
};

template <typename RET, typename A1, typename A2, typename A3, typename A4>
struct FuncTraits<RET (*) (A1, A2, A3, A4)> {
    enum { ArgCount=4 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef void a5_t;
    typedef void a6_t;
};

template <typename RET, typename A1, typename A2, typename A3>
struct FuncTraits<RET (*) (A1, A2, A3)> {
    enum { ArgCount=3 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
};

template <typename RET, typename A1, typename A2>
struct FuncTraits<RET (*) (A1, A2)> {
    enum { ArgCount=2 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef void a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
};

template <typename RET, typename A1>
struct FuncTraits<RET (*) (A1)> {
    enum { ArgCount=1 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef void a2_t;
    typedef void a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
};

template <typename RET>
struct FuncTraits<RET (*) ()> {
    enum { ArgCount=0 };
    typedef RET ret_t;
    typedef void a1_t;
    typedef void a2_t;
    typedef void a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;

    template <RET (*F)()>
    static SEXP wrap() { return ret_t::coerceToR(F()); }

    /*template <>*/
    /*SEXP wrap<void (*F)()>() { F(); return NULL; }*/
};


template <typename F>
struct reg_helper {
    typedef FuncTraits<F> T;
    typedef gen<T> G;
};

#define _FT(_func) boost::add_pointer<BOOST_TYPEOF(_func) >::type
#define reg(_func) _reg(#_func, reg_helper<_FT(_func)>::T::ArgCount, (DL_FUNC) reg_helper<_FT(_func)>::G::_w<_func>::_)


class Module {
    const char* name_;
    std::vector<R_CMethodDef> routines_;

public:
    Module(const char* name)
        : name_(name)
        , routines_()
    {}

    template <typename F> void __() {}

    template <typename RET, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, RET (*F) (A1, A2, A3, A4, A5, A6)>
    Module& _(const char* name) {}
    template <typename RET, typename A1, typename A2, typename A3, RET (*F) (A1, A2, A3)>
    Module& _(const char* name) {}

    Module& _reg(const char* name, int argc, DL_FUNC wrapper) {
        std::cout << "Registering new routine :" << std::endl;
        std::cout << "   - name: " << name << std::endl;
        std::cout << "   - argc: " << argc << std::endl;
        std::cout << "   - wrap: " << ((void*)wrapper) << std::endl;
        return *this;
    }

};

}

#endif
