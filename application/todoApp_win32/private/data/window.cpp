#include "data/window.hpp"
#include "fieldType/fields.hpp"

std::unordered_map<HWND, Window*> Window::registered_windows{};

BEGIN_GEN_QOBJ_STATIC_DEF(Window,QObj)
DynamicArray<Field>
{
    GEN_INS_DEF_FIELD_ENTRY(Window, widgets),
},
DynamicArray<Method> {

}
END_GEN_QOBJ_STATIC_DEF()

Window* currentRegistering = nullptr;

#include <iostream>
bool Window::registerWindowClass(HINSTANCE in_hInstance, int nCmdShow)
{
    auto id = selfPtr.getId();
    auto classNameCStr = id.c_str();
    std::cout << classNameCStr << std::endl;

    winClass.cbSize = sizeof(WNDCLASSEX);
    winClass.style = 0;
    winClass.lpfnWndProc = Window::WndProc;
    winClass.cbClsExtra = 0;
    winClass.cbWndExtra = 0;
    winClass.hInstance = hInstance;
    winClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    winClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    winClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    winClass.lpszMenuName = nullptr;
    winClass.lpszClassName = classNameCStr;
    winClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    if (!RegisterClassEx(&winClass))
        return false;

    hInstance = in_hInstance;
    currentRegistering = this;
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, classNameCStr, "Window", WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, nullptr, nullptr, hInstance,
                          nullptr);
    currentRegistering = nullptr;
    if (hwnd == nullptr)
        return false;

    registered_windows[hwnd] = this;


    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);


    return true;
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* selfPtr = registered_windows[hwnd];

    if (currentRegistering) {
        selfPtr = currentRegistering;
        selfPtr->hwnd = hwnd;
    }

    switch (msg) {
        case WM_CREATE:

            for (auto& widgetIt: selfPtr->widgets) {
                widgetIt.getPtr()->registerInWindow(selfPtr);
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            for (auto& widgetIt: selfPtr->widgets) {
                if (widgetIt.getPtr()->hwnd == (HWND) lParam)
                    widgetIt.getPtr()->receivedCommand();
            }
            break;


        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

Window::Window(const WeakPtr<QObjDef>& in_derivedObjDef) : QObj(in_derivedObjDef)
{

}

Window::~Window()
{
    if (hwnd)
        registered_windows.erase(hwnd);
}

void Window::addWidget(OwnerPtr<Widget> in_widget)
{
    auto weak = in_widget.getWeak();
    widgets.push_back(std::move(in_widget));
    if (hwnd)
        weak.getPtr()->registerInWindow(this);

}

int Window::getNewHMENUIdx()
{
    lastHMENUIdx++;
    return lastHMENUIdx;
}
