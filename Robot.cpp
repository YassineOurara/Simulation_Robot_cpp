 #include <graphics.h>
 #include <cmath>

  int main() 
  
  {
  	initwindow(800,800,"Simulation b cpp  hh"); 
    moveto(0,0);          
    setcolor(15);
    //Variables
 	int x = 90, y = 90, r=80;
 	
	
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
                delay(10);
                
            }
            else if (GetAsyncKeyState(0x53)) {
            	cleardevice();
                x -= 1;
                y += 1;
                delay(10);
                
            }
            else if (GetAsyncKeyState(VK_SPACE)) {
            	cleardevice();
            	
                delay(10);
                
            }
            if (GetAsyncKeyState(VK_RETURN)) {
                break;
                delay(10);
            }
    }
	closegraph(); 
             
    return 0; 
  }
