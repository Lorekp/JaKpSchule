#pragma once
#include "SubGridElement.h"

class AssetManager;

class Straight :
    public SubGridElement
{
public:
    Straight(int side);//side 0 = n, 1 = e, 2 = s, 3 = w
};

