/** \file gtk_base_window.hpp
 * \brief Plik definicję klasy gtk_base_window.
 */

#ifndef GTK_BASE_WINDOW_H
#define GTK_BASE_WINDOW_H

#include <gtk/gtk.h>
#include <fstream>
#include <string>
#include <deque>

#include "paint_exception.hpp"

/** \brief Klasa bazowa dla okien używających biblioteki GTK.
 */
class gtk_base_window {
    public:
         /** \brief Metoda zawiera inicjuje menu oraz zawiera pętlę main GTK. Metoda nie przyjmuje żadnych argumentów wywołania.
         *
         * \return bool Funkcja zwraca wartość true jeśli nie wystąpił w niej krytyczny błąd.
         */
        virtual bool open_gtk_window() = 0;

        /** \brief Destruktor klasy.
         *
         */
        virtual ~gtk_base_window() {

        }
    protected:
        std::string resource_file_path[3] = {
                                             "assets/resources/tool_menu.rc",
                                             "assets/resources/file_manager.rc",
                                             "assets/resources/filter_menu.rc"
        }; /**< Tablica zawiera ścieżki do plików z zasobami różnych menu. */
        std::deque<std::string> resource_strings; /**< Kolejka z ciągami znaków wykorzystywanych w menu. */

        bool failed_to_load_resources; /**< Flaga informująca o błędzie załadowania zasobów okna menu. */

        /** \brief Funkcja obsługująca sygnał usunięcia okna GTK.
         *
         * \param widget GtkWidget* Wskaźnik na okno z którego pochodził sygnał.
         * \param event GdkEvent* Zdarzenie.
         * \param data gpointer Dane dla funkcji.
         * \return gboolean Funkcja zwraca wartość TRUE.
         *
         */
        static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
            return FALSE;
        }

        /** \brief Funkcja obsługująca sygnał zamknięcia okna, nie zwraca żadnej wartości.
         *
         * \param widget GtkWidget* Wskaźnik na okno z którego pochodził sygnał.
         * \param data gpointer Dane dla funkcji.
         *
         */
        static void destroy(GtkWidget *widget, gpointer data) {
            gtk_main_quit();
        }

};


#endif
