#include<stdlib.h>
#include<graph.h>
 
int main()
{
    InitialiserGraphique();
    CreerFenetre(100,10,500,500);
    EcrireTexte(100,100,"Edit World !",2);
    Touche();
    FermerGraphique();
    return EXIT_SUCCESS;
}
