#include <iostream>
using namespace std;

int lefttree[2000000];
int righttree[2000000];
int depth[2000000];

int depthroot( int index, int level)
{
    depth[index] = level;

    if( lefttree[index]!= -1){
        depthroot(lefttree[index], level+1);
    }
    if( righttree[index]!= -1) {
        depthroot(righttree[index],level+1);
    }
}

int postorder ( int index , int out )
{
    if(lefttree[index] != -1){
        postorder(lefttree[index],out);
    }
    if(righttree[index] != -1) {
        postorder(righttree[index],out);
    }
    if( out == 0 ) {
        cout << index << " ";
    }
    else {
        if(lefttree[index] == -1 && righttree[index] == -1 ) {
            cout << index << ":" << depth[index] << " ";
        }
    }
}

int inorder ( int index , int out )
{
    if(lefttree[index] != -1) {
        inorder(lefttree[index],out);
    }
    if( out == 0 ) {
        cout << index << " ";
    }
    else {
        if(lefttree[index] == -1 && righttree[index] == -1 ) {
            cout << index << ":" << depth[index] << " ";
        }
    }
      if(righttree[index] != -1) {
        inorder(righttree[index],out);
    }
}
int preorder ( int index , int out )
{
    if( out == 0 ) {
        cout << index << " ";
    }
    else {
        if(lefttree[index] == -1 && righttree[index] == -1 ) {
            cout << index << ":" << depth[index] << " ";
        }
    }
    if(lefttree[index] != -1) {
        preorder(lefttree[index],out);
    }
      if(righttree[index] != -1) {
        preorder(righttree[index],out);
    }
}
int main()
{
    int z,n;
    cin >> z;
    string in;

    while(z--)
    {
        cin >> n;
        for( int i = 0; i<n; i++)
        {
            cin >> lefttree[i];
            cin >> righttree[i];
        }
        cin >> in;
        depthroot(0,0);
        if(in=="POSTORDER") {
            postorder(0,0);
            cout << endl;
            postorder(0,1);
        }
        if(in=="INORDER") {
            inorder(0,0);
            cout << endl;
            inorder(0,1);
        }
        if(in=="PREORDER") {
            preorder(0,0);
            cout << endl;
            preorder(0,1);
        }
        cout << endl;
    }
    return 0;
}
