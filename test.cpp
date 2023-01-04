#include <graphics.h>
#include <iostream>
#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<math.h>
#include <cmath>
#include <fstream>
using namespace std;

int x=300, y=500;
const double PI = 3.14159265358979323846;
float r=90;
// Fonction pour dessin de Triangle
	void triangle(int x1,int y1,int x2,int y2,int x3,int y3){
	   line(x1,y1,x2,y2);
	   line(x2,y2,x3,y3);
	   line(x3,y3,x1,y1);
	}
// Fonction pour orienter les Figures
	void Rotate(int x,int y, float Angle){
	    int a1,b1,a2,b2,a3,b3,p=x,q=y,dx,dy,ex,ey,fx,fy,gx,gy;
	    int x1=x-95, y1=y, x2=x, y2=y-95, x3=x+95, y3=y, d1=x-47, d2=y-19;
		int e1=x-47, e2=y+19, f1=x+47, f2=y-19, g1=x+47, g2=y+19;
	    Angle=(Angle*3.14)/180;
//	    Rotation Triangle
	    a1=p+(x1-p)*cos(Angle)-(y1-q)*sin(Angle);
	    b1=q+(x1-p)*sin(Angle)+(y1-q)*cos(Angle);
	    a2=p+(x2-p)*cos(Angle)-(y2-q)*sin(Angle);
	    b2=q+(x2-p)*sin(Angle)+(y2-q)*cos(Angle);
	    a3=p+(x3-p)*cos(Angle)-(y3-q)*sin(Angle);
	    b3=q+(x3-p)*sin(Angle)+(y3-q)*cos(Angle);
	    triangle(a1,b1,a2,b2,a3,b3);
//	    Rotation des roues
	    dx=p+(d1-p)*cos(Angle)-(d2-q)*sin(Angle);
	    dy=q+(d1-p)*sin(Angle)+(d2-q)*cos(Angle);
	    ex=p+(e1-p)*cos(Angle)-(e2-q)*sin(Angle);
	    ey=q+(e1-p)*sin(Angle)+(e2-q)*cos(Angle);
	    fx=p+(f1-p)*cos(Angle)-(f2-q)*sin(Angle);
	    fy=q+(f1-p)*sin(Angle)+(f2-q)*cos(Angle);
	    gx=p+(g1-p)*cos(Angle)-(g2-q)*sin(Angle);
	    gy=q+(g1-p)*sin(Angle)+(g2-q)*cos(Angle);
	    line(dx,dy,ex,ey);
	    line(fx,fy,gx,gy);
	}	
	
	bool detectCollision(int Xobs, int Yobs, int Robs) {
	  // Calcul de la distance entre les centres des deux cercles
	  double dx = x - Xobs;
	  double dy = y - Yobs;
	  double d = sqrt(dx * dx + dy * dy);
	  double distance = 95 + Robs + 25;
	  // Si la distance est inférieure à la distance spécifiée, les cercles sont considérés en collision
	  return d < distance;
	}
	
	bool detectBut(int Xbut, int Ybut, int Rbut) {
	  // Calcul de la distance entre les centres des deux cercles
	  double dx = x - Xbut;
	  double dy = y - Ybut;
	  double d = sqrt(dx * dx + dy * dy);
	  double distance = 95 + Rbut;
	  
	  return d <= distance;
	}
	
	void orienterVersBut(int x1, int y1, int r1, int x5, int y5, int r5){
		
		float distance = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
		int X = y - y1;
		float alpha1 = acos(X/distance) ;
		int alpha = (alpha1*180)/3.14;
		int f = alpha ;
		//  Orienter le Robot vers le but
		while(int(r) != f){
			cleardevice();
			if(r > f){
				r=r-1;
			}else{
				r = r + 1;
			}
			Rotate(x, y, r);	
			circle(x1,y1,r1);
			circle(x5,y5,r5);
			circle(x,y,95);
			delay(100);
		}
			
	}
	
	void rotateCircle(int Xobs, int Yobs, float wg, float wd, double dt) {
	  // Mise à jour des coordonnées du cercle en fonction de ses vitesses angulaires
	  x = x + wg * cos(wd * dt) - wd * sin(wg * dt);
	  y = y + wg * sin(wd * dt) + wd * cos(wg * dt);
	  // Calcul de la distance entre les deux cercles
	  double dx = x - Xobs;
	  double dy = y - Yobs;
	  double distancey = sqrt(dx * dx + dy * dy);
	  // Mise à jour de la position du cercle pour qu'il reste à une distance fixe du centre
	  x = Xobs + (95 / distancey) * dx * 1.5 ;
	  y = Yobs + (95 / distancey) * dy * 1.5 ;
}

int main(){
	// Dimension de la fenetre
	int height = 1100;
	int width = 1500;
	initwindow(width,height,"",-3,-3);
	// Manipulation des deux fichiers
	string const nomFichier("trajectoire.txt");
    ofstream monFlux(nomFichier.c_str());
    fstream fichier("obstacle.txt");  //On ouvre le fichier
	float wd=0,wg=0,teD=0,teG=0,teAll=0,Dist=0,teT=0,M1=0,M2=0;
	
	int Mr=0,Ml=0,cpt=0,cptbb=0;
	//	Coordonees du But
	int x1=1000,y1=600,r1=20;
	float Angle=0;
	while(1){
// ---------------------------------------------- Get Obstacle from Fichier ----------------------------------
		string ligne; 
		int x5,y5,r5;
      	while(getline(fichier, ligne)) 
      	{
         fichier >> x5 >> y5 >> r5;
      	}
// ------------------------------------------------------------------------------------------------------------
		// Calcul distance de chaque roue a partir de la vitesse angulaire
		M1 = (wd*0.1)*0.0124;
		M2 = (wg*0.1)*0.0124;
		// Calcul de la distance totale du ROBOT
		teAll = (M1 + M2)/2;
		Dist += teAll;
		// Orientation et Translation du Robot
		r += Mr-Ml;
		Angle=(r*3.14)/180;
		float Angl = Angle-90.25 ;
		M1 = M1/0.0002568 ;
		M2 = M2/0.0002568 ;
		x =x+ M1*cos(Angl)-M2*sin(Angl), y =y+ M1*sin(Angl)+M2*cos(Angl);
		cleardevice();
//  -------------------------------------------------- Robot auto -------------------------------------------------
		//	Calcule distance entre Robot et But
		float distance = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
		//  Calcul angle between Robot and But
		if(cpt == 0){
			orienterVersBut(x1, y1, r1, x5, y5, r5);
			cpt++;
		}
//		 if Robot atteint le But
		if(detectBut(x1,y1,r1) == true){
			wd = 0;
			wg = 0;
		}else{
		// Go ahead to the but
			wd = 1;
			wg = 1;
		}
		double alphabb;
//-------------------------------------------------------------------------------------------------------------------------------		
		//éviter l'obstacles
		float distanceObs = sqrt((x-x5)*(x-x5)+(y-y5)*(y-y5));
		int ybb = x5 - x, YY = y5 - y ;
		if(detectCollision(x5, y5, r5) == true && cptbb != 1){
			wd = 0;
			wg = 0;
			float vv = acos(ybb/distanceObs);
			alphabb = (vv*180)/PI;
			int fbb = 90 - alphabb;
			if(cptbb == 0){
				cptbb=1;
				while(fbb != 0){
					cleardevice();
					if (YY >= 0){
						r -= 1;
					}else{
						r += 1;
					}
					fbb = fbb -1;
					Rotate(x, y, r);
					circle(x1,y1,r1);
					circle(x5,y5,r5);
					circle(x,y,95);
					delay(100);
				}
				  // Définition des vitesses angulaires
				  float fr; int lr;
				  if(YY >= 0){
				  	wg = 0.0;
				  	wd = 0.63;
				  	lr = 40;
				  	fr = 0.7; 
				  }else{
				  	wg = 1.2;
				  	wd = 0.0;
				  	lr = 60;
				  	fr = -1.2;
				  }
				
				  double dt = 0.1;
				  int test;
				  // Boucle de mise à jour de la position du cercle
				  while ( -50 <= x5-x && x5-x >= -100 ) {
				    cleardevice();
				    if(detectBut(x1,y1,r1) == true){
				    	break;
					}
				    circle(x5, y5, r5);
				    circle(x, y, 95);
				    circle(x1,y1,r1);
				    Rotate(x, y, r);
				    rotateCircle(x5, y5, wd, wg, dt);
				    x += lr * dt;
				    r += fr;
				    delay(100);
				    cpt = 0;
				  }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
			}
		}
// --------------------------------------------------------------------------------------------------------------------------------
		//  Draw Figures
		Rotate(x, y, r);
		circle(x5,y5,r5);
		circle(x1,y1,r1);
		circle(x,y,95);
// --------------------------------------------------------------- ROBOT Manuelle --------------------------------------------------
		if(GetAsyncKeyState(VK_RIGHT)){
			Rotate(x, y, r);
			Mr =Mr+1;
			wd += 0.214;
		}else if(GetAsyncKeyState(VK_LEFT)){
			Rotate(x, y, r);
			Ml =Ml+1;
			wg += 0.214;
		}else if(GetAsyncKeyState(VK_UP)){
			wd += 0.214;
			wg += 0.214;
		}else if(GetAsyncKeyState(VK_DOWN)){
			wd -= 0.214;
			wg -= 0.214;
		}else if(GetAsyncKeyState(VK_SPACE)){
			Mr = 0;
			Ml= 0;
			wd = 0;
			wg = 0;
		}else if(GetAsyncKeyState(VK_RETURN))
			break;
// ----------------------------------------------------------- Affichage Coordonnees ---------------------------------
		monFlux << "<< T :" << teT << " s >> << X : " << x << " px >> << Y : " << y << " px >> << Vitesse angulaire Roue Droite : " << wd << " rad/s >> << Vitesse angulaire Roue Gauche : " << wg <<" rad/s >> << Distance : " << Dist << " m >>" << endl;
		
		delay(100);
		
		
		teT += 0.1;
		if(x >= width){
			x=0;
		}
		else if(x<=0){
			x=width;
		}
		
		if(y >= height){
			y=0;
		}
		else if(y<=0){
			y=height;
		}
				
		if(Angl == 360){
			Angl = 0;
		}
	}
	
	closegraph();
}
