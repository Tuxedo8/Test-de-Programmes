#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pile.h"

#define PO '('
#define PF ')'
#define AO '{'
#define AF '}'
#define CO '['
#define CF ']'

void write_file(FILE *fp ,char c) {
    if (fp == NULL) { // Check if the file can be open
        printf("\nERROR ADD : Couldn't open file ! \n");
        exit(1);
    }
    fprintf(fp, "%c", c); // Print the char in the file
}

char caractere_aleatoire() {
    int choix = rand() % 52;
    if (choix < 26) {
        return 'a' + choix;
    } else {
        return 'A' + (choix - 26);  
    }
}


char parenthese_aleatoire_O(){
    char choix=PO;
    int aleatoire = rand()%2;
    if (aleatoire == 0){
        choix=AO;
    } else if (aleatoire == 1){
        choix=CO; 
    }
    return choix;
    
}

char parenthese_aleatoire_F(){
    char choix=PF;
    int aleatoire = rand()%2;
    if (aleatoire == 0){
      choix=AF;
    } else if (aleatoire == 1){
        choix=CF;
    }
    return choix;
}


void generer_parenthesage_aleatoire_lg(FILE *fp, int longueur_min) {
 
    if (fp == NULL) { // Check if the file can be open
        printf("\nERROR ADD : Couldn't open file ! \n");
        exit(1);
    }

    pile p = Pilevide();
    int i = 0;
    int nb_ouvrantes = 0;
    int nb_fermantes = 0;

    while (i < longueur_min || !Estvide(&p)) {
        int aleatoire = rand() % 3;
        int choix = rand() % 3;
        if (Estvide(&p) ||  (aleatoire) == 0) {
            if (choix == 0) {
                Empiler(&p, PO);
                write_file(fp, PO);
            } else if (choix == 1) {
                Empiler(&p, AO);
                write_file(fp, AO);
            } else {
                Empiler(&p, CO);
                write_file(fp, CO);
            }
            i++;
            nb_ouvrantes++;
        } else if (!Estvide(&p) && (aleatoire) == 1) {
            if (Sommet(&p) == PO) {
                Depiler(&p);
                write_file(fp, PF);
            } else if (Sommet(&p) == AO) {
                Depiler(&p);
                write_file(fp, AF);
            } else {
                Depiler(&p);
                write_file(fp, CF);
            }
            i++;
            nb_fermantes++;
        }  else if (aleatoire == 2){
            write_file(fp, caractere_aleatoire());
            i++;
        }
    }


}


void generer_parenthesage_aleatoire_imb(FILE *fp, int imbrication_min) {
     
    if (fp == NULL) { // Check if the file can be open
        printf("\nERROR ADD : Couldn't open file ! \n");
        exit(1);
    }

    pile p = Pilevide();
    int i = 0;
    int niveau_imbrication = 0; 

    while (niveau_imbrication < imbrication_min) {
        int aleatoire = rand() % 3;
        int choix = rand() % 3;
        if ((niveau_imbrication < imbrication_min) && aleatoire == 0) {
            if (choix == 0) {
                Empiler(&p, PO);
                write_file(fp, PO);
            } else if (choix == 1) {
                Empiler(&p, AO);
                write_file(fp, AO);
            } else {
                Empiler(&p, CO);
                write_file(fp, CO);
            }
            niveau_imbrication++;
            i++;
        } else if (!Estvide(&p) &&  aleatoire == 1) {
            if (Sommet(&p) == PO) {
                Depiler(&p);
                write_file(fp, PF);
            } else if (Sommet(&p) == AO) {
                Depiler(&p);
                write_file(fp, AF);
            } else {
                Depiler(&p);
                write_file(fp, CF);
            }
            niveau_imbrication--; 
            i++;
        }else if (aleatoire == 2){
            write_file(fp, caractere_aleatoire());
            i++;
        }
    }
    while (!Estvide(&p)) {
       if (Sommet(&p) == PO) {
                Depiler(&p);
                write_file(fp, PF);
            } else if (Sommet(&p) == AO) {
                Depiler(&p);
                write_file(fp, AF);
            } else {
                Depiler(&p);
                write_file(fp, CF);
            }
        i++;
    }
}


void generer_mauv_parenthesage_lg(FILE *fp, int longueur_min) {
      if (fp == NULL) { // Check if the file can be open
        printf("\nERROR ADD : Couldn't open file ! \n");
        exit(1);
    }
    
    int aleatoire=rand()%100;     // nombre de parenthèse a ajouter
    int k=rand()%50;  
    do{
        k = rand()%50;

        aleatoire=rand()%100;
      }
    while(aleatoire%2==0 && k>aleatoire);

    k=(aleatoire - k);          //mauvais parenthésage avant
    for(int i=0; i<k; i++){
        int O_F = rand() % 2;
        if(O_F==0){
            write_file(fp, parenthese_aleatoire_O());
        } else {
            write_file(fp, parenthese_aleatoire_F());
        }
        write_file(fp, caractere_aleatoire());
    }
    generer_parenthesage_aleatoire_lg(fp, longueur_min);        //Parenthésage bon

    for(int i=0; i<(aleatoire-k); i++){         //mauvais parenthésage après
      write_file(fp, caractere_aleatoire());
      int O_F = rand() % 2;
        if(O_F==0){
            write_file(fp, parenthese_aleatoire_O());
        } else {
            write_file(fp, parenthese_aleatoire_F());
        }
    }
    
}

void generer_mauv_parenthesage_imb(FILE *fp, int imbrication_min) {

    if (fp == NULL) { // Check if the file can be open
        printf("\nERROR ADD : Couldn't open file ! \n");
        exit(1);
    }

    int aleatoire=rand()%100;
    int k = rand()%50;
    do{
        aleatoire=rand()%100;
        k = rand()%50;
      }
    while(aleatoire%2==0 && k>aleatoire);

    k=(aleatoire - k);          //mauvais parenthésage avant
    for(int i=0; i<k; i++){
        int O_F = rand() % 2;
        if(O_F==0){
            write_file(fp, parenthese_aleatoire_O());
        } else {
            write_file(fp, parenthese_aleatoire_F());
        }
        write_file(fp, caractere_aleatoire());
    }
    
    generer_parenthesage_aleatoire_imb(fp, imbrication_min);        //Parenthésage bon

    for(int i=0; i<(aleatoire-k); i++){         //mauvais parenthésage après
      write_file(fp, caractere_aleatoire());
      int O_F = rand() % 2;
        if(O_F==0){
            write_file(fp, parenthese_aleatoire_O());
        } else {
            write_file(fp, parenthese_aleatoire_F());
        }
    }
}

// 5 Cette fonction introduit une erreur où le programme arrête de compter les parenthèses ouvrantes dès la rencontre d'une fermante.
    void generer_mauv_no_successive(FILE *fp, int longueur_min) {
    pile p = Pilevide();
    int i = 0;
    int nb_ouvrantes = 0;
    int nb_fermantes = 0;

    // Tant qu'on n'a pas atteint la longueur minimale requise
    while (i < longueur_min) {
        if (i == 0){

        Empiler(&p, PO);
        write_file(fp, PO);
        nb_ouvrantes++;
        i++;

        write_file(fp, PF);  // Parenthèse fermante
        nb_fermantes++;
        Depiler(&p);  // On dépile une ouvrante
        }
   
        Empiler(&p, PO);
        write_file(fp, PO);
        nb_ouvrantes++;
        i++;
    }
}

// 6 Cette fonction introduit une erreur où les parenthèses fermantes ne sont pas comptées.
void generer_mauv_no_dec(FILE *fp, int longueur_min) {
    int i = 0;

    while (i < longueur_min) {
        // N'ajoute jamais de parenthèse ouvrante (erreur NO_DEC)
        if (rand() % 2 == 0) {
            write_file(fp, caractere_aleatoire());
        } else {
            write_file(fp, PF); // Ajoute des parenthèses fermantes sans tenir compte des ouvrantes
        }
        i++;
    }
}

// 7 Cette fonction génère une chaîne où les parenthèses ouvrantes ne sont pas comptées.
void generer_mauv_no_inc(FILE *fp, int longueur_min) {
    int i = 0;

    while (i < longueur_min) {
        if (rand() % 2 == 0) {
            write_file(fp, caractere_aleatoire());
        } else {
            write_file(fp, PO); // Ajoute des parenthèses fermantes sans tenir compte des ouvrantes
        }
        i++;
    }
}

// 8 Cette fonction traite toutes les parenthèses comme équivalentes, sans différencier les types.
void generer_mauv_no_type(FILE *fp, int longueur_min) {
    pile p = Pilevide();
    int i = 0;
    int nb_ouvrantes = 0;
    int nb_fermantes = 0;

    // On génère un nombre d'ouvrantes et de fermantes, mais pas du même type
    while (i < longueur_min || !Estvide(&p)) {
        if (Estvide(&p) || nb_ouvrantes <= nb_fermantes) {
            // Empile une parenthèse ouvrante aléatoire (type non différencié)
            char ouvrante = parenthese_aleatoire_O();
            Empiler(&p, ouvrante);
            write_file(fp, ouvrante);
            nb_ouvrantes++;
        } else {
            // Dépile et ajoute une parenthèse fermante aléatoire (type non différencié)
            char fermante = parenthese_aleatoire_F();
            Depiler(&p);
            write_file(fp, fermante);
            nb_fermantes++;
        }
        i++;
    }
}


void generer_mauv_no_type_imb(FILE *fp, int imbrication_min) {
    pile p = Pilevide();
    int niveau_imbrication = 0;
    int i = 0;

    // Tant que le niveau d'imbrication minimal n'est pas atteint
    while (niveau_imbrication < imbrication_min) {
        // Ajout des parenthèses ouvrantes mélangées
        char ouvrante = parenthese_aleatoire_O();  // Génère aléatoirement parmi (, {, [
        Empiler(&p, ouvrante);
        write_file(fp, ouvrante);
        niveau_imbrication++;
        i++;

        // Ajout des parenthèses fermantes pour équilibrer chaque niveau
        if (niveau_imbrication > 0 && rand() % 2 == 1) {
            char fermante = parenthese_aleatoire_F();  // Génère aléatoirement parmi ), }, ]
            write_file(fp, fermante);
            Depiler(&p);
            niveau_imbrication--;
            i++;
        }
    }

    // Pour s'assurer que tout est bien équilibré à la fin, ajoute les fermantes restantes
    while (!Estvide(&p)) {
        char fermante = parenthese_aleatoire_F();
        write_file(fp, fermante);
        Depiler(&p);
    }
}




int main(int argc, char *argv[]){


    if (argc < 3 || argc >= 4) {  
        fprintf(stderr, "ERROR : Usage: %s <arg1> <arg2>", argv[0]);
        fprintf(stderr, "\n\n<arg1> : \n0 (chaine vide, <arg2> non pertinent)\n1 (chaine correcte longueur minimal)\n2 (chaine incorrecte longueur minimal)\n3 (chaine correcte niveau d'imbrication minimal)\n4 (chaine incorrecte niveau d'imbrication minimal)\n5 (chaine incorrecte longueur minimal no_successive)\n6 (chaine incorrecte longueur minimal no_inc)\n7 (chaine incorrecte longueur minimal no_dec)\n8 (chaine incorrecte longueur minimal no_type)\n9 (chaine incorrecte niveau d'imbrication minimal no_type)\n\n<arg2> : valeur minimal\n\n");
        return EXIT_FAILURE;
    }    
    FILE *fp = fopen("output.txt", "w"); // Erase the previous content of the file
    if(fp == NULL){
      printf("\nERROR ERASE : Couldn't open file ! \n");
      exit(1);
    }else{
      fclose(fp);
    }

    srand(time(NULL));
    
    fp=fopen("output.txt", "a+");
    

    if ((int)atoi(argv[1])==1){
      
        
        generer_parenthesage_aleatoire_lg(fp, (int) atoi(argv[2]));
    } else if ((int) atoi(argv[1]) == 2){

      
        generer_parenthesage_aleatoire_imb(fp, (int) atoi(argv[2]));
    }
    else if ((int) atoi(argv[1])==3){

        generer_mauv_parenthesage_lg(fp, (int) atoi(argv[2]));
    }
    else if ((int) atoi(argv[1])==4){
        generer_mauv_parenthesage_imb(fp, (int) atoi(argv[2]));
    }
    else if ((int) atoi(argv[1])==5){
        generer_mauv_no_successive(fp, (int) atoi(argv[2])); 
    }
    else if ((int) atoi(argv[1])==6){
        generer_mauv_no_inc(fp, (int) atoi(argv[2])); 

    }
    else if ((int) atoi(argv[1])==7){
        generer_mauv_no_dec(fp, (int) atoi(argv[2])); 

    }
    else if ((int) atoi(argv[1])==8){
        generer_mauv_no_type(fp, (int) atoi(argv[2])); 
    
    }
    else if ((int) atoi(argv[1])==9){
        generer_mauv_no_type_imb(fp, (int) atoi(argv[2])); 
    
    }
    fclose(fp);
    return 0;
}

