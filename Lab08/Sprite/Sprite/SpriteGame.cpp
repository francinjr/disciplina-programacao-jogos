/**********************************************************************************
// SpriteGame
// 
// Criação:     09 Mai 2014
// Atualização: 20 Mai 2025
// Compilador:  Visual C++ 2022
//
// Descrição:   O programa carrega e desenha imagens opacas e transparentes,
//              demonstrando como usar as classes Image e Sprite com os novos
//              recursos de desenho de Sprites da classe Renderer
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

class SpriteGame : public Game
{
private:
    Sprite * backg   = nullptr;            // sprite do fundo de tela
    Sprite * shank   = nullptr;            // sprite do personagem 

    Image  * logoImg = nullptr;            // imagem do logotipo
    Sprite * logo1   = nullptr;            // sprite 1 do logotipo
    Sprite * logo2   = nullptr;            // sprite 2 do logotipo

    float x = 0, y = 0;                    // posição x,y do shank

public:
    void Init();                           // inicialização
    void Update();                         // atualização
    void Draw();                           // desenho
    void Finalize();                       // finalização
};

// ------------------------------------------------------------------------------

void SpriteGame::Init()
{
    // carrega imagens
    logoImg = new Image("Resources/Logo.png");

    // cria sprites
    backg = new Sprite("Resources/Background.jpg");
    shank = new Sprite("Resources/Shank.png");
    logo1 = new Sprite(logoImg);
    logo2 = new Sprite(logoImg);

    // posição inicial do personagem
    x = 380.0f;
    y = 348.0f;
}

// ------------------------------------------------------------------------------

void SpriteGame::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // desloca personagem
    if (window->KeyDown(VK_LEFT))
        x -= 50.0f * gameTime;
    if (window->KeyDown(VK_RIGHT))
        x += 50.0f * gameTime;
    if (window->KeyDown(VK_UP))
        y -= 50.0f * gameTime;
    if (window->KeyDown(VK_DOWN))
        y += 50.0f * gameTime;
} 

// ------------------------------------------------------------------------------

void SpriteGame::Draw()
{
    // desenha pano de fundo
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    
    // desenha personagem
    shank->Draw(x, y);

    // desenha logotipos
    logo1->Draw(230.0f, 125.0f, Layer::UPPER);
    logo2->Draw(590.0f, 515.0f, Layer::LOWER);
}

// ------------------------------------------------------------------------------

void SpriteGame::Finalize()
{
    // remove sprites da memória
    delete backg;
    delete shank;
    delete logo1;
    delete logo2;

    // remove imagem da memória
    delete logoImg;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor de jogo
    Engine * engine = new Engine();
    
    // configura janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 600);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Sprite Game");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);

    // inicia o jogo
    int exit = engine->Start(new SpriteGame());

    // destrói o motor
    delete engine;

    // sai do jogo
    return exit;
}

// ----------------------------------------------------------------------------

