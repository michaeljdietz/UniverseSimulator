#pragma once

#define HUBBLE_CONSTANT 0.7f
#define HUBBLE_CONSTANT_K_MS_MPC 73.24f // (km/s)/mpc

// TODO: How do we handle the fact that this varies over time, and distance approx. time in space?
// TODO: Are we making the assumption that all properties for all astronomical objects are made at CURRENT TIME
// TODO: Are we going to adjust those properties to account for time difference when viewing objects > 1 light year away?
// TODO: - It would be simpler to assume that everything we see is happening NOW rather than in the past.
// TODO: - The alternative is to assign velocity vectors to all objects... they can move as the user travels
// TODO:    - Moreover, stars could age as one travels as well
// TODO:    - Complications/considerations arise when considering collisions/mergers of astronomical objects
// TODO:    - This means that travel both requires generation of objects as they come into view as well as modification of objects as they move/interact due to time/distance

#define HUBBLE_PARAMETER_K_MS_MPC 0.7324f // (km/s)/mpc

#define BOLTZMAN_CONSTANT_J_K 1.380649f * pow(10, 23) 
#define BOLTZMAN_CONSTANT_EV_K 8.617333262145f * pow(10, 5)
#define BOLTZMAN_CONSTANT_ERG_K 1.380649f * pow(10, 16)

#define GRAVITATIONAL_CONSTANT_PC_M_KM_S 4.302 * pow(10, -3)
#define GRAVITATIONAL_CONSTANT_R_M_KM_S 1.90809 * pow(10, 5)
#define GRAVITATIONAL_CONSTANT_M_KG_S 6.67430 * pow(10, -11)

#define DARK_ENERGY_FORCE 0	// TODO: We need to figure this in order to see when expansion outweighs gravity

#define PC_PER_KPC pow(10, 3)
#define PC_PER_MPC pow(10, 6)
#define KPC_PER_MPC pow(10, 3)
#define MPC_PER_PC pow(10, -6)
#define MPC_PER_KPC pow(10, -3)