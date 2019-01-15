/** \file color_inverse.hpp * \brief Plik z definicją klasy color_inverse.*/#ifndef COLOR_REVERSE_H
#define COLOR_REVERSE_H

#include "basic_filter.hpp"

/** \brief Klasa filtra odwracającego kolory obrazu. */class color_inverse : public basic_filter {
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        color_inverse();
        /** \brief Przesłonięta metoda otwierająca menu właściwości filtra. W przypadku tego filtra         * Metoda nie zwraca żadnej wartości.         *         */        void open_fiter_properties();
        /** \brief Metoda wyłuskuje składowe kolorów wszystkich pikseli obszaru roboczego, odejmuje od nich liczbę 255 i zapisuje nowe wartości.         * Metoda nie zwraca żadnej wartości.         *         */        void do_filter();
};

#endif