#pragma once
#include "AstronomicalObject.h"

#define MIN_RADIUS = 1 // Mpc
#define MAX_RADIUS = 2 // Mpc

#define MIN_CHILD_COUNT = 0
#define MAX_CHILD_COUNT = 50

// distance between neighboring galaxies approx equal to 20x diameter of a galaxy
// 50% of galaxies near us are dwarf elliptical galaxies

// spiral galaxies contain moderate amounts of gas and dust
// spread out, less clustered together
// most bright galaxies are THIS, a significant number are elliptical however
// spiral galaxy classes are Sa, Sb, and Sc
// Sa: big central bulge, tightly wound arms, small amount of interstellar gas
// Sc: small bulge, loosely wound arms, large amount of gas
// Sb: intermediate between Sa and Sc.
// Subspecies is BARRED spirals (bar instead of bulge)

// lenticular galaxies have flat, rotating disks, central bulges, very little gas and dust, NO spiral arms
// theory is add gass and it forms a bulge and arms (ie. spiral galaxy)

// eliptical galaxies contain little gas and dust
// more clustered together
// very little gas, however the gas that is there is HOT and DIFFUSE
// stars are old, Population II stars
// E rating is eccentricity (E0 = circular, E7 = flatttened), n=10(a-b)/a

// irregular galaxies contain lots of gas and dust
// stars are clustered (patchy)

// galaxy mergers: spiral arm bridge, tidal tails, rings

// entropy increases over time -- so all galaxies are moving towards elliptical galaxies (via collision)

class Group : public AstronomicalObject {
public:
	Group();
};