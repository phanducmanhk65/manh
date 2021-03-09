
#include "function.h"
 #include "baseobject.h"
 #include "map.h"
 #include "mainobject.h"
 #include "imptimer.h"
BaseObject g_background;
bool InitData()
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
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Tạo cửa sổ
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gscreen = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gscreen == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gscreen, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}
bool LoadBackground()
{

    bool ret = g_background.LoadImg("img//nen.png",gscreen);

    if(ret==false)
        return false;
    return true;
}
void close()
{
    g_background.Free();

    SDL_DestroyRenderer( gscreen );
    gscreen=NULL;
	SDL_DestroyWindow( gWindow );
	gWindow=NULL;

	IMG_Quit();
	SDL_Quit();
}
int main( int argc, char* argv[] )
{
	ImpTimer fps_timer;
	if( InitData()==false )
	{
		printf( "Failed to initialize!\n" );
		return -1;
	}

    if(LoadBackground()==false)
     return -1;

     GameMap game_map;
     game_map.LoadMap("map/map01.dat");
     game_map.LoadTiles(gscreen);

    MainObject p_player;
    p_player.LoadImg("img//player_right.png",gscreen);
    p_player.set_clips();

    bool quit = false;


     while( !quit )
			{
			    fps_timer.start();
			while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                     p_player.HandleInputAction(e,gscreen);
				}
				SDL_SetRenderDrawColor( gscreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
                SDL_RenderClear(gscreen);
                g_background.Render(gscreen,NULL);
                game_map.DrawMap(gscreen);


                Map map_data = game_map.getMap();

                p_player.HandleBullet(gscreen);
                p_player.SetMapXY(map_data.start_x_,map_data.start_y_);
                p_player.DoPlayer(map_data);
                p_player.Show(gscreen);

                game_map.SetMap(map_data);
                game_map.DrawMap(gscreen);
                SDL_RenderPresent( gscreen );
                int real_imp_time = fps_timer.get_ticks();
                int time_one_frame= 1000/FRAME_PER_SECOND;
                if(real_imp_time<time_one_frame)
                {
                    int delay_time=time_one_frame-real_imp_time;
                    if(delay_time>=0)
                    SDL_Delay(delay_time);
                }
			}
     close();
  return 0;

}