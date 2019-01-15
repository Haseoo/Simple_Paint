/** \file file_manager.hpp
 * \brief Plik definicję klasy file_manager oraz typu wyliczeniowego file_manager_mode.
 */

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../base_window.hpp"
#include "../gtk_base_window.hpp"
#include "image_container/image_container.hpp"
#include "image_container/bmp_image_container.hpp"
#include "image_container/ppm_image_container.hpp"
#include "image_container/png_image_container.hpp"

/** \brief Typ wyliczeniowy pozwalający określić tryb pracy managera plików.
 */
enum file_manager_mode {OPEN_FILE, /**< Otwieranie plików. */
                        SAVE_FILE, /**< Zapis plików. */
                        QUICK_SAVE,/**< Szybki zapis. */
                        NONE       /**< Nie podejmuj akcji. */
                        };

/** \brief Klasa mangera plików.
 */
class file_manager : public base_window, public gtk_base_window {
    public:
        /** \brief Konstruktor klasy. Odczytuje informacje z pliku zasobów. Może "rzucić" wyjątek typu  paint_exception w przypadku błędu.
         *
         */
        file_manager();

        /** \brief Metoda przekazuje do klasy informacje na temat okna programu. Metoda nie zwraca żadnej wartości.
         *
         * \param[in] window Uint32* Wskaźnik na tablicę pikseli okna programu.
         * \param[in] window_width std::size_t Szerokość okna.
         * \param[in] window_height std::size_t Wysokość okna.
         * \param[in] menu_height std::size_t Wysokość menu okna.
         *
         */
        void update_file_manager_information(Uint32 *window, std::size_t window_width, std::size_t window_height, std::size_t menu_height);

        /** \brief Getter aktualnego trybu pracy managera plików.
         *
         * \return enum file_manager_mode Tryb pracy managera plików.
         */
        enum file_manager_mode get_file_manager_mode();

        /** \brief Getter ścieżki aktualnie obsługiwanego pliku.
         *
         * \return std::string ścieżka do pliku.
         *
         */
        std::string get_file_path();

        /** \brief Getter (poprzez wyjściowe argumenty wywołania) wymiarów aktualnie obsługiwanego obrazu.
         * Metoda nie zwraca żadnej wartości.
         *
         * \param[out] width std::size_t& Szerokość obrazu.
         * \param[out] height std::size_t& Wysokość obrazu.
         *
         */
        void get_image_dimentions(std::size_t &width, std::size_t &height);

        /** \brief Metoda wczytuje obraz z pliku, przy pomocy klasy image_container. Nie zwraca żadnej wartości i  nie przyjmuje argumentów wywołania.
         *
         */
        void load_image();

        /** \brief Metoda wczytuje obraz z pliku (do którego ścieżka została podana jako agument wywołania), przy pomocy klasy image_container.
         * Wykorzystywana przy upuszczaniu plików na okno. Metoda nie zwraca żadnej wartości.
         *
         * \param[in] file_path std::string ścieżka do pliku
         *
         */
        void load_image(std::string file_path);

        /** \brief Metoda rysuje na wczytany obraz w obszarze roboczym okna programu. Nie zwraca żadnej wartości i  nie przyjmuje argumentów wywołania.
         *
         */
        void print_image();

        /** \brief Metoda zapisuje obszar roboczy okna programu do pliku. Nie zwraca żadnej wartości i  nie przyjmuje argumentów wywołania.
         *
         */
        void save_window_to_image();

        /** \brief Metoda resetuje stan managera plików.
         *
         */
        void reset_state();

        /** \brief Metoda zawiera inicjuje menu managera plików oraz zawiera pętlę main GTK. Metoda nie przyjmuje żadnych argumentów wywołania.
         * Metoda może "rzucić" wyjątek typu paint_exception gdy operacja inicjacji menu się nie powiedzie.
         *
         * \return bool Funkcja zwraca wartość true jeśli nie wystąpił w niej krytyczny błąd.
         *
         */
        bool open_gtk_window();

        /** \brief Destruktor klasy.
         *
         */
        ~file_manager();

    private:
        image_container *image = nullptr; /**< Wskaźnik na kontener obrazu. */
        std::string file_path;            /**< Ścieżka do pliku. */

        bool working_on_file = false; /**< Flaga informująca o tym, że został otwarty/zapisany plik. */

        enum file_manager_mode current_mode = NONE; /**< Tryb pracy managera plików */
        image_container::file_type current_file_type = image_container::UNSUPPORTED; /**< Typ obrazu, na którym są wykonywanie operacje.*/


        /** \brief Metoda otwiera okno dialogowe GTK zapisu plików. Nie zwraca żadnej wartości.
         *
         * \param[out] widget GtkWidget* okno GTK z którego zostało wywołane  okno dialogowe.
         * \param[out] data gpointer dodatkowe dane. W tym przypadku wskaźnik na 2 elementową tablicę std::string.
         *
         */
        static void open_save_file_widget(GtkWidget *widget, gpointer data) {
            GtkWidget *dialog;
            GtkFileChooser *chooser;
            GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;

            dialog = gtk_file_chooser_dialog_new("Open file", nullptr, action, "Cancel", GTK_RESPONSE_CANCEL,
                                                 "Save", GTK_RESPONSE_ACCEPT, nullptr);

            chooser = GTK_FILE_CHOOSER(dialog);

            gtk_file_chooser_set_current_name(chooser, "Untitled.ppm");

            gint response = gtk_dialog_run(GTK_DIALOG(dialog));

            if (response == GTK_RESPONSE_ACCEPT) {
                char *path_buffer =  gtk_file_chooser_get_filename(chooser);
                (reinterpret_cast<std::string*>(data))[0] = path_buffer;
                (reinterpret_cast<std::string*>(data))[1] = "Save file";
                g_free(path_buffer);
            }

            gtk_widget_destroy(dialog);

        }

        /** \brief Metoda otwiera okno dialogowe GTK odczytu plików. Nie zwraca żadnej wartości.
         *
         * \param[out] widget GtkWidget* okno GTK z którego zostało wywołane  okno dialogowe.
         * \param[out] data gpointer dodatkowe dane. W tym przypadku wskaźnik na 2 elementową tablicę std::string.
         *
         */
        static void open_open_file_widget(GtkWidget *widget, gpointer data) {
            GtkWidget *dialog;
            GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
            gint response;

            dialog = gtk_file_chooser_dialog_new("Open file", nullptr, action, "Cancel",
                                                 GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, nullptr);

            GtkFileFilter *filter = gtk_file_filter_new();
            gtk_file_filter_set_name(filter, "Portable Pixmap .ppm");
            gtk_file_filter_add_pattern(filter, "*.ppm");
            gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

            GtkFileFilter *filter2 = gtk_file_filter_new();
            gtk_file_filter_set_name(filter2, "Windows Bitmap .bmp");
            gtk_file_filter_add_pattern(filter2, "*.bmp");
            gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter2);

            GtkFileFilter *filter3 = gtk_file_filter_new();
            gtk_file_filter_set_name(filter3, "Joint Photographic Experts Group .jpg");
            gtk_file_filter_add_pattern(filter3, "*.jpg");
            gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter3);

            response = gtk_dialog_run(GTK_DIALOG(dialog));

            if (response == GTK_RESPONSE_ACCEPT) {
                GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
                char *path_buffer =  gtk_file_chooser_get_filename(chooser);
                (reinterpret_cast<std::string*>(data))[0] = path_buffer;
                (reinterpret_cast<std::string*>(data))[1] = "Open file";
                g_free(path_buffer);
            }

            gtk_widget_destroy(dialog);

        }

        /** \brief Metoda odpowiada za obsługę sygnału kliknięcia na przycisk szybkiego zapisu. Nie zwraca żadnej wartości.
         *
         * \param[out] widget GtkWidget* okno GTK z którego zostało wywołane  okno dialogowe.
         * \param[out] data gpointer dodatkowe dane. W tym przypadku wskaźnik na 2 elementową tablicę std::string.
         *
         */
        static void quick_save_button_clicked(GtkWidget *widget, gpointer data) {
            (reinterpret_cast<std::string*>(data))[1] = "Quick save file";

        }

};

#endif
