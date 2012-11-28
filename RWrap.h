#ifndef _RWRAP_H_
#define _RWRAP_H_

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#include <iostream>

#include <vector>

#include "Value.h"
#include "FuncTraits.h"
#include "gen_wrap.h"

namespace Rwrap {



template <typename T> struct is_void { enum { value=true }; };
template <> struct is_void<void> { enum { value=false }; };



template <typename F>
struct reg_helper {
    typedef FuncTraits<F> T;
    typedef gen<T> G;
};

#define _FT(_func) boost::add_pointer<BOOST_TYPEOF(_func) >::type
#define reg(_func) _reg(#_func, reg_helper<_FT(_func)>::T::ArgCount, (DL_FUNC) reg_helper<_FT(_func)>::G::_w<_func>::_)


class Module {
    std::vector<R_CallMethodDef> routines_;

public:
    Module()
        :  routines_()
    {}

    Module& _reg(const char* name, int argc, DL_FUNC wrapper) {
        Rprintf("Registering new routine :\n");
        Rprintf("   - name: %s\n", name);
        Rprintf("   - argc: %i\n", argc);
        Rprintf("   - wrap: %p\n", wrapper);
        routines_.push_back(*(R_CallMethodDef[]){{name, wrapper, argc}});
        return *this;
    }

    void commit(DllInfo* info) {
        routines_.push_back(*(R_CallMethodDef[]){{NULL, NULL, 0}});
        R_registerRoutines(info, NULL, &routines_[0], NULL, NULL);
    }
};

}

#endif
