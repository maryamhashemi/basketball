#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <ctime>
#include <stdlib.h>
#include <cmath>
#include <SDL/SDL_mixer.h>
using namespace std;



int main()
{

	//ball = SDL_LoadBMP("ss.bmp");	

	//initialize the surface  "screen"
	SDL_Surface *screen = SDL_SetVideoMode(1300, 700 ,32, 0);

	//initialize the surface  "image"
	SDL_Surface *image = SDL_LoadBMP("court.bmp");;
	
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

	//whether the game loop is running or not	
	bool running=true;

	//whether mouse click is occured or not
	bool flag1=0;
	
	//Whether the ball hit the ground or not
	bool flag2=0;
	
	//whether the ball hit the basketball board or not
	bool flag3=0;

	//change the background color
	boxRGBA(screen, 0,0, 1300, 700, 255,255,255, 255);     

	//display ball in "image"
	filledEllipseRGBA(image,x0_ball,y0_ball,7,7,0,0,0,255);
	
	//initialize the sound effect
	Mix_Chunk *effect1;
	Mix_Chunk *effect2;
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	effect1 = Mix_LoadWAV("muro_2.wav");
	effect2 = Mix_LoadWAV("ball_wood_schiacc.wav"); 
	

	float x0=x0_ball;
	float y0=y0_ball;

	int counter=0;

		

	//game loop
	while(running)
	{	

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

						{	
							//check where the mouse click
							if(event.button.x<=x0 && event.button.y<=y0 && flag1==0)	 
							{
								x_click=event.button.x;
								y_click=event.button.y;
								
								a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));

								flag1=1;
							}
							break;
						}	
					}
					break;
				}	
			}	
		}

		//Logical calculation ball motion

		//first move of ball
		if(flag1==1)	
		{	
			y_ball= a*(x_ball -x_click)*(x_ball -x_click) + y_click;
			
			filledEllipseRGBA(image,x,y,7,7,255,255,255,255);
			filledEllipseRGBA(image,x_ball,y_ball,7,7,0,0,0,255);
			
			x=x_ball;
			y=y_ball;

			if(abs(y_click-y0_ball)>=50 && abs(y_click-y0_ball)<=100 && abs(x_click-x0_ball)<=50)
				x_ball-=2;

			else if(abs(y_click-y0_ball)>100 && abs(x_click-x0_ball)<=50)
				x_ball-=1;

			else
				x_ball-=4;
		}

		//check whether the ball hit the ground or not 
		if(y_ball>=560 )	
		{	
			Mix_PlayChannel(-1,effect1,0);
			counter++;
			//Which side has the ball hit the ground left or right

			//right side
			if(x>x_ball)
			{
				//Calculate the coordinates of the peak of next move of ball
				x_click=x_ball-((x0_ball-x_click)*0.6);
				y_click=560 - ((560-y_click)*0.5);
			}
			
			//left side
			else
			{
				//Calculate the coordinates of the peak of next move of ball
				x_click=x_ball+((x_ball-x_click)*0.6);
				y_click=560-((y_ball-y_click)*0.5);
				
			}

			x0_ball=x_ball;
			y0_ball=559;

			a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));

			flag1=0;
			flag2=1;
			flag3=0;
		}
		
		if(counter==3)	//3 ground colleisions
			break;

		// move of ball after hitting the ground
		if(flag2==1)
		{
			y_ball= a*(x_ball -x_click)*(x_ball -x_click) + y_click;

			filledEllipseRGBA(image,x,y,7,7,255,255,255,255);
			filledEllipseRGBA(image,x_ball,y_ball,7,7,0,0,0,255);
	
			if(x>x_ball)
			{
				x=x_ball;
				y=y_ball;
				
				if(abs(y_click-y0_ball)>=50 && abs(y_click-y0_ball)<=100 && abs(x_click-x0_ball)<=50)
					x_ball-=2;				
				else
					x_ball-=3;
				
				SDL_Delay(2);
			}
			else
			{
				x=x_ball;
				y=y_ball;

				x_ball+=3;


				SDL_Delay(2);
			}
		}
		

		//check whether the ball hit the basketbal board or not		
		if(((x_ball>=153 && x_ball<=156 && y_ball>=258 && y_ball<=336)
		  || (((x_ball>=157 && x_ball<=181) || (x_ball>=196 && x_ball<=216)) 
		  && (y_ball>=317 && y_ball<=337))) && flag3==0 )
		{
			Mix_PlayChannel(-1,effect2,0);
			x_click=x_ball;
			y_click=y_ball;
			
			x0_ball=x_ball;
			y0_ball=y_ball;
			
			flag1=0;
			flag2=0;
			flag3=1;
		}

		// move of ball after hitting the basketball board
		if(flag3==1)
		{
			y_ball= 4*a*(x_ball -x_click)*(x_ball -x_click) + y_click;

			filledEllipseRGBA(image,x,y,7,7,255,255,255,255);
			filledEllipseRGBA(image,x_ball,y_ball,7,7,0,0,0,255);

			x=x_ball;
			y=y_ball;


			x_ball+=3;
				
		}

		SDL_BlitSurface(image,NULL,screen,NULL);			
		SDL_Delay(2);
		SDL_Flip(screen);
	}

	SDL_FreeSurface(image);
	Mix_FreeChunk(effect1);
	Mix_FreeChunk(effect2);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit;	
	SDL_Delay(200);
	return 0;
}
