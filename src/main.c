#include "inc/main.h"

int main(void) {

    model.dwork = &rtDW;
    Velocity_Estimation_initialize(&model);

    return EXIT_SUCCESS;
}