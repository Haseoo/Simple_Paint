/** \file png_image_container.cpp
 * \brief Plik definicję metod klasy png_image_container.
 */#include "png_image_container.hpp"

png_image_container::png_image_container(std::size_t width, std::size_t height,
                            std::size_t number_of_colors) {

    image_info.height           = height;
    image_info.width            = width;
    image_info.number_of_colors = number_of_colors;
    image_info.image_type       = PNG_FILE;

    try {
        this->image_pixel_array = new struct color[image_info.height * image_info.width];
    }
    catch(std::bad_alloc &exception) {
        throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_ALLOC, exception.what());
    }
}

png_image_container::png_image_container(std::string file_path) {
    try {
        png::image<png::rgb_pixel> file_image(file_path);

        image_info.width            = file_image.get_width();
        image_info.height           = file_image.get_height();
        image_info.number_of_colors = 4;
        image_info.image_type       = PNG_FILE;

        try {
            image_pixel_array = new struct color[image_info.width * image_info.height];
        }
        catch(std::bad_alloc &exception) {
            throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_ALLOC, exception.what());
        }

        for(std::size_t j = 0; j < image_info.height; j++) {
            for(std::size_t i = 0; i < image_info.width; i++) {

                image_pixel_array[j * image_info.width + i].red   = file_image.get_pixel(i, j).red;
                image_pixel_array[j * image_info.width + i].green = file_image.get_pixel(i, j).green;
                image_pixel_array[j * image_info.width + i].blue  = file_image.get_pixel(i, j).blue;
                image_pixel_array[j * image_info.width + i].alpha = 255; //Dummy value because SDL2 doesn't support alpha channel at all
            }
        }
    }
    catch(png::error exception) {
        throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_PNG, exception.what());
    }

}

void png_image_container::save_to_file(std::string file_path) {
    try {
        png::image<png::rgb_pixel> file_image(image_info.width, image_info.height);

        for(std::size_t j = 0; j < image_info.height; j++) {
            for(std::size_t i = 0; i < image_info.width; i++) {
                file_image.set_pixel(i, j, png::rgb_pixel(image_pixel_array[j * image_info.width + i].red,
                                                          image_pixel_array[j * image_info.width + i].green,
                                                          image_pixel_array[j * image_info.width + i].blue));

            }
        }
        try {
            file_image.write(file_path);
        }
        catch (png::std_error exception) {
            throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_PNG, exception.what());
        }
    }
    catch(png::error exception) {
        throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_PNG, exception.what());
        return;
    }

}

png_image_container::~png_image_container() {

}