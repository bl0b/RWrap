#include <RWrap/RWrap.h>

double mul(double x, double y) {
    return x*y;
}


MODULE(testshlib)
    .reg(mul).auto_glue()
    ;

