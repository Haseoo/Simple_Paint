/** \file triangle.cpp
 * \brief Plik z definicją klasy triangle.
*/

#include "triangle.hpp"

triangle::triangle() {
    type = TRIAGNLE;
}

void triangle::draw_shape(std::size_t x_position, std::size_t y_position) {

    size_t x1 = 0, x2 = 0, y1 = 0, y2 = 0;

    if (abs((int)(x_position - x_begining)) < 4) {
        double h  = sqrt(pow((int)x_begining - (int)x_position, 2) + pow((int)y_begining - (int)y_position, 2)),
               d  = (h * sqrt(3)) / 3.0;

        std::size_t diff = round(d);

        x1 = x_position + diff,
        x2 = x_position - diff,
        y1 = y_position,
        y2 = y_position;

        x2 = ((int)y2 <= 0) ? 1 : x2;
    }
    else if (y_position == y_begining) {
        double h  = sqrt(pow((int)x_begining - (int)x_position, 2) + pow((int)y_begining - (int)y_position, 2)),
            d  = (h * sqrt(3)) / 3.0;

        std::size_t diff = round(d);

        x1 = x_position,
        x2 = x_position,
        y1 = y_position + diff,
        y2 = y_position - diff;

        y2 = ((int)y2 <= 0) ? 1 : y2;
    }
    else {
 
        double x_pos = x_position,
               y_pos = y_position;

        double a1= ((int)y_position - (int)y_begining) / (double)((int)x_position - (int)x_begining),
               a2 = -1 / a1, //a1 will never be equal 0 there
               b2 = y_pos - a2 * x_pos,
               h  = sqrt(pow(x_begining - x_pos, 2) + pow(y_begining - y_pos, 2)),
               d  = (h * sqrt(3)) / 3.0;

        x1 = round((sqrt(a2*a2*d*d - a2*a2*x_pos*x_pos - 2*a2*b2*x_pos + 2*a2*x_pos*y_pos - b2*b2 + 2*b2*y_pos + d*d - y_pos * y_pos) - a2*b2 + a2*y_pos + x_pos) / (a2*a2 + 1));
        x1 = ((int)x1 <= 0) ? 1 : x1;
        y1 = round(a2 * (double)x1 + b2);
        y1 = ((int)y1 <= 0) ? 1 : y1;

        x2 = round((-sqrt(a2*a2*d*d - a2*a2*x_pos*x_pos - 2*a2*b2*x_pos + 2*a2*x_pos*y_pos - b2*b2 + 2*b2*y_pos + d*d - y_pos * y_pos) - a2*b2 + a2*y_pos + x_pos) / (a2*a2 + 1));
        x2 = ((int)x2 <= 0) ? 1 : x2;
        y2 = round(a2 * (double)x2 + b2);
        y2 = ((int)y2 <= 0) ? 1 : y2;
    }

    line::draw_shape(x1, y1);
    line::draw_shape(x2, y2);

    std::size_t tmp_x = x_begining,
                tmp_y = y_begining;

    x_begining = x1;
    y_begining = y1;

    line::draw_shape(x2, y2);

    x_begining = tmp_x;
    y_begining = tmp_y; 
}