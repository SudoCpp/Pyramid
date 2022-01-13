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

#include "Window.hpp"

#define __class__ "pyramid::Window"

namespace pyramid
{
    using namespace simplex;
    using namespace simplex::sdl;

    Window::Window(string title, int width, int height, bool resizable)
    : WidgetContainer(title, width, height),
    window{Framework::CreateWindow(title, width, height, resizable)}, 
    renderer{window.createRenderer()}, windowId{window.getID()}
    {
        canvas = new Canvas(renderer, width, height);
        maximized.connect(&Window::draw, this);
        restored.connect(&Window::draw, this);
        resized.connect(&Window::draw, this);
        gainedFocus.connect(&Window::dispatchGainedWindowFocus, this);
        lostFocus.connect(&Window::dispatchLostWindowFocus, this);
        draw();
    }

    Window::~Window()
    {}

    void Window::draw()
    {
        regenCanvas();
        canvas->fillRect(RGBColor{250, 250, 250}, 0, 0, window.getWidth(), window.getHeight());

        int topOffset = 0;
        int bottomOffset = 0;
        bool centerPopulated = false;
        
        int widgetArraySize = widgets.size();
        for(int loop = 0; loop < widgetArraySize; loop++)
        {
            Tuple<Widget*, int, int>* widgetGroup = widgets[loop];
            Widget* widget = widgetGroup->at<0>();
            widget->draw(canvas->width, canvas->height-topOffset-bottomOffset);
            if(widget->dockLocation == DockLocation::Top)
            {
                widgetGroup->at<1>(0);
                widgetGroup->at<2>(topOffset);
                canvas->copyToCanvas(widget->getCanvas(), 0, topOffset);
                topOffset += widget->height;
            }
            else if(widget->dockLocation == DockLocation::Bottom)
            {
                bottomOffset += widget->height;
                widgetGroup->at<1>(0);
                widgetGroup->at<2>(canvas->height-bottomOffset);
                canvas->copyToCanvas(widget->getCanvas(), 0, canvas->height-bottomOffset);
            }
            else if(widget->dockLocation == DockLocation::Center && !centerPopulated)
            {
                centerPopulated = true;
                canvas->copyToCanvas(widget->getCanvas(), 0, topOffset);
            }
        }
        displayCanvas();
    }

    void Window::displayCanvas()
    {
        renderer.setTarget();
        renderer.copyTexture(*(canvas->texture), 0, 0);
        renderer.present();
    }

    void Window::regenCanvas()
    {
        int width = window.getWidth();
        int height = window.getHeight();
        Canvas* newCanvas = canvas->createNewCanvas(width, height);
        delete canvas;
        canvas = newCanvas;
    }

    void Window::dispatchGainedWindowFocus()
    {
        for(Tuple<Widget*, int, int>* widget : widgets)
            widget->at<0>()->gainedWindowFocus.emit();
        draw();
    }
    void Window::dispatchLostWindowFocus()
    {
        for(Tuple<Widget*, int, int>* widget : widgets)
            widget->at<0>()->lostWindowFocus.emit();
        draw();
    }
}