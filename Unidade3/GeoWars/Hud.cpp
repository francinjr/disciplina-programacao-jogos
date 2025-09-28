/**********************************************************************************
// Hud (Código Fonte)
//
// Criação:     02 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Heads Up Display
//
**********************************************************************************/

#include "Hud.h"
#include "GeoWars.h"

// ------------------------------------------------------------------------------

Hud::Hud()
{
    // cria fonte para exibição de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");
    bold = new Font("Resources/Tahoma14b.png");
    bold->Spacing("Resources/Tahoma14b.dat");

    // Os sprites do infobox e keymap não são mais necessários
}

// ------------------------------------------------------------------------------

Hud::~Hud()
{
    delete font;
    delete bold;
}

// -------------------------------------------------------------------------------

void Hud::Update()
{
    // Não há necessidade de lógica de atualização para este HUD
}

// -------------------------------------------------------------------------------

void Hud::Draw()
{
    // Define a cor e a posição inicial do texto
    Color textColor{ 1.0f, 1.0f, 0.0f, 1.0f }; // Cor amarela para destaque
    float posX = 20.0f;
    float posY = 20.0f;

    // --- Zumbis Abatidos ---
    text.str(""); // Limpa o buffer de texto
    text << "Zumbis Abatidos: " << GeoWars::zombieKillCount;
    font->Draw(posX, posY, text.str(), textColor);

    // --- Tempo Restante ---
    posY += 20.0f; // Move para a linha de baixo

    // Garante que o tempo não fique negativo na tela
    float displayTime = GeoWars::gameTimeRemaining > 0 ? GeoWars::gameTimeRemaining : 0.0f;

    // Formata o tempo para o formato Minutos:Segundos
    int minutes = int(displayTime) / 60;
    int seconds = int(displayTime) % 60;

    text.str("");
    text << "Tempo Restante: " << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
    font->Draw(posX, posY, text.str(), textColor);
}

// -------------------------------------------------------------------------------