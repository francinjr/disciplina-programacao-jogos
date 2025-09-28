#include "EnemySpawner.h"
#include <vector>
#include "Enemy.h"
#include "Engine.h"
#include <fstream>
#include <sstream>
#include "Road.h"
#include <cstdlib>  // Para rand() e srand()
#include <ctime>    // Para time()


// Uma estrutura para definir um "pattern" (chunk) de inimigos
struct EnemyPatternStep {
	int lane; // 0 para meio, -1 para esquerda e 1 para a direita
	float offsetY; // o offSetY é basicamente a distancia em Y do 0 (inicio da road)
	TypeOfEnemy typeOfCar;
};

struct EnemyPattern {
	std::vector<EnemyPatternStep> steps;
};

std::vector<EnemyPattern> patterns;
std::vector<Image*> imgs;
EnemySpawner::EnemySpawner(Scene * newScene)
{
	timer = new Timer();
	timer->Start();

	scene = newScene;

	imgs[SMALL_TRUCK] = new Image("Resources/Traffic_SmallTruck.png");
	imgs[BIG_TRUCK] = new Image("Resources/Traffic_BigTruck.png");
	imgs[SEDAN] = new Image("Resources/Traffic_Sedan.png");
	imgs[HATCH] = new Image("Resources/Traffic_Hatch.png");
	
	srand(static_cast<unsigned int>(time(NULL)));


	InitPatterns();
}

EnemySpawner::~EnemySpawner()
{
	delete timer;
	for (const auto& img : imgs) {
		delete img.second;
	}
	imgs.clear();
}

int EnemySpawner::GetLaneX(int lane) {
	return Engine::window->CenterX() - (lane * 160); // 160 é o laneOffSet, a distância do centro para o meio das outras duas pistas.
}

void EnemySpawner::InitPatterns() {
  
    std::ifstream fin("enemyPatterns.txt");
    std::string line;

    while (std::getline(fin, line)) {
        // ignorar comentários e etc
        if (line.empty() || line[0] == '/' || line[0] == '#') continue;

        std::istringstream iss(line);
        EnemyPattern pattern;
        int lane;
        float offsetY;
        int type;

        while (iss >> lane >> offsetY >> type) {
            EnemyPatternStep step = { lane, offsetY, TypeOfEnemy(type) };
            pattern.steps.push_back(step);
        }

        if (!pattern.steps.empty()) {
            patterns.push_back(pattern);
        }
    }
    fin.close();

}

void EnemySpawner::GenerateEnemies()
{
    SPAWN_DELAY = 5.0f / (Road::globalVel / Road::DEFAULT_SPEED);

    static int lastIndex = -1;  // Índice do último padrão usado

    if (timer->Elapsed(SPAWN_DELAY) && !Road::isEnding()) {
        timer->Reset();

        if (patterns.empty()) InitPatterns();

        // Gera novo índice garantindo que seja diferente do anterior
        uint randomIndex;
        do {
            randomIndex = rand() % patterns.size();
        } while (randomIndex == lastIndex && patterns.size() > 1);

        lastIndex = randomIndex;  // Atualiza o último índice usado
        EnemyPattern chosen = patterns[randomIndex];

        for (const auto& step : chosen.steps) {
            int enemyX = GetLaneX(step.lane);
            float enemyY = -100 - step.offsetY;

            scene->Add(new Enemy(enemyX, enemyY, step.typeOfCar, imgs[step.typeOfCar]), MOVING);
        }
    }
}


