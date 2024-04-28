using namespace std;

struct node_pairing_heap{
    int key;
    node_pairing_heap *child, *sibling;

    node_pairing_heap( int x ) : key( x ), child( NULL ), sibling( NULL ) {}
};
class pairing_heap{

    node_pairing_heap *root;

    node_pairing_heap* merge_heap( node_pairing_heap* H1, node_pairing_heap* H2 ){

        if( H1 == NULL ){
            H1 = H2;
            return H1;
        }
        if( H2 == NULL ) return H1;

        if( H1 -> key < H2 -> key )
            swap( H1, H2 );

        H2 -> sibling = H1 -> child;
        H1 -> child = H2;

        return H1;
    }

    node_pairing_heap* two_pass_merge( node_pairing_heap *_node ){

        if( _node == NULL || _node -> sibling == NULL )
            return _node;

        node_pairing_heap *heap_1, *heap_2, *next_pair;

        heap_1 = _node;
        heap_2 = _node -> sibling;
        next_pair = _node -> sibling -> sibling;

        heap_1 -> sibling = heap_2 -> sibling = NULL;

        return merge_heap( merge_heap( heap_1, heap_2 ), two_pass_merge( next_pair ) );
    }
public:

    pairing_heap() : root( NULL ) {}

    pairing_heap( int _key ){
        root = new node_pairing_heap( _key );
    }

    pairing_heap( node_pairing_heap* _node_pairing_heap ) : root( _node_pairing_heap ) {}

    int top(){
        return root -> key;
    }

    void merge_heap( pairing_heap H ){

        if( root == NULL ){
            root = H.root;
            return;
        }
        if( H.root == NULL ) return;

        if( root -> key < H.root -> key )
            swap( root, H.root );

        H.root -> sibling = root -> child;
        root -> child = H.root;
        H.root = NULL;
    }

    void push( int _key ){
        merge_heap( pairing_heap( _key ) );
    }

    void pop(){

        node_pairing_heap* temp = root;
        root = two_pass_merge( root -> child );

        delete temp;
    }

    void heap_union( pairing_heap &H ){
        merge_heap( H );
        H.root = NULL;
    }
};

