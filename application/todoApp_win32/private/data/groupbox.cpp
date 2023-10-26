#include "data/groupbox.hpp"
#include <windows.h>
#include <data/window.hpp>
#include <CommCtrl.h>

GEN_QOBJ_STATIC_DEF(Groupbox,Widget,{
    GEN_INS_DEF_FIELD_ENTRY(Groupbox, text),
    GEN_INS_DEF_FIELD_ENTRY(Groupbox, widgets),
})

void Groupbox::setText(const std::string& in_string)
{
    text = in_string;
}

void Groupbox::registerInWindow(Window* in_window)
{
    hwnd = CreateWindowEx(0, WC_BUTTON, text.c_str(), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, rect.value.x, rect.value.y, rect.value.w, rect.value.h, in_window->getHwnd(), nullptr, in_window->getHInstance(), nullptr);
}

void Groupbox::addWidget(OwnerPtr<Widget> in_widget)
{

}
