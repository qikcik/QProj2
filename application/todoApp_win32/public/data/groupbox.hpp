#pragma once
#include "qObjDef.hpp"
#include "structMacros.hpp"
#include <windows.h>

#include "data/widget.hpp"

GEN_QOBJ(Groupbox,Widget)
{
    GEN_QOBJ_BODY(Groupbox,Widget)
    GEN_QOBJ_DEF_CONSTRUCTOR_AND_DESTRUCTOR(Groupbox,Widget)
public:
    void setText(const std::string& in_string);
    void addWidget(OwnerPtr<Widget> in_widget);

    void registerInWindow(Window* in_window) override;
protected:
    std::string text;
    DynamicArray<OwnerPtr<Widget>> widgets;
};
