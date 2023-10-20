#pragma once
#include "qObjDef.hpp"
#include "structMacros.hpp"
#include <windows.h>

#include "data/widget.hpp"
#include "observable.hpp"

GEN_QOBJ(Textbox,Widget)
{
GEN_QOBJ_BODY(Textbox,Widget)
public:

    explicit Textbox(const WeakPtr<QObjDef>& in_derivedObjDef);
    ~Textbox() override = default;

    void setText(const std::string& in_string);
    const std::string& getText();

    std::function<void(WeakPtr<Textbox>)> onChange;

    void registerInWindow(Window* in_window) override;
    void receivedCommand() override;
protected:
    Observable<std::string> text;
    bool blocking = false;
};