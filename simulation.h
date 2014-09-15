#ifndef SIMULATION_H
#define SIMULATION_H


/**
 * @brief Clase que modela la simulacion para el algoritmo cultural
 */
class Simulation
{

private:

    /**
     * @brief Contador de identificador de individuo
     *
     * Usado para asignar un identificador unico para cada individuo que se creo en la simulacion.
     */
    static int individualIdCounter;




public:


    Simulation();

    ~Simulation();

    /**
     * @brief Retorna un nuevo identificador para un individuo creado
     * @return Retorna un nuevo identificador para un individuo creado
     */
    static int getNewindividualId();
};

#endif // SIMULATION_H
