#ifndef ENV_H
#define ENV_H
#include <cmath>

class env{
public:
void afficher();
    float Xobs[50],Dx,Dy,Yobs[50],Robs[50],Xr,Yr,alpha,Dr,Dg,Dd,Rc,Dalpha,wg,wd,R0,Dt,D,Xb,Yb,DistGoal,DistObstacle[50];
    int Rr,w0Max,Dw0Max, tr[8] = {Xr, Yr-Rr,Xr+Rr, Yr,Xr,Yr+Rr,Xr-Rr,Yr};
int* rotation(int e[8], int n, int xd,int yd, float tet)
{
int i = 0;
    while (i < n)
    {
        float x=e[i];
        float y=e[i+1];
       //déplacement de (-x,-y)
        int xtemp = x - xd;
        int ytemp = y - yd;
       //rotation
        x= (xtemp*cos(tet)- ytemp*sin(tet));
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
    env();

};

#endif
