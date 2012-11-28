#ifndef _RWRAP_GEN_WRAP_H_
#define _RWRAP_GEN_WRAP_H_

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

namespace Rwrap {

template <typename Function>
struct FuncTraits;

template <typename RET,
          typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6>
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

template <typename RET,
          typename A1, typename A2, typename A3, typename A4, typename A5>
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

template <typename RET,
          typename A1, typename A2, typename A3, typename A4>
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

template <typename RET,
          typename A1, typename A2, typename A3>
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

template <typename RET,
          typename A1, typename A2>
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

template <typename RET,
          typename A1>
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
};


}

#endif

