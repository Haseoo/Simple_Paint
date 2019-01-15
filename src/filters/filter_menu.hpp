/** \file filter_menu.hpp
 * \brief Plik definicję klasy filter_menu.
 */

#ifndef FILTER_MENU_H
#define FILTER_MENU_H

#include "../gtk_base_window.hpp"
#include "basic_filter.hpp"
#include <deque>


/** \brief Struktura przechowująca dane o wybranym filtrze.
 * Umożliwia korzystanie z prostych sygnałów GTK bez użycia zmiennych globalnych.
 */
struct filter_type_data {
    enum filter_type type;      /**< Typ narzędzia. */
    enum filter_type *response; /**< Wskaźnik na zmienną przechowującą wybór użytkownika. */
};

/** \brief Klasa menu do wyboru filtrów.
 */
class filter_menu : public gtk_base_window
{
    public:
        /** \brief Konstruktor klasy. Odczytuje informacje z pliku zasobów. Może "rzucić" wyjątek typu  paint_exception w przypadku błędu.
         *
         */
        filter_menu();

        /** \brief Metoda zawiera inicjuje menu filtrów oraz zawiera pętlę main GTK. Metoda nie przyjmuje żadnych argumentów wywołania.
         * Metoda może "rzucić" wyjątek typu paint_exception gdy operacja inicjacji menu się nie powiedzie.
         *
         * \return bool Funkcja zwraca wartość true jeśli nie wystąpił w niej krytyczny błąd.
         *
         */
        bool open_gtk_window();

        /** \brief Getter wybranego w menu rodzaju filtru.
         *
         *\return enum filter_type wybrany rodzaj filtru.
         */
        enum filter_type get_filter_response();

    private:
        std::size_t number_of_filters;                     /**< Liczba filtrów programu. */
        std::deque <struct filter_type_data> filter_types; /**< Kolejka, która ułatwia działanie GTK. */
        enum filter_type filter_response;                  /**< Filter wybrany przez użytkownika. */

        /** \brief Funkcja obsługująca sygnał kliknięcia na przycisk z wyborem filtra.
         * Funkcja nie zwraca żadnej wartości.
         *
         * \param[out] widget GtkWidget* Wskaźnik na okno z którego pochodził sygnał.
         * \param[out] data gpointer Dane dla funkcji.
         *
         */
        static void get_filter_type(GtkWidget *widget, gpointer data) {
            *((reinterpret_cast <struct filter_type_data*>(data))->response) = (reinterpret_cast <struct filter_type_data*>(data))->type;
        }

};


#endif
