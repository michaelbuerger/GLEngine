#include "CPPML/Loading.hpp"
#include "CPPML/Log.hpp"

#include <stdio.h>

namespace CPPML {

FILE* OpenFile(const char* address) {
    FILE* file = fopen(address, "r"); // tries to open file at address and creates buffer (heap allocated)

    if(file == nullptr) {
        CPPML_ERROR("Could not open file at \"{}\".", address);
    } else {
        CPPML_TRACE("Successfully opened file at \"{}\".", address);
    }

    return file;
}

}