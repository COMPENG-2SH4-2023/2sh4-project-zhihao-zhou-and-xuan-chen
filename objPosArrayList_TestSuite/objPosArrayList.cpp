#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    sizeArray = ARRAY_MAX_CAP;
    sizeList = 0;
    aList = new objPos[sizeArray];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (sizeList < sizeArray) 
    {
        for (int i = sizeList; i > 0; --i) {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;
        sizeList++;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList < sizeArray) 
    {
        aList[sizeList] = thisPos;
        sizeList++;
    }
}

void objPosArrayList::removeHead()
{
    if (sizeList > 0) 
    {
        for (int i = 0; i < sizeList - 1; ++i) 
        {
            aList[i] = aList[i + 1];
        }
        sizeList--;
    }    
}

void objPosArrayList::removeTail()
{
    if (sizeList > 0) 
    {
        sizeList--;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    if (sizeList > 0) 
    {
        returnPos = aList[0];
    }
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if (sizeList > 0) 
    {
        returnPos = aList[sizeList - 1];
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < sizeList) 
    {
        returnPos = aList[index];
    }
}