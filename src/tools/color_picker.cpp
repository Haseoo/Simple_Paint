/** \file color_picker.cpp
 * \brief Plik z definicjami metod klasy color_picker.
 * \bug Użycie color pickera jest traktowane jako operacja "możliwa" do cofnięcia. 
 * Nie powoduje to większych problemów, poza tym, że nie da się wycofać poprzedzającej użycie narzędzia operacji.
*/

#include "color_picker.hpp"

color_picker::color_picker() {
    type = COLOR_PICKER;
}

void color_picker::use_tool(std::size_t x_position, std::size_t y_position) {
    if(y_position >= menu_height) {
        current_color = window_area[y_position * window_width + x_position];
    }
    pressed_left_button = false;
}

 bool color_picker::isBrush() {
     return false;
 }
