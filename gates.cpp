#include "gates.hpp"

hadamard = matrix<complex<double> > (2, 2);
hadamard(0,0) = complex<double>(1/(sqrt(2)));
hadamard(0,1) = complex<double>(1/(sqrt(2)));
hadamard(1,0) = complex<double>(1/(sqrt(2)));
hadamard(1,1) = complex<double>(-(1/(sqrt(2))));