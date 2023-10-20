#pragma once
#include "qObjDef.hpp"
#include "structMacros.hpp"
#include <windows.h>

#include "data/widget.hpp"

GEN_QOBJ(Button,Widget)
{
    GEN_QOBJ_BODY(Button,Widget)
    GEN_QOBJ_DEF_CONSTRUCTOR_AND_DESTRUCTOR(Button,Widget)
public:
    void setText(const std::string& in_string);
    std::function<void(WeakPtr<Widget>)> onClick;

    void registerInWindow(Window* in_window) override;
    void receivedCommand() override;
protected:
    std::string text;
};
