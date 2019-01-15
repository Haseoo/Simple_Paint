/** \file pixelate.hpp
#define PIXELATE_H

#include <cmath>
#include "basic_filter.hpp"

/** \brief Klasa filtra pikselizujacego obraz.
{
    public:
        pixelate();
        /** \brief Metoda otwiera okno GTK, w którym można ustawić rozmar komórki(wielkość "piksela" wyjściowego).
        void do_filter();

    private:
        std::size_t cell_size = 1; /**< Rozmiar wyjściowego ""piksela"/ */

        static void set_confirmed_flag(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <bool*>(data)) = !(*(reinterpret_cast <bool*>(data)));
        }
        static void value_changed(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <int*>(data)) = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
        }
};


#endif