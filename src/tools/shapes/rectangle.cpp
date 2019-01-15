/** \file rectangle.cpp
 * \brief Plik z definicjami metod klasy rectangle.
*/

#include "rectangle.hpp"

rectangle::rectangle() {
    type = RECTANGLE;
}

void rectangle::draw_shape(std::size_t x_position, std::size_t y_position) {
    if (is_square) {
        int x_diff = x_position - x_begining,
            y_diff = y_position - y_begining;

        if (abs(x_diff) < abs(y_diff)) {
            y_position = y_begining + ((y_diff > 0) ? abs(x_diff) : -abs(x_diff));
        }
        else {
            x_position = x_begining + ((x_diff > 0) ? abs(y_diff) : -abs(y_diff));
        }
    }

    std::size_t tmp_x = x_begining,
                tmp_y = y_begining;
    line::draw_shape(x_position, y_begining);
    line::draw_shape(x_begining, y_position);
    x_begining = x_position;
    y_begining = y_position;
    line::draw_shape(tmp_x, y_position);
    line::draw_shape(x_position, tmp_y);

    x_begining = tmp_x;
    y_begining = tmp_y;
}

void rectangle::open_tool_properties() {
    GtkWidget *window        = gtk_window_new(GTK_WINDOW_TOPLEVEL),
              *window_box    = gtk_vbox_new(TRUE, 2),
              *label         = gtk_label_new("Rectangle tool properties: "),
              *square_button = gtk_check_button_new_with_label("Square shape");

    if (!window || !window_box || !label || !square_button) {
        throw paint_exception(paint_exception::GTK_WINDOW_INIT, "rectangle properties menu.");
		return;
    }

    gtk_window_set_title(GTK_WINDOW(window), "Properties");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), nullptr);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy), nullptr);


    if (is_square) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(square_button), TRUE);
    }
    else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(square_button), FALSE);
    }

    gtk_box_pack_start(GTK_BOX(window_box), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(window_box), square_button, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), window_box);

    g_signal_connect(square_button, "clicked", G_CALLBACK(this->set_square_flag), &(this->is_square));

    gtk_widget_show(window_box);
	gtk_widget_show(label);
    gtk_widget_show(square_button);
    gtk_widget_show(window);

    gtk_main();

}
