#ifndef DEF_ARRAY_H
#define DEF_ARRAY_H

typedef  unsigned int uint;


class Array
{
    public:

    Array();

    ~Array();

    static void allocate1D(double* iArray, uint iLenght);

    static void allocate1D(int* iArray, uint iLenght);

    static void allocate2D(double* iArray, uint* iLenght);

    static void allocate2D(double* iArray, uint* iLenght);

    static void deallocate(double* iArray);

    static void deallocate(int* iArray);

    static uint getSize(int* iArray);

    static uint getSize(double* iArray);

    static uint* getSize(int** iArray);

    static uint* getSize(double** iArray);


};




#endif


