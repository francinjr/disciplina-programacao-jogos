/**********************************************************************************
// Home (Código Fonte) 
// 
// Criação:     14 Fev 2013
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Tela de abertura do jogo
//
**********************************************************************************/

#include "Engine.h"
#include "GravityGuy.h"
#include "Home.h"
#include "Level1.h"
#include "Font.h"
#include "Platform.h"

// ------------------------------------------------------------------------------

Font* verdana = nullptr;
Scene* Home::scene = nullptr;
Color white{ 1,1,1,1 };

void Home::Init()
{
    scene = new Scene();
    backg = new Sprite("Resources/full-background.png");
    tituloJogo = new Sprite("Resources/titulo_jogo2.png");
    plat1 = new Sprite("Resources/tronco.png");
    plat2 = new Sprite("Resources/tronco.png");
    tileset = new TileSet("Resources/PressEnter.png", 72, 48, 1, 5);
    anim = new Animation(tileset, 0.180f, true);
    verdana = new Font("Resources/verdana12.png");
    verdana->Spacing("Resources/verdana12.dat");
    // Platform* plat = new Platform(posX, posY, white, new Sprite("Resources/cloud.png"));;

    GravityGuy::audio->Play(MAINMENU, true);
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();
    
    // se a tecla ENTER for pressionada
    if (window->KeyPress(VK_RETURN))
    {
        GravityGuy::audio->Stop(MAINMENU);
        GravityGuy::ResetGame();
        GravityGuy::NextLevel<Level1>();
    }
    else
    {
        anim->NextFrame();
    }
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    tituloJogo->Draw(window->CenterX(), window->CenterY() - 100, Layer::MIDDLE);
    anim->Draw(745, 475);
    plat1->Draw(150, 350, Layer::LOWER);
    plat2->Draw(650, 350, Layer::LOWER);

    Color blue(0.2f, 0.2f, 1.0f, 1.0f);
    verdana->Draw(60, 50, "Verdana 12", blue, Layer::FRONT);
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete anim;
    delete tileset;
    delete backg;
    delete verdana;
    delete tituloJogo;
}

// ------------------------------------------------------------------------------