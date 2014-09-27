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

    gRepository = new GlobalRepository();

    pRepository = new ParticleRepository();
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
        qDebug("particleId: %d", particle->getParticleId());
        particleList.append(particle);

        // verificar repositorio global
        // verificar si la particula NO ES DOMINADA por cada particula del repositorio global
        if (!gRepository->isNewParticleDominatedByGlobalRepository(particle))
        {
            gRepository->addNonDominatedParticle(particle);

            gRepository->eliminateDominatedParticles();

        }

        // agregar la posicion actual de la particula a su repositorio local
        QList<Particle*> internalParticleList;
        internalParticleList.append(particle);
        pRepository->addParticle(particle, internalParticleList);

        /*
        // verificar repositorio local
        // verificar si la particula NO ES DOMINADA por cada particula de su repositorio
        if (!pRepository->isNewParticleDominatedByRepository(particle))
        {

            //pRepository->addNonDominatedParticle(particle);
            pRepository->addNonDominatedParticle(particle, internalParticleList);

            pRepository->eliminateDominatedParticles();

        }
        */


    }
    qDebug("tamano de la poblacion: %d",particleList.count());

}


void Simulation::updateParticles()
{
    Particle * particle;

    // iterar sobre cada particula
    for (int i = 0; i < particles; i++)
    {
        particle = particleList.at(i);

        // seleccionar el mejor global
        bestGlobal = gRepository->getRandomParticle();

        // seleccionar el mejor local
        bestLocal = pRepository->getRandomLocalFromParticle(particle->getParticleId());

        // iterar sobre cada componente de la particula
        for (int j = 0; j < particle->getNumberOfParameters(); j++)
        {
            double newVelocity = getInertiaParameter() + particle->getVelocity(j) +
                    (getCognitiveParameter() * getRandomUniform() * ( bestGlobal->getParameter(j) - particle->getParameter(j))) +
                    (getSocialParameter() * getRandomUniform() * (bestLocal->getParameter(j) - particle->getParameter(j)));

            particle->setVelocitity(j,newVelocity);

            if (particle->getVelocity(j) > getMaxSpeedParameter())
            {
                particle->setVelocitity(j, getMaxSpeedParameter());
            }else if (particle->getVelocity(j) < getMaxSpeedParameter()*(-1))
            {
                particle->setVelocitity(j, getMaxSpeedParameter()*(-1));
            }

            // ahora la actualizacion del componente en la posicion j



        }




    }

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


int Simulation::getCognitiveParameter()
{
    return cognitive;
}

int Simulation::getSocialParameter()
{
    return social;
}

double Simulation::getInertiaParameter()
{
    return inertia;
}

int Simulation::getMaxSpeedParameter()
{
    return maxSpeed;
}

double Simulation::getRandomUniform()
{
    return qrand()/double(RAND_MAX);
}

