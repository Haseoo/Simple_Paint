/** \file bmp_image_container.hpp
 * \brief Plik z definicją klasy bmp_image_container.
*/
#define BMP_IMAGE_CONTAINER

#include "image_container.hpp"

/** \brief Kontener dla plików bmp.
{
    public:

        /*Constructors*/
        bmp_image_container(std::string file_path);

        bmp_image_container(std::size_t width, std::size_t height,
                            std::size_t number_of_colors);

        /*Read/save file*/
        void save_to_file(std::string file_path);

        /*Destructor*/
        ~bmp_image_container();

    private:
        /*Data structures definition*/
        struct bmp_file_info {
              std::uint32_t header_size,                /**< Wielość nagłówka. */
                            width,                      /**< Wysokość obrazu. */
                            height,                     /**< Wysokość obrazu */
                            size,                       /**< Rozmiar pliku. */
                            compression,                /**< Znacznik rodzaju zastosowanej kompresji. */
                            image_size,                 /**< Rozmiar obrazu. */
                            horizontal_resolution,      /**< Rozdzielczość w pionie. */
                            vertical_resolution,        /**< Rozdzielczość w poziomie. */
                            number_of_color_in_palette, /**< Liczba kolorów w palecie. */
                            number_of_important_color;  /**< Liczba znaczących kolorów w palecie. */

              std::uint16_t planes,        /**< Płaszczyzny. */
                            bits_per_pixel;/**< Liczba bitów na piksel. */
        };

};

#endif