
#include <iostream>
#include <cmath>
#include <list>
#include <string>
#include <complex>

using namespace std;

namespace std {
  template <typename _CharT, typename _Traits>
  inline basic_ostream<_CharT, _Traits> &
  tab(basic_ostream<_CharT, _Traits> &__os) {
    return __os.put(__os.widen('\t'));
  }
}

#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/io.hpp"
#include "boost/qvm/mat_access.hpp"


using namespace boost::numeric::ublas;



struct unitGate {
int matrix[2][2];
};

struct qubit {
  complex<double> ket0;
  complex<double> ket1;
  matrix<complex<double> > state ;
  list<matrix<complex<double> > > ops;
};


void run(list<qubit>);
void makeOperations(list<qubit>);
void addOp(qubit,identity_matrix<double>);
bool checkOpSize(list<qubit>);
string measureQubit(qubit);
qubit qubitFactory(complex<double>, complex<double>);
matrix<complex<double> > qubitAsHorizontalMatrix(qubit);
matrix<complex<double> > qubitAsVerticalMatrix(qubit);
matrix<complex<double> > tensorProduct(matrix<complex<double> >, matrix<complex<double> >);
void displayFancyMatrix(matrix<complex<double> >);
matrix<complex<double> > switchHVMatrix(matrix<complex<double> >);
matrix<complex<double> > switchVHMatrix(matrix<complex<double> >);
