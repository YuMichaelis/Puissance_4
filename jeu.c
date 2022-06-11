#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"

Grille initialisation (){
    Grille G = {
    {"       ","       ","       ","       ","       ","       ","       "},
    };
    return G;
}

/*---------------------------------------------------------------*/

Grille affiche_grille (Grille G){
    int l;
    int c;
    printf("_______________\n");
    for(l = 0; l < 7; l++){
        printf("|");
        for(c = 0; c<7; c++){
            printf("%c|", G.GC[c][l]);
        }
        printf("\n");
    }
    printf("_______________\n");
    printf(" 1 2 3 4 5 6 7\n");
    return G;
}

/*---------------------------------------------------------------*/

int puissance_4 (Grille G, char j){
    int c;
    int l;
    int b = 0;
    for(c = 0; c < 7; c++){
        for(l = 0; l < 4; l++){
            if(G.GC[c][l] == j && G.GC[c][l+1] == j && G.GC[c][l+2] == j && G.GC[c][l+3] == j){
                b = 1;
                return b;
            }
        }
    }
    if(b == 1){
        return b;
        }
    for(l = 0; l < 7; l++){
        for(c = 0; c < 4; c++){
            if(G.GC[c][l] == j && G.GC[c+1][l] == j && G.GC[c+2][l] == j && G.GC[c+3][l] == j){
                b = 1;
                return b;
            }
        }
    }
    if(b == 1){
        return b;
        }
    for(c = 0; c < 4; c++){
        for(l = 0; l < 4; l++){
            if(G.GC[c][l] == j && G.GC[c+1][l+1] == j && G.GC[c+2][l+2] == j && G.GC[c+3][l+3] == j){
                b = 1;
                return b;
            }
        }
    }
    if(b == 1){
        return b;
        }
    for(c = 7; c > 4; c--){
        for(l = 0; l < 4; l++){
            if(G.GC[c][l] == j && G.GC[c-1][l+1] == j && G.GC[c-2][l+2] == j && G.GC[c-3][l+3] == j){
                b = 1;
                return b;
            }
        }
    }
    return b;
}

/*---------------------------------------------------------------*/

Grille rotation_90_D (Grille G){
Grille newG;
int c;
int l;
for(c = 0; c < 7; c++){
    for(l = 0; l < 7; l++){
        newG.GC[c][l] = G.GC[l][6 - c];
    }
}
return newG;
}

/*---------------------------------------------------------------*/

Grille rotation_90_G (Grille G){
Grille newG;
int c;
int l;
for(c = 0; c < 7; c++){
    for(l = 0; l < 7; l++){
        newG.GC[c][l] = G.GC[6 - l][c];
    }
}
return newG;
}

/*---------------------------------------------------------------*/

Grille retourner_grille (Grille G){
    Grille newG;
    int c;
    int l;
    for(c = 0; c < 7; c++){
        for(l = 6; l >= 0; l--){
            newG.GC[c][l] = G.GC[c][6 - l];
    }
}
return newG;
}

/*---------------------------------------------------------------*/

Grille graviter (Grille G){
    int c;
    int l;
    int i;
    for(c = 0; c < 7; c++){
        for(l = 5; l >= 0; l--){
            i = 1;
            while(G.GC[c][l + i] == ' ' && G.GC[c][l + i - 1] != ' '){
                if(l + i == 6){
                    G.GC[c][l + i] = G.GC[c][l + i - 1];
                    G.GC[c][l + i - 1] = ' ';
                    break;
                }
                G.GC[c][l + i] = G.GC[c][l + i - 1];
                G.GC[c][l + i - 1] = ' ';
                i++;
            }
            
        }
    }
    affiche_grille(G);
    return G;
}

/*---------------------------------------------------------------*/

Grille mettre_jeton (Grille G, char j){
    int c;
    int l;
    fprintf(stdout, "Dans qu'elle colonne voulez vous mettre votre jeton? \n");
    fscanf(stdin, "%d", &c);
    while(c < 1 || c > 7){
        fprintf(stdout, "erreur veuillez entrer un chiffre compris entre 1 et 7 (inclus) \n");
        fscanf(stdin, "%d", &c);
    }
    while(G.GC[c - 1][0] != ' '){
        fprintf(stdout, "cette colonne est complète veuillez en choisir une autre \n");
        fscanf(stdin, "%d", &c);
    }
    if(G.GC[c - 1][6] == ' '){
        G.GC[c - 1][6] = j;
        affiche_grille(G);
        return G;
    }
    for(l = 0; l < 6; l++){
        if(G.GC[c - 1][l] == ' ' && G.GC[c - 1][l + 1] != ' '){
            G.GC[c - 1][l] = j;
            affiche_grille(G);
            break;
        }
    }
    return G;
}

/*---------------------------------------------------------------*/

int choix_action (){
    int a;
    printf("Que voulez vous faire ? \n \n");
    printf("1/ placer un jeton \n");
    printf("2/ tourner le plateau de 90 degrés sur la gauche \n");
    printf("3/ tourner le plateau de 90 degrés sur la droite \n");
    printf("4/ retourner le plateau \n");
    fprintf(stdout,"5/ quitter la partie \n ");
    fscanf(stdin, "%d", &a);
    while(a < 1 || a > 5){
        fprintf(stdout, "erreur veuillez entrer un chiffre compris entre 1 et 5 (inclus) \n");
        fscanf(stdin, "%d", &a);
    }
    return a;
}

/*---------------------------------------------------------------*/

Grille action (Grille G, char j, int a){
    if(a == 1){
        G = mettre_jeton (G, j);
        return G;
    }
    if(a == 2){
        G = rotation_90_G (G);
        G = graviter (G);
        return G;
    }
    if(a == 3){
        G = rotation_90_D (G);
        G = graviter (G);
        return G;
    }
    if(a == 4){
        G = retourner_grille (G);
        G = graviter (G);
        return G;
    }
    return G;
}

/*---------------------------------------------------------------*/

int compte (Grille G){
    int nbrj = 0;
    int c;
    int l;
    for(c = 0; c < 7; c++){
        for(l = 0; l < 7; l++){
            if(G.GC[c][l] != ' '){
                nbrj++;
            }
        }
    }
    return nbrj;
}

/*---------------------------------------------------------------*/

int choix_jeton (Player j1, Player j2){
    int cj;
    printf("Joueur 1 quel jeton prenez-vous? \n");
    printf("1/ rond 'O' \n");
    fprintf(stdout,"2/ croix 'X' \n");
    fscanf(stdin, "%d", &cj);
    while(cj < 1 || cj > 2){
        fprintf(stdout, "erreur veuillez entrer soit 1 (rond) soit 2 (croix) \n");
        fscanf(stdin, "%d", &cj);
    }
    return cj;
}

/*---------------------------------------------------------------*/

int qui_commence (Player j1, Player j2){
    int pj;
    printf("Joueur 1 voulez-vous commencer? \n");
    printf("1/ Oui \n");
    fprintf(stdout,"2/ Non \n");
    fscanf(stdin, "%d", &pj);
    while(pj < 1 || pj > 2){
        fprintf(stdout, "erreur veuillez entrer soit 1 (oui) soit 2 (non) \n");
        fscanf(stdin, "%d", &pj);
    }
    return pj;
}

/*---------------------------------------------------------------*/

int gagnant (Grille G, Player j1, Player j2){
    int p1;
    int p2;
    p1 = puissance_4(G, j1.jeton);
    p2 = puissance_4(G, j2.jeton);
    if(p1 == 1 && p1 != p2){
        printf("Puissance 4, le joueur 1 gagne \n");
        return 1;
    }
    if(p2 == 1 && p1 != p2){
        printf("Puissance 4, le joueur 2 gagne \n");
        return 1;
    }
    if(p1 == 1 && p2 == 1){
        printf("2 Puissance 4, égalité \n");
        return 1;
    }
    return 0;
}

/*---------------------------------------------------------------*/

int deroulement (Grille G, Player j1, Player j2, int pj){
    int g;
    int a;
    int nbrjeton = 0;
    int tour = 0;
    affiche_grille(G);
    while(nbrjeton < 49){
        if((pj == 1 && (tour % 2) == 0 ) || (pj == 2 && (tour % 2) == 1)){
            printf("tour %d: c'est au joueur 1 \n", tour);
            a = choix_action();
            if(a == 5){
                return 0;
            }
            G = action(G, j1.jeton, a);
        }
        else{
            printf("tour %d: c'est au joueur 2 \n", tour);
            a = choix_action();
            if(a == 5){
                return 0;
            }
            G = action(G, j2.jeton, a);
        }
        g = gagnant(G, j1, j2);
        if(g == 1){
            return 0;
        }
        tour ++;
        nbrjeton = compte(G);
    }
    g = gagnant(G, j1, j2);
    if(g == 0){
        printf("aucun puissance 4, égalité");
    }
    return 0;
}

/*---------------------------------------------------------------*/

int affichage_debut (){
    int ad;
    printf("Bienvenue sur le puissance 4 \n");
    printf("Que voulez-vous faire? \n");
    printf("1/ Commencer une partie \n");
    fprintf(stdout,"2/ Quitter \n");
    fscanf(stdin, "%d", &ad);
    while(ad < 1 || ad > 2){
        fprintf(stdout, "erreur veuillez entrer soit 1 (commencer) soit 2 (quitter) \n");
        fscanf(stdin, "%d", &ad);
    }
    return ad;
}

/*---------------------------------------------------------------*/

int PvsP (){
    int d;
    int j;
    int c;
    Grille plateau;
    Player joueur1;
    Player joueur2;
    d = affichage_debut();
    while(d == 1){
        j = choix_jeton(joueur1, joueur2);
        if(j == 1){
            joueur1.jeton = 'O';
            joueur2.jeton = 'X';
        }
        else{
            joueur1.jeton = 'X';
            joueur2.jeton = 'O';
        }
        c = qui_commence(joueur1, joueur2);
        plateau = initialisation();
        deroulement(plateau, joueur1, joueur2, c);
        fprintf(stdout,"Voulez-vous recommencer? (1/ oui) (2/ non) \n");
        fscanf(stdin, "%d", &d);
    }
    return 0;
}

/*---------------------------------------------------------------*/

int choix_action_M (){
    srand(time(NULL));
    return rand() % 4 + 1;
}

/*---------------------------------------------------------------*/

int choix_colonne_M (){
    srand(time(NULL));
    return rand() % 7 + 1;
}

/*---------------------------------------------------------------*/

int PvsM (){
    int d;
    int j;
    int c;
    Grille plateau;
    Player joueur1;
    Player ordi;
    d = affichage_debut();
    while(d == 1){
        j = choix_jeton(joueur1, ordi);
        if(j == 1){
            joueur1.jeton = 'O';
            ordi.jeton = 'X';
        }
        else{
            joueur1.jeton = 'X';
            ordi.jeton = 'O';
        }
        c = qui_commence(joueur1, ordi);
        plateau = initialisation();
        deroulement_O(plateau, joueur1, ordi, c);
        fprintf(stdout,"Voulez-vous recommencer? (1/ oui) (2/ non) \n");
        fscanf(stdin, "%d", &d);        
    }
    return 0;
}

/*---------------------------------------------------------------*/

Grille mettre_jeton_Ordi (Grille G, char j, int c){
    int l;
    while(G.GC[c - 1][0] != ' '){
        c = choix_colonne_M ();
    }
    if(G.GC[c - 1][6] == ' '){
        G.GC[c - 1][6] = j;
        affiche_grille(G);
        return G;
    }
    for(l = 0; l < 6; l++){
        if(G.GC[c - 1][l] == ' ' && G.GC[c - 1][l + 1] != ' '){
            G.GC[c - 1][l] = j;
            affiche_grille(G);
            break;
        }
    }
    return G;
}

/*---------------------------------------------------------------*/

int deroulement_O (Grille G, Player j1, Player ordi, int pj){
    int g;
    int a;
    int jaj;
    int jao;
    int d = 0;
    int nbrjeton = 0;
    int tour = 0;
    affiche_grille(G);
    while(nbrjeton < 49){
        if((pj == 1 && (tour % 2) == 0 ) || (pj == 2 && (tour % 2) == 1)){
            printf("tour %d: c'est au joueur 1 \n", tour);
            a = choix_action();
            if(a == 5){
                return 0;
            }
            G = action(G, j1.jeton, a);
        }
        else{
            printf("tour %d: c'est au tour de l'ordi \n", tour);
            jao = jeton_aligner(G, ordi);
            if(jao != 8){
                G = mettre_jeton_Ordi(G, ordi.jeton, jao + 1);
            }
            jaj = jeton_aligner(G, j1);
            if(jaj != 8){
                G = mettre_jeton_Ordi(G, ordi.jeton, jaj + 1);
            }
            else{
                a = choix_action_M();
                d = doit_mettre_jeton(G, j1, ordi);
                if( a != 1 && d == 0 && tour != 0 && tour != 1){
                    G = action(G, ordi.jeton, a);
                    action_effectuer(a);
                }
                else{
                    a = choix_colonne_M();
                    while(G.GC[a - 1][0] != ' '){
                    a = choix_colonne_M();
                    }
                    G = mettre_jeton_Ordi(G, ordi.jeton, a);
                    printf("L'ordi à mis un jeton dans la colonne %d \n", a);
                }
            }
        }
        g = gagnant(G, j1, ordi);
        if(g == 1){
            return 0;
        }
        tour ++;
        nbrjeton = compte(G);
    }
    g = gagnant(G, j1, ordi);
    if(g == 0){
        printf("aucun puissance 4, égalité");
    }
    return 0;
}

/*---------------------------------------------------------------*/

int choix_jeu (){
    int p;
    printf("quel genre de partie voulez-vous \n");
    printf("1/ Player vs Player \n");
    fprintf(stdout,"2/ Player vs Machine\n");
    fscanf(stdin, "%d", &p);
    while(p < 1 || p > 2){
        fprintf(stdout, "erreur veuillez entrer soit 1 (PvsP) soit 2 (PvsM) \n");
        fscanf(stdin, "%d", &p);
    }
    return p;
}

/*---------------------------------------------------------------*/

int compteur_jeton (Grille G, Player one, Player two){
    int d;
    int jo = 0;
    int jt = 0;
    int c;
    int l;
    for(c = 0; c < 7; c++){
        for(l = 0; l < 7; l++){
            if(G.GC[c][l] == one.jeton){
                jo++;
            }
            if(G.GC[c][l] == two.jeton){
                jt++;
            }
        }
    }
    d = jo - jt;
    if(d == 2 || d == -2){
        return 1;
    }
    return 0;
}

/*---------------------------------------------------------------*/

int doit_mettre_jeton (Grille G, Player one, Player two){
    int mj;
    mj = compteur_jeton(G, one, two);
    return mj;
}

/*---------------------------------------------------------------*/

int jeton_aligner (Grille G, Player j){
    int c;
    int l;
    int ja = 8;
    for(c = 0; c < 7; c++){
        for(l = 6; l > 2; l--){
            if(G.GC[c][l] == j.jeton && G.GC[c][l] == G.GC[c][l - 1] && G.GC[c][l] == G.GC[c][l - 2]){
                ja = c;
                return ja;
            }
        }
    }
    return ja;
}

/*---------------------------------------------------------------*/

int action_effectuer (int a){
    if(a == 2){
        printf("L'ordi à tourné le plateau de 90° sur la gauche \n");
    }
    if(a == 3){
        printf("L'ordi à tourné le plateau de 90° sur la droite \n");
    }
    if(a == 4){
        printf("L'ordi à retourné \n");
    }
    return 0;
}

/*---------------------------------------------------------------*/

int cj (){
    int c;
    printf("Bienvenue sur le Puissance 4 ! \n");
    printf("Voulez-jouez: \n");
    printf("1/ joueur contre joueur \n");
    fprintf(stdout,"2/ joueur contre machine \n");
    fscanf(stdin, "%d", &c);
    while(c < 1 || c > 2){
        fprintf(stdout, "erreur veuillez entrer soit 1(PvsP) soit 2(PvsM) \n");
        fscanf(stdin, "%d", &c);
    }
    return c;
}

/*---------------------------------------------------------------*/

int jeu (){
    int c;
    c = cj();
    if(c == 1){
        PvsP();
    }
    else{
        PvsM();
    }
    return 0;
}

/*---------------------------------------------------------------*/
