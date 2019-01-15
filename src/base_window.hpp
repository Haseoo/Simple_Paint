/** \file base_window.hpp
 * \brief Plik z definicją klasy base_window.
*/

#ifndef BASE_WINDOW_H
#define BASE_WINDOW_H

#include <SDL2/SDL.h>
#include <iostream>

#include "paint_exception.hpp"

/** \brief Klasa bazowa dla elementów okna programu oraz narzędzi.
 */
class base_window {
    public:
        /** \brief Destruktor klasy.
         *
         */
        virtual ~base_window() {

        }
    protected:
        std::size_t window_width, /**< Szerokość okna programu. */
                    window_height,/**< Wysokość okna programu. */
                    menu_height;  /**< Wysokość menu okna programu. */

        Uint32 *window_area; /**< Tablicy z pikselami, na jej podstawie jest renderowane okno programu */
};

#endif
