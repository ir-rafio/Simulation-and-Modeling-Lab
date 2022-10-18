template<typename T> class Queue
{
protected:
    unsigned Size, Front, Count;
    T *ara;

    void extend();

public:
    Queue();
    Queue(const int);
    ~Queue();

    void enqueue(const T);
    T dequeue();
    T front();
    T back();
    T operator[](const int);
    unsigned size();
    bool isEmpty();
    void clear();

    class Empty_Queue{};
    class Out_of_Bounds{};
};

template<typename T> Queue<T>::Queue(): Size(1), Front(0), Count(0)
{
    ara=new T[Size];
}

template<typename T> Queue<T>::Queue(const int s): Size(s>0? s: 1), Front(0), Count(0)
{
    ara=new T[Size];
}

template<typename T> void Queue<T>::extend()
{
    unsigned i;
    T temp[Count];
    for(i=0; i<Count; ++i) temp[i]=ara[(i+Front)%Size];
    Front=0;

    delete[] ara;
    Size*=2;
    ara=new T[Size];
    for(i=0; i<Count; ++i) ara[i]=temp[i];
}

template<typename T> void Queue<T>::enqueue(const T t)
{
    int Back=Front+Count;
    if(Count==Size) extend();

    Back%=Size;
    ara[Back]=t;
    Count++;
}

template<typename T> T Queue<T>::dequeue()
{
    if(!Count) throw Empty_Queue();
    T temp=ara[Front];

    Front++;
    Front%=Size;
    Count--;

    return temp;
}

template<typename T> T Queue<T>::front()
{
    if(!Count) throw Empty_Queue();
    return ara[Front];
}

template<typename T> T Queue<T>::back()
{
    if(!Count) throw Empty_Queue();
    return ara[(Front+Count-1)%Size];
}

template<typename T> T Queue<T>::operator[](const int i)
{
    if(i>=0 && i<Count) return ara[(Front+i)%Size];
    throw Out_of_Bounds();
}

template<typename T> unsigned Queue<T>::size()
{
    return Count;
}

template<typename T> bool Queue<T>::isEmpty()
{
    return !Count;
}

template<typename T> void Queue<T>::clear()
{
    delete[] ara;
    Size=1;
    ara=new T[Size];
}

template<typename T> Queue<T>::~Queue()
{
    delete[] ara;
}
