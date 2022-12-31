#include <graphics.h>
#include<math.h>
#include"env.h"
#include <fstream>
using namespace std;
char inf[1000];
int main() 
{
  	DWORD w=GetSystemMetrics(SM_CXSCREEN);
    DWORD h=GetSystemMetrics(SM_CYSCREEN);
    h=1100;
    w=1500;
    initwindow(w,h,"Mini_Projet Simulation cpp");
    env robot;
    while(true){
    cleardevice();
    robot.afficher();
    delay(30);
    }
    getch();
    closegraph();
    return 0;
}
	
int nbrObstacle=0;
env::env(){

						//Initialisation des données//
// rayon robot
    Rr=50;
// rayon roue
    R0=0.020;
//intervalle de temps entre chaque mise à jour de la position et de l'orientation du robot:
    Dt=0.1;
// distance entre les roues
    D=0.05;
// vitesse angulaire max des roues
    w0Max=10;
// Acceleration max des roues
    Dw0Max=2;
    alpha=1;
//  Vitesse de la roue gauche(wg) resp. droite(wd)
    wg=0;
    wd=0;
//  position de robot
    Xr=60;
    Yr=60;
//  position de but
    Xb=1300;
    Yb=900;
						//les Obstacles//
						
	ifstream file ("obstacles.obs");
//  position des obstacles et rayons
    int x_obs;
    int y_obs;
    int r_obs;
//  boucle pour stocker les positions et incrémenter le nbr des obstacles 
    while(file >> x_obs >> y_obs >> r_obs ){
            Xobs[nbrObstacle]=x_obs;
            Yobs[nbrObstacle]=y_obs;
            Robs[nbrObstacle]=r_obs;
        nbrObstacle++;
	}             
  }
  
void env::afficher(){

//  cercle du robot
    setcolor(WHITE);
    circle(Xr,Yr,Rr);
    
//  triangle du robot
    setcolor(WHITE);
    drawpoly(4,tr);
    circle(Xb,Yb,Rr);


    setcolor(RED);
               for (int i=0;i<nbrObstacle+1;i++){
                circle(Xobs[i],Yobs[i],Robs[i]);
             }
    setcolor(GREEN);

    sprintf(inf,"WG = %.2f   WD = %.2f ",wg*10,wd*10);
    outtextxy(100,900,inf);

    setcolor(GREEN);
//		    Les commandes afin d'annimer le robot 		    //

       		if(GetAsyncKeyState(VK_LEFT) ){
            	wd=wd+0.025;
				delay(200);
            }
            if(GetAsyncKeyState(VK_DOWN&& wd<w0Max/10 && wg<w0Max/10)){
                wg=wg-0.05;
				delay(100);
                wd=wd-0.05;
				delay(100);
            }
            if(GetAsyncKeyState(VK_RIGHT)){
              	wg=wg+0.025;
			  	delay(200);
            }
            if(GetAsyncKeyState(VK_UP) && wd<w0Max/10 && wg<w0Max/10 ){
                wg=wg+0.05;delay(100);
                wd=wd+0.05;delay(100);
            }
            if(GetAsyncKeyState(VK_DOWN) && wd<w0Max/10 && wg<w0Max/10 ){
                wg=wg-0.05;delay(100);
                wd=wd-0.05;delay(100);
            }
//      	mise a jour des donnees
            Dd=wd*Dt*R0;
            Dg=wg*Dt*R0;
            if(Dg!=Dd)
            Rc=D*(Dg+Dd)/(2*(Dg-Dd));
            Dalpha=(Dg-Dd)/D;
            Dr = (Dg + Dd)/2;
            DistGoal=sqrt((Xr-Xb)*(Xr-Xb)+(Yr-Yb)*(Yr-Yb));
if (DistGoal<60){
    wg=0;delay(100);
    wd=0;delay(100);
    Xb=((rand() % 90) + 50);
    Yb=((rand() % 600) + 50);

}
//  mouvement du robot
    alpha=alpha+Dalpha;
    Xr=Xr+Dr*cos(alpha)*2000;
    Yr=Yr+Dr*sin(alpha)*2000;
//  mise à jour des position en fonction de xr et yr
    int *dx;
    tr[0]=Xr ;
    tr[1]=Yr-Rr;
    tr[2]=Xr+Rr ;
    tr[3]=Yr;
    tr[4]=Xr ;
    tr[5]=Yr+Rr;
    tr[6]=Xr ;
    tr[7]=Yr-Rr;

    dx=rotation(tr,8,Xr,Yr,alpha);
    for (int i=0;i<8;i++)
    tr[i]=*(dx+i);
    for (int i=0;i<nbrObstacle;i++){
            // Distance  entre centre du robot et d'obstacle doit etre inferieur a la somme des rayons de robot et l'obstacle
            DistObstacle[i]=sqrt((Xr-Xobs[i])*(Xr-Xobs[i])+(Yr-Yobs[i])*(Yr-Yobs[i]));
            if(DistObstacle[i] <=Rr+Robs[i]){
                wg =0;
                wd=0;

            }
	}
return;

}
