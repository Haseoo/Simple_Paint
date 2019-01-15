/** \file ppm_image_container.hpp
 * \brief Plik definicję klasy ppm_image_container.
 */#ifndef PPM_IMAGE_CONTAINER_H
#define PPM_IMAGE_CONTAINER_H

#include "image_container.hpp"

/** \brief Kontener dla plików ppm.
 */
class ppm_image_container : public image_container
{
    public:
        /*Constructors*/
        /** \brief Konstruktor. Inicjuje kontener na podstawie pliku o podanej ścieżce.
         *
         * \param[in] file_path std::string ścieżka do pliku zawierającego obraz.
         *
         */
        ppm_image_container(std::string file_path);

        /** \brief Konstruktor. Inicjuje pusty kontener o podanych parametrach.
         *
         * \param[in] width std::size_t szerokość obrazu w kontenerze.
         * \param[in] height std::size_t wysokość obrazu w kontenerze.
         * \param[in] number_of_colors std::size_t liczba składowych koloru w kontenerze (3 lub 4).
         *
         */
        ppm_image_container(std::size_t width, std::size_t height,
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
        ~ppm_image_container();

    private:
        /*Data structures definition*/
        /** \brief Struktura pomocnicza przechowująca informacje o obrazach ppm.
         */
        struct ppm_file_info {
              std::uint32_t width,         /**< Szerokość obrazu. */
                            height,        /**< Wysokość obrazu. */
                            bits_per_color;/**< Liczba bitów na składową koloru. */
        };



};


#endif
