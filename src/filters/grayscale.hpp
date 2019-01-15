/** \file grayscale.hpp * \brief Plik z definicją klasy grayscale.*/#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "basic_filter.hpp"

/** \brief Klasa flitra zmieniająca obraz na czarno-biały. */class grayscale : public basic_filter {
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        grayscale();        /** \brief Przesłonięta metoda otwierająca menu właściwości filtra. W przypadku tego filtra         * Metoda nie zwraca żadnej wartości.         *         */
        void open_fiter_properties();        /** \brief Metoda wyłuskuje składowe kolorów wszystkich pikseli obszaru roboczego, oblicza średnią tych wartości i zapisuje tę wartość w każej składowej.         * Metoda nie zwraca żadnej wartości.         *         */
        void do_filter();
};

#endif