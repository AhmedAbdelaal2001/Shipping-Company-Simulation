#include "Cargo.h"

Cargo::Cargo(Time prepTime, int loadTime = 0, char type = 'U', float distance = 0, float cost = 0, float priority = 0) {

	if (type == 'V')
		priority = cost + distance - 10 * prepTime.getDays() - 5 * prepTime.getHours();

	//Initialize el ba2y
}

//Setters w getters
