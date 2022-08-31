#include "distfuncs_sam.h"

static float saved_dist = -1.;
static float saved_time = -1.;
static int mostctr_index = 0;

// Unités de box_width = pixels
float get_distance(int box_width, int object_type)
{	
	float real_vehicle_width = 0.0;

	//Dépendrait normalent du véhicule pour déterminer sa largeur moyenne
	if(object_type == 0)
		real_vehicle_width = 1.7; // Largeur moyenne citadine en m

	//Calcul de la distance (présenté à l'oral)
	return DP_CAM * (real_vehicle_width - 1.0) / box_width;
}

float get_relspeed(int box_width, double current_time, float current_dist, int object_type)
{
	float new_dist = get_distance(box_width, object_type);

	// Ce qui va être Vexperimentateur - Vcible
	float calc_speed = (new_dist - saved_dist) / (current_time - saved_time);

	// On actualise nos variables globales après avoir fait le calcul
	saved_dist = new_dist;
	saved_time = current_time;

	return calc_speed;
}

int get_mostctr_box(detection *dets, int num, float thresh, int classes)
{
	int ctr_ind = 0;
    float min_ctr_dist = 2.;

    //printf("Dets number: %d\n", num);

    // Determine la box la plus proche du centre (celle contre laquelle on calculera la distance)
    int i, j;
    for(i = 0; i < num; i++){
    	// Pour ne garder que les détections visibles (récupéré de draw_detection de image.c)
        int class = -1;
    	for(j = 0; j < classes; ++j){
            if (dets[i].prob[j] > thresh){
                if (class < 0)
                    class = j;
        	}
        }

        if(class >= 0){
			float ctr_dist_sq = pow(dets[i].bbox.x - RATIO_CTR_X, 2) + pow(dets[i].bbox.y - RATIO_CTR_Y, 2);

	        if(ctr_dist_sq < min_ctr_dist)
	        {
	        	ctr_ind = i;
	        	min_ctr_dist = ctr_dist_sq;
	        }
	        //printf("%d: MinInd: %d, Dist: %f, Min: %f\n", i, ctr_ind, ctr_dist_sq, min_ctr_dist);
    	}
    }

    mostctr_index = ctr_ind;

    printf("Mindist: %f, ind:%d\n", min_ctr_dist, ctr_ind);

    return ctr_ind;
}

// Assesseur de la variable global déjà affectée par get_mostctr_box() dans draw_detection
int get_mostctr_index()
{
	return mostctr_index;
}