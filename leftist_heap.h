using namespace std;

class leftist_heap;

struct node_leftist_heap{
    int key;
    int dist;
    node_leftist_heap *stanga, *dreapta;

    node_leftist_heap(int X, int Y) : key(X), dist(Y), stanga(NULL), dreapta(NULL){}
};

class leftist_heap{
    private:
        node_leftist_heap *root;

        node_leftist_heap* merge_heap(node_leftist_heap* A, node_leftist_heap* B){
            ///A <- B
            if(A == NULL){
                return B;
            }
            if(B == NULL){
                return A;
            }

            if( (B->key) > (A->key) ){
                swap(A, B);
            }

            if(A->stanga == NULL){
                A->stanga = B;
            }
            else {
                A->dreapta = merge_heap(A->dreapta, B);

                if( (A->dreapta->dist) > (A->stanga->dist) ){
                    swap(A->stanga, A->dreapta);
                }
                A->dist = 1 + (A->dreapta->dist);

            }

            return A;
        }


    public:
        leftist_heap() : root(NULL) {}

        leftist_heap (int key, int dist){
            root = new node_leftist_heap(key, dist);
        }

        void heap_union (leftist_heap &H){
            root = merge_heap(root, H.root);
            H.root = NULL;
        }
        int top(){
            return root -> key;
        }
        void push(int key){
            root = merge_heap( root, leftist_heap(key, 0).root );
        }
        void pop(){
            node_leftist_heap *temp = root;
            root = merge_heap(root -> stanga, root -> dreapta);
            delete temp;
        }
};
