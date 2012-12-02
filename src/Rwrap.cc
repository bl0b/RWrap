#include "RWrap.h"
#include <dlfcn.h>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Rwrap NAMESPACE and glue generator © 2012 Damien Leroux" << std::endl;
        std::cout << "Usage: " << argv[0] << " path/to/SHLIB.so" << std::endl;
        return -1;
    }
    void* handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        std::cerr << "Couldn't open shared object " << argv[1] << std::endl;
        return -1;
    }
    void (*gen)() = (void (*)()) dlsym(handle, "Rwrap_gen");
    if (!gen) {
        std::cerr << "Shared object doesn't seem to be an Rwrap'd SHLIB." << std::endl;
        return -1;
    }
    gen();
    return 0;
}

