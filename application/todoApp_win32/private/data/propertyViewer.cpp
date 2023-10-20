
#include "data/propertyViewer.hpp"
#include "fieldType/fields.hpp"
#include "data/window.hpp"

#include "data/label.hpp"
#include "data/textbox.hpp"

GEN_QOBJ_STATIC_DEF(PropertyViewer,QObj,{
    GEN_INS_DEF_FIELD_ENTRY(PropertyViewer, window),
    GEN_INS_DEF_FIELD_ENTRY(PropertyViewer, obj),
})

void PropertyViewer::construct(WeakPtr<Window> in_window, WeakPtr<QObj> in_obj)
{
    window = std::move(in_window);
    obj = in_obj;

    auto objPtr = obj.getPtr();
    auto objDefPtr = objPtr->objDef.getPtr();
    int y = 0;
    for(auto fieldIt : objDefPtr->getAllFields())
    {
        if( auto asInt =  dynamic_cast<const IntField*>(fieldIt->type.getPtr()) )
        {
            auto value = *fieldIt->getValuePtr<int>(objPtr);
            OwnerPtr<Label> label;
            label.createInstance(Label::staticDef);
            label.getPtr()->setText(fieldIt->name);
            label.getPtr()->setRect({{},10,y,100,20});

            OwnerPtr<Textbox> textbox;
            textbox.createInstance(Textbox::staticDef);
            textbox.getPtr()->setText(std::to_string(value));
            textbox.getPtr()->setRect({{},110,y,100,20});

            in_window.getPtr()->addWidget(std::move(label));
            in_window.getPtr()->addWidget(std::move(textbox));
        }
        if( auto asString =  dynamic_cast<const StdStringField*>(fieldIt->type.getPtr()) )
        {
            auto value = fieldIt->getValuePtr<std::string>(objPtr);
            OwnerPtr<Label> label;
            label.createInstance(Label::staticDef);
            label.getPtr()->setText(fieldIt->name);
            label.getPtr()->setRect({{},10,y,100,20});

            OwnerPtr<Textbox> textbox;
            textbox.createInstance(Textbox::staticDef);
            textbox.getPtr()->setText(*value);
            textbox.getPtr()->setRect({{},110,y,100,20});

            auto fieldName = fieldIt->name;
            textbox.getPtr()->onChange = [fieldName,in_obj](auto in_arg) mutable{
                auto field = in_obj.getPtr()->objDef.getPtr()->getField(fieldName);
                *field->getValuePtr<std::string>(in_obj.getPtr()) = in_arg.getPtr()->getText();
            };



            in_window.getPtr()->addWidget(std::move(label));
            in_window.getPtr()->addWidget(std::move(textbox));
        }
        //y += 30;
    }
}

