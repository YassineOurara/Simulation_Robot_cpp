 #include <graphics.h>

  int main() 
  
  {
  	initwindow(800,800); 
    moveto(0,0);          
    setcolor(15);
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
	//Roues
	line(x-r/4, y-r/4, x-r/4, y+r/4);
    line(x+r/4, y-r/4, x+r/4,y+r/4);
	
    

            if (GetAsyncKeyState(VK_RIGHT)) {
            	cleardevice();
                x += 1;
                delay(10);
                
            }
            else if (GetAsyncKeyState(VK_LEFT)) {
            	cleardevice();
                x -= 1;
                delay(10);
                
            }else if (GetAsyncKeyState(VK_UP)) {
                cleardevice();
                y -= 1;
                delay(10);
            }else if (GetAsyncKeyState(VK_DOWN)) {
                cleardevice();
                y += 1;
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