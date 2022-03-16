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

#include "MenuBar.hpp"
#include "WidgetContainer.hpp"

namespace pyramid
{
    using namespace simplex;
    using namespace simplex::sdl;

    MenuBar::MenuBar(string name)
    : Widget{name, AnchorPoint::TopLeft, width, MenuBarHeight, DockLocation::Top, Menu::BackgroundColor}, 
    menus{false}, activated{false}
    {
        gainedWindowFocus.connect(&MenuBar::windowFocusGained, this);
        lostWindowFocus.connect(&MenuBar::windowFocusLost, this);
        mouseDown.connect(&MenuBar::handleMouseDown, this);
    }

    MenuBar::~MenuBar()
    {
        for(Tuple<Menu*, int, int>* menu : menus)
        {
            delete menu->at<0>();
            delete menu;
        }
    }
    
    void MenuBar::draw(int parentCanvasWidth, int parentCanvasHeight)
    {
        width = parentCanvasWidth;
        newCanvas();
        getCanvas().fillRect(RGBColor{217, 217, 217}, 0, 0, width, height);
        int widthOffset = 0;
        int heightOffset = 0;
        int menusSize = menus.size();
        for(int loop = 0; loop < menusSize; loop++)
        {
            Tuple<Menu*, int, int>* menuGroup = menus[loop];
            Menu* menu = menuGroup->at<0>();
            menu->draw(canvas->width, canvas->height);
            heightOffset = (height - menu->height) / 2;
            menuGroup->at<1>(widthOffset);
            menuGroup->at<2>(heightOffset);
            canvas->copyToCanvas(menu->getCanvas(), widthOffset, heightOffset);
            widthOffset += menu->width;
        }
    }

    Menu& MenuBar::addMenu(string menuName)
    {
        Menu* menu = new Menu{menuName};
        menus.add(new Tuple<Menu*, int, int>{menu, 0, 0});
        menu->initWidget(*canvas);
        return *menu;
    }

    void MenuBar::windowFocusGained()
    {
        for(Tuple<Menu*, int, int>* menuGroup : menus)
            menuGroup->at<0>()->windowHasFocus = true;
    }
    void MenuBar::windowFocusLost()
    {
        for(Tuple<Menu*, int, int>* menuGroup : menus)
        {
            menuGroup->at<0>()->deactivate.emit();
            menuGroup->at<0>()->windowHasFocus = false;
        }
    }

    void MenuBar::handleMouseDown(int xPosition, int yPosition, MouseButton mouseButton)
    {
        for(Tuple<Menu*, int, int>* menuGroup : menus)
        {
            Menu* menu = menuGroup->at<0>();
            int menuXPosition = menuGroup->at<1>();
            int menuYPosition = menuGroup->at<2>();
            int menuWidth = menu->width;
            int menuHeight= menu->height;
            if(xPosition >= menuXPosition 
                && yPosition >= menuYPosition 
                && xPosition <= menuXPosition + menuWidth 
                && yPosition <= menuYPosition + menuHeight)
            {
                int modifiedXPosition = xPosition - menuXPosition;
                int modifiedYPosition = yPosition - menuYPosition;
                menu->mouseDown.emit(modifiedXPosition, modifiedYPosition, mouseButton);
            }
        }
    }
}