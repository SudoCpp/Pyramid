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

#include "Canvas.hpp"
#include "Widget.hpp"

namespace pyramid
{
    using namespace simplex::sdl;

    Canvas::Canvas(Renderer& renderer, int width, int height) 
    : renderer{renderer}, width{width}, height{height}, texture{renderer.createTexture(width, height)}
    {}
    Canvas::~Canvas()
    {
        delete texture;
    }
    void Canvas::drawLine(RGBColor color, int point1x, int point1y, int point2x, int point2y)
    {
        renderer.setTarget(*texture);
        renderer.setColor(color.color);
        renderer.drawLine(point1x, point1y, point2x, point2y);
        renderer.setTarget();
    }
    void Canvas::drawRect(RGBColor color, int x, int y, int width, int height)
    {
        renderer.setTarget(*texture);
        renderer.setColor(color.color);
        renderer.drawRect(x, y, width, height);
        renderer.setTarget();
    }
    void Canvas::fillRect(RGBColor color, int x, int y, int width, int height)
    {
        renderer.setTarget(*texture);
        renderer.setColor(color.color);
        renderer.fillRect(x, y, width, height);
        renderer.setTarget();
    }
    void Canvas::copyToCanvas(Canvas& childCanvas, int xPosition, int yPosition)
    {
        renderer.setTarget(*texture);
        renderer.copyTexture(*(childCanvas.texture), xPosition, yPosition);
        renderer.setTarget();
    }
    Canvas* Canvas::createNewCanvas(int width, int height) const
    {
        return new Canvas(renderer, width, height);
    }

    void Canvas::drawText(RGBColor color, simplex::string fontFileName, int fontSize, int x, int y, simplex::string text)
    {
        renderer.setTarget(*texture);
        Font font{fontFileName, fontSize};
        renderer.drawText(color.color, font, x, y, text);
        renderer.setTarget();
    }

    void Canvas::GetTextSize(simplex::string fontFileName, int fontSize, const simplex::string& text, int& width, int& height)
    {
        Font font{fontFileName, fontSize};
        font.getSize(text, width, height);
    }

    void Canvas::getCanvasCoordinates(Widget& widget, int& xCoordinate, int& yCoordinate)
    {
        if(widget.anchorPoint == AnchorPoint::TopLeft)
        {
            xCoordinate = 0;
            yCoordinate = 0;
        }
        else if(widget.anchorPoint == AnchorPoint::TopCenter)
        {
            xCoordinate = (width - widget.width)/2;
            yCoordinate = 0;
        }
        else if(widget.anchorPoint == AnchorPoint::TopRight)
        {
            xCoordinate = width - widget.width;
            yCoordinate = 0;
        }
        else if(widget.anchorPoint == AnchorPoint::MiddleLeft)
        {
            xCoordinate = 0;
            yCoordinate = (height - widget.height)/2;
        }
        else if(widget.anchorPoint == AnchorPoint::MiddleCenter)
        {
            xCoordinate = (width - widget.width)/2;
            yCoordinate = (height - widget.height)/2;
        }
        else if(widget.anchorPoint == AnchorPoint::MiddleRight)
        {
            xCoordinate = width - widget.width;
            yCoordinate = (height - widget.height)/2;
        }
        else if(widget.anchorPoint == AnchorPoint::BottomLeft)
        {
            xCoordinate = 0;
            yCoordinate = height - widget.height;
        }
        else if(widget.anchorPoint == AnchorPoint::MiddleCenter)
        {
            xCoordinate = (width - widget.width)/2;
            yCoordinate = height - widget.height;
        }
        else if(widget.anchorPoint == AnchorPoint::MiddleRight)
        {
            xCoordinate = width - widget.width;
            yCoordinate = height - widget.height;
        }
    }
}