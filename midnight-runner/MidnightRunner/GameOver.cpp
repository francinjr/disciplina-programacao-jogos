// GameOver.cpp
#include "GameOver.h"
#include "Home.h"
#include "Engine.h"
#include "Level1.h"

void GameOver::Init()
{
    backg = new Sprite("Resources/GameOverScreen.png");
}

void GameOver::Update()
{

    if (window->KeyPress(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_RETURN) || window->KeyPress(VK_SPACE))
        Engine::Next<Level1>();
}

void GameOver::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

void GameOver::Finalize()
{
    delete backg;
}