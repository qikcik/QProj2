#include "data/widget.hpp"
#include "fieldType/fields.hpp"

GEN_QOBJ_STATIC_DEF(Widget,QObj,{
    GEN_INS_DEF_FIELD_ENTRY(Widget, rect),
})

void Widget::setRect(const ScreenRectangle& in_rect)
{
    rect= in_rect;
    if(hwnd)
        SetWindowPos(hwnd, nullptr, rect.x,rect.y,rect.w,rect.h, 0);
}
