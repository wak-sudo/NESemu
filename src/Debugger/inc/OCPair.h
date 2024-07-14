#pragma once

template <class T>
struct OCPair
{
    T old;
    T current;

    void update(T newVal)
    {
        old = current;
        current = newVal;
    }

    OCPair(T oldVal, T currentVal)
    {
        old = oldVal;
        current = currentVal;
    }

    OCPair()
    {
        old = T();
        current = T();
    }
};