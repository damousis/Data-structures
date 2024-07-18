#ifndef AVLTREE
#define AVLTREE

#include <string>
#define pow2(n) (1 << (n))
using namespace std;


struct Node //δημιουργούμε ενα struct για κάθε κόμβο του Avl Tree
{
    int data; //η τιμή του κάθε κόμβου
    Node* left; // δείκτης κόμβου που δείχνει στο αριστερό παιδί του κόμβου
    Node* right;//δείκτης κόμβου που δείχνει στο δεξί παιδί του κόμβου
    int height; //το ύψος που βρίσκεται ο κόμβος
};

class AvlTree
{
      protected:
        Node *root=nullptr; 
        int sizeAVL;//μέγεθος του δένδρου
      public:
          //constructor
          void BuildAvlTree(string inp,float & c); //συνάρτηση για την δημιουργία του Avl Tree

          //sizes
          void SetSizeAvl(int x);//συνάρτηση για να μεταβάλουμε το μέγεθος του Avl Tree
          void GetSizeAvlTree(float & c);//συνάρτηση που μας επιστρέφει το πλήθος στοιχείων του Avl Tree

          //others
          void FindMinAvlTree(float & c); //συνάρτηση για εύρεση του ελάχιστου στοιχείου στο Avl Tree
  //ΠΡΕΠΕΙ ΝΑ ΑΛΛΑΞΕΙ ΤΙ ΕΠΙΣΤΡΦΕΙ        
          void SearchAvlTree(string p1,float & c);//συνάρτηση για την αναζήτηση στοιχείου στο Avl Tree
          void insertAvlTree(string p1,float & c);//συνάρτηση για την εισαγωγή στοιχείου στο Avl Tree
          void deleteAvl(string p1,float & c);
            
 
          //helpers
          int height(Node* node) ;//επιστρέφει το ύψος του κόμβου
          int  max(int a, int b); //επιστρέφει το μεγαλύτερο στοιχείο απο τα ορίσματα που δέχεται
          Node * newNode(int data);
          Node * rightRotate(Node* y);
          Node * leftRotate(Node* x);
          int getBalance(Node* node);
          Node * insert(Node* node, int data);
          void inOrder(Node* root,int x,int num,float k);
          void printInOrder(Node* root,ofstream &o);
          Node * deleteNode(Node* root,int n, float &c,int &p);
          Node *minVal(Node * node);

};
#endif