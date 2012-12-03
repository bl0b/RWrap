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
