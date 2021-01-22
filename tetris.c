/*___            _      _    _       _____    _        _
|  _ \ _ __ ___ (_) ___| | _| |_ _  |_   _|__| |_ _ __(_)___
| |_) | '__/ _ \| |/ _ \ |/ / __(_)   | |/ _ \ __| '__| / __|
|  __/| | | (_) | |  __/   <| |_ _    | |  __/ |_| |  | \__ \
|_|   |_|  \___// |\___|_|\_\\__(_)   |_|\___|\__|_|  |_|___/
              |_*/
#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "header.h"

int main(int argc, char *argv[]) {
	//Initialize SDL
	if (init()) {
		//main loop flag
		int quit = 0;
		//Event handler
		SDL_Event e;

		if (loadMedia()) {

			srand(time(NULL));
			rand_first = rand() % 7;
			mino_current.p_texture = mino[rand_first].p_texture;
			for (int m = 0; m < 16; m++) {
				for (int n = 0; n < 4; n++) {
					mino_current.shape[m][n] = mino[rand_first].shape[m][n];
				}
			}
			mino_current.x = 3;
			//while the app is running:  GAMELOOP
			while (!quit) {
				//Handle events on queue
				while (SDL_PollEvent( &e )) {
					//User requests quit
					if (e.type == SDL_QUIT) {
						quit = 1;
					} else if (e.type == SDL_KEYDOWN) {
						//Select surfaces based on key press
						switch (e.key.keysym.sym) {
							case SDLK_UP:
								up_pressed = 1;
								break;
							case SDLK_DOWN:
								treshold = 200;
								break;
							case SDLK_LEFT:
								x_change = -1;
								break;
							case SDLK_RIGHT:
								x_change = 1;
								break;
							case SDLK_ESCAPE:
								gameState = GAMESTATE_MENU;
								break;
							case SDLK_RETURN:
								gameState = GAMESTATE_GAME;
								activeGame = 1;
								break;
							case SDLK_z:

								break;
							case SDLK_h:
								gameState = GAMESTATE_HIGHSCORE;
								break;
							case SDLK_b:
								quit = 1;
								break;
							default:

								break;
						}
					}
				}

					//Gamelogic
					switch (gameState) {
						case GAMESTATE_GAME:
							//rotation
							if (SDL_GetTicks() - key_timestamp > 200) {
								if (up_pressed) {
									//rotation
									for (int m = 0; m < 4; m++) {
										for (int n = 0; n < 4; n++) {
											if (!(game[mino_current.y + m][mino_current.x + n] && mino_current.shape[m + ((rotation + 4) % 16)][n])) {
												rotation_allowed = 1;
											}
										}
									}
									if (rotation_allowed){
										rotation = (rotation + 4) % 16;
									}
									rotation_allowed = 0;
									up_pressed = 0;
								}
								if (x_change != 0){

									//x movement
									for (int m = 0; m < 4; m++) {
										for (int n = 0; n < 4; n++) {
											if ((game[mino_current.y + m][mino_current.x + n + x_change] && mino_current.shape[m + rotation][n])) {
												x_change = 0;
											}
										}
									}
									mino_current.x += x_change;
									x_change = 0;
								}
								key_timestamp = SDL_GetTicks();
							}
							showGame();

							if (SDL_GetTicks() - down_timestamp > treshold) {
								treshold = 1000;
								if (!playGame()) {
									//Handle the game over
									activeGame = 0;
								}
								down_timestamp = SDL_GetTicks();
							}

							break;
						case GAMESTATE_MENU:
							showMenu();
							break;
						case GAMESTATE_HIGHSCORE:
							showHighscore();
							break;
						default:
							break;
					}


					countedFrames++;
			}
		} else {
			printf("Failed to load media!\n");
		}
	} else {
		printf("Failed to initialize!\n");
	}

	//Free resources and close SDL
	close();

	return 0;
}
