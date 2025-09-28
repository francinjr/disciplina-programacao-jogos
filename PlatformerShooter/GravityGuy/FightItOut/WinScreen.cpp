#include "WinScreen.h"
#include "GravityGuy.h"
#include "Home.h"

void WinScreen::Init()
{
    // Decide qual imagem de vit�ria carregar com base na vari�vel global
    if (GravityGuy::gameWinner == 1)
    {
        winImage = new Sprite("Resources/Player1Wins.png");
    }
    else
    {
        winImage = new Sprite("Resources/Player2Wins.png");
    }

    // 1. RESETA O JOGO para a pr�xima partida, zerando os placares.
    GravityGuy::player1Score = 0;
    GravityGuy::player2Score = 0;

    // Inicia o timer para controlar a dura��o desta tela
    timer = new Timer();
    timer->Start();
}

void WinScreen::Update()
{
    // 2. ESPERA 3 SEGUNDOS. Enquanto o tempo n�o passa, nada acontece.
    if (timer->Elapsed(3.0f))
    {
        // 3. VOLTA PARA A TELA INICIAL quando o tempo acaba.
        GravityGuy::NextLevel<Home>();
    }
}

void WinScreen::Draw()
{
    // Apenas desenha a imagem do vencedor no centro da tela
    if (winImage)
        winImage->Draw(window->CenterX(), window->CenterY(), Layer::FRONT);
}

void WinScreen::Finalize()
{
    delete winImage;
    delete timer;
}