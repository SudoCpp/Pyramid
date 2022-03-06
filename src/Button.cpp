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

#include "Button.hpp"

namespace pyramid
{
    using namespace simplex;
    using namespace simplex::sdl;

    Button::Button(const simplex::string& name, const simplex::string& text, const simplex::string& fontPath, int fontSize,
        const RGBColor& textColor, const RGBColor& buttonColor)
    : Widget{name, AnchorPoint::MiddleCenter, 0, 0, DockLocation::Center},
    text{"text", text, fontPath, fontSize, textColor, buttonColor}, 
    buttonDepressed{false}, buttonText{text},
    textColor{textColor}, buttonColor{buttonColor}, 
    fontPath{fontPath}, fontSize{fontSize}
    {
        internalWidgets.add(&this->text);
        mouseDown.connect(&Button::depressButton, this);
    }

    Button::~Button()
    {}

    void Button::depressButton(int xloc, int yloc, simplex::sdl::MouseButton button)
    {
        buttonDepressed = true;
        widgetChanged.emit();
    }

    void Button::draw(int parentCanvasWidth, int parentCanvasHeight)
    {
        width = 200;
        height = 25;
        Canvas& canvas = newCanvas();
        if(!buttonDepressed)
            canvas.fillRect(buttonColor, 0, 0, width, height);
        else
            canvas.fillRect(Color::White, 0, 0, width, height);
        canvas.drawLine(Color::Black, 0, 0, width-1, 0);
        canvas.drawLine(Color::Black, 0, height-1, width-1, height-1);
        canvas.drawLine(Color::Black, 0, 0, 0, height-1);
        canvas.drawLine(Color::Black, width-1, 0, width-1, height-1);
        text.draw(parentCanvasWidth, parentCanvasHeight);
        canvas.copyToCanvas(text.getCanvas(), width/2-text.width/2, height/2-text.height/2);
    }
}