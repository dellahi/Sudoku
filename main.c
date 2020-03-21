//lien source  https://openclassrooms.com/courses/l-aleatoire-en-c-et-c-se-servir-de-rand-1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //on inclu le fichier time.h qui contien la fonction time(time_t *v)
int tab0[4][4];int score=0,p,f,NbrJoueur,flag0,boucler,k;int case_interdite[4][4];
// k:represente le niveau et p: represente le sous niveau
int testligne(int a,int tableau[4][4],int i){
int k, flag=1;
for(k=0;k<4;k++){
    if(tableau[i][k]==a) flag=0;
}
return flag;}



int testcolonne(int chiffre,int tableau[4][4],int j){
int k, flag=1;
for(k=0;k<4;k++){
    if(tableau[k][j]==chiffre) flag=0;
}
return flag;}
int testbloc(int chiffre, int i,int j,int tableau[4][4]){
    int _i=i-i%2,_j=j-j%2;
    for(i=_i;i<(_i+2);i++){
            for(j=_j;j<(_j+2);j++){
                if(tableau[i][j]==chiffre) return 0;}
    }

return 1;
}


int test(int chiffre,int tableau[4][4],int i,int j){
   //ici on va definir la grande fonction test qui appelle toutes les autres
  if(testligne(chiffre,tableau,i)&&testcolonne(chiffre,tableau,j)&&testbloc(chiffre,i,j,tableau))
     return 1;
return 0;
}





int rand_ab(int a,int b){

	int nombre_aleatoire = 0;

		nombre_aleatoire = rand()%(b-a)+a;
		//un entier entre a et b,avec a inclu b exclu

	return nombre_aleatoire;
}
void saisir(){

do{
printf("\n        choisir le niveau entre 1 et 3 : ");
scanf("%d", &k);
printf("\n");
}while (k<1||3<k);
printf("        ->vous avez choisi le niveau %d  \n", k);
do{
printf("\n         ->entrer le sous niveau entre 1 et 3 : ");
scanf("%d",&p);
printf("\n");
}while(p<1||3<p);
return;
}
typedef struct joueur{
char nom[30];
int score;
int niveau;
int sousNiveau;
int mot_de_passe;
}joueur;
joueur* T_joueur;

void sauvegarder(){
int i,PIN,Nouveau_joueur=1;char N[30];
printf("       ->donner votre nom : ");scanf("%s",N);
FILE *flot = fopen("Sudoku.txt","rb");
if(flot == NULL){
    T_joueur=(joueur*)malloc(sizeof(joueur));
    flot=fopen("sudoku.txt","wb");

    T_joueur->score=score;
    T_joueur->sousNiveau=p;
    T_joueur->niveau=k;
    strcpy(T_joueur->nom,N);
    printf("       ->entrer votre mot de passe : ");
    scanf("%d",&PIN);
    T_joueur->mot_de_passe=PIN;
    NbrJoueur=1;
    fwrite(&NbrJoueur,sizeof(int),1,flot);
    fwrite(T_joueur,sizeof(joueur),1,flot);
    fclose(flot);

    printf("       ->Bienvenu %s : vous etes un nouveau joueur vos donnees sont enregistrees\n",N);
    free(T_joueur);
    return;
}
fread(&NbrJoueur,sizeof(int),1,flot);
T_joueur=(joueur*)malloc(NbrJoueur*sizeof(joueur));

if(T_joueur!=NULL){
  fread(T_joueur,sizeof(joueur),NbrJoueur,flot);
  fclose(flot);
  for(i=0;i<NbrJoueur;i++){
    if(strcmp(T_joueur[i].nom,N)==0){
        do {printf("       ->entrer votre mot de passe ,<taper 0 si vous etes nouveau> \n       - ");
        scanf("%d",&PIN);}while(PIN!=T_joueur[i].mot_de_passe&&PIN!=0);
        switch(PIN){
            case 0: i=NbrJoueur;break;
            default :T_joueur[i].score=score;
                     T_joueur[i].sousNiveau=p;
                     T_joueur[i].niveau=k;i=NbrJoueur;Nouveau_joueur=0;}

    }
  }
 if(Nouveau_joueur==1){
        NbrJoueur++;
        T_joueur=(joueur*)realloc(T_joueur,NbrJoueur*sizeof(joueur));
        T_joueur[NbrJoueur-1].score=score;
        T_joueur[NbrJoueur-1].sousNiveau=p;
        T_joueur[NbrJoueur-1].niveau=k;
        strcpy(T_joueur[NbrJoueur-1].nom,N);
        printf("       ->entrer votre mot de passe : ");
        scanf("%d",&PIN);
        T_joueur[NbrJoueur-1].mot_de_passe=PIN;
        printf("\n       ***Bienvenu %s vous etes un nouveau joueur*** : vos donnees sont enregistrees\n",N);
 }
 flot=fopen("sudoku.txt","wb");
 fwrite(&NbrJoueur,sizeof(int),1,flot);

 fwrite(T_joueur,sizeof(joueur),NbrJoueur,flot);
 fclose(flot);
 free(T_joueur);

 return;}
else {printf("        *probleme d'allocation de la m�moire* \n");return;}


}
void charger(){
int i,Mpasse;
f=0;
FILE *flot = fopen("Sudoku.txt","rb");
if(flot!=NULL){
    printf("       ->donnez votre mot de passe\n        **un mot de passe ne doit contenir que des chiffres** : ");
    scanf("%d",&Mpasse);
fread(&NbrJoueur,sizeof(int),1,flot);
T_joueur=(joueur*)malloc(NbrJoueur*sizeof(joueur));
if(T_joueur!=NULL){
fread(T_joueur,sizeof(joueur),NbrJoueur,flot);
fclose(flot);
for(i=0;i<NbrJoueur;i++){
        if(Mpasse==T_joueur[i].mot_de_passe){
                score=T_joueur[i].score;
                p=T_joueur[i].sousNiveau;
                k=T_joueur[i].niveau;
                f=1;
                i=NbrJoueur;//pour sortir de la boucle
                }
}
}
else printf("        *probleme d'allocation de la m�moire* \n ");
}
else {printf("        Pas de jeu sauvegarder encore!!!\n");saisir();f=1;}
free(T_joueur);
return;

}




void sortir(){
FILE *fp=fopen("scoreSudoku.txt","rb");
if(fp==NULL){
    fp=fopen("scoreSudoku.txt","wb");
    int T_score[10]={score,0,0,0,0,0,0,0,0,0};

    fwrite(T_score,sizeof(int),10,fp);
    fclose(fp);}
else{
    int T_score[10], a=8,placer=0;
    fread(T_score,sizeof(int),10,fp);
    fclose(fp);
    if(T_score[9]<score){
      while(a>=0&& !placer){
        if(T_score[a]<score){
            T_score[a+1]=T_score[a];
            a--;
            }
        else placer=1;
      }
      T_score[a+1]=score;
    }
    fp=fopen("scoreSudoku.txt","wb");
    fwrite(T_score,sizeof(int),10,fp);
    fclose(fp);
    }
    return;
}

void afficher_score(){
    FILE *fp=fopen("scoreSudoku.txt","rb");

    if(fp!=NULL){
        int T_score[10],m;
    fread(T_score,sizeof(int),10,fp);
    for(m=0;m<10;m++){
        printf("       -le score du %deme est: %d\n",m+1,T_score[m]);
    }
    fclose(fp);
    }
    else printf("      **aucun score n'est eencore enregistre**\n");
    return;
    }

typedef struct s_tab{
    int tab[4][4];
}s_tab;
s_tab ini_tab(int n){

s_tab tableau;
int i,j,k,p ;
int T0[16]={1,2,3,4,3,4,1,2,2,3,4,1,4,1,2,3};
p=0;
for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      tableau.tab[i][j]=T0[p];
      p++;
    }
}
for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      case_interdite[i][j]=1;
    }
}
 k=0;
while(k<n){
        i=rand_ab(0,4);
        j=rand_ab(0,4);
    if(tableau.tab[i][j]!=0){
    tableau.tab[i][j]=0;
    case_interdite[i][j]=0;
    k++;
    }
}
return tableau;
}



int inserer(int i,int j,int tab1[4][4],int chiffre){
    int k;
if(test(chiffre,tab1,i,j)==1){
   tab1[i][j]=chiffre;
   k=1;
   }
else{
    printf("        mauvais choix!! \n");
    k=0;
    }
return k;

}




void afficher(int tableau[4][4]){
    //fonction affichant le tableau
int i,j;
printf("\n        le TABLEAU est:\n\n");
for(i=0;i<4;i++){
    for(j=0;j<4;j++){
        printf("%d ",tableau[i][j]);
    }
    printf("\n");
}
return;
}
void commencer(int k){
int i,j; s_tab T;
if(k==1)
        T=ini_tab(6);
else if(k==2) T=ini_tab(9);
    else T=ini_tab(11);

for(i=0;i<4;i++)
{
for( j=0;j<4;j++)
    {
tab0[i][j]=T.tab[i][j];
    }

}

return ;
}



void Sudoku(){
int n_c,n_e,s_g,i,j,chiffre,nbr_reussi,h=0,nbr_echec,x,S_sousNiveau,choix;
do{printf("         --------------------------------------------\n       | taper 0 pour comencer une nouvelle partie     |\n       | taper 1 pour charger un jeu enregistrer       |\n       | taper 2 pour afficher les 10 meilleurs scores |\n        --------------------------------------------\n");
scanf("%d",&choix);}while(choix!=0&&choix!=1&&choix!=2);

switch(choix){
    case 0: saisir();break;
    case 1: charger();if(f==0) {printf("\n\n    <<le Mot de passe que vous avez saisie ne correspond � aucun joueur!!!>> \n\n");Sudoku();}break;
    case 2 : afficher_score();Sudoku(); break;
}

while(k<4){
    if(p==1){printf("\n      debut du niveau : %d\n      ---------------\n",k);}
if(k==1) n_c=6;
if(k==2) n_c=9;
if(k==3) n_c=11;
while(p<4){
        commencer(k);afficher(tab0);
        if(p==1){ n_e=18, s_g=3;}
        if(p==2){n_e=12, s_g=5;}
        if(p==3){n_e=6,s_g=11;}
    nbr_echec=nbr_reussi=0;S_sousNiveau=0;boucler=1;flag0=0;
    while(nbr_echec<n_e&&nbr_reussi<n_c&&(boucler==1)){
       do{
        printf("\n        <<choisir une case non pre-remplie!!!>> \n");
        do{printf("\n        ->donner la ligne entre 0 et 3 : ");
        scanf("%d",&i);}while(i<0||3<i);

        do{printf("\n        ->donner la colonne entre 0 et 3 : ");
        scanf("%d",&j);}while(j<0||3<j);
       }while(case_interdite[i][j]);
        do{printf("\n        ->donner une valeur entre 1 et 4 : ");
        scanf("%d",&chiffre);}while(chiffre<1||4<chiffre);
        if(tab0[i][j]==0) h=1;
        if(inserer(i,j,tab0,chiffre)&&h){score+=s_g;S_sousNiveau+=s_g; nbr_reussi++;}
        else if(!inserer(i,j,tab0,chiffre)) nbr_echec++;
        h=0;
        afficher(tab0);
        printf("\n\n        *********************************\n        -0 pour continuer               *\n        -1 pour recomencer              *\n        -2 pour sauvegarder et sortir   *\n        -3 pour sortir sans sauvegarder *\n        *********************************\n ");
        scanf("%d",&choix);
        switch(choix)
        { case 0:break;
           case 1:
            score-=S_sousNiveau;flag0=1;boucler=0;
            break;
            case 2: sauvegarder();sortir();boucler=0;flag0=0;break;
            case 3: sortir();boucler=0;flag0=0;break;
        }
        }

if(nbr_reussi==n_c){
    printf("\n !!!felicitation :\n         le sous niveau %d du niveau %d est reussi \n         ---------------------------------------\n",p,k);
    p=p+1;flag0=1;
    if(p<4) printf("\ndebut du sous niveau %d\n",p);
    }
if(nbr_echec==n_e){
    printf("tapez 1 si vous voulez sauvegarder 0 si non ");
    scanf("%d",&x);
    if(x){sauvegarder();}
    else sortir();
    flag0=0;
    printf("limite d'echec atteind au sous niveau %d du niveau %d \n le score final est: %d",p,k,score);
    }
if(flag0==0) p=4;
}
if(p==4&&flag0!=0){
    k++;p=1;
    }
if(flag0==0||nbr_echec==n_e)k=4;
}
return;
}

int main()
{srand(time(NULL));
Sudoku();
printf("\nHello world!\n");
return 0;
}
