/* Copyright 2003-2004 The MathWorks, Inc. */

#ifndef _SFUN_CPP_USER_DEFINE_CPP_
#define _SFUN_CPP_USER_DEFINE_CPP_

// Define a generic template that can accumulate
// values of any numeric data type
template <class DataType> class GenericAdder {
private:
    DataType Peak;
public:
    GenericAdder() {
        Peak = 0;
    }
    DataType AddTo(DataType Val) {
        Peak += Val;
        return Peak;
    }
    DataType GetPeak() {
        return Peak;
    }
};

// Specialize the generic adder to a 'double'
// data type adder
class DoubleAdder : public GenericAdder<double> {};

#endif