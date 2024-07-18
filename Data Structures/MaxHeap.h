#ifndef MAXH
#define MAXH
#include <string>

using namespace std;

class MaxHeap
{
    protected:
        int *maxhe;//δημιουργούμε ένα πίνακα που θα τον μεταβάλουμε ανάλογα με την είσοδο
        int sizeMAX;//μέγεθος του σωρού
    public:
        //κατασκευαστής 
        MaxHeap();

        //setter getter 
        void SetSizeMax(int k); // συνάρτηση για να μεταβάλουμε το μέγεθος του MaxHeap
        void getsizeMax(float &c);//συνάρτηση που μας επιστρέφει το μέγεθος του MaxHeap

        //συναρτήσεις δημιουργίας του σωρού
        int parent(int k);
        int left(int k);
        int right(int k);

        void BuildMaxHeap(string inp,float &c);//συνάρτηση για την δημιουργία του MaxHeap
        void MaxHeapify(int i);//βοηθητική συνάρτηση για την δημιουργεία του MaxHeap

        //υπόλοιπες συναρτήσεις
        void findMax(float &c); //συνάρτηση για εύρεση μεγίστου στοιχείου στο MaxHeap 
        void insertMax(string p1,float &c);//συνάρτηση για την εισαγωγή στοιχείου στο MaxHeap);
        void deleteMax(float &c); //συνάρτηση για την διαγραφή του μέγισοτυ στοιχείου στο MaxHeap
};
#endif