#pragma once
#include "qObjDef.hpp"
#include "structMacros.hpp"
#include <windows.h>

#include "data/widget.hpp"

GEN_QOBJ(Label,Widget)
{
GEN_QOBJ_BODY(Label,Widget)
GEN_QOBJ_DEF_CONSTRUCTOR_AND_DESTRUCTOR(Label,Widget)
public:
    void setText(const std::string& in_string);
    void registerInWindow(Window* in_window) override;
protected:
    std::string text;
};