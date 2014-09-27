#include "globalrepository.h"

GlobalRepository::GlobalRepository()
{
}

GlobalRepository::~GlobalRepository()
{

}


QList<Particle *> GlobalRepository::getRepositoryList()
{
    return nonDominatedParticlesList;
}

void GlobalRepository::addNonDominatedParticle(Particle * p)
{
    nonDominatedParticlesList.append(p);
}


bool GlobalRepository::isParticleInGlobalRepository(Particle * particle)
{

    qDebug("->ExternalFile::isParticleInGlobalRepository");
    Particle * alreadyInsertedParticle;

    for (int i = 0; i < nonDominatedParticlesList.count(); i++)
    {
        qDebug("   dentro del for");
        alreadyInsertedParticle = nonDominatedParticlesList.at(i);
        if (particle->getParticleId() == alreadyInsertedParticle->getParticleId())
        {
            qDebug("---> la particula EXISTE en el repositorio global");
            return true;
        }

    }

    qDebug("   antes de salir");
    return false;

}

bool GlobalRepository::particleDominate(Particle * xj, Particle * xi)
{
    //qDebug("... ... Simulation::individualDominate");

    // a solution xj is said to dominate another solution xi, and we write xj <| xi if both
    // the following conditions are true:
    //
    // condition a: Fi(xj) <= Fi(xi) to i E 1,2
    //
    // confition b: Exists j 1, 2 such that Fj(xj) < Fj(xi)

    bool conditionA = false;
    bool conditionB = false;


    // condition a
    if ( (xj->getPerformanceDiscovery() >= xi->getPerformanceDiscovery()) &&
         (xj->getPerformanceLatency() <= xi->getPerformanceLatency()) )
    {
        conditionA = true;
    }

    // condition b
    if ( (xj->getPerformanceDiscovery() > xi->getPerformanceDiscovery()) ||
         (xj->getPerformanceLatency() < xi->getPerformanceLatency()) )
    {
        conditionB = true;
    }

    if ( (conditionA) && (conditionB) )
    {
        return true;
    }else
    {
        return false;
    }
}

bool GlobalRepository::isNewParticleDominatedByGlobalRepository(Particle * newParticle)
{
    qDebug("...GlobalRepository::isNewParticleDominatedByGlobalRepository");
    bool isDominated = false;

    Particle * nonDominatedParticle;

    for (int i = 0; i < nonDominatedParticlesList.count(); i++)
    {
        qDebug("   dentro del for");
        nonDominatedParticle = nonDominatedParticlesList.at(i);
        if (particleDominate(nonDominatedParticle, newParticle))
        {
            qDebug("  newParticle dominada por el repositorio global");
            isDominated = true;
            break;
        }
    }
    qDebug("   salio del for");
    return isDominated;
}

void GlobalRepository::eliminateDominatedParticles()
{

    qDebug("...GlobalRepository::eliminateDominatedParticles()");

    Particle * nonDominated;
    Particle * aux;


    for (int i = 0; i < nonDominatedParticlesList.count(); i++)
    {
        nonDominated = nonDominatedParticlesList.at(i);

        for (int j = 0; j < nonDominatedParticlesList.count(); j++)
        {
            aux = nonDominatedParticlesList.at(j);

            if (nonDominated->getParticleId() == aux->getParticleId())
            {
                continue;
            }

            if (particleDominate(aux, nonDominated))
            {

            }


        }
    }



}



Particle * GlobalRepository::getRandomParticle()
{
    int low = 0;
    int high = nonDominatedParticlesList.count()-1;
    int randomPosition = qrand() % ((high + 1) - low) + low;
    return nonDominatedParticlesList.at(randomPosition);
}
