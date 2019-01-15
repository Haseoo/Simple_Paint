/** \file brush.hpp * \brief Plik z definicją klasy brush.*/#ifndef BRUSH_H
#define BRUSH_H

#include "../tool.hpp"
#include <SDL2/SDL.h>
#include <iostream>

/** \brief Klasa narzędzia pędzel. */
class brush : public tool
{
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        brush();        /** \brief Metoda wykonuje akcję rysowania kwadratu (wywołanie metody paint_pixel) w podanym punkcie.         * Metoda nie zwraca żadnej wartości.         *         * \param[in] x_position std::size_t Składowa 'x' punktu.         * \param[in] y_position std::size_t Składowa 'y' punktu.         *         */
        virtual void use_tool(std::size_t x_position, std::size_t y_position);        /** \brief Metoda zwraca informację czy narzędzie jest pędzlem. Nie przyjmuje argumentów wywołania.         *         * \return bool Metoda zwraca true w przypadku tej klasy.         *         */
        bool is_a_brush();

};

#endif // BRUSH_H
