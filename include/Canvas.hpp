/*
    BSD 3-Clause License
    
    Copyright (c) 2022, SudoCpp
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef PYRAMID_CANVAS_HPP
#define PYRAMID_CANVAS_HPP

#include "simplexsdl.hpp"
#include "CMYColor.hpp"
#include "RGBColor.hpp"

namespace pyramid
{
    class Canvas
    {
        friend class Window; //So can see texture for rendering to screen
        
        simplex::sdl::Renderer& renderer;
        simplex::sdl::Texture* texture;
        
        public:
        int width;
        int height;
        Canvas(simplex::sdl::Renderer& renderer, int width, int height);
        ~Canvas();
        void drawLine(RGBColor color, int point1x, int point1y, int point2x, int point2y);
        void drawRect(RGBColor color, int x, int y, int width, int height);
        void fillRect(RGBColor color, int x, int y, int width, int height);
        void drawText(RGBColor color, simplex::string fontFileName, int fontSize, int x, int y, simplex::string text);
        void copyToCanvas(Canvas& childCanvas, int xPosition, int yPosition);
        Canvas* createNewCanvas(int width, int height) const;

        static void GetTextSize(simplex::string fontFileName, int fontSize, const simplex::string& text, int& width, int& height);
    };
}

#endif //PYRAMID_CANVAS_HPP