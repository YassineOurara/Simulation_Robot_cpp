 #include <graphics.h>
 #include <cmath>

  int main() 
  
  {
  	DWORD w=GetSystemMetrics(SM_CXSCREEN);
    DWORD h=GetSystemMetrics(SM_CYSCREEN);
    h=1100;
    w=1500;
  	initwindow(w,h,"Mini_Projet Simulation"); 
    moveto(0,0);          
    setcolor(15);
    //Variables
 	int x = 400, y = 700, r=50;
	float theta=30;
	float alpha,beta;
    while (1) 
	{
			//////////Dessin Robot///////////
	// Cercle
    circle(x,y,r);
    // Triangle
    line(x-r, y, x+r, y);
    line(x-r, y, x, y-r);
    line(x+r, y, x,y-r);
	//Roue 1
	line(x-r/4, y-r/4, x-r/4, y+r/4);
    line(x-r/3, y-r/4, x-r/3, y+r/4);
    line(x-r/4, y-r/4, x-r/3, y-r/4);
    line(x-r/4, y+r/4, x-r/3, y+r/4);
    //Roue 2
    line(x+r/4, y-r/4, x+r/4,y+r/4);
    line(x+r/3, y-r/4, x+r/3,y+r/4);
    line(x+r/4, y-r/4, x+r/3, y-r/4);
    line(x+r/4, y+r/4, x+r/3, y+r/4);
      
            if (GetAsyncKeyState(VK_RIGHT)) {
            	cleardevice();
                x += 1;
            }
            else if (GetAsyncKeyState(VK_LEFT)) {
            	cleardevice();
                x -= 1;

            }else if (GetAsyncKeyState(VK_UP)) {
                cleardevice();
                y -= 1;
               
            }else if (GetAsyncKeyState(VK_DOWN)) {
                cleardevice();
                y += 1;
                
            }
             else if (GetAsyncKeyState(0x44)) {
            	cleardevice();
                x += 1;
                y += 1;
 
            }
             else if (GetAsyncKeyState(0x5A)) {
            	cleardevice();
                x -= 1;
                y -= 1;
  
            }
            else if (GetAsyncKeyState(0x45)) {
            	cleardevice();
                x += 1;
                y -= 1;

            }
            else if (GetAsyncKeyState(0x53)) {
            	cleardevice();
                x -= 1;
                y += 1;

            }
            else if (GetAsyncKeyState(VK_SPACE)) {
            	cleardevice();
            	alpha=theta*3.14f/180;
            	beta=(theta+90)*3.14f/180;
            	//////////////////
//            	x=x*cos(alpha);
//				y=y*sin(beta);
//			    line(x-r, y, x*sin(alpha), y-r*cos(alpha));
//			    line(x+r, y, x*sin(beta),y-r*cos(beta));

				////////////////////
//				line(x,y,x+r*sin(alpha),y+r*cos(alpha));
//				line(x,y,x+r*sin(beta),y+r*cos(beta));
//				line(x,y,x-r*sin(alpha),y-r*cos(alpha));
//				line(x,y,x-r*sin(beta),y-r*cos(beta));
				theta-=8;
				delay(50);
            }
            if (GetAsyncKeyState(VK_RETURN)) {
                break;
                delay(10);
            }
    }
	closegraph(); 
	
	
	int nbrObstacle=0;
	dessin::dessin(){
//Données
// rayon robot
    Rr=50;
// rayon roue
    R0=0.020;
//intervall de temps entre chaque mise a jour de la position et de l'orientation du robot:
    Dt=0.1;
// distance entre les roues
    D=0.05;
// vitesse angulaire max des roues
    w0Max=10;
// Acceleration maximun des roues
    Dw0Max=2;
    alpha=1;
    wg=0;
    wd=0;
// position de robot
    Xr=60;
    Yr=60;
//position de but
    Xc=1300;
    Yc=900;
// position des obstacles
	ifstream file ("obstacles.obs");
    int x_obs;
    int y_obs;
    int r_obs;
             
    return 0; 
  }
