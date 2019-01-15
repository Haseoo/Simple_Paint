/** \file tool.hpp
 * \brief Plik z definicją klasy tool oraz typu wyliczeniowego tool_type.
*/

#ifndef TOOL_H
#define TOOL_H

/** \brief Typ wyliczeniowy służący do określenia narzędzia.
 */
enum tool_type {BRUSH,        /**< Pędzel */
                STAR_BRUSH,   /**< Pędzel w kształcie plusa. */
                SPRAY,        /**< Pędzel- sprej. */
                FLOOD_FILL,   /**< Wypełnianie obszaru kolorem */
                COLOR_PICKER, /**< Próbnik koloru */
                ELLIPSE,       /**< Elipsa z możliwością rysowania koła. */
                LINE,         /**< Linia. */
                RECTANGLE,    /**< Prostokąt z możliwością rysowania kwadratu. */
                TRIAGNLE,     /**< Trójkąt równoboczny */
                };

#include <SDL2/SDL.h>
#include <gtk/gtk.h>
#include <iostream>
#include <string>
#include <deque>
#include <cmath>

#include "../base_window.hpp"
#include "../paint_exception.hpp"

/** \brief Klasa bazowa dla wszystkich typów narzędzi.
 */
class tool : public base_window
{
    public:
        /*Paiting*/
        bool pressed_left_button = false;            /**< Flaga informująca o stanie wciśnięcia lewego przycisku myszy. */
        bool pressed_left_button_second_time = false;/**< Flaga informująca o ponownym wciśnięciu lewego przycisku myszy. */

        /** \brief Metoda wykonuje akcję zależną od typu narzędzia w podanym punkcie.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param[in] x_position std::size_t Składowa 'x' punktu.
         * \param[in] y_position std::size_t Składowa 'y' punktu.
         *
         */
        virtual void use_tool(std::size_t x_position, std::size_t y_position);

        /*Tool properties menu*/
        virtual void open_tool_properties();

        /*Getting information about the tool*/
        /** \brief Metoda zwraca informację czy narzędzie jest pędzlem. Nie przyjmuje argumentów wywołania.
         *
         * \return bool Jeżeli narzędzie jest pędzlem metoda zwraca wartość true, w przeciwnym wypadku wartość false.
         *
         */
        virtual bool is_a_brush();

        /** \brief Metoda zwraca informację o typie narzędzia. Nie przyjmuje argumentów wywołania.
         *
         * \return enum tool_type Metoda zwraca wartość typu wyliczeniowego tool_type w zależności od typu narzędzia.
         */
        virtual enum tool_type get_tool_type();

        /*Taking care of the tool's data consistency*/
        /** \brief Metoda zapewnia spójność danych z klasą window dotyczących rozmiaru okna i jego tablicy pikseli.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param[in] window Uint32* Wskaźnik na tablicę pikseli okna.
         * \param[in] window_width std::size_t Szerokość okna.
         * \param[in] window_height std::size_t Wysokość okna.
         * \param[in] menu_height std::size_t Wysokość menu okna.
         * \return void
         *
         */
        void update_window_information(Uint32 *window, std::size_t window_width, std::size_t window_height, std::size_t menu_height);

        /** \brief Metoda zmienia rozmiar bieżącego narzędzia.
         *
         * \param[in] difference int Różnica względem obecnego rozmiaru.
         * \return Zwraca true jeśli operacja się powiedzie, w przeciwnym wypadku zwraca false.
         *
         */
        bool resize_tool_size(int difference);

        /** \brief Metoda pozwala zmienić kolor narzędzia. Nie zwraca żadnej wartości.
         *
         * \param[in] new_color Uint32 Kolor (format RGBA) jaki ma zostać ustawiony.
         *
         */
        void update_current_color(Uint32 new_color);

        /** \brief Getter koloru narzędzia.
         *
         * \return Uint32 Metoda zwraca bieżący kolor narzędzia (format RGBA).
         *
         */
        Uint32 get_current_color();

        /** \brief Getter rozmiaru narzędzia.
         *
         * \return std::size_t Metoda zwraca rozmiar narzędzia.
         *
         */
        std::size_t get_brush_size();

        /*Operator overloading*/
        /** \brief Przeciążony operator przypisania. Kopiuje kolor i rozmiar narzędzia.
         *
         */
        tool& operator=(const tool &old_tool) {
            window_area = old_tool.window_area;
            window_width = old_tool.window_width;
            window_height = old_tool.window_height;
            menu_height = old_tool.menu_height;
            brush_size = old_tool.brush_size;
            current_color = old_tool.current_color;
            return *this;
        }

        /*destructor*/
        /** \brief Destruktor klasy.
         *
         */
        virtual ~tool();

    protected:
        /*Tool*/
        enum tool_type type;         /**< Typ narzędzia. */
        Uint32 current_color = 0;    /**< Kolor, którym narzędzie rysuje po ekranie. */
        std::size_t brush_size = 15; /**< Rozmiar narzędzia */

        /** \brief Metoda rysuje na ekranie kwadrat o środku w danym punkcie (na podstawie argumentów wywołania) oraz rozmiarze narzędzia.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param[in] x_position std::size_t Składowa 'x' punktu środka kwadratu.
         * \param[in] y_position std::size_t Składowa 'y' punktu środka kwadratu.
         * \return void
         *
         */
        virtual void PaintPixel(std::size_t x_position, std::size_t y_position);

        /** \brief Funkcja obsługująca sygnał usunięcia okna GTK.
         *
         * \param widget GtkWidget* Wskaźnik na okno z którego pochodził sygnał.
         * \param event GdkEvent* Zdarzenie.
         * \param data gpointer Dane dla funkcji.
         * \return gboolean Funkcja zwraca wartość TRUE.
         *
         */
        static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
            return FALSE;
        }

        /** \brief Funkcja obsługująca sygnał zamknięcia okna, nie zwraca żadnej wartości.
         *
         * \param widget GtkWidget* Wskaźnik na okno z którego pochodził sygnał.
         * \param data gpointer Dane dla funkcji.
         *
         */
        static void destroy(GtkWidget *widget, gpointer data) {
            gtk_main_quit();
        }

};

#endif
