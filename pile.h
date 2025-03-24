#ifndef PILE_H
#define PILE_H
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 999999

typedef struct {
  char t[MAX_SIZE]; 
  long long size; // Give the size of the array t between 0 and MAX_SIZE 
  long long top; // Index of the top element in the Pile (last entered element in the array). -1 When Empty

} pile;

pile Pilevide();
void Empiler(pile *p, char c);
void Depiler(pile *p);
int Estvide(pile *p);
char Sommet(pile *p);

#endif
