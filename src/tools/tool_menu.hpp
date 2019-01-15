/** \file tool_menu.hpp
 * \brief Plik z definicją klasy tool_menu.
*/

#ifndef TOOL_MENU_H
#define TOOL_MENU_H

#include <SDL2/SDL.h>
#include <deque>
#include "tool.hpp"
#include "../gtk_base_window.hpp"

/** \brief Struktura przechowująca dane o wybranym narzędziu.
 * Umożliwia korzystanie z prostych sygnałów GTK bez użycia zmiennych globalnych.
 */
struct tool_type_data {
    enum tool_type type;      /**< Typ narzędzia. */
    enum tool_type *response; /**< Wskaźnik zmienną przechowującą wybór użytkownika. */
};

/** \brief Klasa związana z wyświetlaniem menu wyboru narzędzi.
 */
class tool_menu : public gtk_base_window
{
    public:
        /** \brief Konstruktor klasy. Wczytuje z pliku zasoby dla tego menu z plików.
         * Może "rzucić" wyjątek typu paint_exception kiedy nie powiedzie się odczytanie tych zasobów.
         *
         */
        tool_menu();


        /** \brief Metoda zawiera inicjuje menu narzędzi oraz zawiera pętlę main GTK. Metoda nie przyjmuje żadnych argumentów wywołania.
         * Metoda może "rzucić" wyjątek typu paint_exception gdy operacja inicjacji menu się nie powiedzie.
         *
         * \return bool Funkcja zwraca wartość true jeśli nie wystąpił w niej krytyczny błąd.
         *
         */
        bool open_gtk_window();

        /** \brief Metoda konwertuje aktualny kolor używany przez narzędzie na format przyjazny dla GTK.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param[in] curent_color Uint32 Aktualny kolor narzędzia.
         *
         */
        void set_current_color(Uint32 curent_color);


        /** \brief Metoda ustawia aktualne typ aktualnie używanego narzędzia. Nie zwraca żadnej wartości.
         *
         * \param curent_tool enum tool_type Typ aktualnie używanego narzędzia.
         *
         */
        void set_current_tool(enum tool_type curent_tool);

        /** \brief Metoda zwraca kolor wybrany przez użytkownika w oknie color selector w postaci RGBA.
         * Metoda nie przyjmuje żadnych argumentów wywołania.
         *
         * \return Uint32 Kolor wybrany przez użytkownika (format RGBA 8888).
         *
         */
        Uint32 get_color_response();

        /** \brief Metoda zwraca wybór użytkownika odnośnie typu narzędzia, nie przyjmuje argumentów wywołania.
         *
         *\return Narzędzie wybrane przez użytkownika.
         */
        enum tool_type get_tool_response();

        ~tool_menu();


    private:

        std::size_t number_of_tools; /**< Ilość dostępnych narzędzi w programie. */

        enum tool_type tool_response;/**< Wybrane przez uzytkownika narzędzie. */

        std::deque <struct tool_type_data> tool_types_array; /**< Kolejka, która ułatwia działanie GTK. */

        Uint8 RGB[3] = {0, 0, 0}; /**< Kolor do wyświetlenia jako aktualny w oknie color selector. */

        Uint32 new_color; /**< Kolor wyjściowy z okna color selector */

        /** \brief Konweter koloru z formatu RGB 888 do formatu przyjaznego dla GTK.
         *
         * \param color Uint8* Tablica zawierająca składowe koloru RGB 888.
         * \return GdkColor Kolor w formacie przyjaznym dla GTK (RGBA 16 16 16 16).
         *
         */
        GdkColor convert_from_Uint8(Uint8 *color);

        /** \brief Funkcja obsługująca sygnał kliknięcia na przycisk z wyborem nowego narzędzia.
         * Funkcja nie zwraca żadnej wartości.
         *
         * \param[out] widget GtkWidget* Wskaźnik na okno z którego pochodził sygnał.
         * \param[out] data gpointer Dane dla funkcji.
         *
         */
        static void get_tool_type(GtkWidget *widget, gpointer data) {
            *((reinterpret_cast <struct tool_type_data*>(data))->response) = (reinterpret_cast <struct tool_type_data*>(data))->type;
        }

        /** \brief Funkcja obsługująca sygnał kliknięcia na przycisk otwierający wybór koloru.
         * Funkcja nie zwraca żadnej wartości.
         *
         * \param[out] widget GtkWidget* Wskaźnik na okno z którego pochodził sygnał.
         * \param[out] data gpointer Dane dla funkcji.
         *
         */
        static void trigger_color_chooser(GtkWidget *widget, gpointer data) {
            GtkColorSelection *colorsel;
            GtkWidget *colorseldlg = nullptr;

            gint response;
            GdkColor color;

            /*Convering sdl2 color to gtk color*/
            color.red   = (reinterpret_cast <Uint8*>(data)[0] != 255) ? (gint16)(reinterpret_cast <Uint8*>(data))[0] << 8 : 65535;
            color.green = (reinterpret_cast <Uint8*>(data)[1] != 255) ? (gint16)(reinterpret_cast <Uint8*>(data))[1] << 8 : 65535;
            color.blue  = (reinterpret_cast <Uint8*>(data)[2] != 255) ? (gint16)(reinterpret_cast <Uint8*>(data))[2] << 8 : 65535;

            colorseldlg = gtk_color_selection_dialog_new("Select color"); //creates color chooser window
            gtk_window_set_position(GTK_WINDOW(colorseldlg), GTK_WIN_POS_CENTER_ALWAYS);
            colorsel = GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG(colorseldlg)->colorsel);

            gtk_color_selection_set_previous_color(colorsel, &color);
            gtk_color_selection_set_current_color(colorsel, &color);
            gtk_color_selection_set_has_palette(colorsel, TRUE);

            response = gtk_dialog_run(GTK_DIALOG(colorseldlg));
            if (response == GTK_RESPONSE_OK) {
                gtk_color_selection_get_current_color (colorsel, &color);

                /*Convering gtk color back to sdl2 color*/
                (reinterpret_cast <Uint8*>(data))[0] = color.red   >> 8;
                (reinterpret_cast <Uint8*>(data))[1] = color.green >> 8;
                (reinterpret_cast <Uint8*>(data))[2] = color.blue  >> 8;
            }

            gtk_widget_destroy(colorseldlg);
        }
};

#endif
