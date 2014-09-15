#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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


private:
    Ui::MainWindow *ui;

public slots:

    /**
     * @brief Slot para ejecutar el algoritmo cultural al presionar un boton en
     * la interfaz grafica
     */
    void executeAlgorithm();

};

#endif // MAINWINDOW_H
