/*
 *
 *
 *
*/

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>

#define title "JumpScrollShoot"

// TODO(don): Change this type name
// TODO(don): Implement mobile platform colliders
enum class ColliderCategory { immobile, mobile, player, enemy, playerAttack, enemyAttack };

// TODO(don): Should colliders register themselves to a collision handler?
struct Collider
{
	float x;
	float y;

	float w;
	float h;

	ColliderCategory category;
};

// TODO(don): resolving contact points requires the ability to notify parent
struct ContactPoint
{
	Collider *a;
	Collider *b;
	float angle;
};

struct Player
{
	int width;
	int height;

	int left;
	int right;

	float xPos;
	float yPos;

	float xVel;
	float yVel;

	float xVelMax;
	float yVelMax;

	float xyAcceleration;
};

struct WorldBounds
{
	int width;
	int height;
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
};

struct Screen
{
	int width = 640;
	int height = 480;
};

bool handleEvent(SDL_Event *event, Screen *screen, Player *player)
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
				case SDLK_d: // FALL THROUGH
				case SDLK_RIGHT:
				{
					player->right = 1;
				} break;
				case SDLK_a: // FALL THROUGH
				case SDLK_LEFT:
				{
					player->left = 1;
				} break;
			}
		} break;
		case SDL_KEYUP:
		{
			switch (event->key.keysym.sym)
			{
				case SDLK_d: // FALL THROUGH
				case SDLK_RIGHT:
				{
					player->right = 0;
				} break;
				case SDLK_a: // FALL THROUGH
				case SDLK_LEFT:
				{
					player->left = 0;
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
					player->width = (int)(screen->height / 10);
					player->height = player->width;
					player->xVelMax = (float)(screen->width / 2000.0f);
					player->xPos = (float)(screen->width / 2.0f);
					player->yPos = (float)((screen->height / 2.0f) - (player->height / 2.0f));
				} break;
			}
		} break;
	}

	return result;
}

void updatePlayer(Player *player, Screen *screen, uint32_t deltaTime)
{
	// Adjust for accelerations
	if (!player->left && !player->right || player->left && player->right)
	{
		// Decelerate
		if (player->xVel > 0.5f)
		{
			player->xVel -= player->xyAcceleration * 2;
		}
		else if (player->xVel < -0.5f)
		{
			player->xVel += player->xyAcceleration * 2;
		}
		else
		{
			player->xVel = 0.0f;
		}
	}
	else if (player->right)
	{
		// go right
		if (player->xVel > 0)
		{
			player->xVel += player->xyAcceleration;
		}
		else
		{
			player->xVel += player->xyAcceleration * 2;
		}
	}
	else if (player->left)
	{
		// go left
		if (player->xVel < 0)
		{
			player->xVel -= player->xyAcceleration;
		}
		else
		{
			player->xVel -= player->xyAcceleration * 2;
		}
	}

	// Check for maximum velocity
	if (player->xVel > player->xVelMax)
	{
		player->xVel = player->xVelMax;
	}
	else if (player->xVel < -player->xVelMax)
	{
		player->xVel = -player->xVelMax;
	}

	// Update position
	player->xPos += player->xVel*deltaTime;

	// Check for collision
	if (player->xPos > (float)(screen->width - player->width))
	{
		player->xPos = (float)(screen->width - player->width);
	}
	else if (player->xPos < 0.0f)
	{
		player->xPos = 0.0f;
	}
}

int main(int argc, char* args[])
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not initialize SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		SDL_Window *window = nullptr;

		Screen screen = {};
		screen.width = 640;
		screen.height = 480;
		// Create SDL window
		window = SDL_CreateWindow(title,
								  SDL_WINDOWPOS_UNDEFINED,
								  SDL_WINDOWPOS_UNDEFINED,
								  screen.width,
								  screen.height,
								  SDL_WINDOW_RESIZABLE);
		if (window == nullptr)
		{
			printf("Could not create SDL window Error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_Renderer *renderer = nullptr;
			// Create a Renderer for the window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				Player player = {};
				player.width = (int)(screen.height / 10);
				player.height = player.width;
				player.left = 0;
				player.right = 0;
				player.xPos = (float)(screen.width / 2.0f);
				player.yPos = (float)((screen.height / 2.0f) -(player.height / 2.0f));
				player.xVel = 0.0f;
				player.yVel = 0.0f;
				player.xVelMax = (float)(screen.width / 2000.0f);//0.5f;
				player.yVelMax = 0.5f;
				player.xyAcceleration = 0.01f;

				uint32_t startTime = SDL_GetTicks();

				// Main Loop
				bool running = true;
				while (running)
				{
					// Handle SDL events on queue
					SDL_Event event;
					while (SDL_PollEvent(&event) != 0)
					{
						if (handleEvent(&event, &screen, &player))
						{
							running = false;
						}
					}

					uint32_t currentTime = SDL_GetTicks();
					uint32_t deltaTime = currentTime - startTime;
					startTime = currentTime;
					updatePlayer(&player, &screen, deltaTime);

					// Clear screen
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(renderer);

					// Render player quad
					SDL_Rect playerRect = { player.xPos, player.yPos, player.width, player.height };
					SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
					SDL_RenderFillRect(renderer, &playerRect);

					// Render green outlined quad
					SDL_Rect outlineRect = { screen.width / 6, screen.height / 6, screen.width * 2 / 3, screen.height * 2 / 3 };
					SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
					SDL_RenderDrawRect(renderer, &outlineRect);

					// Draw blue horizontal line
					SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
					SDL_RenderDrawLine(renderer, 0, screen.height / 2, screen.width, screen.height / 2);

					// Draw vertical line of yellow dots
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
					for (int i = 0; i < screen.height; i += 4)
					{
						SDL_RenderDrawPoint(renderer, screen.width / 2, i);
					}

					// Update screen
					SDL_RenderPresent(renderer);
				}
			}
		}
	}

	// Clean up
	/*
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	*/
	SDL_Quit();

	return 0;
}