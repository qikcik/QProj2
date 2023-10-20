#pragma once
#include "qInsDef.hpp"
#include "structMacros.hpp"


GEN_QSTRUCT(ScreenRectangle)
{
    GEN_QSTRUCT_BODY(ScreenRectangle)
public:
    int x {0};
    int y {0};
    int w {0};
    int h {0};
};