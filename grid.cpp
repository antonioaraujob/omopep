#include "grid.h"
#include "gridsubinterval.h"

#include <qmessagebox.h>

#include<iostream>
using namespace std;


Grid::Grid(int subIntervals, double lF1, double uF1, double lF2, double uF2 /*NormativePhenotypicPart * nPhenotypicPart*/)
{

    lowerF1 = lF1; //nPhenotypicPart->getLowerF1();

    upperF1 = uF1; //nPhenotypicPart->getUpperF1();

    lowerF2 = lF2; //nPhenotypicPart->getLowerF2();

    upperF2 = uF2; //nPhenotypicPart->getUpperF2();

    subIntervalNumber = subIntervals;

/*
    ptrGrid = new int* [subIntervalNumber];
    for (int i = 0; i < subIntervalNumber; i++)
    {
        ptrGrid[i] = new int[subIntervalNumber];
    }
*/

    ptrGrid = new Cell* [subIntervalNumber];
    for (int i = 0; i < subIntervalNumber; i++)
    {
        //ptrGrid[i] = new int[subIntervalNumber];
        ptrGrid[i] = new Cell[subIntervalNumber];
    }

/*
    QString row;

    qDebug("Elementos de la Matriz : ");
    for (int i = 0; i < subIntervalNumber; i++)
    {
        for (int j = 0; j < subIntervalNumber; j++)
        {
            // inicializar el contador en 0
            ptrGrid[i][j] = 0;
            row.append(QString::number(ptrGrid[i][j]));
            row.append("-");
        }
        qDebug(qPrintable(row));
        row.clear();
    }
*/
    QString row;

    Cell * cell;

    //Individual * individual;
    qDebug("Elementos de la Matriz : ");
    for (int i = 0; i < subIntervalNumber; i++)
    {
        for (int j = 0; j < subIntervalNumber; j++)
        {
            cell = new Cell();
            //individual = new Individual(j);
            //individual->printIndividual();
            //cell->addIndividual(individual);

            // inicializar el contador en 0
            ptrGrid[i][j] = *cell;

            row.append("(");
            row.append(QString::number(ptrGrid[i][j].getCount()));
            row.append(")-");
        }
        qDebug(qPrintable(row));
        row.clear();
    }


    // construir los intervalos de F1 y de F2
    buildSubintervalsF1(lF1, uF1);
    buildSubintervalsF2(lF2, uF2);
}


Grid::~Grid()
{
    // borrar la matriz
    // Elimino cada vector de la matriz
        for (int i = 0; i < subIntervalNumber; i++) {
            delete[] ptrGrid[i];
        }

        // Elimino el vector principal
        delete[] ptrGrid;
}


int Grid::getSubIntervalNumber()
{
    return subIntervalNumber;
}


void Grid::addParticleToGrid(Particle * particle)
{
    qDebug("...Grid::addIndividualToGrid");
    double f1 = particle->getPerformanceDiscovery();
    double f2 = particle->getPerformanceLatency();
    qDebug("particle->getPerformanceDiscovery(): %f", f1);
    // encontrar el subintervalo de F1 y de F2
    int indexF1 = getF1SubintervalIndex(f1);
    int indexF2 = getF2SubintervalIndex(f2);

    if (indexF1 == -1)
    {
        QMessageBox msg;
        msg.setText("Grid::addIndividualToGrid: indexF1 == -1. individuo fuera de la grid");
        msg.exec();

    }
    if (indexF2 == -1)
    {
        QMessageBox msg;
        msg.setText("Grid::addIndividualToGrid: indexF2 == -1. individuo fuera de la grid");
        msg.exec();

    }


    // incrementar el contador de la celda en los subintervalos
    //int count = ptrGrid[indexF1][indexF2];
    //qDebug("...valor de count: %d",count);
    //grid[indexF1].append(indexF2) = increment+1;
    //ptrGrid[indexF1][indexF2] = count+1;

    ptrGrid[indexF1][indexF2].addParticle(particle, indexF1, indexF2);

    // agregar la celda a la lista de celda solo cuando esta no se haya
    // agregado previamente
    if (!isCellInCellList(indexF1,indexF2))
    {
        populatedCellList.append(&ptrGrid[indexF1][indexF2]);
    }


    qDebug("...valor de ptrGrid[%d][%d]: %d",indexF1, indexF2, ptrGrid[indexF1][indexF2].getCount());

}


int Grid::getCount(int f1, int f2)
{
    return ptrGrid[f1][f2].getCount();
}


void Grid::buildSubintervalsF1(double lF1, double uF1)
{
    double widthF1 = (uF1 - lF1) / subIntervalNumber;
    qDebug("---ancho del intervaloF1: %f", widthF1);

    double l = lF1;
    double u = 0;

    //qDebug("   %f",nPhenotypicPart->getLowerF1());
    for (int i = 1; i <= subIntervalNumber /*10*/; i++)
    {
        u = lowerF1+widthF1*i;
        qDebug("%f - %f", l, u);
        GridSubInterval * subInterval = new GridSubInterval(l,u);
        subIntervalListF1.append(subInterval);

        qDebug("   %f",lF1+widthF1*i);
        l = lowerF1+widthF1*i;
    }
}


void Grid::buildSubintervalsF2(double lF2, double uF2)
{
    double widthF2 = (uF2 - lF2) / subIntervalNumber;
    //qDebug("---ancho del intervaloF2: %f", widthF2);

    double l = lF2;
    double u = 0;

    //qDebug("   %f",nPhenotypicPart->getLowerF2());
    for (int i = 1; i <= subIntervalNumber /*10*/; i++)
    {
        u = lowerF2+widthF2*i;
        //qDebug("%f - %f", l, u);
        GridSubInterval * subInterval = new GridSubInterval(l,u);
        subIntervalListF2.append(subInterval);

        //qDebug("   %f",nPhenotypicPart->getLowerF2()+widthF2*i);
        l = lowerF2+widthF2*i;
    }
}

int Grid::getF1SubintervalIndex(double value)
{
    int index = -1;
    for (int i = 0; i < subIntervalListF1.count(); i++)
    {
        if (i == subIntervalListF1.count()-1){
            qDebug("subIntervalListF1.count()-1");
            if (subIntervalListF1.at(i)->belongsToSubinterval(value, true))
            {
                index = i;
                return index;
            }
        }else
        {
            qDebug("subIntervalListF1.count()");
            if (subIntervalListF1.at(i)->belongsToSubinterval(value))
            {
                index = i;
                return index;
            }
        }
    }
    if (index == -1)
    {
        subIntervalListF1.at(0)->printSubInterval();
        qDebug("XXXXXXX getF1SubintervalIndex(double %f): %d", value, index);
        qDebug(qPrintable(QString::number(subIntervalListF1.at(0)->getLowerBound())));
        qDebug(qPrintable(QString::number(subIntervalListF1.at(9)->getUpperBound())));

    }

    return index;
}

int Grid::getF2SubintervalIndex(double value)
{
    int index = -1;
    for (int i = 0; i < subIntervalListF2.count(); i++)
    {
        if (i == subIntervalListF2.count()-1){
            if (subIntervalListF2.at(i)->belongsToSubinterval(value, true))
            {
                index = i;
                return index;
            }
        }else
        {
            if (subIntervalListF2.at(i)->belongsToSubinterval(value))
            {
                index = i;
                return index;
            }
        }
    }
    if (index == -1)
        qDebug("XXXXXXX getF2SubintervalIndex(double %f): %d", value, index);
    return index;
}

void Grid::printGrid()
{
    QString row;
    for (int i = 0; i < subIntervalNumber; i++) {
        for (int j = 0; j < subIntervalNumber; j++) {
            row.append(QString::number(ptrGrid[i][j].getCount()));
            row.append("-");
        }
        qDebug(qPrintable(row));
        row.clear();
    }
}


bool Grid::particleInsideGrid(Particle * particle)
{
    // lowerF1 <= individual->getPerformanceDiscovery() <= upperF1
    // lowerF2 <= individual->getPerformanceLatency() <= upperF2
    if ( ( (particle->getPerformanceDiscovery() >= lowerF1) && (particle->getPerformanceDiscovery() <= upperF1) ) &&
        ( (particle->getPerformanceLatency() >= lowerF2) && (particle->getPerformanceLatency() <= upperF2) ) )
    {
        return true;
    }
    else
    {
        return false;
    }

}

int Grid::getCountOfCell(Particle * particle)
{
    qDebug("...Grid::getCountOfCell");
    double f1 = particle->getPerformanceDiscovery();
    double f2 = particle->getPerformanceLatency();

    // encontrar el subintervalo de F1 y de F2
    int indexF1 = getF1SubintervalIndex(f1);
    int indexF2 = getF2SubintervalIndex(f2);

    if ( (indexF1 == -1) || (indexF2 == -1) )
    {
        return 0;
    }
    else
    {
        return getCount(indexF1, indexF2);
    }

}

QList<Cell*> Grid::getPopulatedCellList()
{
    return populatedCellList;
}


bool Grid::isCellInCellList(int indexF1, int indexF2)
{
    for (int i=0;i<populatedCellList.count(); i++)
    {
        if ( (populatedCellList.at(i)->getSubintervalF1() == indexF1) &&
            (populatedCellList.at(i)->getSubintervalF2() == indexF2) )
        {
            // la celda identificada con (indexF1,indexF2) ya existe en la lista
            return true;
        }
    }
    return false;
}





