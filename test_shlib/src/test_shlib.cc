#include "RWrap.h"
#include <boost/type_traits.hpp>
#include <boost/typeof/std/utility.hpp>

/*#include "test.h"*/

double mul(double x, double y) {
    return x*y;
}


MODULE(test_shlib)
    .reg(mul).auto_glue()
    ;




