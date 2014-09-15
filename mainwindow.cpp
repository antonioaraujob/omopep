#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "individual.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(700, 500);

    connect(ui->pushButtonExecute, SIGNAL(clicked()), this, SLOT(executeAlgorithm()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::executeAlgorithm()
{
    qDebug("...MainWindow::executeAlgorithm()");


    QList<Individual*> particlesList;
    Individual * individuo;

    // inicializacion de la poblacion
    for (int i = 0; i < 20; i++)
    {
        individuo = new Individual(0);
        individuo->printIndividual();
        qDebug("individualId: %d", individuo->getIndividualId());
        particlesList.append(individuo);


    }
    qDebug("tamano de la poblacion: %d",particlesList.count());






}
