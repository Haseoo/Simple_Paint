/** \file star_brush.hpp * \brief Plik z definicją klasy star_brush.*/#ifndef STAR_BRUSH_H
#define STAR_BRUSH_H

#include "brush.hpp"
/** \brief Klasa narzędzia pędzla w kształcie plusa. */
class star_brush : public brush {
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        star_brush();
    protected:        /** \brief Przesłonięta metoda PaintPixel z klasy tool. Rysuje kształt plusa o rozmiarze pędzla. Metoda nie zwraca żadnej wartości.         *         * \param[in] x_position std::size_t Składowa 'x' punktu.         * \param[in] y_position std::size_t Składowa 'y' punktu.         *         */
        void PaintPixel(std::size_t x_position, std::size_t y_position);
};


#endif