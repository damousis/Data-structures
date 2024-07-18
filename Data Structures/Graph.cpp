#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Graph.h"
#define MAX 2147483647

using namespace std;


//κατασκευαστής
Graph::Graph()
{
  sizeGRAPH =0;//αρχικοποίηση του μέγεθους του γράφου στο 0 
}

//setter getter
void Graph::SetSizeGraph(int x){sizeGRAPH =x;}//θέτει το μέγεθος του γράφου

void Graph::getsizeGraph(float &c)//επιστρέφει το μέγεθος των κόμβων και των ακμών 
{
  clock_t c1,c2;
  c1 = clock();
  ofstream o;
  o.open("output.txt",ios::out|ios::app);
  o<<"The number of the nodes is: "<<sizeGRAPH;//εμφανίζουμε πλήθος κορυφών
  c2 = clock();
  c += float(c2 - c1) / CLOCKS_PER_SEC;
  o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to return the number of the nodes of the Graph)"<<endl;
  for(int i=0;i<20;i++)
      o<<"----";
  o<<endl;

  c1 = clock();
  int i,j,e=0;
  for(i=0;i<sizeGRAPH;i++)
  {  
      for(j=i;j<sizeGRAPH;j++)
      {
          if(weights[i][j]!=0)//αν συνδέονται οι κόμβοι τότε αυξάνουμε το πλήθος των ακμών κατά 1
              e+=1;
      }
  }
  c2 = clock();
  c += float(c2 - c1) / CLOCKS_PER_SEC;
  o<<"The number of the edges are: "<<e;//εμφανίζουμε πλήθος ακμών
  o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to return the number of the edges of the Graph)"<<endl;
  for(int i=0;i<20;i++)
      o<<"----";
  o<<endl;
  o.close();
}
  
//συνάρτηση δημιουργίας γράφου
void Graph::BuildGraph(string inp,float &c)
{
    clock_t c1,c2;
    c1 = clock();
    string sup;//βοηθητική μεταβλητή για να μετράμε το πλήθος των στοιχείων εισόδου
    int node1, node2, w,i=0,j,*temp,index1,index2;
    bool isthere;//βοηθητική μεταβλητή για 

    ifstream f;
    f.open(inp);//άνοιγμα αρχείου για ανάγνωση

    if (f.is_open()) 
    {
        while (getline(f, sup)) 
        {
            istringstream iss(sup);//διαχωρίζουμε τις 3 τιμές τις εισόδου και τις διαχωερίζουμε σε 3 διαφορετικές μεταβλητές
            if (!(iss >> node1 >> node2 >> w))//'ελεγχος αν έγινε κάποιο άθος στην ανάγνωση
            {
              continue;//πηγάινουμε στην επόμενη επανάληψη
            }
            else
            {
              isthere =false;//αρχικοποίηση της μεταβλητής με false για να δείξουμε οιτ δεν έχει επισκεφθεί ο κόμβος που βρισκόμαστε
              if(i==0)//ελέγχουμε αν είναι η πρώτη τιμή που εισάγεται
              {
                nodesG = new int [i+1]; //δέσμευση για μια μόνο τιμή
                nodesG[0]=node1;
                i+=1;
              }
              else
              {
                for(j=0;j<i;j++)
                {
                  if(node1==nodesG[j])
                    isthere =true;//ελέγχουμε αν ο κόμβος που εισάγουμε υπάρχει ήδη στον πίνακα 
                }
                if(isthere==false)//αν δέν υπάρχει ο κόμβος τότε τον προσθέτουμε
                {
                  temp = new int[i+1];//βοηθητικός πίνακας για την αποθήκευση των στοιχείων
                  for(j=0;j<i;j++)
                    temp[j]=nodesG[j];//αντιγραφή του παλιού πίνακα στον βοηθητικό
                  temp[i]=node1;//τοποθέτηση του καινούριου στοιχείου στον νέο πίνακα
                  delete [] nodesG;//αποδέσμευση μνήμης για τον παλιό πίνακα
                  nodesG = new int [i+1];//νέα δέσμευση μνήμης για τον πίνακα αυξημένο κατά 1
                  for(j=0;j<i+1;j++)
                    nodesG[j]=temp[j];//αντιγραφή των στοιχείων σρτον νέο πίνακα
                  i+=1;
                  delete []temp;//αποδέσμευση μνήμης του βοηθητικού πίνακα
                }
              }
            }
        }
    } 
    else 
    {
        cout << "There was a problem in opening the file!" << inp << endl;
    }
  f.close();

  f.open(inp);

  //επαναλαμβάνουμε ακριβώς την ίδια διαδικασία για τους δέυτερους κόμβους
  if (f.is_open()) 
  {
      while (getline(f, sup)) 
      {
          istringstream iss(sup);
          if (!(iss >> node1 >> node2 >> w))
          {
            continue; 
          }
          else
          {
              isthere =false;
              for(j=0;j<i;j++)
              {
                if(node2==nodesG[j])
                  isthere =true;
              }
              if(isthere==false)
              {
                temp = new int[i+1];
                for(j=0;j<i;j++)
                  temp[j]=nodesG[j];
                temp[i]=node2;
                delete [] nodesG;
                nodesG = new int [i+1];
                for(j=0;j<i+1;j++)
                  nodesG[j]=temp[j];
                i+=1;
                delete []temp;
              }
          }
      }
      SetSizeGraph(i);//θέτουμε το μέγεθος του γράφου
      
  } 
  else 
  {
    cout << "There was a problem in opening the file!" << inp << endl;
  }
  f.close();
  f.open(inp);
  
  weights = new int *[sizeGRAPH];//δυναμική δέσμευση μνήμης για πίνακα που θα αποθηκεύει το βάρος των ακμών όταν 2 κόμβοι συνδέονται
  for(i=0;i<sizeGRAPH;i++)
    weights[i]= new int [sizeGRAPH];
  for(i=0;i<sizeGRAPH;i++)
    {
      for(j=0;j<sizeGRAPH;j++)
        weights[i][j]=0;//αρχικοποίηση των βάρων σε 0
    }
  
  if (f.is_open()) 
    {
        while (getline(f, sup)) 
        {
            istringstream iss(sup);
            if (!(iss >> node1 >> node2 >> w))
            {
              continue; 
            }
            else
            {
              for(i=0;i<sizeGRAPH;i++)
              {
                if(nodesG[i]==node1)
                  index1 =i;//αναζητήση θέσης του 1ου κόμβου 
                if(nodesG[i]==node2)
                  index2=i;//αναζήτηση θέσης του 2ου κόμβου
              }
              weights[index1][index2]=w;//ανάλογα με την θέσης τους τοποθετούμε το βάρος της ακμής στονμ πίνακα 
              weights[index2][index1]=w;//το ίδιο στην συμμετρική του θέση καθώς είναι μη κατευθυνόμενος
            }
        }
    }
  f.close();
  c2 = clock();
  c += float(c2 - c1) / CLOCKS_PER_SEC;

  //εμφανίση του γράφου
  ofstream o;
  o.open("output.txt",ios::out|ios::app);
  o<<"The graph was made and:";
  o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to build the Graph)"<<endl;
  for(i=0;i<sizeGRAPH;i++)
  {
    int pl=0;
    o<<"the node: "<<nodesG[i]<<" conects with the node ";
    for(j=0;j<sizeGRAPH;j++)
    {
      if(weights[i][j]!=0 && pl==0)
      {
        o<<nodesG[j]<<" with weight "<<weights[i][j]<<" ";
        pl+=1;
      }
      else if(weights[i][j]!=0 && pl!=0)
        o<<" and with the node: "<<nodesG[j]<<" with weight "<<weights[i][j]<<" ";
    }
    o<<endl;
      
  }
  for(i=0;i<20;i++)
    o<<"----";
  o<<endl;
  o.close();
  
  
}

//υπόλοιπες συναρτήσεις 
void Graph::insertGraph(string p1, string p2, string p3, float &c) 
{
    clock_t c1, c2;
    c1 = clock();
    int n1, n2, we, index1 = -1, index2 = -1;

    // μετατροπή απο strings σε  int
    n1 = stoi(p1);
    n2 = stoi(p2);
    we = stoi(p3);

    //άνοιγμα αρχειου για εγγραφή
    ofstream o("output.txt", ios::out | ios::app);
    if (!o.is_open()) 
    {
        return;
    }

    // έλεγχος αν υπάρχει ο n1
    for (int i = 0; i < sizeGRAPH; ++i) 
    {
        if (nodesG[i] == n1) 
        {
            index1 = i;
            break;
        }
    }

    // αν δεν υπάρχει αλλάζουμε τοπ μέγεθο του γράφου
    if (index1 == -1) 
    {
        int newSize = sizeGRAPH + 1; // αύξανουμε το μέγεθοςς κατά 1
        int *tempNodes = new int[newSize];
        int **tempWeights = new int*[newSize];
        for (int i = 0; i < newSize; ++i) 
        {
            tempWeights[i] = new int[newSize]();
            if (i < sizeGRAPH) 
            {
                tempNodes[i] = nodesG[i];
                for (int j = 0; j < sizeGRAPH; ++j) 
                {
                    tempWeights[i][j] = weights[i][j];
                }
            }
        }

        // προσθέτουμε το n1
        tempNodes[sizeGRAPH] = n1;

        //αποδεσμέυουμε την προηγούμενη μνήμη
        delete[] nodesG;
        for (int i = 0; i < sizeGRAPH; ++i) 
        {
            delete[] weights[i];
        }
        delete[] weights;

        nodesG = tempNodes;
        weights = tempWeights;
        sizeGRAPH = newSize;
        index1 = sizeGRAPH - 1;
    }

    // κάνουμε ακριβώς την ίδια διαδικασία αλλά για τον κόμβο n2
    for (int i = 0; i < sizeGRAPH; ++i) 
    {
        if (nodesG[i] == n2)
        {
            index2 = i;
            break;
        }
    }

 
    if (index2 == -1) 
    {
        int newSize = sizeGRAPH + 1; // Increase size by 1
        int *tempNodes = new int[newSize];
        int **tempWeights = new int*[newSize];
        for (int i = 0; i < newSize; ++i) 
        {
            tempWeights[i] = new int[newSize]();
            if (i < sizeGRAPH) 
            {
                tempNodes[i] = nodesG[i];
                for (int j = 0; j < sizeGRAPH; ++j)
                {
                    tempWeights[i][j] = weights[i][j];
                }
            }
        }

        tempNodes[sizeGRAPH] = n2;

        delete[] nodesG;
        for (int i = 0; i < sizeGRAPH; ++i) 
        {
            delete[] weights[i];
        }
        delete[] weights;

        nodesG = tempNodes;
        weights = tempWeights;
        sizeGRAPH = newSize;
        index2 = sizeGRAPH - 1;
    }

    // προσθέτουμε την νέα ακμή αν χρειάζεται
    if (weights[index1][index2] != 0) 
    {
        o << "The edge between nodes " << n1 << " and " << n2 << " already exists.";
    } 
    else 
    {
        weights[index1][index2] = we;
        weights[index2][index1] = we;
        o << "The edge between nodes " << n1 << " and " << n2 << " with weight " << we << " was inserted.";
    }

    c2 = clock();
    c += float(c2 - c1) / CLOCKS_PER_SEC;
    o << " (it took " << fixed << setprecision(6) << float(c2 - c1) / CLOCKS_PER_SEC << " seconds to add the new edge to the graph)" << endl;
    for (int i = 0; i < 20; ++i) o << "----";
    o << endl;
    o.close();
}


void Graph::deleteGraph(string p1, string p2,float &c)
{
  clock_t c1,c2;
  c1 = clock();
  int n1,n2,i,index1=-1,index2=-1;
  ofstream o;//άνοιγμα αρχείου εξόδου
  o.open("output.txt",ios::out|ios::app);
  
  n1 = stoi(p1);//μετατροπή του ορίσματος 1 σε int
  n2 = stoi(p2);//μετατροπή του ορίσματος 2 σε int
  for(i=0;i<sizeGRAPH;i++)
  {
    if(n1 ==nodesG[i])
      index1 = i; //ελέγχουμε αν υπάρχει ο κόμβος 1 στον γράφο
    if(n2==nodesG[i])
      index2 = i;//ελέγχουμε αν υπάρχει ο κόμβος 2 στον γράφο
  }
  if(index1!=-1 && index2!=-1 && weights[index1][index2]!=0)//ελέγχουμε αν υπάρχουν και οι 2 κόμβοι και αν συνδέονται μεταξύ τους
  {
    c2 = clock();
     c += float(c2 - c1) / CLOCKS_PER_SEC;
    weights[index1][index2]=0;//αφαιρούμε την ακμή του θέτοντας την με 0
    weights[index2][index1]=0;
    o<<"The edge of the nodes: "<<n1<<" and "<<n2<<" was deleted succesfully";
     o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to delete the edge from the Graph)"<<endl;
  }
  else
  {//αν δεν υπάρχει κάποιος κόμβος ή αν δεν συνέονται μεταξύ τους
      c2 = clock();
      c += float(c2 - c1) / CLOCKS_PER_SEC;
    o<<"There is no edge between the nodes: "<<n1<<" and "<<n2;
     o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to find out there was no edge from the first node to the second)"<<endl;
  }

  for(i=0;i<20;i++)
    o<<"----";
  o<<endl;
  o.close();
}

void Graph::computeSpanningTree(float &c)
{
  clock_t c1,c2;
  c1 = clock();
  bool *visited;//βοηθητικός πίνακας για τους κόμβους που έχουμε επισκευθεί
  int *p,*k,i,j,start,sum=0,min,h;

  visited = new bool [sizeGRAPH];//δυναμική δέσμευση μνήμης για το πλήθος των στοιχείων του πίνακα
  p = new int [sizeGRAPH];//βοηθητικός πίνακας parent για καθε κόμβο
  k = new int [sizeGRAPH];//βοηθητικός πίνακας για την αποθήκυεση την μικρότερης απόστασης

  //αρχικοποίηση όλων των πινάκων
  for(i=0;i<sizeGRAPH;i++)
  {
    visited[i]=false;
    p[i]=-1;
    k[i]=MAX;
  }

  //επιλογή του κόμβου στην θέση 0 ως αρχικό κόμβο
  start =nodesG[0];//μεταβλητή που αποθηκεύει τον κόμβο που ξεκινήσαμε
  p[0]=start;//ο parent του αρχικού κόμβου είναι ο ίδιος ο κόμβος
  k[0]=0;//το κόστος διαδρομής είναι 0 

  for(i=0;i<sizeGRAPH;i++)
  {
    h=-1;//βοηθητική μεταβλητή 
    min = MAX;//βοηθητική μεταβλητή για την απόσταση
    for(j=0;j<sizeGRAPH;j++)
    {
      if(visited[j]==false && k[j]<min)//ελεγχουμε αν δεν έχουμε επισκεφθεί τον κομβο και άν το κόστος του είναι μικρότερο απο αυτό που αποθηκεύσαμε
      {
        min = k[j];//αλλαγή την min
        h = j; //αλλαγή του h
      }
    }

    if(h!=-1) //ελεγχουμε αν έχει γίνει κάποια αλλαγή
    {
      visited[h]=true;//ενημερώνουμε οτι επισκεφθήκαμε τον κόμβο h
      if(p[h]!= -1) //αν ο parent του δεν έιναι -1 δηλαδή έχει parent
        sum+=k[h];//αυξάνουμε το κόστος συνολικής διαδρομής
    }

  for(j=0;j<sizeGRAPH;j++)// Έλεγχος αν ο κόμβος δεν έχει επισκεφτεί και υπάρχει ακμή από τον τρέχοντα κόμβο στον κόμβο j
    {
        
        if( h!=-1 && visited[j]==false && weights[h][j]!=0 && weights[h][j]<k[j])// Αν ισχύουν οι παραπάνω συνθήκες, ενημέρωσε το μονοπάτι προς τον κόμβο j
        {
          p[j]=h;
          k[j]=weights[h][j];// Ενημέρωσε το βάρος του μονοπατιού προς τον κόμβο j
        }
    }
  }
  c2 = clock();
  c += float(c2 - c1) / CLOCKS_PER_SEC;
  ofstream o;
  o.open("output.txt",ios::out|ios::app);
  o<<"The cost of the minimum spanning tree is: "<<sum;
  o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to calculate the cost of the minimum spanning tree)"<<endl;
  for(i=0;i<20;i++)
    o<<"----";
  o<<endl;
  o.close();

  //αποδέσμευση μνήμης των βοηθητικών πινάκων
  delete[] visited;
  delete[] p;
  delete[] k;
}

void Graph::computeShortestPath(string p1,string p2,float &c)
{
  clock_t c1,c2;
  c1 = clock();
  int n1,n2,*p,*k,i,j,index1,index2,h,min,mcost=0;
  bool * visited;

  //μετατροπή των ορισμάτων απο strings σε integers
  n1= stoi(p1);
  n2 = stoi(p2);

  //αρχικοποίηση των βοηθητικών πινάκων
  visited = new bool [sizeGRAPH];//εάν έχουμε επισκεφθεί τον κάθε κόμβο
  p = new int [sizeGRAPH];//parent
  k = new int [sizeGRAPH];//αποσταση

  for(i=0;i<sizeGRAPH;i++)
  {
    //αρχικοποίηση των βοηθητικών πινάκων
    visited[i]=false;
    p[i]=-1;
    k[i]=MAX;
  }

  for (i = 0; i < sizeGRAPH; i++) 
  {
      if (nodesG[i] == n1)
          index1 = i;//βρίσκουμε την θέση του 1ου κόμβου που δίνεται ως όρισμα
      if (nodesG[i] == n2)
          index2 = i;//βρίσκουμε την θέση του 2ου κόμβου που δίνεται ως όρισμα
  }
  p[index1]=-1;//θέτουμε τον parent του 1ου κόμβου
  k[index1]=0;//θέτουμε την αποστάση του 1ου κόμβου
  for(i=0;i<sizeGRAPH;i++)
  {
    h=-1;//βοηθητική μεταβ
    min= MAX;

    // Εύρεση του κόμβου με τη μικρότερη απόσταση που δεν έχει επισκεφτεί ακόμα
    for(j=0;j<sizeGRAPH;j++)
    {
      if(visited[j]==false && k[j]<min)
      {
        min = k[j];
        h =j;
      }
      
    }
    if(h==-1)
      break;

    visited[h]=true;// Επισκεφτήκαμε τον κόμβο h
    for(j=0;j<sizeGRAPH;j++)
      {
        if(weights[h][j]!=0 && k[h]+weights[h][j]<k[j])
        {
          k[j]= k[h]+weights[h][j];// Ενημερώνουμε την απόστασης
          p[j]=h;//ενημερώνουμε τον γονέα
        }
      }
  }
  mcost = k[index2];//αποθηκέυουμε το τελικό κόστος διαδρομής

  c2 = clock();
  c += float(c2 - c1) / CLOCKS_PER_SEC;
  ofstream o;
  o.open("output.txt",ios::out|ios::app);
  if (mcost != MAX) 
  {
      o << "The shortest path cost to node " << n2 << " from the node "<<n1<<" is: " << mcost;
  } 
  else
  {
      o << "No path found!";
  }
   o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to return compute the shortest path from the two nodes)"<<endl;
  for(i=0;i<20;i++)
      o<<"----";
  o<<endl;
  o.close();

  //αποδέσμευση μνήμης των βοηθητικών πινάκων
  delete[] visited;
  delete[] p;
  delete[] k;
  
}

void Graph::DepthInFirst(int x, bool *visited)
{
  int i;
  visited[x]=true;//ενημερώνουμε ότι επισκεφθηκαμε τον κόμβο x

  for(i=0;i<sizeGRAPH;i++)
    {
      if(weights[x][i]!=0 && visited[i]==false)//ελέγχουμε αν δεν έχομυε επισκεφθεί τον κλόμβο j και αν υπάρχει ακμή με τον κόμβο x
        DepthInFirst(i, visited);//καλούμε αναδρομικά την συνάρτηση για τον κόμβο j
    }

}


void Graph::findConnectedComponents(float &c)
{
  clock_t c1,c2;
  c1 = clock();
  bool * visited;//βοηθητικός πίνακας για το αν έχουμε επισκεφθεί κάποιον κόμβο
  int i,sum=0;

  visited = new bool [sizeGRAPH];//δέσμευση του πίνακα
  for(i=0;i<sizeGRAPH;i++)
    visited[i]=false;//αρχικοποίηση του πίνακα

  for(i=0;i<sizeGRAPH;i++)
    {
      if(visited[i]==false)//ελέγχουμε αν δεν έχουμε επισκεφθεί τον κόμβο i
      {
        DepthInFirst(i, visited);//καλούμε βοηθητική συνάρτηση για τον κόμβο
        sum+=1;//αυξάνουμε τον αριθμό των συνολικών συνιστώσεων
      }
    }

  c2 = clock();
  c += float(c2 - c1) / CLOCKS_PER_SEC;
  ofstream o;
  o.open("output.txt",ios::out|ios::app);
  o<<"The number of connected components is: "<<sum;
   o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to return the connected components of the graph)"<<endl;
  for(i=0;i<20;i++)
    o<<"----";
  o<<endl;

  delete [] visited;//αποδέσμευση μνήμης του βοηθητικού πίνακα
  
}