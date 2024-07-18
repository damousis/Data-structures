#ifndef HASHTABLE
#define HASHTABLE
#include <string>
using namespace std;

class HashTable
{
    protected:
        int sizeHASH;//πλήθος στοιχεςίων του HashTable
        int **hast; //πίνακας απο δείκτες που χρησιμοποιείται για να αποθηκέυσει τα στοιχεία του HashTable με βάση τo key του καθενός
        int *pl;//δυναμικός πίνακας που χρησιμοποιείται για να αποθηκεύσει το πλήθος των στοιχείων της κάθε θέσης
        int st;
    public:

        //const
        HashTable(); //κατασκευαστής

        //sizes
        //void SetSizeHash(int x);//συνάρτηση για να μεταβάλουμε το μέγεθος του HashTable
        void getsizeHashTable(float &c);//συνάρτηση που μας επιστρέφει το μέγεθος του HashTable

        //buidling
        int HashFunction(int key); //συνάρτηση που επιστρέφει το κλειδί για κάθε στοιχείο του HashTable
        void BuildHashTable(string inp,float &c);//συνάρτηση για την δημιουργεία του HashTable

        //others
        void searchHash(string p1,float &c);//συνάρτηση για την αναζήτηση στοιχείου στο HashΤable
        void insertHash(string p1,float &c);//συνάρτηση για την εισαγωγή στοιχείου στο HashΤable

};
#endif