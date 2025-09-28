/**********************************************************************************
// Frogger
//
// Criação:     21 Set 2011
// Atualização: 20 Mai 2025
// Compilador:  Visual C++ 2022
//
// Descrição:   Usa listas de objetos para gerenciar muitos Sprites na tela
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Image.h"
#include "Sprite.h"
#include "Resources.h"
#include "Frog.h"
#include "Enemy.h"
#include <list>
using std::list;

// ------------------------------------------------------------------------------

class Frogger : public Game
{
private:
    Image * woodSmall   = nullptr;      // pequeno tronco de madeira
    Image * woodBig     = nullptr;      // grande tronco de madeira
    Image * turtleSmall = nullptr;      // pequena fila de tartarugas
    Image * turtleBig   = nullptr;      // grande fila de tartarugas
    Image * truck       = nullptr;      // caminhão tanque
    Image * car1        = nullptr;      // carro de passeio azul
    Image * car2        = nullptr;      // carro de passeio branco
    Image * car3        = nullptr;      // carro de passeio amarelo
    Image * car4        = nullptr;      // carro de passeio vermelho

    Sprite * background = nullptr;      // imagem de fundo
    Frog   * frog       = nullptr;      // sapo
    Enemy  * enemy      = nullptr;      // inimigo

    list<Enemy*> objects;               // lista de inimigos em movimento

public:
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

// ------------------------------------------------------------------------------

void Frogger::Init()
{
    // carrega imagens do jogo
    woodSmall   = new Image("Resources/woodSmall.png");
    woodBig     = new Image("Resources/woodBig.png");
    turtleSmall = new Image("Resources/turtlesSmall.png");
    turtleBig   = new Image("Resources/turtlesBig.png");
    truck       = new Image("Resources/truck.png");
    car1        = new Image("Resources/car1.png");
    car2        = new Image("Resources/car2.png");
    car3        = new Image("Resources/car3.png");
    car4        = new Image("Resources/car4.png");

    // inicializa sprites do jogo
    background = new Sprite("Resources/Track.jpg");

    // cria objeto sapo
    frog = new Frog();

    // ---------------------------
    // inimigos na água

    enemy = new Enemy(woodSmall, 80);
    enemy->MoveTo(150, 120);
    objects.push_back(enemy);

    enemy = new Enemy(woodSmall, 80);
    enemy->MoveTo(550, 120);
    objects.push_back(enemy);

    enemy = new Enemy(turtleSmall, 70);
    enemy->MoveTo(480, 160);
    objects.push_back(enemy);

    enemy = new Enemy(turtleSmall, 70);
    enemy->MoveTo(680, 160);
    objects.push_back(enemy);

    enemy = new Enemy(woodBig, 50);
    enemy->MoveTo(200, 200);
    objects.push_back(enemy);

    enemy = new Enemy(woodBig, 50);
    enemy->MoveTo(700, 200);
    objects.push_back(enemy);

    enemy = new Enemy(woodSmall, 60);
    enemy->MoveTo(350, 240);
    objects.push_back(enemy);

    enemy = new Enemy(turtleBig, 40);
    enemy->MoveTo(150, 280);
    objects.push_back(enemy);

    enemy = new Enemy(turtleBig, 40);
    enemy->MoveTo(450, 280);
    objects.push_back(enemy);

    enemy = new Enemy(turtleBig, 40);
    enemy->MoveTo(750, 280);
    objects.push_back(enemy);

    // ---------------------------
    // carros na pista

    enemy = new Enemy(truck, 50);
    enemy->MoveTo(300, 360);
    objects.push_back(enemy);

    enemy = new Enemy(truck, 50);
    enemy->MoveTo(700, 360);
    objects.push_back(enemy);

    enemy = new Enemy(car1, 90);
    enemy->MoveTo(350, 400);
    objects.push_back(enemy);

    enemy = new Enemy(car4, 90);
    enemy->MoveTo(600, 400);
    objects.push_back(enemy);

    enemy = new Enemy(car2, 110);
    enemy->MoveTo(500, 440);
    objects.push_back(enemy);

    enemy = new Enemy(car3, 100);
    enemy->MoveTo(750, 480);
    objects.push_back(enemy);

    enemy = new Enemy(car4, 80);
    enemy->MoveTo(450, 520);
    objects.push_back(enemy);
}

// ------------------------------------------------------------------------------

void Frogger::Update()
{
    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    // atualiza posição
    frog->Update();

    // move inimigos
    for (auto obj : objects)
        obj->Update();
} 

// ------------------------------------------------------------------------------

void Frogger::Draw()
{
    // desenha pano de fundo
    background->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    // desenha sapo
    frog->Draw();

    // desenha inimigos
    for (auto obj : objects)
        obj->Draw();
}

// ------------------------------------------------------------------------------

void Frogger::Finalize()
{
    // remove objetos da memória
    delete background;
    delete frog;

    // remove inimigos
    for (auto obj : objects)
        delete obj;

    // descarrega imagens da memória
    delete woodSmall;
    delete woodBig;
    delete turtleSmall;
    delete turtleBig;
    delete truck;
    delete car1;
    delete car2;
    delete car3;
    delete car4;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria motor de jogos
    Engine * engine = new Engine();

    // configura janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 600);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Frogger");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    
    // configura dispositivo gráfico
    //engine->graphics->VSync(true);

    // inicia o jogo
    int exit = engine->Start(new Frogger());

    // destrói motor
    delete engine;

    // sai do jogo
    return exit;
}

// ----------------------------------------------------------------------------
