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

#ifndef _RWRAP_GEN_WRAP_H_
#define _RWRAP_GEN_WRAP_H_

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

namespace Rwrap {

template <typename RET,
          typename A1=void, typename A2=void, typename A3=void,
          typename A4=void, typename A5=void, typename A6=void,
          typename A7=void, typename A8=void, typename A9=void,
          typename A10=void, typename A11=void, typename A12=void,
          typename _PLACEHOLDER=void>
struct _gen_;
/* placeholder is required so the compiler treats all subsequent specializations
 * as partial specializations. We don't really care about this argument, provided
 * no routine ever has more than twelve (!) arguments.
 * Although this could happen, in R. It's a matter of design, then. Twelve is WAY
 * TOO MUCH already anyways.
 */



/* 0 */

template <>
struct _gen_<void> {
    template<void (*F)()>
    struct _w {
        static SEXP _() {
            SANDBOXED_NORET(F());
        }
    };
    template <class C>
    struct _mw {
        template <void (C::*F)()>
        struct _w {
            static SEXP _(SEXP _ptr) {
                C* this_ = Value<C*>::coerceToC(_ptr);
                SANDBOXED_NORET((this_->*F)());
            }
        };
    };
};

template <typename RET>
struct _gen_<RET> {
    template<RET (*F)()>
    struct _w {
        static SEXP _() {
            SANDBOXED_RET(Value<RET>::coerceToR(F()));
        }
    };
    template <class C, RET (C::*F)()>
    struct _mw {
        static SEXP _(SEXP _ptr) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            SANDBOXED_RET(Value<RET>::coerceToR(this_->F()));
        }
    };
};

/* 1 */

template <typename A1>
struct _gen_<void, A1> {
    template<void (*F)(A1)>
    struct _w {
        static SEXP _(SEXP a) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a)));
        }
    };
};

template <typename RET, typename A1>
struct _gen_<RET, A1> {
    template<RET (*F)(A1)>
    struct _w {
        static SEXP _(SEXP a) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a))));
        }
    };
};

/* 2 */

template <typename A1, typename A2>
struct _gen_<void, A1, A2> {
    template<void (*F)(A1, A2)>
    struct _w {
        static SEXP _(SEXP a, SEXP b) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b)));
        }
    };
};

template <typename RET, typename A1, typename A2>
struct _gen_<RET, A1, A2> {
    template<RET (*F)(A1, A2)>
    struct _w {
        static SEXP _(SEXP a, SEXP b) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b))));
        }
    };
};

/* 3 */

template <typename RET, typename A1, typename A2, typename A3>
struct _gen_<RET, A1, A2, A3> {
    template<RET (*F)(A1, A2, A3)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b),
                                                  Value<A3>::coerceToC(c))));
        }
    };
};

template <typename A1, typename A2, typename A3>
struct _gen_<void, A1, A2, A3> {
    template<void (*F)(A1, A2, A3)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                              Value<A3>::coerceToC(c)));
        }
    };
};

/* 4 */

template <typename RET, typename A1, typename A2, typename A3, typename A4>
struct _gen_<RET, A1, A2, A3, A4> {
    template<RET (*F)(A1, A2, A3, A4)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b),
                                                  Value<A3>::coerceToC(c),
                                                  Value<A4>::coerceToC(d))));
        }
    };
};

template <typename A1, typename A2, typename A3, typename A4>
struct _gen_<void, A1, A2, A3, A4> {
    template<void (*F)(A1, A2, A3, A4)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d)));
        }
    };
};

/* 5 */

template <typename A1, typename A2, typename A3, typename A4, typename A5>
struct _gen_<void, A1, A2, A3, A4, A5> {
    template<void (*F)(A1, A2, A3, A4, A5)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                              Value<A5>::coerceToC(e)));
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5>
struct _gen_<RET, A1, A2, A3, A4, A5> {
    template<RET (*F)(A1, A2, A3, A4, A5)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b),
                                                  Value<A3>::coerceToC(c),
                                                  Value<A4>::coerceToC(d),
                                                  Value<A5>::coerceToC(e))));
        }
    };
};

/* 6 */

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6>
struct _gen_<RET, A1, A2, A3, A4, A5, A6> {
    template<RET (*F)(A1, A2, A3, A4, A5, A6)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b),
                                                  Value<A3>::coerceToC(c),
                                                  Value<A4>::coerceToC(d),
                                                  Value<A5>::coerceToC(e),
                                                  Value<A6>::coerceToC(f))));
        }
    };
};

template <typename A1, typename A2, typename A3, typename A4, typename A5,
          typename A6>
struct _gen_<void, A1, A2, A3, A4, A5, A6> {
    template<void (*F)(A1, A2, A3, A4, A5, A6)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f)));
        }
    };
};

/* 7 */

template <typename A1, typename A2, typename A3, typename A4, typename A5,
          typename A6, typename A7>
struct _gen_<void, A1, A2, A3, A4, A5, A6, A7> {
    template<void (*F)(A1, A2, A3, A4, A5, A6, A7)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                              Value<A7>::coerceToC(g)));
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7>
struct _gen_<RET, A1, A2, A3, A4, A5, A6, A7> {
    template<RET (*F)(A1, A2, A3, A4, A5, A6, A7)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b),
                                                  Value<A3>::coerceToC(c),
                                                  Value<A4>::coerceToC(d),
                                                  Value<A5>::coerceToC(e),
                                                  Value<A6>::coerceToC(f),
                                                  Value<A7>::coerceToC(g))));
        }
    };
};

/* 8 */

template <typename A1, typename A2, typename A3, typename A4, typename A5,
          typename A6, typename A7, typename A8>
struct _gen_<void, A1, A2, A3, A4, A5, A6, A7, A8> {
    template<void (*F)(A1, A2, A3, A4, A5, A6, A7, A8)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g,
                      SEXP h) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                              Value<A7>::coerceToC(g), Value<A8>::coerceToC(h)));
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8>
struct _gen_<RET, A1, A2, A3, A4, A5, A6, A7, A8> {
    template<RET (*F)(A1, A2, A3, A4, A5, A6, A7, A8)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g,
                      SEXP h) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b),
                                                  Value<A3>::coerceToC(c),
                                                  Value<A4>::coerceToC(d),
                                                  Value<A5>::coerceToC(e),
                                                  Value<A6>::coerceToC(f),
                                                  Value<A7>::coerceToC(g),
                                                  Value<A8>::coerceToC(h))));
        }
    };
};

/* 9 */

template <typename A1, typename A2, typename A3, typename A4, typename A5,
          typename A6, typename A7, typename A8, typename A9>
struct _gen_<void, A1, A2, A3, A4, A5, A6, A7, A8, A9> {
    template<void (*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g,
                      SEXP h, SEXP i) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                              Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
                              Value<A9>::coerceToC(i)));
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9>
struct _gen_<RET, A1, A2, A3, A4, A5, A6, A7, A8, A9> {
    template<RET (*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g,
                      SEXP h, SEXP i) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b),
                                                  Value<A3>::coerceToC(c),
                                                  Value<A4>::coerceToC(d),
                                                  Value<A5>::coerceToC(e),
                                                  Value<A6>::coerceToC(f),
                                                  Value<A7>::coerceToC(g),
                                                  Value<A8>::coerceToC(h),
                                                  Value<A9>::coerceToC(i))));
        }
    };
};

/* 10 */

template <typename A1, typename A2, typename A3, typename A4, typename A5,
          typename A6, typename A7, typename A8, typename A9, typename A10>
struct _gen_<void, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10> {
    template<void (*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g,
                      SEXP h, SEXP i, SEXP j) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                              Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
                              Value<A9>::coerceToC(i), Value<A10>::coerceToC(j)));
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9,
          typename A10>
struct _gen_<RET, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10> {
    template<RET (*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g,
                      SEXP h, SEXP i, SEXP j) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b),
                                                  Value<A3>::coerceToC(c),
                                                  Value<A4>::coerceToC(d),
                                                  Value<A5>::coerceToC(e),
                                                  Value<A6>::coerceToC(f),
                                                  Value<A7>::coerceToC(g),
                                                  Value<A8>::coerceToC(h),
                                                  Value<A9>::coerceToC(i),
                                                  Value<A10>::coerceToC(j))));
        }
    };
};

/* 11 */

template <typename A1, typename A2, typename A3, typename A4, typename A5,
          typename A6, typename A7, typename A8, typename A9, typename A10,
          typename A11>
struct _gen_<void, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11> {
    template<void (*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g,
                      SEXP h, SEXP i, SEXP j, SEXP k) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                              Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
                              Value<A9>::coerceToC(i), Value<A10>::coerceToC(j),
                              Value<A11>::coerceToC(k)));
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9,
          typename A10, typename A11>
struct _gen_<RET, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11> {
    template<RET (*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g,
                      SEXP h, SEXP i, SEXP j, SEXP k) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b),
                                                  Value<A3>::coerceToC(c),
                                                  Value<A4>::coerceToC(d),
                                                  Value<A5>::coerceToC(e),
                                                  Value<A6>::coerceToC(f),
                                                  Value<A7>::coerceToC(g),
                                                  Value<A8>::coerceToC(h),
                                                  Value<A9>::coerceToC(i),
                                                  Value<A10>::coerceToC(j),
                                                  Value<A11>::coerceToC(k))));
        }
    };
};

/* 12 */

template <typename A1, typename A2, typename A3, typename A4, typename A5,
          typename A6, typename A7, typename A8, typename A9, typename A10,
          typename A11, typename A12>
struct _gen_<void, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12> {
    template<void (*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g,
                      SEXP h, SEXP i, SEXP j, SEXP k, SEXP l) {
            SANDBOXED_NORET(F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                              Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
                              Value<A9>::coerceToC(i), Value<A10>::coerceToC(j),
                              Value<A11>::coerceToC(k), Value<A12>::coerceToC(l)));
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9,
          typename A10, typename A11, typename A12>
struct _gen_<RET, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12> {
    template<RET (*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g,
                      SEXP h, SEXP i, SEXP j, SEXP k, SEXP l) {
            SANDBOXED_RET(Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                                  Value<A2>::coerceToC(b),
                                                  Value<A3>::coerceToC(c),
                                                  Value<A4>::coerceToC(d),
                                                  Value<A5>::coerceToC(e),
                                                  Value<A6>::coerceToC(f),
                                                  Value<A7>::coerceToC(g),
                                                  Value<A8>::coerceToC(h),
                                                  Value<A9>::coerceToC(i),
                                                  Value<A10>::coerceToC(j),
                                                  Value<A11>::coerceToC(k),
                                                  Value<A12>::coerceToC(l))));
        }
    };
};


/* front-end */

template <typename F>
struct gen : public _gen_<typename F::ret_t, typename F::a1_t,
                          typename F::a2_t, typename F::a3_t, typename F::a4_t,
                          typename F::a5_t, typename F::a6_t, typename F::a7_t,
                          typename F::a8_t, typename F::a9_t, typename F::a10_t,
                          typename F::a11_t, typename F::a12_t> {
    using _gen_<typename F::ret_t, typename F::a1_t, typename F::a2_t,
                typename F::a3_t, typename F::a4_t, typename F::a5_t,
                typename F::a6_t, typename F::a7_t, typename F::a8_t,
                typename F::a9_t, typename F::a10_t, typename F::a11_t,
                typename F::a12_t>::_w;
};


}

#endif

