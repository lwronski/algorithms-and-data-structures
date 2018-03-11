#include <iostream>
using namespace std;

template < typename T1, typename T2 > class node {

    public:

    T1 k;
    T2 n;
    node * left;
    node * right;
    node * parent;

    node(T1 k, T2 n) { this->k = k; this->n = n;  left = right = parent = NULL;}

    T1 GetKey() { return k; }

    T2 GetName() { return n; }

    friend ostream& operator << (ostream& st, node<T1,T2>& a) {
            st << a.k << " " << a.n << endl;
    }
};

template < typename T1, typename T2 > class iteratorM {

    node<T1,T2>* pointer = nullptr;
    public:

        iteratorM() { pointer = nullptr; }
        iteratorM(node<T1,T2>*a) { pointer = a;}

        iteratorM( const iteratorM<T1,T2> & k ) {
            pointer = k.pointer;
        }

        node<T1,T2>& operator *() {
            return *pointer;
        }

        node<T1,T2>* operator->() {
            return pointer;
        }

        operator bool() {
            if(pointer != nullptr) return true;
            else return false;
        }
};


template < typename T1, typename T2 > class map {


    public:

        node<T1,T2>* root;
        int sizetree;
        map() { root = NULL; sizetree = 0; }

        node<T1,T2>* position (T1 key) {

            node<T1,T2>* findvertex= root;

            if(root==NULL) {
                return NULL;
            }

            while( (findvertex->left != NULL || findvertex->right != NULL ) ) {

                if ( findvertex->k == key ) { return findvertex; }
                else {
                    if ( findvertex->k > key ) {
                       if(findvertex->left != NULL) { findvertex = findvertex->left; }
                        else return findvertex;
                    }
                    else {
                       if(findvertex->right != NULL ){ findvertex = findvertex->right;}
                       else return findvertex;
                    }
                }
            }
            return findvertex;
        }


        node<T1,T2>* nextdown (node<T1,T2>* position) {

            if ( position->right == NULL ) {
                return position;
            }
            position = position->right;
            while ( position->left != NULL ) {
                position = position->left;
            }
            return position;
        }
        void insert( T1 key, T2 name) {
             if( root == NULL ) { // empty tree
                 root = new node<T1,T2>(key,name);
                 sizetree++;
                 return;
             }
             node<T1,T2>* findvertex = position(key);
             if(findvertex->k == key ) {
                findvertex->n = name;
             }
             else {
                sizetree++;
                node<T1,T2>* vertex = new node<T1,T2>(key,name);
                vertex->parent = findvertex;
                if(findvertex->k > key ) {
                    findvertex->left = vertex;
                }
                else {
                    findvertex->right = vertex;
                }
            }
        }

        bool deletenode (node<T1,T2>* findvertex) {

            if ( findvertex->left == NULL && findvertex->right == NULL ) { // liœæ
                if ( findvertex == root ) {
                    root = NULL;
                }
                else {
                    if( findvertex->parent->left == findvertex) {
                        findvertex->parent->left = NULL;
                    }
                    else {
                         findvertex->parent->right = NULL;
                    }
                }
                delete findvertex;
                return true;
            }
            if ( findvertex->left == NULL || findvertex->right == NULL) { // jeden syn

                if ( findvertex == root ) {
                    if(findvertex->left != NULL) {
                        root = findvertex->left;
                        root->parent = NULL;
                    }
                    else {
                        root = findvertex->right;
                        root->parent = NULL;
                    }
                }
                else {

                    if(findvertex->parent->left == findvertex) {
                        if(findvertex->left != NULL) {
                                findvertex->parent->left = findvertex->left;
                                findvertex->left->parent = findvertex->parent;
                        }
                        else {
                            findvertex->parent->left = findvertex->right;
                            findvertex->right->parent = findvertex->parent;
                        }
                    }
                    else {
                        if(findvertex->left != NULL) {
                                findvertex->parent->right = findvertex->left;
                                findvertex->left->parent = findvertex->parent;
                        }
                        else {
                            findvertex->parent->right = findvertex->right;
                            findvertex->right->parent = findvertex->parent;
                        }
                    }
                }
                delete findvertex;
                return true;
            }
            // dwoch synow
            node<T1,T2> * nextdownvertex = nextdown(findvertex);

            findvertex->k = nextdownvertex->k;
            findvertex->n = nextdownvertex->n;
            deletenode(nextdownvertex);
        }

        bool erase( T1 key ) {

            if ( root == NULL ) {
                return false;
            }
            node<T1,T2>* findvertex = position(key);
            if ( findvertex->k != key ) {
                return false;
            }
            deletenode(findvertex);
            sizetree--;
            return true;
        }

        bool erase(iteratorM<T1,T2> it) {

            if(*it == nullptr ) return false;
            else return deletenode(*it);

        }

        iteratorM<T1,T2> find(T1 key) {
            node<T1,T2>* findvertex = position(key);
            if( root != NULL && findvertex->k == key) {
                return iteratorM<T1,T2> (findvertex);
            }
            else return iteratorM<T1,T2> (nullptr);
        }

        iteratorM<T1,T2> begin() {

            if( root == NULL ) {
                    return iteratorM<T1,T2> (nullptr);
            }
            node<T1,T2>* findvertex = root;
            while(findvertex->left != NULL ) {
              findvertex = findvertex->left;
            }
            return iteratorM<T1,T2> (findvertex);
        }

        iteratorM<T1,T2> end() {

            if( root == NULL ) return iteratorM<T1,T2> (nullptr);
            node<T1,T2>* findvertex = root;
            while(findvertex->right != NULL ) {
              findvertex = findvertex->right;
            }
            return iteratorM<T1,T2> (findvertex);
        }

        void inorder(node<T1,T2>* vertex) {

              if(vertex->left != NULL ) {
                inorder(vertex->left);
              }
              cout << vertex->k << " " << vertex->n << endl;
              if(vertex->right!=NULL) {
                inorder(vertex->right);
              }
        }

        void postorder( node<T1,T2>*vertex) {
            if(vertex->left != NULL ) {
                postorder(vertex->left);
              }
            if(vertex->right!=NULL) {
                postorder(vertex->right);
            }
            delete vertex;
        }

        void print() {
            if(root!=NULL) {
           inorder(root);
            }
            else cout <<"EMPTY" << endl;
        }

        void clean() {
            if(root!=NULL) {
             postorder(root);
            }
            root = NULL;
            sizetree = 0;
        }

        int size() { return sizetree;}

        T2& operator[] ( T1 key ) {

            node<T1,T2>* findvertex = position(key);

            if( root==NULL || findvertex->k != key ) {
                T2 value;
                this->insert(key,value);
                if( findvertex == NULL ) {
                    findvertex = root;
                }
                else {
                    if(findvertex->right != NULL &&  findvertex->right->k == key) {
                        findvertex = findvertex->right;
                    }
                    if( findvertex->left != NULL &&  findvertex->left->k == key )
                    {
                        findvertex = findvertex->left;
                    }
                }
            }
            return findvertex->n;
        }

        ~map() {
            clean();
        }
};
