#ifndef GLOBALREPOSITORY_H
#define GLOBALREPOSITORY_H

#include <QList>

#include "particle.h"


/**
 * @brief Clase que modela el repositorio global de la optimizacion multiobjetivo
 * por enjambre de particulas
 */
class GlobalRepository
{

private:

    /**
     * @brief Lista de particulas no dominadas
     */
    QList<Particle *> nonDominatedParticlesList;




public:

    /**
     * @brief GlobalRepository
     */
    GlobalRepository();

    /**
     * @brief Destructor de la clase
     */
    ~GlobalRepository();


    /**
     * @brief Retorna la lista con las particulas no dominadas del repositorio global
     * @return Lista de particulas no dominadas del repositorio global
     */
    QList<Particle *> getRepositoryList();

    /**
     * @brief Agregar la particula pasada como argumento
     *
     * @param p particula no dominada que se debe agregar al repositorio global
     */
    void addNonDominatedParticle(Particle * p);

    /**
     * @brief Retorna si la particula pasada como argumento ya se encuentra en el repositorio
     * @param particle particula a verificar si ya existe en el repositorio
     * @return si la particula pasada como argumento ya se encuentra en el repositorio
     */
    bool isParticleInGlobalRepository(Particle * particle);


    bool particleDominate(Particle * xj, Particle * xi);


    bool isNewParticleDominatedByGlobalRepository(Particle * newParticle);


    void eliminateDominatedParticles();


};

#endif // GLOBALREPOSITORY_H
