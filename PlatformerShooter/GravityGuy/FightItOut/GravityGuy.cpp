/**********************************************************************************
// GravityGuy (Código Fonte)
// 
// Criação:     05 Out 2011
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Jogo estilo plataforma usando a engine do curso
//
**********************************************************************************/

#include "Engine.h"
#include "GravityGuy.h"
#include "Home.h"
#include "GameOver.h"

// ------------------------------------------------------------------------------

// inicializa membros estáticos da classe
Game*   GravityGuy::level       = nullptr;
Player* GravityGuy::player1     = nullptr;
Player* GravityGuy::player2     = nullptr;
Audio*  GravityGuy::audio       = nullptr;
Image * GravityGuy::bulletImg   = nullptr;
Scene * GravityGuy::actualScene = nullptr;
bool    GravityGuy::viewBBox    = false;
int GravityGuy::player1Score = 0;
int GravityGuy::player2Score = 0;
int GravityGuy::gameWinner = 0;
// ------------------------------------------------------------------------------

void GravityGuy::Init() 
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(LEVEL1,      "Resources/bgmLevel1.wav");
    audio->Add(LEVEL2,      "Resources/bgmLevel2.wav");
    audio->Add(MAINMENU,    "Resources/mainMenu.wav");
    audio->Add(SMALLGUN,    "Resources/pistol.wav");
    audio->Add(RIFLE,       "Resources/rifle.wav");
    audio->Add(SHOTGUN,     "Resources/shotgun.wav");

    //audio->Add(MENU, "Resources/Menu.wav");
    //audio->Add(MUSIC, "Resources/Music.wav");
    //audio->Add(TRANSITION, "Resources/Transition.wav");

    bulletImg = new Image("Resources/guns_animations/Ak-bullet.png");

    // bounding box não visível
    viewBBox = false;

    // cria jogador 1
    player1 = new Player(FIRST);

    // cria jogador 2
    player2 = new Player(SECOND);
    
    // inicializa nível de abertura do jogo
    level = new Home();
    level->Init();
}

// ------------------------------------------------------------------------------

void GravityGuy::Update()
{
    // habilita/desabilita visualização da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;    

    // atualiza nível
    level->Update();
} 

// ------------------------------------------------------------------------------

void GravityGuy::Draw()
{
    // desenha nível
    level->Draw();
} 

// ------------------------------------------------------------------------------

void GravityGuy::Finalize()
{
    level->Finalize();

    delete player1;
    delete player2;
    delete audio;
    delete level;
    delete actualScene;
}

void GravityGuy::ResetGame()
{
    // Zera todas as variáveis globais de estado
    player1Score = 0;
    player2Score = 0;
    gameWinner = 0;

    // Reseta a posição e estado dos jogadores
    if (player1) player1->Reset();
    if (player2) player2->Reset();
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura o motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 500);
    engine->window->Color(30, 50, 80);
    engine->window->Title("Fight It Out");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new GravityGuy());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

