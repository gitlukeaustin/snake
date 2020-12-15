/*----------------Auteurs: Dorian Ruiz Ramirez et Luke Austin---------------*/

#ifndef SFX_H
#define SFX_H

#define MAXHEIGHT 400
#define MAXLENGTH 600

struct s_snake
{
    int x;
    int y;
    int snax[200];
    int snay[200];
};

struct s_apple
{
    int ax;
    int ay;
    int appx[10];
    int appy[10];
};


typedef struct s_snake snake;

typedef struct s_apple apple;


void pause();

void rainbowsnake(unsigned char*,unsigned char*, unsigned char*);

void radar(const apple, int*, int);

void movesnake(snake*, unsigned int*, int, int*);

int extend(snake*, int, int);

void apples(const snake, apple*, int*, int*, int*);

void death(const snake, unsigned int*, int, int);

void ui(int,long int);

#endif /* FICHIER_H */