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
        //qDebug("particleId: %d", particle->getParticleId());
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
        Particle * newParticle = new Particle(*particle);
        internalParticleList.append(newParticle);
        pRepository->addParticle(newParticle, internalParticleList);
    }
    qDebug("tamano de la poblacion: %d",particleList.count());
}


void Simulation::updateParticles()
{
    Particle * particle;

    // iterar sobre cada particula
    for (int i = 0; i < particles; i++)
    {
        //qDebug("****** actualizando particulas******");
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

            int newParameter = particle->getParameter(j) + particle->getVelocity(j);

            // ahora la actualizacion del componente en la posicion j

            // chequear que el parametro no sea el numero de AP ni que los canales se repitan
            int index = j;

            if (particle->isThisParameterAChannel(index))
            {
                //qDebug("   isThisParameterAChannel(index)");

                // verificar que: 1 <= newParameter <= 11
                if ( (newParameter <= 0) || (newParameter > 11) )
                {
                    // asignar un nuevo valor valido
                    newParameter = particle->getJustARandomChannel();

                }
                // verificar que el canal no se haya utilizado

                //QHash<int, bool> channelsUsed = particle->getChannelsUsedForFly();
                while (particle->isChannelsUsedForFly(newParameter))
                {
                    // seleccionar otro canal que no se haya seleccionado
                    newParameter = particle->getJustARandomChannel();
                }
                //channelsUsed[newParameter]=true;
                particle->markChannelUsedForFly(newParameter);


                //qDebug(qPrintable("   channel despues de mutado: "+QString::number(intYi)));
            }
            else if (particle->isThisParameterAMinChannelTime(index))
            {
                //qDebug("   isThisParameterAMinChannelTime(index)");
                if (newParameter < 0)
                {
                    newParameter = 0;
                    //qDebug("   el minChannelTime mutado esta por debajo del limite (index %d)", index);
                }
                else if (newParameter > 10)
                {
                    newParameter = 10;
                    //qDebug("   el minChannelTime mutado esta por encima del limite (index %d)", index);
                }

                //qDebug(qPrintable("   minChannelTime despues de mutado: "+QString::number(intYi)));
            }
            else if (particle->isThisParameterAMaxChannelTime(index))
            {
                //qDebug("   isThisParameterAMaxChannelTime(index)");
                if (newParameter < 10)
                {
                    newParameter = 10;
                    //qDebug("   el maxChannelTime mutado esta por debajo del limite (index %d)", index);
                }
                else if (newParameter > 100)
                {
                    newParameter = 100;
                    //qDebug("   el maxChannelTime mutado esta por encima del limite (index %d)", index);
                }

                //qDebug(qPrintable("   maxChannelTime despues de mutado: "+QString::number(intYi)));
            }
            else if (particle->isThisParameterAPs(index))
            {
                //qDebug("   isThisParameterAPs(index)");
                newParameter = particle->getNewParameterAPs(particle->getParameter(index-3),
                                           particle->getParameter(index-2),
                                           particle->getParameter(index-1));
                //qDebug(qPrintable("   APs despues de mutado: "+QString::number(intYi)));
            }

            //qDebug("oldParameter: %f - newParameter: %d", particle->getParameter(j), newParameter);
            particle->setParameter(j,newParameter);
        }

        // resetear el diccionario de canales utilizados en el vuelo
        particle->resetChannelsUsedForFly();

        // reemplazar la particula con sus componentes actualizados
        particleList.replace(i,particle);
        //particle->printParticle();



    }

    // iterar sobre cada particula
    for (int k = 0; k < particles; k++)
    {
        particle = particleList.at(k);

        // evaluar las particulas
        particle->calculateDiscoveryValue();
        particle->calculateLatencyValue();

        // actualizar los repositorios

        // verificar si la particula NO ES DOMINADA por cada particula del repositorio global
        if (!gRepository->isNewParticleDominatedByGlobalRepository(particle))
        {
            gRepository->addNonDominatedParticle(particle);

            gRepository->eliminateDominatedParticles();

        }

        // verificar repositorio local
        // verificar si la particula NO ES DOMINADA por cada particula de su repositorio
        if (!pRepository->isNewParticleDominatedByRepository(particle))
        {

            //pRepository->addNonDominatedParticle(particle);
            pRepository->addNonDominatedParticle(particle);

            pRepository->eliminateDominatedParticles();

        }

    }
    //qDebug("****** fin actualizando particulas******");
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
    if (currentIteration == iterations)
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

void Simulation::printGlobalRepository()
{
    for (int i = 0; i < gRepository->getRepositoryList().count(); i++)
    {
        gRepository->getRepositoryList().at(i)->printParticle();
    }
}

GlobalRepository * Simulation::getGlobalRepository()
{
    return gRepository;
}
