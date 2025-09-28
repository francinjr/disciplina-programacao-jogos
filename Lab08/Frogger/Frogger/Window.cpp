/**********************************************************************************
// Window (Código Fonte)
// 
// Criação:     19 Mai 2007
// Atualização: 19 Mai 2025
// Compilador:  Visual C++ 2022
//
// Descrição:   A classe abstrai todos os detalhes de configuração de
//              uma janela para um jogo. 
//
**********************************************************************************/

#include "Window.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe
bool  Window::windowKeys[256] = { 0 };               // estado do teclado/mouse
bool  Window::windowCtrl[256] = { 0 };               // controle de teclado/mouse
int   Window::windowMouseX = 0;                      // posição do mouse no eixo x
int   Window::windowMouseY = 0;                      // posição do mouse no eixo y
float Window::windowAspectRatio = 0;                 // aspect ratio da janela
int   Window::screenWidth = 0;                       // largura da tela
int   Window::screenHeight = 0;                      // altura da tela

long  Window::monitorX = 0;                          // posição x do monitor no desktop virtual
long  Window::monitorY = 0;                          // posição y do monitor no desktop virtual
uint  Window::screenDpi = 0;                         // dpi atual da tela
float Window::windowScale = 0;                       // escala da janela para o dpi atual

// -------------------------------------------------------------------------------
// Construtor

Window::Window()
{
    // adiciona suporte a monitores com alto dpi
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    screenDpi         = GetDpiForSystem();                                  // dpi da tela
    windowScale       = screenDpi / float(USER_DEFAULT_SCREEN_DPI);         // escala da janela

    hInstance         = GetModuleHandle(NULL);                              // identificador da aplicação
    windowHandle      = 0;                                                  // identificador da janela do jogo                 
    screenWidth       = GetSystemMetricsForDpi(SM_CXSCREEN, screenDpi);     // largura da tela
    screenHeight      = GetSystemMetricsForDpi(SM_CYSCREEN, screenDpi);     // altura da tela
    windowWidth       = screenWidth;                                        // janela ocupa toda a tela 
    windowHeight      = screenHeight;                                       // janela ocupa toda a tela
    windowAspectRatio = windowWidth / float(windowHeight);                  // aspect ratio da janela
    windowIcon        = LoadIcon(NULL, IDI_APPLICATION);                    // ícone padrão de uma aplicação
    windowCursor      = LoadCursor(NULL, IDC_ARROW);                        // cursor padrão de uma aplicação
    windowColor       = RGB(0,0,0);                                         // cor de fundo padrão é preta
    windowTitle       = string("Windows Game");                             // título padrão da janela
    windowStyle       = WS_POPUP | WS_VISIBLE;                              // estilo para tela cheia
    windowMode        = FULLSCREEN;                                         // modo padrão é tela cheia
    windowPosX        = 0;                                                  // posição inicial da janela no eixo x
    windowPosY        = 0;                                                  // posição inicial da janela no eixo y
    windowCenterX     = windowWidth/2.0f;                                   // centro da janela no eixo x
    windowCenterY     = windowHeight/2.0f;                                  // centro da janela no eixo y
}

// -------------------------------------------------------------------------------

void Window::Mode(int mode)
{
    windowMode = mode;

    if (mode == WINDOWED)
    {
        // modo em janela 
        windowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
        windowStyle -= WS_MAXIMIZEBOX;
    }
    else
    {
        // modo em tela cheia ou sem bordas
        windowStyle = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE; 
    } 
}

// -------------------------------------------------------------------------------

void Window::Size(int width, int height)
{ 
    // window size
    windowWidth = width; 
    windowHeight = height;

    // aspect ratio da janela
    windowAspectRatio = windowWidth / float(windowHeight);

    // calcula a posição do centro da janela
    windowCenterX = windowWidth / 2.0f;
    windowCenterY = windowHeight / 2.0f;

    // ajusta a posição da janela para o centro da tela
    windowPosX = GetSystemMetrics(SM_CXSCREEN)/2 - windowWidth/2;
    windowPosY = GetSystemMetrics(SM_CYSCREEN)/2 - windowHeight/2;
}

// -------------------------------------------------------------------------------

bool Window::KeyPress(int vkcode)
{
    if (windowCtrl[vkcode])
    {
        if (KeyDown(vkcode))
        {
            windowCtrl[vkcode] = false;
            return true;
        }
    }
    else if (KeyUp(vkcode))
    {
        windowCtrl[vkcode] = true;
    }

    return false;
}

// -------------------------------------------------------------------------------

bool Window::Create()
{
    WNDCLASSEX wndClass; 
    
    // definindo uma classe de janela chamada "GameWindow"
    wndClass.cbSize         = sizeof(WNDCLASSEX);
    wndClass.style          = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc    = Window::WinProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = windowIcon;
    wndClass.hCursor        = windowCursor; 
    wndClass.hbrBackground  = (HBRUSH) CreateSolidBrush(windowColor);
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = "GameWindow";
    wndClass.hIconSm        = windowIcon;

    // registrando "GameWindow"
    if (!RegisterClassEx(&wndClass))
        return false;

    // criando uma janela baseada na classe "GameWindow" 
    windowHandle = CreateWindowEx(
        NULL,                           // estilos extras
        "GameWindow",                   // nome da "window class"
        windowTitle.c_str(),            // título da janela
        windowStyle,                    // estilo da janela
        windowPosX, windowPosY,         // posição (x,y) inicial
        windowWidth, windowHeight,      // largura e altura da janela
        NULL,                           // identificador da janela pai
        NULL,                           // identificador do menu
        hInstance,                      // identificador da aplicação
        NULL);                          // parâmetros de criação

    // Ao usar o modo em janela é preciso levar em conta que as barras 
    // e bordas ocupam espaço na janela. O código abaixo ajusta o tamanho
    // da janela de forma que a área cliente do jogo fique no tamanho 
    // (windowWidth x windowHeight)

    if (windowMode == WINDOWED)
    {
        // retângulo com o tamanho da área cliente desejada
        RECT winRect = {0, 0, windowWidth, windowHeight};

        // ajusta o tamanho do retângulo
        AdjustWindowRectEx(&winRect,
            GetWindowStyle(windowHandle),
            GetMenu(windowHandle) != NULL,
            GetWindowExStyle(windowHandle));

        // novas dimensões da janela
        long width = long((winRect.right - winRect.left) * windowScale);
        long height = long((winRect.bottom - winRect.top) * windowScale);

        // atualiza posição da janela
        windowPosX = GetSystemMetrics(SM_CXSCREEN)/2 - width/2;
        windowPosY = GetSystemMetrics(SM_CYSCREEN)/2 - height/2;

        // atualiza aspect ratio com base nas novas dimensões da janela
        windowAspectRatio = width / float(height);

        // redimensiona janela com uma chamada a MoveWindow
        MoveWindow(
            windowHandle,     // identificador da janela
            windowPosX,       // posição x
            windowPosY,       // posição y
            width,            // largura
            height,           // altura
            TRUE);            // repintar
    }

    // retorna estado da inicialização (bem sucedida ou não)
    return (windowHandle ? true : false);
}

// -------------------------------------------------------------------------------

LRESULT CALLBACK Window::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        // tecla pressionada
    case WM_KEYDOWN:
        windowKeys[wParam] = true;
        return 0;

        // tecla liberada
    case WM_KEYUP:
        windowKeys[wParam] = false;
        return 0;

        // movimento do mouse
    case WM_MOUSEMOVE:
        windowMouseX = GET_X_LPARAM(lParam);
        windowMouseY = GET_Y_LPARAM(lParam);
        return 0;

        // botão esquerdo do mouse pressionado
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        windowKeys[VK_LBUTTON] = true;
        return 0;

        // botão do meio do mouse pressionado
    case WM_MBUTTONDOWN:
    case WM_MBUTTONDBLCLK:
        windowKeys[VK_MBUTTON] = true;
        return 0;

        // botão direito do mouse pressionado
    case WM_RBUTTONDOWN:
    case WM_RBUTTONDBLCLK:
        windowKeys[VK_RBUTTON] = true;
        return 0;

        // botão esquerdo do mouse liberado
    case WM_LBUTTONUP:
        windowKeys[VK_LBUTTON] = false;
        return 0;

        // botão do meio do mouse liberado
    case WM_MBUTTONUP:
        windowKeys[VK_MBUTTON] = false;
        return 0;

        // botão direito do mouse liberado
    case WM_RBUTTONUP:
        windowKeys[VK_RBUTTON] = false;
        return 0;

        // janela ganhou o foco
    case WM_SETFOCUS:
        Engine::Resume();
        return 0;

        // janela perdeu o foco
    case WM_KILLFOCUS:
        Engine::Pause();
        return 0;

    case WM_ENTERSIZEMOVE:
        // pausa durante movimentação ou redimensionamento
        Engine::Pause();
        return 0;

    case WM_EXITSIZEMOVE:
        // resume após movimentação ou redimensionamento
        Engine::Resume();
        return 0;

    case WM_SIZING:
    {
        // novas dimensões da janela
        RECT * rect = (LPRECT)lParam;
        uint width = rect->right - rect->left;
        uint height = rect->bottom - rect->top;

        // qual borda está sendo usada para redimensionar
        switch (wParam)
        {
        case WMSZ_TOPLEFT:
        case WMSZ_TOPRIGHT:
            // calcula altura para manter a proporção da janela
            height = uint(width / windowAspectRatio);
            rect->top = rect->bottom - height;

            // se a coordenada saiu da tela
            if (rect->top - monitorY < 0)
            {
                // limita o topo
                rect->top = monitorY + 0;

                // calcula altura com o novo limite
                height = rect->bottom - rect->top;

                // calcula largura para manter a proporção da janela
                width = uint(height * windowAspectRatio);

                // ajusta largura de acordo com o lado modificado
                if (wParam == WMSZ_TOPLEFT)
                    rect->left = rect->right - width;
                else
                    rect->right = rect->left + width;
            }
            break;

        case WMSZ_BOTTOMLEFT:
        case WMSZ_BOTTOMRIGHT:
        case WMSZ_LEFT:
        case WMSZ_RIGHT:
            // calcula altura para manter a proporção da janela
            height = uint(width / windowAspectRatio);
            rect->bottom = rect->top + height;

            // se a coordenada saiu da tela
            if (rect->bottom - monitorY > screenHeight)
            {
                // limita a coordenada inferior
                rect->bottom = monitorY + screenHeight;

                // calcula altura com o novo limite
                height = rect->bottom - rect->top;

                // calcula largura para manter a proporção da janela
                width = uint(height * windowAspectRatio);

                // ajusta largura de acordo com o lado modificado
                if (wParam == WMSZ_LEFT || wParam == WMSZ_BOTTOMLEFT)
                    rect->left = rect->right - width;
                else
                    rect->right = rect->left + width;
            }
            break;

        case WMSZ_BOTTOM:
        case WMSZ_TOP:
            // calcula largura para manter a proporção da janela
            width = uint(height * windowAspectRatio);
            rect->right = rect->left + width;

            // se a coordenada saiu da tela
            if (rect->right - monitorX > screenWidth)
            {
                // limita a coordenada direita
                rect->right = monitorX + screenWidth;

                // calcula largura com o novo limite
                width = rect->right - rect->left;

                // calcula altura para manter a proporção da janela
                height = uint(width / windowAspectRatio);

                // ajusta altura de acordo com o lado modificado
                if (wParam == WMSZ_TOP)
                    rect->top = rect->bottom - height;
                else
                    rect->bottom = rect->top + height;
            }
            break;
        }

        return TRUE;
    }

    case WM_DPICHANGED:
    {
        HWND hWnd = GetActiveWindow();

        // novo tamanho da janela
        RECT * rect = LPRECT(lParam);
        
        // novo dpi
        screenDpi = HIWORD(wParam);
        
        // escala para novo dpi
        windowScale = screenDpi / float(USER_DEFAULT_SCREEN_DPI);

        // redimensiona janela com uma chamada a MoveWindow
        MoveWindow(
            hWnd,                       // identificador da janela
            rect->left,                 // posição x
            rect->top,                  // posição y
            rect->right - rect->left,   // largura
            rect->bottom - rect->top,   // altura
            TRUE);                      // repintar

        // captura informações do monitor que contém a janela
        HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
        MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
        GetMonitorInfo(hMonitor, &monitorInfo);

        // atualiza tamanho da tela
        screenWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
        screenHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

        // atualiza coordenadas de origem do monitor 
        monitorX = monitorInfo.rcMonitor.left;
        monitorY = monitorInfo.rcMonitor.top;
        return 0;
    }

    // a janela foi destruida
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// -----------------------------------------------------------------------------
