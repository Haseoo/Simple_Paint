/** \file bmp_image_container.hpp
 * \brief Plik z definicją klasy bmp_image_container.
*/#ifndef BMP_IMAGE_CONTAINER
#define BMP_IMAGE_CONTAINER

#include "image_container.hpp"

/** \brief Kontener dla plików bmp. */class bmp_image_container : public image_container
{
    public:

        /*Constructors*/        /** \brief Konstruktor. Inicjuje kontener na podstawie pliku o podanej ścieżce.         *         * \param[in] file_path std::string ścieżka do pliku zawierającego obraz.         *         */
        bmp_image_container(std::string file_path);
        /** \brief Konstruktor. Inicjuje pusty kontener o podanych parametrach.         *         * \param[in] width std::size_t szerokość obrazu w kontenerze.         * \param[in] height std::size_t wysokość obrazu w kontenerze.         * \param[in] number_of_colors std::size_t liczba składowych koloru w kontenerze (3 lub 4).         *         */
        bmp_image_container(std::size_t width, std::size_t height,
                            std::size_t number_of_colors);

        /*Read/save file*/        /** \brief Metoda zapisuje zawartość kontenera do pliku, do którego ścieżka została podana jako argument wywołania.         *         * \param[in] file_path std::string Scieżka do pliku, który ma być zapisany.         *         */
        void save_to_file(std::string file_path);

        /*Destructor*/        /** \brief Destruktor.         *         */
        ~bmp_image_container();

    private:
        /*Data structures definition*/        /** \brief Struktura pomocnicza przechowująca informacje o obrazach bmp.         */
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