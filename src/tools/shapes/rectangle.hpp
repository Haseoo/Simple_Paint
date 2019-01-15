/** \file rectangle.hpp * \brief Plik z definicją klasy rectangle.*/#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cmath>
#include "line.hpp"

/** \brief Klasa rysująca prostokąt. */class rectangle : public line {
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        rectangle();        /** \brief Metoda otwiera okno właściwości narzędzia. Pozwala ustawić flagę rysowania kwadratu.         *         */        void open_tool_properties();
    private:
        /** \brief Metoda rysuje prostokąt od punktu początkowego do wskazanego przez argumenty wywołania, wykorzystując metodę draw_shape klasy line.         * Metoda nie zwraca żadnej wartości.         *         * \param[in] x_position std::size_t Składowa 'x' punktu.         * \param[in] y_position std::size_t Składowa 'y' punktu.         *         */        void draw_shape(std::size_t x_position, std::size_t y_position);

        bool is_square = false; /**< Flaga rysowania kwadratu. */
        /** \brief Metoda obsługująca sygnał kliknięcia w przycisk oknie właściwości narzędzia. Ustawia flagę rysowania kwadratu.         * Metoda nie zwraca żadnej wartości.         *         * \param[out] widget GtkWidget* Wskaźnik na okno GTK, w którym generowany jest sygnał.         * \param[out] data gpointer Dodatkowe dane, w tym przypadku wskaźnik na flagę typu bool.         *         */
        static void set_square_flag(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <bool*>(data)) = !(*(reinterpret_cast <bool*>(data)));
        }
};

#endif