  #include "main.hpp"
  #include "gates.hpp"
// g++ -std=c++11 -I boost_1_70_0 main.cpp -o main
// g++ -g main.cpp -o main -L /usr/local/lib/ -lboost_filesystem

int main(){
  // INTRO
 cout <<"===========================================" << endl;    
 cout <<"    ____ ___ " << endl;                          
 cout <<"   / ___/ _ \\ _   _  ___ _ __   ___ ___ " << endl;    
 cout <<"  | |  | | | | | | |/ _ \\ '_ \\ / __/ _ \\ " << endl;    
 cout <<"  | |__| |_| | |_| |  __/ | | | (_|  __/ " << endl;    
 cout <<"   \\____\\__\\_\\ __,_|\\___|_| |_|\\___\\___| " << endl; 
 cout << "" << endl;
 cout <<"===========================================" << endl;   

//     ____ ___                            
//   / ___/ _ \ _   _  ___ _ __   ___ ___ 
//  | |  | | | | | | |/ _ \ '_ \ / __/ _ \
//  | |__| |_| | |_| |  __/ | | | (_|  __/
//   \____\__\_\\__,_|\___|_| |_|\___\___|
                                        
                                       


  // initialisation
  qubit q0 = qubitFactory(complex<double>(0,0),complex<double>(1,0));
  qubit q1 = qubitFactory(complex<double>(1,0),complex<double>(0,0));
  qubit q2 = qubitFactory(complex<double>(0.3,0),complex<double>(0.7,0));
  qubit q3 = qubitFactory(complex<double>(0.5,0),complex<double>(0.5,0));
  qubit q4 = qubitFactory(complex<double>(5,3),complex<double>(0,6));
  qubit q5 = qubitFactory(complex<double>(3,-4),complex<double>(7,2));

<<<<<<< HEAD
  std::list<qubit> qubits;

  // matrix<complex<double> > hadamard (2,2);
  // hadamard(0,0) = complex<double>(1/(sqrt(2)));
  // hadamard(0,1) = complex<double>(1/(sqrt(2)));
  // hadamard(1,0) = complex<double>(1/(sqrt(2)));
  // hadamard(1,1) = complex<double>(-(1/(sqrt(2))));

=======
  matrix<complex<double> > hadamard (2, 2);
  hadamard(0,0) = complex<double>(1/(sqrt(2)));
  hadamard(0,1) = complex<double>(1/(sqrt(2)));
  hadamard(1,0) = complex<double>(1/(sqrt(2)));
  hadamard(1,1) = complex<double>(-(1/(sqrt(2))));


    std::list<qubit> qubits;
>>>>>>> 62c3d9772c945af733a083cc8893e28d4608fbdb
    identity_matrix<double> mi (2);

    q0.ops.push_back(mi);
    q0.ops.push_back(hadamard);
    q1.ops.push_back(mi);
    q1.ops.push_back(mi);
    q2.ops.push_back(mi);
    q2.ops.push_back(hadamard);
    q3.ops.push_back(mi);
    q3.ops.push_back(mi);
    q4.ops.push_back(hadamard);
    q4.ops.push_back(mi);
    q5.ops.push_back(hadamard);
    q5.ops.push_back(hadamard);

    qubits.push_back(q0);
    qubits.push_back(q1);
    qubits.push_back(q2);
    qubits.push_back(q3);
    qubits.push_back(q4);
    qubits.push_back(q5);

    run(qubits);

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
      measureQubits(qubits);

    }
    else
    {
      cerr << "errors. cannot run program." << endl;
    }


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
     // cout << " currentOp type " << typeid(currentOp).name() << endl;
      // Do matrix multiplication
      cout << "multiplication " << qIter->state << " * " << currentOp << endl;
      qIter->state = prod(qubitAsHorizontalMatrix(*qIter),currentOp);
      cout << "new qubit " << j << " state :: " ;
      displayMatrix(qIter->state);
      cout << endl;
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
          cout << opsIter->operator()(s1, s2) << " " << endl;;
        }
        cout << endl;
      }

      cout << endl;

       if(qIter->ops.size()!= opSize){valid = false;cerr << "ERROR : q" << i<< " opSize is " << qIter->ops.size() << " should be " << opSize << endl; }

      }
       i++;
   }

  return valid;
 }

void displayMatrix(matrix<complex<double> > m){
  for(int s1=0; s1 < m.size1(); s1++){
        for(int s2=0; s2 < m.size2(); s2++){
          cout << m.operator()(s1, s2) << " " << endl;;
        }
      }
}



matrix<complex<double> > qubitAsHorizontalMatrix(qubit q){
  // q.ket0=q.state.operator()(0,0);
  // q.ket1=q.state.operator()(1,0);
  matrix<complex<double> > mq (1,2);
  mq(0,0)=q.ket0;
  mq(0,1)=q.ket1;
  return mq;
}


matrix<complex<double> > qubitAsVerticalMatrix(qubit q){
  // q.ket0=q.state.operator()(0,0);
  // q.ket1=q.state.operator()(1,0);
  matrix<complex<double> > mq (2,1);
  mq(0,0)=q.ket0;
  mq(1,0)=q.ket1;
  return mq;
}

void measureQubits(list<qubit> qubits){
  std::list<qubit>::iterator qIter;

  for(qIter=qubits.begin(); qIter!=qubits.end(); advance(qIter,1)){
    cout <<  measureQubit(*qIter) << endl;
  }
}

string measureQubit(qubit q){
  complex<double> cket0;
  complex<double> cket1;
  cket0 = q.state.operator()(0,0);
  cket1 = q.state.operator()(1,0);
  double totalVecLen = sqrt((abs(cket0) * abs(cket0)) + (abs(cket1) * abs(cket1)));
  double p0 = double(abs(cket0)*abs(cket0))/double(totalVecLen*totalVecLen);
  double p1 = double(abs(cket1)*abs(cket1))/double(totalVecLen*totalVecLen);
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
  // normalize TODO
  qubit q;
  q.ket0 = fket0;
  q.ket1 = fket1;

  q.state = matrix<complex<double> > (2,1);
  q.state(0,0) = q.ket0;
  q.state(1,0) = q.ket1;

  return q;
}
