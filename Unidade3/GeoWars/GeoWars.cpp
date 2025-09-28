/**********************************************************************************
// GeoWars (Código Fonte)
//
// Criação:     23 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Demonstração da versão final do motor
//
**********************************************************************************/

#include "Resources.h"
#include "GeoWars.h"
#include "Engine.h"    
#include "Delay.h"
#include "SmallZombie.h"
#include "MapWall.h"

#include <string>
#include <fstream>
#include <sstream>
// ------------------------------------------------------------------------------

Player* GeoWars::player = nullptr;
Audio* GeoWars::audio = nullptr;
Scene* GeoWars::scene = nullptr;
bool     GeoWars::viewHUD = true;
int      GeoWars::zombieKillCount = 0;
float    GeoWars::gameTimeRemaining = 120.0f; // 2 minutos
bool     GeoWars::isGameOver = false;

// ------------------------------------------------------------------------------

void GeoWars::Init()
{
    // cria sistema de áudio
    audio = new Audio();
    audio->Add(THEME, "Resources/Theme.wav");
    audio->Add(FIRE, "Resources/Fire.wav");
    audio->Add(HITWALL, "Resources/Hitwall.wav");
    audio->Add(EXPLODE, "Resources/Explode.wav");
    audio->Add(START, "Resources/Start.wav");
    audio->Add(PLAYER_HIT, "Resources/DanoNoPlayer.wav");

    GeoWars::audio->Play(THEME);
    // ajusta volumes
    audio->Volume(FIRE, 0.2f);
    audio->Volume(START, 0.8f);
    audio->Volume(THEME, 0.8f);



    // carrega/incializa objetos
    backg = new Background("Resources/Main_Map.png");
    player = new Player();
    scene = new Scene();

    // cria o painel de informações
    hud = new Hud();

    // adiciona objetos na cena (sem colisão)
    scene->Add(player, MOVING);


    for (int i = 0; i < 100; i++)
    {
        scene->Add(new SmallZombie(player, 10, new Vector(90.0f, 2)), MOVING);
    }


    std::vector<Point> points;

    Point* point;
    float posX, posY;

    std::ifstream fin("Walls.txt");
    std::string linha;

    while (std::getline(fin, linha)) {
        std::istringstream iss(linha);
        std::string pointText;
        bool isRect = 0;

        while (iss >> pointText) {
            std::istringstream pointStream(pointText);
            std::string xStr, yStr;

            if (std::getline(pointStream, xStr, ',') && std::getline(pointStream, yStr)) {
                float x = std::stof(xStr);
                float y = std::stof(yStr);
                points.emplace_back(x, y);
            }
        }

        if (points.size() == 2) scene->Add(new MapWall(points[0], points[1]), STATIC);
        else scene->Add(new MapWall(points), STATIC);
        points.clear();
    }

    // ----------------------
    // inicializa a viewport
    // ----------------------

    // calcula posição para manter viewport centralizada
    float difx = (game->Width() - window->Width()) / 2.0f;
    float dify = (game->Height() - window->Height()) / 2.0f;

    // inicializa viewport para o centro do mundo
    viewport.left = 0.0f + difx;
    viewport.right = viewport.left + window->Width();
    viewport.top = 0.0f + dify;
    viewport.bottom = viewport.top + window->Height();
}

// ------------------------------------------------------------------------------

void GeoWars::Update()
{
    // --- LÓGICA DO TEMPORIZADOR ---
    if (gameTimeRemaining > 0)
    {
        gameTimeRemaining -= gameTime; // 'gameTime' é o tempo do último quadro (delta time)
    }
    else
    {
        window->Close(); // Fecha o jogo quando o tempo acaba
        return;          // Impede que o resto do quadro seja processado
    }

    // sai com o pressionamento da tecla ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza cena e calcula colisões
    scene->Update();
    scene->CollisionDetection();
    scene->AgroCollisionDetection();

    // ativa ou desativa a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // ativa ou desativa o heads up display
    if (window->KeyPress('H'))
        viewHUD = !viewHUD;

    // --------------------
    // atualiza a viewport
    // --------------------

    viewport.left = player->X() - window->CenterX();
    viewport.right = player->X() + window->CenterX();
    viewport.top = player->Y() - window->CenterY();
    viewport.bottom = player->Y() + window->CenterY();

    if (viewport.left < 0)
    {
        viewport.left = 0;
        viewport.right = window->Width();
    }
    else if (viewport.right > game->Width())
    {
        viewport.left = game->Width() - window->Width();
        viewport.right = game->Width();
    }

    if (viewport.top < 0)
    {
        viewport.top = 0;
        viewport.bottom = window->Height();
    }
    else if (viewport.bottom > game->Height())
    {
        viewport.top = game->Height() - window->Height();
        viewport.bottom = game->Height();
    }
}

// ------------------------------------------------------------------------------

void GeoWars::Draw()
{
    // desenha pano de fundo
    backg->Draw(viewport);

    // desenha a cena
    scene->Draw();

    // desenha painel de informações
    if (viewHUD)
        hud->Draw();

    // desenha bounding box
    if (viewBBox)
    {
        scene->DrawBBox();
        //scene->DrawAgros();
    }
}

// ------------------------------------------------------------------------------

void GeoWars::Finalize()
{
    delete audio;
    delete hud;
    delete scene;
    delete backg;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor do jogo
    Engine* engine = new Engine();

    // configura motor
    //engine->window->Mode(WINDOWED);
    //engine->window->Size(1152, 648);
    engine->window->Mode(BORDERLESS);
    engine->window->Color(0, 0, 0);
    engine->window->Title("GeoWars");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->window->HideCursor(true);
    //engine->graphics->VSync(true);

    // cria o jogo
    Game* game = new GeoWars();

    // configura o jogo
    game->Size(4096, 1920);

    // inicia execução
    engine->Start(game);

    // destrói motor e encerra jogo
    delete engine;
    return 0;
}

// ----------------------------------------------------------------------------