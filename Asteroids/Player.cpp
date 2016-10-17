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
	 this->draw();
}


Player::~Player()
{
	delete ship;

}

void Player::Interpolate(float& deltaTime, float& ip) {
	pos.x = prevPos.x - (velocity1 * deltaTime) * ip;
	pos.y = prevPos.y - (velocity2 * deltaTime) * ip;
	this->draw();

}

void Player::UpdatePosition(float& deltaTime) {
	if (thrusting) {
		speed += 1;
		if (speed > 5) {
			speed = 5;
		}
	}
	if (deaccelerating) {
		speed -= 1;
		if (speed < -4) speed = -4;	
	}
	if (thrusting == false && deaccelerating == false) {
		speed -= 1;
		if (speed < 0) speed = 0;
	}
	velocity1 += speed * cosA;
	velocity2 += speed * sinA;
	//deal with lefts n rights 
	if (rotatingLeft == true) angle += -0.2;
	if (rotatingRight == true) angle += 0.2;
	//set new positions
	pos.x = prevPos.x - velocity1 * deltaTime;
	pos.y = prevPos.y - velocity2 * deltaTime;
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

	//Math to draw ship greatfully taken from sdl example
	//top point/ front of ship
	ship[0] = { int(cosA * (pos.x - 10 - pos.x) - sinA * (pos.y - pos.y) + pos.x),
		int(sinA * (pos.x - 10 - pos.x) + cosA * (pos.y - pos.y) + pos.y) };
	//bottom right
	ship[1] = { int(cosA * (pos.x + 10 - pos.x) - sinA * (pos.y - 10 - pos.y) + pos.x),
		int(sinA * (pos.x + 10 - pos.x) + cosA * (pos.y - 10 - pos.y) + pos.y) };
	//center bottom
	ship[2] = { int(cosA * (pos.x + 5 - pos.x) - sinA * (pos.y - pos.y) + pos.x),
		int(sinA * (pos.x + 5 - pos.x) + cosA * (pos.y - pos.y) + pos.y) };
	//bottom left
	ship[3] = { int(cosA * (pos.x + 10 - pos.x) - sinA * (pos.y + 10 - pos.y) + pos.x),
		int(sinA * (pos.x + 10 - pos.x) + cosA * (pos.y + 10 - pos.y) + pos.y) };
	//top/front of ship
	ship[4] = { int(cosA * (pos.x - 10 - pos.x) - sinA * (pos.y - pos.y) + pos.x),
		int(sinA * (pos.x - 10 - pos.x) + cosA * (pos.y - pos.y) + pos.y) };

}

void Player::draw(SDL_Renderer* rend) {
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderDrawLines(rend, ship, 5);
	

}
