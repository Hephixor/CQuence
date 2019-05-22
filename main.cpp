  #include "main.hpp"
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

 deutsch();
 //deutschJozsa(3);
 //run(qubits);
}

void deutschJozsa(int size){
  // Declare variables
  identity_matrix<double> identity (2);
  matrix<complex<double> > hadamard (2,2);
  matrix<complex<double> > f0 (2,2);
  matrix<complex<double> > oracle (2,2);
  list<qubit> qubits;
  std::list<qubit>::iterator qIter;
  qubit q1 = qubitFactory(complex<double>(0,0),complex<double>(1,0));
  int tensorSize = pow(2,size);
  matrix<complex<double> > qRegister (tensorSize,1);
  matrix<complex<double> > qRegisterp (tensorSize,1);
  matrix<complex<double> > qRegisterpp (tensorSize,1);
  matrix<complex<double> > qRegisterppp (tensorSize,1);
  matrix<complex<double> > hadamardTensor (tensorSize,tensorSize);
  matrix<complex<double> > oracleTensor (tensorSize,tensorSize);
  matrix<complex<double> > hadamardIdentityTensor (tensorSize,tensorSize);

  // Initialize variables
  hadamard(0,0) = complex<double>(1/(sqrt(2)));
  hadamard(0,1) = complex<double>(1/(sqrt(2)));
  hadamard(1,0) = complex<double>(1/(sqrt(2)));
  hadamard(1,1) = complex<double>(-(1/(sqrt(2))));
  f0(0,0)=1;
  f0(0,1)=0;
  f0(1,0)=0;
  f0(1,1)=1;
  oracle = f0;
  for(int x = 1 ; x < size ; x++){
    qubit q0 = qubitFactory(complex<double>(1,0),complex<double>(0,0));
    qubits.push_back(q0);
  }
  cout << "tensorSize" << tensorSize << endl;
 
  // Intricate qubits
  matrix<complex<double> > tmpReg;
  tmpReg = qubits.front().state;
  qIter = qubits.begin();
  for(int i = 2 ; i < size ; i++){
    tmpReg = tensorProduct(tmpReg, qIter->state);
    advance(qIter,1);
  }

  qubits.push_back(q1);
  qRegister = tensorProduct(tmpReg,q1.state);

  // Build hadamard tensor
  hadamardTensor = tensorProduct(hadamard,hadamard);
  for(int i = 2 ; i < size ; i ++){
    hadamardTensor = tensorProduct(hadamardTensor, hadamard);
  }

  // Build oracle tensor
  oracleTensor = tensorProduct(oracle,oracle);
  for(int j = 2 ; j < size ; j++){
    oracleTensor = tensorProduct(oracleTensor, oracle);
  }

  // Build hadamard tensor and identity tensor
  hadamardIdentityTensor = tensorProduct(hadamard,identity);
  for(int k = 2; k < size ; k++){
    hadamardIdentityTensor = tensorProduct(hadamardIdentityTensor,hadamard);
  }

  // Some display
  cout << "qRegister" << endl;
  displayFancyMatrix(qRegister) ;
  cout <<endl << endl;
  cout << "hadamardTensor" << endl;
  displayFancyMatrix(hadamardTensor);
  cout <<endl << endl;
  cout << "oracleTensor" << endl;
  displayFancyMatrix(oracleTensor);
  cout << endl << endl;
  cout << "hadamardIdentityTensor" << endl;
  displayFancyMatrix(hadamardIdentityTensor);
  cout <<endl << endl;
  
  // apply HxI * Uf
  cout << "apply HxI * Uf " << endl;
  qRegisterp =  prod(hadamardIdentityTensor,oracleTensor);
  displayFancyMatrix(qRegisterp);
  cout <<endl << endl;
  // apply (HxI * Uf) * HxH
  cout << "apply (HxI * Uf) * HxH" << endl;
  qRegisterpp = prod(qRegisterp,hadamardTensor);
  displayFancyMatrix(qRegisterpp);
  cout <<endl << endl;
  // apply ((HxI * Uf) * HxH) * qRegister
  cout << "apply ((HxI * Uf) * HxH) * qRegister" << endl;
  qRegisterppp = prod(qRegisterpp,qRegister);
  displayFancyMatrix(qRegisterppp);
  cout <<endl << endl;

  // qRegisterppp now contains final intricated qubits quarrying the result of the algo

}

void deutsch(){
  // Declare variables
  identity_matrix<double> identity (2);
  matrix<complex<double> > hadamard (2,2);
  matrix<complex<double> > f0 (2,2);
  matrix<complex<double> > qRegister (4,1);
  matrix<complex<double> > qRegisterp (4,1);
  matrix<complex<double> > qRegisterpp (4,1);
  matrix<complex<double> > qRegisterppp (4,1);
  matrix<complex<double> > hadamardTensor (4,4);
  matrix<complex<double> > oracleTensor (4,4);
  matrix<complex<double> > hadamardIdentityTensor (4,4);
  qubit q0 = qubitFactory(complex<double>(1,0),complex<double>(0,0));
  qubit q1 = qubitFactory(complex<double>(0,0),complex<double>(1,0));

  // Initialize variables
  f0(0,0)=1;
  f0(0,1)=0;
  f0(1,0)=0;
  f0(1,1)=1 ;
  hadamard(0,0) = complex<double>(1/(sqrt(2)));
  hadamard(0,1) = complex<double>(1/(sqrt(2)));
  hadamard(1,0) = complex<double>(1/(sqrt(2)));
  hadamard(1,1) = complex<double>(-(1/(sqrt(2))));
  qRegister = tensorProduct(q0.state,q1.state);
  hadamardTensor = tensorProduct(hadamard,hadamard);
  
  displayFancyMatrix(f0);

  int fx0,fx1;

  if(f0.operator()(0,0).real()==1){
    fx0=0;
  } 
  else if(f0.operator()(1,0).real()==1){
    fx0=1;
  }

  if(f0.operator()(0,1).real()==1){
    fx1=0;
  }
  else if(f0.operator()(1,1).real()==1){
    fx1=1;
  }

  cout << "f(0) = " << fx0 << endl;
  cout << "f(1) = " << fx1 << endl;

  if((0^fx0)==0){
    oracleTensor(0,0)=1;
    oracleTensor(1,0)=0;
  }
  else if((0^fx0)==1){
    oracleTensor(0,0)=0;
    oracleTensor(1,0)=1;
  }

  if((1^fx0)==0){
    oracleTensor(0,1)=1;
    oracleTensor(1,1)=0;
  }
  else if((1^fx0)==1){
    oracleTensor(0,1)=0;
    oracleTensor(1,1)=1;
  }

  

  if((0^fx1)==0){
    cout <<"(2,2) = 1" << endl;
    oracleTensor(2,2)=1;
    oracleTensor(3,2)=0;
  }
  else if((0^fx1)==1){
    cout <<"(2,2) = 0" << endl;
    oracleTensor(2,2)=0;
    oracleTensor(3,2)=1;
  }

  if((1^fx1)==0){
    oracleTensor(2,3)=1;
    oracleTensor(3,3)=0;
  }
  else if((1^fx1)==1){
    oracleTensor(2,3)=0;
    oracleTensor(3,3)=1;
  }

  // Always 0
  oracleTensor(0,2)=0;
  oracleTensor(0,3)=0;
  oracleTensor(1,2)=0;
  oracleTensor(1,3)=0;
  oracleTensor(2,0)=0;
  oracleTensor(2,1)=0;
  oracleTensor(3,0)=0;
  oracleTensor(3,1)=0;
  

  hadamardIdentityTensor = tensorProduct(hadamard,identity);

  // Some display
  displayFancyMatrix(qRegister) ;
  cout <<endl << endl;
  displayFancyMatrix(hadamardTensor);
  cout <<endl << endl;
  displayFancyMatrix(oracleTensor);
  cout << endl << endl;
  cout << "hadamardIdentityTensor" << endl;
  displayFancyMatrix(hadamardIdentityTensor);
  cout <<endl << endl;
  
  // apply HxI * Uf 
  cout << "apply HxI * Uf " << endl;
  qRegisterp =  prod(hadamardIdentityTensor,oracleTensor);
  displayFancyMatrix(qRegisterp);
  cout <<endl << endl;
  // apply (HxI * Uf) * HxH
  cout << "apply (HxI * Uf) * HxH" << endl;
  qRegisterpp = prod(qRegisterp,hadamardTensor);
  displayFancyMatrix(qRegisterpp);
  cout <<endl << endl;
  // apply ((HxI * Uf) * HxH) * qRegister
  cout << "apply ((HxI * Uf) * HxH) * qRegister" << endl;
  qRegisterppp = prod(qRegisterpp,qRegister);
  displayFancyMatrix(qRegisterppp);
  cout <<endl << endl;

  /* qRegisterppp now contains final intricated qubits quarrying the result of the algo
     We can see that except the tensor initialization, the number of operation needed to
     compute wether f is balanced or constant is the same 
  */
}

void run(list<qubit> qubits){
  if(qubits.size()>16){
    cerr << "maximum size 16 qubits" << endl;
    }

    if(checkOpSize(qubits)){
      cout << "----------------" << endl;
      cout << "everything ready" << endl;
      cout << "----------------" << endl;
      makeOperations(qubits);
      measureQubits(qubits);
    }
    else
    {
      cerr << "errors. cannot run program." << endl;
    }
}


matrix<complex<double> > applyGateFromMatrix(matrix<complex<double> > state, matrix<complex<double> > gate){
      cout << "qubit state :: " <<endl;

      displayFancyMatrix(state) ;
      cout << "" << endl << endl;
      displayFancyMatrix(gate);
      cout << " " << endl << endl;
      state = switchHVMatrix(prod(switchVHMatrix(state),gate));
      cout << "new qubit  state :: " << endl;
      displayFancyMatrix(state);
      cout << "==========" << endl;
      cout << endl;
      return state;
}

qubit applyGate(qubit q, matrix<complex<double> > gate){
      //  cout << "qubit state :: " <<endl;
      //  displayFancyMatrix(q.state) ;
      //  cout << "" << endl << endl;
      //  displayFancyMatrix(gate);
      //  cout << " " << endl << endl;
      q.state = switchHVMatrix(prod(switchVHMatrix(q.state),gate));
      //  cout << "new qubit  state :: " << endl;
      //  displayFancyMatrix(q.state);
      //  cout << "==========" << endl;
      //  cout << endl;
      return q;
}

void displayFancyMatrix(matrix<complex<double> > m){
  for(int i = 0 ; i < m.size1(); i++){
    for(int j = 0 ; j < m.size2(); j++){
      cout << m.operator()(i,j).real() << " " ;
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
    cout << "=============================" << endl;
    int j = 0;
    for (qIter = qubits.begin(); qIter != qubits.end(); qIter++){
      // Current state
      cout << "qubit " << j << " state :: " <<endl;
      displayFancyMatrix(qIter->state) ;
      cout << "" << endl << "qubit " << j << " operation " << i << ":: " << endl;

      matrix<complex<double> > currentOp;
      opsIter = qIter->ops.begin();
      advance(opsIter,i);
      currentOp = *opsIter;

      // Do matrix multiplication
      //cout << "current op:: " << endl << currentOp << endl;
      displayFancyMatrix(currentOp);
      cout << " " << endl << endl;
      qIter->state = switchHVMatrix(prod(switchVHMatrix(qIter->state),currentOp));

     // cout << "new state expected :: " << endl << switchHVMatrix(prod(switchVHMatrix(qIter->state),currentOp)) << endl;

      cout << "new qubit " << j << " state :: " << endl;
      displayFancyMatrix(qIter->state);
      cout << "==========" << endl;
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
    // cout << "=================================" << endl;
    // cout << "state :: " << qIter->state << endl;
    // cout << "q" << i << " |   opsize :: " << qIter->ops.size() << endl;
    int j = 0;
    for (opsIter = qIter->ops.begin(); opsIter != qIter->ops.end(); opsIter++){
      // cout << "Operation " << j << " : " << endl;
      // j++;
      // for(int s1=0; s1 < opsIter->size1(); s1++){
      //   for(int s2=0; s2 < opsIter->size2(); s2++){
      //     cout << opsIter->operator()(s1, s2) << " ";
      //   }
      //   cout << endl;
      // }
      // cout << endl;

       if(qIter->ops.size()!= opSize){valid = false;cerr << "ERROR : opSize is " << qIter->ops.size() << " should be " << opSize << endl; }

      }
       i++;
   }

  return valid;
 }

matrix<complex<double> > switchHVMatrix(matrix<complex<double> > m){
  matrix<complex<double> > r (m.size2(),m.size1());
  for(int i = 0 ; i < m.size1(); i++){
    for(int j = 0 ; j < m.size2(); j++){
    // cout << "(" << i << "," << j << ")" << endl;
      r(j,i) = m.operator()(i,j);
    }
  }

  return r;
}

matrix<complex<double> > switchVHMatrix(matrix<complex<double> > m){
    matrix<complex<double> > r (m.size2(),m.size1());
  for(int i = 0 ; i < m.size1(); i++){
    for(int j = 0 ; j < m.size2(); j++){
     
      r(j,i) = m.operator()(i,j);
     // cout << "r(" << i << "," << j << ") = " << m.operator()(i,j) <<  endl;
    }
  }

  return r;
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


bool measureQubit(qubit q){
  double totalVecLen = sqrt((abs(q.ket0) * abs(q.ket0)) + (abs(q.ket1) * abs(q.ket1)));
  double p0 = double(abs(q.ket0)*abs(q.ket0))/double(totalVecLen*totalVecLen);
  double p1 = double(abs(q.ket1)*abs(q.ket1))/double(totalVecLen*totalVecLen);
  double total = p0 + p1;
  bool eval;

  cout << " ====================================== " << endl;
  cout << "totalVecLen = " << totalVecLen << " | po = " << p0 << " | p1 = " << p1 << " | p0 + p1 = " << total <<  endl;
  if(p0>p1){eval = false;}
  else{eval = true;}
  if(total>1){cerr << "Warning : total p should be 1. It is " << double(total) << endl;}
  cout << " ====================================== " << endl;
  return eval;
}

void measureQubits(list<qubit> qubits){
  int i = 0 ;
  std::list<qubit>::iterator qIter;
  for(qIter=qubits.begin(); qIter!=qubits.end();advance(qIter,1)){
    cout << "q" << i << endl;
    cout << measureQubit(*qIter) << endl << endl;;
    i++;
  }
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
