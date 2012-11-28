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
}

struct pouet {
    static void toto() {};
};


template <typename Function> struct _sig {};
template <typename R>
struct _sig<R (*) ()> {
};


/*typedef boost::function_traits<totodouble> ft;*/
    /*std::cout << #_func << " " << FuncTraits<_func>::ArgCount << std::endl; \*/
    /*std::cout << #_func << " " << boost::function_traits<boost::add_pointer<BOOST_TYPEOF(_func) >::type>::arity << std::endl; \*/

#define REG(_func) do { \
    typedef boost::add_pointer<BOOST_TYPEOF(_func) >::type F; \
    typedef FuncTraits<F> T; \
    typedef gen<T> G; \
    std::cout << #_func << " " << T::ArgCount << std::endl; \
    std::cout << ((void*) G::_w<_func>::_) << std::endl; \
} while(0)



#define R2(_func) do { \
    std::cout << #_func << " " << reg<boost::add_pointer<BOOST_TYPEOF(_func) >::type>::T::ArgCount << std::endl; \
    std::cout << ((void*) reg<boost::add_pointer<BOOST_TYPEOF(_func) >::type>::G::_w<_func>::_) << std::endl; \
} while(0)

int main(int argc, char** argv) {
    Module m("toto");
    m.reg(totodouble).reg(totovoid);
    /*boost::function_traits< BOOST_TYPEOF(totovoid) > f;*/
    /*REG(totodouble);*/
    /*REG(totovoid);*/
    /*R2(totodouble);*/
    /*R2(totodouble);*/
    /*R2(totovoid);*/
    /*R2(totovoid);*/
    /*m.reg<totovoid>("totovoid");*/
    /*REG(pouet::toto);*/
    /*m.reg("totovoid", &totovoid);*/
    /*m.reg("totoint", &totoint);*/
    /*m.reg<pouet::toto>("toto");*/
    /*m.reg("toto", &pouet::toto);*/
    /*m.reg<totodouble>("totodouble");*/
    /*m._<double, int, int, double, totodouble>("totodouble");*/
    /*m.__<totodouble>("totodouble");*/

    return 0;
}
