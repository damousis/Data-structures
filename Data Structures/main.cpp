#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <sstream>

#include "MinHeap.h"
#include "MaxHeap.h"
#include "AvlTree.h"
#include "Graph.h"
#include "HashTable.h"
using namespace std;

int main()
{
    float cMin=0,cMax=0,cHash=0,cGraph=0,cAvl=0;
    MinHeap minH;//μεταβλητή που αφορά το MinHeap
    MaxHeap maxH;//μεταβλητή που αφορά το MaxHeap
    AvlTree tree;//μεταβλητή που αφορά το AvlTree
    Graph graph;//μεταβλητή πο αφορά το Graph
    HashTable hashT;//μεταβλητή που αφορά το HashTable

    ifstream f;
    f.open("commands.txt",ios::in);  // δημιουργούμε ενα ρεύμα εισόδου και ανοίγουμε το αρχείο commands.txt που περιέχει τις εντολές

    ofstream o;
    o.open("output.txt",ios::out);

    string command; //δημιουργούμε μια μεταβλητή για να αποθηκεύουμε την κάθε γραμμή του commands.txt
    string action,structure,p1,p2,p3; //δημιουργουμε 5 ακόμα μεταβλητές που αποθηκέυθουν τα 5 μέρη τις κάθε εντολή(αν υπάρχουν 5)
    //η 1η αποθηκέυει το action(δηλαδή την ενέργεια,η 2η αποθηκέυει την δομή που θα ενεργήσουμε,η 3η, 4η και η 5η(προαιρετικες) αποθηκεύουν τα ονόματα φακέλων είτε αριθμούς


    if(f.is_open())//ελεγχούμε αν το αρχείο άνοιξε με επιτυχία
    {
        while(getline(f,command)) //παίρνουμε μια μια τις γραμμές του αρχείου με τις εντολές
        {
            istringstream iss(command);//διαχωρίζουμε τις λέξεις της εντολής με βάση τα κενά
            iss >>action>>structure>>p1>>p2>>p3;//δημιουργία τεσσάρων μεταβλητών με βάση τα κενά 

            if(command.empty())
                continue;
            
            //ξεκινάμε τις ενέργεις!!
            if(action=="BUILD")//ελεγχουμε αν η ενέργεια είναι η BUILD
            {
                //Δημιουργία των δομών ! (MINHEAP,MAXHEAP,AVLTREE,GRAPH,HASHTABLE)
                if (structure == "MINHEAP")
                {
                    minH.BuildMinHeap(p1,cMin); 
                }
                else if(structure=="MAXHEAP")
                {
                    maxH.BuildMaxHeap(p1,cMax);
                }
                else if(structure=="AVLTREE")
                {
                    tree.BuildAvlTree(p1,cAvl);
                }
                else if(structure=="GRAPH")
                {
                    graph.BuildGraph(p1,cGraph);
                }
                
                else if(structure=="HASHTABLE")
                {
                    hashT.BuildHashTable(p1,cHash);
                }
            }
            //Κλήση συναρτήσεων που επιστρέφουν το μέγεθος όλων των δομών 
            else if(action=="GETSIZE")
            {
                if(structure=="MINHEAP")
                    minH.getsizeMin(cMin); 
                else if(structure=="MAXHEAP")
                    maxH.getsizeMax(cMax);
                else if(structure=="AVLTREE")
                    tree.GetSizeAvlTree(cAvl);
               else if(structure=="GRAPH")
                    graph.getsizeGraph(cGraph);
                else if(structure=="HASHTABLE")
                    hashT.getsizeHashTable(cHash);
            }
            //Εύρεση ελάχιστου στοιχείου στο MINHEAP και AVLTREE
            else if(action=="FINDMIN")
            {
                if(structure=="MINHEAP")
                    minH.findMin(cMin);
                else if(structure=="AVLTREE")
                    tree.FindMinAvlTree(cAvl);
            }
            //Εύρεση μέγιστου στοιχείου στο MAXHEAP
            else if(action=="FINDMAX")
            {
                if(structure=="MAXHEAP")
                    maxH.findMax(cMax);
            }
            //Εισαγωγή στοιχείων σε όλεσ τις δομές 
            else if(action=="INSERT")
            {
                if(structure=="MINHEAP")
                    minH.insertMin(p1,cMin);
                else if(structure=="MAXHEAP")
                    maxH.insertMax(p1,cMax);
                else if(structure=="AVLTREE")
                    tree.insertAvlTree(p1,cAvl);
                else if(structure=="GRAPH")
                   graph.insertGraph(p1,p2,p3,cGraph);
                else if(structure=="HASHTABLE")
                    hashT.insertHash(p1,cHash);
            }
            else if(action=="DELETEMIN")
                minH.deleteMin(cMin);       // διαγραφή ελάχιστου στοιχείου στο MINHEAP 
            else if(action=="DELETEMAX")
                maxH.deleteMax(cMax);       // διαγραφή μέγιστου στοιχείου στο MAXHEAP
            else if(action=="SEARCH")
            {
                if(structure=="HASHTABLE")
                    hashT.searchHash(p1,cHash);
                else if(structure=="AVLTREE")
                    tree.SearchAvlTree(p1,cAvl);
            }
            else if(action=="COMPUTESPANNINGTREE")
                graph.computeSpanningTree(cGraph);
            else if(action=="DELETE")
            {
                if(structure=="AVLTREE")
                    tree.deleteAvl(p1, cAvl);
                if(structure=="GRAPH")
                    graph.deleteGraph(p1,p2,cGraph);
            }
            else if(action=="COMPUTESHORTESTPATH")
            {
                graph.computeShortestPath(p1,p2,cGraph);
            }
            else if(action=="FINDCONNECTEDCOMPONENTS")
            {
                graph.findConnectedComponents(cGraph);
            }
        }
         f.close();
    }

    //εμφανίζουμε τον συνολικό χρόνο κάθε δομής
    o.close();
    ofstream l;
    l.open("output.txt",ios::out|ios::app);
    l<<"TIME TAKEN FOR EVERY STRUCTURE:"<<endl;
    l<<"The time taken for the MinHeap was: "<<fixed << setprecision(6) <<cMin<<" seconds"<<endl;
    l<<"The time taken for the MaxHeap was: "<<fixed << setprecision(6) <<cMax<<" seconds"<<endl;
    l<<"The time taken for the AvlTree was: "<<fixed << setprecision(6) <<cAvl<<" seconds"<<endl;
    l<<"The time taken for the HashTable was: "<<fixed << setprecision(6) <<cHash<<" seconds"<<endl;
    l<<"The time taken for the Graph was: "<<fixed << setprecision(6) <<cGraph<<" seconds"<<endl;
    l.close();

}