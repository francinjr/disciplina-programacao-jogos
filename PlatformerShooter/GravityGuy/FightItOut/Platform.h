/**********************************************************************************
// Platform (Arquivo de Cabeçalho)
// 
// Criação:     21 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_PLATFORM_H_
#define _GRAVITYGUY_PLATFORM_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites

// ---------------------------------------------------------------------------------

class Platform : public Object
{
private:
    Sprite * platform = nullptr;            // sprite da plataforma
    Color color;                            // cor da plataforma

public:
    Platform(float posX, float posY, 
             Color tint, Sprite * sprite);                   // construtor    
    ~Platform();                            // destrutor
    int height;
    float Top();
    float Bottom();
    float LeftBorder();
    float RightBorder();
    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
}; 

// ---------------------------------------------------------------------------------
// Função Membro Inline

inline void Platform::Draw()
{ platform->Draw(x, y, z, 1.0f, 0.0f, color); }
inline float Platform::Top()
{
    return y - (platform->Height() / 2.0);
}
inline float Platform::Bottom()
{
    return y + (platform->Height() / 2.0);
}
inline float Platform::LeftBorder()
{
    return x - (platform->Width() / 2.0);
}
inline float Platform::RightBorder()
{
    return x + (platform->Width() / 2.0);
}
// ---------------------------------------------------------------------------------

#endif