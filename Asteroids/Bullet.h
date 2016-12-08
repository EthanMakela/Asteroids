#pragma once
#include <SDL.h>
#include <iostream>




using namespace std;

class Bullet
{
	SDL_Point* pixel;
	SDL_Point pos;
	SDL_Point prevPos;

	

	float cosA;
	float sinA;
	float velocityX;
	float velocityY;
	int speed;
	
	float shotAngle;
	

public:
	bool fired;
	bool activeBullet;
	Uint32 createTime;
	int TTL;
	Bullet* nextBullet;
	Bullet* prevBullet;
	bool hasBeenDrawn;

	Bullet();
	void CreateNew(SDL_Point shipPos, int shipAngle, int shipSpeed);
	void UpdatePosition(float& deltaTime );
	void Interpolate(float& deltaTime, float& ip);
	void Draw();
	void Draw(SDL_Renderer* rend);
	~Bullet();
};

