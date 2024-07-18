#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "MinHeap.h"
using namespace std;

MinHeap::MinHeap(){sizeMIN=0;}// αρχικοποιώ το sizeMAX στο 0

int MinHeap::parent(int k){return (k-1)/2;}//επιστρέφει την θεση του κόμβου πατερα
int MinHeap::left(int k){return 2 * k +1;}//επιστρέφει την θέση του αριστερού παιδιού
int MinHeap::right(int k){return 2 *k +2;}//επιστρέφει την θέση του δεξιού παιδιού

//setter getter 
void MinHeap::SetSizeMin(int ns){sizeMIN=ns;}//θέτει το μέγεθος του Minheap

void MinHeap::getsizeMin(float &c)//επιστρέφει στην οθόνη το μέγεθος του MinHeap
{
    clock_t c1,c2;
    c1= clock();
    ofstream o;
    o.open("output.txt",ios::out|ios::app);//δημιουργούμε ενα ρεύμα εξόδου για να γράψουμε τα αποτελέσματα στο τέλος του output.txt
    if(o.is_open())//έλεγχος επιτυχίας ανοίγματος αρχείου 
    {
        o<<"The size of the MinHeap is:"<<sizeMIN;
    }
    c2 =clock();
    o << fixed << setprecision(6) << " (it took " << float(c2 - c1) / CLOCKS_PER_SEC << " seconds to return the size of the MinHeap)" << endl;
    //o<<"It took "<<float(c2-c1)/CLOCKS_PER_SEC<<" seconds"<<"to return the size of the MinHeap"<<endl;
    for(int i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();//κλείσιμο ρεύματος εξόδου
    c += float(c2 - c1) / CLOCKS_PER_SEC;
}

//συναρτήσεις δημιουργίας του σωρού
void MinHeap::MinHeapify(int i)//χρησιμοποιείται για την διαδικασία δημιουργείας του MinHeap καθώς βρίσκει την σωστή θέση του κάθε στοιχειου στον πίνακα που τα τοποθετούμε
{
    int small= i; //δημιουργούμε μια μεταβλητή small για να αποθηκεύσουμε την τιμή του ορίσματος
    int Lch = left(i); //αποθήκευση της θέσης του αριστερού παιδιού
    int Rch = right(i);//αποθήκευση της θέσης του δεξιού παιδιού

    if (Lch < sizeMIN && minhe[Lch] < minhe[small])//ελέγχουμε αν το αριστερό παιδί είναι μικρότερο απο το αρχικό κόμβο
        small = Lch; //αν ισχύει τότε αλλάζουμε τη τιμή της μεταβλητής με το αριστερό παιδί

    if (Rch < sizeMIN && minhe[Rch] < minhe[small])//ελέγχουμε αν το αριστερό παιδί είναι μικρότερο απο το αρχικό κόμβο
        small = Rch;//αν ισχύει τότε αλλάζουμε τη τιμή της μεταβλητής με το δεξί παιδί

    if (small != i)//αν έχει γίνει κάποια if τότε αλλάζουμε τον πίνακα του MinHeap και ξανα κάνουμε την ίδια διαδικασία αναδρομικά
    {
        int t;
        t= minhe[i];
        minhe[i]=minhe[small];
        minhe[small]=t;
        MinHeapify(small);
    }
}

void MinHeap:: BuildMinHeap(string inp,float &c)//δημιουργία του MinHeap
{
    clock_t c1,c2;
    c1 =clock();
    ifstream f;//μεταβλητή για ανοίγμα αρχείου εισόδου
    ofstream o;//μεταβλητή για ανοίγμα αρχείου εξόδου
    string sup;//βοηθητική μεταβλητή για την ανάγνωση των στοιχείων του αρχείου

    f.open(inp);//άνοιγμα αρχείου εισόδου που δίνεται ως όρισμα στην συνάρτηση
    if(f.is_open())
    {
        int size=0;
        while(getline(f,sup))//υπολογισμός των στοιχείων του αρχείου εισοδου για να ορίσουμε το μέγεθος του πίνακα 
        {
            size+=1;//βοηθητική μεταβλητή για να μετρήσουμε το πλήθος των στοιχείων του αρχείου
        }
        SetSizeMin(size);//καλούμε την συνάρτηση για να ορίσουμε το μέγεθος του πίνακα
    }
    f.close();//κλείνουμε το αρχείο εισόδου μετά την ανάγνωση του
    minhe = new int [sizeMIN];//δημιουργία τον πίνακα του MinHeap με δυναμικό τρόπο με βάση το πλήθος των στοιχείων που υπολογίσαμε 

    f.open(inp);
    if(f.is_open())
    {
        o.open("output.txt",ios::out|ios::app);//ανοίγουμε το αρχείο εξόδου
        int i=0;

        while(getline(f,sup))
        {
            minhe[i]=stoi(sup);//μετατρέπουμε τα στοιχεία του αρχείου εισόδου σε integers και τα τοποθετούμε στον πίνακα
            i+=1;
        }

        for (int i = sizeMIN / 2 - 1; i >= 0; i--)//κατασκευή του MinHeap με την μέθοδο bottom-up
        {
            MinHeapify(i);
        }
        o<<"The MinHeap is: ";//εμφάνιση των στοιχείων του πινάκα
        for(i=0;i<sizeMIN;i++)
            o<<minhe[i]<<" ";
        //o<<endl;
    }
    c2 = clock();
    o << fixed << setprecision(6) << "(it took " <<fixed << setprecision(6) << float(c2 - c1)/CLOCKS_PER_SEC<<" second to build the MinHeap)"<<endl;
    f.close();
    for(int i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close(); //κλείσιμο αρχείου εξόδου μετά την εγγραφή
    c += float(c2 - c1) / CLOCKS_PER_SEC;
}

void MinHeap::findMin(float &c)
{
    clock_t c1,c2;
    c1=clock();
    ofstream o;//μεταβλητή για ανοίγμα αρχείου εξόδου
    o.open("output.txt",ios::out|ios::app);
    
    if (o.is_open())
        o<<"The minimun of the MinHeap is:"<<minhe[0];//εμφάνιση του πρώτου στοιχείου του πίνακα καθώς το μικρότερο στοιχείο του MinHeap βρίσκεται στην θέση 0 του πίνακα

    c2 = clock();
    o<<" (it took: "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" secondsa to find the minimun of the MinHeap)"<<endl;
    for(int i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();//κλείσιμο αρχείου εξόδου
     c += float(c2 - c1) / CLOCKS_PER_SEC;
}

void MinHeap::insertMin(string p1,float &c)//εισαγωγή στοιχείου 
{
    clock_t c1,c2;
    c1 = clock();
    int sup,*p,i;
    sup = stoi(p1);//βοηθητική μεταβλητή για την μετατροπή του ορίσματος σε integer(απο string)
    sizeMIN+=1;//αύξηση μεγέθους του MinHeap καθώς προσθέτουμε νέο στοιχείο
    p =new int[sizeMIN]; //δημιουργία νέου  βοηθητικού πίνακα με αυξημένο μέγεθος

    for(i=0;i<sizeMIN-1;i++)
        p[i]=minhe[i]; //αντιγραφή των στοιχείων του αρχικού πίνακα στον νέο  βοηθητικό πίνακα
    p[sizeMIN-1]=sup; //εισαγωγή του νέου στοιχείου στον βοηθητικό πίνακα

    delete [] minhe; //διαγραφή του παλιού πίνακα του MinHeap
    minhe = new int[sizeMIN];//νέα δέσμευση μνήμης για τον νέο πίνακα του MinHeap αυξημένο κατά 1
    for(i=0;i<sizeMIN;i++)
        minhe[i]=p[i]; //αντιγραφή των στοιχείων απο τον βοηθητικό πίνακα στον νέο πίνακα του MinHeap
    delete []p; //αποδεύμευση μνήμης του βοηθητικού πίνακα

    for (int i = sizeMIN / 2 - 1; i >= 0; i--)
    {
        MinHeapify(i); //ξανά τοποθετούμε τα στοιχεία στην σωστή θέση 
    }

    c2 = clock();
    ofstream o;
    o.open("output.txt",ios::out|ios::app);
    o<<"The number:"<<sup<<" was added and the new MinHeap is: ";
    for(i=0;i<sizeMIN;i++)
        o<<minhe[i]<<" ";
    //o<<endl;
    o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" seconds to add the new number in the MinHeap)"<<endl;
    for(i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();
    c += float(c2 - c1) / CLOCKS_PER_SEC;
}


void MinHeap::deleteMin(float &c)//διαγραφή ελάχιστου στοιχείου
{
    clock_t c1,c2;
    c1 = clock();
    int i,min,*k;
    min = minhe[0]; //αποθήκυση του μικροτερου στοιχείου σε μια μεταβλητή(γνωρίζουμε οτι το μικρότερο στοιχείο είναι το πρώτο)
    sizeMIN-=1;//μειώνουμε το μέγεθος του MinHeap κατά 1 γιατί διαγράφουμε ένα στοιχείο
    k = new int [sizeMIN]; //βοηθητικός πίνακας μειωμένος κατά 1 
    for(i=1;i<sizeMIN+1;i++)
        k[i-1]=minhe[i]; //αντιγραφή των στοιχείων του αρχικοόυ πίνακα στον βοηθητικό πίνακα
    delete [] minhe; //διαγραφή του προηγούμενου πίνακα του MinHeap

    minhe = new int [sizeMIN];//νέα δέσμευση μνήμης για τον νέο πίνακα του MinHeap με μικρότερο μέγεθος κατά 1
    for(i=0;i<sizeMIN;i++)
        minhe[i]=k[i]; //αντιγραφή των στοιχείων απο τον βοηθητικό πίνακα στον νέο πίνακα του MinHeap
    delete [] k;//απδεύμευση μνήμης του βοηθητικού πίνακα

    for (int i = sizeMIN / 2 - 1; i >= 0; i--)
    {
        MinHeapify(i);//τοποθεςτούμε πάλι τα στοιχεία στην σωστή θέση
    }

    c2 = clock();
    ofstream o;
    o.open("output.txt",ios::out|ios::app);
    if(o.is_open())
    {
        o<<"The number:"<<min<<" was deleted and the new MinHeap is:";
        for(i=0;i<sizeMIN;i++)
            o<<minhe[i]<<" ";
        //o<<endl;
        o<<" (it took "<<fixed << setprecision(6) <<float(c2-c1)/CLOCKS_PER_SEC<<" seconds to delete the number from the MinHeap)"<<endl;
    }
    for(i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();
    c += float(c2 - c1) / CLOCKS_PER_SEC;

}
