#include <SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"



const int WIDTH = 640;
const int HEIGHT = 480;
const int maxFrameSkip = 2;
const int updatesPS = 30;
const int frameTimeinMS = 1000 / updatesPS;



using namespace std;


int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* rend = NULL;
	SDL_Event e;

	Uint32 nextFrameTime = SDL_GetTicks();
	Uint32 prevFrameTime = SDL_GetTicks();

	srand(time(NULL));
	bool isRunning = true;
	unsigned loops = 0;
	float deltaTime = 0;
	float interpolation = 0;
	int prevInterp = 0;
	
	Player ship;
	Asteroid firstRock;
	Bullet* bullet = new Bullet;
	
	
	
	bool firing = false;
	int count = 0;
	//Init
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL Init Failure! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("Astroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window creation failure SDL_Error: %s\n", SDL_GetError());
		}
		rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (rend == NULL) {
			printf("Renderer could not be made SDL_Error: %s\n", SDL_GetError());
		}
		//inputs
		
		while(isRunning){
			while (SDL_PollEvent(&e)) {
		
				if (e.type == SDL_KEYDOWN){
					if (e.key.keysym.scancode == SDL_SCANCODE_UP || e.key.keysym.scancode == SDL_SCANCODE_W)
					{
						//thrust
						cout << "thrust" << endl;
						ship.thrusting = true;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_DOWN || e.key.keysym.scancode == SDL_SCANCODE_S)
					{
						cout << "deaccelerate" << endl;
						ship.deaccelerating = true;
						//deaccelerate
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_LEFT || e.key.keysym.scancode == SDL_SCANCODE_A)
					{
						cout << "left" << endl;
						ship.rotatingLeft = true;
						//rotate left
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT || e.key.keysym.scancode == SDL_SCANCODE_D)
					{
						cout << "right" << endl;
						ship.rotatingRight = true;
						//rotate right
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
					{					
						Bullet* bullet = new Bullet;						
						for (int i = 0; i < ship.ammoStash; i++) {
							if (ship.firedShots[i]->activeBullet == false) {
								ship.nextOpen = i;
							}
						}
						if (ship.tempPrevBullet != NULL) { //If not first bullet set the previously shot bullet 
							bullet->prevBullet = ship.firedShots[ship.nextOpen];
						}
						else {
							ship.tempPrevBullet = bullet; //Set this bullet as previous bullet for next
							ship.firing = true;
							bullet->activeBullet = true;
							bullet->CreateNew(ship.pos, ship.angle, ship.speed);
							ship.firedShots[ship.nextOpen] = bullet;  //Put the bullet into the chamber
							//cout << "first shot fired" << endl;
						}
						if (bullet->prevBullet != NULL) {
							if (SDL_GetTicks() - bullet->prevBullet->createTime > 2000) { //20 Bullets 2 second load time 
								ship.tempPrevBullet = bullet;
								ship.firing = true;
								bullet->activeBullet = true;
								bullet->CreateNew(ship.pos, ship.angle, ship.speed);
								ship.firedShots[ship.nextOpen] = bullet;
								//cout << "bullet " << ship.nextOpen << " fired" << endl;
							}
						}
					}
					else if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						cout << "quitting" << endl;
						exit(1); //for now just exiting on escape
					}
				}
				if (e.type == SDL_KEYUP){
					if (e.key.keysym.scancode == SDL_SCANCODE_UP || e.key.keysym.scancode == SDL_SCANCODE_W)
					{
						//thrust
						cout << "stop thrust" << endl;
						ship.thrusting = false;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_DOWN || e.key.keysym.scancode == SDL_SCANCODE_S)
					{
						cout << "deaccelerating stopping" << endl;
						ship.deaccelerating = false;
						//deaccelerate
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_LEFT || e.key.keysym.scancode == SDL_SCANCODE_A)
					{
						cout << "stop left" << endl;
						ship.rotatingLeft = false;
						//rotate left
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT || e.key.keysym.scancode == SDL_SCANCODE_D)
					{
						cout << "stop right" << endl;
						ship.rotatingRight = false;
						//rotate right
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
					{
						cout << "Halt fire" << endl;
						ship.firing = false;

						//fire
					}
				}
			}
			loops = 0;
			deltaTime = float(SDL_GetTicks() - prevFrameTime) / 1000.0f; 
			//update loop
			
			while (SDL_GetTicks() > nextFrameTime && loops < maxFrameSkip){
				//update rock position
				firstRock.UpdatePosition(deltaTime);
				ship.UpdatePosition(deltaTime);
				for (int i = 0; i < ship.ammoStash; i++) {
					if (ship.firedShots[i]->activeBullet == true) {
						ship.firedShots[i]->UpdatePosition(deltaTime);
						
					}
				}
				nextFrameTime += frameTimeinMS;
				prevFrameTime = SDL_GetTicks();
				loops++;
			}
			interpolation = float(SDL_GetTicks() + frameTimeinMS - nextFrameTime)
				/ float(frameTimeinMS);
			
			int ip = int(interpolation * 10);

			//deal with collisions	

			if ((ip == 2 || ip == 8) && ip != prevInterp) {//draws on 20% and 50% and 80%
				
				ship.Interpolate(deltaTime, interpolation); //Interpolate the ship
				firstRock.Interpolate(deltaTime, interpolation); //Interpolate the first Rock
				for (int i = 0; i < ship.ammoStash; i++) {
					if ( ship.firedShots[i]->activeBullet == true) {
						
						ship.firedShots[i]->Interpolate(deltaTime, interpolation); //Interpolate the list of bullets
						
							if (SDL_GetTicks() - ship.firedShots[i]->createTime > ship.firedShots[i]->TTL) {
								ship.firedShots[i]->activeBullet = false;

								ship.activeShots--;

								//Small leak looses a few bullets into mem needs attention but all bullets stop rendering after ttl
								cout << "bullet " << i << " removed" << endl;

							}
						}
					
				}
				prevInterp = ip;
				SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
				SDL_RenderClear(rend);
				ship.draw(rend);
				firstRock.Draw(rend);
				for (int i = 0; i < ship.ammoStash; i++) {
					if (ship.firedShots[i]->activeBullet == true ) {
						ship.firedShots[i]->Draw(rend);
					}
				}
				
				//draw rocks here
				SDL_RenderPresent(rend);
				
			}
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	delete bullet;
	return 0;
}

