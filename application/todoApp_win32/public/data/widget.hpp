#pragma once
#include "qObjDef.hpp"
#include "structMacros.hpp"
#include "rectangle.hpp"
#include <windows.h>
#include "observable.hpp"

class Window;

GEN_QOBJ(Widget,QObj)
{
    GEN_QOBJ_BODY(Widget,QObj)
public:
    explicit Widget(const WeakPtr<QObjDef>& in_derivedObjDef);
    ~Widget() override =default;

    Observable<ScreenRectangle> rect {};
    HMENU hmenu {};
    HWND hwnd {};

    void setRect(const ScreenRectangle& in_rect);

    virtual void registerInWindow(Window* in_window) {};
    virtual void receivedCommand() {};
};