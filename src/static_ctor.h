#ifndef _RWRAP_STATIC_CTOR_H_
#define _RWRAP_STATIC_CTOR_H_

#include <string>
#include <typeinfo>
#include "FuncTraits.h"


namespace Rwrap {
template <typename X> void to_str(std::string&s) { s += typeid(X).name(); }

template <> void to_str<void>(std::string&s) {}

template <typename FSIG>
struct static_ctor_base {
    typedef FuncTraits<typename add_ptr<FSIG>::type> sig_traits;
    typedef gen<sig_traits> G;
    std::string rname, cname;
    static_ctor_base(const char* class_name) {
        rname = class_name;
        rname += ".ctor";
        to_str<typename sig_traits::a1_t>(rname);
        to_str<typename sig_traits::a2_t>(rname);
        to_str<typename sig_traits::a3_t>(rname);
        to_str<typename sig_traits::a4_t>(rname);
        to_str<typename sig_traits::a5_t>(rname);
        to_str<typename sig_traits::a6_t>(rname);
        to_str<typename sig_traits::a7_t>(rname);
        to_str<typename sig_traits::a8_t>(rname);
        to_str<typename sig_traits::a9_t>(rname);
        to_str<typename sig_traits::a10_t>(rname);
        to_str<typename sig_traits::a11_t>(rname);
        to_str<typename sig_traits::a12_t>(rname);
        cname = rname + "_";
    }
};

template <typename POUET>
struct static_ctor;

template <class C>
struct static_ctor<C*()> : public static_ctor_base<C*()> {
    using static_ctor_base<C*()>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*()>(class_name)
    {}
    static C* new_() { return new C(); }
};

template <class C, typename A1>
struct static_ctor<C*(A1)> : public static_ctor_base<C*(A1)> {
    using static_ctor_base<C*(A1)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1)>(class_name)
    {}
    static C* new_(A1 a1) { return new C(a1); }
};

template <class C, typename A1, typename A2>
struct static_ctor<C*(A1, A2)> : public static_ctor_base<C*(A1, A2)> {
    using static_ctor_base<C*(A1, A2)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2) { return new C(a1, a2); }
};

template <class C, typename A1, typename A2, typename A3>
struct static_ctor<C*(A1, A2, A3)> : public static_ctor_base<C*(A1, A2, A3)> {
    using static_ctor_base<C*(A1, A2, A3)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2, A3)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2, A3 a3) { return new C(a1, a2, a3); }
};

template <class C, typename A1, typename A2, typename A3, typename A4>
struct static_ctor<C*(A1, A2, A3, A4)>
    : public static_ctor_base<C*(A1, A2, A3, A4)>
{
    using static_ctor_base<C*(A1, A2, A3, A4)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2, A3, A4)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2, A3 a3, A4 a4) {
        return new C(a1, a2, a3, a4);
    }
};

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5>
struct static_ctor<C*(A1, A2, A3, A4, A5)>
    : public static_ctor_base<C*(A1, A2, A3, A4, A5)>
{
    using static_ctor_base<C*(A1, A2, A3, A4, A5)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2, A3, A4, A5)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
        return new C(a1, a2, a3, a4, a5);
    }
};

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6>
struct static_ctor<C*(A1, A2, A3, A4, A5, A6)>
    : public static_ctor_base<C*(A1, A2, A3, A4, A5, A6)>
{
    using static_ctor_base<C*(A1, A2, A3, A4, A5, A6)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2, A3, A4, A5, A6)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
        return new C(a1, a2, a3, a4, a5, a6);
    }
};

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7>
struct static_ctor<C*(A1, A2, A3, A4, A5, A6, A7)>
    : public static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7)>
{
    using static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
        return new C(a1, a2, a3, a4, a5, a6, a7);
    }
};

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8>
struct static_ctor<C*(A1, A2, A3, A4, A5, A6, A7, A8)>
    : public static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8)>
{
    using static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) {
        return new C(a1, a2, a3, a4, a5, a6, a7, a8);
    }
};

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9>
struct static_ctor<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9)>
    : public static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9)>
{
    using static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8,
                   A9 a9) {
        return new C(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
};

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9,
          typename A10>
struct static_ctor<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
    : public static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>
{
    using static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2, A3, A4, A5, A6,
                              A7, A8, A9, A10)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8,
                   A9 a9, A10 a10) {
        return new C(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    }
};

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9,
          typename A10, typename A11>
struct static_ctor<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>
    : public static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>
{
    using static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,
                              A11)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2, A3, A4, A5, A6,
                              A7, A8, A9, A10, A11)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8,
                   A9 a9, A10 a10, A11 a11) {
        return new C(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
    }
};

template <class C, typename A1, typename A2, typename A3, typename A4,
          typename A5, typename A6, typename A7, typename A8, typename A9,
          typename A10, typename A11, typename A12>
struct static_ctor<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>
    : public static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11,
                                 A12)>
{
    using static_ctor_base<C*(A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,
                              A11, A12)>::G;
    static_ctor(const char* class_name)
        : static_ctor_base<C*(A1, A2, A3, A4, A5, A6,
                              A7, A8, A9, A10, A11, A12)>(class_name)
    {}
    static C* new_(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8,
                   A9 a9, A10 a10, A11 a11, A12 a12) {
        return new C(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    }
};

}

#endif

