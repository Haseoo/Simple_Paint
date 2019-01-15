/** \file image_container.hpp
 * \brief Plik z definicją klasy image_container oraz typu wyliczeniowego file_type.
*/
#ifndef IMAGE_CONTAINER
#define IMAGE_CONTAINER

#include <string>
#include <fstream>
#include <algorithm>

#include "../../paint_exception.hpp"

/** \brief Klasa bazowa dla wszystkich typów kontenerów obrazu.
 */
class image_container
{
    public:
        /*Types definitions*/

        typedef std::uint32_t ARGB_8888_color; /**< Definicja typu przechowującego 4 składowe koloru po 8 bitów każdy. */

        /** \brief Typ wyliczeniowy określający typ pliku.
         */
        enum file_type {PPM_FILE,  /**< Plik ppm. */
                        BMP_FILE,  /**< Plik bmp. */
                        PNG_FILE,  /**< Plik jpg. */
                        UNSUPPORTED/**< Typ nieobsługiwany przez kontener. */
                        };

        /** \brief Struktura przechowująca podstawowe informacje o przechowywanym obrazie.
         */
        struct basic_image_info {
            std::uint32_t width,            /**< Szerokość obrazu */
                          height,           /**< Wysokość obrazu. */
                          number_of_colors; /**< Liczba części składowych koloru. */

            enum file_type image_type;
        };

        /** \brief Struktura przechowująca informacje o składowych koloru.
         */
        struct color {
            std::uint8_t red,  /**< Składowa czerwieni. */
                         green,/**< Składowa zielona. */
                         blue, /**< Składowa niebieska. */
                         alpha;/**< Kanał przeźroczystości. */
        };


        /*Constructor*/
        /** \brief Konstruktor klasy.
         *
         */
        image_container();

        /*Image faile info*/
        /** \brief Getter podstawowych informacji na temat przechowywanego obrazu.
         *
         **\return struct basic_image_info struktura przechowująca informacje o obrazie.
         */
        struct basic_image_info get_image_info();

        /*Read/save file*/
        /** \brief Metoda wczytuje obraz z tablicy pikseli, która zawiera 4 składowe po 8 bitów każdy. Nie zwraca żadnej wartości.
         *
         * \param[in] image_pixel_array const ARGB_8888_color* tablica plkseli.
         *
         */
        void set_pixels_form_array(const ARGB_8888_color *image_pixel_array);

        /** \brief Metoda zapisuje zawartość kontenera do pliku, do którego ścieżka została podana jako argument wywołania.
         *
         * \param[in] file_path std::string Scieżka do pliku, który ma być zapisany.
         *
         */
        virtual void save_to_file(std::string file_path)   = 0;

        /*Operator overloading*/
        /** \brief Przeciążenie operatora [], zwraca kolor piksela w formacie ARGB_8888.
         *
         */
        ARGB_8888_color operator[](std::size_t n);

        /*Destructor*/
        /** \brief Destruktor. Usuwa zmienne zaalokowane dynamicznie.
         *
         */
        virtual ~image_container();


        /*Getting type form file*/
        /** \brief Metoda statyczna, która zwraca typ obrazu, do którego sieżka została podana jako argument wywołania.
         * Metoda "rzuca" wyjątek typu paint_exception gdy otwarcie lub czytanie pliku się nie powiedzie.
         *
         * \param[in] file_path std::string ścieżka do pliku.
         * \return enum file_type Typ pliku lub wartość UNSUPPORTED.
         *
         */
        static enum file_type get_file_type(std::string file_path) {

            enum file_type type = UNSUPPORTED;
            std::ifstream image_file;

            image_file.open(file_path);
            if (image_file.is_open()) {
                int buffer = 0;
                image_file.read(reinterpret_cast<char*>(&buffer), 2);

                if (image_file.fail()) {
                    throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path);
                }
                else {
                    if (buffer == 0x3650) {
                        type = PPM_FILE;
                    }
                    else if (buffer == 0x4D42) {
                        type = BMP_FILE;
                    }
                    else if (buffer == 0x5089) {
                        type = PNG_FILE;
                    }
                }
                image_file.close();
            }
            else {
                throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path);
            }
            return type;
        }

        protected:
            std::string image_path(); /**< Ścieża do pliku, nad którym wykonywana jest operacja. */
            struct basic_image_info image_info = {0, 0, 0, UNSUPPORTED}; /**< Informacje o otwartym obrazie. */
            struct color *image_pixel_array = nullptr; /**< Wskaźnik na tablicę pikseli obrazu. */
    };




#endif
