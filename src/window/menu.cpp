/** \file menu.cpp
 * \brief Plik z definicjami metod klasy menu.
 */

#include "menu.hpp"


menu::menu() {
    std::fstream rc_file("assets/resources/menu.rc", std::ios::in);
    /*Reading label images' files form rc file*/
    if (rc_file.is_open()) {
        NUMBER_OF_BUTTONS = (std::size_t)rc_file.get();
        if (rc_file.fail()) {
            throw paint_exception(paint_exception::MENU_RESOURCES);
            return;
        }
        else if (NUMBER_OF_BUTTONS == 0) {
            throw paint_exception(paint_exception::MENU_NUMBER_OF_BUTTONS);
            return;
        }

        for(std::size_t i = 0; i < NUMBER_OF_BUTTONS; i++) {
            std::string buffer;
            getline(rc_file, buffer, '\0');
            if (rc_file.fail()) {
                throw paint_exception(paint_exception::MENU_BUTTON_LABLES_PATH);
                return;
            }
            try {
                menu_buttons_images_paths.push_back(buffer);
            }
            catch (std::bad_alloc& exception) {
                throw paint_exception(paint_exception::MENU_BAD_ALLOC, exception.what());
                return;
            }
        }

        NUMBER_OF_TOOLS = (std::size_t)rc_file.get();

        for(std::size_t i = 0; i < NUMBER_OF_TOOLS; i++) {
            std::string buffer;
            getline(rc_file, buffer, '\0');
            if (rc_file.fail()) {
                throw paint_exception(paint_exception::MENU_TOOL_LABELS_PATH);
                return;
            }
            try {
                tools_images_paths.push_back(buffer);
            }
            catch (std::bad_alloc& exception) {
                
                return;
            }
        }
    }
    else {
        throw paint_exception(paint_exception::MENU_RESOURCES);
        return;
    }

    /*Reading buttons labels' images form files*/
    for (std::size_t i = 0; i < NUMBER_OF_BUTTONS; i++) {
        std::ifstream label_file (menu_buttons_images_paths[i], std::ios::binary);
        if (label_file.is_open()) {
            Uint32 *image;
            try {
                image = new Uint32[40 * 40];
            }
            catch (std::bad_alloc& exception) {
                throw paint_exception(paint_exception::MENU_BAD_ALLOC, exception.what());
                return;
            }
            label_file.read(reinterpret_cast<char*>(image), sizeof(Uint32) * 40 * 40);
            if (label_file.fail()) {
                throw paint_exception(paint_exception::MENU_TOOL_LABEL, menu_buttons_images_paths[i]);
                return;
            }
            try {
                menu_buttons_labels.push_back(image);
            }
            catch (std::bad_alloc& exception) {
                throw paint_exception(paint_exception::MENU_BAD_ALLOC, exception.what());
                return;
            }
            label_file.close();

        }
        else {
            throw paint_exception(paint_exception::MENU_TOOL_LABEL, menu_buttons_images_paths[i]);
            return;
        }
    }

    /*Reading tools labels' images form files*/
    for(std::size_t i = 0; i < NUMBER_OF_TOOLS; i++) {
        std::ifstream label_file (tools_images_paths[i], std::ios::binary);
        if (label_file.is_open()) {
            Uint32 *image;
            try {
                image = new Uint32[40 * 40];
            }
            catch (std::bad_alloc& exception) {
                throw paint_exception(paint_exception::MENU_BAD_ALLOC, exception.what());
                return;
            }
            label_file.read(reinterpret_cast<char*>(image), sizeof(Uint32) * 40 * 40);
            if (label_file.fail()) {
                
                return;
            }
            try {
                tool_labels.push_back(image);
                label_file.close();
            }
            catch (std::bad_alloc& exception) {
                throw paint_exception(paint_exception::MENU_BAD_ALLOC, exception.what());
                return;
            }
        }
        else {
            throw paint_exception(paint_exception::MENU_TOOL_LABEL, tools_images_paths.at(i));
        }
    }
}



void menu::update_window_information(Uint32 *window, std::size_t menu_height, std::size_t window_width) {
    if (window)
        this->window_area = window;
    else
        throw paint_exception(paint_exception::BAD_WINDOW_PTR, "menu.");

    if (menu_height >= 40 && window_width >= 400) {
        this->menu_height = menu_height;
        this->window_width = window_width;
    }
    else {
        throw paint_exception(paint_exception::BAD_WINDOW_DIM, "menu.");
    }
}

void menu::update_tool_pointer(tool *tool_prt) {
    if (tool_prt)
        this->tool_prt = tool_prt;
    else
        throw paint_exception(paint_exception::BAD_TOOL_PTR, "menu.");
}



void menu::print_menu() {

    update_colors();
    update_brush_size_state();
    print_current_color();
    update_tool_state();

    for (std::size_t c = 0; c < NUMBER_OF_BUTTONS; c++) {
        for (std::size_t j = 0; j < menu_height; j++) {
            std::size_t beg_window_x = window_width - ((c + 1) * menu_height);
            for(std::size_t i = 0; i < menu_height; i++) {
                window_area[j * window_width + beg_window_x++] = menu_buttons_labels[c][j* 40 + i];
            }
        }
    }

}

void menu::update_colors() {
    /*calculating free space for colors buttons in menu*/
    std::size_t free_space = window_width - (NUMBER_OF_BUTTONS + NUMBER_OF_LEFT_ELEMENTS) * menu_height;

    if (free_space != 0) {
        /*calculating how many color can be printed*/
        colors_to_print = ((free_space / menu_height) < color_buffer.size()) ?
                        (free_space / menu_height) : color_buffer.size();


        for (std::size_t c = 0; c < color_buffer.size() && c < colors_to_print; c++) {
            std::size_t begin_point = window_width - menu_height * NUMBER_OF_BUTTONS - 1;
            std::size_t offset = menu_height * c;
            for (std::size_t i = begin_point - offset; i > begin_point - menu_height - offset; i--) {
                for (std::size_t j = 0; j <= menu_height; j++ ) {
                    if (j * window_width + i < menu_height * window_width)
                        window_area[j * window_width + i] = color_buffer.at(c);
                }
            }
        }
    }
    else {
        throw paint_exception(paint_exception::MENU_COLOR_SPACE);
    }
}



void menu::update_brush_size_state() {
    /*This loop sets brush szie state area background to white*/
    for (std::size_t j = 0; j < menu_height; j++) {
        for(std::size_t i = 0; i < menu_height; i++) {
            window_area[j * window_width + i] = 0xFFFFFFF;
        }
    }
        if (tool_prt->get_brush_size() != 0) {
        /*Printing square that represents size of the current tool*/
        std::size_t beg_x = menu_height / 2 - tool_prt->get_brush_size() / 2,
                    beg_y = menu_height / 2 - tool_prt->get_brush_size() / 2;

        for(std::size_t j = beg_y; j < beg_x + tool_prt->get_brush_size(); j++) {
            for(std::size_t i = beg_y; i < beg_y + tool_prt->get_brush_size(); i++) {
                window_area[j * window_width + i] = 0; //0 for color black
            }
        }
    }
    else {
        throw paint_exception(paint_exception::MENU_BRUSH_SIZE);
    }
}

void menu::update_tool_state() {
    tool_type current_tool_type = tool_prt->get_tool_type();
    if (tool_labels.size() >= current_tool_type) {
        for (std::size_t j = 0; j < menu_height; j++) {
            std::size_t k = 0;
            for (std::size_t i = menu_height * 2; i < menu_height * 3; i ++)  {
                window_area[j * window_width + i] = tool_labels.at(current_tool_type)[j * 40 + k++];
            }
        }
    }
    else {
        throw paint_exception(paint_exception::MENU_PRINT_TOOL_LABEL);
    }
}

void menu::add_color_to_queue(Uint32 color) {
    try {
        color_buffer.push_front(color);
        if (color_buffer.size() > COLOR_BUFFER_MAX_SIZE) {
            color_buffer.pop_back();
        }
    }
    catch (std::bad_alloc& exception) {
        throw paint_exception(paint_exception::MENU_BAD_ALLOC, exception.what());
    }
    update_colors();
}

void menu::print_current_color(){
    Uint32 current_color = tool_prt->get_current_color();

    for (std::size_t j = 0; j < menu_height; j++) {
        for (std::size_t i = menu_height; i < menu_height * 2; i++) {
            window_area[window_width * j + i] = current_color;
        }
    }
}

bool menu::is_in_color_menu(std::size_t x_position) {
    if (x_position > window_width) {
        throw paint_exception(paint_exception:: MENU_BAD_X_POSITION, "is_in_color_menu.");
    }
    std::size_t x_end = window_width - menu_height * NUMBER_OF_BUTTONS,
                x_beg = x_end - menu_height * colors_to_print;
    return (x_position > x_beg && x_position < x_end);
}



bool menu::is_in_buttons_area(std::size_t x_position) {
    if (x_position > window_width) {
        throw paint_exception(paint_exception:: MENU_BAD_X_POSITION, "is_in_buttons_area.");
    }
    std::size_t x_beg = window_width - menu_height * NUMBER_OF_BUTTONS;
    return ((x_position < window_width && x_position >= x_beg) ||
            (x_position > menu_height * 2 && x_position <= menu_height * 3));
}

enum menu_buttons menu::get_clicked_button(std::size_t x_position){
    if (x_position > window_width) {
        throw paint_exception(paint_exception:: MENU_BAD_X_POSITION, "get_clicked_button.");
    }
    enum menu_buttons choosed_button = (enum menu_buttons)-1;
    std::size_t x_current_possition = window_width;
    for (std::size_t i = 0; i < NUMBER_OF_BUTTONS; i++) {
        if (x_position < x_current_possition && x_position >= x_current_possition - menu_height) {
            choosed_button = (enum menu_buttons)i;
        }
        x_current_possition -= menu_height;
    }
    if (x_position > menu_height * 2 && x_position <= menu_height * 3) {
        choosed_button = TOOL_PROPERITES;
    }
    return choosed_button;
}



menu::~menu() {
    for(std::size_t i = 0; i < tool_labels.size(); i++) {
        delete[] tool_labels.at(i);
    }
    for(std::size_t i = 0; i < menu_buttons_labels.size(); i++) {
        delete[] menu_buttons_labels.at(i);
    }
}
