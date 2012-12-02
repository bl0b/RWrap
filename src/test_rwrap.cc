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


template <typename T>
struct cast;

template <>
struct cast<int> {
    static int _(SEXP v) {
        return 23;
    }
};

template <>
struct cast<const char*> {
    static const char* _(SEXP v) {
        return "coin";
    }
};

struct generic_cast {
    template <typename T>
        operator T() {
            return cast<T>::_(NULL);
        }
};





int main(int argc, char** argv) {
    Module m("toto");
    m.reg(totodouble).reg(totodouble2).reg(totovoid);
    m.reg(pouet::toto);

    generic_cast g;

    const char* totocast = g;
    int coincast = g;

    std::cout << totocast << ' ' << coincast << std::endl;

    return 0;
}
