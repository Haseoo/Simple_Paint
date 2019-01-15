/** \file sepia.cpp * \brief Plik z definicjami metod klasy sepia.*/#include "sepia.hpp"

sepia::sepia() {
    type = SEPIA;
}

void sepia::open_fiter_properties() {

}

void sepia::do_filter(){
    for(std::size_t j = menu_height; j < window_height; j++) {
        for(std::size_t i = 0; i < window_width; i++) {
            Uint8 in_B = (Uint8)(window_area[j * window_width + i]),
                  in_G = (Uint8)(window_area[j * window_width + i] >> 8),
                  in_R = (Uint8)(window_area[j * window_width + i] >> 16);

            unsigned int tmp_R = in_R * 0.393 + in_G * 0.769 + in_B * 0.189,
                         tmp_G = in_R * 0.349 + in_G * 0.686 + in_B * 0.168,
                         tmp_B = in_R * 0.272 + in_G * 0.534 + in_B * 0.131;

            Uint8 out_R = (tmp_R > 255) ? 255 : tmp_R,
                  out_G = (tmp_G > 255) ? 255 : tmp_G,
                  out_B = (tmp_B > 255) ? 255 : tmp_B;

            window_area[j * window_width + i] = (Uint32)(out_B) + (Uint32)(out_G << 8) + (Uint32)(out_R << 16);
        }
    }
}