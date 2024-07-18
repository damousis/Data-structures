#ifndef MINH
#define MINH
#include <string>

using namespace std;


class MinHeap
{
    protected:
        int *minhe;//δημιουργούμε ένα πίνακα που θα τον μεταβάλουμε ανάλογα με την είσοδο
        int sizeMIN;//μέγεθος του σωρού 
    public:
        //κατασκευαστής
        MinHeap();

        //setter getter
        void SetSizeMin(int ns); // συνάρτηση για να μεταβάλουμε το μέγεθος του MinHeap
        void getsizeMin(float &c);//συνάρτηση που μας επιστρέφει το μέγεθος του MinHeap

        //συναρτήσεις δημιουργίας του σωρού
        int parent(int k); 
        int left(int k);
        int right(int k);
        void BuildMinHeap(string inp,float &c); //Δημιουγεία MinHeap
        void MinHeapify(int i); //βοηθητική συνάρτηση για την δημιουργεία του MinHeap

        //υπόλοιπες συναρτήσεις
        void findMin(float &c); //συνάρτηση για εύρεση ελαχίστου
        void insertMin(string p1,float &c); //συνάρτηση για εισαγωγή στοιχείου
        void deleteMin(float &c); //συνάρτηση για διαγραφή ελάχισοτυ στοιχείου
};
#endif

