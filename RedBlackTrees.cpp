#include <iostream>
#include <queue>

using namespace std;

struct Node{

    int firstNumber = -1;
    int secondNumber = -1;
    int thirdNumber = -1;

    char redOrBlackFirst;
    char redOrBlackSecond;
    char redOrBlackThird;

    struct Node *ptr1,*ptr2,*ptr3,*ptr4;

    Node(){

        ptr1 = ptr2 = ptr3 = ptr4 = nullptr;

    }

    Node(int firstNumber) {
        this->firstNumber = firstNumber;
        this->secondNumber = this->thirdNumber = -1;
        this->ptr1 = this->ptr2 = this->ptr3 = this->ptr4 = NULL;
    }

    // Constructor to initialize the node with one value and two child pointers.
    Node(int firstNumber, Node *ptr1, Node *ptr2) {
        this->firstNumber = firstNumber;
        this->ptr1 = ptr1;
        this->ptr2 = ptr2;

        // Everything else is NULL
        secondNumber = thirdNumber = -1;
        this->ptr3 = this->ptr4 = NULL;
    }

    Node(int firstNumber,int secondNumber,int thirdNumber, Node *ptr1, Node *ptr2, Node *ptr3, Node *ptr4) {
        this->firstNumber =firstNumber;
        this->secondNumber = secondNumber;
        this->thirdNumber = thirdNumber;
        this->ptr1 = ptr1;
        this->ptr2 = ptr2;
        this->ptr3 = ptr3;
        this->ptr4 = ptr4;
    }

    bool ContainsKey(int key) {
        if (this->thirdNumber == key) { return true; }
        if (this->secondNumber == key) { return true; }
        if (this->firstNumber == key) { return true; }
        return false;
    }

//    T *FindsKey(int key) {
//        if (C && C == key) { return C; }
//        if (B && secondNumber == key) { return B; }
//        if (A == key) { return A; }
//        return NULL;
//    }
//
//    void DeleteData() {
//        if (A) {
//            delete A;
//            A = NULL;
//        }
//        if (B) {
//            delete B;
//            B = NULL;
//        }
//        if (C) {
//            delete C;
//            C = NULL;
//        }
//    }

    // Returns true if all three data-value pointers, A, B, and C, are non-null,
    // false otherwise.
    bool IsFull() {
        return (firstNumber != -1 && secondNumber != -1 && thirdNumber != -1);
    }

    // Returns true if all 4 child pointers are null,
    // implying that the node is a leaf
    bool IsLeaf() {
        return (NULL == ptr1 && NULL == ptr2 && NULL == ptr3 && NULL == ptr4);
    }

    int ValueCount() {
        if (thirdNumber!=-1) { return 3; }
        else if (secondNumber!=-1) { return 2; }
        else if (firstNumber!= -1) { return 1; }

        // Should never come here
        return 0;
    }

    void setFirst(int value){
        this->firstNumber = value;
    }
    void setSecond(int value){
        this->secondNumber = value;
    }
    void setThird(int value){
        this->thirdNumber = value;
    }

};

Node* createTree(){
    Node * root = new Node();

    return root;
}

void printNode(Node* tmp){

    cout << "[";
    if(tmp->firstNumber != -1) cout << tmp->firstNumber;
    else cout << " ";
    cout << "|";
    if(tmp->secondNumber != -1) cout << tmp->secondNumber;
    else cout << " ";
    cout << "|";
    if(tmp->thirdNumber != -1) cout << tmp->thirdNumber;
    else cout << " ";
    cout << "]";

}

Node* Add(int key, Node* root){

    if(!root){

        root = new Node();
        root->setFirst(key);
        return root;

    }

    Node *tmp = root;
    Node* parent = tmp;

    while(tmp){

        //if(tmp->ContainsKey(key)){return root;}

        if(tmp->IsFull()){

            //parent has 1 key
            if(1 == parent->ValueCount()){
                if(parent->firstNumber < tmp->secondNumber){

                    parent->secondNumber = tmp->secondNumber;
                    parent->ptr2 = new Node(tmp->firstNumber, tmp->ptr1, tmp->ptr2);
                    parent->ptr3 = new Node(tmp->thirdNumber, tmp->ptr3, tmp->ptr4);
                } else {
                    parent->secondNumber = parent->firstNumber;
                    parent->ptr3 = parent->ptr2;
                    parent->firstNumber = tmp->secondNumber;
                    parent->ptr4 = new Node(tmp->firstNumber, tmp->ptr4, tmp->ptr2);
                    parent->ptr2 = new Node(tmp->thirdNumber, tmp->ptr3, tmp->ptr4);
                }

                delete tmp;

                if (key < parent->firstNumber)
                    tmp = parent->ptr4;
                else if (key < parent->secondNumber)
                    tmp = parent->ptr2;
                else if (key > parent->secondNumber)
                    tmp = parent->ptr3;
                else
                    return root; // duplicate

            } // end Case 1a

            //parent of node has 2 keys
            else if(2 == parent->ValueCount()){
                if (parent->secondNumber < tmp->secondNumber) {
                    parent->thirdNumber = tmp->secondNumber;
                    parent->ptr3 = new Node(tmp->firstNumber, tmp->ptr4, tmp->ptr2);
                    parent->ptr4 = new Node(tmp->thirdNumber, tmp->ptr3, tmp->ptr4);
                } else if (parent->firstNumber < tmp->secondNumber) {
                    parent->thirdNumber = parent->secondNumber;
                    parent->ptr4 = parent->ptr3;
                    parent->secondNumber = tmp->secondNumber;
                    parent->ptr2 = new Node(tmp->firstNumber, tmp->ptr1, tmp->ptr2);
                    parent->ptr3 = new Node(tmp->thirdNumber, tmp->ptr3, tmp->ptr4);
                } else {
                    parent->thirdNumber = parent->secondNumber;
                    parent->ptr4 = parent->ptr3;
                    parent->secondNumber = parent->firstNumber;
                    parent->ptr3 = parent->ptr2;
                    parent->firstNumber = tmp->secondNumber;
                    parent->ptr1 = new Node(tmp->firstNumber, tmp->ptr1, tmp->ptr2);
                    parent->ptr2 = new Node(tmp->thirdNumber, tmp->ptr3, tmp->ptr4);
                }

                delete tmp;

                if (key < parent->firstNumber)
                    tmp = parent->ptr1;
                else if (key < parent->secondNumber)
                    tmp = parent->ptr2;
                else if (key < parent->thirdNumber)
                    tmp = parent->ptr3;
                else if (key > parent->thirdNumber)
                    tmp = parent->ptr4;
                else
                    return root; // duplicate
            } // end of Case 1b

            else {
                root = new Node(tmp->secondNumber);
                root->ptr1 = new Node(tmp->firstNumber, tmp->ptr1, tmp->ptr2);
                root->ptr2 = new Node(tmp->thirdNumber, tmp->ptr3, tmp->ptr4);
                delete tmp;
                parent = root;
                if (key < root->firstNumber)
                    tmp = root->ptr1;
                else if (key > root->firstNumber)
                    tmp = root->ptr2;
                else
                    return root; // duplicate
            } // end Case 1c


        }//end case 1

        /*** CASE 2: Is it a leaf node ***/
        if (tmp->IsLeaf()) {
            // Case 2a: Has 1 key
            if (1 == tmp->ValueCount()) {
                if (key > tmp->firstNumber) {
                    tmp->secondNumber = key;
                    return root;
                } else if (key < tmp->firstNumber) {

                    tmp->secondNumber = tmp->firstNumber;
                    tmp->firstNumber = key;
                    return root;
                }
            } // end Case 2a

                // Case 2b: Has 2 keys
            else if (2 == tmp->ValueCount()) {
                if (key > tmp->secondNumber) {
                    tmp->thirdNumber = key;
                    return root;
                } else if (key > tmp->firstNumber) {
                    tmp->thirdNumber = tmp->secondNumber;
                    tmp->secondNumber = key;
                    return root;
                } else if (key < tmp->firstNumber) {
                    tmp->thirdNumber = tmp->secondNumber;
                    tmp->secondNumber = tmp->firstNumber;
                    tmp->firstNumber = key;
                    return root;
                }
            } // end Case 2b
        } // end Case 2

            /*** CASE 3: Not a leaf node ***/
        else {
            // Assigns previous pointer
            parent = tmp;

            // Case 3a: Has 1 key
            if (1 == tmp->ValueCount()) {
                if (key < tmp->firstNumber)
                    tmp = tmp->ptr1;
                else
                    tmp = tmp->ptr2;
            }

                // Case 3b: Has 2 keys
            else if (2 == tmp->ValueCount()) {
                if (key < tmp->firstNumber)
                    tmp = tmp->ptr1;
                else if (key < tmp->secondNumber)
                    tmp = tmp->ptr2;
                else
                    tmp = tmp->ptr3;
            }
        } // end Case 3


    }//end while

    // Should never get here!
    return root;
}

void Paint(Node* root){

    if(root->ValueCount() == 1){

        root->redOrBlackFirst = 'b';

    }
    if(root->ValueCount() == 2){

        root->redOrBlackFirst = 'b';
        root->redOrBlackSecond = 'r';

    }
    if(root->ValueCount() == 3){

        root->redOrBlackFirst = 'b';
        root->redOrBlackSecond = 'r';
        root->redOrBlackThird = 'b';

    }

    if(root->ptr1) Paint(root->ptr1);
    if(root->ptr2) Paint(root->ptr2);
    if(root->ptr3) Paint(root->ptr3);
    if(root->ptr4) Paint(root->ptr4);

}

bool FindKey(Node* root,int key){

    bool containsKey = root->ContainsKey(key);

    if(containsKey){

        return true;

    }
    else{

        if(root->thirdNumber != -1 && root->thirdNumber < key) return FindKey(root->ptr4,key);

        else if(root->secondNumber != -1 && root->secondNumber < key) return FindKey(root->ptr3,key);

        else if(root->firstNumber < key) return FindKey(root->ptr2,key);

        else return FindKey(root->ptr1,key);

    }

}

struct VectorNode{

    int Value;
    char RedOrBlack;

    VectorNode(int Value, char RedOrBlack){

        this->Value = Value;
        this->RedOrBlack = RedOrBlack;

    }

};

vector<VectorNode> nodeArray;

void Print234Tree(Node* root){

    struct Level{
        Node* node;
        int level;

        Level(Node* node, int level){

            this->node = node;
            this->level = level;

        }
    };

    queue<Level> queue;

    queue.push(Level(root,0));

    int maxLevel = 0;

    while(!queue.empty()){

        Level level = queue.front();
        queue.pop();

        Node* tmp = level.node;

        if(level.level > maxLevel){

            cout << endl;
            maxLevel = level.level;

        }

        printNode(tmp);
        cout << " ";


        //making vector for rb tree
        if(tmp->firstNumber != -1) nodeArray.push_back(VectorNode(tmp->firstNumber,tmp->redOrBlackFirst));
        if(tmp->secondNumber != -1) nodeArray.push_back(VectorNode(tmp->secondNumber,tmp->redOrBlackSecond));
        if(tmp->thirdNumber != -1) nodeArray.push_back(VectorNode(tmp->thirdNumber,tmp->redOrBlackThird));
        //end of making vector for rb tree


        if(tmp->ptr1) queue.push(Level(tmp->ptr1, level.level+1));
        if(tmp->ptr2) queue.push(Level(tmp->ptr2, level.level+1));
        if(tmp->ptr3) queue.push(Level(tmp->ptr3, level.level+1));
        if(tmp->ptr4) queue.push(Level(tmp->ptr4, level.level+1));

    }

    cout << endl;

}

int NumberOfAppearances(Node* root,int key){

    int counter = 0;

    struct Level{
        Node* node;
        int level;

        Level(Node* node, int level){

            this->node = node;
            this->level = level;

        }
    };

    queue<Level> queue;

    queue.push(Level(root,0));

    int maxLevel = 0;

    while(!queue.empty()){

        Level level = queue.front();
        queue.pop();

        Node* tmp = level.node;

        if(level.level > maxLevel){

            //cout << endl;
            maxLevel = level.level;

        }

        //printNode(tmp);
        if(tmp->thirdNumber == key) counter++;
        if(tmp->secondNumber == key) counter++;
        if(tmp->firstNumber == key) counter++;

        //cout << " ";


        //making vector for rb tree
//        if(tmp->firstNumber != -1) nodeArray.push_back(VectorNode(tmp->firstNumber,tmp->redOrBlackFirst));
//        if(tmp->secondNumber != -1) nodeArray.push_back(VectorNode(tmp->secondNumber,tmp->redOrBlackSecond));
//        if(tmp->thirdNumber != -1) nodeArray.push_back(VectorNode(tmp->thirdNumber,tmp->redOrBlackThird));
        //end of making vector for rb tree


        if(tmp->ptr1) queue.push(Level(tmp->ptr1, level.level+1));
        if(tmp->ptr2) queue.push(Level(tmp->ptr2, level.level+1));
        if(tmp->ptr3) queue.push(Level(tmp->ptr3, level.level+1));
        if(tmp->ptr4) queue.push(Level(tmp->ptr4, level.level+1));

    }

    //cout << endl;
    return counter;

}

// ##########################################
//         red black tree part
// ##########################################

struct RBNode{

    struct RBNode* left;
    struct RBNode* right;
    int height;
    int key;
    int numberOfKeys;
    int balance;

};

int getHeight(struct RBNode *node)
{
    int height;
    if (!node) height = 0;
    else height = node->height;

    return height;
}

int getBalance(struct RBNode *node)
{
    int balance;
    if (!node)
        balance = 0;
    else balance = getHeight(node->left) - getHeight(node->right);

    return balance;
}

void balanceTree(struct RBNode *root)
{
    if(root != NULL)
    {
        root->balance = getBalance(root);
        balanceTree(root->left);
        balanceTree(root->right);
    }
}

void setHeight(struct RBNode *root)
{
    if(root != NULL)
    {
        root->height = 1 + max(getHeight(root->left),
                               getHeight(root->right));
        setHeight(root->left);
        setHeight(root->right);
    }
}

struct RBNode *rightRotation(struct RBNode *x)
{
    struct RBNode *y = x->left;
    struct RBNode *tmp = y->right;
    y->right = x;
    x->left = tmp;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    return y;
}

struct RBNode *leftRotation(struct RBNode *x)
{
    struct RBNode *y = x->right;
    struct RBNode *tmp = y->left;
    y->left = x;
    x->right = tmp;
    x->height = max(getHeight(x->left), getHeight(x->right))+1;
    y->height = max(getHeight(y->left), getHeight(y->right))+1;
    return y;
}

struct RBNode* chooseTypeOfRotation(struct RBNode* tmp,int key){

    if (tmp->balance > 1 && key < tmp->left->key)
        tmp = rightRotation(tmp);

    if (tmp->balance < -1 && key > tmp->right->key)
        tmp =  leftRotation(tmp);

    if (tmp->balance > 1 && key > tmp->left->key)
    {
        tmp->left =  leftRotation(tmp->left);
        tmp =  rightRotation(tmp);
    }

    if (tmp->balance < -1 && key < tmp->right->key)
    {
        tmp->right = rightRotation(tmp->right);
        tmp = leftRotation(tmp);
    }

    return tmp;

}

struct RBNode* insert(struct RBNode* node, int key)
{
    if (node == NULL) { struct RBNode* node = (struct RBNode*)
                malloc(sizeof(struct RBNode));
        node->key   = key;
        node->left   = NULL;
        node->right  = NULL;
        node->height = 1;
        node->numberOfKeys = 1;
        node->balance = 0;
        return(node); }

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key >= node->key)
        node->right = insert(node->right, key);
    else {
        node->numberOfKeys++;
        return node;
    }


    balanceTree(node);
    setHeight(node);

    if(node->balance == 0) return node;
    else node = chooseTypeOfRotation(node,key);

    return node;

}


void print(struct RBNode *root, int space)
{
    int count= 10;

    if (root == NULL)
        return;

    space += count;

    print(root->right, space);

    printf("\n");
    for (int i = count; i < space; i++)
        printf(" ");
    printf("%d", root->key);
    for (auto i = nodeArray.begin(); i != nodeArray.end(); ++i){
        if(root->key == i->Value) cout << i->RedOrBlack;

    }
    cout << endl;

    //if(find(nodeArray.begin(),nodeArray.end(),root->key) != nodeArray.end())

    print(root->left, space);
}

bool Remove(int key,Node* root)
{
    if (!root) { return false; }

    // Implement the rest of this function for extra credit
    // Return false if the value is not present in the tree
    // Don't forget the rules for fusing nodes

    Node* tmp = root;
    Node* parent = root;

    int the_item = -1;
    Node* n_item = NULL;

    while (tmp)
    {
        // Case 1: If root and root has single key
        // and both descendents has single keys
        if (tmp == root && tmp->ValueCount() == 1 &&
            tmp->ptr1->ValueCount() == 1 &&
            tmp->ptr2->ValueCount() == 1)
        {
            // Set value for C and R & M2 pointers
            Node* right = tmp->ptr2;
            tmp->thirdNumber = right->firstNumber;
            tmp->ptr3 = right->ptr1;
            tmp->ptr4 = right->ptr2;
            delete right;

            // Set value for B
            tmp->thirdNumber = tmp->firstNumber;

            // Set value for A and L & M1 pointers
            Node* left = tmp->ptr1;
            tmp->firstNumber = left->firstNumber;
            tmp->ptr1 = left->ptr1;
            tmp->ptr2 = left->ptr2;
            delete left;

            parent = root;
            tmp = root;
        } // end Case 1

        // Cases 2: Transformations (Ensure the_item does not occur in a 2-node)
        // a) Transform each node encountered into a 3 node or a 4 node
        if (tmp->ValueCount() == 1)
        {
            // single key on L pointer
            if (parent->ptr1 == tmp)
            {
                // Parent has more than 1 key and M1 has 1 key, FUSE IT
                if (parent->ptr2->ValueCount() == 1)
                {
                    // set C and pointers R & M2
                    parent->ptr2->thirdNumber = parent->ptr2->firstNumber;
                    parent->ptr2->ptr4 = parent->ptr2->ptr2;
                    parent->ptr2->ptr3 = parent->ptr2->ptr1;
                    // set B
                    parent->ptr2->thirdNumber = parent->firstNumber;
                    // set A and pointer L & M1
                    parent->ptr2->firstNumber = tmp->firstNumber;
                    parent->ptr2->ptr1 = tmp->ptr1;
                    parent->ptr2->ptr2 = tmp->ptr2;

                    delete parent->ptr1;
                    parent->firstNumber = parent->thirdNumber;
                    parent->thirdNumber = parent->thirdNumber;
                    parent->thirdNumber = -1;
                    parent->ptr1 = parent->ptr2;
                    parent->ptr2 = parent->ptr3;
                    parent->ptr3 = parent->ptr4;
                    parent->ptr4 = NULL;

                    tmp = parent->ptr1;
                }

                    // Sibling has more than 1 key. Borrow
                else if (parent->ptr2->ValueCount() >= 2)
                {
                    // set B and pointer M2
                    tmp->thirdNumber = parent->firstNumber;
                    tmp->ptr3 = parent->ptr2->ptr1;

                    // set parent A
                    parent->firstNumber = parent->ptr2->firstNumber;

                    // set A, B, C of pointer M1 and its pointers
                    parent->ptr2->firstNumber = parent->ptr2->thirdNumber;
                    parent->ptr2->thirdNumber = parent->ptr2->thirdNumber;
                    parent->ptr2->thirdNumber = -1;
                    parent->ptr2->ptr1 = parent->ptr2->ptr2;
                    parent->ptr2->ptr2 = parent->ptr2->ptr3;
                    parent->ptr2->ptr3 = parent->ptr2->ptr4;
                    parent->ptr2->ptr4 = NULL;
                }
            } // end single key on L pointer

                // single key on M1 pointer
            else if (parent->ptr2 == tmp)
            {
                // L & M2 have single key, FUSE L & M1
                if (parent->ptr1->ValueCount() == 1 && parent->ptr3->ValueCount() == 1)
                {
                    // set C and pointers R & M2
                    tmp->thirdNumber = tmp->firstNumber;
                    tmp->ptr4 = tmp->ptr2;
                    tmp->ptr3 = tmp->ptr1;
                    // set B
                    tmp->thirdNumber = parent->firstNumber;
                    // set A and pointers L & M1
                    tmp->firstNumber = parent->ptr1->firstNumber;
                    tmp->ptr2 = parent->ptr1->ptr2;
                    tmp->ptr1 = parent->ptr1->ptr1;

                    delete parent->ptr1;
                    parent->firstNumber = parent->thirdNumber;
                    parent->thirdNumber = parent->thirdNumber;
                    parent->thirdNumber = -1;
                    parent->ptr1 = parent->ptr2;
                    parent->ptr2 = parent->ptr3;
                    parent->ptr3 = parent->ptr4;
                    parent->ptr4 = NULL;

                    // tmp already good
                }

                    // borrow from M2
                else if (parent->ptr1->ValueCount() < parent->ptr3->ValueCount())
                {
                    // set B and pointer M2
                    tmp->thirdNumber = parent->thirdNumber;
                    tmp->ptr3 = parent->ptr3->ptr1;

                    // set parent B
                    parent->thirdNumber = parent->ptr3->firstNumber;

                    // set M2 values and pointers
                    parent->ptr3->firstNumber = parent->ptr3->thirdNumber;
                    parent->ptr3->thirdNumber = parent->ptr3->thirdNumber;
                    parent->ptr3->thirdNumber = -1;
                    parent->ptr3->ptr1 = parent->ptr3->ptr2;
                    parent->ptr3->ptr2 = parent->ptr3->ptr3;
                    parent->ptr3->ptr3 = parent->ptr3->ptr4;
                    parent->ptr3->ptr4 = NULL;
                }

                    // borrow from L
                else
                {
                    // set B and pointer M1 & M2
                    tmp->thirdNumber = tmp->firstNumber;
                    tmp->ptr3 = tmp->ptr2;
                    tmp->ptr2 = tmp->ptr1;

                    // set A, parent A and pointer L
                    tmp->firstNumber = parent->firstNumber;
                    if (parent->ptr1->thirdNumber)
                    {
                        tmp->ptr1 = parent->ptr1->ptr4;
                        parent->firstNumber = parent->ptr1->thirdNumber;
                        parent->ptr1->thirdNumber = -1;
                        parent->ptr1->ptr4 = NULL;
                    }
                    else
                    {
                        tmp->ptr1 = parent->ptr1->ptr3;
                        parent->firstNumber = parent->ptr1->thirdNumber;
                        parent->ptr1->thirdNumber = -1;
                        parent->ptr1->ptr3 = NULL;
                    }
                }

            } // end single key on M1 pointer

                // single key on M2 pointer
            else if (parent->ptr3 == tmp)
            {
                // M1 & R have single key, FUSE M2 & R
                if (parent->ptr4 && parent->ptr2->ValueCount() == 1 &&
                    parent->ptr4->ValueCount() == 1)
                {
                    // set B
                    tmp->thirdNumber = parent->thirdNumber;
                    parent->thirdNumber = -1;

                    // set C and pointer M2 & R
                    tmp->thirdNumber = parent->ptr4->firstNumber;
                    tmp->ptr3 = parent->ptr4->ptr1;
                    tmp->ptr4 = parent->ptr4->ptr2;

                    delete parent->ptr4;
                    parent->ptr4 = NULL;

                    // tmp is good
                }

                    // borrow from R
                else if (parent->ptr4 &&
                         parent->ptr4->ValueCount() >=  parent->ptr2->ValueCount())
                {
                    // set B and pointer M2
                    tmp->thirdNumber = parent->thirdNumber;
                    tmp->ptr3 = parent->ptr4->ptr1;

                    // set parent C
                    parent->thirdNumber = parent->ptr4->firstNumber;

                    // set R values and pointers
                    parent->ptr4->firstNumber = parent->ptr4->thirdNumber;
                    parent->ptr4->thirdNumber = parent->ptr4->thirdNumber;
                    parent->ptr4->thirdNumber = -1;
                    parent->ptr4->ptr1 = parent->ptr4->ptr2;
                    parent->ptr4->ptr2 = parent->ptr4->ptr3;
                    parent->ptr4->ptr3 = parent->ptr4->ptr4;
                    parent->ptr4->ptr4 = NULL;

                    // tmp is good
                }

                    // borrow from M1
                else
                {
                    // set B and pointer M1 & M2
                    tmp->thirdNumber = tmp->firstNumber;
                    tmp->ptr3 = tmp->ptr2;
                    tmp->ptr2 = tmp->ptr1;

                    // set A, parent B and pointer L
                    tmp->firstNumber = parent->thirdNumber;
                    if (parent->ptr2->thirdNumber)
                    {
                        tmp->ptr1 = parent->ptr2->ptr4;
                        parent->thirdNumber = parent->ptr2->thirdNumber;
                        parent->ptr2->ptr4 = NULL;
                        parent->ptr2->thirdNumber = -1;
                    }
                    else
                    {
                        tmp->ptr1 = parent->ptr2->ptr3;
                        parent->thirdNumber = parent->ptr2->thirdNumber;
                        parent->ptr2->ptr3 = NULL;
                        parent->ptr2->thirdNumber = -1;
                    }
                }

            } // end single key on M2 pointer

                // single key on R pointer
            else if (parent->ptr4 == tmp)
            {
                // M2 has a single key, FUSE M2 & R
                if (parent->ptr3->ValueCount() == 1)
                {
                    // set B
                    parent->ptr3->thirdNumber = parent->thirdNumber;
                    parent->thirdNumber = -1;

                    // set C and pointer M2 & R
                    parent->ptr3->thirdNumber = tmp->firstNumber;
                    parent->ptr3->ptr3 = tmp->ptr1;
                    parent->ptr3->ptr4 = tmp->ptr2;

                    tmp->firstNumber = -1;
                    tmp->ptr1 = NULL;
                    tmp->ptr2 = NULL;
                    delete parent->ptr4;

                    tmp = parent->ptr3;
                }

                    // borrow from M2
                else if (parent->ptr3->ValueCount() >= 2)
                {
                    // set B and pointer M1 & M2
                    tmp->thirdNumber = tmp->firstNumber;
                    tmp->ptr3 = tmp->ptr2;
                    tmp->ptr2 = tmp->ptr1;

                    // set A, parent C and pointer L
                    tmp->firstNumber = parent->thirdNumber;
                    if (parent->ptr3->thirdNumber)
                    {
                        tmp->ptr1 = parent->ptr3->ptr4;
                        parent->thirdNumber = parent->ptr3->thirdNumber;
                        parent->ptr3->ptr4 = NULL;
                        parent->ptr3->thirdNumber = -1;
                    }
                    else
                    {
                        tmp->ptr1 = parent->ptr3->ptr3;
                        parent->thirdNumber = parent->ptr3->thirdNumber;
                        parent->ptr3->ptr3 = NULL;
                        parent->ptr3->thirdNumber = -1;
                    }
                }

            } // end single key on R pointer
        }

        // Case 3: Item hasn't been found
        // but this node contains key
        if (!the_item && tmp->ContainsKey(key) && !tmp->IsLeaf())
        {
            parent = tmp;
            n_item = tmp;      // points to the node where the key is found
            if (tmp->thirdNumber && key == tmp->thirdNumber)
            {
                the_item = tmp->thirdNumber;
                tmp = tmp->ptr4;  // go to right of key
            }
            else if (tmp->thirdNumber && key == tmp->thirdNumber)
            {
                the_item = tmp->thirdNumber;
                tmp = tmp->ptr3; // go to right of key
            }
            else
            {
                the_item = tmp->firstNumber;
                tmp = tmp->ptr2; // go to right of key
            }
        } // Case 3

            // Case 4: Item already found
            // and node contains key (assume its a leaf)
            // The key here is the inorder successor key
        else if ((the_item && tmp->ContainsKey(key)) ||
                 (tmp->ContainsKey(key) && tmp->IsLeaf()))
        {
            while (1)
            {
                // # of keys greater than or equal to 2 keys
                // delete the key
                if (tmp->ValueCount() >= 2)
                {
                    // key is C
                    if (tmp->thirdNumber && key == tmp->thirdNumber)
                    {
                        tmp->thirdNumber = -1;
                        //tmp->thirdNumber = NULL;
                    }
                        // key is B
                    else if (tmp->thirdNumber && key == tmp->thirdNumber)
                    {
                        tmp->thirdNumber  = -1;
                        tmp->thirdNumber = tmp->thirdNumber;
                        //tmp->thirdNumber = NULL;
                    }
                        // key is A
                    else // <----- PROBLEM MIGHT BE HERE
                    {
                        tmp->firstNumber = -1;
                        tmp->firstNumber = tmp->thirdNumber;
                        tmp->thirdNumber = tmp->thirdNumber;
                        tmp->thirdNumber = -1;
                    }
                    return true;
                }

                    // key on R pointer
                else if (parent->ptr4 && parent->ptr4 == tmp)
                {
                    // M2 & R has single keys. FUSE IT
                    if (parent->ptr3->ValueCount() == 1 && parent->ptr4->ValueCount() == 1)
                    {
                        parent->ptr3->thirdNumber = parent->thirdNumber;
                        parent->ptr3->thirdNumber = tmp->firstNumber;
                        tmp->firstNumber = -1;
                        delete parent->ptr4;
                        parent->ptr4 = NULL;
                        parent->thirdNumber = -1;
                        tmp = parent->ptr3;
                    }
                        // R has one key and M2 has more than one key
                    else
                    {
                        // borrow from parent C
                        tmp->thirdNumber = tmp->firstNumber;
                        tmp->firstNumber = parent->thirdNumber;
                        // parent C borrow C from M2
                        if (parent->ptr3->thirdNumber != -1)
                        {
                            parent->thirdNumber = parent->ptr3->thirdNumber;
                            parent->ptr3->thirdNumber = -1;
                        }
                            // parent C borrow B from M2
                        else
                        {
                            parent->thirdNumber = parent->ptr3->thirdNumber;
                            parent->ptr3->thirdNumber = -1;
                        }
                    }
                }

                    // key on M2 pointer
                else if (parent->ptr3 && parent->ptr3 == tmp)
                {
                    // M1, M2 & R has single keys. FUSE M2 & R
                    if ((parent->ptr2->ValueCount() == 1 &&
                         parent->ptr3->ValueCount() == 1 && !parent->thirdNumber) ||
                        (parent->ptr4 && parent->ptr2->ValueCount() == 1 &&
                         parent->ptr3->ValueCount() == 1 && parent->ptr4->ValueCount() == 1))
                    {
                        tmp->thirdNumber = parent->thirdNumber;
                        tmp->thirdNumber = parent->ptr4->firstNumber;
                        parent->ptr4->firstNumber = -1;
                        delete parent->ptr4;
                        parent->ptr4 = NULL;
                        parent->thirdNumber = -1;
                    }
                        // M2 has one key and R has more keys than M1
                    else if (parent->ptr4 &&
                             parent->ptr4->ValueCount() >= parent->ptr2->ValueCount())
                    {
                        // borrow from parent C
                        tmp->thirdNumber = parent->thirdNumber;
                        // parent C borrow A from R
                        parent->thirdNumber = parent->ptr4->firstNumber;
                        parent->ptr4->firstNumber = parent->ptr4->thirdNumber;
                        parent->ptr4->thirdNumber = parent->ptr4->thirdNumber;
                        parent->ptr4->thirdNumber = -1;
                    }
                        // M2 has one key and M1 has more keys than R
                    else
                    {
                        // borrow from parent B
                        tmp->thirdNumber = tmp->firstNumber;
                        tmp->firstNumber = parent->thirdNumber;
                        // parent B borrow C from M1
                        if (parent->ptr2->thirdNumber != -1)
                        {
                            parent->thirdNumber = parent->ptr2->thirdNumber;
                            parent->ptr2->thirdNumber = -1;
                        }
                            // parent B borrow B from M1
                        else
                        {
                            parent->thirdNumber = parent->ptr2->thirdNumber;
                            parent->ptr2->thirdNumber = -1;
                        }
                    }
                }

                    // key on M1 pointer
                else if (parent->ptr2 && parent->ptr2 == tmp)
                {
                    // L, M1, & M2 has single keys. FUSE L & M1
                    if (parent->ptr1->ValueCount() == 1 &&
                        parent->ptr2->ValueCount() == 1 &&
                        parent->ptr3->ValueCount() == 1)
                    {
                        tmp->thirdNumber = tmp->firstNumber;
                        tmp->thirdNumber = parent->firstNumber;
                        tmp->firstNumber = parent->ptr1->firstNumber;
                        parent->ptr1->firstNumber = -1;
                        delete parent->ptr1;
                        parent->firstNumber = parent->thirdNumber;
                        parent->thirdNumber = parent->thirdNumber;
                        parent->ptr1 = parent->ptr2;
                        parent->ptr2 = parent->ptr3;
                        parent->ptr3 = parent->ptr4;
                        parent->ptr4 = NULL;
                    }
                        // M1 has one key and M2 has more keys than L
                    else if (parent->ptr1->ValueCount() < parent->ptr3->ValueCount())
                    {
                        // borrow from parent B
                        tmp->thirdNumber = parent->thirdNumber;
                        // parent B borrow A from M2
                        parent->thirdNumber = parent->ptr3->firstNumber;
                        parent->ptr3->firstNumber = parent->ptr3->thirdNumber;
                        parent->ptr3->thirdNumber = parent->ptr3->thirdNumber;
                        parent->ptr3->thirdNumber = -1;
                    }
                        // M1 has one key and L has more keys than M2
                    else
                    {
                        // borrow from parent A
                        tmp->thirdNumber = tmp->firstNumber;
                        tmp->firstNumber = parent->firstNumber;
                        // parent A borrow C from L
                        if (parent->ptr1->thirdNumber != -1)
                        {
                            parent->firstNumber = parent->ptr1->thirdNumber;
                            parent->ptr1->thirdNumber = -1;
                        }
                            // parent A borrow B from L
                        else
                        {
                            parent->firstNumber = parent->ptr1->thirdNumber;
                            parent->ptr1->thirdNumber = -1;
                        }
                    }
                }

                    // key on L pointer
                else
                {
                    // L, M1 has single keys. FUSE IT!
                    if (parent->ptr1->ValueCount() == 1 && parent->ptr2->ValueCount() == 1)
                    {
                        parent->ptr2->thirdNumber = parent->ptr2->firstNumber;
                        parent->ptr2->thirdNumber = parent->firstNumber;
                        parent->ptr2->firstNumber = parent->ptr1->firstNumber;
                        parent->ptr1->firstNumber = -1;
                        delete parent->ptr1;
                        parent->firstNumber = parent->thirdNumber;
                        parent->thirdNumber = parent->thirdNumber;
                        parent->ptr1 = parent->ptr2;
                        parent->ptr2 = parent->ptr3;
                        parent->ptr3 = parent->ptr4;
                        parent->ptr4 = NULL;

                        tmp = parent->ptr2;
                    }
                        // L has one key, borrow from M1
                    else
                    {
                        // borrow from parent A
                        tmp->thirdNumber = parent->firstNumber;
                        // parent A borrow A from M1
                        parent->firstNumber = parent->ptr2->firstNumber;
                        parent->ptr2->firstNumber = parent->ptr2->thirdNumber;
                        parent->ptr2->thirdNumber = parent->ptr2->thirdNumber;
                        parent->ptr2->thirdNumber = -1;
                    }
                }
            } // end while (1)
        } // end Case 4

        // Case: Item not found yet so continue looking
        if (!the_item)
        {
            parent = tmp;
            if (tmp->thirdNumber != -1 && key > tmp->thirdNumber)      { tmp = tmp->ptr4;  }
            else if (tmp->thirdNumber != -1 && key > tmp->thirdNumber) { tmp = tmp->ptr3; }
            else if (key > tmp->firstNumber)             { tmp = tmp->ptr2; }
            else                                           { tmp = tmp->ptr1;  }
        }
            // Case: Item found. Look for inorder successor
        else
        {
            if (tmp->ptr1 == NULL) // tmp key A is the inorder successor
            {
                if (n_item->firstNumber == the_item)
                {
                    n_item->firstNumber = -1;
                    n_item->firstNumber = (tmp->firstNumber);
                }
                else if ( n_item->thirdNumber == the_item)
                {
                    n_item->thirdNumber = -1;
                    n_item->thirdNumber = ((tmp->firstNumber));
                }
                else
                {
                    n_item->thirdNumber = -1;
                    n_item->thirdNumber = ((tmp->firstNumber));
                }

                key = tmp->firstNumber;
            }
            else
            {
                parent = tmp;
                tmp = tmp->ptr1;   // go to left of key
            }
        }
    }

    return false;
}

int main() {
    cout << "Hello, World!" << endl;

    Node* root = createTree();
    root->firstNumber = 0;

    root = Add(3,root);
    root = Add(4,root);
    root = Add(5,root);
    root = Add(6,root);
    root = Add(7,root);
    root = Add(8,root);
    root = Add(9,root);
    root = Add(10,root);
    root = Add(11,root);
    //root = Add(9,root);
    Paint(root);

    if( FindKey(root, 4) ) cout << "true" << endl;

    //printNode(root);

    cout << endl;

    Print234Tree(root);

    cout << "Output of begin and end: ";

    RBNode* rbNode = NULL;

    for (auto i = nodeArray.begin(); i != nodeArray.end(); ++i)
        rbNode = insert(rbNode,i->Value);

    cout << endl;

    print(rbNode,0);

    cout << endl << NumberOfAppearances(root,9) << endl;

    Remove(4,root);
    //Remove(5,root);
    //Remove(3,root);
    //Add(4,root);

    Print234Tree(root);

    return 0;
}
