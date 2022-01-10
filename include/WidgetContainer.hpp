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

#ifndef PYRAMID_WIDGETCONTAINER_HPP
#define PYRAMID_WIDGETCONTAINER_HPP

#include "simplextk.hpp"
#include "Canvas.hpp"
#include "Widget.hpp"

namespace pyramid
{
    class WidgetContainer : public simplex::object
    {
        protected:
        Canvas* canvas;
        //Widget pointer, int width on canvas, int height on canvas
        simplex::Array<simplex::Tuple<Widget*, int, int>*> widgets;

        public:
        simplex::Signal<> resized;

        WidgetContainer();
        virtual ~WidgetContainer();

        virtual void draw() = 0;
        static void GetCanvasCoordinates(Widget& widget, int& xCoordinate, int& yCoordinate, int canvasWidth, int canvasHeight);

        template <typename WidgetType>
        WidgetType& addWidget(WidgetType* widget);

        template <typename WidgetType>
        WidgetType& getWidget(simplex::string widgetName);

        template <typename WidgetType>
        WidgetType* removeWidget(simplex::string widgetName);
    };

    #define __class__ "pyramid::WidgetContainer"

    template <typename WidgetType>
    WidgetType& WidgetContainer::addWidget(WidgetType* widget)
    {
        widget->initWidget(*canvas);
        widgets.add(new simplex::Tuple<Widget*, int, int>{widget, 0, 0});
        return *widget;
    }

    template <typename WidgetType>
    WidgetType& WidgetContainer::getWidget(simplex::string widgetName)
    {
        for(Widget* widget : widgets)
            if(widget->name == widgetName)
                return *widget;
        throw Exception("Widget with name '" + widgetName + "' can not be found.", __ExceptionParams__);
    }

    template <typename WidgetType>
    WidgetType* WidgetContainer::removeWidget(simplex::string widgetName)
    {
        int widgetsSize = widgets.size();
        for(int loop = 0; loop < widgetsSize; loop++)
            if(widgets[loop]->at<0>()->name == widgetName)
            {
                Widget* widget = widgets[loop];
                widgets.removeAt(loop);
                return widget;
            }
        throw Exception("Widget with name '" + widgetName + "' can not be found.", __ExceptionParams__);
    }

    #undef __class__
}

#endif //PYRAMID_WIDGETCONTAINER_HPP