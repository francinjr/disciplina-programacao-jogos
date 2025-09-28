/**********************************************************************************
// MsgBox
// 
// Cria��o:     06 Mai 2011
// Atualiza��o:	15 Abr 2025
// Compilador:	Visual C++ 2022
//
// Descri��o:	Exemplo de utiliza��o da fun��o MessageBox da API Win32.
//              A aplica��o utiliza GetSystemMetrics para pegar o tamanho
//              da tela, recurso muito �til para a programa��o de jogos.
//
**********************************************************************************/
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sstream>
using std::stringstream;

//-------------------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int resp = MessageBox(NULL, 
                          "Vamos calcular o tamanho da tela?",
                          "Mensagem", 
                          MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION) ;

    if (resp == IDYES)
    {
        int cxScreen = GetSystemMetrics(SM_CXSCREEN);
        int cyScreen = GetSystemMetrics(SM_CYSCREEN);

        stringstream text;
        text << "Resolu��o: " << cxScreen << " x " << cyScreen;
        
        MessageBox(NULL, 
                   text.str().c_str(), 
                   "Tamanho da Tela", 
                   MB_OK | MB_ICONINFORMATION);
    } else {

        MessageBox(NULL, 
                   "Um jogo deve conhecer o tamanho da tela!", 
                   "Mensagem", 
                   MB_OK | MB_ICONWARNING);
    }

    return 0 ;
}

//-------------------------------------------------------------------------------