/** \file main.cpp
 * \brief Plik zawiera funkcję main.
 */

#include <deque>
#include <cstring>
#include <iostream>
#include <gtk/gtk.h>
#include <SDL2/SDL.h>

#include "window/menu.hpp"
#include "window/window.hpp"
#include "paint_exception.hpp"


int main(int argc, char **argv)
{
    SDL_Event event;
    window *paintWindow;
    try {
        try {
            paintWindow = new window();
        }
        catch (paint_exception& exception){
            std::cerr << "Program failed to load due to a critical exception: " << exception.what() << std::endl;
            return -1;
        }
    }
    catch (std::bad_alloc& exception) {
        std::cerr << "Program failed to load due to a critical exception: " << exception.what() << std::endl;
        return -1;
    }

    try {
        paintWindow->init_sld();
    }
    catch (paint_exception& exception) {
        std::cerr << "Program failed to load due to a critical exception: " << exception.what() << std::endl;
        delete paintWindow;
        return -1;
    }

    gtk_init(&argc, &argv); //initializes gtk

    paintWindow->render_window();


    bool end = false;
    while (!end) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                end = true;
                break;

            case SDL_MOUSEMOTION:
                if (paintWindow->pressed_left_button_tool_flag()) {
                    paintWindow->use_tool(event.motion.x,event.motion.y);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (event.motion.y > (signed)paintWindow->get_menu_height()) {
                        if (paintWindow->pressed_left_button_tool_flag()) {
                            paintWindow->pressed_left_button_second_time_tool_flag(true);
                        }
                        if (!(paintWindow->pressed_left_button_tool_flag())) {
                            paintWindow->set_coppied_pixels();
                        }
                        paintWindow->use_tool(event.motion.x,event.motion.y);
                    }
                    else {
                        try {
                            paintWindow->clicked_on_menu(event.motion.x, event.motion.y);
                        }
                        catch (paint_exception& exception){
                            std::cerr << "Program was closed due to a critical exception: "
                                      << exception.what() << std::endl;
                            end = true;
                        }
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (paintWindow->is_the_tool_a_brush() && event.button.button == SDL_BUTTON_LEFT) {

                    if(paintWindow->pressed_left_button_tool_flag() ||
                       event.motion.y > (signed)paintWindow->get_menu_height()) {
                            paintWindow->pressed_left_button_tool_flag(true);
                       }
                    }
                break;

            case SDL_MOUSEWHEEL:
                paintWindow->resize_brush(event.wheel.y);
                break;

            case SDL_DROPFILE:
                paintWindow->file_drop(event.drop.file);
                break;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    try {
                        end = !paintWindow->resized_window();
                    }
                    catch (paint_exception& exception) {
                        std::cerr << "Program was closed due to a critical exception: "
                                  << exception.what() << std::endl;
                    }
                else if (event.window.event == SDL_WINDOWEVENT_EXPOSED) {
                    paintWindow->redraw_window();
                }

                break;

        }
        try {
            paintWindow->render_window();
        }
        catch (paint_exception& exception) {
            std::cerr << "Program was closed due to a critical exception: " << exception.what() << std::endl;
            end = true;
        }
    }

    delete paintWindow;

    return 0;
}
