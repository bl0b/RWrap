#include <RWrap/RWrap.h>

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


/*SEXP testdf() {*/
Rwrap::DataFrame testdf() {
    std::vector<int> a;
    std::vector<const char*> b;
    std::vector<double> c;
    /*Rwrap::List ret;*/
    Rwrap::DataFrame ret;
    a.push_back(10);
    a.push_back(11);
    a.push_back(12);
    b.push_back("pouet");
    b.push_back("plop");
    b.push_back("coin");
    c.push_back(23.0);
    c.push_back(42.0);
    c.push_back(61.06);
    ret.add("hop", a);
    ret.add("zoup", b);
    ret.add("flourp", c);
    return ret;
    /*SEXP expr;*/
    /*PROTECT(expr = allocList(2));*/
    /*SET_TYPEOF(expr, LANGSXP);*/
    /*SETCAR(expr, install("as.data.frame"));*/
    /*SETCADR(expr, ret.toR());*/
    /*UNPROTECT(1);*/
    /*return eval(expr, R_GlobalEnv);*/
    /*return expr;*/
}


std::vector<int> getCol(Rwrap::List df, int i) {
    return df[i];
}


MODULE(testshlib)
    .reg(getCol).arg("df").arg("i").auto_glue()
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

