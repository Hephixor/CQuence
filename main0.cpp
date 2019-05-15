  #include "main0.hpp"
//  #include "gates.hpp"
// g++ -std=c++11 -I boost_1_70_0 main.cpp -o main
// g++ -g main.cpp -o main -L /usr/local/lib/ -lboost_filesystem

int main(){
  //Intro
cout <<"========================================" << endl;
cout <<"  ____ ___                            " << endl;
cout <<" / ___/ _ \\ _   _  ___ _ __   ___ ___ " << endl;
cout <<"| |  | | | | | | |/ _ \\ '_ \\ / __/ _ \\ " << endl;
cout <<"| |__| |_| | |_| |  __/ | | | (_|  __/ " << endl;
cout <<" \\____\\__\\_ \\__,_|\\___|_| |_|\\___\\___| " << endl;
cout << "" << endl;
cout <<"========================================" << endl;


  // initialisation
  qubit q0 = qubitFactory(complex<double>(1,0),complex<double>(1,0));
  qubit q1 = qubitFactory(complex<double>(1,0),complex<double>(0,0));
  // qubit q2 = qubitFactory(complex<double>(0.3,0),complex<double>(0.7,0));
  // qubit q3 = qubitFactory(complex<double>(0.5,0),complex<double>(0.5,0));
  // qubit q4 = qubitFactory(complex<double>(5,3),complex<double>(0,6));
  // qubit q5 = qubitFactory(complex<double>(3,-4),complex<double>(7,2));

    matrix<complex<double> > v (3,1);
    matrix<complex<double> > w (1,2);

    matrix<complex<double> > x (2,3);
    matrix<complex<double> > y (2,2);

    v(0,0)=1;
    v(1,0)=2;
    v(2,0)=3;

    w(0,0)=4;
    w(0,1)=5;

    x(0,0)=1;
    x(0,1)=2;
    x(0,2)=3;
    x(1,0)=4;
    x(1,1)=5;
    x(1,2)=6;

    y(0,0)=7;
    y(0,1)=8;
    y(1,0)=9;
    y(1,1)=10;

    matrix<complex<double> > f1 (2,2);
    matrix<complex<double> > f2 (2,2);
    matrix<complex<double> > f3 (2,2);
    matrix<complex<double> > f4 (2,2);

    // always 0
    f1(0,0)=1;
    f1(0,1)=1;
    f1(1,0)=0;
    f1(1,1)=0;

    // always 1
    f1(0,0)=0;
    f1(0,1)=0;
    f1(1,0)=1;
    f1(1,1)=1;

    // not
    f1(0,0)=0;
    f1(0,1)=1;
    f1(1,0)=1;
    f1(1,1)=0;

    // identity
    f1(0,0)=1;
    f1(0,1)=0;
    f1(1,0)=0;
    f1(1,1)=1;





    cout << "tensorProduct" << endl << endl;;
    displayFancyMatrix(tensorProduct(v,w));
    cout << "=====" << endl;
    displayFancyMatrix(tensorProduct(x,y));
    cout << "=====" << endl;
    displayFancyMatrix(tensorProduct(q0.state,q1.state));
    cout << "=====" << endl;

  std::list<qubit> qubits;

  // Operation matrix
  matrix<complex<double> > hadamard (2,2);
  hadamard(0,0) = complex<double>(1/(sqrt(2)));
  hadamard(0,1) = complex<double>(1/(sqrt(2)));
  hadamard(1,0) = complex<double>(1/(sqrt(2)));
  hadamard(1,1) = complex<double>(-(1/(sqrt(2))));

  identity_matrix<double> mi (2);

  q0.ops.push_back(hadamard);
  q1.ops.push_back(hadamard);

  // function

  q0.ops.push_back(hadamard);
  q1.ops.push_back(mi);

  qubits.push_back(q0);
  qubits.push_back(q1);

  //run(qubits);

}

void run(list<qubit> qubits){
  //verification
  if(qubits.size()>16){
    cerr << "maximum size 16 qubits" << endl;
    }

    if(checkOpSize(qubits)){
      cout << "everything ready" << endl;
      cout << " -------------- " << endl;
      makeOperations(qubits);
    }
    else
    {
      cerr << "errors. cannot run program." << endl;
    }


 // run ..

}

void displayFancyMatrix(matrix<complex<double> > m){
  for(int i = 0 ; i < m.size1(); i++){
    for(int j = 0 ; j < m.size2(); j++){
      cout << m.operator()(i,j).real() << "\t";
    }
    cout << "" << endl;
  }
}

matrix<complex<double> > tensorProduct(matrix<complex<double> > m1, matrix<complex<double> > m2){
  int startRow,startCol,i,j,k,l;



  int rowA = m1.size1();
  int colA = m1.size2();
  int rowB = m2.size1();
  int colB = m2.size2();
  int rowC = rowA*rowB;
  int colC = colA*colB;


  matrix<complex<double> > result (rowC,colC);


	for(i=0;i<rowA;i++){
		for(j=0;j<colA;j++){
			startRow = i*rowB;
			startCol = j*colB;
			for(k=0;k<rowB;k++){
				for(l=0;l<colB;l++){
          result(startRow+k,startCol+l) = m1.operator()(i,j)*m2.operator()(k,l);
			//		matrixC[startRow+k][startCol+l] = matrixA[i][j]*matrixB[k][l];
				}
			}
		}
	}

  return result;

}

void makeOperations(list<qubit> qubits){
  std::list<qubit>::iterator qIter;
  std::list<matrix<complex<double> > >::iterator opsIter;

  int nbOps = qubits.front().ops.size();

  for(int i = 0 ; i < nbOps ; i++){
    int j = 0;
    for (qIter = qubits.begin(); qIter != qubits.end(); qIter++){
      cout << "qubit " << j << " state :: " << qIter->state << endl;
      cout << "qubit " << j << " operation " << i << endl;
      matrix<complex<double> > currentOp;
      opsIter = qIter->ops.begin();
      advance(opsIter,i);
      currentOp = *opsIter;

      // Do matrix multiplication
      qIter->state = prod(qubitAsHorizontalMatrix(*qIter),currentOp);
      cout << "new qubit " << j << " state :: " << qIter->state << endl;
      j++;
    }
    cout << endl;
  }

}

bool checkOpSize(list<qubit> qubits){

  int opSize = qubits.front().ops.size();
  bool valid = true;
  int i = 0;
  cout << "expected length for all qubits : " << opSize << endl;

    std::list<qubit>::iterator qIter;
    std::list<matrix<complex<double> > >::iterator opsIter;

   for (qIter = qubits.begin(); qIter != qubits.end(); qIter++){
    cout << "=================================" << endl;
    cout << "state :: " << qIter->state << endl;
    cout << "q" << i << " |   opsize :: " << qIter->ops.size() << endl;
    int j = 0;
    for (opsIter = qIter->ops.begin(); opsIter != qIter->ops.end(); opsIter++){
      cout << "Operation " << j << " : " << endl;
      j++;
      for(int s1=0; s1 < opsIter->size1(); s1++){
        for(int s2=0; s2 < opsIter->size2(); s2++){
          cout << opsIter->operator()(s1, s2) << " ";
        }
        cout << endl;
      }

      cout << endl;

       if(qIter->ops.size()!= opSize){valid = false;cerr << "ERROR : opSize is " << qIter->ops.size() << " should be " << opSize << endl; }

      }
       i++;
   }

  return valid;
 }

matrix<complex<double> > qubitAsHorizontalMatrix(qubit q){
  matrix<complex<double> > mq (1,2);
  mq(0,0)=q.ket0;
  mq(0,1)=q.ket1;
  return mq;
}


matrix<complex<double> > qubitAsVerticalMatrix(qubit q){
  matrix<complex<double> > mq (2,1);
  mq(0,0)=q.ket0;
  mq(1,0)=q.ket1;
  return mq;
}


string measureQubit(qubit q){
  double totalVecLen = sqrt((abs(q.ket0) * abs(q.ket0)) + (abs(q.ket1) * abs(q.ket1)));
  double p0 = double(abs(q.ket0)*abs(q.ket0))/double(totalVecLen*totalVecLen);
  double p1 = double(abs(q.ket1)*abs(q.ket1))/double(totalVecLen*totalVecLen);
  double total = p0 + p1;
  string eval;

  cout << " ====================================== " << endl;
  cout << "totalVecLen = " << totalVecLen << " | po = " << p0 << " | p1 = " << p1 << " | p0 + p1 = " << total <<  endl;
  if(p0>p1){eval = "false";}
  else{eval = "true";}
  if(total>1){cerr << "Warning : total p should be 1. It is " << double(total) << endl;}

  return eval;
}


qubit qubitFactory(complex<double> fket0, complex<double> fket1){
  qubit q;
  q.ket0 = fket0;
  q.ket1 = fket1;

  q.state = matrix<complex<double> > (2,1);
  q.state(0,0) = q.ket0;
  q.state(1,0) = q.ket1;

  return q;
}
