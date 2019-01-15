/** \file triangle.hpp
 * \brief Plik z definicją metod klasy triangle.
*/

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <cmath>
#include "line.hpp"

/** \brief Klasa rysująca trójkąt równoboczny.
 */
class triangle : public line {
    public:
        /** \brief Konstruktor klasy, służy do ustawienia pola type;
         *
         */
        triangle();


    private:
        /** \brief Metoda rysuje trójkąt równoboczny od punktu początkowego do wskazanego przez argumenty wywołania, wykorzystując metodę draw_shape klasy line.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param[in] x_position std::size_t Składowa 'x' punktu.
         * \param[in] y_position std::size_t Składowa 'y' punktu.
         *
         * \bug Trójkąt "traci" równoboczność przy prawej krawędzi okna.
         * \bug Błąd przy rysowaniu koła kiedy x_position =~ x_begining.
         */
        void draw_shape(std::size_t x_position, std::size_t y_position);
};


#endif