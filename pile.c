#include "pile.h"

pile Pilevide(){
  pile p;
  p.size = 0;
  p.top = -1;
  //printf("\nPilevide size = %lld et top = %lld", p.size, p.top);
  return p;
}
int Estvide(pile *p){
  return (p->size == 0); 
}

char Sommet(pile *p){
  if(!Estvide(p)){
    return p->t[p->top];
  }
  else{
    printf("\nError SOMMET : Pile Vide\n");
  }
  return '\0';
}
void Depiler(pile *p){
  if(!Estvide(p)){
    p->top--;
    p->size--;
  }
  else{
    printf("\nError DEPILER : Pile Vide\n");
  }

}
void Empiler(pile *p, char c){
  if(p->size < MAX_SIZE){
    p->top++;
    p->t[p->top] = c;
    p->size++;
  }
  else{
    printf("\nError EMPILER : Pile Vide\n");
  }
}
