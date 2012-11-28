#include "RWrap.h"
#include <boost/type_traits.hpp>
#include <boost/typeof/std/utility.hpp>

/*#include "test.h"*/

using namespace Rwrap;

extern "C" {
void totovoid() {
}

int totoint() {
}

double totodouble(int x, int y, double z) {
    return 0;
}

double totodouble2(int x, int y, double z) {
    return 0;
}
}

struct pouet {
    static void toto() {};
};


int main(int argc, char** argv) {
    Module m("toto");
    m.reg(totodouble).reg(totodouble2).reg(totovoid);
    m.reg(pouet::toto);

    return 0;
}
