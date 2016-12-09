#pragma once
#include <iostream>
#include <SDL.h>
#include "Bullet.h"


using namespace std;

class Player
{
	SDL_Point* ship;
	
	SDL_Point prevPos;
	
	
	float cosA;
	float sinA;


public:
	SDL_Point pos;
	float angle;
	bool thrusting;
	bool rotatingRight;
	bool rotatingLeft;
	bool deaccelerating;
	bool firing;
	Bullet** firedShots;
	int activeShots;
	float speed;
	const int ammoStash = 20;
	Bullet* tempNextBullet;
	Bullet* tempPrevBullet;
	int nextOpen;
	const int reloadTime = 2000;
	int velocityX;
	int velocityY;
	SDL_Rect* collisionRect;
	bool isAlive;
	void newShip();
	int lives;


	Player();
	~Player();
	void draw();
	void draw(SDL_Renderer* rend);
	void UpdatePosition(float& deltaTime);
	void Interpolate(float& deltaTime, float& ip);
	

	
};

