#include "data/window.hpp"
#include <windows.h>
#include "data/button.hpp"
#include "data/label.hpp"
#include "data/textbox.hpp"
#include <fstream>
#include "converter.hpp"
#include "fieldType/fields.hpp"

GEN_QSTRUCT(App)
{
GEN_QSTRUCT_BODY(App)
public:
    DynamicArray<OwnerPtr<Window>> windows {};
};

GEN_QSTRUCT_STATIC_DEF(App,{
    GEN_INS_DEF_FIELD_ENTRY(App, windows),
})

OwnerPtr<Window> CreateWindoww()
{
    OwnerPtr<Window> res = OwnerPtr<Window>::CreateWithInstance( Window::staticDef );
    auto ptr = res.getPtr();

    auto button = OwnerPtr<Button>::CreateWithInstance( Button::staticDef );
    auto lbl = OwnerPtr<Label>::CreateWithInstance( Label::staticDef );
    auto txt = OwnerPtr<Textbox>::CreateWithInstance( Textbox::staticDef );
    auto txtWeak = txt.getWeak();
    auto lblWeak = lbl.getWeak();


    button.getPtr()->rect = ScreenRectangle{{},0,0,100,100};
    button.getPtr()->setText("Click!");
    button.getPtr()->onClick = [lblWeak,txtWeak](auto button) mutable {
        auto val = std::stoi(txtWeak.getPtr()->getText());
        txtWeak.getPtr()->setRect({{},val,val,100,100});
    };

    lbl.getPtr()->setText("Dupa Dupa 123");
    lbl.getPtr()->rect = ScreenRectangle{{},200,400,100,100};

    txt.getPtr()->setText("...");
    txt.getPtr()->rect = ScreenRectangle{{},100,100,100,100};

    ptr->addWidget( std::move(button) );
    ptr->addWidget( std::move(lbl) );
    ptr->addWidget( std::move(txt) );

    return std::move(res);
}
#include "dynamicArray.tpp"
#include "data/propertyViewer.hpp"


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    App app;
//    {
//        std::ifstream file("layout.json");
//        std::stringstream stream{};
//        stream << file.rdbuf();
//        Converter().jsonToQStruct(std::get<json::Object>(json::Parser().parse(stream.str())), App::staticDef, &app);
//    }

    OwnerPtr<Window> res = OwnerPtr<Window>::CreateWithInstance( Window::staticDef );
    auto ptr = res.getPtr();
    auto txt = OwnerPtr<Textbox>::CreateWithInstance( Textbox::staticDef );
    auto txtWeak = txt.getWeak();

    txt.getPtr()->setText("...");
    txt.getPtr()->rect = ScreenRectangle{{},0,0,100,20};

    ptr->addWidget( std::move(txt) );
    auto resWeak = res.getWeak();

    app.windows.push_back(std::move(res));



    OwnerPtr<Window> aaa = OwnerPtr<Window>::CreateWithInstance( Window::staticDef );

    OwnerPtr<PropertyViewer> prop;
    prop.createInstance(PropertyViewer::staticDef);
    prop.getPtr()->construct(aaa,txtWeak);
    app.windows.push_back(std::move(aaa));

    for(auto& it : app.windows)
    {
        it.getPtr()->registerWindowClass(hInstance,nCmdShow);
    }

    MSG msg;
    while( GetMessage( &msg, nullptr, 0, 0 ) )
    {
        txtWeak.getPtr()->setText(txtWeak.getPtr()->getText());
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }

    std::ofstream file {};
    file.open ( "layout.json");
    auto json = Converter().qstructToJson(&app, App::staticDef);
    std::string source = json.stringify();
    file << source;

    return msg.wParam;
}