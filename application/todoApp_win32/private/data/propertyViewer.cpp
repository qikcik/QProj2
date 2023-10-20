
#include "data/propertyViewer.hpp"
#include "fieldType/fields.hpp"
#include "data/window.hpp"

#include "data/label.hpp"
#include "data/textbox.hpp"

GEN_QOBJ_STATIC_DEF(PropertyViewer,QObj,{
    GEN_INS_DEF_FIELD_ENTRY(PropertyViewer, window),
    GEN_INS_DEF_FIELD_ENTRY(PropertyViewer, obj),
})

#include <iostream>

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
        if( auto asObservable =  dynamic_cast<const ObservableField*>(fieldIt->type.getPtr()) )
        {
            if( auto asString =  dynamic_cast<const StdStringField*>( asObservable->valueType.getPtr()) )
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
                auto weakTextbox =textbox.getWeak();

                auto fieldName = fieldIt->name;
                auto self = selfPtr.cast<PropertyViewer>();
                textbox.getPtr()->onChange = [self,fieldName,in_obj](auto in_arg) mutable{
                    auto field = in_obj.getPtr()->objDef.getPtr()->getField(fieldName);
                    auto a = field->getValuePtr<Observable<std::string>>(in_obj.getPtr());

                    self.getPtr()->tmpBlocking = true;
                    a->value = in_arg.getPtr()->getText();
                    a->notify();
                    self.getPtr()->tmpBlocking = false;
                };

                auto a = fieldIt->getValuePtr<Observable<std::string>>(in_obj.getPtr());
                a->add([self,weakTextbox](auto& in_arg) mutable {
                    if(!self.getPtr()->tmpBlocking)
                        weakTextbox.getPtr()->setText(in_arg);
                });

                in_window.getPtr()->addWidget(std::move(label));
                in_window.getPtr()->addWidget(std::move(textbox));
            }
        }
        //y += 30;
    }
}

