#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

void MainMenueScreen();
void LoginUserScreen();
void QuickScreen();
void BalanceScreen();
void ShowNormalScrem();

const string FileName = "Client.txt";

enum ATMMainMenueScreen{Quick=1,Normal=2,Deposit=3,Check=4,Logout=5 };


struct stClient
{
    string AccountNumber;
    string PinCode;
    double AccountBalance;
    bool falg = false;
};
stClient stclienttyp;

vector<string>Spilt(string line, string del)
{
    vector<string>vString;
    string word;
    short pos = 0;
    while ((pos = line.find(del)) != std::string::npos)
    {
        word = line.substr(0, pos);
        if (word != " ")
            vString.push_back(word);
 
        line.erase(0, pos + del.length());
    }
    if (line != " ")
        vString.push_back(line);
    return vString;
}

stClient ReadRecord()
{
    stClient p;
    cout << "please enter the account number ?";
    getline(cin >> ws, p.AccountNumber);
    cout << "please enter the pin code ?";
    getline(cin, p.PinCode);
    cout << "please enter the balance ?";
    cin >> p.AccountBalance;
    return p;

}
string ConvertRecrodToLine(stClient p,string del="#//#")
{
    string line;
    line += p.AccountNumber+ del;
    line += p.PinCode + del;
    line += to_string(p.AccountBalance);
    return line;


}

//Add to file frist one 
void AddToFile(string line,string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << line << endl;
        MyFile.close();
    }
}
void add()
{
    stClient p = ReadRecord();
    AddToFile(ConvertRecrodToLine(p), FileName);
}


stClient ConvertLineToRecord(string line)
{
    vector<string>p;
    p = Spilt(line, "#//#");
    stClient v;

    v.AccountNumber = p[0];
    v.PinCode = p[1];
    v.AccountBalance = stoi(p[2]);
    return v;
}

vector<stClient>LoadFileToVector(string filename)
{
    vector<stClient>vClient;
    fstream MyFile;
    MyFile.open(filename, ios::in);
    if (MyFile.is_open())
    {
        string line;
        stClient p;
        while (getline(MyFile, line))
        {
            p = ConvertLineToRecord(line);
            vClient.push_back(p);

        }
        MyFile.close();
    }
    return vClient;
}
vector<stClient>SavaClientDateToFile(string filename, vector<stClient>oo)
{
    string line;
    fstream myfile;
    myfile.open(filename, ios::out);
    if (myfile.is_open())
    {
        for (stClient u : oo)
        {
            if (u.falg == false)
            {
                line = ConvertRecrodToLine(u);
                myfile << line << endl;
            }
        }
        myfile.close();
    }
    return oo;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClient>& vClients)
{
    
    char Answer = 'n';  
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";    
    
    cin >> Answer;
    
    if (Answer == 'y' || Answer == 'Y')
    {
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber) 
            {
                C.AccountBalance += Amount;
               SavaClientDateToFile(FileName, vClients);
               cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance; 
               
               return true;
            }
        }
        return false;
    }
}




short ReadQChooseATMMainMenue()
{
    short number;
    cout << "\nChoose what do you want to do ? [1 to 5] ?";
    cin >> number;
    return number;
}



bool FindAccountPinCode(string AccountNumber, string PinCode, stClient& p)
{
    vector<stClient>pop = LoadFileToVector(FileName);
    for (stClient o : pop)
    {
        if (o.AccountNumber == AccountNumber && o.PinCode == PinCode)
        {
            p = o;
            return true;
        }
    }
    return false;
}

/////////// Balance Screen 
void BalanceScreen()
{

  
    cout << "==============================================\n";
    cout << "\t\tCheck  Balance \n";
    cout << "==============================================\n";
    
        cout << "Your Balance is " << stclienttyp.AccountBalance;
    

}


int ReadQQuickWithdraw()
{
    int number;
    cout << "\n\nChoose what to withdraw from [1] to [8] ?";
        cin >> number;
        return number;
}

int ChooseQuickWithdraw(int number)
{
    switch (number)
    {
    case 1 :
        return 20;
    case 2:
        return 50;
       
    case 3:
        return 100;
  
    case 4:
        return 200;
       
    case 5:
        return 400;
    case 6:
        return 600;
      
    case 7:
        return 800;
       
    case 8:
        return 1000;
       
    case 9:
        system("cls");
        MainMenueScreen();
        break;
    default :
        return 0;

    }
 }


void QuickWithdraw()
{
   
   
    int number = ChooseQuickWithdraw(ReadQQuickWithdraw());
   
    if (number > stclienttyp.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice.\n";   
        cout << "\nPress Anykey to continue...";      
        system("pause>0");
        system("cls");
        QuickScreen(); 
        return;
    }
    
    vector<stClient>pop = LoadFileToVector(FileName);
    DepositBalanceToClientByAccountNumber(stclienttyp.AccountNumber, number * -1, pop);
    stclienttyp.AccountBalance -= number;
}
void QuickScreen()
{
    cout << "==============================================\n";
    cout << "\t\tQuick Withdraw\n";
    cout << "==============================================\n";
    cout << "\t[1] 20  \t[2] 50 \n";
    cout << "\t[3] 100 \t[4] 200\n";
    cout << "\t[5] 400 \t[6] 600\n";
    cout << "\t[7] 800 \t[8] 1000\n";
    cout << "\t[9] Exit \n";
    cout << "==============================================\n";
    cout << "Your Balance is " << stclienttyp.AccountBalance;
    QuickWithdraw();
}

void DepositScreen()
{
    short number;
    vector<stClient>pop = LoadFileToVector(FileName);
    cout << "==============================================\n";
    cout << "\t\tDepsoit  Screen\n";
    cout << "==============================================\n";
    cout << "Enter a positive Deposit Amount ? ";
    cin >> number;
    DepositBalanceToClientByAccountNumber(stclienttyp.AccountNumber, number, pop);
    stclienttyp.AccountBalance += number;
}




int ReadQNormalScreen()
{
   int number;
    cout << "\nEnter an amount multiple of 5's ? ";
    cin >> number;
   
    while (number % 5 != 0)
    {
        cout << "\nEnter an amount multiple of 5's ? ";
        cin >> number;

    }
    return number;

}
void NormalWithdrawScreen()
{
    int number = ReadQNormalScreen();
    
    if (number > stclienttyp.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice.\n";     
        cout << "\nPress Anykey to continue...\n";      
        system("pause>0");
        system("cls");
        ShowNormalScrem();
        return;
    }
    vector<stClient>pop = LoadFileToVector(FileName);
    DepositBalanceToClientByAccountNumber(stclienttyp.AccountNumber, number*-1, pop);
    stclienttyp.AccountBalance -= number;

}

void ShowNormalScrem()
{
    cout << "===========================================\n";
    cout << "\t\tNormal Withdraw Screen\n";
    cout << "===========================================\n";
    NormalWithdrawScreen();
}


////////////////// Login Screen
bool CheckLogin(string AccountNumber,string PinCode)
{
    fstream myfile;
    myfile.open(FileName, ios::in);
    if (myfile.is_open())
    {
        string line;
        stClient p;
        while (getline(myfile, line))
        {
            p = ConvertLineToRecord(line);
            if (p.AccountNumber == AccountNumber && p.PinCode == PinCode)
            {
                myfile.close();
                return true;
                
            }
        }

        myfile.close();
    }
    return false;
    

}
void LoginUserScreen()
{
    stClient p;
    cout << "==============================================\n";
    cout << "\t\tLogin User Screen\n";
    cout << "==============================================\n";
    cout << "\nPlease enter the Account Number ?";
    getline(cin>>ws, p.AccountNumber);
    cout << "\nplease enter the Pin Code ?";
    getline(cin, p.PinCode);
    while (!FindAccountPinCode(p.AccountNumber,p.PinCode,stclienttyp))
    {
        system("cls");
        cout << "==============================================\n";
        cout << "\t\tLogin User Screen\n";
        cout << "==============================================\n";
        cout << "Invalid Account Number/PinCode!";
        cout << "\nPlease enter the Account Number ?";
        getline(cin, p.AccountNumber);
        cout << "please enter the Pin Code ?";
        getline(cin, p.PinCode);

    }
    system("cls");
    MainMenueScreen();
}

void GoToBackMianMenue()
{
    cout << "\n\nPress any key to go back to main menue ...";
    system("pause>0");
    system("cls");
    MainMenueScreen();
}

void Choose1(ATMMainMenueScreen p)
{

    switch (p)
    {
    case ATMMainMenueScreen::Quick:
        system("cls");
        QuickScreen();
        GoToBackMianMenue();
        break;
    case ATMMainMenueScreen::Normal:
        system("cls");
        ShowNormalScrem();
        GoToBackMianMenue();
        break;
    case ATMMainMenueScreen::Deposit:
        system("cls");
        DepositScreen();
        GoToBackMianMenue();
        break;
    case ATMMainMenueScreen::Check:
        system("cls");
        BalanceScreen();
        GoToBackMianMenue();
        break;
    case ATMMainMenueScreen::Logout:
        system("cls");
        LoginUserScreen();
        break;
   
    }

}

void MainMenueScreen()
{
    cout << "==============================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "==============================================\n";
    cout <<"\n\t[1] Quick Withdraw";
    cout << "\n\t[2] Normal Withdraw";
    cout << "\n\t[3] Deposit ";
    cout << "\n\t[4] Check Balance ";
    cout <<"\n\t[5] Logout";
    cout << "\n==============================================\n";
    Choose1((ATMMainMenueScreen)ReadQChooseATMMainMenue());
}





int main()
{
    LoginUserScreen();
    
    system("pause>0");
}


