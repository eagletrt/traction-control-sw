#include "inc/main.h"

int main(void) {

	model_init();

	return EXIT_SUCCESS;
}

bool model_init(void) {
	// Velocity Estimation
	model.dwork = &rtDW;
	Velocity_Estimation_initialize(&model);

	return true;
}