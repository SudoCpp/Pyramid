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

#ifndef __PYRAMID_WINDOW_HPP__
#define __PYRAMID_WINDOW_HPP__

#include "simplextk.hpp"
#include "simplexsdl.hpp"
#include "MenuBar.hpp"
#include "StatusBar.hpp"
#include "WidgetContainer.hpp"

namespace pyramid
{
    class Window : public WidgetContainer
    {
        friend class Pyramid;

        simplex::sdl::Window& window;
        simplex::sdl::Renderer& renderer;
        bool visuallyChanged;
        
        public:
        uint32_t windowId;

        simplex::Signal<> maximized;
        simplex::Signal<> minimized;
        simplex::Signal<> restored;
        simplex::Signal<> gainedFocus;
        simplex::Signal<> lostFocus;

        simplex::Signal<int, int> mouseMove;
        simplex::Signal<int, int, simplex::sdl::MouseButton> mouseDown;
        simplex::Signal<int, int, simplex::sdl::MouseButton> mouseUp;
        simplex::Signal<int> mouseHorizontalScroll;
        simplex::Signal<int> mouseVerticalScroll;

        Window(simplex::string title, int width, int height, bool resizable);
        ~Window();

        void draw();

        private:
        virtual void draw(int parentCanvasWidth, int parentCanvasHeight){}
        void displayCanvas();
        void regenCanvas();

        void dispatchGainedWindowFocus();
        void dispatchLostWindowFocus();
        void forceRedraw();
    };
}

#endif //__PYRAMID_WINDOW_HPP__