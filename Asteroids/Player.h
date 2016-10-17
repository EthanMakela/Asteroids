#pragma once
#include <iostream>
#include <SDL.h>

using namespace std;

class Player
{
	SDL_Point* ship;
	SDL_Point pos;
	SDL_Point prevPos;
	int velocity1;
	int velocity2;
	float cosA;
	float sinA;
	float angle;
	float speed;
	

public:
	bool thrusting;
	bool rotatingRight;
	bool rotatingLeft;
	bool deaccelerating;

	Player();
	~Player();
	void draw();
	void draw(SDL_Renderer* rend);
	void UpdatePosition(float& deltaTime);
	void Interpolate(float& deltaTime, float& ip);
};

