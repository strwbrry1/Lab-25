
#include "framework.h"
#include "Lab 25.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB25, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB25));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB25));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB25);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


void Triangle(HDC hdc, int cx, int cy, int size) {
    HPEN hPen;
    hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    SelectObject(hdc, hPen);

    MoveToEx(hdc, cx, cy + size, NULL);
    LineTo(hdc, cx - size, cy - size);
    LineTo(hdc, cx + size, cy - size);
    LineTo(hdc, cx, cy + size);

    DeleteObject(hPen);
}

void doubleTriangle(HDC hdc, int cx, int cy, int size) {
    HPEN hPen;
    hPen = CreatePen(PS_SOLID, 2, RGB(0, 125, 255));
    SelectObject(hdc, hPen);

    MoveToEx(hdc, cx - size / 2, cy - size / 2, NULL);
    LineTo(hdc, cx + size / 2, cy - size / 2);
    LineTo(hdc, cx - size, cy + size);
    LineTo(hdc, cx + size, cy + size);
    LineTo(hdc, cx - size / 2, cy - size / 2);

    DeleteObject(hPen);
}

void rhombus(HDC hdc, int cx, int cy, int size) {
    HPEN hPen;
    hPen = CreatePen(PS_SOLID, 2, RGB(0, 125, 255));
    SelectObject(hdc, hPen);

    MoveToEx(hdc, cx, cy - size, NULL);
    LineTo(hdc, cx + size, cy);
    LineTo(hdc, cx, cy + size);
    LineTo(hdc, cx - size, cy);
    LineTo(hdc, cx, cy - size);

    DeleteObject(hPen);
}

void star(HDC hdc, int cx, int cy, int size) {
    HPEN hPen;
    hPen = CreatePen(PS_SOLID, 2, RGB(255, 125, 0));
    SelectObject(hdc, hPen);

    MoveToEx(hdc, cx, cy - size, NULL);
    LineTo(hdc, cx + size / 4, cy - size / 4);
    LineTo(hdc, cx + size, cy);
    LineTo(hdc, cx + size / 4, cy + size / 4);
    LineTo(hdc, cx, cy + size);
    LineTo(hdc, cx - size / 4, cy + size / 4);
    LineTo(hdc, cx - size, cy);
    LineTo(hdc, cx - size / 4, cy - size / 4);
    LineTo(hdc, cx, cy - size);

    DeleteObject(hPen);
}


void recImg1_1(HDC hdc, int cx, int cy, int size) {
    Triangle(hdc, cx, cy, size);
    if (size < 10) {
        return;
    }
    recImg1_1(hdc, cx - size, cy, size / 2);
    recImg1_1(hdc, cx + size, cy, size / 2);
    recImg1_1(hdc, cx, cy - size, size / 2);
}

void recImg1_2(HDC hdc, int cx, int cy, int size) {
    Triangle(hdc, cx, cy, size);
    if (size < 10) {
        return;
    }
    recImg1_2(hdc, cx - size, cy - size, size / 2);
    recImg1_2(hdc, cx + size, cy - size, size / 2);
    recImg1_2(hdc, cx, cy + size, size / 2);
}

void recImg2_1(HDC hdc, int cx, int cy, int size) {
    doubleTriangle(hdc, cx, cy, size);
    if (size < 20) {
        return;
    }
    recImg2_1(hdc, cx - size, cy, size / 2);
    recImg2_1(hdc, cx + size, cy, size / 2);
    //recImg2_1(hdc, cx, cy - size, size / 2);
}

void recImg2_2(HDC hdc, int cx, int cy, int size) {
    doubleTriangle(hdc, cx, cy, size);
    if (size < 20) {
        return;
    }
    recImg2_2(hdc, cx - size / 2, cy - size / 2, size / 2);
    recImg2_2(hdc, cx + size / 2, cy - size / 2, size / 2);
    recImg2_2(hdc, cx + size, cy + size, size / 2);
    recImg2_2(hdc, cx - size, cy + size, size / 2);
}

void recImg3_1(HDC hdc, int cx, int cy, int size) {
    rhombus(hdc, cx, cy, size);
    if (size < 20) {
        return;
    }
    recImg3_1(hdc, cx + size, cy, size / 2);
    recImg3_1(hdc, cx - size, cy, size / 2);
    recImg3_1(hdc, cx, cy + size, size / 2);
    recImg3_1(hdc, cx, cy - size, size / 2);
}

void recImg4_1(HDC hdc, int cx, int cy, int size) {
    star(hdc, cx, cy, size);
    if (size < 20) {
        return;
    }
    recImg4_1(hdc, cx - size, cy - size, size / 2);
    recImg4_1(hdc, cx + size, cy + size, size / 2);
    recImg4_1(hdc, cx + size / 2, cy - size / 2, size / 2);
    recImg4_1(hdc, cx - size / 2, cy + size / 2, size / 2);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            //recImg1_2(hdc, 300, 300, 100);
            //recImg2_2(hdc, 400, 300, 100);
            //recImg3_1(hdc, 400, 300, 100);
            recImg4_1(hdc, 400, 300, 100);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
