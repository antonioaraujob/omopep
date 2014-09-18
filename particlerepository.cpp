#include "particlerepository.h"

ParticleRepository::ParticleRepository()
{
}

ParticleRepository::~ParticleRepository()
{

}

void ParticleRepository::addParticle(Particle * p, QList<Particle *> list)
{

    //personalRepository.append(p);

    int particleId = p->getParticleId();
    //personalRepository.value(particleId).append(p);
    personalRepository.insert(particleId, list);



}

QList<Particle*> ParticleRepository::getParticlePersonalRepository(int particleId)
{
    return personalRepository.value(particleId);
}














