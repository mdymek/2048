#include "cell.hpp"

Cell::Cell(){
    val = 0;
    changed = false;
}

Cell::~Cell(){}

void Cell::setVal( int x ){ val = x; }
int Cell::value() const{ return val; }

void Cell::change(){ changed = true; }
void Cell::unchange(){ changed = false; }

bool Cell::unchanged(){ return !changed; }
