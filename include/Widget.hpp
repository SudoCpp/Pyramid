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

#ifndef __PYRAMID_WIDGET_HPP__
#define __PYRAMID_WIDGET_HPP__

#include "simplextk.hpp"
#include "simplexsdl.hpp"
#include "AnchorPoint.hpp"
#include "Canvas.hpp"
#include "DockLocation.hpp"
#include "Color.hpp"

namespace pyramid
{
    class Widget : public simplex::object
    {
        protected:
        Canvas* canvas;
        
        public:
        int widgetID;
        simplex::string name;
        AnchorPoint anchorPoint;
        DockLocation dockLocation;
        int width;
        int height;

        simplex::string toolTipText;

        simplex::Signal<> gainedWindowFocus;
        simplex::Signal<> lostWindowFocus;
        simplex::Signal<int, int> hover;
        simplex::Signal<int, int, simplex::sdl::MouseButton> mouseDown;
        simplex::Signal<int, int, simplex::sdl::MouseButton> mouseUp;
        simplex::Signal<int, int, simplex::sdl::MouseButton> mouseClick;

        Widget(simplex::string name, AnchorPoint anchorPoint, int width, int height, DockLocation dockLocation);
        virtual ~Widget();

        virtual void initWidget(Canvas& parentCanvas);
        virtual void draw(int parentCanvasWidth, int parentCanvasHeight) = 0;
        virtual Widget* getFinalWidget(int& xPosition, int& yPosition);
        void newCanvas();
        Canvas& getCanvas();
        void handleResize(int width, int height);
    };
}

#endif //__PYRAMID_WIDGET_HPP__