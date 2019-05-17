


// complex<double> oracleConstantZero(list<qubit> qRegister, qubit q){
//         // Comme f(x) = 0 pour toute valeur de x, |y ⊕ f(x)⟩ = |y⟩.
//         // constant -> true;
//         return q.state.operator()(0,0);
// }
    
    
//     // ------------------------------------------------------------------------------------------
//     // Oracle 2. f(x) = 1 (constant)
//     operation Oracle_One (x : Qubit[], y : Qubit) : Unit {
        
//         body (...) {
//             // Since f(x) = 1 for all values of x, |y ⊕ f(x)⟩ = |y ⊕ 1⟩ = |NOT y⟩.
//             // This means that the operation needs to flip qubit y (i.e. transform |0⟩ to |1⟩ and vice versa).
//             X(y);
//         }
        
//         adjoint invert;
//     }
    
    
//     // ------------------------------------------------------------------------------------------
//     // Oracle 3. f(x) = xₖ (i.e., the value of k-th qubit) (balanced)
//     operation Oracle_Kth_Qubit (x : Qubit[], y : Qubit, k : Int) : Unit {
        
//         body (...) {
//             AssertBoolEqual(0 <= k && k < Length(x), true, "k should be between 0 and (number of qubits - 1), inclusive");
//             CNOT(x[k], y);
//         }
        
//         adjoint invert;
//     }
    
    
//     // ------------------------------------------------------------------------------------------
//     // Oracle 4. f(x) = 1 if x has odd number of 1s, and 0 otherwise (balanced)
//     operation Oracle_OddNumberOfOnes (x : Qubit[], y : Qubit) : Unit {
        
//         body (...) {
//             // f(x) can be represented as x_0 ⊕ x_1 ⊕ ... ⊕ x_(N-1)
//             for (i in 0 .. Length(x) - 1) {
//                 CNOT(x[i], y);
//             }
//         }
        
//         adjoint invert;
//     }
    
    
//     // ------------------------------------------------------------------------------------------
//     // Oracle 5. f(x) = Σᵢ 𝑟ᵢ 𝑥ᵢ modulo 2 for a given bit vector r (scalar product function) (balanced)
//     // Note: oracles 3 and 4 are special cases of this oracle.
//     operation Oracle_ProductFunction (x : Qubit[], y : Qubit, r : Int[]) : Unit {
        
//         body (...) {
//             AssertIntEqual(Length(x), Length(r), "Arrays x and r should have the same length");
            
//             for (i in 0 .. Length(x) - 1) {
//                 if (r[i] == 1) {
//                     CNOT(x[i], y);
//                 }
//             }
//         }
        
//         adjoint invert;
//     }
    
    
//     // ------------------------------------------------------------------------------------------
//     // Oracle 6. f(x) = 1 if x has two or three bits (out of three) set to 1, and 0 otherwise  (majority function) (balanced)
//     operation Oracle_MajorityFunction (x : Qubit[], y : Qubit) : Unit {
        
//         body (...) {
//             AssertBoolEqual(3 == Length(x), true, "x should have exactly 3 qubits");
            
//             // f(x) = (x_0 AND x_1) ⊕ (x_0 AND x_2) ⊕ (x_1 AND x_2)
//             CCNOT(x[0], x[1], y);
//             CCNOT(x[0], x[2], y);
//             CCNOT(x[1], x[2], y);
//         }
        
//         adjoint invert;
//     }