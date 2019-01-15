/** \file image_container.cpp
 * \brief Plik z definicjami metod klasy image_container.
*/

#include "image_container.hpp"

image_container::image_container() {

}

struct image_container::basic_image_info image_container::get_image_info() {
    return image_info;
}



void image_container::set_pixels_form_array(const ARGB_8888_color *image_pixel_array) {
    if (image_pixel_array) {
        if (this->image_pixel_array) {
            for(std::size_t j = 0; j < image_info.height; j++) {
                for (std::size_t i = 0; i < image_info.width; i++) {
                    ARGB_8888_color buffer = image_pixel_array[j * image_info.width + i];
                    (this->image_pixel_array)[j * image_info.width + i].blue  = (std::uint8_t)buffer;
                    (this->image_pixel_array)[j * image_info.width + i].green = (std::uint8_t)(buffer >> 8);
                    (this->image_pixel_array)[j * image_info.width + i].red   = (std::uint8_t)(buffer >> 16);
                    (this->image_pixel_array)[j * image_info.width + i].alpha = (std::uint8_t)(buffer >> 24);
                }
            }
        }
        else {
            throw paint_exception(paint_exception::IMAGE_CONTAINTER_PIXEL_ARRAY);
        }
    }
    else {
        throw paint_exception(paint_exception::IMAGE_CONTAINER_BAD_RBGA8888_PIXBUF);
    }
}



image_container::ARGB_8888_color image_container::operator[](std::size_t n) {
    if (n > image_info.width * image_info.height) {
        throw paint_exception(paint_exception::IMAGE_CONTAINER_OPERATOR);
        return 0;
    }
    return ((image_container::ARGB_8888_color)image_pixel_array[n].alpha << 24) + ((image_container::ARGB_8888_color)image_pixel_array[n].red << 16) +
           ((image_container::ARGB_8888_color)image_pixel_array[n].green << 8 ) + ((image_container::ARGB_8888_color)image_pixel_array[n].blue);
}



image_container::~image_container() {
    if (image_pixel_array) {
        delete image_pixel_array;
        image_pixel_array = nullptr;
    }
}
