#include "cell.h"

Cell::Cell()
{
    cellParticleList.clear();
}

Cell::~Cell()
{

}

int Cell::getCount()
{
    return cellParticleList.count();
}

Particle * Cell::getParticle(int index)
{
    return cellParticleList.at(index);
}

void Cell::addParticle(Particle *particle, int indexF1, int indexF2)
{
    cellParticleList.append(particle);
    f1 = indexF1;
    f2 = indexF2;
}


QList<Particle *> Cell::getParticleList()
{
    return cellParticleList;
}


Cell& Cell::operator = (const Cell &cell)
{
    if (&cell != this)
    {
        this->cellParticleList = cell.cellParticleList;
    }
    return *this;
}

int Cell::getSubintervalF1()
{
    return f1;
}

int Cell::getSubintervalF2()
{
    return f2;
}
