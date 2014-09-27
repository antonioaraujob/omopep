#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QValidator>
#include <QDoubleValidator>
#include <QMessageBox>


#include "particle.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(700, 500);

    // Validadores para los parametros del algoritmo

    QValidator * validatorCognitiveParameter = new QIntValidator(0, 9, this);
    ui->lineEditCognitiveParameter->setValidator(validatorCognitiveParameter);
    ui->lineEditCognitiveParameter->setToolTip("[0..9]");

    QValidator * validatorSocialParameter = new QIntValidator(0, 9, this);
    ui->lineEditSocialParameter->setValidator(validatorSocialParameter);
    ui->lineEditSocialParameter->setToolTip("[0..9]");

    QDoubleValidator * validatorInertia = new QDoubleValidator(0.0, 1.0, 2, this);
    validatorInertia->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEditInertiaParameter->setValidator(validatorInertia);
    ui->lineEditInertiaParameter->setToolTip("[0..1]");

    QValidator * validatorSpeedParameter = new QIntValidator(1, 9, this);
    ui->lineEditMaxSpeedParameter->setValidator(validatorSpeedParameter);
    ui->lineEditMaxSpeedParameter->setToolTip("[1..9]");

    QValidator * validatorParticlesParameter = new QIntValidator(1, 40, this);
    ui->lineEditParticlesParameter->setValidator(validatorParticlesParameter);
    ui->lineEditParticlesParameter->setToolTip("[1..40]");

    QValidator * validatorIterationsParameter = new QIntValidator(1, 100, this);
    ui->lineEditIterationsParameter->setValidator(validatorIterationsParameter);
    ui->lineEditIterationsParameter->setToolTip("[1..100]");

    connect(ui->pushButtonExecute, SIGNAL(clicked()), this, SLOT(executeAlgorithm()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::executeAlgorithm()
{
    qDebug("...MainWindow::executeAlgorithm()");


    if (!validateFields())
    {
        return;
    }

    qsrand((uint)QTime::currentTime().msec());

    double inertia = ui->lineEditInertiaParameter->text().toDouble();
    qDebug("valor de inercia: %f",inertia);

    simulation = new Simulation(ui->lineEditCognitiveParameter->text().toInt(),
                                             ui->lineEditSocialParameter->text().toInt(),
                                             ui->lineEditInertiaParameter->text().toDouble(),
                                             ui->lineEditMaxSpeedParameter->text().toInt(),
                                             ui->lineEditParticlesParameter->text().toInt(),
                                             ui->lineEditIterationsParameter->text().toInt());

    // inicializar las particulas
    // (la inicializacion de los repositorios (global y locales) tambien se ejecuta en este paso)
    simulation->initializeParticles();


    // repetir por el numero maximo de generaciones
    do{

        // actualizar las particulas
        simulation->updateParticles();


        // evaluar las particulas



        // incrementar el valor de la iteracion
        simulation->incrementIteration();

    }while(!simulation->stopEvolution()); // fin de la repeticion

    qDebug("...terminó la simulación.");
}


bool MainWindow::validateFields()
{
    bool validate = true;

    QMessageBox msg;
    QString message;
    message.append("Los siguientes campos deben estar asignados:\n");

    if (ui->lineEditCognitiveParameter->text().isEmpty())
    {
        message.append("Parámetro cognitivo\n");
        validate = false;
    }
    if (ui->lineEditSocialParameter->text().isEmpty())
    {
        message.append("Parámetro social\n");
        validate = false;
    }
    if (ui->lineEditInertiaParameter->text().isEmpty())
    {
        message.append("Parámetro de inercia\n");
        validate = false;
    }
    if (ui->lineEditMaxSpeedParameter->text().isEmpty())
    {
        message.append("Velocidad máxima\n");
        validate = false;
    }
    if (ui->lineEditParticlesParameter->text().isEmpty())
    {
        message.append("Número de partículas\n");
        validate = false;
    }
    if (ui->lineEditIterationsParameter->text().isEmpty())
    {
        message.append("Número de iteraciones\n");
        validate = false;
    }

    msg.setText(message);

    if (!validate)
        msg.exec();

    return validate;
}
