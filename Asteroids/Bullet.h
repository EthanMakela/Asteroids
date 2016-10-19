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
	Uint32 createTime;
	int TTL;

	Bullet();
	void CreateNew(SDL_Point shipCenter, float shipAngle );
	void UpdatePosition(float& deltaTime );
	void Interpolate(float& deltaTime, float& ip);
	void Draw();
	void Draw(SDL_Renderer* rend);
	~Bullet();
};

