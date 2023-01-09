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
    initwindow(w,h,"ROBOT-MANUEL");
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
    wg=0;
    wd=0;
//  position de robot
    Xr=60;
    Yr=60;
//  position et rayon de but
    Xb=1300;
    Yb=600;
    Rb=30;
    n=0;
    tet=0;
//  les Obstacles//
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
    sprintf(inf,"Score= %d ",score);
    outtextxy(1300,20,inf);
    
//		----------------------Les commandes afin d'annimer le robot----------------------//
//      =====================================2 roues===================================

       		if(GetAsyncKeyState(VK_LEFT) ){
            	moveLeft();
            }
            if(GetAsyncKeyState(VK_DOWN && wd<w0Max/10 && wg<w0Max/10)){
                moveBackward();
            }
            if(GetAsyncKeyState(VK_RIGHT)){
              	moveRight();
            }
            if(GetAsyncKeyState(VK_UP) && wd<w0Max/10 && wg<w0Max/10 ){
            	moveForward();

            }
            if(GetAsyncKeyState(VK_DOWN) && wd<w0Max/10 && wg<w0Max/10 ){
                moveBackward();
            }
            if(GetAsyncKeyState(VK_SPACE)){
                moveStop();
            }
//      =====================================1 roue===================================            
//          	if(GetAsyncKeyState(VK_LEFT) ){
//            	wd=wd+0.025;
//				delay(200);
//            }
//            if(GetAsyncKeyState(VK_RIGHT)){
//              	wg=wg+0.025;
//			  	delay(200);
//            }
//            if(GetAsyncKeyState(VK_UP) && wd<w0Max/10 && wg<w0Max/10 ){
//                wg=wg+0.05;
//				delay(100);
//
//            }
//            if(GetAsyncKeyState(0x5A) && wd<w0Max/10 && wg<w0Max/10 ){
//                wd=wd+0.05;
//				delay(100);
//            }
//            if(GetAsyncKeyState(VK_DOWN) && wd<w0Max/10 && wg<w0Max/10 ){
//                wg=wg-0.05;
//				delay(100);
//            }
//            if(GetAsyncKeyState(0x53) && wd<w0Max/10 && wg<w0Max/10 ){
//                wd=wd-0.05;
//				delay(100);
//            }
//            if(GetAsyncKeyState(VK_SPACE)){
//                wg=0;
//				delay(100);
//                wd=0;
//				delay(100);
//            }
//==============================================================================================

//      	mise a jour des données
            Dd=wd*Dt*R0;
            Dg=wg*Dt*R0;
            if(Dg!=Dd)
            Rc=D*(Dg+Dd)/(2*(Dg-Dd));
            Dalpha=(Dg-Dd)/D;
            Dr = (Dg + Dd)/2;
            DistGoal=sqrt((Xr-Xb)*(Xr-Xb)+(Yr-Yb)*(Yr-Yb));

if (DistGoal<60){

//	Crée des buts aléatoirement
    Xb=((rand() % 90) + 50); //Un Xb aléatoire entre 0 et 89
    Yb=((rand() % 600) + 50); //Un Yb aléatoire entre  0 et 599
    score++;  
}

//  mouvement du robot
    alpha=alpha+Dalpha;
    Xr=Xr+Dr*cos(alpha)*2000;
    Yr=Yr+Dr*sin(alpha)*2000;
    static float instance = Dt;
	instance += 0.1;
	cout << instance<< " " ;
	std::ofstream file("position.pts", std::ios::app);
    // Write the values to the file
    file << "<< T :" << instance << " s >> << X : " << Xr << " px >> << Y : " << Yr << " px >> << Vitesse angulaire Roue Droite : " << wd/100 << " rad/s <<<< Vitesse angulaire Roue Gauche : " << wg/100 << " rad/s "<< endl;
    // Close the file
    file.close();

//  ----------------------mise à jour des position en fonction de xr et yr----------------------
    int *dx;
//  tr tableau pour tracer le triangle
    tr[0]=Xr ;
    tr[1]=Yr-Rr;
    tr[2]=Xr+Rr ;
    tr[3]=Yr;
    tr[4]=Xr ;
    tr[5]=Yr+Rr;
    tr[6]=Xr ;
    tr[7]=Yr-Rr;
//	orienter le triangle 
    dx=rotation(tr,8,Xr,Yr,alpha);
    for (int i=0;i<8;i++)
    tr[i]=*(dx+i);
    ofstream outfile;

//  Collisions
    for (int i=0;i<nbrObstacle;i++){
            // Distance  entre centre du robot et d'obstacle doit etre inferieur a la somme des rayons de robot et l'obstacle
            DistObstacle[i]=sqrt((Xr-Xobs[i])*(Xr-Xobs[i])+(Yr-Yobs[i])*(Yr-Yobs[i]));
            if(DistObstacle[i] <=Rr+Robs[i]){
            	setcolor(RED);
            	circle(Xobs[i],Yobs[i],Robs[i]);
                moveStop();
            }
	}
		tet= tet+0.1;
		if(Xr >= 1500){
			Xr=0;
		}
		else if(Xr<=0){
			Xr=1500;
		}
		
		if(Yr >= 1100){
			Yr=0;
		}
		else if(Yr<=0){
			Yr=1100;
		}
				
		if(alpha == 360){
			alpha = 0;
		}
		
return;

}
