#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QValidator>
#include <QDoubleValidator>
#include <QMessageBox>
#include <QStringListModel>
#include <QVector>


#include "particle.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(832, 717);

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
    //do{
    while(!simulation->stopEvolution()) // fin de la repeticion
    {
        // actualizar las particulas
        simulation->updateParticles();


        // evaluar las particulas



        // incrementar el valor de la iteracion
        simulation->incrementIteration();
        qDebug("...fin de iteracion: %d", simulation->getCurrentIteration());

    //}while(!simulation->stopEvolution()); // fin de la repeticion
    }
    qDebug("...terminó la simulación.");

    simulation->printGlobalRepository();

    // poblar la lista de individuos no dominados del archivo externo
    populateListView();

    // generar el grafico
    setupCustomPlot(ui->customPlot);

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

void MainWindow::populateListView()
{
    QStringList individuals;

    QString aux;
    for (int i = 0; i < simulation->getGlobalRepository()->getRepositoryList().count(); i++)
    {
        aux.append(simulation->getGlobalRepository()->getRepositoryList().at(i)->getParticleAsQString());
        individuals << aux;
        aux.clear();
    }


    QStringListModel *model = new QStringListModel();
    model->setStringList(individuals);

    ui->listViewBestNonDominatedParticles->setModel(model);


    int numberOfParticles = simulation->getGlobalRepository()->getRepositoryList().count();
    ui->labelNonDominatedNUmber->setText(QString::number(numberOfParticles));
}


void MainWindow::setupCustomPlot(QCustomPlot *customPlot)
{

    int count = simulation->getGlobalRepository()->getRepositoryList().count();
    QVector<double> discovery(count), latency(count);

    int i = 0;

    Particle * particle;
    //for (int z=simulation->getExternalFile()->getExternalFileList().count()-1; z>=0; z-- )
    for (int z=simulation->getGlobalRepository()->getRepositoryList().count()-1; z>=0; z-- )
    {
        particle = simulation->getGlobalRepository()->getRepositoryList().at(z);
        discovery[i] = particle->getPerformanceDiscovery();
        latency[i] = particle->getPerformanceLatency();
        i++;
    }


    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    customPlot->graph(0)->setData(discovery, latency);

    customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, Qt::red, 4));

    // give the axes some labels:
    customPlot->xAxis->setLabel("Descubierta");
    customPlot->yAxis->setLabel("Latencia");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 75);
    customPlot->yAxis->setRange(0, 300);

    customPlot->yAxis->grid()->setSubGridVisible(true);

    ui->customPlot->replot();

    // show legend:
    //customPlot->legend->setVisible(true);

/*
    // add two new graphs and set their look:
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(250), y0(250), y1(250);
    for (int i=0; i<250; ++i)
    {
      x[i] = i;
      y0[i] = exp(-i/150.0)*cos(i/10.0); // exponentially decaying cosine
      y1[i] = exp(-i/150.0);             // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    customPlot->graph(0)->setData(x, y0);
    customPlot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    customPlot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    customPlot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

*/

}
