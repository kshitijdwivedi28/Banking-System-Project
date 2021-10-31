#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<fstream.h>
#include<ctype.h>
#include<process.h>
class account
{
 int acno;
 char name[50];
 int deposit, withdraw;
 char type;
 public:
	void create_account()
	{
	 cout<<"\nEnter The account No. ::";
	 cin>>acno;
	 cout<<"\n\nEnter The Name of The account Holder:: ";
	 gets(name);
	 cout<<"\nEnter Type of The account (C/S):: ";
	 cin>>type;
	 type=toupper(type);
	 cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ):: ";
	 cin>>deposit;
	 cout<<"\n\n\nAccount Created..";
	 }
	void modify_account()
	{
	 cout<<"\nModify Account No. ::  "<<acno;
	 cout<<"\nModify Account Holder Name :: ";
	 gets(name);
	 cout<<"\nModify Type of Account :: ";
	 cin>>type;
	 cout<<"\nModify Balance amount :: ";
	 cin>>deposit;
	 }

	void show_account()
	{
	 cout<<"\nAccount No. ::  "<<acno;
	 cout<<"\nAccount Holder Name ::  ";
	 puts(name);
	 cout<<"\nType of Account ::  "<<type;
	 cout<<"\nBalance amount ::  "<<deposit;
	 }


void dep(int x)
{
  deposit+=x;
}

void draw(int x)
{
  deposit-=x;
}

void report()
{  cout<<acno<<"\t"<<name<<"\t\t"<<type<<"\t\t"<<deposit<<endl;}

  int  retacno()
  { return acno;}

  float retdeposit()
  {return deposit;}

  char rettype()
  {return type;}

};
 fstream fp;
 account ac;

void write_account()
   {
    fp.open("account.dat",ios::out|ios::app);
    ac.create_account();
    fp.write((char*)&ac,sizeof(account));
    fp.close();
   }

void display_sp(int n)
{
    clrscr();
    cout<<"\nBALANCE DETAILS\n";
    int flag=0;
    fp.open("account.dat",ios::in);
    while(fp.read((char*)&ac,sizeof(account)))
	{
	 if(ac.retacno()==n)
		{
		 ac.show_account();
		 flag=1;
		}
	}
    fp.close();
if(flag==0)
 cout<<"\n\nAccount number does not exist.";
    getch();
}
void modify_account()
{
    int no,found=0;
    clrscr();
    cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tEnter The account No. of The account :: ";
    cin>>no;
    fp.open("account.dat",ios::in|ios::out);
    while(fp.read((char*)&ac,sizeof(account)) && found==0)
	   {
	    if(ac.retacno()==no)
		   {
		    ac.show_account();
		    cout<<"\nEnter The New Details of account :: "<<endl;
		    ac.modify_account();
		    int pos=-1*sizeof(ac);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&ac,sizeof(account));
		    cout<<"\n\n\t Record Updated.";
		    found=1;
		   }
	     }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found. ";
    getch();
}
void delete_account()
   {
    int no;
    clrscr();
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nEnter The account no. of the customer whose account You Want To Delete :: ";
    cin>>no;
    fp.open("account.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&ac,sizeof(account)))
	{
	 if(ac.retacno()!=no)
		{
		 fp2.write((char*)&ac,sizeof(account));
		 }
	 }
    fp2.close();
    fp.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\tRecord Deleted ..";
    getch();
    }
    void display_all()
    {
     clrscr();
     fp.open("account.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPENED. \n\nFirst please create the file./n/nThank You.";
       getch();
       return;
     }
     else{
     cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	  cout<<"====================================================\n";
	  cout<<"A/c no.\tNAME\t\tType\t\tBalance\n";
	  cout<<"====================================================\n";

      while(fp.read((char*)&ac,sizeof(account)))
	 ac.report();
      }
     fp.close();
}
void deposit_withdraw(int option)
{
    int no,found=0,amt;
    clrscr();
    cout<<"\n\n\tEnter The account No. :: ";
    cin>>no;
    fp.open("account.dat",ios::in|ios::out);
    while(fp.read((char*)&ac,sizeof(account)) && found==0)
       {
	    if(ac.retacno()==no)
	   {
		    ac.show_account();
		    if(option==1)
		       {
			cout<<"\n\n\tTO DEPOSITE AMOUNT ";
			cout<<"\n\nEnter The amount to be deposited :: ";
			cin>>amt;
			ac.dep(amt);
		       }
		     if(option==2)
		       {
			cout<<"\n\n\tTO WITHDRAW AMOUNT ";
			cout<<"\n\nEnter The amount to be withdraw :: ";
			cin>>amt;
			 int bal=ac.retdeposit()-amt;
			 if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
			      cout<<"Insufficient balance.";
				   else
			       ac.draw(amt);
		      }
			 int pos=-1*sizeof(ac);
			 fp.seekp(pos,ios::cur);
			 fp.write((char*)&ac,sizeof(account));
			 cout<<"\n\n\t Record Updated.";
			 found=1;
	       }
	 }
    fp.close();
    if(found==0)
    cout<<"\n\n Record Not Found. ";
    getch();
}
void intro()
{
 clrscr();
 gotoxy(36,11);
 cout<<"BANKING";
 gotoxy(35,14);
 cout<<"MANAGEMENT";
 gotoxy(36,17);
 cout<<"SYSTEM";
 getch();

}
void main()
{
  char ch;
  intro();
  do
    {
	  clrscr();
	  cout<<"\n\n\n\tMAIN MENU";
	  cout<<"\n\n\t01. NEW ACCOUNT";
	  cout<<"\n\n\t02. DEPOSIT AMOUNT";
	  cout<<"\n\n\t03. WITHDRAW AMOUNT";
	  cout<<"\n\n\t04. BALANCE ENQUIRY";
	  cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
	  cout<<"\n\n\t06. CLOSE AN ACCOUNT";
	  cout<<"\n\n\t07. MODIFY AN ACCOUNT";
	  cout<<"\n\n\t08. EXIT";
	  cout<<"\n\n\tSelect Your Option (1-8) ";
	  ch=getche();
	  switch(ch)
	  {
		case '1': clrscr();
			  write_account();
			  getch();
			break;
		case '2': clrscr();
			  deposit_withdraw(1);
			  break;
		case '3': clrscr();
			  deposit_withdraw(2);
			  getch();
			  break;
		case '4': int num;
			  clrscr();
			  cout<<"\n\n\tEnter The account No. ::";
			  cin>>num;
			  display_sp(num);
			  break;
		case '5': clrscr();
			  display_all();
			getch();
			 break;
		case '6': delete_account();
			  break;
		 case '7': clrscr();
			   modify_account();
			   getch();
			   break;
		  case '8':exit(0);
		  default :cout<<"\a";
	}
    }while(ch!='8');
}
