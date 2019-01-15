/** \file ellipse.hpp
 * \brief Plik z definicją klasy ellipse.
*/

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.hpp"

/** \brief Klasa służąca do rysowania elipsy.
 */
class ellipse :public shape {
    public:
        /** \brief Konstruktor klasy, służy do ustawienia pola type;
         *
         */
        ellipse();

        /** \brief Metoda otwiera okno właściwości narzędzia. Pozwala ustawić flagę rysowania koła.
         *
         */
        void open_tool_properties();

    private:
        /** \brief Przesłonięta metoda PaintPixel z klasy tool. Rysuje kształt plusa o rozmiarze pędzla. Metoda nie zwraca żadnej wartości.
         *
         * \param[in] x_position std::size_t Składowa 'x' punktu.
         * \param[in] y_position std::size_t Składowa 'y' punktu.
         *
         */
        void PaintPixel(std::size_t x_position, std::size_t y_position);

        /** \brief Metoda rysuje prostokąt od punktu początkowego do wskazanego przez argumenty wywołania, wykorzystując metodę draw_shape klasy line.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param[in] x_position std::size_t Składowa 'x' punktu.
         * \param[in] y_position std::size_t Składowa 'y' punktu.
         *
         */
        void draw_shape(std::size_t x_position, std::size_t y_position);

        bool is_circle = false; /**< Flaga rysowania koła. */

        /** \brief Metoda obsługująca sygnał kliknięcia w przycisk oknie właściwości narzędzia. Ustawia flagę rysowania koła.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param[out] widget GtkWidget* Wskaźnik na okno GTK, w którym generowany jest sygnał.
         * \param[out] data gpointer Dodatkowe dane, w tym przypadku wskaźnik na flagę typu bool.
         *
         */
        static void set_cicle_flag(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <bool*>(data)) = !(*(reinterpret_cast <bool*>(data)));
        }
};

#endif
