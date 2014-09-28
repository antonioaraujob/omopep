#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void populateListView();

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

};

#endif // MAINWINDOW_H
