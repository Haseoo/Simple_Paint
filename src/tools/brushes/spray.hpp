/** \file spray.hpp * \brief Plik z definicją klasy spray.*/#ifndef SPRAY_H
#define SPRAY_H

#include "brush.hpp"
#include <random>
#include <chrono>
/** \brief Klasa narzędzia sprej. */
class spray : public brush {
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        spray();
        /** \brief Metoda otwiera okno GTK, które pozwala ustawić wspólczynnik ilości generowanych pikseli.         * Nie przyjmuje argumentów wywołania i nie zwraca żadnej wartości.         *         */        void open_tool_properties();

    protected:
        /** \brief Przesłonięta metoda PaintPixel z klasy tool. Na podstawie współczynnika (w %) generowana jest ilość pikseli, których kolor zostanie zmieniony.         * Do generowania użyty jest generator rozkładu równomiernego.  Metoda nie zwraca żadnej wartości.         *         * \param[in] x_position std::size_t Składowa 'x' punktu.         * \param[in] y_position std::size_t Składowa 'y' punktu.         *         */        void PaintPixel(std::size_t x_position, std::size_t y_position);
    private:
        int dots_ratio = 15; /**< Wspólczynnik (w %) ilości pikseli, których kolor ma być zmieniony. Mnożony jest przez pole obszaru rysowania pędzla. */        std::default_random_engine generator; /**< Generator rozkładu równomiernego. */
        /** \brief Metoda obsługująca sygnał kliknięcia w przycisk zatwierdzający zmiany wprowadzone w oknie właściwości narzędzia.         * Metoda nie zwraca żadnej wartości.         *         * \param[out] widget GtkWidget* Wskaźnik na okno GTK, w którym generowany jest sygnał.         * \param[out] data gpointer Dodatkowe dane, w tym przypadku wskaźnik na flagę typu bool.         *         */        static void set_confirmed_flag(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <bool*>(data)) = !(*(reinterpret_cast <bool*>(data)));
        }
        /** \brief Metoda obsługująca sygnał zmiany wartości w przycisku ustawiania wartości. Nie zwraca żadnej wartości.         *         * \param[out] widget GtkWidget* Wskaźnik na okno, w którym wygenerowany został sygnał.         * \param[out] data gpointer Dodatkowe dane. W tym przypadku liczba naturalna.         *         */        static void value_changed(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <int*>(data)) = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
        }
};


#endif