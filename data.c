#include "data.h"
#include "structs.h"

int getNormalUserID()
{
	int fd=open("NormalUsers",O_RDONLY,0744);
	NormalUser users;
	lseek(fd,-sizeof(NormalUser),SEEK_END);
	read(fd,&users,sizeof(NormalUser));
	close(fd);
	return users.userID+1;
}

int getJointUserID()
{
	int fd=open("JointUsers",O_RDONLY,0744);
	JointUser users;
	lseek(fd,-sizeof(JointUser),SEEK_END);
	read(fd,&users,sizeof(JointUser));
	close(fd);
	return users.userID+1;
}

int getAdminUserID()
{
	int fd=open("AdminUsers",O_RDONLY,0744);
	AdminUser users;
	lseek(fd,-sizeof(AdminUser),SEEK_END);
	read(fd,&users,sizeof(AdminUser));
	close(fd);
	return users.userID+1;
}

int main()
{
	int fd=open("AdminUsers",O_RDWR|O_CREAT,0744);
	int running=1;
	AdminUser newAdminUser;
    
	printf("Enter admin name (only one word): ");
	scanf("%s",newAdminUser.name);
	printf("Enter admin password below 20 characters: ");
	scanf("%s",newAdminUser.password);
	newAdminUser.userID=1;
	printf("Your userID is: %i\n",newAdminUser.userID);
	write(fd,&newAdminUser,sizeof(newAdminUser));
	printf("Enter 1 to continue and 0 to stop registering admins: ");
	scanf("%i",&running);

	while(running)
    {
		printf("Enter admin name (only one word): ");
		scanf("%s",newAdminUser.name);
		printf("Enter admin password below 20 characters: ");
		scanf("%s",newAdminUser.password);
		newAdminUser.userID=getAdminUserID();
		printf("Your userID is: %i\n",newAdminUser.userID);
		write(fd,&newAdminUser,sizeof(AdminUser));
		printf("Enter 1 to continue and 0 to stop registering admins: ");
		scanf("%i",&running);
	}
	close(fd);

	fd=open("NormalUsers",O_RDWR|O_CREAT,0744);
	running=1;
	NormalUser newNormalUser;
	printf("Enter Normal User name (only one word): ");
	scanf("%s",newNormalUser.name);
	printf("Enter account password under 20 characters: ");
	scanf("%s",newNormalUser.password);
	newNormalUser.userID=1;
	newNormalUser.bal=100000;
	newNormalUser.acc_num=(newNormalUser.userID)+100;
	printf("Your userID is: %i\n",newNormalUser.userID);
	strcpy(newNormalUser.status,"ACTIVE");
	write(fd,&newNormalUser,sizeof(NormalUser));
	printf("Enter 1 to continue and 0 to stop registering normal users: ");
	scanf("%i",&running);

	while(running)
    {
		printf("Enter Normal User name (only one word): ");
		scanf("%s",newNormalUser.name);
		printf("Enter account password under 20 characters: ");
		scanf("%s",newNormalUser.password);
		newNormalUser.userID=getNormalUserID();
		newNormalUser.bal=100000;
		newNormalUser.acc_num=(newNormalUser.userID)+100;
		printf("Your userID is: %i\n",newNormalUser.userID);
		strcpy(newNormalUser.status,"ACTIVE");
		write(fd,&newNormalUser,sizeof(NormalUser));
		printf("Enter 1 to continue and 0 to stop registering normal users: ");
		scanf("%i",&running);
	}
	close(fd);

	fd=open("JointUsers",O_RDWR|O_CREAT,0744);
	running=1;
	JointUser newJointUser;
	printf("Enter First Joint User name (only one word): ");
	scanf("%s",newJointUser.name1);
	printf("Enter Second Joint User name (only one word):");
	scanf("%s",newJointUser.name2);
	printf("Enter account password under 20 characters: ");
	scanf("%s",newJointUser.password);
	newJointUser.userID=1;
	newJointUser.bal=100000;
	newJointUser.acc_num=(newJointUser.userID)+100;
	printf("Your userID is: %i\n",newJointUser.userID);
	strcpy(newJointUser.status,"ACTIVE");
	write(fd,&newJointUser,sizeof(JointUser));
	printf("Enter 1 to continue and 0 to stop registering joint users: ");
	scanf("%i",&running);

	while(running)
    {
		printf("Enter First Joint User name (only one word): ");
		scanf("%s",newJointUser.name1);
		printf("Enter Second Joint User name (only one word):");
		scanf("%s",newJointUser.name2);
		printf("Enter account password under 20 characters: ");
		scanf("%s",newJointUser.password);
		newJointUser.userID=getJointUserID();
		newJointUser.bal=100000;
		newJointUser.acc_num=(newJointUser.userID)+100;
		printf("Your userID is : %i\n",newJointUser.userID);
		strcpy(newJointUser.status,"ACTIVE");
		write(fd,&newJointUser,sizeof(JointUser));
		printf("Enter 1 to continue and 0 to stop registering joint users: ");
		scanf("%i",&running);
	}
	close(fd);

	return 0;
}

