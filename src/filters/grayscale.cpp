/** \file grayscale.cpp * \brief Plik z definicjami metod klasy grayscale.*/#include "grayscale.hpp"

grayscale::grayscale() {
    type = GRAYSCALE;
}

void grayscale::open_fiter_properties() {

}

void grayscale::do_filter() {
    for(std::size_t j = menu_height; j < window_height; j++) {
        for(std::size_t i = 0; i < window_width; i++) {
            Uint8 B = (Uint8)(window_area[j * window_width + i]),
                  G = (Uint8)(window_area[j * window_width + i] >> 8),
                  R = (Uint8)(window_area[j * window_width + i] >> 16),
                  O = (R + G + B) / 3;

            window_area[j * window_width + i] = (Uint32)(O) + (Uint32)(O << 8) + (Uint32)(O << 16);
        }
    }

}

