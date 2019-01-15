/** \file rectangle.hpp
#define RECTANGLE_H

#include <cmath>
#include "line.hpp"

/** \brief Klasa rysująca prostokąt.
    public:
        rectangle();
    private:
        /** \brief Metoda rysuje prostokąt od punktu początkowego do wskazanego przez argumenty wywołania, wykorzystując metodę draw_shape klasy line.

        bool is_square = false; /**< Flaga rysowania kwadratu. */

        static void set_square_flag(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <bool*>(data)) = !(*(reinterpret_cast <bool*>(data)));
        }
};

#endif