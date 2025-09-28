/**********************************************************************************
// Level2 (C�digo Fonte)
//
// Descri��o:   N�vel 2 do jogo, com mensagem de in�cio de round.
//
**********************************************************************************/

#include "GravityGuy.h"
#include "Home.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"

#include <string>
#include <fstream>
#include "Level3.h"
#include "WinScreen.h"
using std::ifstream;
using std::string;

Scene* Level3::scene = nullptr;

void Level3::Init()
{
    scene = new Scene();
    GravityGuy::actualScene = scene;

    backg = new Sprite("Resources/bg_clouds.png");


    float startY = -250.0f;
    float centerX = window->CenterX();

    // Posiciona o jogador 1 um pouco � esquerda do centro
    GravityGuy::player1->MoveTo(centerX, startY);

    // Posiciona o jogador 2 um pouco � direita do centro
    GravityGuy::player2->MoveTo(centerX, startY);


    // Adiciona os jogadores na cena, j� com a posi��o correta
    scene->Add(GravityGuy::player1, MOVING);
    scene->Add(GravityGuy::player2, MOVING);
    scene->Add(GravityGuy::player1->GetGun(), STATIC);
    scene->Add(GravityGuy::player2->GetGun(), STATIC);

    round3Image = new Sprite("Resources/Round3.png");
    timer = new Timer();
    timer->Start();
    showingMessage = true;

    // O resto do seu c�digo para carregar as plataformas do Level3.txt
    std::vector<SpawnSurface> surfaces;
    Platform* plat;
    float posX, posY;
    Color white{ 1,1,1,1 };

    ifstream fin("Level3.txt");
    if (fin.is_open())
    {
        fin >> posX;
        while (!fin.eof()) {
            if (fin.good()) {
                fin >> posY;
                plat = new Platform(posX, posY, white, new Sprite("Resources/cloud.png"));
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

    // Toca a m�sica
    GravityGuy::audio->Play(LEVEL2, true); // Pode mudar para LEVEL3 se tiver uma m�sica nova
}

void Level3::Update()
{
    // Se estiver mostrando a mensagem, apenas espera o tempo passar
    if (showingMessage)
    {
        if (timer->Elapsed(messageTime))
        {
            showingMessage = false; // Acabou o tempo, começa o jogo
        }
        return; // N�o executa a l�gica do jogo ainda
    }

    // L�gica do jogo normal
    spawner->Generate();

    if (GravityGuy::player1->Top() > window->Height())
    {
        GravityGuy::player2Score++;
        GravityGuy::audio->Stop(LEVEL2);

        if (GravityGuy::player2Score >= 2)
        {
            GravityGuy::gameWinner = 2; // Avisa que o P2 venceu
            GravityGuy::NextLevel<WinScreen>(); // Vai para a tela de vitria
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
        return;
    }

    scene->Update();
    scene->CollisionDetection();
}

void Level3::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    if (showingMessage)
    {
        round3Image->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);
    }
    else
    {
        // Desenha o jogo
        scene->Draw();
        if (GravityGuy::viewBBox)
            scene->DrawBBox();
    }
}

void Level3::Finalize()
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