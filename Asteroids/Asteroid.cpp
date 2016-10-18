#include "Asteroid.h"



Asteroid::Asteroid()
{
	rockPoints = new SDL_Point[10];
	pos = { 200, 200 };
	prevPos = { 200, 200 };
	cosA = 0.0;
	sinA = 0.0;
	angle = 0.0;
	this->Draw();
}


Asteroid::~Asteroid()
{
	delete rockPoints;
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

	rockPoints[0] = { int(0 - sinA * (pos.y - 50 - pos.y) + pos.x),
		int(sinA * (pos.x - pos.x) + cosA * (pos.y - 50 - pos.y) + pos.y) };

	rockPoints[1] = { int(cosA * (pos.x + 30 - pos.x) - sinA * (pos.y - 40 - pos.y) + pos.x),
		int(sinA * (pos.x + 30 - pos.x) + cosA * (pos.y - 40 - pos.y) + pos.y) };

	rockPoints[2] = { int(cosA * (pos.x + 50 - pos.x) - sinA * (pos.y - 10 - pos.y) + pos.x),
		int(sinA * (pos.x + 50 - pos.x) + cosA * (pos.y - 10 - pos.y) + pos.y) };

	rockPoints[3] = { int(cosA * (pos.x + 35 - pos.x) - sinA * (pos.y + 20 - pos.y) + pos.x),
		int(sinA * (pos.x + 35 - pos.x) + cosA * (pos.y + 20 - pos.y) + pos.y) };

	rockPoints[4] = { int(cosA * (pos.x + 15 - pos.x) - sinA * (pos.y + 50 - pos.y) + pos.x),
		int(sinA * (pos.x + 15 - pos.x) + cosA * (pos.y + 50 - pos.y) + pos.y) };

	rockPoints[5] = { int(cosA * (pos.x - 10 - pos.x) - sinA * (pos.y + 45 - pos.y) + pos.x),
		int(sinA * (pos.x - 10 - pos.x) + cosA * (pos.y + 45 - pos.y) + pos.y) };

	rockPoints[6] = { int(cosA * (pos.x - 40 - pos.x) - sinA * (pos.y + 40 - pos.y) + pos.x),
		int(sinA * (pos.x - 40 - pos.x) + cosA * (pos.y + 40 - pos.y) + pos.y) };

	rockPoints[7] = { int(cosA * (pos.x - 30 - pos.x) - sinA * (pos.y - 10 - pos.y) + pos.x),
		int(sinA * (pos.x - 30 - pos.x) + cosA * (pos.y - 10 - pos.y) + pos.y) };

	rockPoints[8] = { int(cosA * (pos.x - 10 - pos.x) - sinA * (pos.y - 15 - pos.y) + pos.x),
		int(sinA * (pos.x - 10 - pos.x) + cosA * (pos.y - 15 - pos.y) + pos.y) };

	rockPoints[9] = { int(0 - sinA * (pos.y - 50 - pos.y) + pos.x),
		int(cosA * (pos.y - 50 - pos.y) + pos.y) };
}