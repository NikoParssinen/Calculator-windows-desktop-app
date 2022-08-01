#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <atlstr.h>
#include <string>

std::wstring PLUS_SYMBOL = L"+";
std::wstring MINUS_SYMBOL = L"-";
std::wstring TIMES_SYMBOL = L"*";
std::wstring DIVIDE_SYMBOL = L"/";

struct {
    double number1;
    double number2;
    int chosenOperator; // 1 = "+", 2 = "-", 3 = "*", 4 = "/"
} calculations;

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Calculator");
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define ID_ONE 1
#define ID_TWO 2
#define ID_THREE 3
#define ID_FOUR 4
#define ID_FIVE 5
#define ID_SIX 6
#define ID_SEVEN 7
#define ID_EIGHT 8
#define ID_NINE 9
#define ID_ZERO 10
#define ID_PLUS 11
#define ID_MINUS 12
#define ID_TIMES 13
#define ID_DIVIDE 14
#define ID_EQUALS 15
#define ID_CLEAR 16
#define ID_EDIT 17

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Oops!"),
            _T("Call to RegisterClassEx failed!"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        275, 323,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Oops!"),
            _T("Call to CreateWindow failed!"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndEdit;
    HWND hwndButton;

    switch (message)
    {
    case WM_CREATE:

        // Text box
        hwndEdit = CreateWindowW(L"Edit", NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            10, 10, 235, 20, hWnd, (HMENU)ID_EDIT,
            NULL, NULL);


        // Number buttons
        hwndButton = CreateWindowW(L"button", L"1",
            WS_VISIBLE | WS_CHILD, 
            10, 35, 55, 55, hWnd, (HMENU)ID_ONE, 
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"2",
            WS_VISIBLE | WS_CHILD,
            70, 35, 55, 55, hWnd, (HMENU)ID_TWO,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"3",
            WS_VISIBLE | WS_CHILD,
            130, 35, 55, 55, hWnd, (HMENU)ID_THREE,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"4",
            WS_VISIBLE | WS_CHILD,
            10, 95, 55, 55, hWnd, (HMENU)ID_FOUR,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"5",
            WS_VISIBLE | WS_CHILD,
            70, 95, 55, 55, hWnd, (HMENU)ID_FIVE,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"6",
            WS_VISIBLE | WS_CHILD,
            130, 95, 55, 55, hWnd, (HMENU)ID_SIX,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"7",
            WS_VISIBLE | WS_CHILD,
            10, 155, 55, 55, hWnd, (HMENU)ID_SEVEN,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"8",
            WS_VISIBLE | WS_CHILD,
            70, 155, 55, 55, hWnd, (HMENU)ID_EIGHT,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"9",
            WS_VISIBLE | WS_CHILD,
            130, 155, 55, 55, hWnd, (HMENU)ID_NINE,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"0",
            WS_VISIBLE | WS_CHILD,
            70, 215, 55, 55, hWnd, (HMENU)ID_ZERO,
            NULL, NULL);


        // Operator buttons
        hwndButton = CreateWindowW(L"button", L"+",
            WS_VISIBLE | WS_CHILD,
            190, 35, 55, 55, hWnd, (HMENU)ID_PLUS,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"-",
            WS_VISIBLE | WS_CHILD,
            190, 95, 55, 55, hWnd, (HMENU)ID_MINUS,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"*",
            WS_VISIBLE | WS_CHILD,
            190, 155, 55, 55, hWnd, (HMENU)ID_TIMES,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"/",
            WS_VISIBLE | WS_CHILD,
            190, 215, 55, 55, hWnd, (HMENU)ID_DIVIDE,
            NULL, NULL);

        hwndButton = CreateWindowW(L"button", L"=",
            WS_VISIBLE | WS_CHILD,
            130, 215, 55, 55, hWnd, (HMENU)ID_EQUALS,
            NULL, NULL);


        // Clear button
        hwndButton = CreateWindowW(L"button", L"C",
            WS_VISIBLE | WS_CHILD,
            10, 215, 55, 55, hWnd, (HMENU)ID_CLEAR,
            NULL, NULL);

        break;

    case WM_COMMAND:

        // Numbers functionality
        if (LOWORD(wParam) == ID_ONE) {

            // read current number
            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);

            std::wstring compareToOperators(currentNumber);
            if (compareToOperators == PLUS_SYMBOL || 
                compareToOperators == MINUS_SYMBOL ||
                compareToOperators == TIMES_SYMBOL ||
                compareToOperators == DIVIDE_SYMBOL) // check if last action was operator -> start new number
            {
                // add number to display
                LPCTSTR number = L"1";
                SetWindowTextW(hwndEdit, number);
            }
            else 
            {
                // add digit to current number
                std::wstring ws(currentNumber);
                wchar_t addDigit[] = L"1";
                ws.push_back(*addDigit);
                LPCTSTR backToLPSTR = ws.c_str();
                SetWindowTextW(hwndEdit, backToLPSTR);
            }

        }

        if (LOWORD(wParam) == ID_TWO) {

            // read current number
            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);

            std::wstring compareToOperators(currentNumber);
            if (compareToOperators == PLUS_SYMBOL ||
                compareToOperators == MINUS_SYMBOL ||
                compareToOperators == TIMES_SYMBOL ||
                compareToOperators == DIVIDE_SYMBOL) // check if last action was operator -> start new number
            {
                // add number to display
                LPCTSTR number = L"2";
                SetWindowTextW(hwndEdit, number);
            }
            else
            {
                // add digit to current number
                std::wstring ws(currentNumber);
                wchar_t addDigit[] = L"2";
                ws.push_back(*addDigit);
                LPCTSTR backToLPSTR = ws.c_str();
                SetWindowTextW(hwndEdit, backToLPSTR);
            }

        }

        if (LOWORD(wParam) == ID_THREE) {

            // read current number
            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);

            std::wstring compareToOperators(currentNumber);
            if (compareToOperators == PLUS_SYMBOL ||
                compareToOperators == MINUS_SYMBOL ||
                compareToOperators == TIMES_SYMBOL ||
                compareToOperators == DIVIDE_SYMBOL) // check if last action was operator -> start new number
            {
                // add number to display
                LPCTSTR number = L"3";
                SetWindowTextW(hwndEdit, number);
            }
            else
            {
                // add digit to current number
                std::wstring ws(currentNumber);
                wchar_t addDigit[] = L"3";
                ws.push_back(*addDigit);
                LPCTSTR backToLPSTR = ws.c_str();
                SetWindowTextW(hwndEdit, backToLPSTR);
            }

        }

        if (LOWORD(wParam) == ID_FOUR) {

            // read current number
            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);

            std::wstring compareToOperators(currentNumber);
            if (compareToOperators == PLUS_SYMBOL ||
                compareToOperators == MINUS_SYMBOL ||
                compareToOperators == TIMES_SYMBOL ||
                compareToOperators == DIVIDE_SYMBOL) // check if last action was operator -> start new number
            {
                // add number to display
                LPCTSTR number = L"4";
                SetWindowTextW(hwndEdit, number);
            }
            else
            {
                // add digit to current number
                std::wstring ws(currentNumber);
                wchar_t addDigit[] = L"4";
                ws.push_back(*addDigit);
                LPCTSTR backToLPSTR = ws.c_str();
                SetWindowTextW(hwndEdit, backToLPSTR);
            }

        }

        if (LOWORD(wParam) == ID_FIVE) {

            // read current number
            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);

            std::wstring compareToOperators(currentNumber);
            if (compareToOperators == PLUS_SYMBOL ||
                compareToOperators == MINUS_SYMBOL ||
                compareToOperators == TIMES_SYMBOL ||
                compareToOperators == DIVIDE_SYMBOL) // check if last action was operator -> start new number
            {
                // add number to display
                LPCTSTR number = L"5";
                SetWindowTextW(hwndEdit, number);
            }
            else
            {
                // add digit to current number
                std::wstring ws(currentNumber);
                wchar_t addDigit[] = L"5";
                ws.push_back(*addDigit);
                LPCTSTR backToLPSTR = ws.c_str();
                SetWindowTextW(hwndEdit, backToLPSTR);
            }

        }

        if (LOWORD(wParam) == ID_SIX) {

            // read current number
            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);

            std::wstring compareToOperators(currentNumber);
            if (compareToOperators == PLUS_SYMBOL ||
                compareToOperators == MINUS_SYMBOL ||
                compareToOperators == TIMES_SYMBOL ||
                compareToOperators == DIVIDE_SYMBOL) // check if last action was operator -> start new number
            {
                // add number to display
                LPCTSTR number = L"6";
                SetWindowTextW(hwndEdit, number);
            }
            else
            {
                // add digit to current number
                std::wstring ws(currentNumber);
                wchar_t addDigit[] = L"6";
                ws.push_back(*addDigit);
                LPCTSTR backToLPSTR = ws.c_str();
                SetWindowTextW(hwndEdit, backToLPSTR);
            }

        }

        if (LOWORD(wParam) == ID_SEVEN) {

            // read current number
            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);

            std::wstring compareToOperators(currentNumber);
            if (compareToOperators == PLUS_SYMBOL ||
                compareToOperators == MINUS_SYMBOL ||
                compareToOperators == TIMES_SYMBOL ||
                compareToOperators == DIVIDE_SYMBOL) // check if last action was operator -> start new number
            {
                // add number to display
                LPCTSTR number = L"7";
                SetWindowTextW(hwndEdit, number);
            }
            else
            {
                // add digit to current number
                std::wstring ws(currentNumber);
                wchar_t addDigit[] = L"7";
                ws.push_back(*addDigit);
                LPCTSTR backToLPSTR = ws.c_str();
                SetWindowTextW(hwndEdit, backToLPSTR);
            }

        }

        if (LOWORD(wParam) == ID_EIGHT) {

            // read current number
            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);

            std::wstring compareToOperators(currentNumber);
            if (compareToOperators == PLUS_SYMBOL ||
                compareToOperators == MINUS_SYMBOL ||
                compareToOperators == TIMES_SYMBOL ||
                compareToOperators == DIVIDE_SYMBOL) // check if last action was operator -> start new number
            {
                // add number to display
                LPCTSTR number = L"8";
                SetWindowTextW(hwndEdit, number);
            }
            else
            {
                // add digit to current number
                std::wstring ws(currentNumber);
                wchar_t addDigit[] = L"8";
                ws.push_back(*addDigit);
                LPCTSTR backToLPSTR = ws.c_str();
                SetWindowTextW(hwndEdit, backToLPSTR);
            }

        }

        if (LOWORD(wParam) == ID_NINE) {

            // read current number
            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);

            std::wstring compareToOperators(currentNumber);
            if (compareToOperators == PLUS_SYMBOL ||
                compareToOperators == MINUS_SYMBOL ||
                compareToOperators == TIMES_SYMBOL ||
                compareToOperators == DIVIDE_SYMBOL) // check if last action was operator -> start new number
            {
                // add number to display
                LPCTSTR number = L"9";
                SetWindowTextW(hwndEdit, number);
            }
            else
            {
                // add digit to current number
                std::wstring ws(currentNumber);
                wchar_t addDigit[] = L"9";
                ws.push_back(*addDigit);
                LPCTSTR backToLPSTR = ws.c_str();
                SetWindowTextW(hwndEdit, backToLPSTR);
            }

        }

        if (LOWORD(wParam) == ID_ZERO) {

            // read current number
            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);

            std::wstring compareToOperators(currentNumber);
            if (compareToOperators == PLUS_SYMBOL ||
                compareToOperators == MINUS_SYMBOL ||
                compareToOperators == TIMES_SYMBOL ||
                compareToOperators == DIVIDE_SYMBOL) // check if last action was operator -> start new number
            {
                // add number to display
                LPCTSTR number = L"0";
                SetWindowTextW(hwndEdit, number);
            }
            else
            {
                // add digit to current number
                std::wstring ws(currentNumber);
                wchar_t addDigit[] = L"0";
                ws.push_back(*addDigit);
                LPCTSTR backToLPSTR = ws.c_str();
                SetWindowTextW(hwndEdit, backToLPSTR);
            }

        }


        // Operators functionality
        if (LOWORD(wParam) == ID_PLUS) {

            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);
            std::wstring ws(currentNumber);

            // store first number and the chosen operator
            double i = std::stoi(ws);
            calculations.number1 = i;
            calculations.chosenOperator = 1;

            LPCTSTR backToLPSTR = TEXT("+");
            SetWindowTextW(hwndEdit, backToLPSTR);

        }

        if (LOWORD(wParam) == ID_MINUS) {

            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);
            std::wstring ws(currentNumber);

            // store first number and the chosen operator
            double i = std::stoi(ws);
            calculations.number1 = i;
            calculations.chosenOperator = 2;

            LPCTSTR backToLPSTR = TEXT("-");
            SetWindowTextW(hwndEdit, backToLPSTR);

        }

        if (LOWORD(wParam) == ID_TIMES) {

            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);
            std::wstring ws(currentNumber);

            // store first number and the chosen operator
            double i = std::stoi(ws);
            calculations.number1 = i;
            calculations.chosenOperator = 3;

            LPCTSTR backToLPSTR = TEXT("*");
            SetWindowTextW(hwndEdit, backToLPSTR);

        }

        if (LOWORD(wParam) == ID_DIVIDE) {

            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);
            std::wstring ws(currentNumber);

            // store first number and the chosen operator
            double i = std::stoi(ws);
            calculations.number1 = i;
            calculations.chosenOperator = 4;

            LPCTSTR backToLPSTR = TEXT("/");
            SetWindowTextW(hwndEdit, backToLPSTR);
        }

        if (LOWORD(wParam) == ID_EQUALS) {

            LPWSTR currentNumber = new TCHAR[10];
            GetWindowTextW(hwndEdit, currentNumber, 10);
            std::wstring ws(currentNumber);

            // store second number and the chosen operator
            double i = std::stoi(ws);
            calculations.number2 = i;

            double answer = 0;
            if(calculations.chosenOperator == 1)
            {
                answer = calculations.number1 + calculations.number2;
            }
            else if (calculations.chosenOperator == 2)
            {
                answer = calculations.number1 - calculations.number2;
            }
            else if (calculations.chosenOperator == 3)
            {
                answer = calculations.number1 * calculations.number2;
            }
            else if (calculations.chosenOperator == 4)
            {
                answer = calculations.number1 / calculations.number2;
            }

            std::wstring ws2 = std::to_wstring(answer);
            LPCTSTR backToLPSTR = ws2.c_str();
            SetWindowTextW(hwndEdit, backToLPSTR);
        }


        // Clear functionality
        if (LOWORD(wParam) == ID_CLEAR) {

            calculations.number1 = NULL;
            calculations.number2 = NULL;
            calculations.chosenOperator = NULL;

            LPCTSTR lpstr = TEXT("");
            SetWindowTextW(hwndEdit, lpstr);
        }

        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}
