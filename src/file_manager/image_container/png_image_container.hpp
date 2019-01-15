/** \file png_image_container.hpp
 * \brief Plik definicję klasy ppm_image_container.
 */#ifndef PNG_IMAGE_CONTAINER
#define PNG_IMAGE_CONTAINER

#include "image_container.hpp"
#include <png++/png.hpp>

/** \brief Kontener dla plików png.
 */
class png_image_container : public image_container
{
    public:

        /*Constructors*/
        /** \brief Konstruktor. Inicjuje kontener na podstawie pliku o podanej ścieżce.
         *
         * \param[in] file_path std::string ścieżka do pliku zawierającego obraz.
         *
         */
        png_image_container(std::string file_path);

        /** \brief Konstruktor. Inicjuje pusty kontener o podanych parametrach.
         *
         * \param[in] width std::size_t szerokość obrazu w kontenerze.
         * \param[in] height std::size_t wysokość obrazu w kontenerze.
         * \param[in] number_of_colors std::size_t liczba składowych koloru w kontenerze (3 lub 4).
         *
         */
        png_image_container(std::size_t width, std::size_t height,
                            std::size_t number_of_colors);

        /*Read/save file*/
        /** \brief Metoda zapisuje zawartość kontenera do pliku, do którego ścieżka została podana jako argument wywołania.
         *
         * \param[in] file_path std::string Scieżka do pliku, który ma być zapisany.
         *
         */
        void save_to_file(std::string file_path);

        /*Destructor*/
        /** \brief Destruktor.
         *
         */
        ~png_image_container();

};

#endif
