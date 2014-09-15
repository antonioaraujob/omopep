#include "simulation.h"

/**
 * @brief Define e inicializa el miembro estatico individualIdCounter
 */
int Simulation::individualIdCounter = 0;


Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}


int Simulation::getNewindividualId()
{
    int newId = individualIdCounter++;
    return newId;
}
