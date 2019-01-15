/** \file tool_menu.cpp
 * \brief Plik z definicjami metod klasy tool_menu.
*/

#include "tool_menu.hpp"

tool_menu::tool_menu() {
	std::fstream rc_file;
	rc_file.open(resource_file_path[0], std::ios::in);
	if (rc_file.is_open()) {
		std::size_t number_of_elements = (std::size_t)rc_file.get();
		if (rc_file.fail()) {
			throw paint_exception(paint_exception::GTK_WINDOW_RESOURCES, resource_file_path[0]);
			return;
		}
		number_of_tools = number_of_elements - 3;
		for(std::size_t i = 0; i < number_of_elements && !rc_file.eof(); i++) {
			std::string buffer;
			getline(rc_file, buffer, '\0');
			if (rc_file.fail()) {
				throw paint_exception(paint_exception::GTK_WINDOW_RESOURCES, resource_file_path[0]);
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
		throw paint_exception(paint_exception::GTK_WINDOW_RESOURCES, resource_file_path[0]);
		return;
	}

	for(std::size_t i = 0; i < number_of_tools; i++) {
		try {
			tool_types_array.push_back({(enum tool_type)i, &tool_response});
		}
		catch (std::bad_alloc& exception) {
            throw paint_exception(paint_exception::GTK_WINDOW_BAD_ALLOC, exception.what());
            return;
        }
	}
}



bool tool_menu::open_gtk_window() {
	GtkWidget *window,
			  *window_box,
			  *label;

	std::deque <GtkWidget *> buttons;

	try {
		buttons.resize(resource_strings.size() - 2);
	}
	catch (std::bad_alloc& exception) {
		throw paint_exception(paint_exception::GTK_WINDOW_BAD_ALLOC, exception.what());
        return false;
    }

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if (window == nullptr) {
		throw paint_exception(paint_exception::GTK_WINDOW_INIT, "tool menu.");
	}
	gtk_window_set_title(GTK_WINDOW(window), resource_strings.at(0).c_str());
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	label = gtk_label_new(resource_strings.at(1).c_str());

	for(std::size_t i = 0; i <  buttons.size(); i++) {
		buttons.at(i) = gtk_button_new_with_label(resource_strings.at(i + 2).c_str());
		if (buttons.at(i) == nullptr) {
			throw paint_exception(paint_exception::GTK_WINDOW_INIT, "tool menu.");
		}
	}


	window_box = gtk_vbox_new(TRUE, resource_strings.size() - 1);
	if (window_box == nullptr) {
		throw paint_exception(paint_exception::GTK_WINDOW_INIT, "tool menu.");
	}
	gtk_box_pack_start(GTK_BOX(window_box), label, TRUE, TRUE, 0);
	for(std::size_t i = 0; i < buttons.size(); i++) {
		gtk_box_pack_start(GTK_BOX(window_box), buttons.at(i), TRUE, TRUE, 0);
	}

	g_signal_connect(window, "delete-event", G_CALLBACK(this->delete_event), nullptr);
	g_signal_connect(window, "destroy", G_CALLBACK(this->destroy), nullptr);

	for(std::size_t i = 0; i < buttons.size() - 1; i++) {
		g_signal_connect(buttons.at(i), "clicked", G_CALLBACK(this->get_tool_type), &(tool_types_array.at(i)));
		g_signal_connect_swapped(buttons[i], "clicked", G_CALLBACK(gtk_widget_destroy), window);
	}
	g_signal_connect(buttons.at(buttons.size() - 1), "clicked", G_CALLBACK(this->trigger_color_chooser), (this->RGB));
	g_signal_connect_swapped(buttons.at(buttons.size() - 1), "clicked", G_CALLBACK(gtk_widget_destroy), window);

	gtk_container_add(GTK_CONTAINER(window), window_box);

	gtk_widget_show(window_box);
	gtk_widget_show(label);
	for(std::size_t i = 0; i < buttons.size(); i++) {
		gtk_widget_show(buttons.at(i));
	}
	gtk_widget_show(window);
	gtk_main();

	new_color = (Uint32)(RGB[0] << 16) + (Uint32)(RGB[1] << 8) + (Uint32)RGB[2];

	return true;
}



void tool_menu::set_current_color(Uint32 current_color) {
    RGB[2] = (Uint8)current_color;
    RGB[1] = (Uint8)(current_color >> 8);
    RGB[0] = (Uint8)(current_color >> 16);

}

void tool_menu::set_current_tool(enum tool_type curent_tool) {
	this->tool_response = curent_tool;
}

Uint32 tool_menu::get_color_response() {
	return new_color;
}

enum tool_type tool_menu::get_tool_response() {
	return tool_response;
}


tool_menu::~tool_menu() {

}
