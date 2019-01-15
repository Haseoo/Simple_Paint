/** \file flood_fill.hpp * \brief Plik z definicją klasy flood_fill.*/#ifndef FLOOD_FILL_H
#define FLOOD_FILL_H

#include "tool.hpp"

/** \brief Klasa służacą do wypełniania obszaru kolorem. */class flood_fill : public tool
{
    public:        /** \brief Konstruktor klasy, służy do ustawienia pola type;         *         */
        flood_fill();         /** \brief Przesłonięta metoda z klasy tool. Wypełnia obszar (z uwzględnieniem tolerancji) od podanego punktu.         * Metoda nie zwraca żadnej wartości.         *         * \param[in] x_position std::size_t Składowa 'x' punktu.         * \param[in] y_position std::size_t Składowa 'y' punktu.         *         */
        void use_tool(std::size_t x_position, std::size_t y_position);
        /** \brief Metoda zwraca czy narzędzie jest pędzlem. Nie przyjmuje argumentów wywołania.         *         * \return bool W przypadku tego narzędzia metoda zwraca wartość false.         *         */        bool isBrush();        /** \brief Metoda otwiera okno GTK, które pozwala ustawić wspólczynnik tolerancji.         * Nie przyjmuje argumentów wywołania i nie zwraca żadnej wartości.         *         */
        void open_tool_properties();

    private:
        int tolerance_ratio = 0; /**< Współczynnik tolerancji (w %) */

        /** \brief Metoda oblicza na podstawie tolerancji czy kolor danego piksela powinien być zastąpiony nowym kolorem.         *         * \param[in] pointed_color Uint32 Kolor piksela,który został wskazany podczas rozpoczynania wypełnienia.         * \param[in] replace_color Uint32 Kolor piksela, dla którego ma być obliczone czy jego kolor ma zostać zastąpiony nowym.         * \return bool Jeśli różnica kolorów między pikselami będzie mniejsza niż wynikająca ze współczynnika tolerancji, metoda zwróci wartość false,         * w przeciwnym wypadku zwróci wartość true.         *         */        bool calculate_tolerance(Uint32 pointed_color, Uint32 replace_color);        /** \brief Metoda obsługująca sygnał kliknięcia w przycisk zatwierdzający zmiany wprowadzone w oknie właściwości narzędzia.         * Metoda nie zwraca żadnej wartości.         *         * \param[out] widget GtkWidget* Wskaźnik na okno GTK, w którym generowany jest sygnał.         * \param[out] data gpointer Dodatkowe dane, w tym przypadku wskaźnik na flagę typu bool.         *         */
        static void set_confirmed_flag(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <bool*>(data)) = !(*(reinterpret_cast <bool*>(data)));
        }        /** \brief Metoda obsługująca sygnał zmiany wartości w przycisku ustawiania wartości. Nie zwraca żadnej wartości.         *         * \param[out] widget GtkWidget* Wskaźnik na okno, w którym wygenerowany został sygnał.         * \param[out] data gpointer Dodatkowe dane. W tym przypadku liczba naturalna.         *         */
        static void value_changed(GtkWidget *widget, gpointer data) {
            *(reinterpret_cast <int*>(data)) = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
        }
};

#endif