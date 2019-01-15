/** \file line.hpp * \brief Plik z definicją klasy line.*/#ifndef LINE_H
#define LINE_H

#include "shape.hpp"

/** \brief Klasa służąca do rysowania prostej linii. */class line : public shape {
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        line();
    protected:        /** \brief Metoda rysuje linię od punktu początkowego do wskazanego przez argumenty wywołania. Metoda nie zwraca żadnej wartości.         *         * \param[in] x_position std::size_t Składowa 'x' punktu.         * \param[in] y_position std::size_t Składowa 'y' punktu.         *         */
        void draw_shape(std::size_t x_position, std::size_t y_position);
};


#endif