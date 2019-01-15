/** \file filter_menu.cpp
 * \brief Plik z definicjami metod klasy filter_menu.
*/
#include "filter_menu.hpp"

filter_menu::filter_menu() {
    std::fstream rc_file;
	rc_file.open(resource_file_path[2], std::ios::in);
	if (rc_file.is_open()) {
		std::size_t number_of_elements = (std::size_t)rc_file.get();
		if (rc_file.fail()) {
			throw paint_exception(paint_exception::GTK_WINDOW_RESOURCES, resource_file_path[2]);
			return;
		}
		number_of_filters = number_of_elements - 2;
		for(std::size_t i = 0; i < number_of_elements && !rc_file.eof(); i++) {
			std::string buffer;
			getline(rc_file, buffer, '\0');
			if (rc_file.fail()) {
				throw paint_exception(paint_exception::GTK_WINDOW_RESOURCES, resource_file_path[2]);
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
		throw paint_exception(paint_exception::GTK_WINDOW_RESOURCES, resource_file_path[2]);
		return;
	}

    for(std::size_t i = 0; i < number_of_filters; i++) {
		try {
			filter_types.push_back({(enum filter_type)i, &filter_response});
		}
		catch (std::bad_alloc& exception) {
            throw paint_exception(paint_exception::GTK_WINDOW_BAD_ALLOC, exception.what());
            return;
        }
	}

}

bool filter_menu::open_gtk_window() {
    GtkWidget *window,
			  *window_box,
			  *label;

	std::deque <GtkWidget *> buttons;

	filter_response = NONE_FILTER;

	try {
		buttons.resize(number_of_filters);
	}
	catch (std::bad_alloc& exception) {
        throw paint_exception(paint_exception::GTK_WINDOW_BAD_ALLOC, exception.what());
        return false;
    }

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if (window == nullptr) {
		throw paint_exception(paint_exception::GTK_WINDOW_INIT, "filter menu.");
	}
	gtk_window_set_title(GTK_WINDOW(window), resource_strings.at(0).c_str());
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    label = gtk_label_new(resource_strings.at(1).c_str());

    for(std::size_t i = 0; i <  buttons.size(); i++) {
		buttons.at(i) = gtk_button_new_with_label(resource_strings.at(i + 2).c_str());
		if (buttons.at(i) == nullptr) {
			 throw paint_exception(paint_exception::GTK_WINDOW_INIT, "filter menu.");
		}
	}

    window_box = gtk_vbox_new(TRUE, number_of_filters);
	if (window_box == nullptr) {
		throw paint_exception(paint_exception::GTK_WINDOW_INIT, "filter menu.");
	}
	gtk_box_pack_start(GTK_BOX(window_box), label, TRUE, TRUE, 0);
	for(std::size_t i = 0; i < buttons.size(); i++) {
		gtk_box_pack_start(GTK_BOX(window_box), buttons.at(i), TRUE, TRUE, 0);
	}

	g_signal_connect(window, "delete-event", G_CALLBACK(this->delete_event), nullptr);
	g_signal_connect(window, "destroy", G_CALLBACK(this->destroy), nullptr);

    for(std::size_t i = 0; i < number_of_filters; i++) {
		g_signal_connect(buttons.at(i), "clicked", G_CALLBACK(this->get_filter_type), &(filter_types.at(i)));
		g_signal_connect_swapped(buttons[i], "clicked", G_CALLBACK(gtk_widget_destroy), window);
	}

	gtk_container_add(GTK_CONTAINER(window), window_box);

    gtk_widget_show(window_box);
	gtk_widget_show(label);
	for(std::size_t i = 0; i < buttons.size(); i++) {
		gtk_widget_show(buttons.at(i));
	}
	gtk_widget_show(window);
	gtk_main();

    return true;
}

enum filter_type filter_menu::get_filter_response() {
    return filter_response;
}
