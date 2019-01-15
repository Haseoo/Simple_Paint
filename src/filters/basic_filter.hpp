/** \file basic_filter.hpp * \brief Plik z definicją klasy base_filter oraz typu wyliczeniowego filter_type.*/#ifndef BASIC_FITLER_H
#define BASIC_FITLER_H

#include "../base_window.hpp"
#include <gtk/gtk.h>

/** \brief Typ wyliczeniowy określający jaki filter został zabrany. */enum filter_type {GRAYSCALE,      /**< Skala szarości. */                  SEPIA,          /**< Sepia. */                  COLOR_INVERSE,  /**< Odwracanie koloru. */                  PIXELATE,       /**< Pikselizacja obrazu. */                  NONE_FILTER = -1/**< Nie wybrano żadnego filtra */                  };

/** \brief Klasa stanowiąca bazę dla klas realizujących filtry. */class basic_filter : public base_window
{
    public:
        /** \brief Metoda przekazuje do obiektu filtra informacje na temat okna programu. Metoda nie zwraca żadnej wartości.         *         * \param[in] window Uint32* Wskaźnik na tablicę pikseli okna programu.         * \param[in] window_width std::size_t Szerokość okna.         * \param[in] window_height std::size_t Wysokość okna.         * \param[in] menu_height std::size_t Wysokość menu okna.         *         */        void update_filter_information(Uint32 *window, std::size_t window_width, std::size_t window_height, std::size_t menu_height);
        /** \brief Metoda otwiera okno GTK, które pozwala ustawić parametry filtra. Metoda nie zwraca żadnej wartości.         *         */        virtual void open_fiter_properties() = 0;
        /** \brief Metoda wykonująca filter. Nie zwraca żadnej wartości.         *         */        virtual void do_filter() = 0;

    protected:
        enum filter_type type; /**< Rodzaj filtra. */        /** \brief Funkcja obsługująca sygnał usunięcia okna GTK.         *         * \param widget GtkWidget* Wskaźnik na okno z którego pochodził sygnał.         * \param event GdkEvent* Zdarzenie.         * \param data gpointer Dane dla funkcji.         * \return gboolean Funkcja zwraca wartość TRUE.         *         */
        static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
            return FALSE;
        }
        /** \brief Funkcja obsługująca sygnał zamknięcia okna, nie zwraca żadnej wartości.         *         * \param widget GtkWidget* Wskaźnik na okno z którego pochodził sygnał.         * \param data gpointer Dane dla funkcji.         *         */
        static void destroy(GtkWidget *widget, gpointer data) {
            gtk_main_quit();
        }
};

#endif