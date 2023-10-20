#pragma once
#include "qObjDef.hpp"
#include "structMacros.hpp"
#include "rectangle.hpp"
#include <windows.h>

class Window;

GEN_QOBJ(Widget,QObj)
{
    GEN_QOBJ_BODY(Widget,QObj)
    GEN_QOBJ_DEF_CONSTRUCTOR_AND_DESTRUCTOR(Widget,QObj)
public:
    ScreenRectangle rect {};
    HMENU hmenu {};
    HWND hwnd {};

    void setRect(const ScreenRectangle& in_rect);

    virtual void registerInWindow(Window* in_window) {};
    virtual void receivedCommand() {};
};