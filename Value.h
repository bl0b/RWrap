#ifndef _RWRAP_VALUE_H_
#define _RWRAP_VALUE_H_

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

namespace Rwrap {
/*numeric 	REALSXP */
/*integer 	INTSXP */
/*logical 	LGLSXP */
/*single 	SINGLESXP */
/*character STRSXP */
/*list  	VECSXP*/

template <typename T> struct Value {};
template <> struct Value<void> {};


template <>
struct Value<int> {
    typedef int CType;
    static int coerceToC(SEXP v) {
        return asInteger(v);
    }
    static SEXP coerceToR(int v) {
        return ScalarInteger(v);
    }
};


template <>
struct Value<double> {
    typedef double CType;
    static int coerceToC(SEXP v) {
        return asReal(v);
    }
    static SEXP coerceToR(int v) {
        return ScalarReal(v);
    }
};

}

#endif

