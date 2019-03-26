/** \file paint_exception.cpp
 * \brief Plik z definicjami metod klasy paint_exception.
*/

#include "paint_exception.hpp"

paint_exception::paint_exception(enum exception_type type) {
    if (type < number_of_exceptions)
        exception_string = exception_strings[type];
}

paint_exception::paint_exception(enum exception_type type, std::string additional_data) {
    if (type < number_of_exceptions)
        exception_string = exception_strings[type] + additional_data;
}

paint_exception::paint_exception(enum exception_type type, const char *additional_data) {
    if (type < number_of_exceptions)
        exception_string = exception_strings[type] + additional_data;
}


std::string paint_exception::what(){
    return exception_string;
}

const char* paint_exception::what() const noexcept {
    return exception_string.c_str();
}
paint_exception::~paint_exception() {
    //dtor
}
