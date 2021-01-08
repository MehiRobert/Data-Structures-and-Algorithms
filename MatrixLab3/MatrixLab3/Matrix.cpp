#include "Matrix.h"
#include <exception>
#include <iostream>
using namespace std;

//Complexity:Θ(1)
Matrix::Matrix(int nrLines, int nrCols) {

    //TODO - Implementation
    this->lines = nrLines;
    this->columns = nrCols;
    this->head = -1;
    this->tail = -1;
    this->cap = 1;
    this->firstempty = 0;
    this->size = 0;

    this->elems = new DLLANode[1];
    this->elems[this->cap - 1].next = -1;
    this->elems[0].previous = -1;


}
Matrix::~Matrix()
{
   
}
// Complexity:Θ(n)
void Matrix::resize()
{
    this->cap = 2 * this->cap;
    DLLANode* newelems = new DLLANode[this->cap];
    for (int i = 0; i < this->cap / 2; i++)
    {
        newelems[i].data = this->elems[i].data;
        newelems[i].next = this->elems[i].next;
        newelems[i].previous = this->elems[i].previous;
    }
    delete[] this->elems;
    for (int i = this->cap / 2; i < this->cap; i++)
    {
        newelems[i].next = i + 1;
        newelems[i].previous = i - 1;
    }
    newelems[this->cap - 1].next = -1;
    this->firstempty = this->cap / 2;
    this->elems = newelems;
}

//Complexity Θ(1)
int Matrix::nrLines() const {
    return this->lines;
}

//Complexity Θ(1)
int Matrix::nrColumns() const {
    return this->columns;
}

//BC : Θ(1) WC: Θ(n) : Complexity: O(n)
TElem Matrix::element(int i, int j) const {
    if (i < 0 or j < 0 or j >= this->nrColumns() or i >= this->nrLines())
        throw exception();
    int current = this->head;
    while (current != -1)
    {
        if (this->elems[current].data->line == i and this->elems[current].data->column == j)
            return this->elems[current].data->value;
        current = this->elems[current].next;
    }
    return NULL_TELEM;
}
int Matrix::allocate() {
    int newElem = this->firstempty;
    if (newElem != -1)
    {
        this->firstempty = this->elems[this->firstempty].next;
        if (this->firstempty != -1)
            this->elems[this->firstempty].previous = -1;
        this->elems[newElem].next = -1;
        this->elems[newElem].previous = -1;
    }
    return newElem;
}
void Matrix::deallocate(int poz) {
    this->elems[poz].next = this->firstempty;
    this->elems[poz].previous = -1;
    if (this->firstempty != -1)
        this->elems[this->firstempty].previous = poz;
    this->firstempty = poz;
}


//Complexity Θ(n)
TElem Matrix::modify(int i, int j, TElem e) {

    if (i < 0 or j < 0 or j >= this->nrColumns() or i >= this->nrLines())
        throw exception();
    int new_pos = allocate();
    if (this->cap == this->size or new_pos == -1)
    {
        this->resize();
        new_pos = allocate();

    }
   
    if (this->head == -1)
    {
        Triples* t = new Triples();
        t->column = j;
        t->line = i;
        t->value = e;
        this->elems[new_pos].data = t;
        this->elems[new_pos].next = -1;
        this->head = new_pos;
        this->tail = new_pos;
        this->size++;

    }
    else
    {
        int current = this->head;
        int cond = 0;
        while (current != -1 and cond == 0)
        {
            if (this->elems[current].data->line == i and this->elems[current].data->column == j)
                cond = 1;
            else
            {
                current = this->elems[current].next;
            }
        }
        // this is the add
        if (cond == 0 and e != 0)
        {
            Triples* t = new Triples();
            t->column = j;
            t->line = i;
            t->value = e;
            this->elems[new_pos].data = t;
            this->elems[new_pos].next = -1;
            this->elems[new_pos].previous = this->tail;
            this->elems[this->tail].next = new_pos;
            this->tail = new_pos;
            this->size++;
        }
        //modify
        else if (cond == 1 and e != 0)
        {
            TElem old = this->elems[current].data->value;
            this->elems[current].data->value = e;
            return old;
        }
        //delete
        else if (cond == 1 and e == 0)
        {
            TElem avalue = this->elems[current].data->value;
            if (current == this->head)
            {
                this->head = this->elems[current].next;
                this->elems[this->head].previous = -1;
                this->size--;
                this->deallocate(current);
            }
            else if (this->elems[current].next == -1)
            {
                this->tail = this->elems[current].previous;
                this->elems[this->tail].next = -1;
                this->size--;
                this->deallocate(current);
            }
            else
            {
                this->elems[this->elems[current].previous].next = this->elems[current].next;
                this->elems[this->elems[current].next].previous = this->elems[current].previous;
                this->size--;
                this->deallocate(current);


            }
            return avalue;
        }



    }
    return 0;
}
// BC: Θ(1) WC: Θ(n) : Complexity: O(n)
std::pair<int, int> Matrix::positionOf(TElem e) {
    int current = this->head;
    while (current != -1)
    {
        if (this->elems[current].data->value == e)
        {
            pair<int, int> p = make_pair(this->elems[current].data->line, this->elems[current].data->column);
            return p;
        }
        current = this->elems[current].next;
    }
    return make_pair(-1, -1);
}
