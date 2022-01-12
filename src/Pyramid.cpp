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

#include "Pyramid.hpp"
#include "Window.hpp"

#define __class__ "pyramid::Pyramid"

namespace pyramid
{
    using namespace simplex;
    using namespace simplex::sdl;

    Pyramid* Pyramid::instance = nullptr;
    Pyramid::Pyramid() : Singleton{this} {}
    Pyramid::~Pyramid()
    {
        for(Window* window : windows)
            delete window;
    }
    Pyramid& Pyramid::GetInstance()
    {
        if(instance == nullptr)
            instance = new Pyramid();
        return *instance;
    }
    Window& Pyramid::CreateWindow(string title, int width, int height, bool resizable)
    {
        Window* window = new Window(title, width, height, resizable);
        Pyramid& pyramid = GetInstance();
        pyramid.windows.add(window);
        return *window;
    }

    void Pyramid::StartEventLoop()
    {
        Pyramid& instance = GetInstance();
        Event* event;

        for(Window* window : instance.windows)
            window->draw();

        while(true)
        {
            if(event = Framework::GetEvent())
            {
                if(event->type == EventClass::Quit)
                    break;
                else if(event->type == EventClass::Window)
                    instance.processWindowEvents(*(WindowEvent*)event);
                else if(event->type == EventClass::Mouse)
                    instance.processMouseEvents(*(MouseEvent*)event);
            }
        }
    }

    void Pyramid::processWindowEvents(simplex::sdl::WindowEvent& event)
    {
        Window* currentWindow = getCurrentWindow(event.windowID);
        if(!currentWindow)
            return;
            
        if(event.windowType == WindowEventType::Minimized)
            currentWindow->minimized.emit();
        else if(event.windowType == WindowEventType::Maxamized)
            currentWindow->maximized.emit();
        else if(event.windowType == WindowEventType::Resized)
            currentWindow->resized.emit();
        else if(event.windowType == WindowEventType::Restored)
            currentWindow->restored.emit();
        else if(event.windowType == WindowEventType::GainedFocus)
            currentWindow->gainedFocus.emit();
        else if(event.windowType == WindowEventType::LostFocus)
            currentWindow->lostFocus.emit();
    }

    Window* Pyramid::getCurrentWindow(uint32_t windowID)
    {
        Window* currentWindow = windows[0];
        for(Window* window : windows)
            if(window->windowId == windowID)
                return window;
        return nullptr;
    }


    void Pyramid::processMouseEvents(simplex::sdl::MouseEvent& event)
    {
        Window* currentWindow = getCurrentWindow(event.windowID);
        if(!currentWindow)
            return;

        if(event.mouseEventType == MouseEventType::Move)
             currentWindow->mouseMove.emit(event.x, event.y);
        if(event.mouseEventType == MouseEventType::ButtonDown)
            currentWindow->mouseDown.emit(event.x, event.y, event.mouseButton);
        if(event.mouseEventType == MouseEventType::ButtonUp)
            currentWindow->mouseUp.emit(event.x, event.y, event.mouseButton);
        if(event.mouseEventType & MouseEventType::ScrollHorizontal)
            currentWindow->mouseHorizontalScroll.emit(event.x);            
        if(event.mouseEventType & MouseEventType::ScrollVertical)
            currentWindow->mouseVerticalScroll.emit(event.y);            
    }

    void Pyramid::RedrawWindows()
    {
        for(Window* window : GetInstance().windows)
            window->draw();
    }
}
#undef __class__