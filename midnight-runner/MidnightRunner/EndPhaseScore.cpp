#include "Home.h"
#include "Engine.h"
#include "EndPhaseScore.h"
#include "Level1.h"

void EndPhaseScore::Init()
{
    std::string finalImage;

    // Decide qual imagem carregar com base na vida final
    if (Level1::finalPlayerHealth >= 3)
    {
        // Vida cheia ou tomou só 1 dano = 3 estrelas
        finalImage = "Resources/EndPhaseScore3.png";
    }
    else if (Level1::finalPlayerHealth == 2)
    {
        // Metade da vida = 2 estrelas
        finalImage = "Resources/EndPhaseScore2.png";
    }
    else
    {
        // Somente 1 de vida = 1 estrela
        finalImage = "Resources/EndPhaseScore1.png";
    }
    backg = new Sprite(finalImage);
}

void EndPhaseScore::Update()
{

    if (window->KeyPress(VK_ESCAPE))
        window->Close();

	if (window->KeyPress(VK_RETURN) || window->KeyPress(VK_SPACE))
        Engine::Next<Level1>();

}

void EndPhaseScore::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

void EndPhaseScore::Finalize()
{
    delete backg;
}