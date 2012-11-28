#ifndef _RWRAP_GEN_WRAP_H_
#define _RWRAP_GEN_WRAP_H_

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

namespace Rwrap {

template <typename RET,
          typename A1=void, typename A2=void, typename A3=void,
          typename A4=void, typename A5=void, typename A6=void>
struct _gen_;

template <>
struct _gen_<void, void, void, void, void, void, void> {
    template<void (*F)()>
    struct _w {
        static SEXP _() {
            F();
            return NULL;
        }
    };
};

template <typename RET>
struct _gen_<RET, void, void, void, void, void, void> {
    template<void (*F)()>
    struct _w {
        static SEXP _() {
            return Value<RET>::coerceToR(F());
        }
    };
};

template <typename A1>
struct _gen_<void, A1, void, void, void, void, void> {
    template<void (*F)(A1)>
    struct _w {
        static SEXP _(A1 a) {
            F(Value<A1>::coerceToC(a));
            return NULL;
        }
    };
};

template <typename RET, typename A1>
struct _gen_<RET, A1, void, void, void, void, void> {
    template<RET (*F)(A1)>
    struct _w {
        static SEXP _(A1 a) {
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a)));
        }
    };
};

template <typename A1, typename A2>
struct _gen_<void, A1, A2, void, void, void, void> {
    template<void (*F)(A1, A2)>
    struct _w {
        static SEXP _(A1 a, A2 b) {
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b));
            return NULL;
        }
    };
};

template <typename RET, typename A1, typename A2>
struct _gen_<RET, A1, A2, void, void, void, void> {
    template<RET (*F)(A1, A2)>
    struct _w {
        static SEXP _(A1 a) {
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b)));
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3>
struct _gen_<RET, A1, A2, A3, void, void, void> {
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
struct _gen_<A1, A2, A3, void, void, void> {
    template<RET (*F)(A1, A2, A3)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c) {
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c));
            return NULL;
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4>
struct _gen_<RET, A1, A2, A3, A4, void, void> {
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

template <typename A1, typename A2, typename A3, typename A4, typename A5>
struct _gen_<A1, A2, A3, A4, A5, void> {
    template<RET (*F)(A1, A2, A3, A4, A5)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e) {
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e));
            return NULL;
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5>
struct _gen_<RET, A1, A2, A3, A4, A5, void> {
    template<RET (*F)(A1, A2, A3, A4, A5)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e) {
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A3>::coerceToC(d),
                                           Value<A4>::coerceToC(e)));
        }
    };
};

template <typename A1, typename A2, typename A3, typename A4, typename A5>
struct _gen_<A1, A2, A3, A4, A5, void> {
    template<RET (*F)(A1, A2, A3, A4, A5)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e) {
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e));
            return NULL;
        }
    };
};

template <typename RET, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6>
struct _gen_<RET, A1, A2, A3, A4, A5, A6> {
    template<RET (*F)(A1, A2, A3, A4, A5, A6)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f) {
            return Value<RET>::coerceToR(F(Value<A1>::coerceToC(a),
                                           Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A3>::coerceToC(d),
                                           Value<A3>::coerceToC(e),
                                           Value<A4>::coerceToC(f)));
        }
    };
};

template <typename A1, typename A2, typename A3, typename A4, typename A5,
          typename A6>
struct _gen_<A1, A2, A3, A4, A5, A6> {
    template<RET (*F)(A1, A2, A3, A4, A5, A6)>
    struct _w {
        static SEXP _(SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f) {
            F(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
              Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
              Value<A5>::coerceToC(e), Value<A6>::coerceToC(f));
            return NULL;
        }
    };
};


/* front-end */

template <typename F>
struct gen : public _gen_<typename F::ret_t, typename F::a1_t,
                          typename F::a2_t, typename F::a3_t, typename F::a4_t,
                          typename F::a5_t, typename F::a6_t> {
    using _gen_<typename F::ret_t, typename F::a1_t, typename F::a2_t,
                typename F::a3_t, typename F::a4_t, typename F::a5_t,
                typename F::a6_t>::_w;
};


}

#endif

