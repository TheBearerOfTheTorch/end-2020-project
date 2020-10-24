#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <sstream>

using namespace std;

//sorting function
string sort(int size,string names[])
{
    string temp;

    cout<<"The names are:"<<endl;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size-1;j++)
        {
            if(names[j]>names[j+1])
            {
                temp = names[j];
                names[j] = names[j+1];
                names[j+1] = temp;
            }
        }
    }
    //output the sorted names
    cout<<"The sorted names are:"<<endl;
    for(int i=0;i<size;i++)
    {
        cout<<names[i]<<endl;
    }
}
//menu function
char menu()
{
    //getting the name from the user
    cout<<"Enter your name"<<endl;
    string name;
    cin>>name;

    //menu
    cout<<"+--------------------------------------------------------------+"<<endl;
    cout<<"|                         WELCOME                              |"<<endl;
    cout<<"|         Botswana Ministry of Health COVID 19 Register        |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"+--------------------------------------------------------------+"<<endl;
    cout<<"                       GOOD DAY! "<<name<<"                     "<<endl;
    cout<<"+--------------------------------------------------------------+"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|               1. CAPTURE CONTACT DETAILS                     |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|               2. VIEW UNSORTED DATA                          |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|               3. VIEW SORTED DATA IN ASCENDING               |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|               4. SEARCH FOR A RECORD (omang/surname)         |"<<endl;
    cout<<"|                                                              |"<<endl;
    cout<<"|               5. EXIT                                        |"<<endl;
    cout<<"+--------------------------------------------------------------+"<<endl;

    cout<<"Choose service number"<<endl;
    char service;
    cin>>service;

    return service;
}

//saving the data to the database
string database(string firstname,string lastname,string location,int number,int bd,int bm,int by,int age,float temp)
{
    //checking for mysql connection
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"192.168.0.27","admin","admin","cplusplus",0,NULL,0);

    //check for connection
    if(conn)
    {
        //declaration
        int qstate = 0;
        stringstream ss;

        //inserting the data
        ss<<"INSERT INTO users(firstname,lastname,location,number,age,temperature) VALUES('"<<firstname<<"','"<<lastname<<"','"<<location<<"','"<<number<<"','"<<age<<"','"<<temp<<"')";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn,q);

        //checking for success
        if(qstate == 0)
        {
            cout<<"Record is inserted..."<<endl;
        }
        else
        {
            cout<<"Record failed to be saved to the database"<<endl;
        }

    }
    else
    {
        cout<<"Database not connect"<<endl;
    }
}
//capturing data
string dataCapture()
{
    //names
    cout<<"Enter first and last name"<<endl;
    string firstname,lastname;
    cin>>firstname>>lastname;

    //location
    cout<<"Enter location"<<endl;
    string location;
    cin>>location;

    //cell number
    cout<<"Enter cell number"<<endl;
    int num;
    cin>>num;

    //date of birth
    cout<<"Enter date of birth (days,month,year)"<<endl;
    int bd,bm,by;
    cin>>bd>>bm>>by;

    //present date
    cout<<"Enter present date (days,month,year)"<<endl;
    int pd,pm,py;
    cin>>pd>>pm>>py;

    //temperature
    cout<<"Enter temparature"<<endl;
    float temp;
    cin>>temp;

    //computing for the age
    int d, m, y;
    int md[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    y = py - by;
    if (pm < bm)
    {
        y--;
        m = 12 - (bm - pm);
    }
    else
    {
        m = pm - bm;
    }

    if (pd < bd)
    {
        m--;
        d = md[pm - 1] - (bd - pd);
    }
    else
    {d = pd - bd;}

    //calling the fucntion for the database
    database(firstname,lastname,location,num,bd,bm,by,y,temp);
}

//getting data from the database
string unsortedData()
{
    //checking for mysql connection
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"192.168.0.27","admin","admin","cplusplus",0,NULL,0);
    MYSQL_ROW row;
    MYSQL_RES* res;

    //checking for connection
    if(conn)
    {
        int qstate = mysql_query(conn,"SELECT * FROM users");

        if(!qstate)
        {
            //checking the result
            res = mysql_store_result(conn);

            cout<<"+-------+------------+---------------+---------------+--------------+---------+-------------+------------------------+"<<endl;
            cout<<"| userid| firstname  | lastname      | location      | number       | age     | temperature | time created           |"<<endl;
            cout<<"+-------+------------+---------------+---------------+--------------+---------+-------------+------------------------+"<<endl;
            while(row = mysql_fetch_row(res))
            {
                //displaying the database results
                cout<<"  "<<row[0]<<"      "<<row[1]<<"          "<<row[2]<<"           "<<row[3]<<"      "<<row[4]<<"        "<<row[5]<<"       "<<row[6]<<"          "<<row[7]<<endl;
            }
            cout<<"+------------------------------------------------------------------------------------------------------------------------+"<<endl;

        }
        else
        {
            cout<<"query has failed to retrieve information"<<endl;
        }
    }
    else
    {
        cout<<"theres no connection with the database"<<endl;
    }
}

//fucntion for displaying the sorted data from the database
string viewSortedData()
{
    //checking for mysql connection
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"192.168.0.27","admin","admin","cplusplus",0,NULL,0);
    MYSQL_ROW row;
    MYSQL_RES* res;

    //checking for connection
    if(conn)
    {
        int qstate = mysql_query(conn,"SELECT * FROM users ORDER BY firstname");

        if(!qstate)
        {
            //checking the result
            res = mysql_store_result(conn);

            cout<<"+-------+------------+---------------+---------------+--------------+---------+-------------+------------------------+"<<endl;
            cout<<"| userid| firstname  | lastname      | location      | number       | age     | temperature | time created           |"<<endl;
            cout<<"+-------+------------+---------------+---------------+--------------+---------+-------------+------------------------+"<<endl;
            while(row = mysql_fetch_row(res))
            {
                //displaying the database results
                cout<<"  "<<row[0]<<"      "<<row[1]<<"          "<<row[2]<<"           "<<row[3]<<"      "<<row[4]<<"        "<<row[5]<<"       "<<row[6]<<"          "<<row[7]<<endl;
            }
            cout<<"+--------------------------------------------------------------------------------------------------------------------+"<<endl;

        }
        else
        {
            cout<<"query has failed to retrieve information"<<endl;
        }
    }
    else
    {
        cout<<"theres no connection with the database"<<endl;
    }
}

//searching from the database
string searchUser(string value)
{
    //checking for mysql connection
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"192.168.0.27","admin","admin","cplusplus",0,NULL,0);
    MYSQL_ROW row;
    MYSQL_RES* res;

    //checking for connection
    if(conn)
    {
        //checking if the parameter passed is string or integer
        ostringstream strstr;
        strstr << "SELECT * FROM users WHERE lastname='" << value << "'";

        string str = strstr.str();
        int qstate = mysql_query(conn, str.c_str());


        if(!qstate)
        {
            //checking the result
            res = mysql_store_result(conn);
            cout<<"+---------+------------+---------------+----------------+--------------+---------+-------------+-------------------+"<<endl;
            cout<<"| userid  | firstname  | lastname      | location       | number       | age     | temperature | time created      |"<<endl;
            cout<<"+---------+------------+---------------+----------------+--------------+---------+-------------+-------------------+"<<endl;
            while(row = mysql_fetch_row(res))
            {
                //displaying the database results
                cout<<"     "<<row[0]<<"      "<<row[1]<<"          "<<row[2]<<"         "<<row[3]<<"      "<<row[4]<<"       "<<row[5]<<"       "<<row[6]<<"        "<<row[7]<<endl;
            }
            cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;

        }
        else
        {
            cout<<"query has failed to retrieve information"<<endl;
        }
    }
    else
    {
        cout<<"theres no connection with the database"<<endl;
    }
}
//search 2
string searchUser(int value)
{
    //checking for mysql connection
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"192.168.0.27","admin","admin","cplusplus",0,NULL,0);
    MYSQL_ROW row;
    MYSQL_RES* res;

    //checking for connection
    if(conn)
    {
        //checking if the parameter passed is string or integer
        ostringstream strstr;
        strstr << "SELECT * FROM users WHERE id='" << value << "'";

        string str = strstr.str();
        int qstate = mysql_query(conn, str.c_str());


        if(!qstate)
        {
            //checking the result
            res = mysql_store_result(conn);
            cout<<"+---------+------------+---------------+----------------+--------------+---------+-------------+-------------------+"<<endl;
            cout<<"| userid  | firstname  | lastname      | location       | number       | age     | temperature | time created      |"<<endl;
            cout<<"+---------+------------+---------------+----------------+--------------+---------+-------------+-------------------+"<<endl;
            while(row = mysql_fetch_row(res))
            {
                //displaying the database results
                cout<<"     "<<row[0]<<"      "<<row[1]<<"          "<<row[2]<<"         "<<row[3]<<"      "<<row[4]<<"       "<<row[5]<<"       "<<row[6]<<"        "<<row[7]<<endl;
            }
            cout<<"+------------------------------------------------------------------------------------------------------------------+"<<endl;

        }
        else
        {
            cout<<"query has failed to retrieve information"<<endl;
        }
    }
    else
    {
        cout<<"theres no connection with the database"<<endl;
    }
}
//for looping the project
string loopProject()
{
    //calling the menu method
    char service = menu();

    //checking the service chosen buy the user and rendering it
    switch(service)
    {
        case '1':
            cout<<"You opted for 1."<<endl;
            dataCapture();
            loopProject();
        case '2':
            cout<<"Viewing unsorted data"<<endl;
            unsortedData();
            loopProject();
        case '3':
            cout<<"View sorted data"<<endl;
            viewSortedData();
            loopProject();
        case '4':
            cout<<"+--------------------------------------------------------------+"<<endl;
            cout<<"|             search for a record by selecting below           |"<<endl;
            cout<<"+--------------------------------------------------------------+"<<endl;
            cout<<"|             1. use surname to search                         |"<<endl;
            cout<<"|                                                              |"<<endl;
            cout<<"|             2. use id to search                           |"<<endl;
            cout<<"+--------------------------------------------------------------+"<<endl;
            cout<<"choose from above what you will be searching with"<<endl;
            int para;
            cin>>para;

            //checking for what the user has opted to search with
            switch(para)
            {
                case 1:
                {
                    cout<<"You have opted to search with surname Enter the name to search records"<<endl;
                    string name;
                    cin>>name;
                    //passing the value to the search function
                    searchUser(name);
                    break;
                }

                case 2:
                {
                    cout<<"You have opted to search with id ,Enter the name to search records"<<endl;
                    int id;
                    cin>>id;

                    //passing value to the search function
                    searchUser(id);
                    break;
                }

                default:
                    cout<<"The number you have choosen is invalid"<<endl;
            }
            loopProject();
        case '5':
            cout<<"Thank you for using our application! Good Bye!!!"<<endl;
            exit;
            exit;
        default:
            cout<<"The number entered is invalid. choose from the menu"<<endl;
            loopProject();
    }
}
int main()
{
    //recursive function
    loopProject();
    return 0;
}



