#include "data/textbox.hpp"
#include "data/window.hpp"

GEN_QOBJ_STATIC_DEF(Textbox,Widget,{
    GEN_INS_DEF_FIELD_ENTRY(Textbox, text),
})

void Textbox::registerInWindow(Window* in_window)
{
    hmenu = (HMENU)in_window->getNewHMENUIdx();
    hwnd = CreateWindowEx( 0, "EDIT", text.c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE,
                           rect.x, rect.y, rect.w, rect.h,
                           in_window->getHwnd(), hmenu, in_window->getHInstance(), nullptr );
}

void Textbox::setText(const std::string& in_string)
{
    text = in_string;
    if(hwnd)
        SetWindowText(hwnd, in_string.c_str());
}


void Textbox::receivedCommand()
{
    static CHAR buf[1024];
    GetWindowText(hwnd, buf, 1024);
    text = buf;
    if(onChange)
        onChange(selfPtr.cast<Textbox>());
}

const std::string& Textbox::getText()
{
    return text;
}
