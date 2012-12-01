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

MODULE(testshlib)
    .reg(mul).auto_glue()
    .reg(isTrue).auto_glue()
    .reg(hazcheez).auto_glue()
    ;

