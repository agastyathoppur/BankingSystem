typedef struct AdminUser
{
	int userID;
	char name[20];
	char password[20];
}AdminUser;

typedef struct NormalUser
{
	int userID;
	char name[20];
	char password[20];
	int acc_num;
	float bal;
	char status[6];
}NormalUser;

typedef struct JointUser
{
	int userID;
	char name1[20];
	char name2[20];
	char password[20];
	int acc_num;
	float bal;
	char status[6];
}JointUser;
