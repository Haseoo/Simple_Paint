/** \file menu.hpp
 * \brief Plik z definicją klasy menu oraz typu wyliczeniowego menu_buttons.
 */

#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include "../base_window.hpp"
#include "../tools/tool.hpp"

/** \brief Typ wyliczeniowy służący do określenia przycisku z menu.
 *Używany do określenia, który przycisk z menu został wybrany oraz do wczytywania ich etykiet.
 */
 enum menu_buttons {NEW_FILE,     /**< Resetowanie obszaru roboczego.*/
                   UNDO,          /**< Operacja undo/redo. */
                   OPEN_SAVE_FILE,/**< Menu dotyczące operacji na plikach. */
                   TOOL_CHOOSER,  /**< Menu wyboru narzędzi. */
                   FILTERS,       /**< Menu z filtrami. */
                   TOOL_PROPERITES/**< Menu z opcjami aktualnie używanego narzędzia. */
                  };

/** \brief Klasa służaca do rysowania menu oraz obsługi kliknięć w jego obrębie.
 */
class menu : public base_window
{
    public:
        /*Constructor*/
        /** \brief Konstruktor klasy. Otwiera pliki zawierające etykiety przycisków i narzędzi oraz wypełnia tablice pikseli ich zawartością.
         * Jeśli nie uda się otworzyć bądź odczytać jednego z pliku zostanie ustawiona flaga informująca o tym fakcie.
         * Konstruktor tej klasy "rzuca" wyjątki typu paint_exception, w przypadku ich wystąpienia program nie może działać prawidłowo.
         */
        menu();

        /*Taking care of the menu's data consistency*/
        /** \brief Metoda zapewnia spójność danych z klasą window dotyczących rozmiaru okna i jego tablicy pikseli.
         * Metoda nie zwraca żadnej wartości, może "rzucać" wyjątki typu paint_exception w przypadku nieprawidłowych danych wejściowych.
         *
         * \param[in] window Uint32* Wskaźnik na tablicę pikseli okna.
         * \param[in] menu_height std::size_t Wysokość menu okna.
         * \param[in] window_width std::size_t Szerokość okna.
         *
         */
        void update_window_information(Uint32 *window, std::size_t menu_height, std::size_t window_width);

        /** \brief Metoda zapewnia spójność danych z klasą window dotyczących bieżącego narzędzia.
         * Klasa potrzebuje tych informacji, ponieważ odpowiada za wyświetlanie informacji o stanie bieżącego narzędzia.
         * Metoda nie zwraca żadnej wartości, może "rzucać" wyjątki typu paint_exception w przypadku nieprawidłowych danych wejściowych.
         *
         * \param[in] tool_prt tool* Wskaźnik na bieżące narzędzie.
         *
         */
        void update_tool_pointer(tool *tool_prt);

        /*Printing menu*/
        /** \brief Metoda odpowiada za rysowanie menu programu. Funkcja nie przyjmuje argumentów wywołania i  nie zwraca żadnej wartości.
         *
         */
        void print_menu();

        /** \brief Metoda rysuje kolory w menu, które są zawarte w kolejce.
         * Metoda nie zwraca żadnej wartości i nie przyjmuje argumentów wywołania.
         * Metoda może "rzuać" wyjątek typu paint_exception w przypadku braku miejsca do rysowania.
         *
         */
        void update_colors();

        /*Tool*/
        /** \brief Metoda rysuje w menu czarny kwadrat, który reprezentuje rozmiar narzędzia.
         * Metoda nie zwraca żadnej wartości i nie przyjmuje argumentów wywołania.
         * Metoda może "rzuać" wyjątek typu paint_exception w przypadku rozmiaru pędza równego 0.
         *
         */
        void update_brush_size_state();

        /** \brief Metoda rysuje etykietę bieżącego narzędzia.
         * Metoda nie zwraca żadnej wartości i nie przyjmuje argumentów wywołania.
         *
         */
        void update_tool_state();

        /*Menu color area*/
        /** \brief Metoda dodaje kolor podany jako argument do kolejki kolorów.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param[in] color Uint32 Kolor (format RGBA) jaki ma zostać dodany do kolejki.
         *
         */
        void add_color_to_queue(Uint32 color);

        /** \brief Metoda rysuje w menu kwadrat w kolorze pobieranym od bieżącego narzędzia.
         * Metoda nie zwraca żadnej wartości, może "rzucać" wyjątek typu paint_exception, gdy dodanie koloru do kolejki się nie powiedzie.
         *
         */
        void print_current_color();

        /** \brief Metoda informuje czy punkt (wystarczy tylko położenie X) znajduje się o obszarze kolorów w menu.
         * Metoda może "rzucać" wyjątki typu paint_exception w przypadku nieprawidłowych danych wejściowych.
         *
         * \param[in] x_position std::size_t Składowa 'x' punktu kliknięcia.
         * \return bool Metoda zwraca true jeśli punkt znajduje się w obszarze kolorów w menu, w przeciwnym wypadku zwraca false.
         *
         */
        bool is_in_color_menu(std::size_t x_position);

        /*Menu buttons area*/
        /** \brief Metoda informuje czy punkt (wystarczy tylko położenie X) znajduje się o obszarze przycisków w menu.
         * Metoda może "rzucać" wyjątki typu paint_exception w przypadku nieprawidłowych danych wejściowych.
         *
         * \param[in] x_position std::size_t Składowa 'x' punktu kliknięcia.
         * \return bool Metoda zwraca true jeśli punt znajduje się w obszarze przycisków w menu, w przeciwnym wypadku zwraca false.
         *
         */
        bool is_in_buttons_area(std::size_t x_position);

        /** \brief Metoda zwraca na podstawie punktu kliknięcia (wystarczy tylko położenie X) jaki przycisk menu został wciśnięty przez użytkownika.
         * Metoda może "rzucać" wyjątki typu paint_exception w przypadku nieprawidłowych danych wejściowych.
         *
         * \param[in] x_position std::size_t Składowa 'x' punktu kliknięcia.
         * \return enum menu_buttons Wartość typu wyliczeniowego odpowiadająca klikniętemu przez użytkownika przyciskowi.
         */
        enum menu_buttons get_clicked_button(std::size_t x_position);

        /*destructor*/
        /** \brief Destruktor klasy, zwalnia pamięć po wszystkich zmiennych zaalokowanych dynamicznie.
         */
        ~menu();

    private:

        /*Menu buttons area*/
        std::size_t NUMBER_OF_BUTTONS;                        /**< Liczba przycisków w menu. */
        const static std::size_t NUMBER_OF_LEFT_ELEMENTS = 3; /**< Liczba elementów sygnalizujących stan bieżącego narzędzia (kolor, rozmiar, typ). */
        std::size_t NUMBER_OF_TOOLS;                          /**< Liczba rodzajów narzędzi. */
        std::deque <std::string> menu_buttons_images_paths;   /**< Kolejka ze ścieżkami do plików zawierających etykiety przycisków. */

        std::deque <Uint32*> menu_buttons_labels; /**< Kolejka wskaźników na tablice pikseli z etykietami przycisków. */

        /*Tool*/
        tool *tool_prt = nullptr;         /**< Wskaźnik na bieżące narzędzie. */
        std::deque <Uint32*> tool_labels; /**< Kolejka wskaźników na tablice pikseli zawierające etykiety narzędzi. */
        std::deque <std::string> tools_images_paths; /**< Kolejka ze ścieżkami do plików zawierających etykiety narzędzi. */

        /*Menu color area*/
        const static std::size_t COLOR_BUFFER_MAX_SIZE = 25; /**< Maksymalna wielkość bufora kolorów w menu. */
        std::size_t colors_to_print;                         /**< Liczba kolorów jaką można narysować przy danym rozmiarze okna programu. */

        std::deque <Uint32> color_buffer = {0x000000, 0x808080, 0xFFFFFF, 0x800000, 0xFF0000,
                                            0xFFA500, 0x800080, 0xFF69B4, 0x008000, 0x08E100,
                                            0x93FF2D, 0xFFFF00, 0xFFFF83, 0x000080, 0x0000FF}; /**< Kolejka zawierająca kolory wyświetlane w menu. */

};
#endif
