#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#
using namespace std;
#define Null -32
#define Up 72
#define Down 80
#define Home 71
#define End 79
#define Enter 13

void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}
void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

int compar(char a[],char b[])
{
    int x = 0;
    for(int i = 0; a[i] != '\0'; i++)
    {
        if( (int)a[x] < (int)b[x] )
            return 1;
        else if( (int)a[x] == (int)b[x] )
            x++;
    }
    return 0;
}

int countDigit(long x)
{
    int NumberOfDigigt = 0;
    while( x != 0 )
    {
        x /= 10;
        NumberOfDigigt++;
    }
    return NumberOfDigigt;
}

void swap(int &x,int&y)
{
    int z;
    z = x;
    x = y;
    y = z;
}

struct node
{
    char name[20];
    long phone[2];
    node* next;
    node* prev;
};

class LinkedList
{
    node* head,*tail;
public:

    LinkedList()
    {
        head = tail = NULL;
    }

    void append( char name[],long phone)
    {
        if( (strlen(name) <10) || ((strlen(name)) >20) || ( countDigit(phone) != 10 ) )
        {
            gotoxy(40,11);
            cout<<"Cannot Add Invalid Input (-_-)"<<endl;
        }
        else
        {
            node* temp = new node();
            temp->phone[0] = phone;
            temp->phone[1] = 0;
            strcpy( temp->name, name );

            if(head == NULL)
            {
                head = temp;
                tail = temp;
                temp->prev =NULL;
                temp->next =NULL;
            }
            else
            {
                temp->prev = tail;
                temp->next = NULL;
                tail->next = temp;
                tail = temp;
            }
        }
    }

    void append(char name[], long phone1, long phone2)
    {
        if( phone1 == phone2 || ((strlen(name)) < 10||(strlen(name)) > 20) || (countDigit(phone1) != 10 || countDigit(phone2) != 10 ) )
        {
            gotoxy(40,15);
            cout<<"Cannot Add Invalid Input (-_-)"<<endl;
        }
        else
        {
            node* temp = new node();
            temp->phone[0] = phone1;
            temp->phone[1] = phone2;
            strcpy( temp->name, name );
            if( head == NULL )
            {
                head = temp;
                tail = temp;
                temp->prev = NULL;
                temp->next = NULL;
            }
            else
            {
                temp->prev = tail;
                temp->next = NULL;
                tail->next = temp;
                tail = temp;
            }
        }
    }

    void display()
    {
        node* temp = new node();
        temp = head;
        while( temp != NULL)
        {
            cout<<"Name : "<< temp->name;
            cout<<"\t|   Phone(1) : 0"<< temp->phone[0];
            cout<<"\t|   Phone(2) : 0"<< temp->phone[1] <<"\t"<<endl;
            temp = temp->next;
        }
    }

    void display2()
    {
        node* temp = new node();
        temp = tail;
        while( temp != NULL )
        {
            cout<<"Name : "<<temp->name;
            cout<<"\t|   Phone(1) : 0"<<temp->phone[0];
            cout<<"\t|   Phone(2) : 0"<<temp->phone[1]<<"\t"<<endl;
            temp = temp->prev;
        }
    }

    void saveInFile()
    {
        node* temp = new node();
        temp = head;
        ofstream myfile ("Contact.txt",ios::trunc);
        while( temp != NULL )
        {
            if (myfile.is_open())
            {
                for( int i = 0; i < strlen( temp->name ); i++ )
                {
                    if( temp->name[i] == ' ' )
                        temp->name[i] = '_';
                }
                myfile <<temp->name<<" "<<temp->phone[0]<<" "<<temp->phone[1]<<endl;
            }
            else cout << "Unable to Open File (-_-)";
            // cout<<"name : "<<temp->name<<"\tphone(1) : "<<temp->phone[0]<<"\tphone(2) : "<<temp->phone[1]<<"\t\n";
            temp = temp->next;
        }
        myfile.close();
    }

    void loadFromFile()
    {
        string line;
        int phone,phone2;
        char name[20];
        ifstream myfile ("Contact.txt");
        if ( myfile.is_open() )
        {
            while ( !myfile.eof() )
            {
                //prevent dublication of last line

                while( (myfile>>name>>phone>>phone2).good() )
                {
                    for(int i = 0; i < strlen(name); i++)
                    {
                        if(name[i] == '_')
                            name[i] = ' ';
                    }
                    cout<<"phone 2"<<phone2;
                    if(phone2>0)

                        append(name,phone,phone2);


                    else if(phone2==0)
                        append(name, phone);

                }
            }
            myfile.close();
        }
        else cout << "Unable to Open File";
        myfile.close();
    }

    //****

    void saveInFile2()
    {
        node* temp = new node();
        temp = head;
        ofstream myfile ("calledlist.txt",ios::trunc);
        while( temp != NULL )
        {
            if (myfile.is_open())
            {
                for( int i = 0; i < strlen( temp->name ); i++ )
                {
                    if( temp->name[i] == ' ' )
                        temp->name[i] = '_';
                }
                myfile <<temp->name<<" "<<temp->phone[0]<<" "<<temp->phone[1]<<endl;
            }
            else cout << "Unable to Open File (-_-)";
            // cout<<"name : "<<temp->name<<"\tphone(1) : "<<temp->phone[0]<<"\tphone(2) : "<<temp->phone[1]<<"\t\n";
            temp = temp->next;
        }
        myfile.close();
    }

    void loadFromFile2()
    {
        string line;
        int phone,phone2;
        char name[20];
        ifstream myfile ("calledlist.txt");
        if ( myfile.is_open() )
        {
            while ( !myfile.eof() )
            {
                //prevent dublication of last line

                while( (myfile>>name>>phone>>phone2).good() )
                {
                    for(int i = 0; i < strlen(name); i++)
                    {
                        if(name[i] == '_')
                            name[i] = ' ';
                    }
                    cout<<"phone 2"<<phone2;
                    if(phone2>0)

                        append(name,phone,phone2);


                    else if(phone2==0)
                        append(name, phone);

                }
            }
            myfile.close();
        }
        else cout << "Unable to Open File";
        myfile.close();
    }

    //****

    int countt()
    {
        int counter = 0;
        node*temp = head;
        while( temp != NULL )
        {
            counter++;
            temp = temp->next;
        }
        return counter;
    }

    node* searchByName(char name[])
    {
        node* temp = head;
        while( temp != NULL )
        {
            if( !strcmp( name, temp->name ) )
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }
    node* searchByPhone(long phone)
    {
        node* temp = head;
        while( temp != NULL )
        {
            if( phone == temp->phone[0] || phone == temp->phone[1] )
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void deleteByName(char name[])
    {
        node* temp = searchByName(name);
        if(temp == NULL)
        {
            return;
        }
        else if( head == tail )
        {
            delete temp;
            head = tail = NULL;
        }
        else if( temp == head )
        {
            head = temp->next;
            head->prev = NULL;
        }
        else if( temp == tail )
        {
            tail = temp->prev;
            tail->next = NULL;
        }
        else
        {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
        }
        delete temp;
    }

    void deleteByPhone(long phone)
    {
        node* temp = searchByPhone(phone);
        if( temp == NULL )
        {
            return;
        }
        else if( head == tail )
        {
            head = tail = NULL;
        }
        else if( temp == head )
        {
            head = temp->next;
            head->prev = NULL;
        }
        else if(temp == tail)
        {
            tail = temp->prev;
            tail->next = NULL;
        }
        else
        {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
        }
        delete temp;
    }

    void modify(char name[])
    {
        char x;
        node* temp = searchByName(name);
        system("Cls");
        gotoxy(30,2);
        cout<<"****************************************"<<endl;
        gotoxy(45,3);
        cout<<"Search Result"<<endl;
        gotoxy(30,4);
        cout<<"****************************************"<<endl;
        gotoxy(40,6);
        cout<<"You Modified By Name."<<endl;
        gotoxy(40,9);
        cout<<"Name : "<<temp->name<<endl<<endl;
        gotoxy(40,10);
        cout<<"Phone(1): "<<temp->phone[0]<<endl;
        gotoxy(40,11);
        cout<<"Phone(2): "<<temp->phone[1]<<endl;
        gotoxy(40,13);
        cout<<"Press (1) To Modify Name "<<endl;
        gotoxy(40,14);
        cout<<"Press (2) To Modify Phone(1)"<<endl;
        gotoxy(40,15);
        cout<<"Press (3) To Modify Phone(2)"<<endl;
        gotoxy(40,16);
        cout<<"Press (0) To Delete Contact"<<endl;
        gotoxy(40,17);
        x = _getch();

        if( x == '1' )
        {
            char newname[20] ;

            system("Cls");
            gotoxy(30,2);
            cout<<"****************************************"<<endl;
            gotoxy(45,3);
            cout<<"Search Result"<<endl;
            gotoxy(30,4);
            cout<<"****************************************"<<endl;
            gotoxy(40,6);
            cout<<"You Modified By Name."<<endl;
            gotoxy(40,8);
            cout<<"Old Name : "<<temp->name<<endl<<endl;
            gotoxy(40,9);
            cout<<"Enter New Name : ";
            gets(newname);
            _flushall();
            strcpy( temp->name, newname);
        }
        else if( x == '2' )
        {
            long phone1;
            system("Cls");
            gotoxy(30,2);
            cout<<"****************************************"<<endl;
            gotoxy(45,3);
            cout<<"Search Result"<<endl;
            gotoxy(30,4);
            cout<<"****************************************"<<endl;
            gotoxy(40,6);
            cout<<"You Modified By Name."<<endl;
            gotoxy(40,8);
            cout<<"Old Phone (1) : 0"<<temp->phone[0]<<endl<<endl;
            gotoxy(40,9);
            cout<<"Enter New Phone(1) : 0";
            cin>>phone1;
            temp->phone[0] = phone1;
        }
        else if( x == '3' )
        {
            long phone2;
            system("Cls");
            gotoxy(30,2);
            cout<<"****************************************"<<endl;
            gotoxy(45,3);
            cout<<"Search Result"<<endl;
            gotoxy(30,4);
            cout<<"****************************************"<<endl;
            gotoxy(40,6);
            cout<<"You Modified By Name."<<endl;
            gotoxy(40,8);
            cout<<"Old Phone (2) : 0"<<temp->phone[1]<<endl<<endl;
            gotoxy(40,9);
            cout<<"Enter New Phone(1) : 0";
            cin>>phone2;
            temp->phone[1] = phone2;
        }
        else if( x == '0' )
        {
            deleteByName(temp->name);
        }
        else
        {
            return;
        }
        _flushall();
    }

    void modify(long phone)
    {
        char x;
        node* temp = searchByPhone(phone);
        system("Cls");
        gotoxy(30,2);
        cout<<"****************************************"<<endl;
        gotoxy(45,3);
        cout<<"Search Result"<<endl;
        gotoxy(30,4);
        cout<<"****************************************"<<endl;
        gotoxy(40,6);
        cout<<"You Modified By Name."<<endl;
        gotoxy(40,9);
        cout<<"Name : "<<temp->name<<endl<<endl;
        gotoxy(40,10);
        cout<<"Phone(1): "<<temp->phone[0]<<endl;
        gotoxy(40,11);
        cout<<"Phone(2): "<<temp->phone[1]<<endl;
        gotoxy(40,13);
        cout<<"Press (1) To Modify Name "<<endl;
        gotoxy(40,14);
        cout<<"Press (2) To Modify Phone(1)"<<endl;
        gotoxy(40,15);
        cout<<"Press (3) To Modify Phone(2)"<<endl;
        gotoxy(40,16);
        cout<<"Press (0) To Delete Contact"<<endl;
        x=_getch();

        if( x == '1' )
        {
            char newname[20] ;
            system("Cls");
            gotoxy(30,2);
            cout<<"****************************************"<<endl;
            gotoxy(45,3);
            cout<<"Search Result"<<endl;
            gotoxy(30,4);
            cout<<"****************************************"<<endl;
            gotoxy(40,6);
            cout<<"You Modified By Name."<<endl;
            gotoxy(40,8);
            cout<<"Old Name : "<<temp->name<<endl<<endl;
            gotoxy(40,9);
            cout<<"Enter New Name : ";
            _flushall();
            gets(newname);
            //cin>>newname;
            strcpy(temp->name,newname);
        }
        else if( x == '2' )
        {
            long phone1;
            system("Cls");
            gotoxy(30,2);
            cout<<"****************************************"<<endl;
            gotoxy(45,3);
            cout<<"Search Result"<<endl;
            gotoxy(30,4);
            cout<<"****************************************"<<endl;
            gotoxy(40,6);
            cout<<"You Modified By Name."<<endl;
            gotoxy(40,8);
            cout<<"Old Phone (1) : 0"<<temp->phone[0]<<endl<<endl;
            gotoxy(40,9);
            cout<<"Enter New Phone(1) : 0";
            cin>>phone1;
            temp->phone[0] = phone1;
        }
        else if( x == '3' )
        {
            long phone2;
            system("Cls");
            gotoxy(30,2);
            cout<<"****************************************"<<endl;
            gotoxy(45,3);
            cout<<"Search Result"<<endl;
            gotoxy(30,4);
            cout<<"****************************************"<<endl;
            gotoxy(40,6);
            cout<<"You Modified By Name."<<endl;
            gotoxy(40,8);
            cout<<"Old Phone (1) : 0"<<temp->phone[1]<<endl<<endl;
            gotoxy(40,9);
            cout<<"Enter New Phone(1) : 0";
            cin>>phone2;
            temp->phone[1] = phone2;
        }
        else if( x == '0' )
        {
            deleteByName(temp->name);
        }
        else
        {
            return;
        }
        _flushall();
    }

    node* operator[](int i)
    {
        int counter = 0;
        node* temp = head;
        while( temp != NULL )
        {
            if( counter == i )
                return temp;
            else
                temp = temp->next;
            counter++;
        }
        return NULL;
    }


    void deleteAll()
    {
        node* temp = head;
        while(temp!=NULL)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    ~LinkedList()
    {
        deleteAll();
    }
};

void bubbleSort(LinkedList &temp)
{
    int flage = 0;
    for( int i = (temp.countt()) - 1 ; i > 0; i-- )
    {
        flage = 0;
        for( int j = 0; j < i; j++ )
        {
            if( compar( (temp[j])->name, (temp[j+1])->name ) ==0 )
            {
                swap((temp[j])->name, (temp[j+1])->name);
                swap((temp[j])->phone[0], (temp[j+1])->phone[0]);
                swap((temp[j])->phone[1], (temp[j+1])->phone[1]);
            }
            flage = 1;
        }
        if(flage == 0 )
        {
            break;
        }
    }
}

int main()
{
    LinkedList base , calledList;
    base.loadFromFile();
    calledList.loadFromFile2();
    char menu[7][15] = {"Call","Add Contact","Search","Modify","All Contact","All Calls","Exit And Save"};
    int i, current = 0;
    char ch;
    int flag = 0;
    system("cls");
    do
    {
        system("cls");
        for( i = 0; i < 7; i++)
        {
            if( i == current )
            {
                textattr(0x65);
            }
            gotoxy( 35, 8+i*3 );
            _cprintf("%s",menu[i]);
            textattr(0x07);
        }
        ch=_getch();
        switch(ch)
        {
        case Null:
            ch = _getch();
            switch(ch)
            {
            case Up:
                current--;
                if( current < 0 )
                {
                    current = 6;
                }
                break;
            case Down:
                current++;
                if( current > 6 )
                {
                    current = 0 ;
                }
                break;
            case Home:

                break;
            case End:

                break;
            }
            break;
        case Enter:
            switch(current)
            {
            case 0: //Call
                system("cls");
                bubbleSort(base);
                base.display();
                char a ;
                gotoxy(40,10);
                cout<<"Insert Your Choice... "<<endl;
                gotoxy(40,11);
                cout<<"Press (1) To Call By Name"<<endl;
                gotoxy(40,12);
                cout<<"Press (2) To Call By Phone"<<endl;
                gotoxy(40,13);
                a=_getch();
                if( a == '1' )
                {
                    char name[20];
                    gotoxy(40,13);
                    cout<<"Enter Name : ";
                    gotoxy(52,13);
                    gets(name);
                    _flushall();
                    node *temp = base.searchByName(name);
                    if( temp != NULL )
                    {
                        system("Cls");
                        gotoxy(40,12);
                        cout<<temp->name<<endl;
                        gotoxy(40,13);
                        cout<<temp->phone[0]<<endl;
                        gotoxy(40,15);
                        cout<<"\tCalling... (^_^)"<<endl;

                        calledList.append( temp->name, temp->phone[0] );
                    }
                    else
                    {
                        gotoxy(40,14);
                        cout<<"Not Exist (-_-)"<<endl;
                    }
                }
                else if( a == '2' )
                {
                    long phone;
                    cout<<"Enter Phone Number : 0";
                    cin>>phone;
                    node *temp = base.searchByPhone(phone);
                    if(temp != NULL)
                    {
                        system("Cls");
                        gotoxy(40,12);
                        cout<<temp->name<<endl;
                        gotoxy(40,13);
                        cout<<temp->phone[0]<<endl;
                        gotoxy(40,15);
                        cout<<"\tCalling... (^_^)"<<endl;
                        calledList.append( temp->name, temp->phone[0] );
                    }
                    else
                    {
                        gotoxy(40,14);
                        cout<<"Not Exist"<<endl;
                    }
                }
                //gotoxy(40,15);
                //cout<<"Invalid Input"<<endl;
                gotoxy(35,18);
                cout<<"Press Any Key To Return To Main Menu."<<endl;
                gotoxy(72,18);
                _getch();
                break;

            case 1: //Add New Contact
                system("cls");
                char name[20];
                long phone1;
                gotoxy(40,2);
                cout<<"********************"<<endl;
                gotoxy(42,3);
                cout<<"Add New Contact"<<endl;
                gotoxy(40,4);
                cout<<"********************"<<endl;
                gotoxy(40,6);
                cout<<"Enter Name : ";
                gets(name);
                gotoxy(40,7);
                cout<<"Add phone(1) : 0";
                cin>>phone1;
                cout<<endl;
                _flushall();
                if(base.searchByPhone(phone1)!=NULL)
                {
                    gotoxy(40,15);
                    cout<<"Phone Is Already Exist (-_-)"<<endl;
                }
                else
                    base.append(name,phone1);
                gotoxy(35,18);
                cout<<"Press Any Key To Return To Main Menu."<<endl;
                gotoxy(72,18);
                _getch();
                break;

            case 2: //Search In All Contact
                system("cls");
                char x ;
                gotoxy(40,2);
                cout<<"********************"<<endl;
                gotoxy(38,3);
                cout<<"...Insert Your Choice..."<<endl;
                gotoxy(40,4);
                cout<<"********************"<<endl;
                gotoxy(35,6);
                cout<<"Press (1) To Search By Name."<<endl;
                gotoxy(35,7);
                cout<<"Press (2) To Search By Phone."<<endl;
                gotoxy(45,9);
                x = _getch();
                if( x == '1' )
                {
                    char name[20];
                    system("Cls");
                    gotoxy(37,2);
                    cout<<"********************"<<endl;
                    gotoxy(40,3);
                    cout<<"Search Result"<<endl;
                    gotoxy(37,4);
                    cout<<"********************"<<endl;
                    gotoxy(35,6);
                    cout<<"You Search By Name."<<endl;
                    gotoxy(40,9);
                    cout<<"Enter Name : ";
                    gets(name);
                    node *temp = base.searchByName(name);

                    if( temp != NULL )
                    {
                        gotoxy(40,11);
                        cout<<"Name : "<<temp->name<<endl;
                        gotoxy(40,12);
                        cout<<"Phone(1) : "<<temp->phone[0]<<endl;
                        gotoxy(40,13);
                        if(temp->phone[1]==NULL) {}
                        else
                            cout<<"Phone(2) : "<<temp->phone[1]<<endl;
                    }
                    else
                    {
                        gotoxy(40,11);
                        cout<<"Not Exist"<<endl;
                    }
                    //_getch();
                }
                else if( x == '2' )
                {
                    long phone;
                    system("Cls");
                    gotoxy(37,2);
                    cout<<"********************"<<endl;
                    gotoxy(40,3);
                    cout<<"Search Result"<<endl;
                    gotoxy(37,4);
                    cout<<"********************"<<endl;
                    gotoxy(35,6);
                    cout<<"You Search By Phone."<<endl;
                    gotoxy(40,9);

                    cout<<"Enter Phone : 0";
                    cin>>phone;
                    node *temp = base.searchByPhone(phone);
                    if( temp != NULL )
                    {
                        gotoxy(40,11);
                        cout<<"Name : "<<temp->name<<endl;
                        gotoxy(40,12);
                        cout<<"Phone(1) : "<<temp->phone[0]<<endl;
                        gotoxy(40,13);
                        cout<<"Phone(2) : "<<temp->phone[1]<<endl;
                    }
                    else
                    {
                        gotoxy(40,11);
                        cout<<"Not Exist (-_-)"<<endl;
                    }
                }
                else
                {
                    gotoxy(40,13);
                    cout<<"Invalid Input (-_-)!!!"<<endl;
                }
                gotoxy(35,18);
                cout<<"Press Any Key To Return To Main Menu."<<endl;
                gotoxy(72,18);
                _getch();
                break;
            case 3: //Modify Contact
                char xx ;
                system("cls");
                gotoxy(40,2);
                cout<<"********************"<<endl;
                gotoxy(38,3);
                cout<<"...Insert Your Choice..."<<endl;
                gotoxy(40,4);
                cout<<"********************"<<endl;
                gotoxy(35,6);
                cout<<"Press (1) To Search By Name."<<endl;
                gotoxy(35,7);
                cout<<"Press (2) To Search By Phone."<<endl;
                gotoxy(45,9);
                xx = _getch();
                _flushall();
                if( xx == '1' )
                {
                    char name[20];
                    cout<<"Enter Name : ";
                    gets(name);
                    _flushall();
                    node *temp = base.searchByName(name);
                    if(temp != NULL)
                        base.modify(name);
                    else
                    {
                        gotoxy(40,15);
                        cout<<"Not Exist (-_-)"<<endl;
                    }
                }
                else if( xx == '2' )
                {
                    long phone;
                    cout<<"Enter Phone : 0";
                    cin>>phone;
                    node *temp = base.searchByPhone(phone);
                    if(temp != NULL)
                        base.modify(phone);
                    else
                    {
                        gotoxy(40,15);
                        cout<<"Not Exist (-_-)"<<endl;
                    }
                }
                else
                {
                    gotoxy(40,15);
                    cout<<"Invalid Input (-_-)!!!"<<endl;
                }
                gotoxy(35,18);
                cout<<"Press Any Key To Return To Main Menu."<<endl;
                gotoxy(72,18);
                _getch();
                break;
            case 4: //Display All Contact Sorted
                system("cls");
                bubbleSort(base);
                base.display();
                _getch();
                break;
            case 5: //Display All Call Contact
                system("cls");
                calledList.display2();
                //gotoxy(35,15);
                cout<<endl<<"Press Any Key To Return To Main Menu."<<endl;
                gotoxy(72,18);
                _getch();
                break;
            case 6:
                system("cls");
                base.saveInFile();
                calledList.saveInFile2();
                gotoxy(40,10);
                cout<<"Data Saved To File. (^_^) .Successfully."<<endl;
                gotoxy(40,15);
                cout<<"Press Any Key To Return To Main Menu."<<endl;
                gotoxy(72,15);
                _getch();
                break;
            }
            break;
        case 27: //esc
            flag=1;
            break;
        }
    }
    while(flag == 0);

    return 0;
}
