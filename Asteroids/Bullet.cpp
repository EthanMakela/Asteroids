#include "Bullet.h"

Bullet::Bullet()
{
	
	pixel = new SDL_Point[2];
	
}

Bullet::~Bullet()
{
	delete pixel;
}

void Bullet::CreateNew(SDL_Point shipPos, int shipAngle, int shipSpeed) {
	shotAngle = shipAngle;
	if (shipSpeed > 3) {
		speed = 20 * shipSpeed;
	}
	else speed = 50;
	TTL = 2000;
	cosA = cos(shotAngle);
	sinA = sin(shotAngle);
	pos = shipPos;
	pos.x += -10;
	prevPos = pos;
	createTime = SDL_GetTicks();
	velocityX = speed * cosA * 2;
	velocityY = speed * sinA * 2;
	activeBullet = true;
	nextBullet = NULL;
	prevBullet = NULL;
	
}

void Bullet::Interpolate(float& deltaTime, float& ip) {
	pos.x = prevPos.x - (velocityX * deltaTime) * ip;
	pos.y = prevPos.y - (velocityY * deltaTime) * ip;
	this->Draw();

}

void Bullet::UpdatePosition(float& deltaTime) {

	
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

void Bullet::Draw() {
	pixel[0] = { int(pos.x + cosA * -5),
		int(pos.y + sinA * -5) };
	pixel[1] = { int(pos.x + cosA * -5),
		int(pos.y + sinA * -5) };


}

void Bullet::Draw(SDL_Renderer* rend) {
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderDrawLines(rend, pixel, 2);


}
