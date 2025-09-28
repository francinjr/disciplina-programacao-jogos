

#include "Home.h"
#include "Road.h"
#include "Engine.h"
#include "Player.h"
#include "Level1.h"
#include "Enemy.h"
#include "GameOver.h"
#include "EndPhaseScore.h"

Scene * Level1::scene = nullptr;
bool Level1::requestSceneChange = false;
bool Level1::requestVictory = false;
int Level1::finalPlayerHealth = 4;


void Level1::Init() 
{
	requestSceneChange = false;
	requestVictory = false;

    scene = new Scene();
	totalDistance = 150;

	uiControls = new Sprite("Resources/UI_Controls.png");

    roadTex = new Image("Resources/Level1_Road.png");
    scene->Add(new Road(roadTex, scene, totalDistance), STATIC);

	//Player * player = new Player();
	//scene->Add(player, MOVING);
	this->player = new Player();
	scene->Add(this->player, MOVING);

	enemySpawner = new EnemySpawner(scene);
}

// Finalize remains unchanged
void Level1::Finalize() 
{
    delete scene;
    delete roadTex;
	delete enemySpawner;
	delete uiControls;
}


void Level1::Update()
{
	if (requestSceneChange)
	{
		Engine::Next<GameOver>();
		return;
	}

	if (requestVictory)
	{
		// Antes de mudar de cena salva a vida do jogador
		if (player)
		{
			finalPlayerHealth = player->GetLifeCount();
		}

		Engine::Next<EndPhaseScore>(); // Agora faz a transição
		return;
	}

	// habilita/desabilita bounding box
	if (window->KeyPress('B'))
	{
		viewBBox = !viewBBox;
	}
	//----------------------------------------

	// Spawna inimigos
	enemySpawner->GenerateEnemies();

	// atualiza cena
	scene->Update();
	if (!Road::isEnding())
	{
		scene->CollisionDetection();
	}


	if (Road::isEnding()) 
	{
		Sprite* finish = new Sprite("Resources/Level1_FinishLine.png");
		finish->Draw(window->CenterX()-0.5f, 100, Layer::LOWER);
	}

	if (window->KeyPress(VK_F9))
	{
		Engine::Next<GameOver>();
	}

	if (window->KeyPress(VK_TAB))
	{
		Engine::Next<EndPhaseScore>();
	}

}



void Level1::Draw()
{
	// desenha cena
	scene->Draw();
	uiControls->Draw(34 + (uiControls->Width() / 2.0f),					  // X
				     window->Height() - 34 - (uiControls->Height() / 2),  // Y
					 Layer::FRONT);										  // Z

	// desenha bounding box dos objetos
	if (viewBBox)
		scene->DrawBBox();
}