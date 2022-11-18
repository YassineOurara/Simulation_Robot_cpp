 #include <graphics.h>

  int main() 
  
  {
  	initwindow(600,600); 
    moveto(0,0);          
    setcolor(15);
 	int x = 80, y = 80;
    while (1) 
	{
    circle(x,y,50);
            if (GetAsyncKeyState(VK_RIGHT)) {
            	cleardevice();
                x += 10;
                delay(1);
                
            }
            else if (GetAsyncKeyState(VK_LEFT)) {
            	cleardevice();
                x -= 10;
                delay(1);
                
            }else if (GetAsyncKeyState(VK_UP)) {
                cleardevice();
                y -= 10;
                delay(1);
            }else if (GetAsyncKeyState(VK_DOWN)) {
                cleardevice();
                y += 10;
                delay(1);
            }
            if (GetAsyncKeyState(VK_RETURN)) {
                break;
                delay(10);
            }
    }
	closegraph(); 
             
      return 0; 
  }
