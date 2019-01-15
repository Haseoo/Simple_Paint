/** \file basic_filter.cpp
 * \brief Plik z definicjami metod klasy basic_filter.
*/

#include "basic_filter.hpp"

void basic_filter::update_filter_information(Uint32 *window, std::size_t window_width, std::size_t window_height, std::size_t menu_height) {
    if (window)
        this->window_area = window;
    else
        throw paint_exception(paint_exception::BAD_WINDOW_PTR, "filter.");

    if (menu_height >= 40 && window_width >= 400 && window_height >= 200) {
        this->menu_height = menu_height;
        this->window_width = window_width;
        this->window_height = window_height;
    }
    else {
        throw paint_exception(paint_exception::BAD_WINDOW_DIM, "filter.");
    }
}

