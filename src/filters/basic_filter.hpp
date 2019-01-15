/** \file basic_filter.hpp
#define BASIC_FITLER_H

#include "../base_window.hpp"
#include <gtk/gtk.h>

/** \brief Typ wyliczeniowy określający jaki filter został zabrany.

/** \brief Klasa stanowiąca bazę dla klas realizujących filtry.
{
    public:
        /** \brief Metoda przekazuje do obiektu filtra informacje na temat okna programu. Metoda nie zwraca żadnej wartości.
        /** \brief Metoda otwiera okno GTK, które pozwala ustawić parametry filtra. Metoda nie zwraca żadnej wartości.
        /** \brief Metoda wykonująca filter. Nie zwraca żadnej wartości.

    protected:
        enum filter_type type; /**< Rodzaj filtra. */
        static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
            return FALSE;
        }

        static void destroy(GtkWidget *widget, gpointer data) {
            gtk_main_quit();
        }
};

#endif