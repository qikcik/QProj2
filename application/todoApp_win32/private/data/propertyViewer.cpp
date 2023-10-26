
#include "data/propertyViewer.hpp"
#include "fieldType/fields.hpp"
#include "data/window.hpp"

#include "data/label.hpp"
#include "data/textbox.hpp"
#include "data/groupbox.hpp"


GEN_QOBJ_STATIC_DEF(PropertyViewer,QObj,{
    GEN_INS_DEF_FIELD_ENTRY(PropertyViewer, window),
    GEN_INS_DEF_FIELD_ENTRY(PropertyViewer, obj),
})

#include <iostream>


void dumpSimple(WeakPtr<Window>& in_window, WeakPtr<QObj>& in_obj, const QIns* objPtr, int& y, Field* fieldIt,WeakPtr<PropertyViewer> self)
{
    if( auto asInt =  dynamic_cast<const IntField*>(fieldIt->type.getPtr()) )
    {
        auto value = *fieldIt->getValuePtr<int>((QIns*) objPtr);
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
        y += 30;
    }
    if( auto asObservable =  dynamic_cast<const ObservableField*>(fieldIt->type.getPtr()) )
    {
        if( auto asString =  dynamic_cast<const StdStringField*>( asObservable->valueType.getPtr()) )
        {
            auto value = fieldIt->getValuePtr<std::string>((QIns*) objPtr);
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
            textbox.getPtr()->onChange = [self,fieldName,in_obj](auto in_arg) mutable{
                auto field = in_obj.getPtr()->objDef.getPtr()->getField(fieldName);
                auto a = field->getValuePtr<Observable<std::string>>(in_obj.getPtr());

                self.getPtr()->tmpBlocking = true;
                a->value = in_arg.getPtr()->getText();
                a->notify();
                self.getPtr()->tmpBlocking = false;
            };

            auto a = fieldIt->getValuePtr<Observable<std::string>>(in_obj.getPtr());
            a->add([fieldIt,in_obj,self,weakTextbox]() mutable {
                if(!self.getPtr()->tmpBlocking)
                {
                    auto val = fieldIt->getValuePtr<std::string>(in_obj.getPtr());
                    weakTextbox.getPtr()->setText(*val);
                }
            });

            in_window.getPtr()->addWidget(std::move(label));
            in_window.getPtr()->addWidget(std::move(textbox));
            y += 30;
        }
    }
}




void PropertyViewer::construct(WeakPtr<Window>& in_window, WeakPtr<QObj> in_obj)
{
    window = in_window;
    obj = in_obj;

    auto objPtr = obj.getPtr();
    auto objDefPtr = objPtr->objDef.getPtr();
    int y = 5;
    for(auto fieldIt : objDefPtr->getAllFields())
    {
        dumpSimple(window, in_obj, objPtr, y, fieldIt,selfPtr.cast<PropertyViewer>());
        if( auto asObservable =  dynamic_cast<const ObservableField*>(fieldIt->type.getPtr()) )
        {
            auto observablePtr = fieldIt->getValuePtr<uint8_t>(objPtr);
            if( auto asQStruct =  dynamic_cast<const QStructField*>( asObservable->valueType.getPtr()))
            {
                auto startY = y;
                y+=30;
                auto insPtr = reinterpret_cast<QIns*>(observablePtr);
                for(auto innerIt : asQStruct->type.getPtr()->getAllFields())
                {
                    if( auto asInt =  dynamic_cast<const IntField*>(innerIt->type.getPtr()) )
                    {
                        auto value = *innerIt->getValuePtr<int>(insPtr);
                        OwnerPtr<Label> label;
                        label.createInstance(Label::staticDef);
                        label.getPtr()->setText(innerIt->name);
                        label.getPtr()->setRect({{},20,y,100,20});

                        OwnerPtr<Textbox> textbox;
                        textbox.createInstance(Textbox::staticDef);
                        textbox.getPtr()->setText(std::to_string(value));
                        textbox.getPtr()->setRect({{},120,y,100,20});

                        textbox.getPtr()->onChange = [=](WeakPtr<Textbox> in_arg) mutable{
                            *innerIt->getValuePtr<int>(insPtr) = std::stoi(in_arg.getPtr()->getText());
                            auto arr = reinterpret_cast<DynamicArray<std::function<void()>>*>(observablePtr + asObservable->listenersOffset);
                            for(auto& it : *arr)
                            {
                                it();
                            }
                        };

                        window.getPtr()->addWidget(std::move(label));
                        window.getPtr()->addWidget(std::move(textbox));
                        y += 25;
                    }
                }

                auto gr = OwnerPtr<Groupbox>::CreateWithInstance( Groupbox::staticDef );
                gr.getPtr()->setText(fieldIt->name+" ("+asQStruct->type.getPtr()->name+")");
                gr.getPtr()->rect.value = ScreenRectangle{{},10,startY,220,y-startY};
                window.getPtr()->addWidget( std::move(gr) );
                y += 5;

            }

        }
    }
}