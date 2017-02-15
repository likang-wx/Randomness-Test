#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "util.cpp"

#include "algo\rank.cpp"
#include "algo\berlekamp_massey.cpp"
#include "algo\dfft.cpp"

#include "test\test.cpp"
#include "test\monobit_frequency_test.cpp"
#include "test\frequency_test_within_a_block.cpp"
#include "test\poker_test.cpp"
#include "test\serial_test.cpp"
#include "test\runs_test.cpp"
#include "test\runs_distribution_test.cpp"
#include "test\test_for_the_longest_run_of_ones_in_a_block.cpp"
#include "test\binary_derivative_test.cpp"
#include "test\autocorrelation_test.cpp"
#include "test\binary_matrix_rank_test.cpp"
#include "test\cumulative_test.cpp"
#include "test\approximate_entropy_test.cpp"
#include "test\linear_complexity_test.cpp"
#include "test\Maurers_universal_test.cpp"
#include "test\Discrete_Fourier_Transform_test.cpp"

default_random_engine generator(time(NULL));
uniform_int_distribution<int> distribution(0, 1);

vector<bool> v;
int main(int argc, char* argv[]){
    if (argc<=1){
        srand(time(NULL));
        for (int i=0;i<1000000;i++){
            v.push_back(distribution(generator));
        }

        test::TestMethod* M = new test::SerialTest(5);

        M->run(v);
        cout<<M->testName()<<endl;
        cout<<M->P<<endl;
        cout<<M->result()<<endl;

        M = new test::SerialTest2(5);
        M->run(v);
        cout<<M->testName()<<endl;
        cout<<M->P<<endl;
        cout<<M->result()<<endl;

        return 0;

    } else {
        fstream f(argv[1]);
        char c;
        while (f>>c){
            if (c=='0') v.push_back(false);
            else if(c=='1') v.push_back(true);
            else {
                cout<< "Invalid character!"<<endl;
                return 0;
            }
        }
    }

    test::monobit_frequency_test(v);
    test::frequency_test_within_a_block(v, 100);
    test::poker_test(v, 4);
    test::poker_test(v, 8);
    test::serial_test(v, 2);
    test::serial_test2(v);
    test::serial_test(v, 5);
    test::serial_test2(v);
    test::runs_test(v);
    test::runs_distribution_test(v);
    test::test_for_the_longest_run_of_ones_in_a_block(v, 10000);
    test::binary_derivative_test(v, 3);
    test::binary_derivative_test(v, 7);
    test::autocorrelation_test(v, 1);
    test::autocorrelation_test(v, 2);
    test::autocorrelation_test(v, 8);
    test::autocorrelation_test(v, 16);
    test::binary_matrix_rank_test(v, 32, 32);
    test::cumulative_test(v);
    test::approximate_entropy_test(v, 2);
    test::approximate_entropy_test(v, 5);
    test::linear_complexity_test(v, 500);
    test::Maurers_universal_test(v, 7, 1280);
    test::Discrete_Fourier_Transform_test(v);
    return 0;
}

