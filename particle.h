#ifndef PARTICLE_H
#define PARTICLE_H


#include <QObject>
#include <QList>
#include <QSet>



class Particle
{

private:
    /**
     * @brief Identificador unico del individuo
     */
    unsigned int particleId;

    /**
     *  @brief Lista de parametros de un individuo
     */
    QList<double> parametersList;

    /**
     *  @brief Lista de velocidades de la particula
     */
    QList<double> velocitityList;

    /**
     * @brief Valor de desempeno del individuo
     */
    double performanceValue;

    /**
     * @brief Valor de desempeno del individuo para la funcion objetivo 1 tasa de descubrimiento
     * de APs
     */
    double performanceDiscovery;

    /**
     * @brief Valor de desempeno del individuo para la funcion objetivo 2 latencia de full scanning
     *
     */
    double performanceLatency;

    /**
     * @brief Conjunto utilizado para generar secuencias de scanning aleatorias
     */
    QSet<int> channelSequenceSet;

    /**
     * @brief Contador de encuentros ganados en un torneo
     */
    int wonMatchesCounter;


public:
    /**
     * @brief Constructor de la clase
     *
     * @param numberOfApsDeployed Numero de APs desplegados
     * @param maxSpeed velocidad maxima del algoritmo de enjambre de particulas
     */
    Particle(int numberOfApsDeployed, int maxSpeed);

    /**
     * @brief Destructor de la clase
     */
    ~Particle();

    /**
     * @brief Constructor copia
     */
    Particle(Particle &p);

    /**
     * @brief Retorna el Id del individuo
     * @return Retorna el Id del individuo
     */
    int getParticleId();

    /**
     * @brief Retorna un numero de canal aleatorio.
     *
     * Esta funcion se utiliza para inicializar los individuos de manera que los canales
     * aleatorios seleccionados no se repitan en la secuencia de scanning.
     *
     * @return Numero de canal aleatorio
     */
    int getRandomChannel();

    /**
     * @brief Retorna un numero de minChannelTime aleatorio
     * @return valor de minChannelTime aleatorio
     */
    double getRandomMinChannelTime();

    /**
     *  @brief Retorna un numero de maxChannelTime aleatorio
     * @return canal aleatorio
     */
    double getRandomMaxChannelTime();

    /**
     * @brief Retorna un valor de velocidad aleatoria entre 1 <= v <= maxSpeed
     * @param maxSpeed valor de velocidad maxima
     * @return valor de velocidad aleatoria
     */
    double getRandomSpeed(int maxSpeed);

    /**
     * @brief Retorna un numero de APs descubiertos en el canal i
     * dado un numero de AP desplegados.
     *
     * El valor se obtiene de la proporcion promedio de APs que operan en
     * cada canal.
     *
     * @param
     * @return Numero de APs descubiertos en el canal i
     */
    double getAPNumberOnChannel(int numberOfApsDeployed, int channel);

    /**
     *  @brief Imprime el individuo en una cadena legible al humano
     */
    void printParticle();

    /**
     * @brief Retorna el individuo como una cadena
     * @return Cadena legible al humano de los parametros del individuo
     */
    QString getParticleAsQString();

    /**
     *  @brief Establece el valor de desempeno del individuo
     * @param performance valor de desempeno
     */
    void setPerformanceValue(double performance);

    /**
     *  @brief Calcula el valor de desempeno del individuo
     */
    void calculatePerformanceValue();

    /**
     * @brief Retorna el valor de desempeno del individuo
     * @return valor de desempeno del individuo
     */
    double getPerformanceValue();


    /**
     *  @brief Calcula el valor de desempeno del descubrimiento
     */
    void calculateDiscoveryValue();

    /**
     *  @brief Calcula el valor de desempeno de la latencia
     */
    void calculateLatencyValue();

    /**
     *  @brief Establece el valor de desempeno de la funcion objetivo 1 tasa de descubrimiento
     * @param performance valor de desempeno
     */
    void setPerformanceDiscovery(double performance);

    /**
     * @brief Retorna el valor de desempeno del individuo para la funcion objetivo 1 tasa de descubrimiento
     * @return valor de desempeno de la tasa de descubrimiento del individuo
     */
    double getPerformanceDiscovery() const;

    /**
     *  @brief Establece el valor de desempeno de la funcion objetivo 2 latencia
     * @param performance valor de desempeno de latencia
     */
    void setPerformanceLatency(double performance);

    /**
     * @brief Retorna el valor de desempeno del individuo para la funcion objetivo 2 latencia
     * @return valor de desempeno de la latencia
     */
    double getPerformanceLatency() const;

    /**
     * @brief Asigna el valor del parametro en la posicion i
     * @param i indice del parametro a asignar
     * @param value valor a asignar en el parametro
     */
    void setParameter(int i, double value);

    /**
     * @brief Retorna el valor del parametro en la posicion i
     * @param i indice del parametro a retornar
     */
    double getParameter(int i) const;

    /**
     * @brief Retorna el numero de parametros del individuo
     * @return Numero de parametros del individuo
     */
    int getNumberOfParameters() const;

    /**
     * @brief Asigna el valor del contador de encuentros ganados en torneos
     * @param value numero de encuentros ganados por el individuo en un torneo
     */
    void setWonMatchesCounter(int value);

    /**
     * @brief Retorna el contador de encuentros ganados por el individuo en un torneo
     * @return El contador de encuentros ganados por el individuo en un torneo
     */
    int getWonMatchesCounter();

    /**
     * @brief Incrementa el contador de encuentros ganados del individuo en un torneo
     */
    void incrementWonMatchesCounter();

    /**
     * @brief Sobrecarga del operador = para asignar un individuo
     * @return nuevo individuo
     */
    //Individual& operator = (const Individual &ind);

    /**
     * @brief Retorna la probabilidad de encontrar al menos un AP en el canal pasado como argumento.
     *
     * La distribucion de probabilidad es aproximada de acuerdo al articulo que se esta estudiando
     *
     * @param channel Canal que se escanea
     * @return Valor de probabilidad de encontrar al menos un AP en el canal pasado como argumento.
     */
    double probabilityExistAtLeastOneAp(int channel);

    /**
     * @brief Retorna la probabilidad de que el retardo del primer Probe Response sea menor que el
     * parametro MinChannelTime
     *
     * La distribucion de probabilidad es aproximada de acuerdo al articulo que se esta estudiando
     *
     * @param delay retardo del primer Probe Response recibido
     * @return probabilidad de que el retardo del primer Probe Response sea menor que el
     * parametro MinChannelTime
     */
    double probabilityDelayLessThanMinCT(double delay);

    /**
     * @brief Establece el valor de la velocidad para el componente de la posicion pasada como
     * primer argumento
     * @param position posicion del componente dentro de la lista de velocidades
     * @param velocityValue valor de la velocidad para el componente
     */
    void setVelocitity(int position, double velocityValue);

    /**
     * @brief Retorna el valor de la velocidad del componente en la posicion pasada como argumento
     * @param position posicion del componente
     * @return valor de la velocidad del componente en la posicion pasada como argumento
     */
    double getVelocity(int position);

};


#endif // PARTICLE_H
