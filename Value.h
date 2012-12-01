#ifndef _RWRAP_VALUE_H_
#define _RWRAP_VALUE_H_

#include <vector>
#include <string>

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
struct Value<bool> {
    typedef bool CType;
    static CType coerceToC(SEXP v) {
        return asLogical(v);
    }
    static SEXP coerceToR(CType v) {
        return ScalarLogical(v);
    }
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
    static SEXP coerceToR(CType v) {
        return v.toR();
    }
};


template <typename T>
struct RVecTraits {
    enum { type=VECSXP };
    typedef SEXP RContainerType;
    typedef T value_type;
    static RContainerType initRC(SEXP value) {
        return value;
    }
    static void Rset(RContainerType rc, std::vector<T>& cc, int i) {
        SET_VECTOR_ELT(rc, i, Value<T>::coerceToR(cc[i]));
    }
    static void Cset(std::vector<T>& cc, RContainerType rc, int i) {
        cc.push_back(Value<T>::coerceToC(Value<T>::coerceToC(VECTOR_ELT(rc, i))));
    }
};

template <typename T>
struct PODVecTraits {
    typedef T* RContainerType;
    typedef std::vector<T> CVecType;
    static void Rset(RContainerType rc, CVecType& cc, int i) {
        rc[i] = cc[i];
    }
    static void Cset(CVecType& cc, RContainerType rc, int i) {
        cc.push_back(rc[i]);
    }
};

template <> struct RVecTraits<double> : public PODVecTraits<double> {
    enum { type=REALSXP };
    typedef double value_type;
    typedef double* RContainerType;
    static RContainerType initRC(SEXP value) {
        return REAL(value);
    }
    using PODVecTraits<double>::Rset;
    using PODVecTraits<double>::Cset;
};

template <> struct RVecTraits<int> : public PODVecTraits<int> {
    enum { type=INTSXP };
    typedef int value_type;
    typedef int* RContainerType;
    static RContainerType initRC(SEXP value) {
        return INTEGER(value);
    }
    using PODVecTraits<int>::Rset;
    using PODVecTraits<int>::Cset;
};

template <> struct RVecTraits<bool> : public PODVecTraits<int> {
    enum { type=LGLSXP };
    typedef int value_type;
    typedef int* RContainerType;
    static RContainerType initRC(SEXP value) {
        return LOGICAL(value);
    }
    using PODVecTraits<int>::Rset;
    using PODVecTraits<int>::Cset;
};

template <> struct RVecTraits<float> {
    enum { type=SINGLESXP };
    /* should be avoided and coerced into double somewhere else */
};

template <> struct RVecTraits<std::string> { enum { type=STRSXP }; };
template <> struct RVecTraits<char*> { enum { type=STRSXP }; };
template <> struct RVecTraits<const char*> { enum { type=STRSXP }; };

template <typename T>
struct Value<std::vector<T> > {
    typedef std::vector<T> CType;
    typedef RVecTraits<T> vtraits;

    static SEXP coerceToR(CType v) {
        SEXP ret;
        PROTECT(ret = allocVector(vtraits::type, v.size()));
        typename vtraits::RContainerType buf = vtraits::initRC(ret);
        for(int i = 0; i < v.size(); ++i) {
            vtraits::Rset(buf, v, i);
        }
        UNPROTECT(1);
        return ret;
    }

    static CType coerceToC(SEXP v) {
        CType ret;
        std::cout << "R.length = " << (length(v)) << std::endl;
        ret.reserve(length(v));
        typename vtraits::RContainerType buf = vtraits::initRC(v);
        for(int i = 0; i < length(v); ++i) {
            vtraits::Cset(ret, buf, i);
        }
        return ret;
    }
};

}

#endif

