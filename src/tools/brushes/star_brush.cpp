/** \file star_brush.cpp * \brief Plik z definicjami metod klasy star_brush.*/#include "star_brush.hpp"

star_brush::star_brush() {
    type = STAR_BRUSH;
}

void star_brush::PaintPixel(std::size_t x_position, std::size_t y_position) {
    x_position = x_position - brush_size / 2;
    y_position = (y_position - brush_size / 2 > 0) ? y_position - brush_size / 2 : 0;
    std::size_t x_end = brush_size + (int)x_position;
    x_position = ((int)x_position < 0) ? 0 : x_position;

    std::size_t thickness = (brush_size / 2) - 1;
    std::size_t free_space = (brush_size - thickness) / 2;

    for(std::size_t i = x_position + free_space; i <= x_position + free_space + thickness; i++) {
        for(std::size_t j = y_position; j <= y_position + brush_size; j++) {
            if (i < window_width && j < window_height && j >= menu_height) {
                window_area[j * window_width + i] = current_color;
            }
        }
    }

    for(std::size_t i = x_position; i < x_end; i++) {
        for(std::size_t j = y_position + free_space; j <= y_position + free_space + thickness; j++) {
            if (i < window_width && j < window_height && j >= menu_height) {
                window_area[j * window_width + i] = current_color;
            }
        }
    }
}

