#include <graphics.h>
#include<math.h>
#include"dessin.h"
#include <fstream>
#include <iostream>
using namespace std;
char inf[1000];	
int nbrObstacle=0;
int score= 0;
int main() 
{
  	DWORD w=GetSystemMetrics(SM_CXSCREEN);
    DWORD h=GetSystemMetrics(SM_CYSCREEN);
    h=1100;
    w=1500;
    initwindow(w,h,"ROBOT-AUTO");
    figure robot;
    while(true){
    cleardevice();
    robot.afficher();
    delay(30);
    }
    getch();
    closegraph();
    return 0;
}

figure::figure(){
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
    wg=1;
    wd=1;
//  position de robot
    Xr=60;
    Yr=60;
//  position et rayon de but
    Xb=1400;
    Yb=600;
    Rb=30;
    ang=0;
//  les Obstacles
	ifstream file ("obstacles.obs");
//  position des obstacles et rayons
    int x_obs;
    int y_obs;
    int r_obs;
//  les positions et le rayons d'obstacles dans le fichier obstacles.obs 
    while(file >> x_obs >> y_obs >> r_obs ){
        Xobs[nbrObstacle]=x_obs;
        Yobs[nbrObstacle]=y_obs;
        Robs[nbrObstacle]=r_obs;
        nbrObstacle++;
	}
	
}

void figure::afficher(){

//  cercle du robot
    setcolor(WHITE);
    circle(Xr,Yr,Rr);
    
//  triangle du robot
    setcolor(WHITE);
    drawpoly(4,tr);

//  cercle du but
    setcolor(GREEN);
    circle(Xb,Yb,Rb);
    
//  cercle des obstacles 

    for (int i=0;i<nbrObstacle+1;i++){
    		setcolor(YELLOW);
    		circle(Xobs[i],Yobs[i],Robs[i]);
    }
    
//  Affichage dans l'écran des coordonnées du robot et vitesse de ces deux roues
	setcolor(WHITE);
    sprintf(inf,"Nombre d'obstacles= %d ",nbrObstacle-1);
    outtextxy(1300,20,inf);
    sprintf(inf,"Score= %d ",score);
    outtextxy(1300,40,inf);
    
//      	mise a jour des données
            
	Dd=wd*Dt*R0;
    Dg=wg*Dt*R0;
    if(Dg!=Dd)
//    Rc=D*(Dg+Dd)/(2*(Dg-Dd)); //dr/dalpha
    Dalpha=(Dg-Dd)/D;
    Dr = (Dg + Dd)/2;
    DistGoal=sqrt((Xr-Xb)*(Xr-Xb)+(Yr-Yb)*(Yr-Yb));
            
if (DistGoal<80){
	moveStop();
	delay(10);
    Xb=((rand() % 90) + 50); //this code generates a random number between 0 and 89
    Yb=((rand() % 600) + 50); //this code generates a random number between 0 and 599
    score++;
    
}else{
    float ang = atan2(Yb - Yr, Xb - Xr);
    for (int i = 0; i <nbrObstacle; i++){
        DistObstacle[i] = sqrt((Xobs[i] - Xr) * (Xobs[i] - Xr) + (Yobs[i] - Yr) * (Yobs[i] - Yr));
        double obsAngle = atan2(Yobs[i] - Yr, Xobs[i] - Xr);
        if (DistObstacle[i] < 160)
        {
            double produitvect = (Xb - Xr) * (Yobs[i] - Yr) - (Yb - Yr) * (Xobs[i] - Xr);
            // If the robot is close to the obstacle, adjust the angle to avoid the obstacle
            // Check if the angle between the robot and the obstacle is closer to the angle between the robot and the goal
            if (produitvect > 0)
            {
                ang = obsAngle - M_PI/2;
            }
            // If the cross product is negative, the angle between the vectors is obtuse, and the longest detour should be taken
            else
            {
                ang = obsAngle + M_PI/2;
            }

            break;
        }
    }
    //  Calcule de la vitesse angulaire wg (resp. wd)
    wg = DistGoal * cos(ang) / 0.1;
    wd = DistGoal * sin(ang) / 0.1;
	Xr += wg/DistGoal*0.5;
    Yr += wd/DistGoal*0.5;

    
	Dd=wd*Dt*R0;
    Dg=wg*Dt*R0;
    Dalpha=(Dg-Dd)/D;
    Dr = (Dg + Dd)/2;
    static float instance = Dt;
	instance += 0.1;
	//cout << instance<< " " ;
	std::ofstream file("position.pts", std::ios::app);
    // Write the values to the file
    file << "<< T :" << instance << " s >> << X : " << Xr << " px >> << Y : " << Yr << " px >> << Vitesse angulaire Roue Droite : " << wd/100 << " rad/s <<<< Vitesse angulaire Roue Gauche : " << wg/100 << " rad/s "<< endl;
    // Close the file
    file.close();
	//  ----------------------mise à jour des position en fonction de xr et yr----------------------
    int *dx;
//  tr tableau des positions triangle
    tr[0]=Xr ;
    tr[1]=Yr-Rr;
    tr[2]=Xr+Rr ;
    tr[3]=Yr;
    tr[4]=Xr ;
    tr[5]=Yr+Rr;
    tr[6]=Xr ;
    tr[7]=Yr-Rr;
//	orienter le triangle 
    dx=rotation(tr,8,Xr,Yr,ang);
    for (int i=0;i<8;i++)
    tr[i]=*(dx+i);
}
			
return;



}
