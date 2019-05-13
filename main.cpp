  #include "main.hpp"
  #include "gates.hpp"
// g++ -std=c++11 -I boost_1_70_0 main.cpp -o main
// g++ -g main.cpp -o main -L /usr/local/lib/ -lboost_filesystem

int main(){
  // initialisation
  qubit q0 = qubitFactory(complex<double>(0,0),complex<double>(1,0));
  qubit q1 = qubitFactory(complex<double>(1,0),complex<double>(0,0));
  qubit q2 = qubitFactory(complex<double>(0.3,0),complex<double>(0.7,0));
  qubit q3 = qubitFactory(complex<double>(0.5,0),complex<double>(0.5,0));
  qubit q4 = qubitFactory(complex<double>(5,3),complex<double>(0,6));
  qubit q5 = qubitFactory(complex<double>(3,-4),complex<double>(7,2));

  hadamard = matrix<complex<double> > (2, 2);
  hadamard(0,0) = complex<double>(1/(sqrt(2)));
  hadamard(0,1) = complex<double>(1/(sqrt(2)));
  hadamard(1,0) = complex<double>(1/(sqrt(2)));
  hadamard(1,1) = complex<double>(-(1/(sqrt(2))));


  std::list<qubit> qubits;

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

    // matrix<double> gnot (2, 2);
    // gnot(0,0)=0;
    // gnot(0,1)=1;
    // gnot(1,0)=1;
    // gnot(1,1)=0;
    //
    // for (unsigned i = 0; i < gnot.size1 (); ++ i){
    //   cout << "" << endl;
    //  for (unsigned j = 0; j < gnot.size2 (); ++ j){
    //    cout << gnot(i,j) << " ";
    //   }
    //
    //  }
    //  cout << endl;

     // cout << "q5 as matrix : " << endl;
     // matrix<complex<double> > mq = qubitAsHorizontalMatrix(q5);
     //     for (unsigned i = 0; i < mq.size1 (); ++ i){
     //       cout << "" << endl;
     //      for (unsigned j = 0; j < mq.size2 (); ++ j){
     //        cout << mq(i,j) << " ";
     //       }
     //      }
     // cout << endl;
      //
      // identity_matrix<double> mi (2);
      //  matrix<complex<double> > mqi (1,2);
      //  mqi = prod(mq,mi);
      //
      //        for (unsigned i = 0; i < mqi.size1 (); ++ i){
      //          cout << "" << endl;
      //         for (unsigned j = 0; j < mqi.size2 (); ++ j){
      //           cout << mqi(i,j) << " ";
      //          }
      //   }
      //  cout << endl;
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
    }
    else
    {
      cerr << "errors. cannot run program." << endl;
    }


 // run ..

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
      //qIter->state = qIter->state * currentOp;
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
