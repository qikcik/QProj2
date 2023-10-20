#pragma once
#include "qObjDef.hpp"
#include "structMacros.hpp"
#include <windows.h>
#include "data/widget.hpp"
#include <unordered_map>

GEN_QOBJ(Window,QObj)
{
    GEN_QOBJ_BODY(Window,QObj)
public:
    explicit Window(const WeakPtr<QObjDef>& in_derivedObjDef);
    ~Window() override;

    bool registerWindowClass(HINSTANCE in_hInstance,int nCmdShow);
    void addWidget(OwnerPtr<Widget> in_widget);

    HWND getHwnd() {return hwnd; };
    HINSTANCE getHInstance() {return hInstance; };

    int getNewHMENUIdx();

protected:
    DynamicArray<OwnerPtr<Widget>> widgets;

protected:
    WNDCLASSEX winClass {};
    HWND hwnd {};
    HINSTANCE hInstance {};
    int lastHMENUIdx = 0;

    static LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
    static std::unordered_map<HWND,Window*> registered_windows;
};