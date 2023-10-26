#include "data/textbox.hpp"
#include "data/window.hpp"
#include "fieldType/fields.hpp"

GEN_QOBJ_STATIC_DEF(Textbox,Widget,{
    GEN_INS_DEF_FIELD_ENTRY(Textbox, text),
})

Textbox::Textbox(const WeakPtr<QObjDef>& in_derivedObjDef) : Widget(in_derivedObjDef)
{
    text.add( [&]() {
        if(hwnd && !blocking)
            SetWindowText(hwnd, text.value.c_str());
    });
}

void Textbox::registerInWindow(Window* in_window)
{
    auto self = selfPtr.cast<Textbox>();
//    text.add( [self](auto& val) {
//        //if(self.getPtr()->hwnd)
//        //SetWindowText(self.getPtr()->hwnd, val.c_str());
//    });

    hmenu = (HMENU)in_window->getNewHMENUIdx();
    hwnd = CreateWindowEx( 0, "EDIT", text.value.c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE,
                           rect.value.x, rect.value.y, rect.value.w, rect.value.h,
                           in_window->getHwnd(), hmenu, in_window->getHInstance(), nullptr );
}


void Textbox::setText(const std::string& in_string)
{
    text.value = in_string;
    text.notify();
}

void Textbox::receivedCommand()
{
    static CHAR buf[1024];
    GetWindowText(hwnd, buf, 1024);
    std::string str = buf;
    if(str != text.value)
    {
        text.value = str;

        blocking = true;
        text.notify();
        blocking = false;

        if(onChange)
            onChange(selfPtr.cast<Textbox>());
    }
}

const std::string& Textbox::getText()
{
    return text.value;
}
