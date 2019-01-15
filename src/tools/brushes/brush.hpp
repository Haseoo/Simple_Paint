/** \file brush.hpp
#define BRUSH_H

#include "../tool.hpp"
#include <SDL2/SDL.h>
#include <iostream>

/** \brief Klasa narzędzia pędzel.
class brush : public tool
{
    public:
        brush();
        virtual void use_tool(std::size_t x_position, std::size_t y_position);
        bool is_a_brush();

};

#endif // BRUSH_H