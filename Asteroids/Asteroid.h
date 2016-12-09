#pragma once
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

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
	int randSpin;
	int speed;
	int random;
	
public:
	Asteroid();
	//Asteroid(SDL_Renderer* rend);
	~Asteroid();
	void UpdatePosition(float& deltaTime);
	void Draw();
	void Draw(SDL_Renderer* rend);
	void Interpolate(float& deltaTime, float& ip);
	//void Remove();
	inline SDL_Point* getLines() { return rockPoints; }
	inline SDL_Point getPos() { return pos; }
};

