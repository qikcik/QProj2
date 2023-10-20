#pragma once
#include "qObjDef.hpp"
#include "structMacros.hpp"
#include <windows.h>

#include "data/widget.hpp"


class Window;
GEN_QOBJ(PropertyViewer,QObj)
{
GEN_QOBJ_BODY(PropertyViewer,QObj)
GEN_QOBJ_DEF_CONSTRUCTOR_AND_DESTRUCTOR(PropertyViewer,QObj)
public:
    void construct(WeakPtr<Window> in_window, WeakPtr<QObj> in_obj);
protected:
    WeakPtr<QObj> obj;
    WeakPtr<Window> window;

    bool tmpBlocking {false};
};