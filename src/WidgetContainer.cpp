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

#include "WidgetContainer.hpp"

namespace pyramid
{
    using namespace simplex::sdl;
    using namespace simplex;

    WidgetContainer::WidgetContainer(simplex::string name, int width, int height)
    :Widget{name, AnchorPoint::TopLeft, width, height, DockLocation::Center, Color::White}, widgets{false}
    {
        canvas = nullptr;
    }

    WidgetContainer::~WidgetContainer()
    {
        for(Tuple<Widget*,int,int>* widget : widgets)
        {
            delete widget->at<0>();
            delete widget;
        }
    }

    Widget& WidgetContainer::getFinalWidget(int& xPosition, int& yPosition)
    {
        for(Tuple<Widget*, int, int>* widgetGroup : widgets)
        {
            Widget* widget = widgetGroup->at<0>();
            int widgetXPosition = widgetGroup->at<1>();
            int widgetYPosition = widgetGroup->at<2>();
            int widgetWidth = widget->width;
            int widgetHeight= widget->height;
            if(xPosition >= widgetXPosition 
                && yPosition >= widgetYPosition 
                && xPosition <= widgetXPosition + widgetWidth 
                && yPosition <= widgetYPosition + widgetHeight)
            {
                xPosition = xPosition-widgetXPosition;
                yPosition = yPosition-widgetYPosition;
                return widget->getFinalWidget(xPosition, yPosition);
            }
        }
        return *this;
    }
}