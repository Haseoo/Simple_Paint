/** \file line.cpp
 * \brief Plik z definicjami metod klasy line.
*/

#include "line.hpp"

line::line() {
    type = LINE;
}

void line::draw_shape(std::size_t x_position, std::size_t y_position) {
    int delta_x = abs((int)(x_begining - x_position));
	int delta_y = -abs((int)(y_begining - y_position));
	int start_x = x_begining > x_position ? 1 : -1;
	int start_y = y_begining > y_position ? 1 : -1;
	int delta_error = delta_x + delta_y;
	bool end = false;

	while (!end) {
		PaintPixel(x_position, y_position);
		if (x_begining == x_position && y_begining == y_position) {
			end = true;
		}
		int e2 = 2 * delta_error;
		if (e2 >= delta_y) {
			delta_error += delta_y;
			x_position += start_x;
		}
		if (e2 <= delta_x) {
			delta_error += delta_x;
			y_position += start_y;
		}
	}
}
