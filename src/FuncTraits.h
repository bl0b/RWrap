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

#ifndef _RWRAP_FUNCTRAITS_H_
#define _RWRAP_FUNCTRAITS_H_

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

namespace Rwrap {

/*#define _FT(_func) boost::add_pointer<BOOST_TYPEOF(_func) >::type*/
template <typename T>
struct add_ptr {
    typedef T* type;
};
template <typename T>
struct remove_ptr {
    typedef T type;
};
template <typename T>
struct remove_ptr<T*> {
    typedef T type;
};

template <typename Function>
struct FuncTraits;

template <typename RET,
          typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8,
          typename A9, typename A10, typename A11, typename A12>
struct FuncTraits<RET (*)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)> {
    enum { ArgCount=12 };
    typedef RET (*type)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
    template <class C> struct method { typedef RET(C::*type)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef A6 a6_t;
    typedef A7 a7_t;
    typedef A8 a8_t;
    typedef A9 a9_t;
    typedef A10 a10_t;
    typedef A11 a11_t;
    typedef A12 a12_t;
};

template <typename RET,
          typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8,
          typename A9, typename A10, typename A11>
struct FuncTraits<RET (*)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)> {
    enum { ArgCount=11 };
    typedef RET (*type)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
    template <class C> struct method { typedef RET(C::*type)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef A6 a6_t;
    typedef A7 a7_t;
    typedef A8 a8_t;
    typedef A9 a9_t;
    typedef A10 a10_t;
    typedef A11 a11_t;
    typedef void a12_t;
};

template <typename RET,
          typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8,
          typename A9, typename A10>
struct FuncTraits<RET (*)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)> {
    enum { ArgCount=10 };
    typedef RET (*type)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
    template <class C> struct method { typedef RET(C::*type)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef A6 a6_t;
    typedef A7 a7_t;
    typedef A8 a8_t;
    typedef A9 a9_t;
    typedef A10 a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <typename RET,
          typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8,
          typename A9>
struct FuncTraits<RET (*)(A1, A2, A3, A4, A5, A6, A7, A8, A9)> {
    enum { ArgCount=9 };
    typedef RET (*type)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
    template <class C> struct method { typedef RET(C::*type)(A1, A2, A3, A4, A5, A6, A7, A8, A9); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef A6 a6_t;
    typedef A7 a7_t;
    typedef A8 a8_t;
    typedef A9 a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <typename RET,
          typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8>
struct FuncTraits<RET (*)(A1, A2, A3, A4, A5, A6, A7, A8)> {
    enum { ArgCount=8 };
    typedef RET (*type)(A1, A2, A3, A4, A5, A6, A7, A8);
    template <class C> struct method { typedef RET(C::*type)(A1, A2, A3, A4, A5, A6, A7, A8); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef A6 a6_t;
    typedef A7 a7_t;
    typedef A8 a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <typename RET,
          typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7>
struct FuncTraits<RET (*)(A1, A2, A3, A4, A5, A6, A7)> {
    enum { ArgCount=7 };
    typedef RET (*type)(A1, A2, A3, A4, A5, A6, A7);
    template <class C> struct method { typedef RET(C::*type)(A1, A2, A3, A4, A5, A6, A7); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef A6 a6_t;
    typedef A7 a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <typename RET,
          typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6>
struct FuncTraits<RET (*)(A1, A2, A3, A4, A5, A6)> {
    enum { ArgCount=6 };
    typedef RET (*type)(A1, A2, A3, A4, A5, A6);
    template <class C> struct method { typedef RET(C::*type)(A1, A2, A3, A4, A5, A6); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef A6 a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <typename RET,
          typename A1, typename A2, typename A3, typename A4, typename A5>
struct FuncTraits<RET (*) (A1, A2, A3, A4, A5)> {
    enum { ArgCount=5 };
    typedef RET (*type)(A1, A2, A3, A4, A5);
    template <class C> struct method { typedef RET(C::*type)(A1, A2, A3, A4, A5); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <typename RET,
          typename A1, typename A2, typename A3, typename A4>
struct FuncTraits<RET (*) (A1, A2, A3, A4)> {
    enum { ArgCount=4 };
    typedef RET (*type)(A1, A2, A3, A4);
    template <class C> struct method { typedef RET(C::*type)(A1, A2, A3, A4); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef void a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <typename RET,
          typename A1, typename A2, typename A3>
struct FuncTraits<RET (*) (A1, A2, A3)> {
    enum { ArgCount=3 };
    typedef RET (*type)(A1, A2, A3);
    template <class C> struct method { typedef RET(C::*type)(A1, A2, A3); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <typename RET,
          typename A1, typename A2>
struct FuncTraits<RET (*) (A1, A2)> {
    enum { ArgCount=2 };
    typedef RET (*type)(A1, A2);
    template <class C> struct method { typedef RET(C::*type)(A1, A2); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef void a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <typename RET,
          typename A1>
struct FuncTraits<RET (*) (A1)> {
    enum { ArgCount=1 };
    typedef RET (*type)(A1);
    template <class C> struct method { typedef RET(C::*type)(A1); };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef void a2_t;
    typedef void a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <typename RET>
struct FuncTraits<RET (*) ()> {
    enum { ArgCount=0 };
    typedef RET (*type)();
    template <class C> struct method { typedef RET(C::*type)(); };
    typedef RET ret_t;
    typedef void a1_t;
    typedef void a2_t;
    typedef void a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

#if 1
template <class C, typename RET,
          typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6>
struct FuncTraits<RET (C::*) (A1, A2, A3, A4, A5, A6)> {
    enum { ArgCount=6 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <class C, typename RET,
          typename A1, typename A2, typename A3, typename A4,
          typename A5>
struct FuncTraits<RET (C::*) (A1, A2, A3, A4, A5)> {
    enum { ArgCount=5 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef A5 a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <class C, typename RET,
          typename A1, typename A2, typename A3, typename A4>
struct FuncTraits<RET (C::*) (A1, A2, A3, A4)> {
    enum { ArgCount=4 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef A4 a4_t;
    typedef void a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <class C, typename RET,
          typename A1, typename A2, typename A3>
struct FuncTraits<RET (C::*) (A1, A2, A3)> {
    enum { ArgCount=3 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef A3 a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <class C, typename RET,
          typename A1, typename A2>
struct FuncTraits<RET (C::*) (A1, A2)> {
    enum { ArgCount=2 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef A2 a2_t;
    typedef void a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <class C, typename RET,
          typename A1>
struct FuncTraits<RET (C::*) (A1)> {
    enum { ArgCount=1 };
    typedef RET ret_t;
    typedef A1 a1_t;
    typedef void a2_t;
    typedef void a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};

template <class C, typename RET>
struct FuncTraits<RET (C::*) ()> {
    enum { ArgCount=0 };
    typedef RET ret_t;
    typedef void a1_t;
    typedef void a2_t;
    typedef void a3_t;
    typedef void a4_t;
    typedef void a5_t;
    typedef void a6_t;
    typedef void a7_t;
    typedef void a8_t;
    typedef void a9_t;
    typedef void a10_t;
    typedef void a11_t;
    typedef void a12_t;
};
#endif

}

#define _FT(_func) Rwrap::add_ptr<__typeof__ _func>::type
#define _MT(_func) __typeof__ _func

#endif

