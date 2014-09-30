#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "qcustomplot.h"

#include "simulation.h"

namespace Ui {
class MainWindow;
}


/**
 * @brief Clase que modela la ventana principal del programa OMOPEP
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    /**
     * @brief Constructor de la clase
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief Destructor de la clase
     */
    ~MainWindow();

    /**
     * @brief Valida los parametros del algoritmo en la interfaz grafica
     * @return si todos los parametros estan establecidos
     */
    bool validateFields();

    /**
     * @brief Completa el widget ListView con lass particulas no dominadas del
     * repositorio // This is available in all editors. al final de la ejecución del algoritmo PSO
     */
    void populateListView();

    /**
     * @brief Configura el widget para generar el grafico de los individuos no dominados del
     * archivo externo.
     *  Se esta utilizando QCustomPlot
     *
     * @param customPlot
     */
    void setupCustomPlot(QCustomPlot *customPlot);


private:
    Ui::MainWindow *ui;

    /**
     * @brief Objeto Simulation que abstrae todo el algoritmo cultural
     */
    Simulation * simulation;

public slots:

    /**
     * @brief Slot para ejecutar el algoritmo cultural al presionar un boton en
     * la interfaz grafica
     */
    void executeAlgorithm();

    /**
     * @brief Slot para habilitar el campo de numero de subintervalos de la grid para la seleccion
     * del lider
     * @param state
     */
    void activateGridSelection(int state);

};

#endif // MAINWINDOW_H
