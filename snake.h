#include "nodo.h"

class Snake
{
private:
    Nodo *front;
    Nodo *rear;
public:
    Snake();
    bool is_empty();
    void enqueue(int x, int y);
    void dequeue(int &x, int &y);
    void get_front(int &x, int &y);
}

Snake::Snake()
{
    this->front = NULL;
    this->rear = NULL;
}

bool Snake::is_empty()
{
    return (this->front == NULL);
}

void Snake::insert_tail(int x, int y)
{
    Nodo *aux = new Nodo();
    aux->pos_x = x;
    aux->pos_y = y;
    aux->sig = NULL;

    if (this->rear == NULL)
    {
        this->rear == aux;
        this->front = aux;
    } else
    {
        this->rear->sig = aux;
        this->rear = aux;
    }
}

void Snake::clear_tail(int &x, int &y)
{
    if (!(this->is_empty()))
    {
        x = this->front->pos_x;
        y = this->front->pos_y;

        Nodo *aux = new Nodo();
        aux = this->front;
        this->front = this->front->sig;
        delete aux;

        if (this->is_empty())
        {
            this->rear = NULL;
        }
    } else
    {
        std::cout << "la cola esta vacia" << std::endl;
    }
}

void Snake::get_front(int &x, int &y)
{
    if (!(this->is_empty()))
    {
        x = this->front->pos_x;
        y = this->front->pos_y;
    } else
    {
        std::cout << "la cola esta vacia" << std::endl;
    }
}
