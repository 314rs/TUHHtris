/*___            _      _    _       _____    _        _
|  _ \ _ __ ___ (_) ___| | _| |_ _  |_   _|__| |_ _ __(_)___
| |_) | '__/ _ \| |/ _ \ |/ / __(_)   | |/ _ \ __| '__| / __|
|   __/| | | (_) | |  __/   <| |_ _    | |  __/ |_| |  | \__ \
|_|   |_|  \___// |\___|_|\_\\__(_)   |_|\___|\__|_|  |_|___/
              |_*/
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//The window we'll be rendering to
SDL_Window* gp_window = NULL;

//The surface contained by the window
SDL_Surface* gp_screenSurface = NULL;

//this will end in the header
int init(void);

void close(void);

//this goes in the *.o
int init() {
	//Initialization flag
	int success = 1;
	//Initialize SDL
	if(SDL_Init( SDL_INIT_VIDEO )) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = 0;
	} else {
		//Create window

		gp_window = SDL_CreateWindow("TUHHtris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if(gp_window == NULL) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = 0;
		} else {
			//Get window surface
			//gp_screenSurface = SDL_GetWindowSurface(gp_window);
		}
	}

	return success;
}

void close() {
	//Deallocate surface
	SDL_FreeSurface( gp_screenSurface );
	gp_screenSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gp_window );
	gp_window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char *argv[]) {
	//Initialize SDL
	if (init()) {
		//main loop flag
		int quit = 0;
		//Event handler
		SDL_Event e;

		//while the app is running:
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

							break;
						case SDLK_DOWN:

							break;
						case SDLK_LEFT:

							break;
						case SDLK_RIGHT:

							break;
						default:

							break;
					}
				}
			}
			gp_screenSurface = SDL_GetWindowSurface(gp_window);
			//Fill the surface white
			SDL_FillRect(gp_screenSurface, NULL, SDL_MapRGB(gp_screenSurface->format, 0xFF, 0x00, 0x00));

			//Update the surface
			SDL_UpdateWindowSurface(gp_window);
		}
	} else {
		printf("Failed to initialize!\n");
	}

	//Free resources and close SDL
	close();

	return 0;
}
