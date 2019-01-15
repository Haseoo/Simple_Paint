/** \file brush.cpp * \brief Plik z definicjami metod klasy brush.*/#include "brush.hpp"

brush::brush() {
    type = BRUSH;
}

void brush::use_tool(std::size_t x_position, std::size_t y_position) {
    PaintPixel(x_position, y_position);
    pressed_left_button = true;
}


bool brush::is_a_brush() {
    return true;
}
