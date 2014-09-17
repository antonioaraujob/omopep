#include "simulation.h"
#include "particle.h"

#include <QList>


/**
 * @brief Define e inicializa el miembro estatico individualIdCounter
 */
int Simulation::particleIdCounter = 0;


Simulation::Simulation(int cognitiveParameter, int socialParameter,
                       double inertiaParameter, int maxSpeedParameter, int particlesParameter, int maxIterations)
{
    cognitive = cognitiveParameter;

    social = socialParameter;

    inertia = inertiaParameter;

    maxSpeed = maxSpeedParameter;

    particles = particlesParameter;

    iterations = maxIterations;

    currentIteration = 0;
}

Simulation::~Simulation()
{
}

void Simulation::initializeParticles()
{

    Particle * particle;

    // inicializacion de la poblacion
    for (int i = 0; i < particles; i++)
    {
        particle = new Particle(0, maxSpeed);
        particle->printParticle();
        qDebug("individualId: %d", particle->getParticleId());
        particleList.append(particle);

        // verificar repositorio global


        // verificar repositorio local



    }
    qDebug("tamano de la poblacion: %d",particleList.count());

}

int Simulation::getNewParticleId()
{
    int newId = particleIdCounter++;
    return newId;
}

void Simulation::incrementIteration()
{
    currentIteration++;
}

int Simulation::getCurrentIteration()
{
    return currentIteration;
}

bool Simulation::stopEvolution()
{
    if (currentIteration > iterations)
        return true;
    else
        return false;
}
