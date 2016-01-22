//-------------------------------------------------------------------------------------- basketball game ------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------- include libraries-----------------------------------------------------------------------------
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <ctime>
#include <stdlib.h>
#include <cmath>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
using namespace std;
//----------------------------------------------------------------------- the menu which is displayed  at the firt of game ------------------------------------------------------------
int showmenu1(SDL_Surface* screen , TTF_Font* font  )
{
	int x,y;
	const int menunumber=2;
	const char* menuitem[menunumber]={ "play","exit"};//0,1
	SDL_Surface* menu[menunumber]={NULL};
	bool selected_item[menunumber]={0,0};
	SDL_Color color[menunumber]={{0,128,192},{255,128,0}};
	SDL_Rect position[menunumber];

	position[0].x=350;
	position[0].y=450;
	position[0].w=400;
	position[0].h=400;

	position[1].x=800;
	position[1].y=450;
	position[1].w=400;
	position[1].h=400;
	
	SDL_Rect position_logo;
	position_logo.x=350;
	position_logo.y=0;

	SDL_Surface* image=SDL_LoadBMP("logo.bmp");

	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xff, 0xff, 0xff ) );
	
	menu[0]=TTF_RenderText_Solid(font,menuitem[0],color[0]);
	menu[1]=TTF_RenderText_Solid(font,menuitem[1],color[0]);

	Mix_Chunk* effect4;
	Mix_Chunk* effect5;
	
	effect4 = Mix_LoadWAV("change.WAV");
	effect5 = Mix_LoadWAV("ok.WAV");
	
	SDL_Event event;
	while(1)	
	{
		for(int i=0;i<menunumber;i++)
			SDL_BlitSurface(menu[i],NULL,screen,&position[i]);

		SDL_BlitSurface(image,NULL,screen,&position_logo);


		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case(SDL_QUIT):
				{
					for(int i=0;i<menunumber;i++)
						SDL_FreeSurface(menu[i]);
						SDL_FreeSurface(image);
					
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
								Mix_PlayChannel(-1,effect4,0);

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
								Mix_PlayChannel(-1,effect5,0);
								SDL_Delay(500);

								SDL_FreeSurface( menu[0]);
								SDL_FreeSurface( menu[1]);
								SDL_FreeSurface(image);
								Mix_FreeChunk(effect4);
								Mix_FreeChunk(effect5);

								return i;
							}	
						}
					}
					break;
				}		
			}	
		}
		SDL_Flip(screen);
	}
	
}
//--------------------------------------------------------------------------- the menu which is displayed between the game ----------------------------------------------------------- 
int showmenu2(SDL_Surface* screen , TTF_Font* font)
{
	int x,y;
	const int menunumber=3;
	const char* menuitem[menunumber]={ "continue", "play again" , "exit"};//0,1,2
	SDL_Surface* menu[menunumber]={NULL};
	bool selected_item[menunumber]={0,0,0};
	SDL_Color color[menunumber]={{0,128,192},{255,128,0}};
	SDL_Rect position[menunumber];
	


	position[0].x=150;
	position[0].y=450;
	position[0].w=100;
	position[0].h=200;

	position[1].x=530;
	position[1].y=450;
	position[1].w=100;
	position[1].h=200;

	position[2].x=1000;
	position[2].y=450;
	position[2].w=100;
	position[2].h=200;
	
	SDL_Rect position_logo;
	position_logo.x=350;
	position_logo.y=0;

	SDL_Surface* image=SDL_LoadBMP("logo.bmp");

	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xff, 0xff, 0xff ) );
	
	menu[0]=TTF_RenderText_Solid(font,menuitem[0],color[0]);
	menu[1]=TTF_RenderText_Solid(font,menuitem[1],color[0]);
	menu[2]=TTF_RenderText_Solid(font,menuitem[2],color[0]);
	
	Mix_Chunk* effect4;
	Mix_Chunk* effect5;

	effect4 = Mix_LoadWAV("change.WAV");
	effect5 = Mix_LoadWAV("ok.WAV");
	
	SDL_Event event;
	while(1)	
	{
		for(int i=0;i<menunumber;i++)
			SDL_BlitSurface(menu[i],NULL,screen,&position[i]);

		SDL_BlitSurface(image,NULL,screen,&position_logo);

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case(SDL_QUIT):
				{
					for(int i=0;i<menunumber;i++)
						SDL_FreeSurface(menu[i]);
						SDL_FreeSurface(image);
					
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
							Mix_PlayChannel(-1,effect4,0);

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
								Mix_PlayChannel(-1,effect5,0);
								SDL_Delay(1000);
								
								SDL_FreeSurface( menu[0]);
								SDL_FreeSurface( menu[1]);
								SDL_FreeSurface( menu[2]);
								SDL_FreeSurface(image);
								Mix_FreeChunk(effect4);
								Mix_FreeChunk(effect5);

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
						Mix_PlayChannel(-1,effect5,0);
						SDL_Delay(500);

						SDL_FreeSurface( menu[0]);
						SDL_FreeSurface( menu[1]);
						SDL_FreeSurface( menu[2]);
						SDL_FreeSurface(image);
						Mix_FreeChunk(effect4);
						Mix_FreeChunk(effect5);

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
//---------------------------------------------------------------------------------- clculate the iterrator -------------------------------------------------------------------------------
int angle1(float teta)
{
	int iterrator;

	if(teta<0.26)
		iterrator=-14;

	else if(teta>=0.26 && teta<0.52)
		iterrator=-8;

	else if(teta>=0.52 && teta<0.78)
		iterrator=-6;

	else if(teta>=0.78 && teta<1.04)
		iterrator=-4;

	else if(teta>=1.04)
		iterrator=-2;

	return iterrator;
}


int angle2(float teta)
{
	int iterrator;

	if(teta<0.26)
		iterrator=+11;

	else if(teta>=0.26 && teta<0.52)
		iterrator=+6;

	else if(teta>=0.52 && teta<0.78)
		iterrator=+4;

	else if(teta>=0.78 && teta<1.04)
		iterrator=+2;

	else if(teta>=1.04)
		iterrator=+1;
	
	return iterrator;
}

//-------------------------------------------------------------------------------------------- main function ----------------------------------------------------------------------------
int main()
{
	//initialize the surface  "screen"
	SDL_Surface *screen = SDL_SetVideoMode(1300, 700 ,32, 0);

	//initialize the surface  "image"
	
	
	//Specify the initial position of the ball randomly
	srand(time(0));
	float x0_ball=rand()%700+300;
	float y0_ball=rand()%200+250;

	//initialize the X&Y coordinate of mouse in motion state
	float x_motion;
	float y_motion;

	//initialize the X&Y coordinate of mouse in click state
	float x_click;
	float y_click;

	//initiaize the X&Y coordinate of ball during moving 
	float x_ball=x0_ball;
	float y_ball=y0_ball;

	//initialize the  X&Y coordinate of the previous ball for animation
	float x=x0_ball;
	float y=y0_ball;

	//intialize
	float a;
	int counter=0;

	//intialize an iterrator to animate the ball
	int iterrator;	

	float teta;

	//whether the game loop is running or not	
	bool running;

	//whether mouse click is occured or not
	bool flag1=0;
	
	//Whether the ball hit the ground or not
	bool flag2=0;
	
	//whether the ball hit the basketball board or not
	bool flag3=0;
	
	//whether the ball hit the rod of ring or not
	bool flag4=0;
	
	//whether the ball hit the inside ring or not
	bool flag5=0;

	//whther the ball hit the outside ring or not
	bool flag6=0;

	//whether the ball hit the edge(up) side of basketball board
	bool flag7=0;

	//whether the bal hit the edge(down) side of asketball board 
	bool flag8=0; 

	//initialize the sound effect
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);

	Mix_Chunk *effect1;
	Mix_Chunk *effect2;
	Mix_Chunk *effect3;
	Mix_Chunk *effect4;
	Mix_Chunk *effect5;
	

	effect1 = Mix_LoadWAV("muro_2.wav");
	effect2 = Mix_LoadWAV("ball_wood_schiacc.wav"); 
	effect3 = Mix_LoadWAV("palo_metal.wav");
	
	
	
	//initialize the font 
	TTF_Init();
	TTF_Font* font;
	font=TTF_OpenFont("PLAYBILL.TTF",120);
	TTF_SetFontStyle(font,TTF_STYLE_ITALIC );
	TTF_GetFontStyle(font);

	float x0=x0_ball;
	float y0=y0_ball;
	

	//show  first menu in screen
	int i=showmenu1(screen,font);
	if(i==0)
	{
	 	running=true;
	}
	else if(i==1)
	{
		running=false;
	}



	//game loop
	while(running)
	{
	
		SDL_Surface* image = SDL_LoadBMP("court.bmp");
		filledEllipseRGBA(image,x_ball,y_ball,7,7,255,128,0,255);

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case (SDL_QUIT):
				{
					running=false;
					break;
				}
				case(SDL_MOUSEMOTION):
				{
					x_motion=event.motion.x;
					y_motion=event.motion.y;
					break;
					
				}
				case(SDL_MOUSEBUTTONDOWN):
				{
					switch(event.button.button)
					{
						case(SDL_BUTTON_LEFT):
						{	x_click=event.button.x;
							y_click=event.button.y;
							if(x_click<=x0 && y_click<=y0 && flag1==0)	 
							{
								
								
								a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));
								
								teta=atan(abs((y0_ball-y_click)/(x0_ball-x_click)));
								iterrator=angle1(teta);

								flag1=1;
								flag2=0;
								flag3=0;
								flag4=0;
								flag5=0;
								flag6=0;
								flag7=0;
								flag8=0;
							}
							break;
						}	
					}
					break;
				}
				case(SDL_KEYDOWN):
				{
					switch(event.key.keysym.sym)
					{
						case(SDLK_ESCAPE):
						{
						
						i=showmenu2(screen,font);
							if(i==1)
							{
								x0_ball=rand()%700+300;
								y0_ball=rand()%200+250;

								x_ball=x0_ball;
								y_ball=y0_ball;
								
								x=x0_ball;
								y=y0_ball;
						
								flag1=0;
								flag2=0;
								flag3=0;
								flag4=0;
								flag5=0;
								flag6=0;
								flag7=0;
								flag8=0;
								
								counter=0;
								
								filledEllipseRGBA(image,x_ball,y_ball,7,7,255,128,0,255);

								running=true;
								
							}
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

		//Logical calculation ball motion

		//check whether the ball hit the ground or not 
		if(y_ball>=560 )	
		{	
			// sound effect
			Mix_PlayChannel(-1,effect1,0);

			counter++;

			//Which side has the ball hit the ground left or right

			//right side
			if(x>x_ball)
			{
				//Calculate the coordinates of the peak of next move of ball
				x_click=x_ball-((x0_ball-x_click)*0.6);
				y_click=560 - ((560-y_click)*0.5);
				
				x0_ball=x_ball;
				y0_ball=559;

				iterrator=angle1(teta);
			}
			
			//left side
			else
			{
				//Calculate the coordinates of the peak of next move of ball
				x_click=x_ball+((x_ball-x_click)*0.6);
				y_click=560-((y_ball-y_click)*0.5);
				
				x0_ball=x_ball;
				y0_ball=559;

				iterrator=angle2(teta);
					
			}

			a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));
			
			flag1=1;
			flag2=1;
			flag3=0;
			flag4=0;
			flag5=0;
			flag6=0;
			flag7=0;
			flag8=0;
		}
		
		if(counter==3)	//3 ground colleisions
			break;

		//check whether the ball hit the basketbal board or not		
		if( x_ball>=147 && x_ball<=160 && y_ball>=258 && y_ball<=336 && flag3==0 )
		{	
			//sound effect
			Mix_PlayChannel(-1,effect2,0);

			x_click=x_ball;
			y_click=y_ball;
			
			x0_ball=x_ball;
			y0_ball=y_ball;
			
			a=4*a;
			
			iterrator=-1*iterrator;
			
			flag1=1;
			flag2=0;
			flag3=1;
			flag4=0;
			flag5=0;
			flag6=0;
			flag7=0;
			flag8=0;
		}

		//check whether the ball hit the rod of ring or not
		if(x_ball>=157 && x_ball<=180 && y_ball>=321 && y_ball<=330 && flag4==0)
		{	
			// sound effect
			Mix_PlayChannel(-1,effect3,0);

			y_click = 325 - ((y0_ball-y_click)/4);
			x_click = 190;			
			
			x0_ball=x_ball;
			y0_ball=y_ball;
			
			a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));

			iterrator=angle2(teta);			
			
			flag1=1;
			flag2=0;
			flag3=0;
			flag4=1;
			flag5=0;
			flag6=0;
			flag7=0;
			flag8=0;
		}

		//check whether the ball hit the inside ring or not
		if(x_ball>=203 && x_ball<=208 && y_ball>=321 && y_ball<=330 && flag5==0)
		{
			// sound effect
			Mix_PlayChannel(-1,effect3,0);

			y_click = 325 - ((y0_ball-y_click)/4);
			x_click = 190;			
			
			x0_ball=x_ball;
			y0_ball=y_ball;
			
			a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));

			iterrator=angle1(teta);

			flag1=1;
			flag2=0;
			flag3=0;
			flag4=0;
			flag5=1;
			flag6=0;
			flag7=0;
			flag8=0;
		}

		//check whether the ball hit the outside ring or not
		if(x_ball>=210 && x_ball<=215 && y_ball>=321 && y_ball<=330 && flag6==0)
		{
			// sound effect
			Mix_PlayChannel(-1,effect3,0);

			x_click = 215 + ((x0_ball-x_click)/4);
			y_click = 325 - ((y0_ball-y_click)/4);
		
			x0_ball=x_ball;
			y0_ball=y_ball;
			
			a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));

			iterrator=angle2(teta);

			flag1=1;
			flag2=0;
			flag3=0;
			flag4=0;
			flag5=0;
			flag6=1;
			flag7=0;
			flag8=0;
		}

		//check whther the ball hit the edge(up) side of basketball board
		if(x_ball>=171 && x_ball<=179 && y_ball>=245 && y_ball<=253 && flag7==0 && flag8==0)
		{
			//sound effect
			Mix_PlayChannel(-1,effect2,0);

			x_click = 175 - ((x0_ball-x_click)/4);
			y_click = 250 - ((y0_ball-y_click)/4);
		
			x0_ball=x_ball;
			y0_ball=y_ball;
			
			a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));

			iterrator=angle1(teta);			
			
			flag1=1;
			flag2=0;
			flag3=0;
			flag4=0;
			flag5=0;
			flag6=0;
			flag7=1;
			flag8=0;
		}	
			
		//check whther the ball hit the edge(down) side of basketball board
		if(x_ball>=155 && x_ball<=163 && y_ball>=255 && y_ball<=263 && flag7==0 && flag8==0 )
		{
			//sound effect
			Mix_PlayChannel(-1,effect2,0);
			
			x_click = 160 + ((x0_ball-x_click)/4);
			y_click = 260 - ((y0_ball-y_click)/4);
		
			x0_ball=x_ball;
			y0_ball=y_ball;
			
			a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));

			iterrator=angle2(teta);

			flag1=1;
			flag2=0;
			flag3=0;
			flag4=0;
			flag5=0;
			flag6=0;
			flag7=0;
			flag8=1;
			
		}

		// move of ball
		if(flag1==1)
		{

			y_ball= a*(x_ball -x_click)*(x_ball -x_click) + y_click;
			x=x_ball;
			x_ball+=iterrator;
		}

		SDL_BlitSurface(image,NULL,screen,NULL);
		SDL_Flip(screen);
		SDL_FreeSurface(image);
	}

	

	Mix_FreeChunk(effect1);
	Mix_FreeChunk(effect2);
	Mix_FreeChunk(effect3);
	
	Mix_CloseAudio();
	Mix_Quit();

	TTF_CloseFont(font);
	TTF_Quit();

	SDL_Delay(200);
	SDL_Quit;	
	
	return 0;
}
