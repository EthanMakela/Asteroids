#include "Asteroid.h"



Asteroid::Asteroid()
{
	rockPoints = new SDL_Point[10];
	int widthRand = rand() % 640;
	int heightRand = rand() % 480;
	if (widthRand > 192 && widthRand < 384) widthRand = rand() % 192;//if asteroid spawns in center of screen
	if (heightRand > 144 && heightRand < 288) heightRand = rand() % 144;// spawn it in the top right area...safe
	pos = { widthRand, heightRand };
	prevPos = { widthRand, heightRand };
	cosA = 30;
	sinA = 10;
	angle = 0.0;
	randSpin = rand() % 2;
	speed = 3;
	random = rand() % 70;
	this->Draw();
}


Asteroid::~Asteroid()
{
	delete rockPoints;
}

void Asteroid::UpdatePosition(float& deltaTime) {
	
		velocityX += speed * cosA;
		velocityY += speed * sinA;
		//deal with lefts n rights
		if (randSpin == 0) angle += -0.1;
		if (randSpin == 1) angle += 0.1;
		//set new positions
		pos.x = prevPos.x - velocityX * deltaTime;
		pos.y = prevPos.y - velocityY * deltaTime;
		//deal with moving through screen
		if (pos.x > 640) pos.x = 0;
		if (pos.x < 0) pos.x = 640;
		if (pos.y > 480) pos.y = 0;
		if (pos.y < 0) pos.y = 480;
		prevPos.x = pos.x;
		prevPos.y = pos.y;
	
	
}

void Asteroid::Interpolate(float& deltaTime, float& ip) {
	pos.x = prevPos.x - (velocityX * deltaTime) * ip;
	pos.y = prevPos.y - (velocityY * deltaTime) * ip;
	this->Draw();
}

void Asteroid::Draw(SDL_Renderer* rend) {
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderDrawLines(rend, rockPoints, 10);
}

void Asteroid::Draw() {
	cosA = cos(angle);
	sinA = sin(angle);
	
	rockPoints[0] = { int(pos.x + random * sinA),
		int(pos.y - random * cosA) };

	rockPoints[1] = { int(pos.x + 30 * cosA + 40 * sinA),
		int(pos.y - 40 * cosA + 30 * sinA) };

	rockPoints[2] = { int(pos.x + random * cosA + 10 * sinA),
		int(pos.y - 10 * cosA + 50 * sinA) };

	rockPoints[3] = { int(pos.x + 35 * cosA - 20 * sinA),
		int(pos.y + 20 * cosA + 35 * sinA) };
	
	rockPoints[4] = { int(pos.x + 30 * cosA  - 25 * sinA),
		int(pos.y + 25 * cosA  + 30 * sinA) };
	
	rockPoints[5] = { int(pos.x - 10 * cosA - 45 * sinA),
		int(pos.y + 45 * cosA - 10 * sinA) };
	
	rockPoints[6] = { int(pos.x - 30 * cosA - 25 * sinA),
		int(pos.y + 25 * cosA - 30 * sinA) };
	
	rockPoints[7] = { int(pos.x - 30 * cosA + 10 * sinA),
		int(pos.y - 10 * cosA - 30 * sinA) };
	
	rockPoints[8] = { int(pos.x - 10 * cosA + 15 * sinA),
		int(pos.y - 15 * cosA - 10 * sinA) };
	
	rockPoints[9] = { int(pos.x + random * sinA),
		int(pos.y - random * cosA) };
}