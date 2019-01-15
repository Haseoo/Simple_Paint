/** \file shape.hpp
 * \brief Plik z definicją klasy shape.
*/

#ifndef SHAPE_H
#define SHAPE_H

#include "../tool.hpp"

/** \brief Klasa bazowa dla klas rysujących figury geometryczne.
 */
class shape : public tool {
    public:
        /** \brief Metoda zwraca informację czy narzędzie jest pędzlem. Nie przyjmuje argumentów wywołania.
         *
         * \return bool Metoda zwraca wartość false w przypadku tej klasy.
         *
         */
        bool is_brush();

        /** \brief Metoda wykonuje akcję "ciągłego" rysowania kształtu. Może rzucić wyjątek typu paint_exception gdy dynamiczny przydział pamięci się nie powiedzie.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param[in] x_position std::size_t Składowa 'x' punktu.
         * \param[in] y_position std::size_t Składowa 'y' punktu.
         *
         */
        void use_tool(std::size_t x_position, std::size_t y_position);
    protected:
        std::size_t x_begining, /**< Składowa 'x' punktu rozpoczęcia rysowania kształtu. */
                    y_begining; /**< Składowa 'y' punktu rozpoczęcia rysowania kształtu. */
        Uint32 *copied_pixels; /**< Piksele skopiowane przed rozpoczęciem rysowania kształtu. */

        /** \brief Metoda rysuje figurę od punktu początkowego do wskazanego przez argumenty wywołania. Metoda nie zwraca żadnej wartości.
         *
         * \param[in] x_position std::size_t Składowa 'x' punktu.
         * \param[in] y_position std::size_t Składowa 'y' punktu.
         *
         */
        virtual void draw_shape(std::size_t x_position, std::size_t y_position);

};


#endif
