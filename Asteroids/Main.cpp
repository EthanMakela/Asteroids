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
	Bullet bullet;
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
					if (e.key.keysym.scancode == SDL_SCANCODE_UP)
					{
						//thrust
						cout << "thrust" << endl;
						ship.thrusting = true;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
					{
						cout << "deaccelerate" << endl;
						ship.deaccelerating = true;
						//deaccelerate
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
					{
						cout << "left" << endl;
						ship.rotatingLeft = true;
						//rotate left
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
					{
						cout << "right" << endl;
						ship.rotatingRight = true;
						//rotate right
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
					{
						cout << "fire" << endl;
						bullet.CreateNew(ship.pos , ship.angle);
						bullet.fired = true;
						//fire
					}
					else if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						cout << "quitting" << endl;
						exit(1); //for now just exiting on escape
					}
				}
				if (e.type == SDL_KEYUP){
					if (e.key.keysym.scancode == SDL_SCANCODE_UP)
					{
						//thrust
						cout << "stop thrust" << endl;
						ship.thrusting = false;
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
					{
						cout << "deaccelerating stopping" << endl;
						ship.deaccelerating = false;
						//deaccelerate
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
					{
						cout << "stop left" << endl;
						ship.rotatingLeft = false;
						//rotate left
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
					{
						cout << "stop right" << endl;
						ship.rotatingRight = false;
						//rotate right
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
					{
						cout << "hold fire" << endl;
						//fire
					}
				}
			}
			loops = 0;
			deltaTime = float(SDL_GetTicks() - prevFrameTime) / 1000.0f; 
			//update loop
			while (SDL_GetTicks() > nextFrameTime && loops < maxFrameSkip){
				//update rock position
				if (bullet.fired == true) {
					bullet.UpdatePosition(deltaTime);
					if (SDL_GetTicks() - bullet.createTime > bullet.TTL) {
						bullet.fired = false;
						cout << "bullet removed" << endl;
					}
				}
				firstRock.UpdatePosition(deltaTime);
				ship.UpdatePosition(deltaTime);
				nextFrameTime += frameTimeinMS;
				prevFrameTime = SDL_GetTicks();
				loops++;
			}
			interpolation = float(SDL_GetTicks() + frameTimeinMS - nextFrameTime)
				/ float(frameTimeinMS);
			
			int ip = int(interpolation * 10);
			//deal with collisions	

			//Draw everything
			if ((ip == 2 || ip == 5 || ip == 8) && ip != prevInterp) {//draws on 20% and 50% and 80%
				if (bullet.fired == true) {
					bullet.Interpolate(deltaTime, interpolation);
				}
				ship.Interpolate(deltaTime, interpolation);
				firstRock.Interpolate(deltaTime, interpolation);
				prevInterp = ip;
				SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
				SDL_RenderClear(rend);
				ship.draw(rend);
				firstRock.Draw(rend);
				bullet.Draw(rend);
				//draw rocks and missles here
				SDL_RenderPresent(rend);
				
			}
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}