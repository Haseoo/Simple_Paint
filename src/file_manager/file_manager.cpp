/** \file file_manager.cpp
 * \brief Plik z definicjami metod klasy file_manager.
*/

#include "file_manager.hpp"

file_manager::file_manager() {
    std::fstream rc_file;
	rc_file.open(resource_file_path[1], std::ios::in);
    if (rc_file.is_open()) {
		std::size_t number_of_elements = (std::size_t)rc_file.get();
		if (rc_file.fail()) {
			throw paint_exception(paint_exception::GTK_WINDOW_RESOURCES, resource_file_path[1]);
			return;
		}
		for(std::size_t i = 0; i < number_of_elements && !rc_file.eof(); i++) {
			std::string buffer;
			getline(rc_file, buffer, '\0');
			if (rc_file.fail()) {
				throw paint_exception(paint_exception::GTK_WINDOW_RESOURCES, resource_file_path[1]);
				return;
			}
			try {
				resource_strings.push_back(buffer);
			}
			catch (std::bad_alloc& exception) {
                throw paint_exception(paint_exception::GTK_WINDOW_BAD_ALLOC, exception.what());
                return;
            }

		}
	}
	else {
		throw paint_exception(paint_exception::GTK_WINDOW_RESOURCES, resource_file_path[1]);
		return;
	}
}



void file_manager::update_file_manager_information(Uint32 *window, std::size_t window_width, std::size_t window_height, std::size_t menu_height) {
    if (window)
        this->window_area = window;
    else
        throw paint_exception(paint_exception::BAD_WINDOW_PTR, "file manager.");

    if (menu_height >= 40 && window_width >= 400 && window_height >= 200) {
        this->menu_height = menu_height;
        this->window_width = window_width;
        this->window_height = window_height;
    }
    else {
        throw paint_exception(paint_exception::BAD_WINDOW_DIM, "file manager.");
    }
}



enum file_manager_mode file_manager::get_file_manager_mode() {
    return current_mode;
}

std::string file_manager::get_file_path() {
    return file_path;
}



void file_manager::get_image_dimentions(std::size_t &width, std::size_t &height) {
    width = image->get_image_info().width;
    height = image->get_image_info().height;
}


void file_manager::load_image() {
    try {
        switch (current_file_type) {
            case image_container::PPM_FILE:
                image = new ppm_image_container(file_path);
                break;

            case image_container::BMP_FILE:
                image = new bmp_image_container(file_path);
                break;

            case image_container::PNG_FILE:
                image = new png_image_container(file_path);
                break;

            default:
                throw paint_exception(paint_exception::UNSUPPORTED_IMAGE_FILE);
        }
    }
    catch(std::bad_alloc& exception) {
        throw paint_exception(paint_exception::GTK_WINDOW_BAD_ALLOC, exception.what());
    }
}

void file_manager::load_image(std::string file_path) {
    this->file_path         = file_path;
    this->current_file_type = image_container::get_file_type(file_path);

    switch (current_file_type) {
        case image_container::PPM_FILE:
            image = new ppm_image_container(file_path);
            break;

        case image_container::BMP_FILE:
            image = new bmp_image_container(file_path);
            break;

        case image_container::PNG_FILE:
            image = new png_image_container(file_path);
            break;

        default:
            throw paint_exception(paint_exception::UNSUPPORTED_IMAGE_FILE);
    }
}

void file_manager::print_image() {
    for(std::size_t j = 0; j < image->get_image_info().height; j++) {
        for(std::size_t i = 0; i < image->get_image_info().width; i++) {
            window_area[(j + menu_height) * window_width + i] = (*image)[j * image->get_image_info().width + i];
        }
    }

    delete image;
    working_on_file = true;
}

void file_manager::save_window_to_image() {
    switch (current_file_type) {
        case image_container::PPM_FILE:
            image = new ppm_image_container(window_width, window_height - menu_height, 3);
            break;

        case image_container::BMP_FILE:
            image = new bmp_image_container(window_width, window_height - menu_height, 4);
            break;

        case image_container::PNG_FILE:
            image = new png_image_container(window_width, window_height - menu_height, 4);
            break;

        default:
            throw paint_exception(paint_exception::UNSUPPORTED_IMAGE_FILE, "While saving file.");
            return;
    }

    image->set_pixels_form_array(window_area + (menu_height * window_width));
    image->save_to_file(file_path);
    delete image;

    working_on_file = true;
}



void file_manager::reset_state() {
    working_on_file = false;
    current_mode = NONE;
    file_path = "";
}



bool file_manager::open_gtk_window() {
    GtkWidget *window      = gtk_window_new(GTK_WINDOW_TOPLEVEL),
			  *window_box  = gtk_vbox_new(TRUE, 4),
			  *label       = gtk_label_new(resource_strings.at(1).c_str()),
              *open_button = gtk_button_new_with_label(resource_strings.at(2).c_str()),
              *save_button = gtk_button_new_with_label(resource_strings.at(3).c_str()),
              *q_sv_button = gtk_button_new_with_label(resource_strings.at(4).c_str());

    current_mode = NONE;
    std::string buffer[2];

    if (!window || !window_box || !label || !open_button || !save_button || !q_sv_button) {
        throw paint_exception(paint_exception::GTK_WINDOW_INIT, "file manager menu.");
		return false;
    }

    gtk_window_set_title(GTK_WINDOW(window), resource_strings.at(0).c_str());
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), nullptr);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy), nullptr);

    g_signal_connect(open_button, "clicked", G_CALLBACK(this->open_open_file_widget), &buffer);
    g_signal_connect_swapped(open_button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    g_signal_connect(save_button, "clicked", G_CALLBACK(this->open_save_file_widget), &buffer);
    g_signal_connect_swapped(save_button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    g_signal_connect(q_sv_button, "clicked", G_CALLBACK(this->quick_save_button_clicked), &buffer);
    g_signal_connect_swapped(q_sv_button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    gtk_box_pack_start(GTK_BOX(window_box), label, TRUE, TRUE, 0);
    if (working_on_file) {
        gtk_box_pack_start(GTK_BOX(window_box), q_sv_button, TRUE, TRUE, 0);
    }
    gtk_box_pack_start(GTK_BOX(window_box), open_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(window_box), save_button, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), window_box);

    gtk_widget_show(window_box);
    gtk_widget_show(label);
    if (working_on_file) {
        gtk_widget_show(q_sv_button);
    }
    gtk_widget_show(open_button);
    gtk_widget_show(save_button);
    gtk_widget_show(window);

    gtk_main();

    if (buffer[1] == "Open file") {
        file_path = buffer[0];
        current_mode = OPEN_FILE;
        current_file_type = image_container::get_file_type(file_path);
        if (current_file_type == image_container::UNSUPPORTED) {
            throw paint_exception(paint_exception::UNSUPPORTED_IMAGE_FILE, "Unsupported file type.\nProgram supports only .bmp, .ppm and .jpg files.");
        }
    }
    else if (buffer[1] == "Save file") {
        file_path = buffer[0];
        current_mode = SAVE_FILE;
        if (file_path.find(".ppm") != std::string::npos) {
            current_file_type = image_container::PPM_FILE;
        }
        else if (file_path.find(".bmp") != std::string::npos) {
            current_file_type = image_container::BMP_FILE;
        }
        else if (file_path.find(".png") != std::string::npos) {
            current_file_type = image_container::PNG_FILE;
        }
        else {
            current_file_type = image_container::UNSUPPORTED;
            throw paint_exception(paint_exception::UNSUPPORTED_IMAGE_FILE, "Unsupported file type.\nProgram supports only .bmp, .ppm and .png files.");
        }
    }
    else if (buffer[1] == "Quick save file") {
        current_mode = QUICK_SAVE;
    }

    return true;

}



file_manager::~file_manager() {

}
