/** \file bmp_image_container.cpp
 * \brief Plik z definicjami metod klasy bmp_image_container.
*/

#include "bmp_image_container.hpp"
#include <iostream>

bmp_image_container::bmp_image_container(std::size_t width, std::size_t height,
                            std::size_t number_of_colors) {

    image_info.height           = height;
    image_info.width            = width;
    image_info.number_of_colors = number_of_colors;
    image_info.image_type       = BMP_FILE;

    try {
        this->image_pixel_array = new struct color[image_info.height * image_info.width];
    }
    catch(std::bad_alloc &exception) {
        throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_ALLOC, exception.what());
    }
}

bmp_image_container::bmp_image_container(std::string file_path) {

    image_info.image_type = BMP_FILE;
    std::ifstream image_file;

    image_file.open(file_path);

    if (image_file.is_open()) {

        char image_short_header[14];

        /*Reading header form file*/
        image_file.read(image_short_header, 14);
        if (image_file.fail()) {
            
            image_info.image_type = UNSUPPORTED;
            return;
        }

        /*Checking if pointed file is really bitmap*/
        if (*(reinterpret_cast <std::uint16_t*>(image_short_header)) != 0x4D42) {
            throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_BMP);
            image_info.image_type = UNSUPPORTED;
            return;
        }
        struct bmp_file_info DIB_header_info; //Structure that holds information form DIB header

        std::uint32_t pixel_array_offset = *(reinterpret_cast <std::uint32_t*>(image_short_header + 10)); //Geting adress of pixel array
        DIB_header_info.size = *(reinterpret_cast <std::uint32_t*>(image_short_header + 2)); //Getting image size

        image_file.read(reinterpret_cast<char*>(&(DIB_header_info.header_size)), 4); //Geting information about DIB header size

        if (DIB_header_info.header_size == 40) { //Program supports only windows bitmap that has DIB header 40 bytes long
            char DIB_header[36]; //40-4 because information about header size is 4 bytes long

            image_file.read(DIB_header, DIB_header_info.header_size - 4); //reading DIB header form file
            if (image_file.fail()) {
                
                image_info.image_type = UNSUPPORTED;
                return;
            }

            /*Getting information about image from DIB header*/
            DIB_header_info.width          = *(reinterpret_cast <std::uint32_t*>(DIB_header));
            DIB_header_info.height         = *(reinterpret_cast <std::uint32_t*>(DIB_header + 4));
            DIB_header_info.planes         = *(reinterpret_cast <std::uint16_t*>(DIB_header + 8));
            DIB_header_info.bits_per_pixel = *(reinterpret_cast <std::uint16_t*>(DIB_header + 10));
            DIB_header_info.compression    = *(reinterpret_cast <std::uint32_t*>(DIB_header + 12));
            DIB_header_info.image_size     = *(reinterpret_cast <std::uint32_t*>(DIB_header + 16));

            std::size_t number_of_colors = DIB_header_info.bits_per_pixel / 8;

            /*Program supports only 32 bit bitmap with 3/4 color with no comprssion nor animation*/
            if (DIB_header_info.width > 0 && DIB_header_info.height > 0 && (number_of_colors == 3 || number_of_colors == 4) &&
                DIB_header_info.planes == 1 && DIB_header_info.compression == 0) {

                    /*Writing information got form DIB header to class fields*/
                    image_info.width            = DIB_header_info.width;
                    image_info.height           = DIB_header_info.height;
                    image_info.number_of_colors = number_of_colors;

                    char *file_pixel_array;
                    try {
                        file_pixel_array  = new char[DIB_header_info.size - 54]; //Creating an array with size of pixel array (total size - headers size)
                        image_pixel_array = new struct color[image_info.width * image_info.height];
                    }
                    catch(std::bad_alloc &exception) {
                        throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_ALLOC, exception.what());
                    }

                    image_file.seekg(std::ios_base::beg + pixel_array_offset); //Getting to pixel array
                    image_file.read(file_pixel_array, DIB_header_info.size - 54); //Reading pixel array

                    if (image_file.fail()) {
                        throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path); 
                        image_info.image_type = UNSUPPORTED;
                        return;
                    }

                    std::size_t pixel_array_iterator = 0; //Iterator for pixel array got form file

                    /*Writing information about color form file to container's pixel color array*/
                    /*Pixels in bmp file are stored in BGRA order*/
                    for(std::size_t j = 0; j < image_info.height; j++) {
                        for(std::size_t i = 0; i < image_info.width; i++) {

                            image_pixel_array[j * image_info.width + i].blue  = file_pixel_array[pixel_array_iterator++];
                            image_pixel_array[j * image_info.width + i].green = file_pixel_array[pixel_array_iterator++];
                            image_pixel_array[j * image_info.width + i].red   = file_pixel_array[pixel_array_iterator++];

                            if(number_of_colors == 4)
                                image_pixel_array[j * image_info.width + i].alpha = file_pixel_array[pixel_array_iterator++];
                            else
                                 image_pixel_array[j * image_info.width + i].alpha = 255;
                        }
                    }

                    delete[] file_pixel_array; //Deleting temporary array

                    /*Reversing array becouse of pixels in bitmap file are stored in oposite order*/

                    /*Vertical flip*/
                    std::reverse(image_pixel_array, image_pixel_array + (image_info.width * image_info.height));
                    /*Horizontal flp*/
                    for(std::size_t i = 0; i < image_info.height; i++) {
                        std::reverse(image_pixel_array + (i * image_info.width), image_pixel_array + ((i + 1) * image_info.width));
                    }

                }
            else {
                throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_BMP, "Unsupported bitmap. Unsupported or invaild bitmap parameters.");
                image_info.image_type = UNSUPPORTED;
            }
        }
        else {
            throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_BMP, "Unsupported bitmap. Invalid header");
            image_info.image_type = UNSUPPORTED;
        }

    }
    else {
        throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path); 
        image_info.image_type = UNSUPPORTED;
    }

}

void bmp_image_container::save_to_file(std::string file_path) {
    std::ofstream image_file;

    image_file.open(file_path);

    if (image_file.is_open(), std::ios::ate) {
        /*File headers*/
        char header[14];
        char DIB_header[40];

        struct bmp_file_info DIB_header_info = {40, //Header size
                                                image_info.width, //File width
                                                image_info.height, //File height
                                                image_info.height * image_info.width * 4 + 54, //file total size
                                                0, //compression
                                                0, //dummy pritning data
                                                0x0EC3, //dummy value horizontal resolution
                                                0x0EC3, //dummy value vertical resolution
                                                0, //number of color in palette
                                                0, //number of important color in palette
                                                1, //planes
                                                32 }; //32bit bitmap

        /*Initializing file header*/
        *(reinterpret_cast <std::uint16_t*>(header))      = 0x4D42; //BMP file magic number
        *(reinterpret_cast <std::uint32_t*>(header + 2))  = DIB_header_info.size;
        *(reinterpret_cast <std::uint32_t*>(header + 6))  = 0; //Dummy data
        *(reinterpret_cast <std::uint32_t*>(header + 10)) = 0x36; //Pixel array offset

        /*Initializing file DIB header*/
        *(reinterpret_cast <std::uint32_t*>(DIB_header))      = DIB_header_info.header_size;
        *(reinterpret_cast <std::uint32_t*>(DIB_header + 4))  = DIB_header_info.width;
        *(reinterpret_cast <std::uint32_t*>(DIB_header + 8))  = DIB_header_info.height;
        *(reinterpret_cast <std::uint16_t*>(DIB_header + 12)) = DIB_header_info.planes;
        *(reinterpret_cast <std::uint16_t*>(DIB_header + 14)) = DIB_header_info.bits_per_pixel;
        *(reinterpret_cast <std::uint32_t*>(DIB_header + 16)) = DIB_header_info.compression;
        *(reinterpret_cast <std::uint32_t*>(DIB_header + 20)) = DIB_header_info.image_size;
        *(reinterpret_cast <std::uint32_t*>(DIB_header + 24)) = DIB_header_info.horizontal_resolution;
        *(reinterpret_cast <std::uint32_t*>(DIB_header + 28)) = DIB_header_info.vertical_resolution;
        *(reinterpret_cast <std::uint32_t*>(DIB_header + 32)) = DIB_header_info.number_of_color_in_palette;
        *(reinterpret_cast <std::uint32_t*>(DIB_header + 36)) = DIB_header_info.number_of_important_color;

        char *pixel_array_buffer;

        try {
            pixel_array_buffer = new char[DIB_header_info.size - 54]; //Creating buffer for pixels
        }
        catch (std::bad_alloc &exception) {
            throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_ALLOC, exception.what());
            return;
        }

        /*Making vertical flip because pixels in BMP files are stored in oposide order*/
        for(std::size_t i = 0; i < image_info.height; i++) {
            std::reverse(image_pixel_array + (i * image_info.width), image_pixel_array + ((i + 1) * image_info.width));
        }

        std::size_t pixel_array_iterator = DIB_header_info.size - 55; //Iterator with value with which it's possible to make horizontal flip
        for(std::size_t j = 0; j < image_info.height; j++) {
            for(std::size_t i = 0; i < image_info.width; i++) {
                pixel_array_buffer[pixel_array_iterator--] = image_pixel_array[j * image_info.width + i].alpha;
                pixel_array_buffer[pixel_array_iterator--] = image_pixel_array[j * image_info.width + i].red;
                pixel_array_buffer[pixel_array_iterator--] = image_pixel_array[j * image_info.width + i].green;
                pixel_array_buffer[pixel_array_iterator--] = image_pixel_array[j * image_info.width + i].blue;
            }
        }

        image_file.write(header, sizeof(header)); //Writing header to file
        image_file.write(DIB_header, DIB_header_info.header_size); //Writing DIB header to file
        image_file.write(pixel_array_buffer, DIB_header_info.size - 54); //Writing pixel array to file

        delete[] pixel_array_buffer; //Deleting temporary array

        if (image_file.bad()) {
            throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path); 
        }
    }
    else {
        throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path); 
    }
}

bmp_image_container::~bmp_image_container() {
}
