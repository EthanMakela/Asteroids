#include "Player.h"



Player::Player()
{
	pos = { 320,240 };
	prevPos = { 320, 240 };
	cosA = 0.0;
	sinA = 0.0;
	angle = 0.0;
	thrusting = false;
	rotatingRight = false;
	rotatingLeft = false;
	deaccelerating = false;
	ship = new SDL_Point[5];
	firedShots = new Bullet*[ammoStash];
	for (int i = 0; i < ammoStash; i++) {
		Bullet* bullet = new Bullet;
		firedShots[i] = bullet;
	}
	activeShots = 0;
	lives = 3;
	tempPrevBullet = NULL;
	tempNextBullet = NULL;
	nextOpen = 0;
	collisionRect = new SDL_Rect[4];
	isAlive = true;
	this->draw();
}

void Player::newShip() {
	lives--;
	pos = { 320,240 };
	prevPos = { 320, 240 };
	cosA = 0.0;
	sinA = 0.0;
	angle = 0.0;
	thrusting = false;
	rotatingRight = false;
	rotatingLeft = false;
	deaccelerating = false;
	activeShots = 0;
	tempPrevBullet = NULL;
	tempNextBullet = NULL;
	nextOpen = 0;
	isAlive = true;
	this->draw();
}

Player::~Player()
{
	
	for (int i = 0; i < ammoStash; i++) {
		delete firedShots[i];
	}
	delete firedShots;
	delete[] collisionRect;
	delete ship;

}




void Player::Interpolate(float& deltaTime, float& ip) {
	pos.x = prevPos.x - (velocityX * deltaTime) * ip;
	pos.y = prevPos.y - (velocityY * deltaTime) * ip;
	this->draw();

}

void Player::UpdatePosition(float& deltaTime) {
	if (thrusting) {
		if (speed == 0) {
			speed += 1;
		}
		else speed += abs(speed * 2);
		if (speed > 5) {
			speed = 5;
		}
	}
	if (deaccelerating) {
		if (speed == 0) {
			speed -= 1;
		}
		else speed -= abs(speed * 2);
		if (speed < -3) speed = -3;
	}
	if (thrusting == false && deaccelerating == false) {
		speed -= (speed * 2);
		if (speed < 0) speed = 0;
	}
	velocityX += speed * cosA;
	velocityY += speed * sinA;
	//deal with lefts n rights
	if (rotatingLeft == true) angle += -0.2;
	if (rotatingRight == true) angle += 0.2;
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

void Player::draw() {
	cosA = cos(angle);
	sinA = sin(angle);

	//top point/ front of ship
	ship[0] = { int(pos.x + cosA * -10),
		int(pos.y + sinA * -10) };
	//bottom right
	ship[1] = { int(pos.x + 10 * cosA + 10 * sinA),
		int(pos.y - 10 * cosA + 10 * sinA) };
	//center bottom
	ship[2] = { int(pos.x + 5 * cosA),
		int(pos.y + 5 * sinA) };
	//bottom left
	ship[3] = { int(pos.x + 10 * cosA - 10 * sinA),
		int(pos.y + 10 * cosA + 10 * sinA) };
	//top/front of ship
	ship[4] = { int(pos.x + cosA * -10),
		int(pos.y + sinA * -10) };
	
	collisionRect[0] = { int(pos.x + cosA * -10),
		int(pos.y + sinA * -10),
		2,2 };

	collisionRect[1] = { int(pos.x + 10 * cosA - 10 * sinA),
		int(pos.y + 10 * cosA + 10 * sinA),
		2,2 };

	collisionRect[2] = { int(pos.x + 10 * cosA + 10 * sinA),
		int(pos.y - 10 * cosA + 10 * sinA),
		2,2 };
	collisionRect[3] = { int(pos.x + 5 * cosA),
		int(pos.y + 5 * sinA) };

}

void Player::draw(SDL_Renderer* rend) {
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderDrawLines(rend, ship, 5);
}


