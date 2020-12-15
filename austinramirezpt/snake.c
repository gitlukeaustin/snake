/*----------------------Auteurs: Dorian Ruiz Ramirez et Luke Austin-------------------*/

#include <stdlib.h>
#include <graph.h>
#include "sfx.h"

int main()
{
    
    snake sn; /*serpent*/
    sn.x=MAXLENGTH/2;
    sn.y=MAXHEIGHT/2;
    
    int d=5; /* direction */
    
    apple ap; /*pommes*/
    
    int i=0;        /*indique quelle segment du serpent a enregistrer*/
    int new=1; /* nouveaux pommes */
    int score=0;
    
    unsigned int T=0, PT;   /*touche directionnel*/
    
    int r=0; /* rayon */
    
    
	InitialiserGraphique();
	CreerFenetre(100,100,MAXLENGTH,MAXHEIGHT);
	EffacerEcran(CouleurParNom("white"));
    
    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexte(200,250,"Appuyez sur une touche directionnelle",1);
    
    while((T!=XK_Up)&&(T!=XK_Right)&&(T!=XK_Left)&&(T!=XK_Down))
        T=Touche();
    
    ChoisirCouleurDessin(CouleurParNom("white"));
    RemplirRectangle(200,235,350,25);
    
    long int start = Microsecondes();
    
    /*----------------Boucle Principale-------------*/
    
    while(T!=XK_Escape)
	{
        death(sn,&T,score,i);
        
        movesnake(&sn,&T,score,&d);
        
        ui(score,start);
            
        apples(sn,&ap,&new,&score,&r);

        i=extend(&sn,i,score);
        
        death(sn,&T,score,i);
	
        pause();
    }

    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexte(300,250,"Appuyez sur une touche",1);
    Touche();
    
	FermerGraphique();
	return EXIT_SUCCESS;
}
