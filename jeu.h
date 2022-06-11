#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct grille {
	char GC[7][7];
} Grille;

typedef struct player {
	char jeton;
} Player;

Grille initialisation ();

Grille affiche_grille (Grille G);

int puissance_4 (Grille G, char j);

Grille rotation_90_D (Grille G);
Grille rotation_90_G (Grille G);
Grille retourner_grille (Grille G);

Grille graviter (Grille G);

Grille mettre_jeton (Grille G, char j);

int choix_action ();

Grille action (Grille G, char j, int a);

int compte (Grille G);

int choix_jeton (Player j1, Player j2);

int qui_commence (Player j1, Player j2);

int gagnant (Grille G, Player j1, Player j2);

int deroulement (Grille G, Player j1, Player j2, int pj);

int affichage_debut ();

int PvsP ();

int choix_action_M ();

int choix_colonne_M ();

int PvsM ();

Grille mettre_jeton_Ordi (Grille G, char j, int c);

int deroulement_O (Grille G, Player j1, Player ordi, int pj);

int choix_jeu ();

int compteur_jeton (Grille G, Player one, Player two);

int doit_mettre_jeton (Grille G, Player one, Player two);

int jeton_aligner (Grille G, Player j);

int action_effectuer (int a);

int cj ();

int jeu ();
