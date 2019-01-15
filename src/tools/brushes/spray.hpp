/** \file spray.hpp
#define SPRAY_H

#include "brush.hpp"
#include <random>
#include <chrono>
/** \brief Klasa narzędzia sprej.
class spray : public brush {
    public:
        spray();
        /** \brief Metoda otwiera okno GTK, które pozwala ustawić wspólczynnik ilości generowanych pikseli.

    protected:
        /** \brief Przesłonięta metoda PaintPixel z klasy tool. Na podstawie współczynnika (w %) generowana jest ilość pikseli, których kolor zostanie zmieniony.
    private:
        int dots_ratio = 15; /**< Wspólczynnik (w %) ilości pikseli, których kolor ma być zmieniony. Mnożony jest przez pole obszaru rysowania pędzla. */
        /** \brief Metoda obsługująca sygnał kliknięcia w przycisk zatwierdzający zmiany wprowadzone w oknie właściwości narzędzia.
            *(reinterpret_cast <bool*>(data)) = !(*(reinterpret_cast <bool*>(data)));
        }
        /** \brief Metoda obsługująca sygnał zmiany wartości w przycisku ustawiania wartości. Nie zwraca żadnej wartości.
            *(reinterpret_cast <int*>(data)) = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
        }
};


#endif