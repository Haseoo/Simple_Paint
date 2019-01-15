/** \file spray.cpp
 * \brief Plik z definicjami metod klasy spray.
*/

#include "spray.hpp"

spray::spray() {
    type = SPRAY;
    std::chrono::high_resolution_clock::time_point beg_time = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::duration dur = std::chrono::high_resolution_clock::now() - beg_time;
    std::size_t seed = dur.count();
    generator.seed(seed);
}

void spray::PaintPixel(std::size_t x_position, std::size_t y_position) {
    x_position = x_position - brush_size / 2;
    y_position = (y_position - brush_size / 2 > 0) ? y_position - brush_size / 2 : 0;
    x_position = ((int)x_position < 0) ? 0 : x_position;

    std::size_t amount_of_dots = brush_size * brush_size * (dots_ratio / 100.0);
    std::uniform_int_distribution<std::size_t> x_distribution(x_position, x_position + brush_size);
    std::uniform_int_distribution<std::size_t> y_distribution(y_position, y_position + brush_size);

    for(std::size_t c = 0; c < amount_of_dots; c++) {
        std::size_t i = x_distribution(generator),
                    j = y_distribution(generator);
        if (i < window_width && j < window_height && j >= menu_height) {
                window_area[j * window_width + i] = current_color;
        }
    }
}



void spray::open_tool_properties() {
    GtkWidget *window         = gtk_window_new(GTK_WINDOW_TOPLEVEL),
              *window_box     = gtk_vbox_new(TRUE, 3),
              *label          = gtk_label_new("Set number of spray dots ratio: "),
              *ratio_button   = gtk_spin_button_new_with_range(0.0, 100.0, 1.0),
              *confirm_button = gtk_button_new_with_label("Ok");

    if (!window || !window_box || !label || !ratio_button || !confirm_button) {
        throw paint_exception(paint_exception::GTK_WINDOW_INIT, "spray properties menu.");
		return;
    }

    bool confirmed = false;
    int value_buffer = dots_ratio;

    gtk_window_set_title(GTK_WINDOW(window), "Properties");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), nullptr);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy), nullptr);

    g_signal_connect(confirm_button, "clicked", G_CALLBACK(this->set_confirmed_flag), &confirmed);
    g_signal_connect_swapped(confirm_button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    g_signal_connect(ratio_button, "value-changed", G_CALLBACK(this->value_changed), &value_buffer);

    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(ratio_button), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(ratio_button), dots_ratio);

    gtk_box_pack_start(GTK_BOX(window_box), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(window_box), ratio_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(window_box), confirm_button, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), window_box);


    gtk_widget_show(window_box);
	gtk_widget_show(label);
    gtk_widget_show(ratio_button);
    gtk_widget_show(confirm_button);
    gtk_widget_show(window);

    gtk_main();

    if (confirmed) {
        dots_ratio = value_buffer;
    }

}
