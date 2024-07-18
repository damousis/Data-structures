#include <iostream>
#include <cstring>
#include <fstream>
#include "AvlTree.h"
#include <ctime>
#include <iomanip>
#include<cstdio>
#include<sstream>
#include<algorithm>
using namespace std;

void AvlTree::BuildAvlTree(string inp,float & c)
{
    clock_t c1,c2;
    c1 = clock();
    ifstream f;
    f.open(inp);;//άνοιγμα αρχείου εισόδου
    ofstream o;
    o.open("output.txt",ios::out|ios::app);//άνοιγμα αρχείου εξόδου
    string sup;//βοηθητική μεταβλητή για την μετρήσουμε το πλήθος των στοιχείων του αρχείου εισόδου
    int s=0;//μετρητής μας
    if (f.is_open())
    {
        while(getline(f,sup))
            s+=1;
        SetSizeAvl(s);//καθορισμός μεγέθους του Avl Tree
    }
    f.close();//κλείσιμο αρχείου εισόδου μετά την πρώτη ανάγνωση του
    f.open(inp);//το ξανα ανοίγουμε για να διαβάσουμε τα δεδομένα του αρχείου εισόδου
    while(getline(f,sup))
        root =insert(root,stoi(sup));//χρησιμοποιούμε την βοηθητική μεταβλητή για να τοποθετήσουμε την λάθε μεταβλητή στην σωστή θέση ανάλογα με την τιμή της

    c2 = clock();
    c += float(c2 - c1) / CLOCKS_PER_SEC;
    inOrder(root,1,-1,c2-c1);//στο τέλος εμφανίζουμε το δένδρο μας
   // o<<endl;
    o.close();//κλείσιμο αρχείου εξόδου
}

//sizes
void AvlTree::SetSizeAvl(int x){sizeAVL=x;}//μεταβάλει το μέγεθος του Αvl Tree

void AvlTree::GetSizeAvlTree(float & c)
{
    clock_t c1,c2;
    c1 = clock();
    ofstream o;
    o.open("output.txt",ios::out|ios::app);//άνοιγμα αρχείου εξόδου
    o<<"The size of the AvlTree is: "<<sizeAVL;//εμφάνιση του μεγέθους του Αvl Tree
    c2 = clock();
    c += float(c2 - c1) / CLOCKS_PER_SEC;
    o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" seconds to return the size of the Avl tree)"<<endl;
    for(int i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();//κλείσιμο αρχείου μετά την εγγραφή
}

//ohers
void AvlTree::FindMinAvlTree(float & c)
{
    clock_t c1,c2;
    c1 = clock();
    ofstream o;
    o.open("output.txt",ios::out|ios::app);
    Node *help = root;//βοηθητική μεταβλητή που δείχνει στην ρίζα του δένδρου
    while(help->left!=nullptr)//συνεχώς πηγαίνουμε στο αριστερό παιδί του κάθε κόμβου μέχρι να μην υπάρχει άλλο
        help=help ->left;//τοποθετούμε στον βοηθητικό κόμβο το αριστερό παιδί του κόμβου που βρισκόμαστε

    c2 = clock();
    c += float(c2 - c1) / CLOCKS_PER_SEC;
    o<<"The minimum value in the avl tree is: "<<help->data;
    o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" seconds to find the minimum of the Avl tree)"<<endl;
    for(int i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();
}

void AvlTree::SearchAvlTree(string p1,float & c)
{
    clock_t c1,c2;
    c1 = clock();
    int i,n;
    n= stoi(p1);//μετατροπή του ορίσματος απο string σε integer
    ofstream o;
    o.open("output.txt",ios::out|ios::app);
    Node * help=root;//βοηθητική μεταβλητή που δείχνει στην ρίζα του δένδρου
    while(help !=nullptr)//ψάχνουμε μέχρι να φτάσουμε στο κενό
    {
        if(help->data==n)//αν ο κόμβος που βρισκόμαστε είναι αυτός που αναζητούμε
        {
            c2 = clock();
            o<<"SUCCESS! The number: "<<n<<" is in the avl tree!";
            o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" seconds to find the number in the Avl tree)"<<endl;
            for(i=0;i<20;i++)
                o<<"----";
            o<<endl;
            return;
        }
        else if(help->data > n)// Αν η τιμή του κόμβου που βρισκόμαστε  είναι μεγαλύτερη από αυτή που αναζητούμε τότε δίνουμε το αριστερό παιδί του κόμβου αυτού στη βοηθητική μεταβλητή
            help = help->left;
        else//αλλίως δίνουμε το δεξί παιδί του κόμβου που βρισκόμαστε αφοπύ οι τιμές των κόμβων δεξιά του είναι μεγαλύτερες απο την  τιμή αυτού
            help = help->right;
    }

    c2 = clock();
    c += float(c2 - c1) / CLOCKS_PER_SEC;
     o<<"FAILURE! The number: "<<n<<" is not in the avl tree!";
    o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" seconds to find out the number was not in the Avl tree)"<<endl;
    for(i=0;i<20;i++)
        o<<"----";
    o<<endl;
    return;
}

void AvlTree::insertAvlTree(string p1,float & c)
{
    clock_t c1,c2;
    c1 = clock();
    int n;
    ofstream o;
    o.open("output.txt",ios::app);

    sizeAVL +=1;
    n=stoi(p1);//μετατροπή του ορίσματος απο string σε integer
    root = insert(root,n);//χρησιμοποιούμε την μέθοδο insert για να τοποθετήσουμε την τιμή στην σωστή θέση ανάλογα με την τιμή της
    c2 = clock();
    c += float(c2 - c1) / CLOCKS_PER_SEC;
    inOrder(root,2,n,c2-c1);//εμφανίζουμε το νέο δένδρο
    o.close();


}

void AvlTree::deleteAvl(string p1,float & c)
{
    clock_t c1,c2; // μεταβλητές για τον χρόνο
    c1 = clock();
    int n,pl=0;
    n = stoi(p1);
    root = deleteNode(root,n,c,pl); //καλούμε την βοηθητική συνάρτηση
    c2 = clock();
    sizeAVL -=1; //μειώνουμε το μέγεθος
    c+=float(c2-c1)/CLOCKS_PER_SEC;
    inOrder(root,pl,n,c);//εμφανίζουμε το νέο δένδρο	
}

int AvlTree:: height(Node* node) {
    if (node == nullptr)//αν το δέδνρο είναι άδειο επιστρέφει 0
        return 0;
    return node->height;//αν δεν είναι 0 επιστρέφει το ύψος του κόμβου
}

int AvlTree:: max(int a, int b) 
{
    if(a>=b) //αν το πρώτο όρισμα είναι μεγαλύτερο το επιστρέφει
        return a;
    else
        return b;//αλλιώς επιστρέφει το 2ο
}

Node* AvlTree:: newNode(int data) 
{
    Node* node = new Node(); //δημιουργείς καινούριο κόμβο
    node->data = data; //αποθηκεύει την τιμή του κόμβου που δίνεται ως όρισμα
    
    node->left = nullptr;//αρχικοποιεί το αριστερό παιδί του με το κενό
    node->right = nullptr;//αρχικοποιεί το δεξί παιδί του με το κενό
    node->height = 1;//αρχικοποιεί το ύψος του κόμβοπυ εμ το 1
    return node; //επιστρέφει τον νέο κόμβο
}

Node*  AvlTree::rightRotate(Node* y) 
{
    Node* x = y->left;//δημιουργείς καινούριο κόμβο που θα είναι το αριστερό παιδί του κόμβου που δίνεται ως όρισμα
    Node* T2 = x->right; //δημιουργείς καινούριο κόμβο που θα αποθηκεύει το δεξί παιδί του κόμβου που δημιουργήσαμε επάνω

    x->right = y; //μεταβάλεις το δεξί παιδί του κόμβου που δημιουργήσαμε με τον κόμβο που δίνεται ως όρισμα
    y->left = T2;//μεταβάλεις το αριστερό παιδί του κόμβου που δίνεται ως όρσιμα με το δεξί παιδί του κόμβου που δημιουργήσαμε

    y->height = max(height(y->left), height(y->right)) + 1;//αλλάζεις το ύψος του κόμβου που δίνεται ως όρισμα 
    x->height = max(height(x->left), height(x->right)) + 1;//αλλάζεις το ύψος του κόμβου που δημιουργήσαμε

    return x;
}

Node* AvlTree:: leftRotate(Node* x) 
{
    
    Node* y = x->right;//δημιουργείς καινούριο κόμβο που θα είναι το δεξί παιδί του κόμβου που δίνεται ως όρισμα
    Node* T2 = y->left;//δημιουργείς καινούριο κόμβο που θα αποθηκεύει το αριστερό παιδί του κόμβου που δημιουργήσαμε επάνω

    y->left = x;//μεταβάλεις το αριστερό παιδί του κόμβου που δημιουργήσαμε με τον κόμβο που δίνεται ως όρισμα
    x->right = T2;//μεταβάλεις το δεξί παιδί του κόμβου που δίνεται ως όρσιμα με το δεξί παιδί του κόμβου που δημιουργήσαμε

    x->height = max(height(x->left), height(x->right)) + 1;//αλλάζεις το ύψος του κόμβου που δίνεται ως όρισμα 
    y->height = max(height(y->left), height(y->right)) + 1;//αλλάζεις το ύψος του κόμβου που δημιουργήσαμε

    return y;//επιστρέφεις τον κόμβο που δημιουργήσαμε
}

int AvlTree:: getBalance(Node* node) 
{
    if (node == nullptr)//αν το δένδρο είναι κενό επιστρέφεις το 0
        return 0;
    return height(node->left) - height(node->right);//αλλιώς επιστρέφεις το balance factor του κόμβου που δίνεται ωςς όρισμα
}

Node*  AvlTree:: insert(Node* node, int data) 
{
    if (node == nullptr) //αν το δένδρο είναι κενό δημιουργηεί απλά ένα νέο κόμβο
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data); // Εισαγωγή στο αριστερό υποδέντρο αν η τιμή είναι μικρότερη από την τιμή του αρχικού κόμβου
    else if (data > node->data)
        node->right = insert(node->right, data);// Εισαγωγή στο δεξί υποδέντρο αν η τιμή είναι μεγαλύτερη από την τιμή του αρχικού κόμβου
    else
    {
         sizeAVL -= 1;
        return node;// Η τιμή υπάρχει ήδη στο δέντρο, επιστρέφουμε τον κόμβο που υπάρχει ήδη
    }

    node->height = 1 + max(height(node->left), height(node->right));// Υπολογισμός του ύψους του κόμβου που βρισκόμαστε

    int balance = getBalance(node);//υπολογίζουμε το balance factor του κόμβου που βρίσκομαστε

    //ελέγχουμε αν υπάρχει κάποια κατάσταση ανισορροπίας και τότε εκτελούμε τις κατάλληλες εντολές για να μην υπάρχει η ανισορροπία
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;//επιστροφή του κόμβου που βρισκόμαστε
}

void AvlTree::inOrder(Node* root, int ap, int num,float k) 
{
    ofstream o;
    o.open("output.txt", ios::out | ios::app);  // Open the file to append the message
    if(ap==1)//ελέγχουμε αν είναι η πρώτη εκτέλεση της συνάρτησης για να εμφανίσουμε το αρχικό μήνυμα
        o << "The AvlTree looks like this using inorder method: ";
    else if(ap==2)//αλλιώς εμφανίζουμε το νέο δένδρο αφού προστέθηκε στοιχείο
        o<<"The number: "<<num<<" was successfully added and the new Avl tree is: ";//εμφανίζουμε τα στοιχεία στο αρχείο
    else if(ap==4)
        o<<"The number: "<<num<<" was successfully deleted and the new Avl tree is:";
    else
    {
        o<<"The number: "<<num<<" was not found in the Avl tree:";
        sizeAVL +=1;//προσθέτουμε το 1 για να μην έχουμε θέμα με το μέγεθος αφού δεν βρέθηκε το στοιχείο για να πρέπει να μειωθεί το μέγεθος
    }

    printInOrder(root, o);  // εμφανίζει τις τιμές του δένδρου
    if(ap==1)
        o<<" (it took "<<fixed << setprecision(6) <<float(k)/CLOCKS_PER_SEC<<" seconds to build the AVL tree)"<<endl;
    else if(ap==2)
         o<<" (it took "<<fixed << setprecision(6) <<float(k)/CLOCKS_PER_SEC<<" seconds to add the new number in the AVL tree)"<<endl;
    else if(ap==4)
         o<<" (it took "<<fixed << setprecision(6) <<float(k)/CLOCKS_PER_SEC<<" seconds to delete the number from the AVL tree)"<<endl;
    else
    {
        o<<" (it took "<<fixed << setprecision(6) <<float(k)/CLOCKS_PER_SEC<<" find out the number was not in the AVL tree)"<<endl;
        for(int i = 0; i < 20; i++)
            o << "----";
        o<<endl;
        return;
    }

    for(int i = 0; i < 20; i++)
        o << "----";
    o<<endl;
    o.close();
}

void AvlTree::printInOrder(Node* root, ofstream& o)
{
    if (root != nullptr) //ελέχγει αν το δένδρο δεν είναι κενό
    {
        printInOrder(root->left, o);//εμφανίζει αναδρομικά πρώτα τα στοιχεία με την μικρότερη τιμή πηγαίνοντα στο αριστερό παιδί του κάθε κόμβου
        o << root->data << " ";
        printInOrder(root->right, o);//και στην συνέχεια εμφανίζει τα στοιχεία με την συνεχώς μεγαλύτερη τιμή(πάλι αναδρομικά)
    }
}

Node * AvlTree::deleteNode(Node* root, int n,float &c,int & pl)
{
    if (root == nullptr)
    {    
        pl =3;
        return root;
    }

    pl=4;
    if(n<root->data)
        root->left = deleteNode(root->left,n,c,pl);
    else if(n>root->data)
    {
        root->right = deleteNode(root->right,n,c,pl);
    }
    else
    {
        if ((root->left == nullptr) || (root->right == nullptr)) 
        {
            Node* temp = root->left ? root->left : root->right;
            if(temp==nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
                
        }
        else
        {
            Node * temp = minVal(root->right);
            root->data = temp -> data;
            root -> right = deleteNode(root->right,temp->data,c,pl);
            
        }
    }
    if (root == nullptr) 
    {
            return root;
    }

        // STEP 2: Update the height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

        // STEP 3: Get the balance factor of this node (to check whether this node became unbalanced)
    int balance = getBalance(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) 
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

        // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

        // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) 
    {
        root->right = rightRotate(root->right);
         return leftRotate(root);
    }

    return root;
}

Node* AvlTree::minVal(Node* node) 
{
    Node* current = node;

    // Loop down to find the leftmost leaf
    while (current->left != nullptr)
        current = current->left;

    return current;
}
