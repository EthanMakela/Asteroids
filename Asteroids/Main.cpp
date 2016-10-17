#include <SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Player.h"


const int WIDTH = 640;
const int HEIGHT = 480;
const int maxFrameSkip = 5;
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
		
		 

		while(isRunning){
			while (SDL_PollEvent(&e)) {
		
				if (e.type == SDL_KEYDOWN)
				{
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
						//fire
					}
					else if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						cout << "quitting" << endl;
						exit(1); //for now just exiting on escape
					}
				}
				if (e.type == SDL_KEYUP)
				{
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

			while (SDL_GetTicks() > nextFrameTime && loops < maxFrameSkip)
			{
				//update player and rock position
				
				
				ship.UpdatePosition(deltaTime);
				nextFrameTime += frameTimeinMS;
				prevFrameTime = SDL_GetTicks();
				loops++;
			}
			interpolation = float(SDL_GetTicks() + frameTimeinMS - nextFrameTime)
				/ float(frameTimeinMS);

			
			int ip = int(interpolation * 10);

			//deal with collisions

			
			if ((ip == 5 || ip == 0  || ip == 8) && ip != prevInterp) {//draws on 0% and 50%
				
				
				ship.Interpolate(deltaTime, interpolation);
				prevInterp = ip;
				SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
				SDL_RenderClear(rend);
				ship.draw(rend);
				SDL_RenderPresent(rend);
				//draweverything else
			}

		}

	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}