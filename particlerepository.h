#ifndef PARTICLEREPOSITORY_H
#define PARTICLEREPOSITORY_H

#include <QList>
#include <QHash>


#include "particle.h"

/**
 * @brief The ParticleRepository class
 */
class ParticleRepository
{

private:

    QHash<int, QList<Particle*> > personalRepository;

public:

    ParticleRepository();

    ~ParticleRepository();

    void addParticle(Particle * p, QList<Particle*> list);

    QList<Particle*> getParticlePersonalRepository(int particleId);



};

#endif // PARTICLEREPOSITORY_H
