#include "data/button.hpp"
#include "data/window.hpp"

GEN_QOBJ_STATIC_DEF(Button,Widget,{
    GEN_INS_DEF_FIELD_ENTRY(Button, text),
})

void Button::registerInWindow(Window* in_window)
{
    hmenu = (HMENU)in_window->getNewHMENUIdx();
    hwnd = CreateWindowEx( 0, "BUTTON", text.c_str(), WS_CHILD | WS_VISIBLE,
                    rect.x, rect.y, rect.w, rect.h,
                    in_window->getHwnd(),hmenu, in_window->getHInstance(), nullptr );
}

#include <iostream>
void Button::receivedCommand()
{
    if(!onClick) return;
    onClick(selfPtr.cast<Button>());
}

void Button::setText(const std::string& in_string)
{
    text = in_string;
    if(hwnd)
        SetWindowText(hwnd, in_string.c_str());
}
