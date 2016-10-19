#pragma once
#include <iostream>
#include <SDL.h>

using namespace std;

class Player
{
	SDL_Point* ship;
	
	SDL_Point prevPos;
	int velocityX;
	int velocityY;
	float cosA;
	float sinA;
	
	float speed;
	

public:
	SDL_Point pos;
	float angle;
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

