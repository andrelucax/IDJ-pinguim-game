#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);

    Rect SumVec2(Vec2 v);
    Rect SubVec2(Vec2 v);
    Vec2 CenterCoord();

    float DistRecs(Rect r);
    bool Contains(Vec2 v);
};

#endif