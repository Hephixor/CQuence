
#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <complex>

using namespace std;

#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/io.hpp"


using namespace boost::numeric::ublas;



struct unitGate {
int matrix[2][2];
};

struct qubit {
  complex<double> ket0;
  complex<double> ket1;
  list<matrix<double> > ops;
};


void run(list<qubit>);
void makeOperations(list<qubit>);
void addOp(qubit,identity_matrix<double>);
bool checkOpSize(list<qubit>);
string measureQubit(qubit);
qubit qubitFactory(complex<double>, complex<double>);
matrix<complex<double> > qubitAsHorizontalMatrix(qubit);
matrix<complex<double> > qubitAsVerticalMatrix(qubit);
