/** \file window.hpp
 * \brief Plik z definicją klasy window.
*/

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <cstring> //for mem family functions
#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include "../base_component.hpp"
#include "menu.hpp"
#include "../file_manager/file_manager.hpp"
#include "../tools/tool.hpp"
#include "../tools/brushes/brush.hpp"
#include "../tools/brushes/star_brush.hpp"
#include "../tools/brushes/spray.hpp"
#include "../tools/flood_fill.hpp"
#include "../tools/shapes/line.hpp"
#include "../tools/color_picker.hpp"
#include "../tools/shapes/ellipse.hpp"
#include "../tools/shapes/rectangle.hpp"
#include "../tools/shapes/triangle.hpp"
#include "../tools/tool_menu.hpp"
#include "../filters/filter_menu.hpp"
#include "../filters/grayscale.hpp"
#include "../filters/sepia.hpp"
#include "../filters/color_inverse.hpp"
#include "../filters/pixelate.hpp"

/** \brief Klasa służąca do obsługi okna głównego programu.
 */
class window : public base_component
{
    public:
        /*Constructor*/
        /** \brief Konstruktor klasy. Ustawia jej pola wartościami domyślnymi, lub podanymi jako argumenty (dotyczy wysokości i szerokości okna),
         * Alokuje również pamięć  na tablicę pikseli, rysuje na niej menu, tworzy komponenty programu m.in. domyśle narzędzie (pedzel).
         * Konstruktor tej klasy "rzuca" wyjątki typu paint_exception, w przypadku ich wystąpienia program nie może działać prawidłowo.
         *
         * \param[in] 1080 std::size_t window_width= Szerokość okna (domyślnie 1080 pikseli).
         * \param[in] 720 std::size_t window_height= Wysokość okna (domyślnie 720 pikseli).
         */
        window(std::size_t window_width = 1080, std::size_t window_height = 720);

        /*Window and menu*/
        /** \brief Getter wysokości menu.
         *
         * \return std::size_t Wysokość menu okna.
         *
         */
        std::size_t get_menu_height();

        /** \brief Metoda zajmująca się obsługą menu. Nie zwraca żadnej wartości.
         * Metoda może "rzucić" wyjątek typu paint_exception w przypadku błędu alokacji pamięci (podczas otwierania pliku).
         *
         * \param[in] x_position std::size_t Pozycja x kliknięcia myszy.
         * \param[in] y_position std::size_t Pozycja y kliknięcia myszy.
         *
         */
        void clicked_on_menu(std::size_t x_position, std::size_t y_position);

        /*Undo facility*/
        /** \brief Metoda kopiuje obszar roboczy tablicy pikseli (bez menu) do bufora. Pozwala na wycofanie ostatniej operacji użytkownika.
         * Nie zwraca żadnej wartości, nie przyjmuje argumentów.
         *
         */
        void set_coppied_pixels();

       /*Tool*/
        /** \brief Metoda używa bieżącego narzędzia do rysowania na tablicy pikseli w miejscu o pozycji podanym jej przez argumenty wywołania.
         * Nie zwraca żadnej wartości.
         *
         * \param[in] mouse_x std::size_t Pozycja x kliknięcia myszy.
         * \param[in] mouse_y std::size_t Pozycja x kliknięcia myszy.
         *
         */
        void use_tool(std::size_t mouse_x, std::size_t mouse_y);

        /** \brief Metoda zmienia rozmiar bieżącego narzędzia. Nie zwraca żadnej wartości.
         *
         * \param[in] difference int Różnica względem obecnego rozmiaru.
         *
         */
        void resize_brush(int difference);

        /** \brief Dzięki tej metodzie można dowiedzieć się czy bieżące narzędzie jest pędzlem. Jest to ważne dla mechaniki rysowania.
         * Metoda zwraca wartość typu bool, nie przyjmuje argumentów wywołania.
         *
         * \return bool Zwraca true jeśli bieżące narzędzie jest pędzlem, w przeciwnym przypadku zwraca false.
         *
         */
        bool is_the_tool_a_brush();

        /** \brief Metoda informuje o stanie flagi wciśnięcia prawego przycisku myszy (1 raz) bieżącego narzędzia, pozwala zmienić jej stan.
         * Znajomość stanu flagi jest kluczowa dla mechanizmu rysowania.
         *
         * \param[in] bool change_flag Jeżeli wartość tego argumentu to true, to flaga zostanie zmieniona. Domyślna wartość to false.
         * \return bool Metoda zwraca stan flagi wciśnięcia prawego przycisku myszy bieżącego narzędzia.
         *
         */
        bool pressed_left_button_tool_flag(bool change_flag = false);

        /** \brief Metoda informuje o stanie flagi wciśnięcia prawego przycisku myszy (2 raz) bieżącego narzędzia, pozwala zmienić jej stan.
         * Znajomość stanu flagi jest kluczowa dla mechanizmu rysowania.
         *
         * \param[in] bool change_flag Jeżeli wartość tego argumentu to true, to flaga zostanie zmieniona. Domyślna wartość to false.
         * \return bool Metoda zwraca stan flagi wciśnięcia prawego przycisku myszy po raz drugi bieżącego narzędzia.
         *
         */
        bool pressed_left_button_second_time_tool_flag(bool change_flag = false);

        /*SDL2 things*/
        /** \brief Metoda inicjuje bibliotekę SDL2 oraz okno programu. Metoda nie przyjmuje argumentów wywołania.
         * Metoda może "rzucić" wyjątki typu paint_exception kiedy wystąpi błąd podczas inicjowania biblioteki bądź okna.
         *
         */
        void init_sld();

        /** \brief Metoda wyświetla zawartość tablicy pikseli w oknie programu. Wykonanie operacji renderowania jest zależne od stanu flagi.
         * Metoda nie zwraca żadnej wartości i nie przyjmuje argumentów wywołania.
         * Metoda może "rzucać" wyjątki typu paint_exceptoin jeśli wystąpi błąd jednej z funkcji SDL2 służącej do renderowania obrazu.
         *
         *
         */
        void render_window();

        /** \brief Metoda odpowiada za obsługę upuszczenia pliku w oknie programu. Metoda nie zwraca żadnej wartości.
         *
         * \param[in] file_path char* Ścieżka do upuszczonego pliku.
         *
         */
        void file_drop(char *file_path);

        /** \brief Metoda zmienia rozmiar okna programu, zmienia parametry okna oraz kopiuje zawartość tablicy i bufora pikseli.
         * Używana, gdy użytkownik zmieni rozmiar okna programu. Nie przyjmuje argumentów wywołania.
         * Metoda może "rzucić" wyjątki typu paint_exceptoin.
         * Meotda może "rzucać" wyjątki w przypadku błędu alokacji pamięci lub aktualizowania okna.
         *
         * \return bool Metoda zwraca true jeśli operacja się powiedzie, w przeciwnym wypadku zwraca false.
         *
         */
        bool resized_window();

        /** \brief Metoda zmienia rozmiar okna programu na podstawie argumentów, zmienia parametry okna oraz kopiuje zawartość tablicy i bufora pikseli.
         * Używana podczas wczytywania obrazów z pliku.Okno nie może być mniejsze niż 400x200 pikseli.
         * Metoda dba o to żeby okno programu nie było mniejsze niż 400x200 pikseli oraz o spójnść danych wszystkich obiektów.
         * Meotda może "rzucać" wyjątki w przypadku błędu alokacji pamięci lub aktualizowania okna.
         *
         * \param[in] new_width std::size_t Nowa szerokość okna.
         * \param[in] new_height std::size_t Nowa wysokość okna.
         * \return bool
         *
         */
        bool resized_window(std::size_t new_width, std::size_t new_height);

        /** \brief Metoda odpowiada za odrysowanie okna programu. Nie przyjmuje argumentów wywołania i nie zwraca żadnej wartości.
         *
         */
        void redraw_window();

        /*Destructor*/
        /** \brief Destruktor, zajmuje się usuwaniem zmiennych zaalokowanych dynamicznie.
         *
         */
        ~window();

    private:
        /*Window and menu*/
        std::string window_name = "Simple Paint";/**< Pole typu std::string zawierające nazwę okna programu. */
        Uint32 *copied_pixels;           /**< Buffor z plkselami, umożliwa realizacje operacji undo/redo. */
        menu window_menu;                /**< Obiekt- menu programu. */
        tool_menu tool_menu_widget;      /**< Obiekt- okno menu z narzędziami. */
        file_manager file_manager_widget;/**< Obiekt- okno managera plików. */
        filter_menu filter_menu_widget;  /**< Obiekt- okno menu fltrów. */

        /** \brief Metoda czyści obszar roboczy okna programu. Sprawdza czy użytkownik go edytował, w takim wypadku prosi go o potwierdzenie operacji.
         * Metoda zwraca żadnej wartości i nie przyjmuje argumentów wywołania.
         *
         */
        void reset_canva();

        /*Undo facility*/
        /** \brief Metoda podmienia zawartość bufora pikseli z tablicą pikseli okna programu.
         * Nie zwraca żadnej wartości i nie przyjmuje argumentów wywołania.
         * Metoda może "rzucić" wyjątek typu paint_exception w przypadku błędu alokacji pamięci.
         *
         */
        void swap_current_and_undo_pixels();

        /** \brief Metoda otwiera menu do wyboru narzędzi zrealizowanym za pomocą biblioteki GTK+-2.0.
         * Nie zwraca żadnej wartości i nie przyjmuje argumentów wywołania.
         *
         */
        void trigger_tool_menu();
        /** \brief Metoda otwiera menu do wyboru pliku zrealizowanym za pomocą biblioteki GTK+-2.0.
         * Nie zwraca żadnej wartości i nie przyjmuje argumentów wywołania.
         *
         */
        void trigger_file_manager_menu();

        /** \brief Metoda otwiera menu do wyboru filtrów zrealizowanym za pomocą biblioteki GTK+-2.0.
         * Nie zwraca żadnej wartości i nie przyjmuje argumentów wywołania.
         *
         */
        void trigger_filter_menu();

        /*Tool*/
        tool *current_tool;/**< Wskaźnik na bieżące narzędzie. */
        bool render = true;/**< Flaga renderowania okna, domyślna wartość do true. */


        /*SDL2 things*/
        SDL_Window *sdl_window;/**< Wskaźnik na okno główne programu. */
        SDL_Renderer *renderer;/**< Wskaźnik na obiekt biblioteki SDL2 służący do renderownia obrazu. */
        SDL_Texture *texture;  /**< Wskaźnik na obiekt biblioteki SDL2 zawierający teksturę okna. */

        /** \brief Metoda służąca do wypisywania komunikatu o błędzie zrealizowana za pomocą biblioteki SDL2.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param text const char* Komunikat o błędzie do wyświetlenia w oknie.
         *
         */
        void print_sdl_error(const char *text);
};

#endif
