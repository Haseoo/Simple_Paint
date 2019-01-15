/** \file flood_fill.hpp
#define FLOOD_FILL_H

#include "tool.hpp"

/** \brief Klasa służacą do wypełniania obszaru kolorem.
{
    public:
        flood_fill();
        void use_tool(std::size_t x_position, std::size_t y_position);
        /** \brief Metoda zwraca czy narzędzie jest pędzlem. Nie przyjmuje argumentów wywołania.
        void open_tool_properties();

    private:
        int tolerance_ratio = 0; /**< Współczynnik tolerancji (w %) */

        /** \brief Metoda oblicza na podstawie tolerancji czy kolor danego piksela powinien być zastąpiony nowym kolorem.
        static void set_confirmed_flag(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <bool*>(data)) = !(*(reinterpret_cast <bool*>(data)));
        }
        static void value_changed(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <int*>(data)) = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
        }
};

#endif