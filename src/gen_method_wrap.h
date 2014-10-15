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

#ifndef _RWRAP_GEN_METHOD_WRAP_H_
#define _RWRAP_GEN_METHOD_WRAP_H_

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

namespace Rwrap {

template <class C, typename RET,
          typename A1=void, typename A2=void, typename A3=void,
          typename A4=void, typename A5=void, typename A6=void,
          typename A7=void, typename A8=void, typename A9=void,
          typename A10=void, typename A11=void, typename A12=void,
          typename _PLACEHOLDER=void>
struct _gen_meth_;
/* placeholder is required so the compiler treats all subsequent specializations
 * as partial specializations. We don't really care about this argument, provided
 * no routine ever has more than twelve (!) arguments.
 * Although this could happen, in R. It's a matter of design, then. Twelve is WAY
 * TOO MUCH already anyways.
 */


/* 0 */

template <class C>
struct _gen_meth_<C, void> {
    template <void (C::*F)()>
    struct _w {
        static SEXP _(SEXP _ptr) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            SANDBOXED_NORET((this_->*F)());
        }
    };
};

template <class C, typename RET>
struct _gen_meth_<C, RET> {
    template <RET (C::*F)()>
    struct _w {
        static SEXP _(SEXP _ptr) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            SANDBOXED_RET(Value<RET>::coerceToR((this_->*F)()));
        }
    };
};

/* 1 */

template <class C, typename A1>
struct _gen_meth_<C, void, A1> {
    template<void (C::*F)(A1)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            SANDBOXED_NORET((this_->*F)(Value<A1>::coerceToC(a)));
        }
    };
};

template <class C, typename RET, typename A1>
struct _gen_meth_<C, RET, A1> {
    template<RET (C::*F)(A1)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            SANDBOXED_RET(Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a))));
        }
    };
};

/* 2 */

template <class C, typename A1, typename A2>
struct _gen_meth_<C, void, A1, A2> {
    template<void (C::*F)(A1, A2)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            SANDBOXED_NORET((this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b)));
        }
    };
};

template <class C, typename RET, typename A1, typename A2>
struct _gen_meth_<C, RET, A1, A2> {
    template<RET (C::*F)(A1, A2)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            SANDBOXED_RET(Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
                                                            Value<A2>::coerceToC(b))));
        }
    };
};

/* 3 */

template <class C, typename RET, typename A1, typename A2, typename A3>
struct _gen_meth_<C, RET, A1, A2, A3> {
    template<RET (C::*F)(A1, A2, A3)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            SANDBOXED_RET(Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
                                                            Value<A2>::coerceToC(b),
                                                            Value<A3>::coerceToC(c))));
        }
    };
};

template <class C, typename A1, typename A2, typename A3>
struct _gen_meth_<C, void, A1, A2, A3> {
    template<void (C::*F)(A1, A2, A3)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            SANDBOXED_NORET((this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                                        Value<A3>::coerceToC(c)));
        }
    };
};

/* 4 */

template <class C, typename RET, typename A1, typename A2, typename A3,
          typename A4>
struct _gen_meth_<C, RET, A1, A2, A3, A4> {
    template<RET (C::*F)(A1, A2, A3, A4)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            return Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
                                                   Value<A2>::coerceToC(b),
                                                   Value<A3>::coerceToC(c),
                                                   Value<A4>::coerceToC(d)));
        }
    };
};

template <class C, typename A1, typename A2, typename A3, typename A4>
struct _gen_meth_<C, void, A1, A2, A3, A4> {
    template<void (C::*F)(A1, A2, A3, A4)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            (this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                      Value<A3>::coerceToC(c), Value<A4>::coerceToC(d));
            return R_NilValue;
        }
    };
};

/* 5 */

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5>
struct _gen_meth_<C, void, A1, A2, A3, A4, A5> {
    template<void (C::*F)(A1, A2, A3, A4, A5)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            (this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                      Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                      Value<A5>::coerceToC(e));
            return R_NilValue;
        }
    };
};

template <class C, typename RET, typename A1, typename A2, typename A3,
          typename A4, typename A5>
struct _gen_meth_<C, RET, A1, A2, A3, A4, A5> {
    template<RET (C::*F)(A1, A2, A3, A4, A5)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            return Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
                                                   Value<A2>::coerceToC(b),
                                                   Value<A3>::coerceToC(c),
                                                   Value<A4>::coerceToC(d),
                                                   Value<A5>::coerceToC(e)));
        }
    };
};

/* 6 */

template <class C, typename RET, typename A1, typename A2, typename A3,
          typename A4, typename A5, typename A6>
struct _gen_meth_<C, RET, A1, A2, A3, A4, A5, A6> {
    template<RET (C::*F)(A1, A2, A3, A4, A5, A6)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f)
        {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            return Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
                                                   Value<A2>::coerceToC(b),
                                           Value<A3>::coerceToC(c),
                                           Value<A4>::coerceToC(d),
                                           Value<A5>::coerceToC(e),
                                           Value<A6>::coerceToC(f)));
        }
    };
};

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6>
struct _gen_meth_<C, void, A1, A2, A3, A4, A5, A6> {
    template<void (C::*F)(A1, A2, A3, A4, A5, A6)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f)
        {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            (this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                      Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                      Value<A5>::coerceToC(e), Value<A6>::coerceToC(f));
            return R_NilValue;
        }
    };
};

/* 7 */

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7>
struct _gen_meth_<C, void, A1, A2, A3, A4, A5, A6, A7> {
    template<void (C::*F)(A1, A2, A3, A4, A5, A6, A7)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            (this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                      Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                      Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                      Value<A7>::coerceToC(g));
            return R_NilValue;
        }
    };
};

template <class C, typename RET, typename A1, typename A2, typename A3,
          typename A4, typename A5, typename A6, typename A7>
struct _gen_meth_<C, RET, A1, A2, A3, A4, A5, A6, A7> {
    template<RET (C::*F)(A1, A2, A3, A4, A5, A6, A7)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            return Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
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

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8>
struct _gen_meth_<C, void, A1, A2, A3, A4, A5, A6, A7, A8> {
    template<void (C::*F)(A1, A2, A3, A4, A5, A6, A7, A8)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g, SEXP h) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            (this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                      Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                      Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                      Value<A7>::coerceToC(g), Value<A8>::coerceToC(h));
            return R_NilValue;
        }
    };
};

template <class C, typename RET, typename A1, typename A2, typename A3,
          typename A4, typename A5, typename A6, typename A7, typename A8>
struct _gen_meth_<C, RET, A1, A2, A3, A4, A5, A6, A7, A8> {
    template<RET (C::*F)(A1, A2, A3, A4, A5, A6, A7, A8)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g, SEXP h) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            return Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
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

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9>
struct _gen_meth_<C, void, A1, A2, A3, A4, A5, A6, A7, A8, A9> {
    template<void (C::*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g, SEXP h, SEXP i) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            (this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                      Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                      Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                      Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
                      Value<A9>::coerceToC(i));
            return R_NilValue;
        }
    };
};

template <class C, typename RET, typename A1, typename A2, typename A3,
          typename A4, typename A5, typename A6, typename A7, typename A8,
          typename A9>
struct _gen_meth_<C, RET, A1, A2, A3, A4, A5, A6, A7, A8, A9> {
    template<RET (C::*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g, SEXP h, SEXP i) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            return Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
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

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9,
          typename A10>
struct _gen_meth_<C, void, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10> {
    template<void (C::*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g, SEXP h, SEXP i, SEXP j) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            (this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                      Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                      Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                      Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
                      Value<A9>::coerceToC(i), Value<A10>::coerceToC(j));
            return R_NilValue;
        }
    };
};

template <class C, typename RET, typename A1, typename A2, typename A3,
          typename A4, typename A5, typename A6, typename A7, typename A8,
          typename A9, typename A10>
struct _gen_meth_<C, RET, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10> {
    template<RET (C::*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g, SEXP h, SEXP i, SEXP j) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            return Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
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

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9,
          typename A10, typename A11>
struct _gen_meth_<C, void, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11> {
    template<void (C::*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g, SEXP h, SEXP i, SEXP j, SEXP k) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            (this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                      Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                      Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                      Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
                      Value<A9>::coerceToC(i), Value<A10>::coerceToC(j),
                      Value<A11>::coerceToC(k));
            return R_NilValue;
        }
    };
};

template <class C, typename RET, typename A1, typename A2, typename A3,
          typename A4, typename A5, typename A6, typename A7, typename A8,
          typename A9, typename A10, typename A11>
struct _gen_meth_<C, RET, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11> {
    template<RET (C::*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g, SEXP h, SEXP i, SEXP j, SEXP k) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            return Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
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

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9,
          typename A10, typename A11, typename A12>
struct _gen_meth_<C, void, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12> {
    template<void (C::*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g, SEXP h, SEXP i, SEXP j, SEXP k, SEXP l) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            (this_->*F)(Value<A1>::coerceToC(a), Value<A2>::coerceToC(b),
                      Value<A3>::coerceToC(c), Value<A4>::coerceToC(d),
                      Value<A5>::coerceToC(e), Value<A6>::coerceToC(f),
                      Value<A7>::coerceToC(g), Value<A8>::coerceToC(h),
                      Value<A9>::coerceToC(i), Value<A10>::coerceToC(j),
                      Value<A11>::coerceToC(k), Value<A12>::coerceToC(l));
            return R_NilValue;
        }
    };
};

template <class C, typename RET, typename A1, typename A2, typename A3,
          typename A4, typename A5, typename A6, typename A7, typename A8,
          typename A9, typename A10, typename A11, typename A12>
struct _gen_meth_<C, RET, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12> {
    template<RET (C::*F)(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>
    struct _w {
        static SEXP _(SEXP _ptr, SEXP a, SEXP b, SEXP c, SEXP d, SEXP e, SEXP f,
                      SEXP g, SEXP h, SEXP i, SEXP j, SEXP k, SEXP l) {
            C* this_ = Value<C*>::coerceToC(_ptr);
            if (!this_) { throw NullPtrError(); }
            return Value<RET>::coerceToR((this_->*F)(Value<A1>::coerceToC(a),
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

template <class C, typename F>
struct gen_meth
    : public _gen_meth_<C, typename F::ret_t, typename F::a1_t,
                        typename F::a2_t, typename F::a3_t, typename F::a4_t,
                        typename F::a5_t, typename F::a6_t, typename F::a7_t,
                        typename F::a8_t, typename F::a9_t, typename F::a10_t,
                        typename F::a11_t, typename F::a12_t>
{
    typedef F FT;
    using _gen_meth_<C, typename F::ret_t, typename F::a1_t, typename F::a2_t,
                     typename F::a3_t, typename F::a4_t, typename F::a5_t,
                     typename F::a6_t, typename F::a7_t, typename F::a8_t,
                     typename F::a9_t, typename F::a10_t, typename F::a11_t,
                     typename F::a12_t>::_w;
};


}

#endif

