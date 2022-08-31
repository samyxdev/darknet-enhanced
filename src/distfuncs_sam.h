#ifndef DISTFUNCS_SAM_H
#define DISTFUNCS_SAM_H

#include "box.h"
#include "darknet.h"
#include <math.h>

// Couleur appliqué a la box de la cible et au texte ajouté
// Vert Menthe pour l'instant
#define TARGET_RED 73/255.0
#define TARGET_GREEN 248.0/255.0
#define TARGET_BLUE 255.0/255.0

// ----- PARAMETRES A ADAPTER POUR CHAQUE VIDEO ----
// D' de la caméra utilisée, à étalonner
#define DP_CAM 8036.7595

// Position du centre de la visée voiture (pour les bons resultats de mostctr_box)
#define RATIO_CTR_X 0.45
#define RATIO_CTR_Y 0.7

float get_distance(int box_width, int object_type);
float get_relspeed(int box_width, double current_time, float current_dist, int object_type);
int get_mostctr_box(detection *dets, int num, float thresh, int classes);
int get_mostctr_index();

#endif
