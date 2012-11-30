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
struct Value<SEXP> {
    typedef SEXP CType;
    static SEXP coerceToR(CType v) { return v; }
    static CType coerceToC(SEXP v) { return v; }
};

template <>
struct Value<int> {
    typedef int CType;
    static CType coerceToC(SEXP v) {
        return asInteger(v);
    }
    static SEXP coerceToR(CType v) {
        return ScalarInteger(v);
    }
};


template <>
struct Value<double> {
    typedef double CType;
    static CType coerceToC(SEXP v) {
        return asReal(v);
    }
    static SEXP coerceToR(CType v) {
        return ScalarReal(v);
    }
};


template <>
struct Value<const char*> {
    typedef const char* CType;
    static CType coerceToC(SEXP v) {
        return CHAR(STRING_ELT(v, 0));
    }
    static SEXP coerceToR(CType v) {
        return mkString(v);
    }
};


template <>
struct Value<char*> {
    typedef char* CType;
    static CType coerceToC(SEXP v) {
        return const_cast<CType>(CHAR(STRING_ELT(v, 0)));
    }
    static SEXP coerceToR(CType v) {
        return mkString(v);
    }
};


template <typename T>
SEXP coerceToR(T v) { return Value<T>::coerceToR(v); }





class List {
    private:
        std::vector<const char*> names_;
        std::vector<SEXP> elements_;
    public:
        List()
            : names_(), elements_()
        {}

        template <typename T>
        List& add(const char* name, T elem) {
            names_.push_back(name);
            SEXP e;
            PROTECT(e = Value<T>::coerceToR(elem));
            elements_.push_back(e);
            return *this;
        }

        SEXP toR() const {
            int n = names_.size();
            SEXP ret;
            SEXP names;
            PROTECT(ret = allocVector(VECSXP, n));
            PROTECT(names = allocVector(VECSXP, n));
            for(int i = 0; i < n; i++) {
                std::cout << i << ": " << names_[i] << " " << elements_[i] << std::endl;
                SET_VECTOR_ELT(names, i, Value<const char*>::coerceToR(names_[i]));
                SET_VECTOR_ELT(ret, i, elements_[i]);
            }
            setAttrib(ret, R_NamesSymbol, names);
            UNPROTECT(2 + n);
            return ret;
        }
};


template <>
struct Value<List> {
    typedef List CType;
    static SEXP coerceToR(CType& v) {
        return v.toR();
    }
};


}

#endif

