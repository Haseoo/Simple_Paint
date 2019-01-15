/** \file window.cpp
 * \brief Plik z definicjami metod klasy window.
*/
#include "window.hpp"

window::window(std::size_t window_width, std::size_t window_height) {
    this->window_width = window_width;
    this->window_height = window_height;
    this->menu_height = 40;

    try {
        window_area = new Uint32[window_height * window_width]; //allocating memeory to window pixels
        copied_pixels = new Uint32[(window_height - menu_height) * window_width]; //allocating memory to pixel buffer

        memset(window_area, 255, sizeof(Uint32) * window_height * window_width); //setting window area to white
        memset(copied_pixels, 255, sizeof(Uint32) * (window_height - menu_height) * window_width); //setting copied pixels to white

        current_tool = new brush; //default tool is brush
    }
    catch (std::bad_alloc& exception) {
        throw paint_exception(paint_exception::WINDOW_BAD_ALLOC, exception.what());
        return;
    }

    try {
        current_tool->update_window_information(window_area, window_width, window_height, menu_height);

        this->window_menu.update_window_information(window_area, menu_height, window_width);
        this->window_menu.update_tool_pointer(current_tool);

        window_menu.print_menu();
    }
    catch (paint_exception& exception) {
        throw exception;
    }
}



std::size_t window::get_menu_height() {
    return menu_height;
}

void window::clicked_on_menu(std::size_t x_position, std::size_t y_position) {
    try {
        if (window_menu.is_in_color_menu(x_position) && !current_tool->pressed_left_button) {
            current_tool->update_current_color(window_area[y_position * window_width + x_position]);
            window_menu.print_current_color();
            render = true;
        }
        else if (window_menu.is_in_buttons_area(x_position) && !current_tool->pressed_left_button) {
            enum menu_buttons clicked_button = window_menu.get_clicked_button(x_position);
            switch (clicked_button) {
                case NEW_FILE:
                    reset_canva();
                    break;

                case UNDO:
                    swap_current_and_undo_pixels();
                    render = true;
                    break;

                case OPEN_SAVE_FILE: {
                    trigger_file_manager_menu();
                    break;
                }

                case TOOL_CHOOSER:
                    trigger_tool_menu();
                    break;
                case FILTERS:
                    trigger_filter_menu();
                    break;

                case TOOL_PROPERITES: {
                    current_tool->open_tool_properties();
                    break;
                }
            }
        }
    }
    catch (paint_exception& exception) {
        print_sdl_error(exception.what().c_str());
    }
}

void window::reset_canva() {
    int cmp_result = memcmp(window_area + (menu_height * window_width), copied_pixels,
                             sizeof(Uint32) * window_width * (window_height - menu_height));
    if (cmp_result == 0) {
        memset(window_area + (menu_height * window_width), 255,
               sizeof(Uint32) * window_width * (window_height - menu_height));
        memset(copied_pixels, 255, sizeof(Uint32) * window_width * (window_height - menu_height));
        render = true;
    }
    else {
        const SDL_MessageBoxButtonData buttons[3] = {
                                                      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "yes"   },
                                                      {                                      0, 1, "no"    },
                                                      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel"}
                                                    };

        const SDL_MessageBoxData messageboxdata = {
                                                    SDL_MESSAGEBOX_INFORMATION,
                                                    sdl_window,
                                                    "Resetting workspace area",
                                                    "Unsaved work will be lost, are you sure?",
                                                    SDL_arraysize(buttons),
                                                    buttons,
                                                    nullptr
                                                  };

        int confirmation_dialog_choice = 0;

        if (SDL_ShowMessageBox(&messageboxdata, &confirmation_dialog_choice) < 0) {
            throw paint_exception(paint_exception::WINDOW_SDL_DIALOG);
        }

        if (confirmation_dialog_choice == 0) {
            memset(window_area + (menu_height * window_width), 255,
            sizeof(Uint32) * window_width * (window_height - menu_height));
            memset(copied_pixels, 255, sizeof(Uint32) * window_width * (window_height - menu_height));
            render = true;
            file_manager_widget.reset_state();
            SDL_SetWindowTitle(sdl_window, window_name.c_str());
        }
    }
}

void window::swap_current_and_undo_pixels() {
    Uint32 *tmp;
    try {
        tmp = new Uint32[window_width * (window_height - menu_height)];
    }
    catch(std::bad_alloc& exception) {
        throw paint_exception(paint_exception::WINDOW_PIXELS_SWAP);
        return;
    }
    memcpy(tmp, window_area + (menu_height * window_width),
            sizeof(Uint32) * window_width * (window_height - menu_height));
    memcpy(window_area + (menu_height * window_width), copied_pixels,
            sizeof(Uint32) * window_width * (window_height - menu_height));
    memcpy(copied_pixels, tmp, sizeof(Uint32) * window_width * (window_height - menu_height));
    delete[] tmp;
}

void window::set_coppied_pixels() {
    memcpy(copied_pixels, window_area + (menu_height * window_width),
            sizeof(Uint32) * window_width * (window_height - menu_height));
}


void window::trigger_tool_menu() {
    tool_menu_widget.set_current_color(current_tool->get_current_color());
    tool_menu_widget.set_current_tool(current_tool->get_tool_type());
    try {
        tool_menu_widget.open_gtk_window();

        Uint32 new_color = tool_menu_widget.get_color_response();
        enum tool_type new_tool_type = tool_menu_widget.get_tool_response();


        if (current_tool->get_tool_type() != new_tool_type) {
            tool *new_tool;
            try {
                switch (new_tool_type) {
                    case BRUSH:
                        new_tool =  new brush;
                        break;

                    case STAR_BRUSH:
                        new_tool =  new star_brush;
                        break;

                    case SPRAY:
                        new_tool =  new spray;
                        break;

                    case FLOOD_FILL:
                        new_tool = new flood_fill;
                        break;

                    case COLOR_PICKER:
                        new_tool = new color_picker;
                        break;

                    case ELLIPSE:
                        new_tool = new ellipse;
                        break;

                    case LINE:
                        new_tool = new line;
                        break;

                    case RECTANGLE:
                        new_tool = new rectangle;
                        break;

                    case TRIAGNLE:
                        new_tool = new triangle;
                        break;
                }
                *new_tool = *current_tool;
                delete current_tool;
                current_tool = new_tool;
                window_menu.update_tool_pointer(current_tool);
                window_menu.update_tool_state();
            }
            catch (std::bad_alloc& exception) {
                throw paint_exception(paint_exception::WINDOW_BAD_ALLOC, exception.what());
            }
        }
        else if (current_tool->get_current_color() != new_color) {
            current_tool->update_current_color(new_color);
            window_menu.add_color_to_queue(new_color);
            window_menu.print_current_color();
        }
        render = true;
    }
    catch (paint_exception& exception) {
        print_sdl_error(exception.what().c_str());
    }

}

void window::trigger_file_manager_menu() {
    file_manager_widget.open_gtk_window();

    file_manager_mode mode = file_manager_widget.get_file_manager_mode();

    if (mode == OPEN_FILE) {
        file_manager_widget.load_image();
        std::size_t new_width = 0, new_height = 0;
        file_manager_widget.get_image_dimentions(new_width, new_height);
        resized_window(new_width, new_height + menu_height);
        file_manager_widget.update_file_manager_information(window_area, window_width, window_height, menu_height);
        file_manager_widget.print_image();
        render = true;
        SDL_SetWindowTitle(sdl_window, (window_name + "- " + file_manager_widget.get_file_path()).c_str());
    }
    else if (mode == SAVE_FILE) {
        file_manager_widget.update_file_manager_information(window_area, window_width, window_height, menu_height);
        file_manager_widget.save_window_to_image();
        SDL_SetWindowTitle(sdl_window, (window_name + "- " + file_manager_widget.get_file_path()).c_str());
    }
    else if (mode == QUICK_SAVE) {
        file_manager_widget.update_file_manager_information(window_area, window_width, window_height, menu_height);
        file_manager_widget.save_window_to_image();
    }


}

void window::trigger_filter_menu() {
    filter_menu_widget.open_gtk_window();

    enum filter_type response = filter_menu_widget.get_filter_response();

    basic_filter *filter = nullptr;
    try {
        switch (response) {
            case GRAYSCALE:
                filter = new grayscale;
                break;

            case COLOR_INVERSE:
                filter = new color_inverse;
                break;

            case SEPIA:
                filter = new sepia;
                break;

            case PIXELATE:
                filter = new pixelate;
                break;

            case NONE_FILTER:
                break;
        }
    }
    catch (std::bad_alloc& exception) {
        throw paint_exception(paint_exception::WINDOW_BAD_ALLOC, exception.what());
    }

    if (filter) {
        set_coppied_pixels();

        filter->update_filter_information(window_area, window_width, window_height, menu_height);
        filter->open_fiter_properties();
        filter->do_filter();

        delete filter;

        render = true;
    }
}



void window::use_tool(std::size_t mouse_x, std::size_t mouse_y) {
    try {
        Uint32 old_color = current_tool->get_current_color();
        current_tool->use_tool(mouse_x, mouse_y);
        if (old_color != current_tool->get_current_color()) {
            window_menu.print_current_color();
        }
        render = true;
    }
    catch (paint_exception& exception) {
        print_sdl_error(exception.what().c_str());
    }
}

void window::resize_brush(int difference) {
    if (current_tool->resize_tool_size(difference)) {
        window_menu.update_brush_size_state();
        render = true;
    }
}

bool window::is_the_tool_a_brush() {
    return current_tool->is_a_brush();
}

bool window::pressed_left_button_tool_flag(bool change_flag) {
    current_tool->pressed_left_button = current_tool->pressed_left_button ^ change_flag;
    return current_tool->pressed_left_button;
}

bool window::pressed_left_button_second_time_tool_flag(bool change_flag) {
    current_tool->pressed_left_button_second_time = current_tool->pressed_left_button_second_time ^ change_flag;
    return current_tool->pressed_left_button_second_time;
}



void window::init_sld() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw paint_exception(paint_exception::WINDOW_SDL_INIT, SDL_GetError());
        return;
    }

    sdl_window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  window_width, window_height,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    if (sdl_window == nullptr) {
       throw paint_exception(paint_exception::WINDOW_SDL_INIT, SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        throw paint_exception(paint_exception::WINDOW_SDL_INIT, SDL_GetError());
        return;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
                                window_width, window_height);
    if (texture == nullptr) {
        throw paint_exception(paint_exception::WINDOW_SDL_INIT, SDL_GetError());
        return;
    }
    if (SDL_UpdateTexture(texture, nullptr, window_area, window_width * sizeof(Uint32))) {
        throw paint_exception(paint_exception::WINDOW_SDL_INIT, SDL_GetError());
    }
}

void window::render_window() {
    if (render) {
        if (SDL_UpdateTexture(texture, nullptr, window_area, window_width * sizeof(Uint32)) < 0) {
            throw paint_exception(paint_exception::WINDOW_SDL_RENDER, SDL_GetError());
        }
        else if (SDL_RenderClear(renderer) < 0) {
            throw paint_exception(paint_exception::WINDOW_SDL_RENDER, SDL_GetError());
        }
        else if (SDL_RenderCopy(renderer, texture, nullptr, nullptr) < 0) {
            throw paint_exception(paint_exception::WINDOW_SDL_RENDER, SDL_GetError());
        }
        SDL_RenderPresent(renderer);
        render = false;
    }
}

void window::file_drop(char *file_path) {
    std::string string_file_path(file_path);
    try {
        file_manager_widget.load_image(file_path);
        std::size_t new_width = 0, new_height = 0;
        file_manager_widget.get_image_dimentions(new_width, new_height);
        resized_window(new_width, new_height + menu_height);
        file_manager_widget.update_file_manager_information(window_area, window_width, window_height, menu_height);
        file_manager_widget.print_image();
        render = true;
        SDL_SetWindowTitle(sdl_window, (window_name + "- " + file_manager_widget.get_file_path()).c_str());

    }
    catch(paint_exception& exception) {
        print_sdl_error(exception.what().c_str());
    }

    SDL_free(file_path);
}

bool window::resized_window() {
    int new_width = 0, new_height = 0;
    SDL_GetWindowSize(sdl_window, &new_width, &new_height); //getting new size of window
    new_width = (new_width < 400) ? 400 : new_width; // window minimium size
    new_height = (new_height < 200) ? 200 : new_height; //window minimum height
    SDL_SetWindowSize(sdl_window, new_width, new_height); // setting new size of window

    Uint32 *new_window_area;
    Uint32 *new_copied_pixels;
    try {
        new_window_area = new Uint32 [new_height * new_width]; //making new pixel array for new dimentions
        new_copied_pixels = new Uint32 [new_height * new_width];
        memset(new_window_area, 255, sizeof(Uint32) * new_height * new_width); // setting all to white
        memset(new_copied_pixels, 255, sizeof(Uint32) * new_height * new_width); // setting all to white
    }
    catch (std::bad_alloc& exception) {
        throw paint_exception(paint_exception::WINDOW_SDL_RESIZED, exception.what());
        return false;
    }

    int miniumum_height = (new_height < (int)window_height) ? new_height : window_height;
    int minimum_width   = (new_width < (int)window_width) ? new_width : window_width;

    Uint32 *new_window_pointer = new_window_area + new_width * menu_height; //setting pointer to area below the menu
    Uint32 *new_copied_pixels_pointer = new_copied_pixels;

    for (int i = menu_height; i < miniumum_height ; i++) { //copying data to new pixel array starting below the menu
        memcpy(new_window_pointer, window_area + i * window_width, minimum_width * sizeof(Uint32));
        new_window_pointer += new_width;
    }
    //TODO merge these two loops
    for(std::size_t i = 0; i < miniumum_height - menu_height; i++) {
        memcpy(new_copied_pixels_pointer, copied_pixels + i * window_width, minimum_width * sizeof(Uint32));
        new_copied_pixels_pointer += new_width;
    }

    window_height = (size_t)new_height; //setting new dimentions
    window_width = (size_t)new_width;

    delete[] window_area; // making free old pixel array
    delete[] copied_pixels;
    window_area = new_window_area; //seting pointer to new pixel array
    copied_pixels = new_copied_pixels;

    SDL_DestroyTexture(texture);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, window_width, window_height);
    SDL_UpdateTexture(texture, NULL, window_area, window_width * sizeof(Uint32)); //making new render with new dimentions
    if (texture == nullptr) {
        throw paint_exception(paint_exception::WINDOW_SDL_RESIZED, SDL_GetError());
        return false;
    }

    try {
        current_tool->update_window_information(window_area, window_width, window_height, menu_height);
        //updating data about window dimentnions
        window_menu.update_window_information(window_area, menu_height, window_width);
        //updating data about window dimentnions
    }
    catch(paint_exception& exception) {
        throw exception;
        return false;
    }

    window_menu.print_menu();

    render = true;

    return true;
}

bool window::resized_window(std::size_t new_width, std::size_t new_height) {
    new_width = (new_width > 400) ? new_width : 400;
    new_height = (new_height > 200 ) ? new_height : 200;

    SDL_SetWindowSize(sdl_window, new_width, new_height); // setting new size of window

    Uint32 *new_window_area;
    Uint32 *new_copied_pixels;

    try {
        new_window_area = new Uint32 [new_height * new_width]; //making new pixel array for new dimentions
        new_copied_pixels = new Uint32 [new_height * new_width];
        memset(new_window_area, 255, sizeof(Uint32) * new_height * new_width); // setting all to white
        memset(new_copied_pixels, 255, sizeof(Uint32) * new_height * new_width); // setting all to white
    }
    catch (std::bad_alloc& exception) {
        throw paint_exception(paint_exception::WINDOW_SDL_RESIZED,exception.what());
        return false;
    }

    memset(new_window_area, 255, sizeof(Uint32) * new_height * new_width); // setting all to white
    memset(new_copied_pixels, 255, sizeof(Uint32) * new_height * new_width); // setting all to white

    delete[] window_area; // making free old pixel array
    delete[] copied_pixels;

    window_area = new_window_area; //seting pointer to new pixel array
    copied_pixels = new_copied_pixels;

    window_width = new_width;
    window_height = new_height;

    SDL_DestroyTexture(texture);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, window_width, window_height);
    SDL_UpdateTexture(texture, NULL, window_area, window_width * sizeof(Uint32)); //making new render with new dimentions
    if (texture == nullptr) {
        throw paint_exception(paint_exception::WINDOW_SDL_RESIZED, SDL_GetError());
        return false;
    }

    try {
        current_tool->update_window_information(window_area, window_width, window_height, menu_height);
        //updating data about window dimentnions
        window_menu.update_window_information(window_area, menu_height, window_width);
        //updating data about window dimentnions
    }
    catch(paint_exception& exception) {
        throw exception;
        return false;
    }

    window_menu.print_menu();

    render = true;

    return true;
}

void window::redraw_window() {
    render = true;
}

void window::print_sdl_error(const char *text) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An error occurred", text, sdl_window);
}



window::~window()
{
    delete[] window_area;
    delete[] copied_pixels;
    delete current_tool;

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}
