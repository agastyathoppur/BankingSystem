#include "client.h"
#include "structs.h"

void chooseAccLogin(int sd)
{
    int running=1;
	while(running)
    {
		write(STDOUT_FILENO,"1:Normal-User Login\n",21);
		write(STDOUT_FILENO,"2:Joint Account-User Login\n",28);
		write(STDOUT_FILENO,"3:Admin Login\n",15);
		
		write(STDOUT_FILENO,"Choose one of the options: ",28);
		scanf("%i",&choice);
        switch(choice)
        {
            case 1:
			NormalUserLogin(sd);
            running=0; 
			break;
		    case 2:
			JointUserLogin(sd);
            running=0;
			break;
            case 3:
			AdminUserLogin(sd);
            running=0;
			break;
            default:
            write(STDOUT_FILENO,"Invalid Choice\n",16);
            running=1;
		}      
	}
}

void AccOperationMenu(int sd)
{
	int local_choice;
	if(choice==1||choice==2)
    {
		write(STDOUT_FILENO,"1: Deposit\n",12);
		write(STDOUT_FILENO,"2: Withdraw\n",13);
		write(STDOUT_FILENO,"3: Balance Enquiry\n",20);
		write(STDOUT_FILENO,"4: Password Change\n",20);
		write(STDOUT_FILENO,"5: View Details\n",17);
		write(STDOUT_FILENO,"6: Exit\n",9);
	
		write(STDOUT_FILENO,"Choose one of the options: ",28);
		scanf("%i",&local_choice);
		printf("Option: %i\n",local_choice);
		
		switch(local_choice)
        {
		    case 1:
			deposit(sd);
			break;
		    case 2:
			withdraw(sd);
			break;
		    case 3:
			balEnquiry(sd);
			break;
		    case 4:
			changePassword(sd);
			break;
		    case 5:
			viewDetails(sd);
			break;
		    case 6:
			write(sd,&local_choice,sizeof(int));
			write(STDOUT_FILENO,"Exiting\n",9);
			exit(0);
		    default:
			write(STDOUT_FILENO,"Invalid Choice\n",16);
			AccOperationMenu(sd);
			break;
		}
	}
	else if(choice==3)
    {
		write(STDOUT_FILENO,"1: Add Account\n",16);
		write(STDOUT_FILENO,"2: Delete Account\n",19);
		write(STDOUT_FILENO,"3: Modify Account\n",19);
		write(STDOUT_FILENO,"4: Search Account\n",19);
		write(STDOUT_FILENO,"5: Exit\n",9);

		write(STDOUT_FILENO,"Choose one of the options: ",28);
		scanf("%i",&local_choice);
		printf("Option: %i\n",local_choice);
		
		switch(local_choice)
        {
		    case 1:
			addAcc(sd);
			break;
		    case 2:
			deleteAcc(sd);
			break;
		    case 3:
			modifyAcc(sd);
			break;
		    case 4:
			searchforAcc(sd);
			break;
		    case 5:
			write(sd,&local_choice,sizeof(int));
			write(STDOUT_FILENO,"Exiting\n",9);
			exit(0);
		    default:
			write(STDOUT_FILENO,"Invalid Choice\n",16);
			AccOperationMenu(sd);
			break;
		}
	}
}

void NormalUserLogin(int sd)
{
	bool flag;
	NormalUser User;
	write(STDOUT_FILENO,"User ID: ",10);
	scanf("%i",&User.userID);
	UserID=User.userID;
	write(STDOUT_FILENO,"Password: ",11);
	scanf("%s",User.password);

	write(sd,&choice,sizeof(int));
	write(sd,&User,sizeof(NormalUser));
	read(sd,&flag,sizeof(flag));

	if(!flag)
    {
		write(STDOUT_FILENO,"Invalid login\n",15);
		chooseAccLogin(sd);
	}
	else
		write(STDOUT_FILENO,"Logged in\n",11);

}

void JointUserLogin(int sd)
{
	bool flag;
	JointUser User;
	write(STDOUT_FILENO,"User ID: ",10);
	scanf("%i",&User.userID);
	UserID=User.userID;
	write(STDOUT_FILENO,"Password: ",11);
	scanf("%s",User.password);

	write(sd,&choice,sizeof(int));
	write(sd,&User,sizeof(JointUser));
	read(sd,&flag,sizeof(flag));

	if(!flag)
    {
		write(STDOUT_FILENO,"Invalid login\n",15);
		chooseAccLogin(sd);
	}
	else
		write(STDOUT_FILENO,"Logged in\n",11);

}

void AdminUserLogin(int sd)
{
	bool flag;
	AdminUser User;
	write(STDOUT_FILENO,"User ID: ",10);
	scanf("%i",&User.userID);
	UserID=User.userID;
	write(STDOUT_FILENO,"Password: ",11);
	scanf("%s",User.password);

	write(sd,&choice,sizeof(int));
	write(sd,&User,sizeof(AdminUser));
    read(sd,&flag,sizeof(flag));

	if(!flag)
    {
		write(STDOUT_FILENO,"Invalid login\n",15);
		chooseAccLogin(sd);
	}
	else
		write(STDOUT_FILENO,"Logged in\n",11);

}

void deposit(int sd)
{
	float amount;
	int local_choice=1;
	bool flag;

	write(STDOUT_FILENO,"Amount to Deposit:",19);
	scanf("%f",&amount);

	write(sd,&local_choice,sizeof(int));
	write(sd,&amount,sizeof(float));
    read(sd,&flag,sizeof(flag));

	if(!flag)
		write(STDOUT_FILENO,"Error depositing your money\n",29);
	else
		write(STDOUT_FILENO,"Money sucessfully deposited\n",29);
	AccOperationMenu(sd);
}

void withdraw(int sd)
{
	float amount;
	int local_choice=2;
	bool flag;

	write(STDOUT_FILENO,"Amount to Withdraw:",20);
	scanf("%f",&amount);

	write(sd,&local_choice,sizeof(int));
	write(sd,&amount,sizeof(float));
    read(sd,&flag,sizeof(flag));

	if(!flag)
		write(STDOUT_FILENO,"Error withdrawing your money\n",30);
	else
		write(STDOUT_FILENO,"Money successfully withdrawn\n",30);
	AccOperationMenu(sd);
}

void balEnquiry(int sd)
{
	float amount;
	int local_choice=3;

	write(sd,&local_choice,sizeof(int));	
	read(sd,&amount,sizeof(float));
	write(STDOUT_FILENO,"Available Balance: ",20);
	printf("%0.2f\n",amount);
	AccOperationMenu(sd);
}

void changePassword(int sd)
{
	int local_choice=4;
	char password[20];
	bool flag;

	write(STDOUT_FILENO,"Enter a new password below 20 characters: ",43);
	scanf("%s",password);
    write(sd,&local_choice,sizeof(int));
	write(sd,password,sizeof(password));
    read(sd,&flag,sizeof(flag)); 

	if(!flag)
		write(STDOUT_FILENO,"Couldn't change your password\n",31);
	else
		write(STDOUT_FILENO,"Password successfully changed\n",31);
	AccOperationMenu(sd);
}

void viewDetails(int sd)
{
	int local_choice=5;
	write(sd,&local_choice,sizeof(int));

	if(choice==1)
    {
		NormalUser User1;
		read(sd,&User1,sizeof(NormalUser));
		
		printf("User ID: %i\n",User1.userID);
		printf("Name: %s\n",User1.name);
		printf("Account Number: %i\n",User1.acc_num);
		printf("Available Balance: %0.2f\n",User1.bal);
		printf("Status: %s\n",User1.status);
	}
	else if(choice==2)
    {
		JointUser User2;
		read(sd,&User2,sizeof(JointUser));
		
		printf("User ID: %i\n",User2.userID);
		printf("Main Account Holder's Name: %s\n",User2.name1);
		printf("Other Account Holder's Name: %s\n",User2.name2);
		printf("Account Number: %i\n",User2.acc_num);
		printf("Available Balance: Rs.%0.2f\n",User2.bal);
		printf("Status: %s\n",User2.status);
	}
	AccOperationMenu(sd);
}

void addAcc(int sd)
{
	int local_choice=1;
	int type;
	bool flag;

	write(sd,&local_choice,sizeof(int));

	write(STDOUT_FILENO,"Enter account type(1: Normal Account 2: Joint Account): ",57);
	scanf("%i",&type);
    write(sd,&type,sizeof(int));

	if(type==1)
    {
		NormalUser addUser1;
		write(STDOUT_FILENO,"Enter account holder name: ",28);
		scanf("%s",addUser1.name);
		printf("%s", addUser1.name);
		write(STDOUT_FILENO,"Enter password: ",17);
		scanf("%s",addUser1.password);
		write(STDOUT_FILENO,"Initial Deposit: ",18);
		scanf("%f",&addUser1.bal);
		write(sd,&addUser1,sizeof(NormalUser));
	}

	if(type==2)
    {
		JointUser addUser2;
		write(STDOUT_FILENO,"Enter first account holder's name: ",36);
		scanf("%s",addUser2.name1);
		write(STDOUT_FILENO,"Enter second account holder's name: ",37);
		scanf("%s",addUser2.name2);
		write(STDOUT_FILENO,"Enter password: ",17);
		scanf("%s",addUser2.password);
		write(STDOUT_FILENO,"Initial Deposit: ",18);
		scanf("%f",&addUser2.bal);
		write(sd,&addUser2,sizeof(JointUser));
	}
	
	read(sd,&flag,sizeof(flag)); //from the server

	if(!flag)
		write(STDOUT_FILENO,"Error adding the account!!\n\n",sizeof("Error adding the account!!\n\n"));
	else
		write(STDOUT_FILENO,"Succesfully added the account!!\n\n",sizeof("Succesfully added the account!!\n\n"));
	AccOperationMenu(sd);
}

void deleteAcc(int sd)
{
	int local_choice=2;
	int type,userID;
	bool flag;

	write(sd,&local_choice,sizeof(int));

	write(STDOUT_FILENO,"Enter account type(1: Normal Account 2: Joint Account): ",57);
	scanf("%i",&type);
	
	write(sd,&type,sizeof(int));

	write(STDOUT_FILENO,"User ID:",9);
	scanf("%i",&userID);
	write(sd,&userID,sizeof(int));
	read(sd,&flag,sizeof(flag)); 

	if(!flag)
		write(STDOUT_FILENO,"Error deleting the account\n",28);
	else
		write(STDOUT_FILENO,"Account successfully deleted\n",30);
	AccOperationMenu(sd);
}

void modifyAcc(int sd)
{
	int local_choice=3;
	int type;
	bool flag;

	write(sd,&local_choice,sizeof(int));
    write(STDOUT_FILENO,"Enter the account type(1: Normal Account 2: Joint Account) : ",62);
	scanf("%i",&type);
    write(sd,&type,sizeof(int));

	if(type==1)
    {
		NormalUser modUser1;
		write(STDOUT_FILENO,"User ID: ",10);
		scanf("%i",&modUser1.userID);
		write(STDOUT_FILENO,"Account Number: ",18);
		scanf("%i",&modUser1.acc_num);
		write(STDOUT_FILENO,"New account holder name: ",26);
		scanf("%s",modUser1.name);
		write(STDOUT_FILENO,"New Password below 20 characters: ",35);
		scanf("%s",modUser1.password);
		write(STDOUT_FILENO,"New Balance: ",14);
		scanf("%f",&modUser1.bal);
		write(sd,&modUser1,sizeof(NormalUser));
	}

	if(type==2)
    {
		JointUser modUser2;
		write(STDOUT_FILENO,"User ID: ",10);
		scanf("%i",&modUser2.userID);
		write(STDOUT_FILENO,"Account Number: ",17);
		scanf("%i",&modUser2.acc_num);
		write(STDOUT_FILENO,"New first account holder name: ",32);
		scanf("%s",modUser2.name1);
		write(STDOUT_FILENO,"New second account holder name: ",33);
		scanf("%s",modUser2.name2);
		write(STDOUT_FILENO,"New password below 20 characters: ",35);
		scanf("%s",modUser2.password);
		write(STDOUT_FILENO,"New Balance: ",14);
		scanf("%f",&modUser2.bal);
		write(sd,&modUser2,sizeof(JointUser));
	}
	
	read(sd,&flag,sizeof(flag)); 

	if(!flag)
		write(STDOUT_FILENO,"Error modifying the account\n",29);
	else
		write(STDOUT_FILENO,"Account modified successfully\n",31);
	AccOperationMenu(sd);
	return;
}

void searchforAcc(int sd)
{
	int local_choice=4;
	int type,len_read;
	bool flag;

	write(sd,&local_choice,sizeof(int));
	write(STDOUT_FILENO,"Enter the account type(1: Normal Account 2: Joint Account) : ",62);
	scanf("%i",&type);
	write(sd,&type,sizeof(int));

	if(type==1)
    {
		NormalUser searchUser1;
		int userID;
		write(STDOUT_FILENO,"User ID: ",10);
		scanf("%i",&userID);
		write(sd,&userID,sizeof(int));
		
		len_read=read(sd,&searchUser1,sizeof(NormalUser));
		if(len_read==0)
			write(STDOUT_FILENO,"Incorrect User ID\n",19);
		else{
			printf("User ID: %i\n",searchUser1.userID);
			printf("Name: %s\n",searchUser1.name);
			printf("Account Number: %i\n",searchUser1.acc_num);
			printf("Available Balance: Rs.%0.2f\n",searchUser1.bal);
			printf("Status: %s\n\n",searchUser1.status);
		}
	}

	if(type==2)
	{
		JointUser searchUser2;
		int userID1;
		write(STDOUT_FILENO,"User ID: ",10);
		scanf("%i",&userID1);
		write(sd,&userID1,sizeof(int));
		
		len_read=read(sd,&searchUser2,sizeof(JointUser));
		if(len_read==0)
			write(STDOUT_FILENO,"Incorrect User ID\n",19);
		else
		{
			printf("User ID: %i\n",searchUser2.userID);
			printf("First Account Holder's Name: %s\n",searchUser2.name1);
			printf("Second Account Holder's Name: %s\n",searchUser2.name2);
			printf("Account Number: %i\n",searchUser2.acc_num);
			printf("Available Balance: Rs.%0.2f\n",searchUser2.bal);
			printf("Status: %s\n\n",searchUser2.status);
		}
	}
	AccOperationMenu(sd);
	return;
}

int main()
{
	struct sockaddr_in server;
	int sd,msgLength;
	char buff[50];
	char flag;

	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;

	server.sin_addr.s_addr=inet_addr("127.0.0.1"); 
	server.sin_port=htons(5555);
	connect(sd,(struct sockaddr *)&server,sizeof(server));

	chooseAccLogin(sd);
	AccOperationMenu(sd);	
    close(sd);

	return 0;
}