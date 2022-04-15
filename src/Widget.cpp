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

#include "Widget.hpp"
#include "Pyramid.hpp"

namespace pyramid
{
    Widget::Widget(simplex::string name, AnchorPoint anchorPoint, int width, int height, 
    DockLocation dockLocation, RGBColor backgroundColor) : simplex::object{},
    //Internal Widgets should be known before widget is created and they should be allocated with main widget.
    internalWidgets{false},
    widgetID{Pyramid::GetWidgetID()}, name{name}, anchorPoint{anchorPoint}, 
    dockLocation{dockLocation}, width{width}, height{height}, 
    //parentBackgroundColor must be defaulted to something, should be overriden almost immedately.
    parentBackgroundColor{Color::White},
    backgroundColor{backgroundColor},
    toolTipText{""}
    { }

    Widget::~Widget()
    {
        delete canvas;
    }

    void Widget::initWidget(Canvas& parentCanvas)
    {
        canvas = parentCanvas.createNewCanvas(width, height);
        for(Widget* widget : internalWidgets)
            widget->initWidget(*canvas);
    }

    Canvas& Widget::newCanvas()
    {
        Canvas* newCanvas = canvas->createNewCanvas(width, height);
        delete canvas;
        canvas = newCanvas;
        return *canvas;
    }

    Canvas& Widget::getCanvas()
    {
        return *canvas;
    }

    void Widget::handleResize(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    Widget& Widget::getFinalWidget(int& xPosition, int& yPosition)
    {
        return *this;
    }
}