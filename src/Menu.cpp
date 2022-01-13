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

#include "Menu.hpp"
#include "Pyramid.hpp"

namespace pyramid
{
    using namespace simplex;
    using namespace simplex::sdl;

    Menu::Menu(string name)
    : Widget{name, AnchorPoint::MiddleLeft, 0, 0, DockLocation::Center}, windowHasFocus{true}
    {
        mouseDown.connect(&Menu::handleMouseDown, this);
    }

    Menu::~Menu(){}

    void Menu::draw(int parentCanvasWidth, int parentCanvasHeight)
    {
        string nameToUse = "  "+name+"  ";
        int textHeight = 0;
        Canvas::GetTextSize(FontPath, 13, nameToUse, width, textHeight);
        height = parentCanvasHeight;
        newCanvas();

        int textPositionHeight = (height - textHeight) / 2;
        if(!windowHasFocus)
        {
            getCanvas().fillRect(BackgroundColor, 0, 0, width, height);
            getCanvas().drawText(TextColorNoWindowFocus, FontPath, FontSize, 0, textPositionHeight, nameToUse);
        }
        // else if(activated)
        // {
        //     getCanvas().fillRect(HilightBackgroundColor, 0, 0, width, height);
        //     getCanvas().drawText(HilightTextColor, FontPath, FontSize, 0, textPositionHeight, nameToUse);
        // }
        else
        {
            getCanvas().fillRect(BackgroundColor, 0, 0, width, height);
            getCanvas().drawText(TextColor, FontPath, FontSize, 0, textPositionHeight, nameToUse);
        }
    }

    void Menu::handleMouseDown(int xPosition, int yPosition, MouseButton mouseButton)
    {
        //activated = true;
        Pyramid::RedrawWindows();
    }
}