#include "data/widget.hpp"
#include "fieldType/fields.hpp"

GEN_QOBJ_STATIC_DEF(Widget,QObj,{
    GEN_INS_DEF_FIELD_ENTRY(Widget, rect),
})

void Widget::setRect(const ScreenRectangle& in_rect)
{
    rect.value = in_rect;
    if(hwnd)
        SetWindowPos(hwnd, nullptr, rect.value.x,rect.value.y,rect.value.w,rect.value.h, 0);
}

Widget::Widget(const WeakPtr<QObjDef>& in_derivedObjDef) : QObj(in_derivedObjDef)
{
    rect.add([&](){
        SetWindowPos(hwnd, nullptr, rect.value.x,rect.value.y,rect.value.w,rect.value.h, 0);
    });
}
