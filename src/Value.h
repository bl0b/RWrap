#ifndef _RWRAP_VALUE_H_
#define _RWRAP_VALUE_H_

#include <vector>
#include <string>
#include <cstring>

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


template <>
struct Value<std::string> {
    typedef std::string CType;
    static CType coerceToC(SEXP v) {
        return std::string(CHAR(STRING_ELT(v, 0)));
    }
    static SEXP coerceToR(CType v) {
        return mkString(v.c_str());
    }
};


template <typename T>
SEXP coerceToR(T v) { return Value<T>::coerceToR(v); }



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

template <> struct RVecTraits<bool> {
    enum { type=LGLSXP };
    typedef bool value_type;
    typedef int* RContainerType;
    typedef std::vector<bool> CVecType;
    static RContainerType initRC(SEXP value) {
        return LOGICAL(value);
    }
    static void Rset(RContainerType rc, CVecType& cc, int i) {
        rc[i] = cc[i];
    }
    static void Cset(CVecType& cc, RContainerType rc, int i) {
        cc.push_back(rc[i]);
    }
};

template <> struct RVecTraits<float> {
    enum { type=SINGLESXP };
    /* should be avoided and coerced into double somewhere else */
};

template <> struct RVecTraits<std::string> {
    enum { type=STRSXP };
    typedef std::string value_type;
    typedef SEXP RContainerType;
    typedef std::vector<std::string> CVecType;
    static RContainerType initRC(SEXP value) { return value; }
    static void Rset(RContainerType rc, CVecType& cc, int i) {
        SET_STRING_ELT(rc, i, asChar(Value<value_type>::coerceToR(cc[i])));
    }
    static void Cset(CVecType& cc, RContainerType rc, int i) {
        cc.push_back(CHAR(STRING_ELT(rc, i)));
    }
};

template <> struct RVecTraits<char*> {
    enum { type=STRSXP };
    typedef char* value_type;
    typedef SEXP RContainerType;
    typedef std::vector<char*> CVecType;
    static RContainerType initRC(SEXP value) { return value; }
    static void Rset(RContainerType rc, CVecType& cc, int i) {
        SET_STRING_ELT(rc, i, asChar(Value<value_type>::coerceToR(cc[i])));
    }
    static void Cset(CVecType& cc, RContainerType rc, int i) {
        cc.push_back(const_cast<char*>(CHAR(STRING_ELT(rc, i))));
    }
};

template <> struct RVecTraits<const char*> {
    enum { type=STRSXP };
    typedef const char* value_type;
    typedef SEXP RContainerType;
    typedef std::vector<const char*> CVecType;
    static RContainerType initRC(SEXP value) { return value; }
    static void Rset(RContainerType rc, CVecType& cc, int i) {
        SET_STRING_ELT(rc, i, asChar(Value<value_type>::coerceToR(cc[i])));
    }
    static void Cset(CVecType& cc, RContainerType rc, int i) {
        cc.push_back(CHAR(STRING_ELT(rc, i)));
    }
};

template <typename T>
struct Value<std::vector<T> > {
    enum { type=VECSXP };
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
        ret.reserve(length(v));
        typename vtraits::RContainerType buf = vtraits::initRC(v);
        for(int i = 0; i < length(v); ++i) {
            vtraits::Cset(ret, buf, i);
        }
        return ret;
    }
};


struct generic_value {
    SEXP v;
    generic_value(SEXP _) : v(_) {}
    template <typename T>
    operator T() const { return Value<T>::coerceToC(v); }
};


class List {
    private:
        std::vector<const char*> names_;
        std::vector<SEXP> elements_;
    public:
        List()
            : names_(), elements_()
        {}

        List(SEXP list)
            : names_(), elements_()
        {
            int n = length(list);
            SEXP nm = getAttrib(list, R_NamesSymbol);
            for(int i = 0; i < n; ++i) {
                elements_.push_back(VECTOR_ELT(list, i));
                names_.push_back(CHAR(STRING_ELT(nm, i)));
            }
        }

        generic_value operator[](int i) const {
            return generic_value(elements_.at(i));
        }

        generic_value operator[](const char* n) const {
            int i;
            for (i = 0; i < names_.size() && (!names_[i] || strcmp(names_[i], n)); ++i);
            if (i == names_.size()) {
                return NULL;
            }
            return generic_value(elements_.at(i));
        }

        template <typename T>
        List& add(const char* name, T elem) {
            names_.push_back(name);
            SEXP e;
            PROTECT(e = Value<T>::coerceToR(elem));
            elements_.push_back(e);
            return *this;
        }

        virtual SEXP toR() const {
            int n = names_.size();
            SEXP ret;
            SEXP names;
            PROTECT(ret = allocVector(VECSXP, n));
            PROTECT(names = allocVector(VECSXP, n));
            for(int i = 0; i < n; i++) {
                SET_VECTOR_ELT(names, i, Value<const char*>::coerceToR(names_[i]));
                SET_VECTOR_ELT(ret, i, elements_[i]);
            }
            setAttrib(ret, R_NamesSymbol, names);
            UNPROTECT(2 + n);
            return ret;
        }
};

class DataFrame : public List {
    public:
        DataFrame() : List() {}
        DataFrame(SEXP e) : List(e) {}
        virtual SEXP toR() const {
            SEXP expr;
            PROTECT(expr = allocList(2));
            SET_TYPEOF(expr, LANGSXP);
            SETCAR(expr, install("as.data.frame"));
            SETCADR(expr, List::toR());
            UNPROTECT(1);
            return eval(expr, R_GlobalEnv);
        }
};


template <>
struct Value<List> {
    typedef List CType;
    static SEXP coerceToR(CType v) {
        return v.toR();
    }
    static List coerceToC(SEXP v) {
        return List(v);
    }
};

template <>
struct Value<DataFrame> {
    typedef DataFrame CType;
    static SEXP coerceToR(CType v) {
        return v.toR();
    }
    static CType coerceToC(SEXP v) {
        return DataFrame(v);
    }
};

}

#endif

