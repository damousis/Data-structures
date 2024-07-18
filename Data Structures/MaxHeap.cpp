#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "MaxHeap.h"
using namespace std;

MaxHeap::MaxHeap() {sizeMAX = 0;} // αρχικοποιώ το sizeMAX στο 0


int MaxHeap::parent(int k){return (k-1)/2;}//επιστρέφει την θεση του κόμβου πατερα
int MaxHeap::left(int k){return 2 * k +1;}//επιστρέφει την θέση του αριστερού παιδιού
int MaxHeap::right(int k){return 2 *k +2;}//επιστρέφει την θέση του δεξιού παιδιού

void MaxHeap::SetSizeMax(int x){sizeMAX=x;}//θέτει το μέγεθος του MaxHeap
void MaxHeap::getsizeMax(float &c)//επιστρέφει το μέγεθος του MaxHeap
{
    clock_t c1,c2;
    c1 = clock();
    ofstream o;
    o.open("output.txt",ios::out|ios::app);
    if(o.is_open())
    {
        o<<"The size of the MaxHeap is:"<<sizeMAX;
    }
    c2 = clock();
    o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" seconds to return the size of the MaxHeap)"<<endl;
    for(int i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();
    c += float(c2 - c1) / CLOCKS_PER_SEC;
}

//συναρτήσεις δημιουργίας του σωρού 
void MaxHeap::MaxHeapify(int i)//βοηθητική συνάρτηση που μας βοηθάει να φτιάξουμε το MaxHeap καθώς ελέγχει τα στοιχεία και τα τοποθετεί στην κατάλληλη ΄θέση
{
    int big= i;//δημιουργούμε μια μεταβλητή big για να αποθηκεύσουμε την τιμή του ορίσματος
    int Lch = left(i); //αποθήκευση της θέσης του αριστερού παιδιού
    int Rch = right(i);//αποθήκευση της θέσης του δεξιού παιδιού

    if (Lch < sizeMAX && maxhe[Lch] > maxhe[big])//ελέγχουμε αν το αριστερό παιδί είναι μεγαλύερο απο το αρχικό κόμβο
        big = Lch;//αν ισχύει τότε αλλάζουμε τη τιμή της μεταβλητής με τη θέσ του αριστερού παιδιού

    if (Rch < sizeMAX && maxhe[Rch] > maxhe[big])//ελέγχουμε αν το δεξί παιδί είναι μεγαλύερο απο το αρχικό κόμβο
        big = Rch;//αν ισχύει τότε αλλάζουμε τη τιμή της μεταβλητής με τη θέση του δεξιού παιδιού


    if (big != i)//αν έχει γίνει κάποια if τότε αλλάζουμε τον πίνακα του MinHeap και ξανα κάνουμε την ίδια διαδικασία αναδρομικά
    {
        int t;
        t= maxhe[i];
        maxhe[i]=maxhe[big];
        maxhe[big]=t;
        MaxHeapify(big);
    }
}

void MaxHeap::BuildMaxHeap(string inp,float &c)//δημιουργία του MaxHeap
{
    clock_t c1,c2;
    c1 = clock();
    ifstream f;//μεταβλητή για ανοίγμα αρχείου εισόδου
    ofstream o;;//μεταβλητή για ανοίγμα αρχείου εξόδου
    string sup;//βοηθητική μεταβλητή για την ανάγνωση των στοιχείων του αρχείου

    f.open(inp);//άνοιγμα αρχείου εισόδου που δίνεται ως όρισμα στην συνάρτηση
    if(f.is_open())
    {
        int size=0;
        while(getline(f,sup))//υπολογισμός των στοιχείων του αρχείου εισόδου για να ορίσουμε το μέγεθος του πίνακα 
        {
            size+=1;//βοηθητική μεταβλητή για να μετρήσουμε το πλήθος των στοιχείων του αρχείου
        }
        SetSizeMax(size);//καλούμε την συνάρτηση για να ορίσουμε το μέγεθος του πίνακα του MaxHeap
    }
  f.close();//κλείνουμε το αρχείο εισόδου μετά την ανάγνωση του

  maxhe = new int [sizeMAX];//δημιουργία τον πίνακα του MinHeap με δυναμικό τρόπο με βάση το πλήθος των στοιχείων που υπολογίσαμε 
  f.open(inp);
  if(f.is_open())
  {
    o.open("output.txt",ios::out|ios::app);//ανοίγουμε το αρχείο εξόδου
    int i=0;

    while(getline(f,sup))//μετατροπή των string inputs σε int και τοποθέτηση στον πίνακα
    {
      maxhe[i]=stoi(sup);//μετατρέπουμε τα στοιχεία του αρχείου εισόδου σε integers και τα τοποθετούμε στον πίνακα του MaxHeap
      i+=1;    
    }
    for (int i = sizeMAX / 2 - 1; i >= 0; i--)//κατασκευή του MaxHeap με την μέθοδο bottom-up
    {
        MaxHeapify(i);
    }
    c2 = clock();
       c += float(c2 - c1) / CLOCKS_PER_SEC;
    o<<"The MaxHeap is: ";
      for(i=0;i<sizeMAX;i++)
      {
        o<<maxhe[i]<<" ";
      }
    o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" seconds to build the MaxHeap)"<<endl;
    f.close();
    for(i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();
  }
}

void MaxHeap::findMax(float &c)//εύρεση ελάχιστου στοιχείου 
{
    clock_t c1,c2;
    c1 = clock();
    ofstream o;//μεταβλητή για ανοίγμα αρχείου εξόδου
    o.open("output.txt",ios::out|ios::app);
    if (o.is_open())
        o<<"The maximum of the MaxHeap is:"<<maxhe[0];//εμφάνιση του πρώτου στοιχείου του πίνακα καθώς το μεγαλύτερο στοιχείο του MaxHeap βρίσκεται στην θέση 0 του πίνακα
    c2 = clock();
    o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to find the maximum of the MaxHeap)"<<endl;
    for(int i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();//κλείσιμο αρχείου εξόδου
    c += float(c2 - c1) / CLOCKS_PER_SEC;
}

void MaxHeap::insertMax(string p1,float &c)//εισαγωγή στοιχείου
{
    clock_t c1,c2;
    c1 = clock();
    int sup,*p,i;
    sup = stoi(p1);//βοηθητική μεταβλητή για την μετατροπή του ορίσματος σε integer(απο string)
    sizeMAX+=1;//αύξηση μεγέθους του MaxHeap καθώς προσθέτουμε νέο στοιχείο
    p =new int[sizeMAX];//δημιουργία νέου βοηθητικού πίνακα με αυξημένο μέγεθος

    for(i=0;i<sizeMAX-1;i++)
        p[i]=maxhe[i];//αντιγραφή των στοιχείων του αρχικού πίνακα του MaxHeap στον νέο  βοηθητικό πίνακα
    p[sizeMAX-1]=sup;//εισαγωγή του νέου στοιχείου στον βοηθητικό πίνακα

    delete [] maxhe;//διαγραφή του παλιού πίνακα του MaxHeap
    maxhe = new int[sizeMAX];//νέα δέσμευση μνήμης για τον νέο πίνακα του MaxHeap αυξημένο κατά 1
    for(i=0;i<sizeMAX;i++)
        maxhe[i]=p[i];//αντιγραφή των στοιχείων απο τον βοηθητικό πίνακα στον νέο πίνακα του MaxHeap
    delete []p;//αποδεύμευση μνήμης του βοηθητικού πίνακα

    for (int i = sizeMAX / 2 - 1; i >= 0; i--)
    {
        MaxHeapify(i); //ξανά τοποθετούμε τα στοιχεία στην σωστή θέση 
    }
    c2 = clock();

    ofstream o;
    o.open("output.txt",ios::out|ios::app);
    o<<"The number:"<<sup<<" was added and the new MaxHeap is: ";
    for(i=0;i<sizeMAX;i++)
        o<<maxhe[i]<<" ";
    o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to insert the  new number in the MaxHeap)"<<endl;
    for(i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();
    c += float(c2 - c1) / CLOCKS_PER_SEC;
}

void MaxHeap::deleteMax(float &c)//διαγραφή μεγίστου στοιχείου
{
    clock_t c1,c2;
    c1 = clock();
    int i,max,*k;
    max = maxhe[0];
    sizeMAX-=1;//μειώνουμε το μέγεθος του MaxHeap κατά 1 γιατί διαγράφουμε ένα στοιχείο
    k = new int [sizeMAX];//δημιουργούμε βοηθητικό πίνακα μειωμένο κατά 1 
    for(i=1;i<sizeMAX+1;i++)
        k[i-1]=maxhe[i];//αντιγραφή των στοιχείων του αρχικοόυ πίνακα στον βοηθητικό πίνακα
    delete [] maxhe;//διαγραφή του αρχικού πίνακα του MaxHeap

    maxhe = new int [sizeMAX];//νέα δέσμευση μνήμης για τον νέο πίνακα του MaxHeap με μικρότερο μέγεθος κατά 1
    for(i=0;i<sizeMAX;i++)
        maxhe[i]=k[i];//αντιγραφή των στοιχείων απο τον βοηθητικό πίνακα στον νέο πίνακα του MaxHeap
    delete [] k;//αποδεύσμευση μνήμης του βοηθητικού πίνακα

    for (int i = sizeMAX / 2 - 1; i >= 0; i--)
    {
       MaxHeapify(i);//τοποθεςτούμε πάλι τα στοιχεία στην σωστή θέση
    }
    c2 = clock();
     c += float(c2 - c1) / CLOCKS_PER_SEC;
    ofstream o;
    o.open("output.txt",ios::out|ios::app);
    if(o.is_open())
    {
        o<<"The number:"<<max<<" was deleted and the new MaxHeap is:";
        for(i=0;i<sizeMAX;i++)
            o<<maxhe[i]<<" ";
        o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" to delete the maximum from the MaxHeap)"<<endl; ;
    }
    for(i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();
}











