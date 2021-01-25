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
			//create  first shapes
			mino_current.index = rand() % 7;
			mino_current.p_texture = mino[mino_current.index].p_texture;
			for (int m = 0; m < 16; m++) {
				for (int n = 0; n < 4; n++) {
					mino_current.shape[m][n] = mino[mino_current.index].shape[m][n];
				}
			}
			mino_current.x = 3;
			mino_next.index = rand() % 7;
			mino_next.p_texture = mino[mino_next.index].p_texture;
			for (int m = 0; m < 16; m++) {
				for (int n = 0; n < 4; n++) {
					mino_next.shape[m][n] = mino[mino_next.index].shape[m][n];
				}
			}
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
								if(gameState == GAMESTATE_GAME) {
									up_pressed = 1;
								}
								break;
							case SDLK_DOWN:
								if (gameState == GAMESTATE_GAME) {
									treshold = 50;
								}
								break;
							case SDLK_LEFT:
								if (gameState == GAMESTATE_GAME) {
									x_change = -1;
								}
								break;
							case SDLK_RIGHT:
								if (gameState == GAMESTATE_GAME) {
									x_change = 1;
								}
								break;
							case SDLK_ESCAPE:
								gameState = GAMESTATE_MENU;
								break;
							case SDLK_RETURN:
								if (gameState == GAMESTATE_MENU) {
									startGame();
								}
								break;
							case SDLK_z:
									if (activeGame) {
										gameState = GAMESTATE_GAME;
									}
								break;
							case SDLK_h:
								if (gameState == GAMESTATE_MENU) {
									gameState = GAMESTATE_HIGHSCORE;
								}
								break;
							case SDLK_b:
								if (gameState == GAMESTATE_MENU) {
									quit = 1;
								}
								break;
							case SDLK_c:
								if (gameState == GAMESTATE_GAME && (SDL_GetTicks() - change_timestamp) > 100) {
									change();
								}
							default:

								break;
						}
					}
				}

					//Gamelogic
					switch (gameState) {
						case GAMESTATE_GAME:

							//rotation - works
							if ((SDL_GetTicks() - rotation_timestamp > 100) && up_pressed) {
								//check if rotation is allowed
								rotation_allowed = 1;
								for (int m = 0; m < 4; m++) {
									for (int n = 0; n < 4; n++) {
										if (mino_current.shape[m + ((rotation + 4) % 16)][n]) {
											if ((game[mino_current.y + m][mino_current.x + n]) || (mino_current.x + n < 0) ||( mino_current.x + n >= GAMEWIDTH)) {
												rotation_allowed = 0;
											}
										}
									}
								}
								//rotate if allowed
								if (rotation_allowed){
									rotation = (rotation + 4) % 16;
								}
								//reset flags
								up_pressed = 0;
								rotation_timestamp = SDL_GetTicks();
							}

							//x movement - works
							if (SDL_GetTicks() - move_timestamp > 100) {
								if (x_change != 0) {
									for (int m = 0; m < 4; m++) {
										for (int n = 0; n < 4; n++) {
											if(mino_current.shape[m + rotation][n]) {
												if((mino_current.x + n + x_change < 0) || (mino_current.x + n + x_change >= GAMEWIDTH) || (game[mino_current.y + m][mino_current.x + n + x_change])) {
													x_change = 0;
												}
											}
										}
									}
									mino_current.x += x_change;
									x_change = 0;
									move_timestamp = SDL_GetTicks();
								}
							}

							//down movement
							if (SDL_GetTicks() - down_timestamp > treshold) {
								//check if
								mino_current.y ++;
								for (int m = 0; m < 4; m++) {
									for (int n = 0; n < 4; n++) {
										if (mino_current.shape[m + rotation][n]) {
											if(mino_current.y + m >= GAMEHEIGHT || (game[mino_current.y + m][mino_current.x + n])) {
												saveMinoToGame();
											}
										}
									}
								}


								treshold = 1000;
								down_timestamp = SDL_GetTicks();
							}

							showGame();

							break;
						case GAMESTATE_MENU:
							showMenu();
							break;
						case GAMESTATE_HIGHSCORE:
							showHighscore();
							break;
						case GAMESTATE_GAMEOVER:
							showGameOver();
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
