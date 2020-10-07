
# include<iostream>
# include<fstream>
# include<iomanip>
using namespace std;

class account
{
	int acc_no;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//function to get data from user
	void show_account();	//function to show data on screen
	void add_balance(int);	//function to accept amount and add to balance amount
	void draw_balance(int);	//function to accept amount and subtract from balance amount
	void report();	//function to show data in tabular format
	int get_acc();	//function to return account number
	int get_deposit();	//function to return balance amount
	char get_type();	//function to return type of account
};         //class ends here

void account::create_account()
{
	cout<<"\nEnter the Account Number :";
	cin>>acc_no;
	cout<<"\n\nEnter the Name of the account holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount to deposit =  ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account()
{
	cout<<"\nAccount No. : "<<acc_no;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}
	
void account::add_balance(int x)
{
	deposit+=x;
}
	
void account::draw_balance(int x)
{
	deposit-=x;
}
	
void account::report() 
{
	cout<<acc_no<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(10)<<deposit<<endl;
}

int account::get_acc()
{
	return acc_no;
}

int account::get_deposit() 
{
	return deposit;
}

char account::get_type()
{
	return type;
}


// function declaration
void write_account();	//function to write record in binary file
void display_acc(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function

// main function of the program
int main()
{
	char var;
	int num;
	while (true){
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. NEW ACCOUNT";
		cout<<"\n\n\t2. DEPOSIT AMOUNT";
		cout<<"\n\n\t3. WITHDRAW AMOUNT";
		cout<<"\n\n\t4. BALANCE ENQUIRY";
		cout<<"\n\n\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t6. EXIT";
		cout<<"\n\n\tSelect Your Option\n";
		cin>>var;
		switch(var)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter the account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter the account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter the account No. : "; cin>>num;
			display_acc(num);
			break;
		case '5':
			display_all();
			break;
		 case '6':
			cout<<"\n\n\tThanks for using bank management system.\n";
			break;
		 default :cout<<"Invalid input"<<endl;
		}
		if (var == '6' )
		break;
		
	}
	return 0;
}


// function to create a new account
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account_details.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(ac));
	outFile.close();
}

// function to display account details, acc no is passed as argument
void display_acc(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account_details.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read((char *) &ac, sizeof(ac)))
	{
		if(ac.get_acc()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount does not exist";
}

// function to display everybody's details
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account_details.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *) &ac, sizeof(ac)))
	{
		ac.report();
	}
	inFile.close();
}

//function to either withdraw or deposit 
void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.details", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be opened !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read((char *) &ac, sizeof(account));
		if(ac.get_acc()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSIT AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.add_balance(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.get_deposit()-amt;
				if((bal<500 && ac.get_type()=='S') || (bal<1000 && ac.get_type()=='C'))
					cout<<"Insufficient balance";
				else
					ac.draw_balance(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			cout<<pos<<endl;
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(ac));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
