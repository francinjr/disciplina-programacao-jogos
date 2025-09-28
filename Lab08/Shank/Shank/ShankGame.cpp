/**********************************************************************************
// ShankGame
//
// Criação:     20 Set 2011
// Atualização: 20 Mai 2025
// Compilador:  Visual C++ 2022
//
// Descrição:   O programa testa a nova organização dos sprites 
//              através da classe base Object.
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Resources.h"
#include "Shank.h"

// ------------------------------------------------------------------------------

class ShankGame : public Game
{
private:
    Image  * img     = nullptr;         // imagem do logotipo
    Sprite * backg   = nullptr;         // sprite para fundo da cena
    Sprite * logo1   = nullptr;         // sprite do logotipo
    Sprite * logo2   = nullptr;         // sprite do logotipo
    Shank  * shank   = nullptr;         // objeto do personagem shank

public:
    void Init();                        // inicialização
    void Update();                      // atualização
    void Draw();                        // desenho
    void Finalize();                    // finalização
};

// ------------------------------------------------------------------------------

void ShankGame::Init()
{
    // carrega imagens do jogo
    img = new Image("Resources/Logo.png");

    // cria sprites
    logo1 = new Sprite(img);
    logo2 = new Sprite(img);
    backg = new Sprite("Resources/Background.jpg");

    // cria objeto do jogo
    shank = new Shank();
}

// ------------------------------------------------------------------------------

void ShankGame::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza objetos
    shank->Update();
} 

// ------------------------------------------------------------------------------

void ShankGame::Draw()
{
    // desenha sprites
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    logo1->Draw(230.0f, 125.0f, Layer::UPPER);
    logo2->Draw(590.0f, 515.0f, Layer::LOWER);

    // desenha objetos
    shank->Draw();
}

// ------------------------------------------------------------------------------

void ShankGame::Finalize()
{
    // descarrega imagens
    delete img;

    // libera sprites
    delete backg;    
    delete logo1;
    delete logo2;

    // libera objetos da memória
    delete shank;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 600);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Shank Game");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);

    // inicia o jogo
    int exit = engine->Start(new ShankGame());

    // destrói o motor
    delete engine;

    // sai do jogo
    return exit;
}

// ----------------------------------------------------------------------------

