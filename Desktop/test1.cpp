#include<SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include<SDL/SDL_ttf.h>
#include<iostream>
using namespace std;

int showmenu(SDL_Surface* screen , TTF_Font* font)
{
	int x,y;

	const int menunumber=3;
	const char* menuitem[menunumber]={ "continue", "play again" , "exit"};//0,1,2
	SDL_Surface* menu[menunumber];
	bool selected_item[menunumber]={0,0,0};
	SDL_Color color[menunumber]={{255,255,255},{255,0,0}};
	SDL_Rect position[menunumber];

	position[0].x=200;
	position[0].y=500;
	position[0].w=200;
	position[0].h=200;

	position[1].x=500;
	position[1].y=500;
	position[1].w=200;
	position[1].h=200;

	position[2].x=900;
	position[2].y=500;
	position[2].w=200;
	position[2].h=200;
	
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
	
	menu[0]=TTF_RenderText_Solid(font,menuitem[0],color[0]);
	menu[1]=TTF_RenderText_Solid(font,menuitem[1],color[0]);
	menu[2]=TTF_RenderText_Solid(font,menuitem[2],color[0]);
	
	SDL_Event event;
	while(1)	
	{
		for(int i=0;i<menunumber;i++)
			SDL_BlitSurface(menu[i],NULL,screen,&position[i]);

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case(SDL_QUIT):
				{
					for(int i=0;i<menunumber;i++)
						SDL_FreeSurface(menu[i]);
					
					return 2;
					break;
				}	
				case(SDL_MOUSEMOTION):
				{
					x=event.motion.x;
					y=event.motion.y;
					for(int i=0; i<menunumber;i++)
					{
						if( x>=position[i].x && x<=position[i].x+position[i].w && y>=position[i].y && y<=position[i].y+position[i].h )
						{
							if(selected_item[i]!=1)
							{
								SDL_FreeSurface(menu[i]);
								menu[i]=TTF_RenderText_Solid(font,menuitem[i],color[1]);
								selected_item[i]=1;									
							}
								
						}
						else
						{
							if(selected_item[i]==1)
							{
								SDL_FreeSurface(menu[i]);
								menu[i]=TTF_RenderText_Solid(font,menuitem[i],color[0]);
								selected_item[i]=0;	
							}
						}
					}
					break;
				}
				case(SDL_MOUSEBUTTONDOWN):
				{				
					if(event.button.button=SDL_BUTTON_LEFT)
					{
						x=event.button.x;
						y=event.button.y;
						for(int i=0;i<menunumber;i++)
						{
							if(x>=position[i].x && x<=position[i].x + position[i].w && y>=position[i].y && y<=position[i].y + position[i].h)
							{	
								SDL_FreeSurface( menu[0]);
								SDL_FreeSurface( menu[1]);
								SDL_FreeSurface( menu[2]);
								
								return i;
							}	
						}
					}
					break;
				}
				case(SDL_KEYDOWN):
				{
					if(event.key.keysym.sym=SDLK_ESCAPE)
					{
						SDL_FreeSurface( menu[0]);
						SDL_FreeSurface( menu[1]);
						SDL_FreeSurface( menu[2]);
						
						return 0;
					}
					break;
				}	
					
			}
				
		}
		

		SDL_Flip(screen);
		SDL_Delay(20);
	}
	
}


int main() 
{
	
	SDL_Surface* screen = SDL_SetVideoMode( 1200 , 800 , 32 , 0 );

	TTF_Init();
	TTF_Font* font;
	font=TTF_OpenFont("Adler.ttf",32);
	SDL_Color color={255,255,255};
	SDL_Surface* text= TTF_RenderText_Solid(font,"hello world",color);
	bool running=true;

	int i=showmenu(screen,font);
	if(i==2)
	{
	 	running=false;
	}
	while(running)
	{
		SDL_Event event;
		while(SDL_PollEvent(& event))
		{
			switch (event.type)
			{
				case(SDL_QUIT):
				{
					running=false;
					break;
				}
				case(SDL_KEYDOWN):
				{
					switch(event.key.keysym.sym)
					{
						case(SDLK_ESCAPE):
						{
						i=showmenu(screen,font);
							if(i==2)
							{
								running=false;
							}
						break;
						}
					}
					break;
				}

			}
		}
	//logic

	//render
	SDL_BlitSurface(text,NULL,screen,NULL);
	SDL_Flip(screen);
	SDL_Delay(20);
	}

	
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	SDL_Delay(2000);
	return 0;
	
}
