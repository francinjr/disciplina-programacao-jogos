/**********************************************************************************
// AnimaCtrl
// 
// Criação:     10 Abr 2012
// Atualização: 07 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Exemplo de uso da classe Animation
//
**********************************************************************************/

#include "Engine.h"
#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"
#include "Resources.h"

// ------------------------------------------------------------------------------

class AnimaCtrl : public Game
{
private:
    Sprite * text = nullptr;            // instruções
    Sprite * backg = nullptr;           // pano de fundo
    TileSet * explosion = nullptr;      // folha de sprites da explosão
    Animation * anim = nullptr;         // animação da explosão
    unsigned frame = 0;                 // quadro atual da animação

public:
    void Init();                        // inicializa jogo
    void Update();                      // atualiza lógica do jogo
    void Draw();                        // desenha jogo
    void Finalize();                    // finaliza jogo
};

// -----------------------------------------------------------------------------

void AnimaCtrl::Init()
{
    text      = new Sprite("Resources/TextBar.png");
    backg     = new Sprite("Resources/Background.jpg");
    explosion = new TileSet("Resources/Explosion.png", 192, 192, 5, 10);
    anim      = new Animation(explosion, 0.120f, true);
}

// ------------------------------------------------------------------------------

void AnimaCtrl::Update()
{
    // sai com o pressionamento do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // passa para o próximo frame da animação manualmente
    if (window->KeyPress(VK_RETURN))
    {
        frame = (frame + 1) % 10;
        anim->frame = frame;
    } 

    // passa para o próximo frame da animação automaticamente
    if (window->KeyDown(VK_SPACE))
    {
        anim->NextFrame();
        frame = anim->frame;
    }
} 

// ------------------------------------------------------------------------------

void AnimaCtrl::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    text->Draw(window->CenterX(), window->CenterY() + 40.0f);
    anim->Draw(window->CenterX(), window->CenterY() - 140.0f);
} 

// ------------------------------------------------------------------------------

void AnimaCtrl::Finalize()
{
    delete text;
    delete backg;
    delete explosion;
    delete anim;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // cria engine
    Engine * engine = new Engine();

    // configura janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 540);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Animation Control");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    engine->Start(new AnimaCtrl());

    // destrói engine e jogo
    delete engine;
}

// ----------------------------------------------------------------------------

