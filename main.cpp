#include <iostream>
#include <fstream>
#include <vector>

#include "pairing_heap.h"
#include "binomial_heap.h"

using namespace std;


int main()
{
    ifstream fin("tests/mergeheap.in");
    ofstream fout("tests/mergeheap.out");

    int N, M;
    fin >> N >> M;


    ///vector< pairing_heap > list_of_pairing_heap;
    vector< binomial_heap > list_of_binomial_heap;
    for(int i = 0; i <= N; i++){
        ///pairing_heap temp;
        ///list_of_pairing_heap.push_back(temp);

        binomial_heap temp;
        list_of_binomial_heap.push_back(temp);
    }

    int task, h, x, h1, h2;
    for( int i = 1; i <= M; ++i ){

        fin >> task;

        if( task == 1 ){
            fin >> h >> x;

            ///list_of_pairing_heap[h].push( x );
            list_of_binomial_heap[h].push( x );
        }
        if( task == 2 ){
            fin >> h;

            ///fout << list_of_pairing_heap[h].top() << '\n';
            ///list_of_pairing_heap[h].pop();
            fout << list_of_binomial_heap[h].top() << '\n';
            list_of_binomial_heap[h].pop();
        }
        if( task == 3 ){
            fin >> h1 >> h2;

            ///list_of_pairing_heap[h1].heap_union( list_of_pairing_heap[h2] );
            list_of_binomial_heap[h1].heap_union( list_of_binomial_heap[h2] );
        }
    }

    return 0;
}
