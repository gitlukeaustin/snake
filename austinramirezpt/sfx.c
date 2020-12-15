/*------------------Auteurs: Dorian Ruiz Ramirez et Luke Austin-----------------*/

#include <stdlib.h>
#include <graph.h>
#include "sfx.h"

/*
 * Pause le jeu.
 *
 *  Postcondition : le jeu est mis en pause pour un temps.
 *
 */
void pause()
{
    unsigned int taketime=Microsecondes();
    unsigned int resettime=Microsecondes()-taketime;
    
    while(resettime<100000)
    {
        resettime=Microsecondes()-taketime;
    }
}


/*
*
* Choisit un couleur aléatoire
*
*  Précondition : 3 pointeurs d'entiers positives entre 0 et 255
*
*  Postcondition : la valeur des entiers sera changé
*
*/
void rainbowsnake(unsigned char* r,unsigned char* g, unsigned char* b)
{
    srand(Microsecondes());
    *r=rand()%255;
    *g=rand()%255;
    *b=rand()%255;
}

/*
 *  Cache l'emplacement des pommes par des cercles croissants
 *
 *  Précondition 1: un structure apple
 *  Précondition 2: un entier qui indique le rayon des cercles
 *  Précondition 3: un entier qui indique le dernier rayon d'un pomme mangé
 * 
 *  Postcondition: l'entier qui indique le rayon est mis a jour.
 *  Postcondition 2: affichage d'un rayon
 *
 */
void radar(const apple ap, int* r, int lastr)
{
    
    int j,k,n;

    for(k=0;k<=4;k++)
    {
        ChoisirCouleurDessin(CouleurParNom("white"));
        DessinerArc(ap.appx[k]-*r/2,ap.appy[k]-*r/2,*r,*r,360,360);
    }
 
    *r=*r+5;
    
    for(j=0;j<=4;j++)
    {
        ChoisirCouleurDessin(CouleurParNom("green"));
        DessinerArc(ap.appx[j]-*r/2,ap.appy[j]-*r/2,*r,*r,360,360);
    }
    
    if(lastr!=-1)
    {
        ChoisirCouleurDessin(CouleurParNom("white"));
        DessinerArc(ap.ax-lastr/2,ap.ay-lastr/2,lastr,lastr,360,360);
    }
    
    
    if(*r>200)
    {
        for(n=0;n<=4;n++)
        {
            ChoisirCouleurDessin(CouleurParNom("white"));
            DessinerArc(ap.appx[n]-*r/2,ap.appy[n]-*r/2,*r,*r,360,360);
        }
        
        *r=0;
    }
}

/*
 *  Détermine la direction du serpent
 *
 *  Précondition 1 : pointeur d'un structure représentant le serpent
 *  Précondition 2 : pointeur d'un entier positif représentant une touche.
 *  Précondition 3 : un entier représentant le score.
 *
 *  Postcondition 1 : Les coordonnées du serpent changeront. 
 *  Postcondition 2: La valeur de la Touche T sera potentiellement modifié.
 *  Postcondition 3: Le je sera potententiellement mis en pause.
 *  Postcondition 3: La fonction rainbow sera appelé après un score de 35.
 *
 */
void movesnake(snake *s, unsigned int* T, int score, int* dir)
{
    unsigned int savet=*T;
    int stop=1;
    
    while(stop==1)
    {
        stop=2;
        if(ToucheEnAttente())
        {
            *T= Touche();
        }
    
        if(*T==XK_Up)
        {
            if(*dir==1)
            {
                s->y=s->y+10;
                *dir=1;
            }
            else
            {
                s->y=s->y-10;
                *dir=0;
            }
        }
        if(*T==XK_Down)
        {
            if(*dir==0)
            {
                s->y=s->y-10;
                *dir=0;
            }
            else
            {
                s->y=s->y+10;
                *dir=1;
            }
        }
        if(*T==XK_Left)
        {
            if(*dir!=2)
            {
                s->x=s->x-10;
                *dir=3;
                
            }
            else
            {
                s->x=s->x+10;
                *dir=2;
            }
        }
        if(*T==XK_Right)
        {
            if(*dir!=3)
            {
                s->x=s->x+10;
                *dir=2;
            }
            else
            {
                s->x=s->x-10;
                *dir=3;
                
            }
        }
        
        /*-------------pause du jeu-------------*/
        
        if(*T==XK_space)
        {
            *T=XK_Return;
            ChoisirCouleurDessin(CouleurParNom("black"));
            EcrireTexte(300,250,"Appuyez sur Espace",1);
            while(*T!=XK_space)
            {
                if(ToucheEnAttente())
                    *T=Touche();
            }
            stop=1;
            ChoisirCouleurDessin(CouleurParNom("white"));
            RemplirRectangle(300,235,200,25);
            *T=savet;
        }
        if(stop==2)
            stop=0;
    }
    
    /*------------trace le serpent--------------*/
    
    ChoisirCouleurDessin(CouleurParNom("cyan"));
    if(score>5)
    {
        unsigned char r,g,b;
        rainbowsnake(&b,&g,&b);
        ChoisirCouleurDessin(CouleurParComposante(r,g,b));
        
    }
    RemplirRectangle(s->x,s->y,10,10);
        
}


/*
 *  Enrengistre tous les segments du serpent et retrace les carrés après la queue.
 *
 *  Précondition 1: l'adresse d'un structure serpent. 
 *  Précondition 2: un entier qui indique quelle partie du serpent doit étre changé. 
 *  Précondition 3: l'entier qui représente le score. 
 *
 *  Postcondition 1: les cordonnées du dernier segment du serpent seront modifié.
 *  Postcondition 2: l'indice indicant le prochain partie a changer sera retourné.
 *
 */
int extend(snake *s, int i, int score)
{
    
    s->snax[i]=s->x;
    s->snay[i]=s->y;
    
    if(i<=15 + score * 2)
        i++;
    else
        i=0;
    
    ChoisirCouleurDessin(CouleurParNom("white"));
    RemplirRectangle(s->snax[i],s->snay[i],10,10);
    
    
    return i;
    
}


/*
 *  Place les pommes. Fait appel au fonction radar.
 *
 *  Précondition 1: struct de type snake
 *  Précondition 2: pointeur d'un struct de type apple
 *  Précondition 3: pointeur d'un entier entre 0 et 1
 *  Précondition 4: pointeur d'un entier
 *  Précondition 5: pointeur d'un entier
 *
 *  Postcondition 1: 5 pommes seront affichées et enrengistrés. une seul fois.
 *  Postcondition 2: Une nouvelle pomme sera potentiellement remplacé.
 *  Postcondition 3: La fonction radar sera appelé après un score de 55.
 *
 */
void apples(const snake s, apple *a, int* new, int* score, int* r)
{
    int i;
    int lastr=-1;
    /*---------------- Initialisation -------------------*/
    
    if(*new==1)
    {
        for(i=0;i<5;i++)
        {
            srand(Microsecondes());
            a->appx[i]=(rand()%60)*10;
            a->appy[i]=(rand()%40)*10;
            ChoisirCouleurDessin(CouleurParNom("green"));
            RemplirArc(a->appx[i],a->appy[i],10,10,360,360);
            
        }
    *new=0;
    }

    /*---------------- Nouvelle Pomme -------------------*/
    
    for(i=0;i<5;i++)
    {
        if((s.x==a->appx[i])&&(s.y==a->appy[i]))
        {
            a->ax=a->appx[i];
            a->ay=a->appy[i];
            lastr=*r;
            a->appx[i]=(rand()%60)*10;
            a->appy[i]=(rand()%40)*10;
            *score = *score + 1;
        }
        
        ChoisirCouleurDessin(CouleurParNom("green"));
        
        if(*score>10)
        {
            ChoisirCouleurDessin(CouleurParNom("white"));
        }
        RemplirArc(a->appx[i],a->appy[i],10,10,360,360);
        
    }
    if(*score>10)
    {
        radar(*a,r,lastr);
    }
}

/*
 *  Vérifie les conditions de continuation du jeu.
 *
 *  Précondition 1: struct de type snake
 *  Précondition 2: pointeur d'un entier positif
 *  Précondition 3: entier
 *  Précondition 4: entier
 *
 *  Postcondition 1: l'entier T sera potentiellement modifié 
 *  Postcondition 2: un message de succés ou de défaite sera potentiellement affiché
 *
 */
void death(const snake s, unsigned int* T, int score, int i)
{
    int k;
    /*---------------- Queue -------------------*/
 
    for(k=0;k<=15+score*2;k++)
    {

            if((k!=i)&&(k!=i+1)&&(k!=i-1)&&(s.x==s.snax[k])&&(s.y==s.snay[k]))
            {
                ChoisirCouleurDessin(CouleurParNom("red"));
                EcrireTexte(200,200,"Game Over [Contact]",2);
                *T=XK_Escape;
            }
    }

    
    /*---------------- Bordures -------------------*/
    
    if((s.x>MAXLENGTH)||(s.x<0)||(s.y>MAXHEIGHT)||(s.y<0))
    {
        ChoisirCouleurDessin(CouleurParNom("red"));
        EcrireTexte(100,100,"Game Over [Exit]",2);
        *T=XK_Escape;
    }
    
    if(score>100)
    {
        EcrireTexte(100,100,"Vous avez Gagné!",2);
        *T=XK_Escape;
    }
}


/*
 *  Affiche le score et le temps.
 *
 *  Précondition 1: entier 
 *  Précondition 2: entier
 *
 *  Postcondition: conversion et affichage des deux valeurs sur la fenêtre graphique.
 *
 */
void ui(int score, long int start)
{
    /*--------------Conversions-----------------*/
    
    char c = (score/20)%10+'0';
    char d = (score/2)%10+'0';
    char u = (score*5)%10+'0';
    char sc[10] = { c, d, u,'\0'};
    char su = ((Microsecondes()-start)/1000000)%10+'0';
    char sd = ((Microsecondes()-start)/10000000)%6+'0';
    char mu = ((Microsecondes()-start)/60000000)%10+'0';
    char md = ((Microsecondes()-start)/600000000)%6+'0';
    char ti[10] = { md, mu, ':', sd, su, '\0'};
    
    /*---------------- Score -------------------*/
    
    ChoisirCouleurDessin(CouleurParNom("grey"));
    EcrireTexte(40,380,"Score: ",2);
    
    ChoisirCouleurDessin(CouleurParNom("white"));
    RemplirRectangle(145,355,50,25);
    
    ChoisirCouleurDessin(CouleurParNom("grey"));
    EcrireTexte(145,380,sc,2);
    
    /*---------------- Temps -------------------*/
    
    ChoisirCouleurDessin(CouleurParNom("grey"));
    EcrireTexte(375,380,"Temps: ",2);
    
    ChoisirCouleurDessin(CouleurParNom("white"));
    RemplirRectangle(495,355,70,25);
    
    ChoisirCouleurDessin(CouleurParNom("grey"));
    EcrireTexte(495,380,ti,2);
    
}
