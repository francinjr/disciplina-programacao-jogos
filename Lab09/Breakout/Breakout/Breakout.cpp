/**********************************************************************************
// D3DBreakout (Código Fonte)
// 
// Criação:     26 Mar 2012
// Atualização: 26 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Exercício sobre uso da classe Scene para gerenciar objetos
//
**********************************************************************************/

#include "Engine.h"
#include "Breakout.h"
#include "Resources.h"
#include "Player.h"
#include "Block.h"
#include "Ball.h"

// ------------------------------------------------------------------------------
// Inicialização de membros estáticos da classe

Scene * Breakout::scene = nullptr;

// ------------------------------------------------------------------------------

void Breakout::Init()
{
    // cena do jogo
    scene = new Scene();

    // carrega background
    backg = new Sprite("Resources/Background.jpg");

    // carregar imagens
    tile1 = new Image("Resources/Tile1.png");
    tile2 = new Image("Resources/Tile2.png");
    tile3 = new Image("Resources/Tile3.png");
    tile4 = new Image("Resources/Tile4.png");
    tile5 = new Image("Resources/Tile5.png");
    
    // -----------------------------------------
    // posição dos blocos

    float line1 = 62.0f;
    float line2 = 92.0f;
    float line3 = 122.0f;
    float line4 = 152.0f;
    float line5 = 182.0f;

    // -----------------------------------------
    // linha 1 de blocos    

    Block* block;
    block = new Block(tile1);
    block->MoveTo(window->CenterX() - 320.0f, line1);
    scene->Add(block);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() - 240.0f, line1);
    scene->Add(block);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() - 160.0f, line1);
    scene->Add(block);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() - 80.0f, line1);
    scene->Add(block);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() - 0.0f, line1);
    scene->Add(block);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() + 80.0f, line1);
    scene->Add(block);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() + 160.0f, line1);
    scene->Add(block);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() + 240.0f, line1);
    scene->Add(block);

    block = new Block(tile1);
    block->MoveTo(window->CenterX() + 320.0f, line1);
    scene->Add(block);

    // -----------------------------------------
    // linha 2 de blocos    

    block = new Block(tile2);
    block->MoveTo(window->CenterX() - 320.0f, line2);
    scene->Add(block);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() - 240.0f, line2);
    scene->Add(block);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() - 160.0f, line2);
    scene->Add(block);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() - 80.0f, line2);
    scene->Add(block);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() - 0.0f, line2);
    scene->Add(block);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() + 80.0f, line2);
    scene->Add(block);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() + 160.0f, line2);
    scene->Add(block);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() + 240.0f, line2);
    scene->Add(block);

    block = new Block(tile2);
    block->MoveTo(window->CenterX() + 320.0f, line2);
    scene->Add(block);

    // -----------------------------------------
    // linha 3 de blocos    

    block = new Block(tile3);
    block->MoveTo(window->CenterX() - 320.0f, line3);
    scene->Add(block);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() - 240.0f, line3);
    scene->Add(block);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() - 160.0f, line3);
    scene->Add(block);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() - 80.0f, line3);
    scene->Add(block);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() - 0.0f, line3);
    scene->Add(block);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() + 80.0f, line3);
    scene->Add(block);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() + 160.0f, line3);
    scene->Add(block);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() + 240.0f, line3);
    scene->Add(block);

    block = new Block(tile3);
    block->MoveTo(window->CenterX() + 320.0f, line3);
    scene->Add(block);

    // -----------------------------------------
    // linha 4 de blocos    

    block = new Block(tile4);
    block->MoveTo(window->CenterX() - 320.0f, line4);
    scene->Add(block);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() - 240.0f, line4);
    scene->Add(block);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() - 160.0f, line4);
    scene->Add(block);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() - 80.0f, line4);
    scene->Add(block);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() - 0.0f, line4);
    scene->Add(block);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() + 80.0f, line4);
    scene->Add(block);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() + 160.0f, line4);
    scene->Add(block);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() + 240.0f, line4);
    scene->Add(block);

    block = new Block(tile4);
    block->MoveTo(window->CenterX() + 320.0f, line4);
    scene->Add(block);

    // -----------------------------------------
    // linha 5 de blocos    

    block = new Block(tile5);
    block->MoveTo(window->CenterX() - 320.0f, line5);
    scene->Add(block);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() - 240.0f, line5);
    scene->Add(block);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() - 160.0f, line5);
    scene->Add(block);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() - 80.0f, line5);
    scene->Add(block);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() - 0.0f, line5);
    scene->Add(block);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() + 80.0f, line5);
    scene->Add(block);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() + 160.0f, line5);
    scene->Add(block);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() + 240.0f, line5);
    scene->Add(block);

    block = new Block(tile5);
    block->MoveTo(window->CenterX() + 320.0f, line5);
    scene->Add(block);
}

// ------------------------------------------------------------------------------

void Breakout::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza objetos da cena
    scene->Update();
} 

// ------------------------------------------------------------------------------

void Breakout::Draw()
{
    // desenha cena
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    scene->Draw();
} 

// ------------------------------------------------------------------------------

void Breakout::Finalize()
{
    // apaga sprite
    delete backg;

    // apaga imagens
    delete tile1;
    delete tile2;
    delete tile3;
    delete tile4;
    delete tile5;

    delete scene;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria engine
    Engine * engine = new Engine();

    // configura a janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 540);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Breakout");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);
    
    // inicia jogo
    engine->Start(new Breakout());

    // destrói engine e jogo
    delete engine;
}

// ----------------------------------------------------------------------------

