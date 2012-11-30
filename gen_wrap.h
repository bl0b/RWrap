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
            F();
            return R_NilValue;
        }
    };
};

template <typename RET>
struct _gen_<RET> {
    template<RET (*F)()>
    struct _w {
        static SEXP _() {
            return Value<RET>::coerceToR(F());
        }
    };
};

/* 1 */

template <typename A1>
struct _gen_<void, A1> {
    template<void (*F)(A1)>
    struct _w {
        static SEXP _(SEXP a) {
            F(Value<A1>::coerceToC(a));
            return R_NilValue;
        }
    };
};

template <typename RET, typename A1>
struct _gen_<RET, A1> {
    template<RET (*F)(A1)>
    struct _w {
        static SEXP _(SEXP a) {
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a)));
        }
    };
};

/* 2 */

template <typename A1, typename A2>
struct _gen_<void, A1, A2> {
    template<void (*F)(A1, A2)>
    struct _w {
        static SEXP _(SEXP a, SEXP b) {
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b));
            return R_NilValue;
        }
    };
};

template <typename RET, typename A1, typename A2>
struct _gen_<RET, A1, A2> {
    template<RET (*F)(A1, A2)>
    struct _w {
        static SEXP _(SEXP a, SEXP b) {
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b)));
        }
    };
};

/* 3 */

template <typename RET, typename A1, typename A2, typename A3>
struct _gen_<RET, A1, A2, A3> {
    template<RET (*F)(A1, A2, A3)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c) {
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c)));
        }
    };
};

template <typename A1, typename A2, typename A3>
struct _gen_<void, A1, A2, A3> {
    template<void (*F)(A1, A2, A3)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c) {
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c));
            return R_NilValue;
        }
    };
};

/* 4 */

template <typename RET, typename A1, typename A2, typename A3, typename A4>
struct _gen_<RET, A1, A2, A3, A4> {
    template<RET (*F)(A1, A2, A3, A4)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d) {
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A4>::coerceToC(d)));
        }
    };
};

template <typename A1, typename A2, typename A3, typename A4>
struct _gen_<void, A1, A2, A3, A4> {
    template<void (*F)(A1, A2, A3, A4)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d) {
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d));
            return R_NilValue;
        }
    };
};

/* 5 */

template <typename A1, typename A2, typename A3, typename A4, typename A5>
struct _gen_<void, A1, A2, A3, A4, A5> {
    template<void (*F)(A1, A2, A3, A4, A5)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e) {
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e));
            return R_NilValue;
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5>
struct _gen_<RET, A1, A2, A3, A4, A5> {
    template<RET (*F)(A1, A2, A3, A4, A5)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e) {
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A4>::coerceToC(d),
                                           Value<A5>::coerceToC(e)));
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
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A4>::coerceToC(d),
                                           Value<A5>::coerceToC(e),
                                           Value<A6>::coerceToC(f)));
        }
    };
};

template <typename A1, typename A2, typename A3, typename A4, typename A5,
          typename A6>
struct _gen_<void, A1, A2, A3, A4, A5, A6> {
    template<void (*F)(A1, A2, A3, A4, A5, A6)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f) {
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f));
            return R_NilValue;
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
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
              Value<A7>::coerceToC(g));
            return R_NilValue;
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7>
struct _gen_<RET, A1, A2, A3, A4, A5, A6, A7> {
    template<RET (*F)(A1, A2, A3, A4, A5, A6, A7)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f, SEXP g) {
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A4>::coerceToC(d),
                                           Value<A5>::coerceToC(e),
                                           Value<A6>::coerceToC(f),
                                           Value<A7>::coerceToC(g)));
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
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
              Value<A7>::coerceToC(g), Value<A8>::coerceToC(h));
            return R_NilValue;
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
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A4>::coerceToC(d),
                                           Value<A5>::coerceToC(e),
                                           Value<A6>::coerceToC(f),
                                           Value<A7>::coerceToC(g),
                                           Value<A8>::coerceToC(h)));
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
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
              Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
              Value<A9>::coerceToC(i));
            return R_NilValue;
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
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A4>::coerceToC(d),
                                           Value<A5>::coerceToC(e),
                                           Value<A6>::coerceToC(f),
                                           Value<A7>::coerceToC(g),
                                           Value<A8>::coerceToC(h),
                                           Value<A9>::coerceToC(i)));
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
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
              Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
              Value<A9>::coerceToC(i), Value<A10>::coerceToC(j));
            return R_NilValue;
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
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A4>::coerceToC(d),
                                           Value<A5>::coerceToC(e),
                                           Value<A6>::coerceToC(f),
                                           Value<A7>::coerceToC(g),
                                           Value<A8>::coerceToC(h),
                                           Value<A9>::coerceToC(i),
                                           Value<A10>::coerceToC(j)));
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
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
              Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
              Value<A9>::coerceToC(i), Value<A10>::coerceToC(j),
              Value<A11>::coerceToC(k));
            return R_NilValue;
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
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A4>::coerceToC(d),
                                           Value<A5>::coerceToC(e),
                                           Value<A6>::coerceToC(f),
                                           Value<A7>::coerceToC(g),
                                           Value<A8>::coerceToC(h),
                                           Value<A9>::coerceToC(i),
                                           Value<A10>::coerceToC(j),
                                           Value<A11>::coerceToC(k)));
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
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
              Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
              Value<A9>::coerceToC(i), Value<A10>::coerceToC(j),
              Value<A11>::coerceToC(k), Value<A12>::coerceToC(l));
            return R_NilValue;
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
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
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
                                           Value<A12>::coerceToC(l)));
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
                typename F::a6_t>::_w;
};


}

#endif

