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

#include "TableContainer.hpp"

#define __class__ "pyramid::TableContainer"

namespace pyramid
{
    using namespace simplex;
    using namespace simplex::sdl;

    TableContainer::TableContainer(string name)
    : WidgetContainer(name, 0, 0)
    {}

    TableContainer::~TableContainer(){}

    void TableContainer::setPixelData(int parentCanvasValue, string dataType, 
        Array<string>& array, Array<int>& actualArray)
    {
        uint16_t absoluteValue = 0;
        uint16_t totalPercentage = 0;
        uint8_t totalStars = 0;

        for(simplex::string rowHeight : array)
            if(!rowHeight.contains("%") && !rowHeight.contains("*"))
                absoluteValue += rowHeight.toNumber<uint16_t>();
            else if(rowHeight.contains("%"))
                totalPercentage += rowHeight.subString(0, rowHeight.indexOf("%")).toNumber<uint16_t>();
            else
                totalStars++;

        if(totalPercentage > 100)
            throw Exception("Table Container named '" + name + "' has " + dataType + " that add up to over 100 percent.", __ExceptionParams__);

        uint16_t remainingPixels = parentCanvasValue - absoluteValue;
        uint16_t remainingPercentagePixels = (100-totalPercentage)/100 * remainingPixels;
        uint16_t starPixels = 0;
        if(totalStars > 0)
            starPixels = remainingPercentagePixels / totalStars;

        actualArray.clear();
        remainingPixels = parentCanvasValue;
        for(simplex::string rowHeight : array)
            if(!rowHeight.contains("%") && !rowHeight.contains("*"))
                actualArray.add(rowHeight.toNumber<uint16_t>());
            else if(rowHeight.contains("%"))
            {
                uint8_t rowPercentage = rowHeight.subString(0, rowHeight.indexOf("%")).toNumber<uint16_t>();
                actualArray.add(remainingPercentagePixels * (float)rowPercentage/100);
            }
            else
                actualArray.add(starPixels);
    }

    void TableContainer::setActualValues(int parentCanvasWidth, int parentCanvasHeight)
    {
        setPixelData(parentCanvasHeight, "row", rows, rowActual);
        setPixelData(parentCanvasWidth, "column", columns, columnActual);
    }

    void TableContainer::draw(int parentCanvasWidth, int parentCanvasHeight)
    {
        if(rows.size() == 0 || columns.size() == 0)
            throw Exception("Unable to draw TableContainer named '"+name+"' without rows and/or columns.", __ExceptionParams__);
        setActualValues(parentCanvasWidth, parentCanvasHeight);
        width = parentCanvasWidth;
        height = parentCanvasHeight;
    }
}

#undef __class__