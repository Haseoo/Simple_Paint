/** \file shape.cpp
 * \brief Plik z definicjami metod klasy shape.
*/

#include "shape.hpp"

bool shape::is_brush() {
    return false;
}

void shape::use_tool(std::size_t x_position, std::size_t y_position) {
    if (!pressed_left_button) {
        x_begining = x_position;
        y_begining = y_position;
        try {
            copied_pixels = new Uint32[window_width * (window_height - menu_height)];
        }
        catch (std::bad_alloc &exception) {

            throw paint_exception(paint_exception::SHAPE_BAD_ALLOC, exception.what()) ;
        }

        memcpy(copied_pixels, window_area + (menu_height * window_width),
                       sizeof(Uint32) * window_width * (window_height - menu_height));
        pressed_left_button = true;
    }
    else if (pressed_left_button && !pressed_left_button_second_time) {
        memcpy(window_area + (menu_height * window_width), copied_pixels,
                       sizeof(Uint32) * window_width * (window_height - menu_height));
        draw_shape(x_position, y_position);
    }
    else if (pressed_left_button_second_time) {
        draw_shape(x_position, y_position);
        pressed_left_button = false;
        pressed_left_button_second_time = false;
        delete[] copied_pixels;
    }
}

void shape::draw_shape(std::size_t x_position, std::size_t y_position) {

}
