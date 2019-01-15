/** \file pixelate.hpp * \brief Plik z definicją klasy pixelate.*/#ifndef PIXELATE_H
#define PIXELATE_H

#include <cmath>
#include "basic_filter.hpp"

/** \brief Klasa filtra pikselizujacego obraz. */class pixelate : public basic_filter
{
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        pixelate();
        /** \brief Metoda otwiera okno GTK, w którym można ustawić rozmar komórki(wielkość "piksela" wyjściowego).         * Metoda nie zwraca żadnej wartości.         * \return void         */        void open_fiter_properties();        /** \brief Metoda dzieli obszar na kwadraty o boku równemu rozmiarowi komórki. Dla każego obszaru wylicza średnie wartości składowych koloru.         * Następnie ustawia ten kolor dla wszystkich pikseli w obszarze. Metoda nie zwraca żadnej wartości.         *         */
        void do_filter();

    private:
        std::size_t cell_size = 1; /**< Rozmiar wyjściowego ""piksela"/ */
        /** \brief Metoda obsługująca sygnał kliknięcia w przycisk zatwierdzający zmiany wprowadzone w oknie właściwości filtra.         * Metoda nie zwraca żadnej wartości.         *         * \param[out] widget GtkWidget* Wskaźnik na okno GTK, w którym generowany jest sygnał.         * \param[out] data gpointer Dodatkowe dane, w tym przypadku wskaźnik na flagę typu bool.         *         */
        static void set_confirmed_flag(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <bool*>(data)) = !(*(reinterpret_cast <bool*>(data)));
        }         /** \brief Metoda obsługująca sygnał zmiany wartości w przycisku ustawiania wartości. Nie zwraca żadnej wartości.         *         * \param[out] widget GtkWidget* Wskaźnik na okno, w którym wygenerowany został sygnał.         * \param[out] data gpointer Dodatkowe dane. W tym przypadku liczba naturalna.         *         */
        static void value_changed(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <int*>(data)) = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
        }
};


#endif