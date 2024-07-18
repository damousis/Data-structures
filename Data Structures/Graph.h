#ifndef GRAPH
#define GRAPH
#include <string>

using namespace std;

class Graph
{
  protected:
    int sizeGRAPH;//μέγεθος του γράφου
    int **weights;//πίνακας με τα βάρη του γράφου
    int *nodesG;//πίνακας με τα κόμβους του γράφου
  public:
    //κατασκευαστής
    Graph();

    //setter getter
    void SetSizeGraph(int x);//συνάρτηση για να μεταβάλουμε το πλήθος στοιχείων  του γράφου
    void getsizeGraph(float & c); //συνάρτηση που μας επιστρέφει το πλήθος στοιχείων του γράφου

    //συνάρτηση δημιουργίας του γράφου
    void BuildGraph(string inp,float & c);//συνάρτηση για την δημιουργία του γράφου

    //υπόλοιπες συναρτήσεις
    void insertGraph(string p1,string p2,string p3,float & c);//συνάρτηση για την εισαγωγή μια ακμής στο γράφο
    void deleteGraph(string p1,string p2,float & c);//συνάρτηση για την διαγραφή ακμής από το γράφο

    void computeSpanningTree(float & c);//συνάρτηση για την εύρεση του  κόστους του ελάχισοτυ εκτεινόμενου δένδρου
    void computeShortestPath(string p1,string p2,float & c);//υπολογίζει το χαμηλότερο κόστος για να φτάσουμε απο τον έναν κόμβο στον άλλον(που δέχεται σαν όρισματα)
    void findConnectedComponents(float & c);//βρίσκει το πλήθος των συνιστώσεων
    void DepthInFirst(int x,bool visited[]);//βοηθητική συνάρτηση για την findConnectedComponents


};
#endif