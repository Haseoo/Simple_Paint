/** \file color_inverse.cpp * \brief Plik z definicjami metod klasy color_inverse.*/#include "color_inverse.hpp"

color_inverse::color_inverse() {
    type = COLOR_INVERSE;
}

void color_inverse::open_fiter_properties() {

}

void color_inverse::do_filter() {
    for(std::size_t j = menu_height; j < window_height; j++) {
        for(std::size_t i = 0; i < window_width; i++) {
            Uint8 B = 255 - (Uint8)(window_area[j * window_width + i]),
                  G = 255 - (Uint8)(window_area[j * window_width + i] >> 8),
                  R = 255 - (Uint8)(window_area[j * window_width + i] >> 16);

            window_area[j * window_width + i] = (Uint32)(B) + (Uint32)(G << 8) + (Uint32)(R << 16);
        }
    }
}