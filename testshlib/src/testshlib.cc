#include <RWrap/RWrap.h>

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

MODULE(testshlib)
    .reg(mul).arg("x").arg("y", "50").auto_glue()
    .reg(isTrue).arg("plop").auto_glue()
    .reg(hazcheez).auto_glue()
    .reg(mydf).wrap_result("as.data.frame(", ")").auto_glue()
    .reg(sqr).arg("vec").auto_glue()
    ;

