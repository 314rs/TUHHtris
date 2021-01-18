/*___            _      _    _       _____    _        _
|  _ \ _ __ ___ (_) ___| | _| |_ _  |_   _|__| |_ _ __(_)___
| |_) | '__/ _ \| |/ _ \ |/ / __(_)   | |/ _ \ __| '__| / __|
|  __/| | | (_) | |  __/   <| |_ _    | |  __/ |_| |  | \__ \
|_|   |_|  \___// |\___|_|\_\\__(_)   |_|\___|\__|_|  |_|___/
              |_*/
#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

#define GAMEWIDTH (10)
#define GAMEHEIGHT (18)

//Screen dimension constants
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

//The window we'll be rendering to
SDL_Window* gp_window = NULL;

//The window renderer
SDL_Renderer* gp_renderer = NULL;

//Current displayed texture
SDL_Texture* gp_Texture = NULL;

//Globally used font
TTF_Font* g_font = NULL;
SDL_Rect g_fontViewport = {400, 0, SCREEN_WIDTH - 400, 28};
SDL_Color g_textColor = {0, 0, 0};


//Top left corner viewport
SDL_Rect minoViewport = {0, 0, 40, 40};



int game[GAMEHEIGHT][GAMEWIDTH] = {	{1,0,0,0,0,0,0,0,0,1},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,1,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,1},
									{0,0,0,0,0,0,0,0,0,1},
									{1,0,0,0,0,0,0,0,1,1},
									{1,0,0,0,0,0,0,0,0,0},
									{1,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,1,0,0,0,0,0},
									{1,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{1,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{1,0,0,0,0,0,0,0,0,1},
};

struct minoTexture {
	SDL_Texture* p_texture;
	char path[20];
	int width;
	int height;
} mino_I = {NULL, "light_blue.png", 0, 0};

struct fontTexture {
	SDL_Texture* p_texture;
	char string[20];
	int width;
	int height;
} 	score = {NULL, "Average FPS", 0, 0},
	scoreNum = {NULL, "", 0, 0};

//Loads individual image as texture (hardware based rendering)
SDL_Texture* loadTextureFromFile(char path[], int *width, int *height);

//this will end in the header.h
int init(void);

int loadMedia();

void close(void);

void renderToViewport(SDL_Texture* texture, SDL_Rect* viewport);

SDL_Texture* loadTextureFromFont(char textString[], SDL_Color textColor,int *width, int *height);
//this goes in the *.o
int init() {
	//Initialization flag
	int success = 1;
	//Initialize SDL
	if(SDL_Init( SDL_INIT_VIDEO )) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = 0;
	} else {
		//Set texture filtering to linear
		if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}
		//Create window
		gp_window = SDL_CreateWindow("TUHHtris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if(gp_window == NULL) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = 0;
		} else {
			//Create renderer for window
		   gp_renderer = SDL_CreateRenderer(gp_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		   if(gp_renderer == NULL)  {
			   printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			   success = 0;
		   } else {
			   //Initialize renderer color
			   SDL_SetRenderDrawColor(gp_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = 0;
				}

				//Initialize SDL_ttf
			   if( TTF_Init() == -1 ) {
				   printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				   success = 0;
			   } else {
				   g_font = TTF_OpenFont("AtariClassic.ttf", 28);
				   if( g_font == 0 ) {
						printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
						success = 0;
					}
			   }
			}
		}
	}
	return success;
}

int loadMedia() {
	//Loading success flag
	int success = 1;

	//Load png texture
	mino_I.p_texture = loadTextureFromFile(mino_I.path, &mino_I.width, &mino_I.height);
	if(mino_I.p_texture == NULL) {
		printf("Failed to load texture image!\n");
		success = 0;
	}
	score.p_texture = loadTextureFromFont(score.string, g_textColor, &score.width, &score.height);
	//printf("width: %d, height: %d", score.width, score.height);
	//Set blending function
	//SDL_SetTextureBlendMode( score.p_texture, blending );
	//SDL_SetTextureAlphaMod( score.p_texture, alpha );


	return success;
}

void close() {
	//Free loaded image
	SDL_DestroyTexture(mino_I.p_texture);
    mino_I.p_texture = NULL;
	SDL_DestroyTexture(score.p_texture);
	score.p_texture = NULL;

	//Free global font
	TTF_CloseFont(g_font);
	g_font = NULL;

	//Destroy window
	SDL_DestroyRenderer( gp_renderer );
	SDL_DestroyWindow(gp_window);
	gp_window = NULL;
	gp_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void renderToViewport(SDL_Texture* texture, SDL_Rect* viewport) {
	//Clear screen
	SDL_SetRenderDrawColor( gp_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	//set viewport
	SDL_RenderSetViewport( gp_renderer, viewport);

	//Render texture to screen
	SDL_RenderCopy( gp_renderer, texture, NULL, NULL );
}

//load a texture form a file (path)
SDL_Texture* loadTextureFromFile(char path[], int *width, int *height) {
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gp_renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        } else {
			*width = loadedSurface->w;
			*height = loadedSurface->h;
		}

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

//load a texture from a font (string)
SDL_Texture* loadTextureFromFont(char textString[], SDL_Color textColor,int *width, int *height) {
	SDL_Texture* newTexture;
	SDL_Surface* textSurface = TTF_RenderText_Solid( g_font, textString, textColor );
	if( textSurface == NULL ) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	} else {
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gp_renderer, textSurface);
		if( newTexture == NULL ) {
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		} else {
			*width = textSurface->w;
			*height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return newTexture;
}


int main(int argc, char *argv[]) {
	//Initialize SDL
	if (init()) {
		//main loop flag
		int quit = 0;
		//Event handler
		SDL_Event e;
		uint32_t startTime = 0;
		char timeText[64];
		unsigned int countedFrames = 0;
		if (loadMedia()) {
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

			//clear backbuffer
			SDL_RenderClear( gp_renderer );

			//print the game gackground
			for (int i = 0; i < GAMEWIDTH * GAMEHEIGHT; i++) {
				if (game[i / GAMEWIDTH][i % GAMEWIDTH]) {
					minoViewport.y = (i / GAMEWIDTH) * 40;
					minoViewport.x = (i % GAMEWIDTH) * 40;
					renderToViewport(mino_I.p_texture, &minoViewport);
				}
			}
			g_fontViewport.y = 0;
			g_fontViewport.w = score.width;
			renderToViewport(score.p_texture, &g_fontViewport);
			g_fontViewport.y += score.height + 10;

			startTime = countedFrames / (SDL_GetTicks() / (float) 1000);
			sprintf(timeText, "%8u", startTime);
			//scoreNum.string = timeText;
			scoreNum.p_texture = loadTextureFromFont(timeText, g_textColor, &scoreNum.width, &scoreNum.height);
			g_fontViewport.w = scoreNum.width;
			renderToViewport(scoreNum.p_texture, &g_fontViewport);



			//Update screen
			SDL_RenderPresent(gp_renderer);
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
