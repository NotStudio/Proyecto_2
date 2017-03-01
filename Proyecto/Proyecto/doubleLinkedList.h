
#ifndef _DOUBLE_LINKED_LIST_H
#define _DOUBLE_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template <class T>
class DoubleLinkedList {
public:
	// Constructor sin parámetros
	DoubleLinkedList() : _ini(nullptr), _current(_ini) {}
    
	// Constructor copia
	DoubleLinkedList(DoubleLinkedList const& other) {
		_ini = copia(other._ini);
	}
    
	// destructor
	~DoubleLinkedList() {
		libera(_ini);
		_ini = nullptr;
	}
    
	// Operador de asignación
	DoubleLinkedList<T> &operator=(const DoubleLinkedList<T> &other) {
        if (this != &other) {
            libera(_ini);
            _ini = copia(other._ini);
        }
        return *this;
    }
    
	// Operador de comparacion
	bool operator== (DoubleLinkedList<T> const& rhs) const {
		Nodo* aux1 = _ini; Nodo* aux2 = rhs._ini;
		while (aux1 != nullptr && aux2 != nullptr){
			if (aux1->_elem != aux2->_elem) return false;
			aux1 = aux1->_sig;
			aux2 = aux2->_sig;
		}
		return (aux1 == nullptr && aux2 == nullptr);
	}
    
	// Añadir un nodo por el comienzo de la lista
	void push_front(const T &e) {
		Nodo * nuevo = new Nodo(nullptr, e, _ini);
		if (_ini != nullptr) _ini->_ant = nuevo;
        _ini = nuevo;
		_current = _ini;
	}
    
	// Elimina el nodo del comienzo de la lista
	void pop_front() {
		if (_ini == nullptr) throw std::invalid_argument("lista vacia");
		Nodo *aux = _ini;
		_ini = _ini->_sig;
		if (_ini != nullptr) _ini->_ant = nullptr;
		delete aux;
	}

	T getCurrent(){
		return _current->_elem;
	}

	bool avanza(){
		if (_current->_sig == nullptr){
			return false;
		}
		else{
			_current = _current->_sig;
			return true;
		}
	}

	bool retrocede(){
		if (_current->_ant == nullptr){
			return false;
		}
		else{
			_current = _current->_ant;
			return true;
		}
	}
        
private:
	// Clase nodo que almacena internamente el elemento (de tipo T),
	// y un puntero al nodo siguiente.
	class Nodo {
    public:
		Nodo() : _sig(nullptr), _ant(nullptr) {}
		Nodo(const T &elem) : _elem(elem), _sig(nullptr), _ant(nullptr) {}
		Nodo(Nodo* ant, const T &elem, Nodo *sig) :
        _elem(elem), _sig(sig), _ant(ant) {}
        
		T _elem;
		Nodo* _sig;
		Nodo* _ant;
	};
    
	// Puntero al primer elemento
	Nodo *_ini;
	Nodo *_current;
    
	// libera todos los nodos de la lista
    void libera(Nodo *ini) {
		while (ini != nullptr) {
			Nodo *aux = ini;
			ini = ini->_sig;
			delete aux;
		}
	}
    
    // Copia el parámetro en la lista.
    // La lista debe estar vacia.
	Nodo* copia(Nodo* other) {
		if (other == nullptr) return nullptr;
		else if (other->_sig == nullptr) { // Un solo elemento
			Nodo* nuevo = new Nodo(other->_elem);
			return nuevo;
		}
		else {
			Nodo* aux = copia(other->_sig);
			Nodo* nuevo = new Nodo(nullptr, other->_elem, aux);
			aux->_ant = nuevo;
			aux = nuevo;
			return aux;
		}
	}
    
};

#endif // _DOUBLE_LINKED_LIST_H

