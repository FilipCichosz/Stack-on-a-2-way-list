#pragma once
#include <iostream>
using namespace std;

//Klasa Element na szablonie.

template<typename T>class Element
{
private:
    //Pola klasy Element.
    Element<T>* next;
    Element<T>* prev;
    T key;
public:
    //Konstruktor domyslny klasy Element.
    Element() {
        this->key = NULL;
        this->next = nullptr;
        this->prev = nullptr;
    }
    //Konstruktor parametryzowany klasy Element.
    Element(T Key) {
        key = Key;
        this->next = nullptr;
        this->prev = nullptr;
    }
    //Konstruktor parametryzowany klasy Element.
    Element(T Key, Element<T>* Prev, Element<T>* Next) {
        key = Key;
        prev = Prev;
        next = Next;
    }
    //Destruktor klasy Element.
    ~Element() { next = nullptr; prev = nullptr; };
    //Funkcja getujaca element nastepny.
    inline Element<T>* get_next() {
        return this->next;
    }
    //Funkcja getujaca element poprzedni.
    inline Element<T>* get_prev() {
        return this->prev;
    }
    //Funkcja setujaca element nastepny.
    inline void set_next(Element<T>* a) {
        this->next = a;
    }
    //Funkcja setujaca element poprzedni.
    inline void set_prev(Element<T>* a) {
        this->prev = a;
    }
    //Funkcja getujaca wartosc elementu.
    inline T get_key() {
        return this->key;
    }
};

//Klasa dblink_list na szablonie.

template <typename T>
class dblink_list :public Element<T> {
private:
    //Pola klasy dblink_list.
    Element<T>* head, * tail;
    unsigned counter;
    unsigned capacity;
public:
    //Konstruktor domyslny klasy dblink_list.
    dblink_list<T>() {
        head = nullptr;
        tail = nullptr;
        counter = 0;
        capacity = 100;
    }
    //Konstruktor kopiujacy klasy dblink_list.
    dblink_list<T>(const dblink_list& obj)
    {
        while (head != nullptr) {
            pop_front();
        }
        Element<T>* t = obj.head;
        while (t != nullptr)
        {
            push_back(t->key);
            t = t->next;
        }
        this->capacity = obj.capacity;
        delete t;
    }
    //Destruktor klasy dblink_list.
    ~dblink_list<T>() {
        while (head) {
            Element<T>* pomoc = head;
            head = head->get_next();
            delete pomoc;
        }
    }
    //Operator przypisania klasy dblink_list.
    dblink_list<T>& operator=(const dblink_list& obj)
    {
        while (head != nullptr) {
            pop_front();
        }
        Element<T>* t = obj.head;
        while (t != nullptr)
        {
            push_back(t->get_key());
            t = t->get_next();
        }
        delete t;
        return *this;
    }
    //Funkcja setujaca element nastêpny.
    inline Element<T>* get_front() {
        return this->head;
    }
    //Funkcja getujaca element poprzedni.
    inline Element<T>* get_back() {
        return this->tail;
    }
    //Funkcja setujaca element poprzedni.
    inline void set_front(Element<T>* a) {
        this->head = a;
    }
    //Funkcja setujaca wartosc pojemnosci.
    inline void set_capacity(unsigned a) {
        this->capacity = a;
    }
    //Funkcja setujaca element nastepny.
    inline void set_back(Element<T>* a) {
        this->tail = a;
    }
    //Funkcja zwiekszajaca licznik o 1.
    inline void increase() {
        counter++;
    }
    //Funkcja zmniejszajaca licznik o 1.
    inline void decrease() {
        counter--;
    }
    //Funkcja logiczna sprawdzajaca, czy element z przodu jest pusty.
    inline bool empty() const {
        if (head == nullptr)
            return true;
        else
            return false;
    }
    //Funkcja zwracajaca zawartosc licznika elementow w liscie.
    inline unsigned size()
    {
        return counter;
    }
    T get_key();
    void push_front(T val);
    void push_back(T val);
    void pop_front();
    void pop_back();
    friend ostream& operator<< <>(ostream& output, const dblink_list<T>& lista);
    
};

//Funkcje i operatory klasy: dblink_list.

//Funkcja zwracajaca pobrana wartosc z elementu listy.
template <typename T>
T dblink_list<T>::get_key() {
    if (empty()) {
        throw out_of_range("Kontener jest pusty.");
    }
    else {
        return this->head->get_key();
    }
}

//Funkcja dodajaca element na poczatek listy.
template <typename T>
void dblink_list<T>::push_front(T val)
{
    if (capacity == counter) {
        throw overflow_error("Kontener jest przepelniony");
    }
    else {
        Element<T>* temp = new Element<T>(val);

        if (!tail)
            tail = temp;

        if (head)
        {
            temp->set_next(head);
            head->set_prev(temp);
        }

        head = temp;
        counter++;
    }
}

//Funkcja dodajaca element na koniec listy.
template <typename T>
void dblink_list<T>::push_back(T val)
{
    Element<T>* temp = new Element<T>(val);

    if (!head)
        head = temp;

    if (tail)
    {
        temp->set_prev(tail);
        tail->set_next(temp);
    }

    tail = temp;
    counter++;
}

//Funkcja usuwajaca pierwszy element z listy.
template <typename T>
void dblink_list<T>::pop_front() {
    if (head != nullptr) {
        head = head->get_next();
        counter--;
    }
    else
        throw out_of_range("Kontener jest pusty.");
}

//Funkcja usuwajaca ostatni element z listy.
template <typename T>
void dblink_list<T>::pop_back() {
    if (tail != nullptr) {
        tail->prev->next = nullptr;
        tail = tail->prev;
        counter--;
    }
    else
        throw out_of_range("Kontener jest pusty.");
}

//Operator wypisania dla klasy dblink_list.
template <typename T>
ostream& operator << (ostream& output, const dblink_list<T>& list) {
    output << list.head->data;
    Element<T>* temp = list.head->next;
    while (temp != nullptr) {
        output << ", " << temp->data;
        temp = temp->next;
    }
    return output;
}
enum status { pusty, posiada_elementy, pelny };




//Klasa Stack na szablonie.

template <typename T> class Stack:public dblink_list<T> {
private:
    //Pola klasy Stack.
    dblink_list<T> container;
     unsigned counter;
     status stat;
public:
    unsigned maxSize;
    //Konstruktor domyslny klasy Stack.
    Stack<T>() {
        maxSize = 100;
        counter = 0;
         stat = pusty;
    }
    //Konstruktor parametryzowany klasy Stack.
    Stack<T>(int size) {
        maxSize = size;
        counter = 0;
        this->container.set_capacity(size);
        stat = pusty;
    }
    //Destruktor klasy Stack.
    ~Stack<T>() {
        while (container.get_front() != nullptr) {
            container.pop_front();
        }
    }
    //Operator przypisania klasy Stack
    Stack<T>& operator=(const Stack<T>& rhs)
    {
        this->container = rhs.container;
        this->counter = rhs.counter;
        this->maxSize = rhs.maxSize;
        this->stat = rhs.stat;
        return *this;

    }
    //Konstruktor kopiujacy klasy Stack.
    Stack<T>(Stack& copy) {

        Element<T>* cpCurrent = copy.container.get_front();
        Element<T>* lsCurrent = nullptr;
        this->counter = copy.counter;
        this->maxSize = copy.maxSize;
        this->stat = copy.stat;
        if (cpCurrent != nullptr) {
            this->container.set_front(cpCurrent);
            lsCurrent = this->container.get_front();

            cpCurrent = cpCurrent->get_next();

        }
        while (cpCurrent != nullptr) {
            Element<T>* newNode = new Element<T>(cpCurrent->get_key());
            lsCurrent->set_next(newNode);

            lsCurrent = lsCurrent->get_next();
            cpCurrent = cpCurrent->get_next();
        }
    }
    //Podejrzenie dokladnej wartosci ilosci elementow na stosie.
    inline void show_counter() {
        cout << counter << endl;
    }
    //Podejrzenie wartosci maksymalnej pojemnosci stosu.
    inline void show_maxSize() {
        cout << maxSize << endl;
    }
    void push(T num);
    T pop();
    void status();
    void peek();
    friend ostream& operator<< <>(ostream& operation, Stack<T>& lil_stack);
     };



//Funkcje i operatory klasy: Stack.

//Dodanie wartosci na szczyt stosu.
template <typename T>
void Stack<T>::push(T num)
    {

            try {
                container.push_front(num);
                if ((counter + 1) == maxSize)
                {
                    this->stat = pelny;
                }
                else {
                    this->stat = posiada_elementy;
                }
            }
            catch (overflow_error & e) {
                cout << "Stack_overflow: " << e.what() << endl;
            }
            counter++;
    }

//Usuniecie i pobranie wartosci ze szczytu stosu.
template <typename T>
T  Stack<T>::pop()
{
    T temp;
    try {
        Element<T>* tail = container.get_back();
        temp = container.get_key();
        container.pop_front();
        if ((counter - 1) == 0)
        {
            this->stat = pusty;
        }
        else {
            this->stat = posiada_elementy;
        }
        counter--;
    }
    catch (out_of_range& e)
    {
        cout << "Out_of_range: " << e.what() << endl;
    }

    return temp;
}

//Wyswietlenie statusu zapelnienia stosu.
template <typename T>
void Stack<T>::status() {
    switch (stat) {
    case 0:
        cout << "Stos jest pusty" << endl;
        break;
    case 1:
        cout << "Stos zawiera elementy i jest operowalny" << endl;
        break;
    case 2:
        cout << "Stos jest pelny" << endl;
    }
}

//Podejrzenie wartosci ze szczytu stosu.
template <typename T>
void Stack<T>::peek()
{
    try {
        cout << this->container.get_key() << endl;
    }
    catch (out_of_range& e)
    {
        cout << "Out_of_range: " << e.what() << endl;
    }
}

//Operator wypisania dla klasy Stack.
template<typename T> ostream& operator<< (ostream& operation, Stack<T>& lil_stack)
{
    Element<T>* node = lil_stack.container.get_front();
    while (node != nullptr)
    {
        operation << node->get_key() << ", ";
        node = node->get_next();
    }
    return operation;
}