#ifndef SIMULATION_H
#define SIMULATION_H


#include <QList>

#include "particle.h"
#include "globalrepository.h"
#include "particlerepository.h"


/**
 * @brief Clase que modela la simulacion para el algoritmo cultural
 */
class Simulation
{

private:

    /**
     * @brief cognitive
     */
    int cognitive;

    /**
     * @brief social
     */
    int social;

    /**
     * @brief inertia
     */
    double inertia;

    /**
     * @brief maxSpeed
     */
    int maxSpeed;

    /**
     * @brief particles
     */
    int particles;

    /**
     * @brief iterations
     */
    int iterations;

    /**
     * @brief currentIteration
     */
    int currentIteration;

    /**
     * @brief Contador de identificador de una particula
     *
     * Usado para asignar un identificador unico para cada particula que se creo en la simulacion.
     */
    static int particleIdCounter;


    /**
     * @brief Lista de particulas
     */
    QList<Particle *> particleList;


    GlobalRepository * gRepository;

    ParticleRepository * pRepository;

public:

    /**
     * @brief Constructor de la clase Simulation
     *
     * @param cognitiveParameter valor del parametro cognitivo
     * @param socialParameter valor del parametro social
     * @param inertiaParameter valor del parametro de inercia
     * @param maxSpeed valor del parametro velocidad maxima
     * @param particles valor del parametro numero de particulas
     * @param maxIterations valor del parametro numero de iteraciones
     */
    Simulation(int cognitiveParameter, int socialParameter, double inertiaParameter, int maxSpeedParameter,
               int particlesParameter, int maxIterations);

    /**
     * @brief Destructor de la clase
     */
    ~Simulation();

    /**
     * @brief Inicializa las particulas de la simulacion
     */
    void initializeParticles();


    /**
     * @brief Retorna un nuevo identificador para una particula creado
     * @return Retorna un nuevo identificador para una particula creado
     */
    static int getNewParticleId();

    void incrementIteration();

    int getCurrentIteration();

    /**
     * @brief stopEvolution
     * @return
     */
    bool stopEvolution();
};

#endif // SIMULATION_H
