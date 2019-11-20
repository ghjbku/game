/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window
bool init();

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;
SDL_Surface* gCurrentSurface=NULL;
SDL_Surface* gLastSurface=NULL;

//the image that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL];


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Project crawl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
			{
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface( gWindow );
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	/* gPNGSurface = loadSurface( "guysitting.gif" );
	if( gPNGSurface == NULL )
	{
		printf( "Failed to load PNG image!\n" );
		success = false;
	}*/


//load default

	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("hAJrAck.png");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]==NULL)
	{
	printf("Failed to load default img\n");
	success=false;
	}
	//load up
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("guysitting.gif");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP]==NULL)
	{
	printf("Failed to load up img\n");
	success=false;
	}
	//load down
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN]==NULL)
	{
	printf("Failed to load dwn img\n");
	success=false;
	}

	//load left
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT]==NULL)
	{
	printf("Failed to load left img\n");
	success=false;
	}
	//load right
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("hAJrAck.png");
	if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT]==NULL)
	{
	printf("Failed to load rght img\n");
	success=false;
	}


	return success;
}

void close()
{
	//Free loaded image
	SDL_FreeSurface( gPNGSurface );
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
                	{
               		     //User requests quit
                	    if( e.type == SDL_QUIT )
                	    {
                	        quit = true;
                	    }
			  //User presses a key
		            else if( e.type == SDL_KEYDOWN )
		            {
						SDL_FillRect(gScreenSurface, NULL, 0x000000);
		                //Select surfaces based on key press
		                switch( e.key.keysym.sym )
		                {
		                    case SDLK_UP:
							gPNGSurface=gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							gCurrentSurface = gPNGSurface;
		                    break;

		                    case SDLK_DOWN:
							gPNGSurface=gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							gCurrentSurface = gPNGSurface;
		                    break;

		                    case SDLK_LEFT:
		                    gPNGSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							gCurrentSurface = gPNGSurface;
		                    break;

		                    case SDLK_RIGHT:
		                    gPNGSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							gCurrentSurface = gPNGSurface;
		                    break;

		                    default:
		                    gPNGSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							gCurrentSurface = gPNGSurface;
		                    break;
		                }
		            }
                	}  
//pictures strecthing into half of the window size
                SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = (SCREEN_HEIGHT)/2;
				//Apply the PNG image
				SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &stretchRect );
			
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}