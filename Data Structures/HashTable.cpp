#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "HashTable.h"
using namespace std;

HashTable::HashTable()
{
    sizeHASH=0; //αρχικοποίηση του μεγέθους του HashTable
    st=0;
}

//sizes

void HashTable::getsizeHashTable(float &c)//εμφανίζει το μέγεθος του HashTable
{
    clock_t c1,c2;
    c1 = clock();
    ofstream o;//άνοιγμα αρχείου εγγραφής
    o.open("output.txt",ios::out|ios::app);
    if(o.is_open())
        o<<"The size of the HashTable is: "<<st;
    c2 = clock();
    c += float(c2 - c1) / CLOCKS_PER_SEC;
    o<<" (it took "<<fixed << setprecision(6) <<double(c2-c1)/CLOCKS_PER_SEC<<" seconds to return the size of the HashTable)"<<endl;
    for(int i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();//κλείσιμο αρχείου μετά την εγγραφή
}

//building
int HashTable::HashFunction(int key)
{
    return key%sizeHASH;//επιστρέφει την θέση που πρέπει να τοποθετηθεί το στοιχεί στον πίνακα με βάση μια συνθήκη
}

void HashTable::BuildHashTable(string inp,float &c)
{
    clock_t c1,c2;
    c1 = clock();
    ifstream f;//άνοιγμα αρχείου εισόδου
    f.open(inp);
    if(f.is_open())
    {
        string sup;//βοηθητική συνάρτηση για να μετρήσουμε τα στοιχεία του αρχείου
        int s=0;
        while(getline(f,sup))
        {
            s+=1;
        }
        sizeHASH = s;//θέτουμε το μέγεθος του HashTable με τον αριθμό των στοιχείων που διαβάσαμε
        st = s;
    }
    f.close();//κλείσιμο αρχείου εισόδου

    int i ;

    pl = new int[sizeHASH];//δυναμική δέσμευση του πίνακα που μετράει το πλήθος των στοιχείων του κάθε κλειδιού με βάση τον αριθμό των στοιχείων που διαβάσαμε
    for(i=0;i<sizeHASH;i++)
        pl[i]=0; //αρχικοποίηση του πίνακα με 0

    hast = new int *[sizeHASH];//δυναμική δέσμευση του πίνακα με βάση το πλήθος των στοιχείων που διαβάσαμε
    for(i=0;i<sizeHASH;i++)
        hast[i]=nullptr; //αρχικοποίηση των δεικτών της κάθε θέσης

    f.open(inp);//άνοιγμα αρχείου εισόδου

    ofstream o;
    o.open("output.txt",ios::out|ios::app);//άνοιγμα αρχείου εξόδου

    if(f.is_open())
    {
        string key;//βοηθητική μεταβλητή για να αποθηκέυουμε τις τιμές απο το αρχείο
        int val;//μεταβλητή για μετατρέπουμε την τιμή απο το string σε int
        int index;//μεταβλητή για να αποθηκέυει την θέση που πρέπει να αποθηκευτεί το στοιχείο με βάση το key του(αποτέλεσμα της συνάρτησης)
        while(getline(f,key))
        {
            val = stoi(key);
            index = stoi(key);
            index = HashFunction(index);
            if(hast[index]==nullptr)//ελέγχουμε αν είναι άδεια η θέση που θέλουμε να το αποθηκεύσουμε
            {    
                hast[index] = new int[1]; //δυναμική δέσμευση για ένα στοιχείο
                hast[index][0] = val;//αποθήκευση του στοιχείου
                pl[index]+=1;//αύξηση του πλήθους των στοιχείων της συγκεκριμένης θέσης κατά 1
            }
            else//αν δεν είναι άδεια η θέση
            {
                pl[index]+=1;//αύξηση του πλήθους των στοιχείων κατά 1
                int *h; //βοηθητικός πίνακας για να αποθηκεύσουμε τα στοιχεία του αρχικόυ πίνακα της θέσης index του HashTable

                h = new int[pl[index]];//δυναμική δέσμευση για το νέο πλήξθος στοιχείων του συγκεκριμένου index
                for(i=0;i<pl[index]-1;i++)
                    h[i]=hast[index][i];//αντιγραφή των στοιχείων

                h[pl[index]-1]=val;//προσθέτουμε το νεό στοιχείο στην επιπλέον θέση
                delete[]hast[index];//αποδέσμευση του παλιού πίνακα 

                hast[index]=new int[pl[index]];//νέα δυναμική δέσμευση για τον πίνακα που αποθηκέυει τα στοιχεία του συγκεκριμένου index
                for(i=0;i<pl[index];i++)
                    hast[index][i]= h[i];//αντιγραφή των στοιχείων που αποθηκέυσαμε στο βοηθητικό πίνακα
                delete []h;//αποδέσμευση μνήμης του βοηθητικού πίνακα
            }
        }

    }
        c2 = clock();
        c += float(c2 - c1) / CLOCKS_PER_SEC;
        o<<"The HashTable has been made:";
        o<<" (it took "<<fixed << setprecision(6) <<double(c2-c1)/CLOCKS_PER_SEC<<" seconds to build the HashTable)"<<endl;
        for(i=0;i<sizeHASH;i++)
        {
            if(hast[i]!=nullptr)//ελέγχουμε αν η θέση δεν είναι άδεια
            {
                o<<"For the key:"<<hast[i][0]%sizeHASH<<" the numbers are:";
                int j=0;
                for(j=0;j<pl[i];j++)
                    o<<hast[i][j]<<" ";///εμφάνιση των στοιχείων για κάθε Key
                o<<endl;
            }
        }
        for(i=0;i<20;i++)
            o<<"----";
        o<<endl;
    
    o.close(); //κλείσιμο αρχείου μετά την εγγραφή
}

//others
void HashTable::searchHash(string p1,float &c)
{
    clock_t c1,c2;
    int num,i=0,j,k;

    c1 = clock();
    ofstream o;//άνοιγμα αρχείου εξόδου
    o.open("output.txt",ios::out|ios::app);

    num = stoi(p1); //μετατροπή του ορίσματος σε int
    while(i<sizeHASH)
    {
        //ελέγχουμε αν η θέση δεν είναι άδεια και αν το όρισμα έχει ίδιο key με το πρώτο στοιχείο της κάθε θέσης
        if(hast[i]!=nullptr && HashFunction(hast[i][0])==HashFunction(num))
        {
            j=0;
            while(j<pl[HashFunction(num)] && hast[i][j]!=num)//ελέγχουμε αν το στοιχείο είναι στην θέση j(αφού έχει γίνει η πρώτη if)
            {
                j+=1;//αν δεν ισχύει η συνθήκη αυξάνουμε το j κατά 1
            }
            if(j<pl[HashFunction(num)])//αν το j είναι μικρότερο απο το πλήθος των στοιχείων του πίνακα που αντιστοιχεί στο κλειδί του num τότε εχει βρεθεί το στοιχείο
            {
                o<<"SUCCESS! The number: "<<num<<" was in the HashTable!";
                c2 = clock();
                 c += float(c2 - c1) / CLOCKS_PER_SEC;
                 o<<" (it took "<<fixed << setprecision(6) <<double(c2-c1)/CLOCKS_PER_SEC<<" seconds to find number in the HashTable)"<<endl;
                for(k=0;k<20;k++)
                    o<<"----";
                o<<endl;
            }
            else//αλλιώς το στοιχείο δεν υπάρχει στο HashTable
            {
                o<<"FAILURE! The number: "<<num<<" was not in the HashTable!";
                c2 = clock();
                 c += float(c2 - c1) / CLOCKS_PER_SEC;
                o<<" (it took"<<fixed << setprecision(6) <<double(c2-c1)/CLOCKS_PER_SEC<<" seconds to find out the number was not in the HashTable)"<<endl;
                for(k=0;k<20;k++)
                    o<<"----";
                o<<endl;
            }
            o.close(); //κλείσιμο αρχείου μετά την εγγραφή
            return;
        }
        else
            i+=1;//αυξήση του i κατά 1 για να πάμε στην επόμενη θέση του HashTable αν δεν πραγματοποιηθούν οι προηγούμενες εντολές
    }
    //αν βγέι απο την επανάληψη σημαίνει οτι δεν υπήρχε το στοιχείο
    o<<"FAILURE! The number: "<<num<<" was not in the HashTable!";
    c2 = clock();
     c += float(c2 - c1) / CLOCKS_PER_SEC;
    o<<" (it took "<<fixed << setprecision(6) <<double(c2-c1)/CLOCKS_PER_SEC<<" seconds to find out the number was not in the HashTable)"<<endl;
    for(i=0;i<20;i++)
        o<<"----";
    o<<endl;
    o.close();

}


void HashTable::insertHash(string p1,float &c)
{
clock_t c1,c2;
    int num,i,key;
    ofstream o;
    c1 = clock();
    o.open("output.txt",ios::out|ios::app);

    st+=1;
    num = stoi(p1);//μετατροπή του ορίσματος σε int
    key =HashFunction(num);//εύρεση της θέσης που πρέπει να τοποθετηθεί το στοιχείο με βάση το key του
    if(hast[key]==nullptr)// αν η θέση που πρέπει να τοποθετηθέι δείχνει στο NULL τότε σημαίνει οτι είναι άδειος ο πίνακας
    {
        hast[key] = new int[1];//δυναμική δέσμευση για ένα στοιχείο
        hast[key][0] = num;//αποθήλευεση του στοιχείου
        pl[key]+=1;//αύξηση του πλήθους των στοιχείων της συγκεκριμένης θέσης κάτα 1
    }
    else//η θέση δεν είναι άδεια
    {
        pl[key]+=1;//αύξηση του πλήθους των στοιχείων της θέσης αυτής κατά 1
        int *h;//βοηθητικός πίνακας

        h = new int[pl[key]];//δυναμική δέσμευση για το νέο πίνακα της θέσης key
        for(i=0;i<pl[key]-1;i++)
            h[i]=hast[key][i];//αντιγραφή των στοιχείων του παλιού πίνακα

        h[pl[key]-1]=num;//αποθήκευση του νέου στοιχείου στο τέλος του νέου πίνακα
        delete[]hast[key];//διαγραφή του παλιού πίνακα τηε θέσης key

        hast[key]=new int[pl[key]];//νέα δέσμευση μνήμης για την θέση key
        for(i=0;i<pl[key];i++)
            hast[key][i]= h[i];//αποθήκυεση των στοιχείων στον νέο πίνακα
        delete []h;//αποδέσμευση μνήμης του βοηθητικού πίνακα
    }
    c2 = clock();
     c += float(c2 - c1) / CLOCKS_PER_SEC;
    o<<"The number:"<<num<<" was succesfully inserted int HashTable and the new HashTable is:";
    o<<" (it took "<<fixed << setprecision(6) <<double(c2-c1)/CLOCKS_PER_SEC<<" seconds to insert the value in the HashTable)"<<endl;
    for(i=0;i<sizeHASH;i++)
    {
         if(hast[i]!=nullptr)//αν δεν είναι NULL εμφανίζουμε τα στοιχεία της θέσης 
        {
                o<<"For the key:"<<HashFunction(hast[i][0])<<" the numbers are:";
                int j=0;
                for(j=0;j<pl[i];j++)
                    o<<hast[i][j]<<" ";
                o<<endl;
        }
    }
        for(i=0;i<20;i++)
            o<<"----";
        o<<endl;
    o.close();

}
