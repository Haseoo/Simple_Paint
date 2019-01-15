/** \file star_brush.hpp
#define STAR_BRUSH_H

#include "brush.hpp"

class star_brush : public brush {
    public:
        star_brush();
    protected:
        void PaintPixel(std::size_t x_position, std::size_t y_position);
};


#endif