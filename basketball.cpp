#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include<ctime>
#include<stdlib.h>
#include<cmath>
using namespace std;
int main()
{	
bool running=true;
	SDL_Surface* screen = SDL_SetVideoMode(1300, 700 ,32, 0);//intialize the surface  "screen"

	lineRGBA(screen,100,200,150,150,0,0,255,255);	//up side
	lineRGBA(screen,100,200,100,350,0,0,255,255);	//left side
	lineRGBA(screen,100,350,150,300,0,0,255,255);	//down side
	lineRGBA(screen,150,150,150,300,0,0,255,255);	//right side
	
	lineRGBA(screen,115,320,135,300,0,0,255,255);	//up side
	lineRGBA(screen,115,320,115,270,0,0,255,255);	//left side
	lineRGBA(screen,115,270,135,250,0,0,255,255);	//down side
	lineRGBA(screen,135,300,135,250,0,0,255,255);	//right side

	boxRGBA(screen,123,303,155,306,255,0,0,255);	//bar of basket
	ellipseRGBA(screen,185,305,30,10,255,0,0,255);	//basket
	
	
	srand(time(0));
	
	float x0_ball=rand()%700+300;
	float y0_ball=rand()%250+250;
	
	float x_motion;
	float y_motion;

	float x_click;
	float y_click;

	float x_ball=x0_ball;
	float y_ball=y0_ball;

	float x=x0_ball;
	float y=y0_ball;	

	float teta;
	const int g=10;
	const int velocity=1000;
		
	boxRGBA(screen, 0,0, 1300, 700, 255,255,255, 255);     //serface	
	filledEllipseRGBA(screen,x0_ball,y0_ball,7,7,0,0,0,255); 	
	
	float a;

	bool flag1=0;//click mouse
	bool flag2=0;//ground colleision 
	bool flag3=0;//basketball board colleision

	while(running)
	{	
		
//...........................................................................................
		
		
	lineRGBA(screen,100,240,140,220,0,0,255,255);	//up side big rectangle
	lineRGBA(screen,100,240,100,320,0,0,255,255);	//left side big rectangle
	lineRGBA(screen,100,320,140,300,0,0,255,255);	//down side big rectangle
	lineRGBA(screen,140,220,140,300,0,0,255,255);	//right side big rectangle
	
	lineRGBA(screen,110,280,130,270,0,0,255,255);	//up side small rectangle
	lineRGBA(screen,110,280,110,310,0,0,255,255);	//left side small rectangle
	lineRGBA(screen,110,310,130,300,0,0,255,255);	//down side small rectangle
	lineRGBA(screen,130,300,130,270,0,0,255,255);	//right side small rectangle

	boxRGBA(screen,120,300,140,302,255,0,0,255);	//bar of basket
	ellipseRGBA(screen,160,301,20,5,255,0,0,255);	//basket
	ellipseRGBA(screen,160,301,19,4,255,0,0,255);	//basket
	lineRGBA(screen,120,230,120,310,0,0,255,255);	//middle side

//.................................................ground.......................................	

	lineRGBA(screen,0,550,200,400,0,0,255,255);		//right side
	lineRGBA(screen,200,400,1300,400,0,0,255,255);	//up side		
	lineRGBA(screen,1200,400,1200,700,0,0,255,255);	//middle side vetical
	lineRGBA(screen,70,500,1300,500,0,0,255,255);	//middle side horizontal

	


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
							x_click=event.button.x;
							y_click=event.button.y;
							a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));
							//teta=atan(2*a*(x_ball -x_click));
							flag1=1;
							break;
							
						}

					}
					break;
				}	
			}	
		}

		//logic
		if(flag1==1)//first move of ball
		{	
			y_ball= a*(x_ball -x_click)*(x_ball -x_click) + y_click;

			filledEllipseRGBA(screen,x,y,7,7,255,255,255,255);
			filledEllipseRGBA(screen,x_ball,y_ball,7,7,0,0,0,255);

			x=x_ball;
			y=y_ball;
			if(abs(y_click-y0_ball)>=50 && abs(y_click-y0_ball)<=100)
				x_ball-=2;
			else if(abs(y_click-y0_ball)>100)
				x_ball-=1;
			else
				x_ball-=3;
		}
	
		if(y_ball>=500 )//ground colleision
		{	
			if(x>x_ball)
			{
				x_click=x_ball-((x0_ball-x_click)*0.6);
				y_click=500 - ((500-y_click)*0.5);
			}
			else
			{
				x_click=x_ball+((x_ball-x_click)*0.6);
				y_click=500-((y_ball-y_click)*0.5);
			}

			x0_ball=x_ball;
			y0_ball=499;

			a=(y0_ball-y_click)/((x0_ball-x_click)*(x0_ball-x_click));
			flag1=0;
			flag2=1;
			flag3=0;
		}

		if(flag2==1)
		{	
			if(x>x_ball)
			{
				y_ball= a*(x_ball -x_click)*(x_ball -x_click) + y_click;

				filledEllipseRGBA(screen,x,y,7,7,255,255,255,255);
				filledEllipseRGBA(screen,x_ball,y_ball,7,7,0,0,0,255);

				x=x_ball;
				y=y_ball;

				x_ball--;
				
				if( (x_click-x_ball) == (x0_ball-x_click) )
					flag2==0;	
				SDL_Delay(2);
			}
			else
			{
				y_ball= a*(x_ball -x_click)*(x_ball -x_click) + y_click;

				filledEllipseRGBA(screen,x,y,7,7,255,255,255,255);
				filledEllipseRGBA(screen,x_ball,y_ball,7,7,0,0,0,255);

				x=x_ball;
				y=y_ball;

				x_ball+=2;
				if( (x_ball-x_click) == (x_click-x0_ball) )
					flag2==0;
				SDL_Delay(2);
			}
		}
		
		if( x>=117 && x_ball<=120 && y_ball>=230 && y_ball<=310 && flag3==0)//basketball board colleisoin
		{
			x_click=x_ball;
			y_click=y_ball;
			
			x0_ball=x_ball;
			y0_ball=y_ball;
			
			flag1=0;
			flag2=0;
			flag3=1;
		}
		if(flag3==1)
		{
			y_ball= 4*a*(x_ball -x_click)*(x_ball -x_click) + y_click;

			filledEllipseRGBA(screen,x,y,7,7,255,255,255,255);
			filledEllipseRGBA(screen,x_ball,y_ball,7,7,0,0,0,255);

			x=x_ball;
			y=y_ball;
			x_ball+=2;
				
		}			
		SDL_Delay(2);
		SDL_Flip(screen);
	}
	SDL_Quit;	
	SDL_Delay(200);
	return 0;
}
