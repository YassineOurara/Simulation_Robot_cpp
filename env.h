#ifndef ENV_H
#define ENV_H
#include <cmath>

class env{
public:
void afficher();
    float Xr,Yr,Dx,Dy,Xobs[50],Yobs[50],Robs[50],alpha,Dr,Dg,Dd,Rc,Rb,Dalpha,wg,wd,R0,Dt,D,Xb,Yb,DistObstacle[50],DistGoal;
    int Rr,w0Max,Dw0Max, tr[8] = {Xr, Yr-Rr,Xr+Rr, Yr,Xr,Yr+Rr,Xr-Rr,Yr},n;
int* rotation(int e[8], int n, int xd,int yd, float tet){
	int i = 0;
    while (i < n){
        float x=e[i];
        float y=e[i+1];
        //déplacement de (-x,-y)
        int xtemp = x - xd;
        int ytemp = y - yd;
        //rotation
        x = (xtemp*cos(tet)- ytemp*sin(tet));
        y = (xtemp*sin(tet)+ ytemp*cos(tet));
        //déplacement de (x,y)
        x=x+xd;
        y=y+yd;
        //transformation en entier
        e[i]=rint(x);
        e[i+1]=rint(y);
        i=i+2;
    }
    return e;
}
    void moveForward(){
                wg=wg+0.25;
				delay(100);
                wd=wd+0.25;
				delay(100);   	
    	
	}
	void moveBackward(){
        wg=wg-0.05;
		delay(100);
        wd=wd-0.05;
		delay(100);   	
    	
	}
	void moveRight(){
		wg=wg+0.25;
		delay(200);
	}
	void moveLeft(){
		wd=wd+0.25;
		delay(200);
	}
	void moveStop(){
		wg=0;
		delay(100);
        wd=0;
		delay(100);
	}
	
	
env();

};

#endif
