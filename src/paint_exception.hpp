/** \file paint_exception.hpp
 * \brief Plik z definicją klasy paint_exception.
*/
#ifndef PAINT_EXCEPTION_H
#define PAINT_EXCEPTION_H

#include <string>

/** \brief Klasa do obsługi wyjątków programu.
 */
class paint_exception
{
    public:
        /** \brief Typ wyliczeniowy służący do obsługi wyjątków w programie.
         */
        enum exception_type {
                             WINDOW_BAD_ALLOC,                   /**< Błąd alokowania pamięci w obiekcie klasy window. */
                             WINDOW_UPDATING_DATA,               /**< Błąd aktualizowania danych między obiektami programu. */
                             WINDOW_PIXELS_SWAP,                 /**< Błąd podmieniania tablicy pikseli. */
                             WINDOW_SDL_INIT,                    /**< Błąd inicjowania okna SDL2. */
                             WINDOW_SDL_RENDER,                  /**< Błąd podczas renderowania okna. */
                             WINDOW_SDL_RESIZED,                 /**< Błąd podczas zmiany rozmiaru okna. */
                             WINDOW_SDL_DIALOG,                  /**< Błąd otwarcia okna dialogowego SDL2. */
                             BAD_WINDOW_DIM,                     /**< Podano błędne rozmiary okna. */
                             BAD_WINDOW_PTR,                     /**< Podano błędy wskaźnik na okno. */
                             BAD_TOOL_PTR,                       /**< Podano błędy wskaźnik na narzędzie. */
                             MENU_BAD_ALLOC,                     /**< Błąd alokowania pamieci w obiekcie klasy menu. */
                             MENU_RESOURCES,                     /**< Błąd otwarcia/odczytu pliku z zasobami klasy menu. */
                             MENU_NUMBER_OF_BUTTONS,             /**< Liczba przycisków równa zero. */
                             MENU_BUTTON_LABLES_PATH,            /**< Błąd otwarcia/odczytu pliku ze ścieżkami do etykiet przycisków. */
                             MENU_TOOL_LABELS_PATH,              /**< Błąd otwarcia/odczytu pliku ze ścieżkami do etykiet narzędzi. */
                             MENU_BUTTON_LABEL,                  /**< Błąd otwarcia/odczytu pliku z etykietą przycisku. */
                             MENU_TOOL_LABEL,                    /**< Błąd otwarcia/odczytu pliku z etykietą narzędzia. */
                             MENU_COLOR_SPACE,                   /**< Brak miejsca na rysowanie kolorów z kolejki. */
                             MENU_BRUSH_SIZE,                    /**< Próba narysowania stanu narzędzia o rozmiarze równym zero. */
                             MENU_PRINT_TOOL_LABEL,              /**< Błąd podczas rysowania etykiety narzędzia. */
                             MENU_BAD_X_POSITION,                /**< Podano współrzędną X większą niż rozmiar okna. */
                             GTK_WINDOW_RESOURCES,               /**< Błąd podczas otwierania/odczytu pliku zasobów klasy. */
                             GTK_WINDOW_BAD_ALLOC,               /**< Błąd alokacji pamięci w obiekcie obsługującym okno GTK. */
                             GTK_WINDOW_INIT,                    /**< Błąd podczas inicjowania okna GTK. */
                             UNSUPPORTED_IMAGE_FILE,             /**< Niewspierany typ obrazu. */
                             IMAGE_FILE_ERROR,                   /**< Błąd odczytu obrazu. */
                             IMAGE_CONTAINTER_PIXEL_ARRAY,       /**< Docelowa tablica pikseli nie została zainicjowana. */
                             IMAGE_CONTAINER_BAD_RBGA8888_PIXBUF,/**< Podano wskaźnik o wartości NULL na tablicę źródłową pikseli. */
                             IMAGE_CONTAINER_OPERATOR,           /**< Przekroczono zakres tablicy pikseli przy używaniu operatora[] */
                             IMAGE_CONTAINER_BAD_ALLOC,          /**< Błąd alokowania tablicy w klasie image_container. */
                             IMAGE_CONTAINER_BAD_PPM,            /**< Próba otwarcia pliku PPM o niespodziewanej strukturze. */
                             IMAGE_CONTAINER_BAD_BMP,            /**< Próba otwarcia pliku BMP o niespodziewanej strukturze. */
                             IMAGE_CONTAINER_BAD_PNG,            /**< Próba otwarcia pliku PNG o niespodziewanej strukturze. */
                             SHAPE_BAD_ALLOC,                    /**< Błąd alokowania pamięci podczas rysowania figury geometrycznej. */
                     };
        /** \brief Konstruktor klasy. Tworzy komunikat wyjątku na podstawie tylko jego kodu.
         *
         * \param[in] exception_type enum Kod wyjątku.
         *
         */
        paint_exception(enum exception_type);

        /** \brief Konstruktor klasy. Tworzy komunikat wyjątku na podstawie  jego kodu oraz dodatkowych danych typu std::string.
         *
         * \param[in] exception_type enum Kod wyjątku.
         * \param[in] additional_data std::string Dodatkowe informacje.
         *
         */
        paint_exception(enum exception_type, std::string additional_data);

        /** \brief Konstruktor klasy. Tworzy komunikat wyjątku na podstawie  jego kodu oraz dodatkowych danych typu const char*.
         *
         * \param exception_type enum Kod wyjątku.
         * \param additional_data const char* Dodatkowe informacje
         *
         */
        paint_exception(enum exception_type, const char* additional_data);

        /** \brief Metoda zwraca komunikat wyjątku w zmiennej typu std::string. Nie przyjmuje argumentów wywołania.
         *
         * \return std::string Komunikat wyjątku.
         *
         */
        std::string what();

        /** \brief Destruktor klasy.
         *
         */
        virtual ~paint_exception();

    private:
        const static std::size_t number_of_exceptions = 34; /**< Liczba wyjątków w programie */
        std::string exception_string = " "; /**< Komunikat wyjątku. */
        std::string exception_strings[number_of_exceptions] = { "Failed to allocate memory in window object.",
                                                                "Failed to update information in: ",
                                                                "Undo facility will not work due to an error: ",
                                                                "SDL Window could not initialize! SDL_Error: ",
                                                                "Render failed! SDL_Error: ",
                                                                "Resize failed due to: ",
                                                                "Opening SDL2 dialog failed. ",
                                                                "Trying to point invalid window dimensions to: ",
                                                                "Trying to point null window pointer to: ",
                                                                "Trying to point null tool pointer to: ",
                                                                "Failed to allocate memory in menu object.",
                                                                "Failed to open/read resource file: assets/resources/menu.rc",
                                                                "Number of menu buttons couldn't be 0.",
                                                                "Failed to load menu buttons labels paths form resources file.",
                                                                "Failed to load tool labels paths form resources file.",
                                                                "Failed to load menu button label form file: ",
                                                                "Failed to load tool label form file: ",
                                                                "There's no space in menu for colors form color buffer to print",
                                                                "Trying to print brush size which is 0.",
                                                                "Trying to print tool label for tool with unexpected type.",
                                                                "Pointed to position outside window in method: ",
                                                                "Failed to open/read resource file: ",
                                                                "Failed to allocate memory in one of the GTK menu object.",
                                                                "Failed to initialize GTK menu: ",
                                                                "Unsupported file type. ",
                                                                "Failed to open/read image file: ",
                                                                "Trying to fill uninitialized pixel array.",
                                                                "Trying to fill pixel with null pointer pixbuf array.",
                                                                "Image container operator[] out of range!",
                                                                "Failed to allocate memory in image container object: ",
                                                                "Unsupported pixmap. ",
                                                                "Unsupported bmp file. ",
                                                                " ",
                                                                "Failed to use this tool because of: "
                                                              }; /**< Tablica komunikatów wyjątków. */
};

#endif // PAINT_EXCEPTION_H
