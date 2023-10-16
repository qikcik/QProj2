#include <windows.h>

LPCSTR ClassName = "Wolololo";
MSG Communicate;
HWND g_hButton;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

    // WYPEŁNIANIE STRUKTURY
    WNDCLASSEX wc;

    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
    wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = ClassName;
    wc.hIconSm = LoadIcon( nullptr, IDI_APPLICATION );

    // REJESTROWANIE KLASY OKNA
    if( !RegisterClassEx( & wc ) )
    {
        MessageBox( nullptr, "Wysoka Komisja odmawia rejestracji tego okna!", "Niestety...",
                    MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }

    // TWORZENIE OKNA
    HWND hwnd;
    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, ClassName, "Window", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, nullptr, nullptr, hInstance, nullptr );
    if( hwnd == nullptr )
    {
        MessageBox( nullptr, "Okno odmówiło przyjścia na świat!", "Ale kicha...", MB_ICONEXCLAMATION );
        return 1;
    }

    g_hButton = CreateWindowEx( 0, "BUTTON", "button", WS_CHILD | WS_VISIBLE,
                                  100, 100, 150, 30, hwnd, NULL, hInstance, NULL );
    DestroyWindow(g_hButton);
    ShowWindow( hwnd, nCmdShow ); // Pokaż okienko...
    UpdateWindow( hwnd );

    // Pętla komunikatów
    while( GetMessage( & Communicate, nullptr, 0, 0 ) )
    {
        TranslateMessage( & Communicate );
        DispatchMessage( & Communicate );
    }
    return Communicate.wParam;
}

// OBSŁUGA ZDARZEŃ
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_CLOSE:
            DestroyWindow( hwnd );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hwnd, msg, wParam, lParam );
    }

    return 0;
}