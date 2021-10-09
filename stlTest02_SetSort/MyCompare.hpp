#pragma once
#ifndef _MY_COMPARE_H_
#define _MY_COMPARE_H_

template<class T>
class MyCompare
{
public:
    bool operator()(T v1, T v2);
};

#endif // !_MY_COMPARE_H_

template<class T>
bool MyCompare<T>::operator()(T v1, T v2)
{
    return v1 > v2;
}
