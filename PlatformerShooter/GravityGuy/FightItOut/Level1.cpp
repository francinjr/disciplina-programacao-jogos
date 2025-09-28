/**********************************************************************************
// Level1 (C�digo Fonte)
//
// Descri��o:   N�vel 1 do jogo
//
**********************************************************************************/

#include "GravityGuy.h"
#include "Home.h"
#include "Level1.h" // Pr�prio header
#include "Level2.h" // Header do pr�ximo n�vel
#include "Player.h"
#include "Platform.h"
#include "Spawner.h"

#include <string>
#include <fstream>
using std::ifstream;
using std::string;


Scene* Level1::scene = nullptr;
void Level1::Init()
{
    // Cria e configura a cena para este n�vel
    scene = new Scene();
    GravityGuy::actualScene = scene;

    backg = new Sprite("Resources/bg_moutains.png");

    scene->Add(GravityGuy::player1, MOVING);
    scene->Add(GravityGuy::player2, MOVING);
    scene->Add(GravityGuy::player1->GetGun(), STATIC);
    scene->Add(GravityGuy::player2->GetGun(), STATIC);

    // Carrega plataformas do Level1.txt
    std::vector<SpawnSurface> surfaces;
    Platform* plat;
    float posX, posY;
    Color white{ 1,1,1,1 };

    ifstream fin("Level1.txt");
    if (fin.is_open())
    {
        fin >> posX;
        while (!fin.eof()) {
            if (fin.good()) {
                fin >> posY;
                plat = new Platform(posX, posY, white, new Sprite("Resources/large_cloud.png"));
                SpawnSurface s = { plat->LeftBorder(), plat->RightBorder(), plat->Top() };
                surfaces.push_back(s);
                scene->Add(plat, STATIC);
            }
            else {
                fin.clear();
                char temp[80];
                fin.getline(temp, 80);
            }
            fin >> posX;
        }
        fin.close();
    }

    spawner = new Spawner(5.0f, 5.0f, surfaces);

    // Toca a m�sica do n�vel
    GravityGuy::audio->Play(LEVEL1, true);
}

void Level1::Update()
{
    spawner->Generate();

    if (window->KeyPress(VK_ESCAPE))
    {
        GravityGuy::audio->Stop(LEVEL1);
        GravityGuy::NextLevel<Home>();
        return;
    }

    // Se um jogador cair, muda para o Level 2
    if ((GravityGuy::player1->Top() > window->Height()))
    {
        GravityGuy::player2Score++;

        GravityGuy::audio->Stop(LEVEL1);
        GravityGuy::player1->Reset();
        GravityGuy::player2->Reset();
        GravityGuy::NextLevel<Level2>();
        return;
    }

    // Se o jogador 2 cair
    if (GravityGuy::player2->Top() > window->Height())
    {
        GravityGuy::player1Score++;

        GravityGuy::audio->Stop(LEVEL1);
        GravityGuy::player1->Reset();
        GravityGuy::player2->Reset();
        GravityGuy::NextLevel<Level2>();
        return;
    }

    // L�gica normal do jogo
    scene->Update();
    scene->CollisionDetection();
}

void Level1::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    scene->Draw();

    if (GravityGuy::viewBBox)
        scene->DrawBBox();
}

void Level1::Finalize()
{
    // Remove objetos globais da cena para n�o serem deletados
    scene->Remove(GravityGuy::player1, MOVING);
    scene->Remove(GravityGuy::player2, MOVING);
    scene->Remove(GravityGuy::player1->GetGun(), STATIC);
    scene->Remove(GravityGuy::player2->GetGun(), STATIC);

    delete spawner;
    delete backg;
    delete scene; // Deleta a cena e tudo que foi adicionado a ela
}