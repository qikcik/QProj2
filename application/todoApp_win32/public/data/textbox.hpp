#pragma once
#include "qObjDef.hpp"
#include "structMacros.hpp"
#include <windows.h>

#include "data/widget.hpp"

GEN_QOBJ(Textbox,Widget)
{
GEN_QOBJ_BODY(Textbox,Widget)
GEN_QOBJ_DEF_CONSTRUCTOR_AND_DESTRUCTOR(Textbox,Widget)
public:
    void setText(const std::string& in_string);
    const std::string& getText();

    std::function<void(WeakPtr<Textbox>)> onChange;

    void registerInWindow(Window* in_window) override;
    void receivedCommand() override;
protected:
    std::string text;
};