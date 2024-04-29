#include <list>

using namespace std;

const int INF_binomial_heap = 2000000001;

struct node_binomial_heap{
    int key, degree;
    node_binomial_heap *child, *sibling, *parent;
};

node_binomial_heap* new_node_binomial_heap( int val ){
    node_binomial_heap* temp = new node_binomial_heap;
    temp -> key = val;
    temp -> degree = 0;
    temp -> child = temp -> sibling = temp -> parent = NULL;
    return temp;
}

class binomial_heap{

    list < node_binomial_heap* > H;

    list < node_binomial_heap* > :: iterator get_root(){

        list < node_binomial_heap* > :: iterator it, it_max;
        node_binomial_heap* vmax = new_node_binomial_heap( -INF_binomial_heap );

        for( it = H.begin(); it != H.end(); ++it )
            if( (*it) -> key > vmax -> key ){
                vmax = *it;
                it_max = it;
            }

        return it_max;
    }

    void delete_root( node_binomial_heap* tree, binomial_heap& heap ){

        if( tree -> degree == 0 ){
            delete tree;
            return;
        }

        node_binomial_heap* temp = tree;

        tree -> child -> parent = NULL;
        heap.H.push_front( tree -> child );

        tree = tree -> child;
        while( tree -> sibling ){
            tree -> sibling -> parent = NULL;
            heap.H.push_front( tree -> sibling );
            tree = tree -> sibling;
        }
        delete temp;
    }

    void merge_tree( node_binomial_heap* tree1, node_binomial_heap* tree2 ){

        if( tree1 -> key < tree2 -> key )
            swap ( *tree1, *tree2 );

        tree2 -> sibling = tree1 -> child;
        tree2 -> parent = tree1;
        tree1 -> child = tree2;
        tree1 -> degree++;

    }

    void adjust(){

        if( H.size() <= 1 ) return;

        list < node_binomial_heap* > :: iterator prev;
        list < node_binomial_heap* > :: iterator curr;
        list < node_binomial_heap* > :: iterator next;
        list < node_binomial_heap* > :: iterator temp;

        prev = curr = H.begin();
        curr++;
        next = curr;
        next++;

        while( curr != H.end() ){

            while ( ( next == H.end() || (*next) -> degree > (*curr) -> degree ) && curr != H.end() && (*prev) -> degree == (*curr) -> degree ){

                merge_tree( *curr, *prev );

                temp = prev;

                if( prev == H.begin() ){
                    prev++;
                    curr++;
                    if( next != H.end() )
                        next++;
                }
                else prev--;

                H.erase( temp );

            }

            prev++;
            if( curr != H.end() ) curr++;
            if( next != H.end() ) next++;
        }
    }
public:

    int top(){
        return (*get_root()) -> key;
    }

    void push( int val ){

        node_binomial_heap *tree = new_node_binomial_heap( val );
        H.push_front( tree );
        adjust();
    }

    void heap_union( binomial_heap& heap2){

        list < node_binomial_heap* > :: iterator it1 = H.begin();
        list < node_binomial_heap* > :: iterator it2 = heap2.H.begin();

        list < node_binomial_heap* > new_heap;

        while( it1 != H.end() && it2 != heap2.H.end() ){
            if( (*it1) -> degree <= (*it2) -> degree ){
                new_heap.push_back( *it1 );
                it1++;
            }
            else{
                new_heap.push_back( *it2 );
                it2++;
            }
        }

        while( it1 != H.end() ){
            new_heap.push_back( *it1 );
            it1++;
        }

        while( it2 != heap2.H.end() ){
            new_heap.push_back( *it2 );
            it2++;
        }

        heap2.H.clear();

        H = new_heap;
        adjust();
    }

    void pop(){

        list < node_binomial_heap* > :: iterator root = get_root();

        binomial_heap new_heap;
        delete_root( (*root), new_heap );

        H.erase( root );

        heap_union( new_heap );

    }
};
