// windowsAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Common.h"
#include "windowsAPI.h"
#include "Application.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, WNDPROC wndProc, LPCWSTR windowname);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    AtlasWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 메모리 누수를 체크해주는 함수
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(363);

    // 1. wndclass 정의 윈도우의 기반(여러가지 속성)이되는 클래스를 정의해준다.
    // 
    // 2. 메모리상에우니도우를 할당해야한다. (CreatWindow)
    // 
    // 3. Showwindow 함수를 통해서 윈도우가 화면에 보여진다. (update window)
    // 
    // 4. winclass 정의할때 넣어준 함수포인터에 넣어준 loop (wndproc) 매 프레임마다 실핸한다. wndproc-(우리가 제어할 부분이다)

    // 5. 윈도우즈는 크게 3가지 라이브러리로 이루어져 있는데.
    // 메모리를 관리하고 실행시키는 KERNEL 커널
    // 유저 인터페이스와 관리하는 USER
    // 화면처리와 그래픽을 담당하는 GDI 로 이루어져있다.




    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, WndProc, szWindowClass);
    MyRegisterClass(hInstance, AtlasWndProc,L"AtlasWindow");

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSAPI));

    MSG msg;

    // GetMaessage : 프로세스에 발생한 메시지를 메세지 큐에서 꺼내서내옴
    // 메세지가 있을때만 메세지를 꺼내온다.
    // 메세지 case 함수를 호출해준다.
    
    
    // PeekMessage : 발생한 메세지를 가져 올때 메세지큐에서 따로 제거해줘야한다.
    // 메세지큐에 메세지가 들어있는 유/무에 관계없이 함수가 리턴된다.



    // 기본 메시지 루프입니다:
    while (1)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 게임 실행
            sw::Application::GetInstance().Tick();
        }
    }

    // 종료가 되었을때
    if (WM_QUIT == msg.message)
    {
        // 메모리 해제 작업
        sw::Application::GetInstance().Clear();
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance, WNDPROC wndProc, LPCWSTR windowName)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    // 생성할 윈도우의 속성
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = wndProc; //함수포인터
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSAPI)); // 아이콘모양
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); // 마우스 커서모양
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // 배겨 색
    wcex.lpszMenuName   = nullptr;  /*MAKEINTRESOURCEW(IDC_WINDOWSAPI);*/ // 창이름  
    wcex.lpszClassName  = windowName; // 프로그램 클래스이름
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   
   WindowData windowData;
   windowData.width = 1600;
   windowData.height = 900;


   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, // - 창스타일
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   //  창시작 위지 // 창의 가로세로 크기  //-부모핸들 - 메뉴 //- 메인핸들 - 구조체번지수

   windowData.hWnd = hWnd;
   windowData.hdc = nullptr;

   if (!hWnd)
   {
      return FALSE;
   }

   SetWindowPos(hWnd, nullptr, 0, 0, windowData.width, windowData.height, 0);
   ShowWindow(hWnd, nCmdShow); // 생성한 윈도우를 그려주는 함수
   UpdateWindow(hWnd);         // 윈도우창 업데이트

   sw::Application::GetInstance().Initialize(windowData);

   return TRUE;

   WindowData atlasWindowdata;
   hWnd = CreateWindowW(L"AtlasWindow", szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   atlasWindowdata.hWnd = hWnd;

   sw::Application::GetInstance().initializeAtlasWindow(atlasWindowdata);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

#include "SceneManager.h"
#include "Scene.h"
#include "ToolScene.h"
#include "TilePalette.h"
#include "Image.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 무효화 영역 발생시키기 ( WM_PAINT 메세지를 호출해주겠다)
    //InvalidateRect(hWnd, nullptr, false);

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;

            case ID_SAVE:
            {
                sw::Scene* scene = sw::SceneManager::GetInstance()->GetPlayScene();
                sw::ToolScene* toolScene = dynamic_cast<sw::ToolScene*>(scene);
                toolScene->SaveTilePalette();
            }
                break;

            case ID_LOAD:
            {
                sw::Scene* scene = sw::SceneManager::GetInstance()->GetPlayScene();
                sw::ToolScene* toolScene = dynamic_cast<sw::ToolScene*>(scene);
                toolScene->LoadTilePalette();
            }
                break;

            case IDM_EXIT:
                //DestroyWindow(hWnd);
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

            // 스톡오브젝트
            // 화면 지우기
            
            HBRUSH hClearBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
            HBRUSH oldClearBrush = (HBRUSH)SelectObject(hdc, hClearBrush);
            Rectangle(hdc, -1, -1, 1921, 1081);
            SelectObject(hdc, oldClearBrush);


            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);

            // DC 정리
            // 1. PEN BRUSH 핸들을 선언한다.
            // 2. GDI 오브젝트를 생성해준다.
            // 3. 생선된 오브젝트로 hdc 세팅해줘야한다. selectobject
            
            // 사용하고
            // 기존의 오브젝트로 되돌린다 (해제)
            // 핸들을 삭제한다.
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

// 정보 대화 상자의 메시지 처리기입니다.
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
