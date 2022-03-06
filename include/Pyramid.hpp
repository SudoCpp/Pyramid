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

#ifndef __PYRAMID_PYRAMID_HPP__
#define __PYRAMID_PYRAMID_HPP__

#include "simplextk.hpp"
#include "simplexsdl.hpp"
#include "RGBColor.hpp"

namespace pyramid
{
    class Window;
    class Widget;
    class Pyramid : public simplex::Singleton
    {
        static Pyramid* instance;
        simplex::Array<Window*> windows;
        int lastWidgetID;

        static const RGBColor WidgetTextColor;
        static const RGBColor WidgetForegroundColor;
        static const int HoverTimer;

        Widget* lastMouseButtonWidget;
        Widget* lastMouseHoverWidget;

        public:
        const static simplex::string DefaultFontPath;
        const static RGBColor DefaultBackgroundColor;

        virtual ~Pyramid();
        template <typename WindowType, typename... Args>
        static WindowType& CreateWindow(Args&&... args);
        static void StartProgram();
        static void RedrawWindows();
        static int GetWidgetID();

        private:
        static Pyramid& GetInstance();
        Pyramid();
        void processWindowEvents(simplex::sdl::WindowEvent& event);
        void processMouseEvents(simplex::sdl::MouseEvent& event);
        Widget& getWidgetAtMouse(Window& window, int xPosition, int yPosition);
        Window& getCurrentWindow(uint32_t windowID);
    };

    #define __class__ "pyramid::Pyramid"

    template <typename WindowType, typename... Args>
    WindowType& Pyramid::CreateWindow(Args&&... args)
    {
        WindowType* window = new WindowType(std::forward<Args>(args)...);
        Pyramid& pyramid = GetInstance();
        pyramid.windows.add(window);
        return *window;
    }

    #undef __class__
}

#endif //__PYRAMID_PYRAMID_HPP__