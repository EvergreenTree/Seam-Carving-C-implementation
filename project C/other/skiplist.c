/* Ensembles comme skip-lists */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

// noeud pour la skip list et fonction d'allocation

struct node{int val; struct node *right; struct node *down;} ; 

struct node *allocate_node(int v){          
  struct node *p=(struct node *)(malloc(sizeof(struct node))); 
  (p->val)=v;
  (p->right)=NULL; (p->down)=NULL; 
  return p;}

// recherche d'un element

struct node * search(int x, struct node * l){
  while(1){
  if (l==NULL){return NULL;}
  if ((l->val)==x){return l;}
  struct node * lr=(l->right);
  struct node * ld=(l->down);
  if (lr==NULL){l=ld;continue;}
  if (x < (lr->val)){l=ld; continue;}
  if (x >= (lr->val)){l=lr; continue;}}
}

void prsearch(int x, struct node *l){
  struct node *res=search(x,l);
  if (res==NULL){printf("%d not found\n",x); return;}
  if ((res->val)==x){printf("%d found\n",x); return;}
  printf("search error !\n"); return;}

struct node * clean(struct node * l){
  struct node * ld = (l->down);
  struct node * lr = (l->right);
  if (ld==NULL){return l;}                                  // on est au niveau 0 (rien a faire)
  if (ld!=NULL  && (lr==NULL)){free(l); return clean(ld);}  // niveau i+1 vide: on l'elimine
  else {return l;}                                          // niveau i+1 non vide: on laisse en etat
}

// elimination d'un element. 

struct node * elim (int x, struct node * l){

struct node * entry=l;
// Phase 1: on reprend la fonction search en gardant la trace du predecesseur;
// si on trouve x, pred est son predecesseur.

struct node * pred=NULL;                  
while(1){
  if (l==NULL){return NULL;}                        // x pas la, rien a faire
  if ((l->val)==x){assert(pred!=NULL);break;}   // il faut enlever x (phase 2)
  struct node * lr=(l->right);
  struct node * ld=(l->down);
  if (lr==NULL){l=ld; continue;}                // on descend si possible, sinon rien a faire
  if (x < (lr->val)){l=ld;continue;}            // idem
  if (x >= (lr->val)){pred=l; l=lr; continue;}  // si on va a droite on note le pred
} 

// NB Tant qu'on descend on est sur que pour trouver l'element il faudra faire un pas a droite.

// Phase 2: elimination colonne de x.

while (1){
  assert((l->val)==x);
  assert((pred->right)==l);
  (pred->right) = (l->right);                          // elimine l
  free(l);                                             
  pred=(pred->down);                                   // passe niveau inferieur
  if(pred==NULL){break;}                               // atteint dernier niveau !
  assert((pred->right)!=NULL);
  while (((pred->right)->val)!=x){
    pred=(pred->right); assert((pred->right)!=NULL);}  // cherche  pred de x au prochain niveau
  l=(pred->right);}

 return clean(entry);

}




// Insertion probabiliste

// On utilise anode pour constuire une pile de predecesseurs

struct anode{struct node * point; struct anode *next;} ; 

struct anode *allocate_anode(struct node * x){          
  struct anode *p=(struct anode *)(malloc(sizeof(struct anode))); 
  (p->point)=x;
  (p->next)=NULL; 
  return p;
}

// insertion dans la pile
struct anode * ins_stack(struct node *x, struct anode *stack){
  struct anode *p=allocate_anode(x);
  (p->next)=stack;
  return p;
}

// elimination de la pile
struct  anode * pop(struct anode * stack){
  assert(stack !=NULL);
  struct anode * stacknext = (stack->next);
  free(stack);
  return stacknext;
}

// imprime la pile (utilise juste pour le test)

void prstack(struct anode * stack, int x){
  printf("print stack for %d :",x);
  while (stack!=NULL){
    printf("%d ", ((stack->point)->val));
    stack = (stack->next);}
  printf("\n");
}

// alloue un noeud x avec valeur x apres p (p!=NULL) et au dessus de d (peut etre NULL)
  
struct node * ins_el(int x, struct node * p, struct node * d){
  assert(p!=NULL); assert((p->val)<x);
  struct node *l = allocate_node(x);
  (l->right) = (p->right);
  (l->down)=d;
  (p->right) =l;
  if (d!=NULL){assert((d->val)==x);}
  if ((l->right)!=NULL){assert(((l->right)->val)>x);}  
  return l;
}


struct node * insert(int x, struct node * l){

  // initialisation
  struct node * entry=l;                     // sauve point d'entree
  struct anode * stack= allocate_anode(l);   // initialise pile avec point d'entree

  // phase 1, recherche endroit pour inserer x
while(1){
  if (l==NULL){break ;}                       //il faut maintenant inserer x, phase 2

  if ((l->val)==x){return entry;}             //on a rien a faire

  struct node * lr=(l->right);
  struct node * ld=(l->down);

  if (lr==NULL){                              //descendre si possible
    l=ld;
    if (ld!=NULL){stack=ins_stack(ld,stack);} //si on descend, on insere l'element dans la pile
    continue;}

  if (x < (lr->val)){                         //idem
    l=ld;
    if (ld!=NULL){stack=ins_stack(ld,stack);} 
    continue;}

  if (x >= (lr->val)){           
    assert(stack!=NULL);
    stack=pop(stack);
    stack=ins_stack(lr,stack);   
    l=lr; 
    continue;}               
 }

// phase 2
// l== NULL et le sommet du stack est le predecesseur du noeud qu'il faut inserer

 assert(l==NULL); assert(stack!=NULL); 
 prstack(stack,x);
 struct node *pred=(stack->point); 
stack = pop(stack); 
 assert((pred->val)<x);
 if ((pred->right)!=NULL){assert(((pred->right)->val)>x);}   
 struct node *down=NULL;
 struct node *current= ins_el(x, pred, down);      
 

// phase 3 duplication probabiliste

 while (rand()%2==1){
   if (stack==NULL){
     struct node *p=allocate_node(INT_MIN);
     (p->down)=entry;
     entry=p;
     stack=allocate_anode(p);}
   assert(stack!=NULL);
   pred = (stack->point); 
   stack=pop(stack);
   assert((current->val)==x);
   down=current;
   current=ins_el(x,pred,down);
}

return entry;}


// A partir d'ici les fonctions servent juste a faire des tests

// imprime une skip-list par niveaux a partir du haut (sans les -infty)

void print_sl(struct node * l){
  while (l!=NULL){
    struct node * l1=(l->right);  
    while (l1!=NULL){printf("%d ",(l1->val)); l1=(l1->right);}
    printf("\n");
    l=(l->down);
  }
}

// construit une liste -inf -> 1*10->....->n*10 avec pointeurs down null.

struct node * buildl(int n){
  struct node * entry=NULL;
  int i; struct node * l;
  for (i=n;i>0;i--){           // on construit 1*10 -> ...-> n*10
  l=allocate_node(i*10);
  (l->down)=NULL;
  (l->right)=entry;
  entry=l;}
  l=allocate_node(INT_MIN);   //on ajoute -inf
  (l->right)=entry; 
  entry=l;
  return entry;}

//construit une skip list avec n elements a la base


struct node * buildsl(int n){
  assert(n>0);
  struct node* entry=buildl(n);                   //liste de base
  while (n/2>0){
    struct node *newentry=allocate_node(INT_MIN); //nouvelle entree
    (newentry->down)=entry;
    struct node* p=(entry->right);                //p pointeur a la liste basse apres -infty
    struct node* q=newentry;                      //q pointeur liste haute
    while(p!=NULL){
      if ((rand()%2)==1){
        (q->right)=allocate_node(p->val);
        ((q->right)->down)=p;
        q=(q->right);}
      p=(p->right);}
    entry=newentry;
    n=n/2;}
  return entry;
}


int main(){ 
  struct node * l;
  int i;

  srand( (unsigned) time(NULL) );

  //test generation list et impression
  // l= buildl(10);
  // print_sl(l);

  //test generation skiplist et impression
  //for (i=0;i<10;i++){
  //l=buildsl(10);
  //print_sl(l);
  //printf("\n\n");}

  //test recherche
  //l=buildsl(10);
  //print_sl(l);
  //for(i=0;i<102;i++){prsearch(i,l);}

  //test elimination
  //  l=buildsl(10);
  //   print_sl(l);
  //   for(i=10;i>=0;i--){l=elim(i*10,l); print_sl(l);}
  //   l=elim(30,l); print_sl(l);
     
  //test insertion
    l=buildsl(5);
    printf("initial\n"); print_sl(l);printf("\n");
    for (i=0;i<10;i++){l=insert(5*i,l);printf("insert %d\n",5*i); 
                       print_sl(l); printf("\n");}
    for (i=0;i<=10;i++){l=elim(5*i,l);printf("elim %d\n",5*i); 
                       print_sl(l); printf("\n");}
}


