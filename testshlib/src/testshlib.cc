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

#include <RWrap/RWrap.h>
#include <typeinfo>

bool testlgl(bool x) { return !x; }
int testint(int x) { return -x; }
double testdouble(double x) { return -x; }

#define REV(name, _type_) \
    _type_ test##name(_type_ x) { return _type_(x.rbegin(), x.rend()); }

REV(string, std::string);
REV(veci, std::vector<int>);
REV(vecd, std::vector<double>);
REV(vecb, std::vector<bool>);
REV(vecs, std::vector<std::string>);
REV(vecs2, std::vector<const char*>);

double mul(double x, double y) {
    return x*y;
}


bool isTrue(bool x) {
    return !!x;
}

std::vector<int> hazcheez() {
    std::vector<int> ret;
    ret.push_back(23);
    ret.push_back(42);
    return ret;
}

std::vector<int> sqr(std::vector<int> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << ' ';
        vec[i] *= vec[i];
        std::cout << vec[i] << std::endl;
    }
    return vec;
}

Rwrap::List mydf() {
    Rwrap::List ret;
    std::vector<int> a, b;
    a.push_back(1);
    a.push_back(3);
    a.push_back(5);
    b.push_back(10);
    b.push_back(20);
    b.push_back(30);
    ret.add("a", a);
    ret.add("b", b);
    return ret;
}

int mylist(Rwrap::List l) {
    const char* coin = l["str"];
    int plop = l["int"];
    return 42 + 100 * plop;
}

double mul10(double ten, double y) {
    return ten * y;
}

std::vector<const char*> cvec() {
    std::vector<const char*> ret;
    ret.push_back("toto");
    ret.push_back("plop");
    ret.push_back("coin");
    return ret;
}

void testvoid(const char* x) {
    std::cout << x << std::endl;
}


Rwrap::DataFrame testdf() {
    std::vector<int> a;
    std::vector<const char*> b;
    std::vector<double> c;

    a.push_back(10);
    a.push_back(11);
    a.push_back(12);

    b.push_back("pouet");
    b.push_back("plop");
    b.push_back("coin");

    c.push_back(23.0);
    c.push_back(42.0);
    c.push_back(61.06);

    Rwrap::DataFrame ret;
    ret.add("hop", a);
    ret.add("zoup", b);
    ret.add("flourp", c);
    return ret;
}


std::vector<int> getColi(Rwrap::List df, int i) {
    return df[i];
}

std::vector<const char*> getCols(Rwrap::List df, int i) {
    return df[i];
}

struct toto {
    int test(double z) { return 0; }
};

typedef Rwrap::FuncTraits<BOOST_TYPEOF(&toto::test)> hop;

class pouet {
    public:
        int hop;
        pouet() : hop(42) {}
        void toto() {
            std::cout << "Called toto " << hop << std::endl;
        }
};

pouet* new_pouet() {
    return new pouet();
}

void delete_pouet(pouet* p) {
    delete p;
}




/*Rwrap::Class c = Rwrap::Class("pouet")*/
CLASS(pouet)
    .reg_meth(pouet, toto).auto_glue()
    ;

void modify_pouet(pouet* p) {
    p->hop = 23;
}

#if 0
struct pouet_name { static const char* name; };
const char* pouet_name::name = "pouet";
namespace Rwrap {
    template<> struct Value<pouet*> : public ClassWrap<pouet, pouet_name> {};
    {
        typedef pouet* CType;
        static CType coerceToC(SEXP v) {
            if (isObject(v)) {
                /* get('this.ptr', slot(x, '.xData')) */
                SEXP slot = lang3(install("slot"), v, mkString(".xData"));
                SEXP get = lang3(install("get"), mkString("this.ptr"), slot);
                return (CType) Value<void*>::coerceToC(eval(get, R_GlobalEnv));
            } else {
                return (CType) Value<void*>::coerceToC(v);
            }
        }
        static SEXP coerceToR(CType v) {
            SEXP n = lang3(R_DollarSymbol, install("pouet"), install("new"));
            SEXP call = lang2(n, Value<void*>::coerceToR(v));
            SET_TAG(CADR(call), install("this.ptr"));
            return eval(call, R_GlobalEnv);
            /* pouet$new(this.ptr=<ptr>) */
        }
    };
}
#endif

MODULE(testshlib)
    .reg(new_pouet).auto_glue()
    .reg(delete_pouet).arg("p").auto_glue()
    .reg(modify_pouet).arg("p").auto_glue()
    /*.reg_meth(pouet, toto).auto_glue()*/
    /*._reg("pouet.toto", 1, (DL_FUNC) Rwrap::gen_meth<pouet, Rwrap::FuncTraits<BOOST_TYPEOF(&pouet::toto)> >::_w<&pouet::toto>::_).arg("this.ptr").auto_glue()*/
    /*.reg_meth(pouet, toto).auto_glue()*/
    .add_class(pouet)
    .reg(getColi).arg("df").arg("i").auto_glue()
    .reg(getCols).arg("df").arg("i").auto_glue()
    .reg(testdf).auto_glue()
    .reg(testvoid).auto_glue()
    .reg(testlgl).arg("x").auto_glue()
    .reg(testint).arg("x").auto_glue()
    .reg(testdouble).arg("x").auto_glue()
    .reg(teststring).arg("x").auto_glue()
    .reg(testveci).arg("x").auto_glue()
    .reg(testvecd).arg("x").auto_glue()
    .reg(testvecb).arg("x").auto_glue()
    .reg(testvecs).arg("x").auto_glue()
    .reg(testvecs2).arg("x").auto_glue()
    .reg(mul).arg("x").arg("y", "50").auto_glue()
    .reg(isTrue).arg("plop").auto_glue()
    .reg(hazcheez).auto_glue()
    .reg(mydf).wrap_result("as.data.frame(", ")").auto_glue()
    .reg(sqr).arg("vec").auto_glue()
    .reg(mylist).arg("l").auto_glue()
    .reg(mul10).implicit_arg("10").arg("y").auto_glue()
    .reg(cvec).auto_glue()
    ;

#define __(_x_) #_x_
#define ___(_x_) __(_x_)


int main() {
    std::cout << ___(BOOST_TYPEOF(&toto::test)) << std::endl;
    std::cout << typeid(BOOST_TYPEOF(&toto::test)).name() << std::endl;
}
