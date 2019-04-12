#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;
using namespace boost::numeric::ublas;

// g++ -o main main.cpp
struct unitGate {
int matrix[2][2];
};

int main(){
unitGate not_gate;

not_gate.matrix[0][] = {0,1};
not_gate.matrix[1][0] = 1;
not_gate.matrix[0][1] = 1;
not_gate.matrix[1][1] = 0;

for(int i = 0 ; i < 2 ; i++){
    for(int j = 0 ; j < 2 ; j++){
    cout << not_gate.matrix[i][j];
    }
    cout << endl;
}

matrix<double> m (3, 3);
    for (unsigned i = 0; i < m.size1 (); ++ i)
        for (unsigned j = 0; j < m.size2 (); ++ j)
            m (i, j) = 3 * i + j;
    std::cout << m << std::endl;


}