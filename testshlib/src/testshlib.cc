#include <RWrap/RWrap.h>

double mul(double x, double y) {
    return x*y;
}


bool isTrue(bool x) {
    return !!x;
}

MODULE(testshlib)
    .reg(mul).auto_glue()
    .reg(isTrue).auto_glue()
    ;

