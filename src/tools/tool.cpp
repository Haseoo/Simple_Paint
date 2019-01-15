/** \file tool.cpp
 * \brief Plik z definicjami metod klasy tool.
*/

#include "tool.hpp"

void tool::use_tool(std::size_t x_position, std::size_t y_position) {
}



void tool::open_tool_properties() {

}




bool tool::is_a_brush() {
    return false;
}

enum tool_type tool::get_tool_type() {
    return type;
}

void tool::update_window_information(Uint32 *window, std::size_t window_width, std::size_t window_height,
                                     std::size_t menu_height) {

    if (window)
        this->window_area = window;
    else
        throw paint_exception(paint_exception::BAD_WINDOW_PTR, "tool.");

    if (menu_height >= 40 && window_width >= 400 && window_height >= 200) {
        this->menu_height = menu_height;
        this->window_width = window_width;
        this->window_height = window_height;
    }
    else {
        throw paint_exception(paint_exception::BAD_WINDOW_DIM, "tool.");
    }
}

 bool tool::resize_tool_size(int difference) {
    if ((difference < 0 && brush_size > 5) || (difference > 0 && brush_size < 35))
        brush_size += difference;
    else
        return false;

    if (brush_size < 5 || brush_size > 36) {
        brush_size = (brush_size < 5) ? 5 : 35;
    }
    return true;

 }

 void tool::update_current_color(Uint32 new_color) {
     this->current_color = new_color;
 }

 Uint32 tool::get_current_color() {
     return current_color;
}

std::size_t tool::get_brush_size() {
    return brush_size;
}


void tool::PaintPixel(std::size_t x_position, std::size_t y_position) {
    x_position = x_position - brush_size / 2;
    y_position = (y_position - brush_size / 2 > 0) ? y_position - brush_size / 2 : 0;
    std::size_t x_end = brush_size + (int)x_position;
    x_position = ((int)x_position < 0) ? 0 : x_position;

    for(std::size_t i = x_position; i < x_end; i++) {
        for(std::size_t j = y_position; j <= y_position + brush_size; j++) {
            if (i < window_width && j < window_height && j >= menu_height) {
                window_area[j * window_width + i] = current_color;
            }
        }
    }
}



tool::~tool() {
}
