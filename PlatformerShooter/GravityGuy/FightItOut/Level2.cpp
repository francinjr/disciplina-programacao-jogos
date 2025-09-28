/**********************************************************************************
// Level2 (C�digo Fonte)
//
// Descri��o:   N�vel 2 do jogo, com mensagem de in�cio de round.
//
**********************************************************************************/

#include "GravityGuy.h"
#include "Home.h"
#include "Level2.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"

#include <string>
#include <fstream>
#include "Level3.h"
#include "WinScreen.h"
using std::ifstream;
using std::string;

Scene* Level2::scene = nullptr;

void Level2::Init()
{
    scene = new Scene();
    GravityGuy::actualScene = scene;

    backg = new Sprite("Resources/bg_forest.png");

    // Adiciona jogadores e suas armas
    GravityGuy::player1->Reset();
    GravityGuy::player2->Reset();

    scene->Add(GravityGuy::player1, MOVING);
    scene->Add(GravityGuy::player2, MOVING);

    scene->Add(GravityGuy::player1->GetGun(), STATIC);
    scene->Add(GravityGuy::player2->GetGun(), STATIC);



    // Inicializa itens para a mensagem "Round 2"
    round2Image = new Sprite("Resources/Round2.png");
    p1winsImage = new Sprite("Resources/Player1Wins.png");
    p2winsImage = new Sprite("Resources/Player2Wins.png");
    timer = new Timer();
    timer->Start();
    showingMessage = true;

    // Carrega plataformas do Level2.txt
    std::vector<SpawnSurface> surfaces;
    Platform* plat;
    float posX, posY;
    Color white{ 1,1,1,1 };

    ifstream fin("Level2.txt");
    if (fin.is_open())
    {
        fin >> posX;
        while (!fin.eof()) {
            if (fin.good()) {
                fin >> posY;
                plat = new Platform(posX, posY, white, new Sprite("Resources/plat_tronco.png"));
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

    // Toca a m�sica do N�vel 2
    GravityGuy::audio->Play(LEVEL2, true);
}

void Level2::Update()
{
    // Se estiver mostrando a mensagem, apenas espera o tempo passar
    if (showingMessage)
    {
        if (timer->Elapsed(messageTime))
        {
            showingMessage = false; // Acabou o tempo, come�a o jogo
        }
        return; // N�o executa a l�gica do jogo ainda
    }

    // L�gica do jogo normal
    spawner->Generate();

    if (window->KeyPress(VK_ESCAPE))
    {
        GravityGuy::audio->Stop(LEVEL2);
        GravityGuy::NextLevel<Home>();
        return;
    }

    // Se um jogador cair, vai para a tela de Game Over
    if (GravityGuy::player1->Top() > window->Height())
    {
        GravityGuy::player2Score++;
        GravityGuy::audio->Stop(LEVEL2);

        if (GravityGuy::player2Score >= 2)
        {
            GravityGuy::gameWinner = 2; // Avisa que o P2 venceu
            GravityGuy::NextLevel<WinScreen>(); // Vai para a tela de vitria
        }
        else
        {
            GravityGuy::player1->Reset();
            GravityGuy::player2->Reset();
            GravityGuy::NextLevel<Level3>(); // Vai para o prximo round
        }
        return;
    }

    // Se o jogador 2 cair
    if (GravityGuy::player2->Top() > window->Height())
    {
        GravityGuy::player1Score++;
        GravityGuy::audio->Stop(LEVEL2);

        if (GravityGuy::player1Score >= 2)
        {
            GravityGuy::gameWinner = 1; // Avisa que o P1 venceu
            GravityGuy::NextLevel<WinScreen>();
        }
        else
        {
            GravityGuy::player1->Reset();
            GravityGuy::player2->Reset();
            GravityGuy::NextLevel<Level3>(); // Vai para o prximo round
        }
        return;
    }

    scene->Update();
    scene->CollisionDetection();
}

void Level2::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    if (showingMessage)
    {
        // Desenha "Round 2" na tela
        round2Image->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);
    }
    else
    {
        // Desenha o jogo
        scene->Draw();
        if (GravityGuy::viewBBox)
            scene->DrawBBox();
    }
}

void Level2::Finalize()
{
    // Remove objetos globais
    scene->Remove(GravityGuy::player1, MOVING);
    scene->Remove(GravityGuy::player2, MOVING);
    scene->Remove(GravityGuy::player1->GetGun(), STATIC);
    scene->Remove(GravityGuy::player2->GetGun(), STATIC);

    // Deleta objetos do n�vel
    delete spawner;
    delete backg;
    delete font;
    delete timer;
    delete scene;
}