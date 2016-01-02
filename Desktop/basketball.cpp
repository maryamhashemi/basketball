#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include<ctime>
#include<stdlib.h>
#include<cmath>
using namespace std;
int main()
{	bool running=true;
	SDL_Surface* screen = SDL_SetVideoMode(1200, 800 ,32, 0);//intialize the surface  "screen"

	lineRGBA(screen,100,200,150,150,255,255,255,255);	//up side
	lineRGBA(screen,100,200,100,350,255,255,255,255);	//left side
	lineRGBA(screen,100,350,150,300,255,255,255,255);	//down side
	lineRGBA(screen,150,150,150,300,255,255,255,255);	//right side
	
	lineRGBA(screen,115,320,135,300,255,255,255,255);	//up side
	lineRGBA(screen,115,320,115,270,255,255,255,255);	//left side
	lineRGBA(screen,115,270,135,250,255,255,255,255);	//down side
	lineRGBA(screen,135,300,135,250,255,255,255,255);	//right side

	boxRGBA(screen,123,303,155,306,255,0,0,255);		//bar of basket
	ellipseRGBA(screen,185,305,30,10,255,0,0,255);		//basket
	
	
	
	float x0_ball=600;
	float y0_ball=400;

	float x_motion_mouse;
	float y_motion_mouse;

	float x_click_mouse;
	float y_click_mouse;

	float x_ball=600;
	float y_ball;
	
	float teta;
	const int g=10;
	const int velocity=1000;
	
	float a;

	bool flag=0;

	filledEllipseRGBA(screen,x0_ball,y0_ball,10,10,0,50,100,255);

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
					x_motion_mouse=event.motion.x;
					y_motion_mouse=event.motion.y;
					break;
					
				}
				case(SDL_MOUSEBUTTONDOWN):
				{
					switch(event.button.button)
					{
						case(SDL_BUTTON_LEFT):
						{
							x_click_mouse=event.button.x;
							y_click_mouse=event.button.y;
							a=(y0_ball-y_click_mouse)/((x0_ball-x_click_mouse)*(x0_ball-x_click_mouse));
							cout<<a<<endl;
							flag=1;
							break;
							
						}

					}
					break;
				}	
			}	
		}

		//logic
		if(flag==1)
		{
			//y_ball=0.02*(x_ball-x0_ball) * (x_ball-x0_ball);
			y_ball= a*(x_ball -x_click_mouse)*(x_ball -x_click_mouse) + y_click_mouse;
			cout<<y_ball<<endl;
			filledEllipseRGBA(screen,x_ball,y_ball,10,10,0,50,100,255);
			x_ball--;
		}
		SDL_Delay(20);
		SDL_Flip(screen);
	}

	
	SDL_Quit;	
	SDL_Delay(20);
	return 0;
}
