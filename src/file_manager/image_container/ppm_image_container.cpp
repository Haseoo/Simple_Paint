/** \file ppm_image_container.cpp
 * \brief Plik z definicjami metod klasy ppm_image_container.
*/

#include "ppm_image_container.hpp"

ppm_image_container::ppm_image_container(std::size_t width, std::size_t height,
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

ppm_image_container::ppm_image_container(std::string file_path) {

    image_info.image_type = PPM_FILE;
    std::ifstream image_file;

    image_file.open(file_path);

    if (image_file.is_open()) {
        std::string file_id;

        std::getline(image_file, file_id);
        if (image_file.fail()) {
            throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path); 
            image_info.image_type = UNSUPPORTED;
            return;
        }

        if (file_id == "P6") { //checking if pointed file is really pixmap
            std::string dummy;

            /*Getting rid of all comments in file*/
            while (image_file.peek() == '#') {
                std::getline(image_file, dummy);
            }

            struct ppm_file_info info_form_file;

            image_file >> info_form_file.width >> info_form_file.height >> info_form_file.bits_per_color;
            image_file.get(); //passing \n char

            if (image_file.fail()) {
                throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path); 
                image_info.image_type = UNSUPPORTED;
                return;
            }

            /*Program supports only 8 bit color pixmaps*/
            if (info_form_file.height != 0 && info_form_file.width != 0 && info_form_file.bits_per_color == 255) {

                /*Writing information got form file header to class fields*/
                image_info.width            = info_form_file.width;
                image_info.height           = info_form_file.height;
                image_info.number_of_colors = 3;

                char *file_pixel_array;
                try {
                    file_pixel_array  = new char[image_info.width * image_info.height * image_info.number_of_colors];
                    image_pixel_array = new struct color[image_info.width * image_info.height];
                }
                catch(std::bad_alloc &exception) {
                    throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_ALLOC, exception.what());
                }

                image_file.read(file_pixel_array, image_info.width * image_info.height * image_info.number_of_colors);

                if (image_file.fail()) {
                    throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path);
                    image_info.image_type = UNSUPPORTED;
                    return;
                }

                std::size_t pixel_array_iterator = 0;

                for (std::size_t j = 0; j < image_info.height; j++) {
                    for (std::size_t i = 0; i < image_info.width; i++) {
                        image_pixel_array[j * image_info.width + i].alpha = 255;
                        image_pixel_array[j * image_info.width + i].red   = file_pixel_array[pixel_array_iterator++];
                        image_pixel_array[j * image_info.width + i].green = file_pixel_array[pixel_array_iterator++];
                        image_pixel_array[j * image_info.width + i].blue  = file_pixel_array[pixel_array_iterator++];
                    }
                }
            }
            else {
                throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_PPM, "Unsupported or invaild pixmap parameters.");
                image_info.image_type = UNSUPPORTED;
            }

        }
        else {
            throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_PPM, "Unsupported or invaild pixmap header.");
            image_info.image_type = UNSUPPORTED;
        }
    }

    else {
        throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path); 
        image_info.image_type = UNSUPPORTED;
    }

}

void ppm_image_container::save_to_file(std::string file_path) {
    std::ofstream image_file;

    image_file.open(file_path);

    if (image_file.is_open(), std::ios::ate) {
        std::string header[4];

        /*Initializing file header*/
        header[0] = "P6\n"; //file id
        header[1] = "#Created in SimpePaint v2.1\n"; //comment
        header[2] = std::to_string(image_info.width) + " " + std::to_string(image_info.height) + "\n"; //dimentions
        header[3] = std::to_string(255) + "\n"; // bits per color

        char *pixel_array_buffer;

        try {
            pixel_array_buffer = new char[image_info.width * image_info.height * image_info.number_of_colors]; //Creating buffer for pixels
        }
        catch (std::bad_alloc &exception) {
            throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_ALLOC, exception.what());
            return;
        }

        std::size_t pixel_array_iterator = 0;
        for(std::size_t j = 0; j < image_info.height; j++) {
            for(std::size_t i = 0; i < image_info.width; i++) {
                pixel_array_buffer[pixel_array_iterator++] = image_pixel_array[j * image_info.width + i].red;
                pixel_array_buffer[pixel_array_iterator++] = image_pixel_array[j * image_info.width + i].green;
                pixel_array_buffer[pixel_array_iterator++] = image_pixel_array[j * image_info.width + i].blue;
            }
        }

        image_file << header[0] << header[1] << header[2] << header[3];
        image_file.write(pixel_array_buffer, image_info.width * image_info.height * image_info.number_of_colors);

        delete[] pixel_array_buffer; //Deleting temporary array

        if (image_file.bad()) {
            throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path); 
        }
    }
    else {
        throw paint_exception(paint_exception::IMAGE_FILE_ERROR, file_path); 
    }
}



ppm_image_container::~ppm_image_container(){

}
