#pragma once
#include <SDL.h>
#include <iostream>

using namespace std;

class Asteroid
{
	SDL_Point* rockPoints;
	SDL_Point pos;
	SDL_Point prevPos;
	int size;
	float angle;
	float velocityX;
	float velocityY;
	float cosA;
	float sinA;
	float rotationFactor;
public:
	Asteroid();
	Asteroid(SDL_Renderer* rend);
	~Asteroid();
	void Update();
	void Draw();
	void Draw(SDL_Renderer* rend);
	void Interpolate(float& deltaTime, float& ip);
	void Remove();
};

