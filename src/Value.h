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

#ifndef _RWRAP_VALUE_H_
#define _RWRAP_VALUE_H_

#include <vector>
#include <string>
#include <cstring>
#include <typeinfo>
#include <exception>

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

struct Error : public std::exception {
    const char* _what;
    const char* what() const throw() { return _what; }
    Error(const char* _) : _what(_) {}
};

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
struct Value<void*> {
    typedef void* CType;
    static CType coerceToC(SEXP v) {
        void* ret = R_ExternalPtrAddr(v);
        /*std::cerr << "R->C ret=" << ret << std::endl;*/
        return ret;
    }
    static SEXP coerceToR(CType v) {
        /*std::cerr << "C->R ptr=" << v << std::endl;*/
        return R_MakeExternalPtr(v, R_NilValue, R_NilValue);
    }
};

template <typename T>
struct Value<T*> {
    typedef T* CType;
    static CType coerceToC(SEXP v) {
        return static_cast<T*>(Value<void*>::coerceToC(v));
    }
    static SEXP coerceToR(CType v) {
        return Value<void*>::coerceToR(static_cast<void*>(v));
    }
};

template <class C, typename N>
struct ClassWrap {
    typedef C* CType;
    static CType coerceToC(SEXP v) {
        if (isObject(v)) {
            SEXP slot = lang3(install("slot"), v, mkString(".xData"));
            SEXP get = lang3(install("get"), mkString("this.ptr"), slot);
            CType ptr = (CType) Value<void*>::coerceToC(eval(get, R_GlobalEnv));
            if (!ptr) {
                throw Error("NULL pointer");
            }
        } else {
            CType ptr = (CType) Value<void*>::coerceToC(v);
            if (!ptr) {
                throw Error("NULL pointer");
            }
            return ptr;
        }
    }
    static SEXP coerceToR(CType v) {
        SEXP n = lang3(R_DollarSymbol, install(N::name), install("new"));
        SEXP call = lang2(n, Value<void*>::coerceToR(v));
        SET_TAG(CDR(call), install(".ptr"));
        return eval(call, R_GlobalEnv);
    }
};


template <typename INT_TYPE>
INT_TYPE safe_num(SEXP v)
{
    if (!isNumeric(v)) {
        throw Error("Expected a numeric value");
    }
    if (isReal(v)) {
        return (INT_TYPE) asReal(v);
    } else if (isInteger(v)) {
        return (INT_TYPE) asInteger(v);
    } else if (isLogical(v)) {
        return (INT_TYPE) asLogical(v);
    }
}


template <>
struct Value<unsigned long> {
    typedef unsigned long CType;
    static CType coerceToC(SEXP v) {
        return safe_num<CType>(v);
    }
    static SEXP coerceToR(CType v) {
        return ScalarInteger(v);
    }
};

template <>
struct Value<unsigned int> {
    typedef unsigned int CType;
    static CType coerceToC(SEXP v) {
        return safe_num<CType>(v);
    }
    static SEXP coerceToR(CType v) {
        return ScalarInteger(v);
    }
};

template <>
struct Value<long> {
    typedef long CType;
    static CType coerceToC(SEXP v) {
        return safe_num<CType>(v);
    }
    static SEXP coerceToR(CType v) {
        return ScalarInteger(v);
    }
};

template <>
struct Value<int> {
    typedef int CType;
    static CType coerceToC(SEXP v) {
        return safe_num<CType>(v);
    }
    static SEXP coerceToR(CType v) {
        return ScalarInteger(v);
    }
};


template <>
struct Value<double> {
    typedef double CType;
    static CType coerceToC(SEXP v) {
        return safe_num<double>(v);
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
        if (v) {
            return mkString(v);
        } else {
            return R_NilValue;
        }
    }
};


template <>
struct Value<char*> {
    typedef char* CType;
    static CType coerceToC(SEXP v) {
        return const_cast<CType>(CHAR(STRING_ELT(v, 0)));
    }
    static SEXP coerceToR(CType v) {
        if (v) {
            return mkString(v);
        } else {
            return R_NilValue;
        }
    }
};


template <>
struct Value<std::string&> {
    typedef std::string& CType;
    static CType coerceToC(SEXP v) {
        std::string ret(CHAR(STRING_ELT(v, 0)));
        return ret;
    }
    static SEXP coerceToR(CType v) {
        return mkString(v.c_str());
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


inline
SEXP force_int(SEXP v)
{
    SEXP expr;
    PROTECT(expr = allocList(2));
    SET_TYPEOF(expr, LANGSXP);
    SETCAR(expr, install("as.integer"));
    SETCADR(expr, v);
    UNPROTECT(1);
    return eval(expr, R_GlobalEnv);
}



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

template <typename RT, typename CT=RT>
struct PODVecTraits {
    typedef RT* RContainerType;
    typedef std::vector<CT> CVecType;
    static void Rset(RContainerType rc, CVecType& cc, int i) {
        rc[i] = (RT) cc[i];
    }
    static void Cset(CVecType& cc, RContainerType rc, int i) {
        cc.push_back((CT) rc[i]);
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

template <> struct RVecTraits<unsigned long>
    : public PODVecTraits<int, unsigned long>
{
    enum { type=INTSXP };
    typedef unsigned long value_type;
    typedef int* RContainerType;
    static RContainerType initRC(SEXP value) {
        return INTEGER(force_int(value));
    }
    using PODVecTraits<int, unsigned long>::Rset;
    using PODVecTraits<int, unsigned long>::Cset;
};

template <> struct RVecTraits<long> : public PODVecTraits<int, long> {
    enum { type=INTSXP };
    typedef long value_type;
    typedef int* RContainerType;
    static RContainerType initRC(SEXP value) {
        return INTEGER(force_int(value));
    }
    using PODVecTraits<int, long>::Rset;
    using PODVecTraits<int, long>::Cset;
};

template <> struct RVecTraits<unsigned int>
    : public PODVecTraits<int, unsigned int>
{
    enum { type=INTSXP };
    typedef unsigned int value_type;
    typedef int* RContainerType;
    static RContainerType initRC(SEXP value) {
        return INTEGER(force_int(value));
    }
    using PODVecTraits<int, unsigned int>::Rset;
    using PODVecTraits<int, unsigned int>::Cset;
};

template <> struct RVecTraits<int> : public PODVecTraits<int> {
    enum { type=INTSXP };
    typedef int value_type;
    typedef int* RContainerType;
    static RContainerType initRC(SEXP value) {
        return INTEGER(force_int(value));
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
    operator std::vector<std::string>() {
        /* should actually check that class is 'factor'. */
        SEXP levels = getAttrib(v, install("levels"));
        return Value<std::vector<std::string> >::coerceToC(levels ? levels : v);
    }
    operator std::vector<char*>() {
        /* should actually check that class is 'factor'. */
        SEXP levels = getAttrib(v, install("levels"));
        return Value<std::vector<char*> >::coerceToC(levels ? levels : v);
    }
    operator std::vector<const char*>() {
        /* should actually check that class is 'factor'. */
        SEXP levels = getAttrib(v, install("levels"));
        return Value<std::vector<const char*> >::coerceToC(levels ? levels : v);
    }
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
    private:
        SEXP rownames_;
        int protect_count;
    public:
        DataFrame() : List(), rownames_(0), protect_count(0) {}
        DataFrame(SEXP e) : List(e), rownames_(0), protect_count(0) {}
        template <typename StringType>
        void rownames(std::vector<StringType>& names) {
            PROTECT(rownames_ = Value<std::vector<StringType> >::coerceToR(names));
            ++protect_count;
        }
        virtual SEXP toR() const {
            SEXP expr;
            PROTECT(expr = allocList(2 + (rownames_ != 0)));
            SET_TYPEOF(expr, LANGSXP);
            SETCAR(expr, install("as.data.frame"));
            SETCADR(expr, List::toR());
            if (rownames_ != 0) {
                SETCADDR(expr, rownames_);
                SET_TAG(CDDR(expr), install("row.names"));
            }
            UNPROTECT(1 + protect_count);
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

