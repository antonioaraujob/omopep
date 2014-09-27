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
     * @brief Parametro cognitivo
     */
    int cognitive;

    /**
     * @brief Parametro social
     */
    int social;

    /**
     * @brief Parametro inertia
     */
    double inertia;

    /**
     * @brief Parametro maxima velocidad
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


    /**
     * @brief Repositorio global de particulas no dominadas
     */
    GlobalRepository * gRepository;

    /**
     * @brief Repositorio local de particulas no dominadas
     */
    ParticleRepository * pRepository;

    /**
     * @brief Mejor particula global
     */
    Particle * bestGlobal;

    /**
     * @brief Mejor particula local
     */
    Particle * bestLocal;

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
     * @brief Ejecuta el proceso de actualizacion de las particulas
     * (ejecucion de las iteraciones del algoritmo)
     */
    void updateParticles();


    /**
     * @brief Retorna un nuevo identificador para una particula creado
     * @return Retorna un nuevo identificador para una particula creado
     */
    static int getNewParticleId();

    /**
     * @brief Incrementa el contador de iteraciones
     */
    void incrementIteration();

    /**
     * @brief Retorna el contador de iteraciones con el valor actual
     * @return el contador de iteraciones con el valor actual
     */
    int getCurrentIteration();

    /**
     * @brief Retorna si se debe detener la simulacion porque se cumplio la condicion
     * de parada
     * @return si se debe detener la simulacion porque se cumplio la condicion de parada
     */
    bool stopEvolution();

    /**
     * @brief Retorna el parametro cognitivo
     * @return parametro cognitivo
     */
    int getCognitiveParameter();

    /**
     * @brief Retorna el parametro social
     * @return parametro social
     */
    int getSocialParameter();

    /**
     * @brief Retorna el parametro de inertia
     * @return parametro de inertia
     */
    double getInertiaParameter();

    /**
     * @brief Retorna el parametro maxima velocidad
     * @return parametro maxima velocidad
     */
    int getMaxSpeedParameter();

    /**
     * @brief Retorna un valor aleatorio entre [0,1]
     * @return valor aleatorio entre [0,1]
     */
    double getRandomUniform();

};

#endif // SIMULATION_H
