/** \file ellipse.cpp
 * \brief Plik z definicjami metod klasy ellipse.
*/

#include "ellipse.hpp"


ellipse::ellipse() {
    type = ELLIPSE;
}

void ellipse::PaintPixel(std::size_t x_position, std::size_t y_position) {
    x_position = x_position - brush_size / 2;
    y_position = (y_position - brush_size / 2 > 0) ? y_position - brush_size / 2 : 0;
    std::size_t x_end = brush_size + (int)x_position;
    x_position = ((int)x_position < 0) ? 0 : x_position;

    std::size_t thickness = (brush_size / 2) - 1;
    std::size_t free_space = (brush_size - thickness) / 2;

    for(std::size_t i = x_position + free_space; i <= x_position + free_space + thickness; i++) {
        for(std::size_t j = y_position; j <= y_position + brush_size; j++) {
            if (i < window_width && j < window_height && j >= menu_height) {
                window_area[j * window_width + i] = current_color;
            }
        }
    }

    for(std::size_t i = x_position; i < x_end; i++) {
        for(std::size_t j = y_position + free_space; j <= y_position + free_space + thickness; j++) {
            if (i < window_width && j < window_height && j >= menu_height) {
                window_area[j * window_width + i] = current_color;
            }
        }
    }
}

void ellipse::draw_shape(std::size_t x_position, std::size_t y_position) {
    int a_axis = abs((int)(x_begining - x_position)),
        b_axis = abs((int)(y_begining - y_position)),
        radius = (int)sqrt(pow((signed)x_position - (signed)x_begining, 2) +
                 pow((signed)y_position - (signed)y_begining, 2));

    for (double alpha = 0; alpha <= (double)(2 * M_PI); alpha += 1 / (double)radius) {
            size_t paint_x = x_begining + (size_t)(((is_circle) ? radius : a_axis) * cos(alpha));
            size_t paint_y = y_begining + (size_t)(((is_circle) ? radius : b_axis) * sin(alpha));
            if ((signed)(paint_x - brush_size / 2) >= 0 && (signed)(paint_y - brush_size / 2) >= 0)
                PaintPixel(paint_x, paint_y);

        }
}

void ellipse::open_tool_properties() {
    GtkWidget *window        = gtk_window_new(GTK_WINDOW_TOPLEVEL),
              *window_box    = gtk_vbox_new(TRUE, 2),
              *label         = gtk_label_new("ellipse tool properties: "),
              *circle_button = gtk_check_button_new_with_label("Circle shape");

    if (!window || !window_box || !label || !circle_button) {
        throw paint_exception(paint_exception::GTK_WINDOW_INIT, "ellipse properties menu.");
		return;
    }

    gtk_window_set_title(GTK_WINDOW(window), "Properties");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), nullptr);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy), nullptr);


    if (is_circle) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(circle_button), TRUE);
    }
    else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(circle_button), FALSE);
    }

    gtk_box_pack_start(GTK_BOX(window_box), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(window_box), circle_button, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), window_box);

    g_signal_connect(circle_button, "clicked", G_CALLBACK(this->set_cicle_flag), &(this->is_circle));

    gtk_widget_show(window_box);
	gtk_widget_show(label);
    gtk_widget_show(circle_button);
    gtk_widget_show(window);

    gtk_main();

}
