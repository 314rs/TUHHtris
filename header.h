
#define GAMEWIDTH (10)
#define GAMEHEIGHT (18)
#define GAMESTATE_MENU 0
#define GAMESTATE_GAME 1
#define GAMESTATE_HIGHSCORE 2

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

//timing
unsigned int treshold = 1000;
uint32_t down_timestamp = 0;
uint32_t startTime = 0;
char timeText[64];
unsigned int countedFrames = 0;
uint32_t rotation_timestamp = 0;
uint32_t move_timestamp = 0;

int gameState = 0;
int activeGame = 0;
int rand_first = 0;
int next_rand;
int rotation = 0;
int up_pressed = 0;
int x_change = 0;
int rotation_allowed = 0;

//Top left corner viewport
SDL_Rect minoViewport = {0, 0, 40, 40};



int game[GAMEHEIGHT][GAMEWIDTH] = {	{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
									{0,0,0,0,0,0,0,0,0,0},
};
int game_current[GAMEHEIGHT][GAMEWIDTH];

struct minoTexture {
	SDL_Texture* p_texture;
	char path[20];
	int width;
	int height;
	int shape[16][4];
} mino[7] = {
		{NULL, "media/light_blue.png", 0, 0, {
			{1, 1, 1, 1}, //1.
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{0, 1, 0, 0}, //2.
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},

			{1, 1, 1, 1}, //3.
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{0, 1, 0, 0}, //4.
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
		}},
		{NULL, "media/blue.png", 0, 0, {
			{2, 2, 2, 0}, //1.
			{0, 0, 2, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{2, 2, 0, 0}, //2.
			{2, 0, 0, 0},
			{2, 0, 0, 0},
			{0, 0, 0, 0},

			{2, 0, 0, 0}, //3.
			{2, 2, 2, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{0, 2, 0, 0}, //4.
			{0, 2, 0, 0},
			{2, 2, 0, 0},
			{0, 0, 0, 0},
		}},
		{NULL, "media/orange.png", 0, 0, {
			{3, 3, 3, 0}, //1.
			{3, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{3, 0, 0, 0}, //2.
			{3, 0, 0, 0},
			{3, 3, 0, 0},
			{0, 0, 0, 0},

			{0, 0, 3, 0}, //3.
			{3, 3, 3, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{3, 3, 0, 0}, //4.
			{0, 3, 0, 0},
			{0, 3, 0, 0},
			{0, 0, 0, 0},
		}},
		{NULL, "media/yellow.png", 0, 0, {
			{4, 4, 0, 0}, //1.
			{4, 4, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{4, 4, 0, 0}, //2.
			{4, 4, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{4, 4, 0, 0}, //3.
			{4, 4, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{4, 4, 0, 0}, //4.
			{4, 4, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
		}},
		{NULL, "media/green.png", 0, 0, {
			{0, 5, 5, 0}, //1.
			{5, 5, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{5, 0, 0, 0}, //2.
			{5, 5, 0, 0},
			{0, 5, 0, 0},
			{0, 0, 0, 0},

			{0, 5, 5, 0}, //3.
			{5, 5, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{5, 0, 0, 0}, //4.
			{5, 5, 0, 0},
			{0, 5, 0, 0},
			{0, 0, 0, 0},
		}},
		{NULL, "media/violett.png", 0, 0, {
			{6, 6, 6, 0}, //1.
			{0, 6, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{6, 0, 0, 0}, //2.
			{6, 6, 0, 0},
			{6, 0, 0, 0},
			{0, 0, 0, 0},

			{0, 6, 0, 0}, //3.
			{6, 6, 6, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{0, 6, 0, 0}, //4.
			{6, 6, 0, 0},
			{0, 6, 0, 0},
			{0, 0, 0, 0},
		}},
		{NULL, "media/red.png", 0, 0, {
			{7, 7, 0, 0}, //1.
			{0, 7, 7, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{0, 7, 0, 0}, //2.
			{7, 7, 0, 0},
			{7, 0, 0, 0},
			{0, 0, 0, 0},

			{7, 7, 0, 0}, //3.
			{0, 7, 7, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},

			{0, 7, 0, 0}, //4.
			{7, 7, 0, 0},
			{7, 0, 0, 0},
			{0, 0, 0, 0},
		}}
	};

struct generalTexture {
	SDL_Texture* p_texture;
	char path[20];
	int width;
	int height;
} 	logo = {NULL, "media/logo.png", 0, 0},
	black = {NULL, "media/blackdots.png", 0, 0};

struct minoGame {
	SDL_Texture* p_texture;
	int shape[16][4];
	int x;
	int y;
} 	mino_current = {NULL, {
	{0, 0, 0, 0}, //1.
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{0, 0, 0, 0}, //2.
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{0, 0, 0, 0}, //3.
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{0, 0, 0, 0}, //4.
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}}, 3, 0},
	mino_next = {NULL, {
		{0, 0, 0, 0}, //1.
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},

		{0, 0, 0, 0}, //2.
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},

		{0, 0, 0, 0}, //3.
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},

		{0, 0, 0, 0}, //4.
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}}, 14, 12};

struct fontTexture {
	SDL_Texture* p_texture;
	char	 string[20];
	int width;
	int height;
} 	score = {NULL, "Score:", 0, 0},
	scoreNum = {NULL, "", 0, 0},
	start = {NULL, "Neues Spiel [Enter]", 0, 0},
	endButton = {NULL, "Spiel [b]eenden", 0, 0},
	highscoreButton = {NULL, "[H]ighscore anzeigen", 0, 0},
	resumeButton = {NULL, "[z]urueck zum Spiel", 0, 0};


//Loads individual image as texture (hardware based rendering)
SDL_Texture* loadTextureFromFile(char path[], int *width, int *height);

//this will end in the header.h
int init(void);

int loadMedia();

void close(void);

void renderToViewport(SDL_Texture* texture, SDL_Rect* viewport);

SDL_Texture* loadTextureFromFont(char textString[], SDL_Color textColor,int *width, int *height);

void showGame(void);

void showMenu(void);

void showHighscore(void);

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
			//set icon
			SDL_Surface* surfaceIcon = IMG_Load(logo.path);
		    if (surfaceIcon == NULL) {
		        printf( "Unable to load icon! SDL_image Error: %s\n", IMG_GetError() );
		    }
			SDL_SetWindowIcon(gp_window, surfaceIcon);
			SDL_FreeSurface(surfaceIcon);
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
	for (int i = 0; i < 7; i++) {
		mino[i].p_texture = loadTextureFromFile(mino[i].path, &mino[i].width, &mino[i].height);
		if(mino[i].p_texture == NULL) {
			printf("Failed to load texture image!\n");
			success = 0;
		}
	}

	black.p_texture = loadTextureFromFile(black.path, &black.width, &black.height);
	if(black.p_texture == NULL) {
		printf("Failed to load texture image!\n");
		success = 0;
	}
	score.p_texture = loadTextureFromFont(score.string, g_textColor, &score.width, &score.height);
	//printf("width: %d, height: %d", score.width, score.height);
	//Set blending function
	//SDL_SetTextureBlendMode( score.p_texture, blending );
	//SDL_SetTextureAlphaMod( score.p_texture, alpha );
	start.p_texture = loadTextureFromFont(start.string, g_textColor, &start.width, &start.height);
	endButton.p_texture = loadTextureFromFont(endButton.string, g_textColor, &endButton.width, &endButton.height);
	highscoreButton.p_texture = loadTextureFromFont(highscoreButton.string, g_textColor, &highscoreButton.width, &highscoreButton.height);
	resumeButton.p_texture = loadTextureFromFont(resumeButton.string, g_textColor, &resumeButton.width, &resumeButton.height);


	return success;
}

void close() {
	//Free loaded image
	for (int i = 0; i < 7; i++) {
		SDL_DestroyTexture(mino[i].p_texture);
		mino[i].p_texture = NULL;
	}
	SDL_DestroyTexture(score.p_texture);
	score.p_texture = NULL;
	SDL_DestroyTexture(black.p_texture);
	black.p_texture = NULL;

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

void saveMinoToGame(void) {
	//function is called, when its too late. so go back up one line
	mino_current.y--;
	if(mino_current.y < 0) {
		printf("game over\n");
		//handle the game over
	}
	//mino_current in game
	for (int m = 0; m < 4; m++) {
		for (int n = 0; n < 4; n++) {
			if (mino_current.shape[m + rotation][n]) {
				game[m + mino_current.y][n + mino_current.x] = mino_current.shape[m + rotation][n];
			}
		}
	}
	//check for full rows
	int fullrow;
	int fullrowsum = 0;
	for (int m = (GAMEHEIGHT - 1); m >= 0; m--) {
		fullrow = 1;
		for (int n = 0; n < GAMEWIDTH; n++) {
			if (!game[m][n]) {
				fullrow = 0;
				break;
			}
		}

		if (fullrow) {
			printf("line %d is full.\n", GAMEHEIGHT - m + fullrowsum);
			fullrowsum++;
			for (int n1 = 0; n1 < GAMEWIDTH; n1++) {
				for (int m1 = m; m1 > 0; m1--) {
					game[m1][n1] = game[m1 - 1][n1];
				}
				game[0][n1] = 0;
			}
			m++;
		}
	}

	//mino_current = mino_next
	mino_current.y = 0;
	mino_current.x = 3;
	rotation = 0;
	mino_current.p_texture = mino[next_rand].p_texture;
	for (int m = 0; m < 16; m++) {
		for (int n = 0; n < 4; n++) {
			mino_current.shape[m][n] = mino[next_rand].shape[m][n];
		}
	}
	next_rand = rand() % 7;
	mino_next.p_texture = mino[next_rand].p_texture;
	for (int m = 0; m < 16; m++) {
		for (int n = 0; n < 4; n++) {
			mino_next.shape[m][n] = mino[next_rand].shape[m][n];
		}
	}
}

void showGame(void) {
	//clear backbuffer
	SDL_RenderClear( gp_renderer );

	//game in game_current
	for (int m = 0; m < GAMEHEIGHT; m++) {
		for (int n = 0; n < GAMEWIDTH; n++) {
			game_current[m][n] = game[m][n];
		}
	}

	// mino_current in game_current
	for (int m = 0; m < 4; m++) {
		for (int n = 0; n < 4; n++) {
			if (mino_current.shape[m + rotation][n]) {

				game_current[m + mino_current.y][n + mino_current.x] = mino_current.shape[m + rotation][n];
			}
		}
	}

	//render game_current
	for (int i = 0; i < GAMEWIDTH * GAMEHEIGHT; i++) {
		minoViewport.y = (i / GAMEWIDTH) * 40;
		minoViewport.x = (i % GAMEWIDTH) * 40;
		int square = game_current[i / GAMEWIDTH][i % GAMEWIDTH];
		if (square) {
			renderToViewport(mino[square - 1].p_texture, &minoViewport);
		} else {
			renderToViewport(black.p_texture, &minoViewport);
		}
	}

	//print next mino
	for (int i = 0; i < 4 * 4; i++) {
		minoViewport.y = (i / 4) * 40 + 480;
		minoViewport.x = (i % 4) * 40 + 480;
		int square = mino_next.shape[i / 4][i % 4];
		if (square) {
			renderToViewport(mino_next.p_texture, &minoViewport);
		}
	}

	//"Score:"
	g_fontViewport.y = 0;
	g_fontViewport.x = 400;
	g_fontViewport.w = score.width;
	renderToViewport(score.p_texture, &g_fontViewport);
	g_fontViewport.y += score.height + 10;
	//score
	startTime = countedFrames / (SDL_GetTicks() / (float) 1000);
	sprintf(timeText, "%8u", startTime);
	scoreNum.p_texture = loadTextureFromFont(timeText, g_textColor, &scoreNum.width, &scoreNum.height);
	g_fontViewport.w = scoreNum.width;
	renderToViewport(scoreNum.p_texture, &g_fontViewport);
	SDL_DestroyTexture(scoreNum.p_texture);
	scoreNum.p_texture = NULL;

	//Update screen
	SDL_RenderPresent(gp_renderer);
}

void showMenu(void) {
	//clear backbuffer
	SDL_RenderClear( gp_renderer );

	g_fontViewport.x = SCREEN_WIDTH / 2 - (start.width / 2);
	g_fontViewport.y = 20;
	g_fontViewport.w = start.width;
	renderToViewport(start.p_texture, &g_fontViewport);

	if (activeGame) {
		g_fontViewport.y += 60;
		g_fontViewport.w = resumeButton.width;
		g_fontViewport.x = SCREEN_WIDTH / 2 - (resumeButton.width / 2);
		renderToViewport(resumeButton.p_texture, &g_fontViewport);
	}

	g_fontViewport.y += 60;
	g_fontViewport.w = endButton.width;
	g_fontViewport.x = SCREEN_WIDTH / 2 - (endButton.width / 2);
	renderToViewport(endButton.p_texture, &g_fontViewport);

	g_fontViewport.y += 60;
	g_fontViewport.w = highscoreButton.width;
	g_fontViewport.x = SCREEN_WIDTH / 2 - (highscoreButton.width / 2);
	renderToViewport(highscoreButton.p_texture, &g_fontViewport);





	//Update screen
	SDL_RenderPresent(gp_renderer);

}

void showHighscore(void) {
	renderToViewport(score.p_texture, &g_fontViewport);
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
