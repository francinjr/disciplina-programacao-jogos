/**********************************************************************************
// AnimaMax (Código Fonte)
// 
// Criação:     10 Abr 2012
// Atualização: 07 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Exemplo de uso da classe Animation
//
**********************************************************************************/

#include "Engine.h"
#include "AnimaMax.h"
#include "Explosion.h"
#include "Resources.h"

// -----------------------------------------------------------------------------

Scene * AnimaMax::scene = nullptr;

// -----------------------------------------------------------------------------

void AnimaMax::Init()
{
    scene   = new Scene();
    text    = new Sprite("Resources/TextBar.png");
    backg   = new Sprite("Resources/Background.jpg");
    tileset = new TileSet("Resources/Explosion.jpg", 150, 133, 3, 12);
}

// ------------------------------------------------------------------------------

void AnimaMax::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // gera explosões de forma contínua com a BARRA DE ESPAÇOS
    if (window->KeyDown(VK_SPACE))
    {
        Explosion * explo = new Explosion(tileset);
        explo->MoveTo(randWidth(mt), randHeight(mt));
        scene->Add(explo, STATIC);
    } 

    // gera uma explosão com cada pressionamento do ENTER
    if (window->KeyPress(VK_RETURN))
    {
        Explosion* explo = new Explosion(tileset);
        explo->MoveTo(randWidth(mt), randHeight(mt));
        scene->Add(explo, STATIC);
    }

    // atualização da cena
    scene->Update();
} 

// ------------------------------------------------------------------------------

void AnimaMax::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    text->Draw(window->CenterX(), window->CenterY() + 45.0f);
    scene->Draw();
} 

// ------------------------------------------------------------------------------

void AnimaMax::Finalize()
{
    delete text;
    delete backg;
    delete tileset;
    delete scene;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria engine
    Engine * engine = new Engine();

    // configura janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 540);
    engine->window->Color(0, 0, 0);
    engine->window->Title("AnimaMax");
    engine->window->Icon(IDI_ICON);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    engine->Start(new AnimaMax());

    // destrói engine e jogo
    delete engine;
}

// ----------------------------------------------------------------------------

