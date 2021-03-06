//============================================================================
// Name        : 
// Author      : Don England
// Version     :
// Copyright   : (c) 2015
// Description : 
//============================================================================

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>

#include "JumpScrollShoot.h"
#include "JSS_PhysicsComponent.h"

#define title "JumpScrollShoot"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define JOYSTICK_DEAD_ZONE 8000

SDL_GameController *gGamepad = nullptr;

struct WorldBounds
{
	int width;
	int height;
	/*
	union
	{
		Collider edges[4];
		struct
		{
			Collider left;
			Collider right;
			Collider top;
			Collider bottom;
		};
	};
	*/
};

struct Screen
{
	int width;
	int height;
};

bool handleEvent(SDL_Event *event, EntityInput *input, int numInputs, Screen *screen)
{
	bool result = false;
	//User requests quit
	switch (event->type)
	{
		case SDL_QUIT:
		{
			result = true;
		} break;
		case SDL_KEYDOWN:
		{
			switch (event->key.keysym.sym)
			{
				case SDLK_ESCAPE:
				{
					result = true;
				} break;

				case SDLK_w: // FALL THROUGH
				case SDLK_UP:
				{
					input[0].up = 1;
				} break;

				case SDLK_s: // FALL THROUGH
				case SDLK_DOWN:
				{
					input[0].down = 1;
				} break;

				case SDLK_d: // FALL THROUGH
				case SDLK_RIGHT:
				{
					input[0].right = 1;
				} break;
				case SDLK_a: // FALL THROUGH
				case SDLK_LEFT:
				{
					input[0].left = 1;
				} break;
				case SDLK_e:
				{
					input[0].shoot = 1;
				} break;
				case SDLK_SPACE:
				{
					input[0].jump += 1;
				} break;
			}
		} break;
		case SDL_KEYUP:
		{
			switch (event->key.keysym.sym)
			{
				case SDLK_w: // FALL THROUGH
				case SDLK_UP:
				{
					input[0].up = 0;
				} break;

				case SDLK_s: // FALL THROUGH
				case SDLK_DOWN:
				{
					input[0].down = 0;
				} break;

				case SDLK_d: // FALL THROUGH
				case SDLK_RIGHT:
				{
					input[0].right = 0;
				} break;

				case SDLK_a: // FALL THROUGH
				case SDLK_LEFT:
				{
					input[0].left = 0;
				} break;
				case SDLK_e:
				{
					input[0].shoot = 0;
				} break;
				case SDLK_SPACE:
				{
					input[0].jump = 0;
				} break;
			}
		}
		case SDL_WINDOWEVENT:
		{
			switch (event->window.event)
			{
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				{
					screen->width = event->window.data1;
					screen->height = event->window.data2;
				} break;
			}
		} break;
	}

	return result;
}

int main(int argc, char* args[])
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		std::cout << "Could not initialize SDL Error: "<< SDL_GetError() << std::endl;
	}
	else
	{
		// NOTE(don): input has up to 5 inputs (1 keyboard and up to 4 controllers)
		EntityInput inputs[MAX_ENTITY_INPUTS] = {};
		EntityInput *input = inputs;
		int numInputs = (1 + SDL_NumJoysticks());
		// TODO(don): open and close each joystick for initialization and shutdown respectively
		std::cout << "Found " << numInputs - 1 << " controllers!" << std::endl;
		if (numInputs > 1)
		{
			gGamepad = SDL_GameControllerOpen(0);
		}


		SDL_Window *window = nullptr;

		Screen screen = {};
		screen.width = SCREEN_WIDTH;
		screen.height = SCREEN_HEIGHT;
		// Create SDL window
		window = SDL_CreateWindow(title,
								  SDL_WINDOWPOS_UNDEFINED,
								  SDL_WINDOWPOS_UNDEFINED,
								  screen.width,
								  screen.height,
								  SDL_WINDOW_RESIZABLE);
		if (window == nullptr)
		{
			std::cout << "Could not create SDL window Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			SDL_Renderer *renderer = nullptr;
			// Create a Renderer for the window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr)
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;

			}
			else
			{
				// Make world
				WorldBounds world = {};

				uint32 startTime = SDL_GetTicks();

				// Main Loop
				JumpScrollShoot jumpScrollShoot;
				bool running = true;
				while (running)
				{
					// Handle SDL events on queue
					SDL_Event event;
					while (SDL_PollEvent(&event) != 0)
					{
						if (handleEvent(&event, input, numInputs, &screen))
						{
							running = false;
						}
					}

					uint32 currentTime = SDL_GetTicks();
					uint32 deltaTime = currentTime - startTime;
					startTime = currentTime;

					// TODO(don): Fix Update Controller
					{
						if (SDL_GameControllerGetButton(gGamepad, SDL_CONTROLLER_BUTTON_A))
						{
							input[1].jump += 1;
						}
						else
						{
							input[1].jump = 0;
						}

						input[1].shoot = SDL_GameControllerGetButton(gGamepad, SDL_CONTROLLER_BUTTON_X);
						int16_t StickX = SDL_GameControllerGetAxis(gGamepad, SDL_CONTROLLER_AXIS_LEFTX);
						int16_t StickY = SDL_GameControllerGetAxis(gGamepad, SDL_CONTROLLER_AXIS_LEFTY);
						if (StickX > JOYSTICK_DEAD_ZONE)
						{
							input[1].right = 1;
							input[1].left = 0;
						}
						else if (StickX < -JOYSTICK_DEAD_ZONE)
						{
							input[1].left = 1;
							input[1].right = 0;
						}
						else
						{
							input[1].left = 0;
							input[1].right = 0;
						}
						if (StickY > JOYSTICK_DEAD_ZONE)
						{
							input[1].up = 0;
							input[1].down = 1;
						}
						else if (StickY < -JOYSTICK_DEAD_ZONE)
						{
							input[1].down = 0;
							input[1].up = 1;
						}
						else
						{
							input[1].down = 0;
							input[1].up = 0;
						}
					}

					// Clear screen
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(renderer);

					jumpScrollShoot.GameLoop(input, numInputs, deltaTime, renderer);

					// Update screen
					SDL_RenderPresent(renderer);

					SDL_Delay(33);
				}
			}
			// Clean up renderer
			if (renderer != nullptr)
			{
				SDL_DestroyRenderer(renderer);
				renderer = nullptr;
			}
		}
		// Clean up window
		if (window != nullptr)
		{
			SDL_DestroyWindow(window);
			window = nullptr;
		}
	}

	SDL_GameControllerClose(gGamepad);
	gGamepad = nullptr;

	// Clean up SDL
	SDL_Quit();

	return 0;
}