#include "RWrap.h"
#include <boost/type_traits.hpp>
#include <boost/typeof/std/utility.hpp>

/*#include "test.h"*/

using namespace Rwrap;


double mul(double x, double y) {
    return x*y;
}




extern "C" {

void R_init_test_shlib(DllInfo* info) {
    Module m;
    m.reg(mul)
     .commit(info);
}
}
