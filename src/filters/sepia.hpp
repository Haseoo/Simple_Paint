/** \file sepia.hpp * \brief Plik z definicją klasy sepia.*/#ifndef SEPIA_H
#define SEPIA_H

#include "basic_filter.hpp"

/** \brief Klasa filtra sepia. */class sepia : public basic_filter {
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        sepia();        /** \brief Przesłonięta metoda otwierająca menu właściwości filtra. W przypadku tego filtra         * Metoda nie zwraca żadnej wartości.         *         */
        void open_fiter_properties();        /** \brief Metoda wyłuskuje składowe kolorów wszystkich pikseli obszaru roboczego, mnoży wartości przez odpowiedni licznik i zapisuje nową wartość.         * Metoda nie zwraca żadnej wartości.         *         */
        void do_filter();
};

#endif