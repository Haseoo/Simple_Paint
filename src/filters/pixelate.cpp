/** \file pixelate.cpp
 * \brief Plik z definicjami metod klasy pixelate.
*/

#include "pixelate.hpp"

pixelate::pixelate() {
    type = PIXELATE;
}

void pixelate::do_filter() {

    std::size_t number_of_x_cells = ceil(window_width / (double)cell_size),
                number_of_y_cells = ceil((window_height - menu_height) / (double)cell_size),
                x_pixel_alignment = window_width  - (number_of_x_cells - 1) * cell_size,
                y_pixel_alignment = (window_height - menu_height) - (number_of_y_cells - 1) * cell_size;

    Uint32 *drawing_area = window_area + (menu_height * window_width);

    for(std::size_t j = 0; j < number_of_y_cells; j++) {
        for(std::size_t i = 0; i < number_of_x_cells; i++) {
            Uint32 R_sum = 0,
                   G_sum = 0,
                   B_sum = 0,
                   A_sum = 0;

            for(std::size_t l = j * cell_size; l < (j + 1) * cell_size && l < (window_height - menu_height); l++) {
                for(std::size_t k = i * cell_size; k < (i + 1) * cell_size && k < window_width; k++) {
                    /*Calculating sum of pixels in cell*/
                    B_sum += (Uint8)(drawing_area[l * window_width + k]);
                    G_sum += (Uint8)(drawing_area[l * window_width + k] >> 8);
                    R_sum += (Uint8)(drawing_area[l * window_width + k] >> 16);
                    A_sum += (Uint8)(drawing_area[l * window_width + k] >> 24);
                }
            }

            /*Calculating average of pixels in cell*/
            std::size_t x_cell_size = cell_size,
                        y_cell_size = cell_size;

            if (x_pixel_alignment && i > number_of_x_cells - 2) {
                x_cell_size = x_pixel_alignment;
            }
            if (y_pixel_alignment &&  j > number_of_y_cells - 2) {
                y_cell_size = y_pixel_alignment;
            }
            Uint32 tmp_R_avg = R_sum / (x_cell_size * y_cell_size),
                   tmp_G_avg = G_sum / (x_cell_size * y_cell_size),
                   tmp_B_avg = B_sum / (x_cell_size * y_cell_size),
                   tmp_A_avg = A_sum / (x_cell_size * y_cell_size);

            Uint8 R_avg = (tmp_R_avg > 255) ? 255 : tmp_R_avg,
                  G_avg = (tmp_R_avg > 255) ? 255 : tmp_G_avg,
                  B_avg = (tmp_R_avg > 255) ? 255 : tmp_B_avg,
                  A_avg = (tmp_R_avg > 255) ? 255 : tmp_A_avg;

            /*Setting all pixels in cell with average value*/
            for(std::size_t l = j * cell_size; l < (j + 1) * cell_size && l < (window_height - menu_height); l++) {
                for(std::size_t k = i * cell_size; k < (i + 1) * cell_size && k < window_width; k++) {
                    drawing_area[l * window_width + k] = (Uint32)(A_avg << 24) +
                                                         (Uint32)(R_avg << 16) +
                                                         (Uint32)(G_avg <<  8) +
                                                         (Uint32)(B_avg);
                }
            }
        }

    }

}

void pixelate::open_fiter_properties() {
GtkWidget *window         = gtk_window_new(GTK_WINDOW_TOPLEVEL),
              *window_box     = gtk_vbox_new(TRUE, 3),
              *label          = gtk_label_new("Set size of cell:"),
              *ratio_button   = gtk_spin_button_new_with_range(1.0, 15.0, 1.0),
              *confirm_button = gtk_button_new_with_label("Ok");

    if (!window || !window_box || !label || !ratio_button || !confirm_button) {
        throw paint_exception(paint_exception::GTK_WINDOW_INIT, "filter menu.");
		return;
    }

    bool confirmed = false;
    int value_buffer = 1;

    gtk_window_set_title(GTK_WINDOW(window), "Set cell size");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), nullptr);
	g_signal_connect(window, "destroy", G_CALLBACK(destroy), nullptr);

    g_signal_connect(confirm_button, "clicked", G_CALLBACK(this->set_confirmed_flag), &confirmed);
    g_signal_connect_swapped(confirm_button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    g_signal_connect(ratio_button, "value-changed", G_CALLBACK(this->value_changed), &value_buffer);

    gtk_spin_button_set_digits(GTK_SPIN_BUTTON(ratio_button), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(ratio_button), value_buffer);

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
        cell_size = value_buffer;
    }

}
