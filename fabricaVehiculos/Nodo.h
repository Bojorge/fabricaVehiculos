//
// Created by adrian on 25/03/19.
//

#ifndef TC_NODO_H
#define TC_NODO_H


/// Clase necesaria para que lla clase lista funcione
class Nodo {

public: Nodo* siguiente;
public: int Dato;


    Nodo (int dato){
        Dato = dato;
        siguiente = NULL;
    }
};


#endif //TC_NODO_H
