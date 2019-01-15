/** \file color_picker.hpp * \brief Plik z definicją klasy color_picker.*/#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include "tool.hpp"

/** \brief Definicja klasy narzędzia pobierania koloru z obszaru rysowania. */class color_picker : public tool {
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        color_picker();
        /** \brief Metoda zapisuje w polu current_color kolor wskazanego piksela. Metoda nie zwraca żadnej wartości.         *         * \param[in] x_position std::size_t Składowa 'x' punktu.         * \param[in] y_position std::size_t Składowa 'y' punktu.         *         */        void use_tool(std::size_t x_position, std::size_t y_position);        /** \brief Metoda zwraca informację czy narzędzie jest pędzlem. Nie przyjmuje argumentów wywołania.         *         * \return bool Metoda zwraca wartość false w przypadku tej klasy.         *         */
        bool isBrush();
};

#endif