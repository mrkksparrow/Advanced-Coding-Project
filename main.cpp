#include <bits/stdc++.h>
using namespace std;

struct Details{
    string name;
    string dob;
    bool giftcard = false;
    string gfnumber;
    string gfpin;
    int reward=0;
    vector <string> history;
    string password;
    int topup = 0;
    int balance = 10000;
};

map<string,Details*> details;
map<string,Details*>::iterator itr;
static int spent=0;

class Login{
    private :
        string Acc_No;
        string Password;

    public :
        string getAccNo(){
            cin>>Acc_No;
            return Acc_No;
        }

        string getPassword(){
            cout<<"Enter ur Password : "<<endl;
            cin>>Password;
            return Password;
        }
};

class NewUser{
    private :
        string Acc_No;
        string Password;
        string name;
        string dob;

    public :
        string getAccNo(){
            cin>>Acc_No;
            return Acc_No;
        }

        string getPassword(){
            cout<<"Enter any Password : "<<endl;
            cin>>Password;
            cin.ignore();
            return Password;
        }
        
        string getName(){
            cout<<"Enter ur Name : "<<endl;
            getline(cin,name);
            return name;
        }

        string getDob(){
            cout<<"Enter ur DOB : dd/mm/yy "<<endl;
            cin>>dob;
            return dob;
        }

};

void UpdateTransaction(string Acc_No, int amt){
    itr = details.find(Acc_No);
    string h;
    h = to_string(itr->second->topup)+" - "+to_string(amt)+" = "+to_string(itr->second->topup-amt);
    itr->second->history.push_back(h);
    itr->second->topup -= amt;
}

void CreateGiftCard(string Acc_No){
    itr = details.find(Acc_No);
    if(itr->second->giftcard==true){
        cout<<"Gift Card Already Created"<<endl;
    }
    else{
        itr->second->giftcard = true;
        itr->second->gfnumber = Acc_No.substr(0,5);
        cout<<"Enter 4-digit for ur gift card "<<endl;
        cin>>itr->second->gfpin;
        cout<<"-------------------------------"<<endl
            <<"Gift card Number : "<<itr->second->gfnumber<<endl
            <<"Gift card Pin : "<<itr->second->gfpin<<endl
            <<"-------------------------------"<<endl;
        cout<<"Gift Card Created"<<endl;
    }
}

void TopUp(string Acc_No){
    itr = details.find(Acc_No);
    if (itr->second->giftcard==true){
        cout<<"Enter the amount for TopUp"<<endl;
        int amt;
        do{
            cin>>amt;
            if(itr->second->balance>=amt){
                itr->second->topup += amt;
                itr->second->balance -= amt;

                string h = to_string(itr->second->balance+amt)+" - "+to_string(amt)+" = "+to_string(itr->second->balance);
                itr->second->history.push_back(h);

                cout<<"Gift Card Created"<<endl;
                cout<<"-------------------------------"<<endl
                    <<"Gift Card Number : "<<itr->second->gfnumber<<endl
                    <<"Gift Card Pin : "<<itr->second->gfpin<<endl
                    <<"Gift Card Balance : "<<itr->second->topup<<endl
                    <<"-------------------------------"<<endl;
            }
            else{
                cout<<"Please enter amount lesser or equal to ur account balance"<<endl;
            }
        }while(!itr->second->balance>=amt);
    }
    else{
        cout<<"Please first Create ur Gift Card "<<endl;
    }
}

void BlockGiftCard(string Acc_No){
    itr = details.find(Acc_No);
    cout<<"Are you sure to block ur Gift Card"<<endl<<"1. Yes"<<endl<<"2. No"<<endl;
    int choice;
    cin>>choice;
    if(choice){
        itr->second->gfnumber="";
        itr->second->gfpin="";
        itr->second->giftcard=false;
        itr->second->balance += itr->second->topup;

        string h = to_string(itr->second->balance+itr->second->topup)+" + "+to_string(itr->second->topup)+" = "+to_string(itr->second->balance);
        itr->second->history.push_back(h);

        itr->second->topup = 0;
        cout<<"Gift Card Blocked, Gift Card Balance added to ur main Balance"<<endl;
    }
    else{
        return ;
    }
}

void Transaction(string Acc_No){
    itr = details.find(Acc_No);
    cout<<"----------------------------------------"<<endl
        <<"Transaction done in this Account : "<<endl;
    for(auto &it : itr->second->history){
        cout<<it<<endl;
    }
    cout<<"----------------------------------------"<<endl;
}

void Dashboard(string Acc_No){
    int choice;
    do{
        itr = details.find(Acc_No);
        cout<<"-------------------------------"<<endl;
        cout<<"Account No : "<<itr->first<<endl;
        cout<<"Name : "<<itr->second->name<<endl;
        cout<<"DOB : "<<itr->second->dob<<endl;
        cout<<"Balance : "<<itr->second->balance<<endl;
        if(itr->second->giftcard==true){
            cout<<"Gift Card Number : "<<itr->second->gfnumber<<endl;
            cout<<"Gift Card balance : "<<itr->second->topup<<endl;
        }
        else{
            cout<<"Gift Card Status : Blocked"<<endl;
        }
        cout<<"-------------------------------"<<endl;
        cout<<"Select ur option"<<endl
            <<"1. Create Gift Card"<<endl
            <<"2. TopUp"<<endl
            <<"3. Transaction History"<<endl
            <<"4. Block"<<endl
            <<"0. Logout"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                CreateGiftCard(Acc_No);
                break;
            
            case 2:
                TopUp(Acc_No);
                break;

            case 3:
                Transaction(Acc_No);
                break;

            case 4:
                BlockGiftCard(Acc_No);
                break;

            case 0:
                cout<<"Logging Out"<<endl;
                break;
            
            default :
                cout<<"Enter correct input"<<endl;
                break;
        }
    }while(choice!=0);
}

bool Authentication(string Acc_no, string Password){
    itr = details.find(Acc_no);
    if(Password==itr->second->password){
        return 1;
    }
    else{
        return 0;
    }
}

bool AccNoExist(string Acc_No){
    if(details.find(Acc_No)==details.end()){
        return 0;
    }
    else{
        return 1;
    }
}

void Loginn(){
    string Acc_No;
    string Password;

    Login loginobj;
    Acc_No = loginobj.getAccNo();

    while(!AccNoExist(Acc_No)){
        cout<<"Enter valid Account Number : "<<endl;
        Acc_No = loginobj.getAccNo();
    }

    Password = loginobj.getPassword();
    while(!Authentication(Acc_No, Password)){
        cout<<"Enter correct Password : "<<endl;
        Password = loginobj.getPassword();
    }
    cout<<"Login Successfull"<<endl;
    Dashboard(Acc_No);
    
}

void NewUserr(){
    string Acc_No;
    string Password;
    NewUser newuser_obj;
    Acc_No = newuser_obj.getAccNo();
    //cout<<Acc_No<<endl;
    while(AccNoExist(Acc_No)){
        cout<<"Account Number already taken, Please enter another Account Number"<<endl;
        Acc_No = newuser_obj.getAccNo();
    }

    Details* temp = new Details();
    temp->password = newuser_obj.getPassword();
    temp->name = newuser_obj.getName();
    temp->dob = newuser_obj.getDob();

    details.insert(pair<string,Details*>(Acc_No, temp));
    cout<<"Account created Successfully"<<endl;
}

bool Buy(string Acc_No, int amt){
    itr = details.find(Acc_No);
    if(itr->second->topup>=amt){
        UpdateTransaction(Acc_No, amt);
        //itr->second->topup -= amt;
        spent += amt;
        if(spent/100>=1){
            //UpdateTransaction(Acc_No, -spent/100);
            itr->second->reward += spent/100;
            spent %= 100;
        }
        if(itr->second->reward>=10){
            //UpdateTransaction(Acc_No, (itr->second->reward/10)*10);
            string h = to_string(itr->second->balance)+" + "+to_string((itr->second->reward/10)*10)+" = "+to_string(itr->second->balance+(itr->second->reward/10)*10);
            itr->second->history.push_back(h);
            itr->second->balance += (itr->second->reward/10)*10;
            itr->second->reward %= 10;
        }
        return 1;
    }
    else{
        cout<<"Insufficeient Balance "<<endl;
        return 0;
    }

}

void StoreRoom(string Acc_No){
    itr = details.find(Acc_No);
    int choice;
    do{
        cout<<"Buy what you want"<<endl
            <<"1. Nike Shoe - Rs.700"<<endl
            <<"2. Poco F1 Phone - Rs.3200"<<endl
            <<"3. OnePlus EarBuds - Rs.1400"<<endl
            <<"0. Exit"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                if(Buy(Acc_No, 700)){
                    cout<<"Nike Shoe Purchased, Happy Shopping"<<endl;
                }
            
            case 2:
                if(Buy(Acc_No, 3200)){
                    cout<<"Poco F1 Phone Purchased, Happy Shopping"<<endl;
                }
            
            case 3:
                if(Buy(Acc_No, 1400)){
                    cout<<"OnePlus EarBuds Purchased, Happy Shopping"<<endl;
                }
            
            case 0:
                cout<<"Thank You for Shopping"<<endl;
        }
    }
    while(choice!=0);
}

void Purchasee(){
    string Acc_No;
    string Password;

    Login loginobj;
    Acc_No = loginobj.getAccNo();

    while(!AccNoExist(Acc_No)){
        cout<<"Enter valid Account Number : "<<endl;
        Acc_No = loginobj.getAccNo();
    }

    Password = loginobj.getPassword();
    while(!Authentication(Acc_No, Password)){
        cout<<"Enter correct Password : "<<endl;
        Password = loginobj.getPassword();
    }
    cout<<"Login Successfull"<<endl;
    StoreRoom(Acc_No);
}

int main(){
    //details.insert(pair<string,Details*>("123456789","password"));
    cout<<"-------------------------------"<<endl
        <<"Welcome to Zoho Bank of India"<<endl
        <<"-------------------------------"<<endl;
    int choice;
    do{
        cout<<"Select ur option"<<endl
            <<"1. Account Login"<<endl
            <<"2. Register"<<endl
            <<"3. Purchase"<<endl
            <<"0. Exit"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"Enter ur Account Number : "<<endl;
                Loginn();
                break;
            
            case 2:
                cout<<"Enter ur choice of Account Number : "<<endl;
                NewUserr();
                break;

            case 3:
                cout<<"Enter ur Account Number : "<<endl;
                Purchasee();
                break;
            
            case 0:
                cout<<"------------------------------------------"<<endl
                    <<"Thank you for using Zoho Bank of India"<<endl
                    <<"Have a Great Day"<<endl
                    <<"------------------------------------------"<<endl;
            
            default :
                cout<<"Enter correct input"<<endl;
                break;
        }
    }while(choice!=0);
    return 0;
}
