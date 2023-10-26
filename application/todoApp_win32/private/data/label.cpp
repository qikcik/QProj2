#include "data/label.hpp"
#include "data/window.hpp"

GEN_QOBJ_STATIC_DEF(Label,Widget,{
    GEN_INS_DEF_FIELD_ENTRY(Label, text),
})

void Label::registerInWindow(Window* in_window)
{
    hmenu = 0;
    hwnd = CreateWindowEx( 0, "EDIT", text.c_str(), WS_VISIBLE | WS_CHILD | SS_LEFT| ES_READONLY,
                   rect.value.x, rect.value.y, rect.value.w, rect.value.h,
                    in_window->getHwnd(), nullptr, in_window->getHInstance(), nullptr );
}

void Label::setText(const std::string& in_string)
{
    text = in_string;
    if(hwnd)
        SetWindowText(hwnd, in_string.c_str());
}
