/** \file flood_fill.cpp
 * \brief Plik z definicjami metod klasy flood_fill.
*/

#include "flood_fill.hpp"

flood_fill::flood_fill() {
    type = FLOOD_FILL;
}

void flood_fill::use_tool(std::size_t x_position, std::size_t y_position) {
    if(window_area[y_position * window_width + x_position] == current_color) {
       // return; //ending procedure if there's no area to fill;
    }

    struct mouse_coordinates {
        std::size_t x,y;
    } top; //struct that holds coorinates to fill

    Uint32 pointed_color = window_area[y_position * window_width + x_position]; //getting color that will be replaced
    std::deque <struct mouse_coordinates> flood_queue;
    flood_queue.push_front({x_position, y_position});  //adding clicked point to queue

    while (!flood_queue.empty()) {

        top = flood_queue.front();
        flood_queue.pop_front();

        if (top.y >= menu_height && top.y < window_height && top.x < window_width && (int)top.x >=0 && (int)top.y >= 0 &&
            calculate_tolerance(pointed_color, window_area[top.y * window_width + top.x]) &&
            current_color != window_area[top.y * window_width + top.x]) {

            window_area[top.y * window_width + top.x] = current_color; //setting color to point
            flood_queue.push_front({top.x + 1, top.y});
            flood_queue.push_front({top.x, top.y + 1});
            flood_queue.push_front({top.x - 1, top.y});
            flood_queue.push_front({top.x, top.y - 1});
            flood_queue.push_front({top.x - 1, top.y - 1});
            flood_queue.push_front({top.x + 1, top.y + 1});
            flood_queue.push_front({top.x + 1, top.y - 1});
            flood_queue.push_front({top.x - 1, top.y + 1}); //adding neighboring points to queue
        }
    }
    pressed_left_button = false;
}

bool flood_fill::isBrush() {
    return false;
}



bool flood_fill::calculate_tolerance(Uint32 pointed_color, Uint32 replace_color) {

    return (abs((Uint8)pointed_color         - (Uint8)replace_color        ) <= tolerance_ratio &&   //blue
            abs((Uint8)(pointed_color >> 8)  - (Uint8)(replace_color >> 8) ) <= tolerance_ratio &&   //green
            abs((Uint8)(pointed_color >> 16) - (Uint8)(replace_color >> 16)) <= tolerance_ratio &&   //red
            abs((Uint8)(pointed_color >> 24) - (Uint8)(replace_color >> 24)) <= tolerance_ratio   ); // alpha
}



void flood_fill::open_tool_properties() {
    GtkWidget *window         = gtk_window_new(GTK_WINDOW_TOPLEVEL),
              *window_box     = gtk_vbox_new(TRUE, 3),
              *label          = gtk_label_new("Set tolerance for flood fill in percents:"),
              *ratio_button   = gtk_spin_button_new_with_range(0.0, 100.0, 1.0),
              *confirm_button = gtk_button_new_with_label("Ok");

    if (!window || !window_box || !label || !ratio_button || !confirm_button) {
        throw paint_exception(paint_exception::GTK_WINDOW_INIT, "flood fill properties menu.");
		return;
    }

    bool confirmed = false;
    int value_buffer = 100.0 * tolerance_ratio / 255.0;

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
        tolerance_ratio = 1 + value_buffer * 255 / 100;
    }

}
