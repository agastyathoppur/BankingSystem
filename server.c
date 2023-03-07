#include "server.h"
#include "structs.h"

NormalUser getNormalUser(int ID)
{
	int offset=ID-1;
	NormalUser User;
	int fd=open("NormalUsers",O_RDONLY,0744);
	
	int flocknum;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(offset)*sizeof(NormalUser);    	 
	lock.l_len=sizeof(NormalUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);	

	lseek(fd,(offset)*sizeof(NormalUser),SEEK_SET);  
	read(fd,&User,sizeof(NormalUser));
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);

	return User;
}

JointUser getJointUser(int ID)
{
	int offset=ID-1;
	JointUser User;
	int fd=open("JointUsers",O_RDONLY,0744);
	
	int flocknum;
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(offset)*sizeof(JointUser);    	     
	lock.l_len=sizeof(JointUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);

	lseek(fd,(offset)*sizeof(JointUser),SEEK_SET);  
	read(fd,&User,sizeof(JointUser));
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);

	return User;
}

AdminUser getAdmin(int ID)
{
	int offset=ID-1;
	AdminUser User;
	int fd=open("AdminUsers",O_RDONLY,0744);

	int flocknum;
	struct flock lock;
	lock.l_type=F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(offset)*sizeof(AdminUser);    	     
	lock.l_len=sizeof(AdminUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);

	lseek(fd,(offset)*sizeof(AdminUser),SEEK_SET); 
	read(fd,&User,sizeof(AdminUser));
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);

	return User;
}

bool checkforNormalUser(NormalUser User)
{
	int offset=User.userID-1;
	int fd=open("NormalUsers",O_RDONLY,0744);
	bool flag;
	NormalUser Userinfile;
	
	int flocknum;
	struct flock lock;
	lock.l_type=F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(offset)*sizeof(NormalUser);    	    
	lock.l_len=sizeof(NormalUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);

	lseek(fd,(offset)*sizeof(NormalUser),SEEK_SET); 
	read(fd,&Userinfile,sizeof(NormalUser));
	if(!strcmp(Userinfile.password,User.password) && !strcmp(Userinfile.status,"ACTIVE"))	
		flag=true;
	else						
		flag=false;
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);

	return flag;
}

bool checkforJointUser(JointUser User)
{
	int offset=User.userID-1;
	int fd=open("JointUsers",O_RDONLY,0744);
	bool flag;
	JointUser Userinfile;
	
	int flocknum;
	struct flock lock;
	lock.l_type=F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(offset)*sizeof(JointUser);    	    
	lock.l_len=sizeof(JointUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);

	lseek(fd,(offset)*sizeof(JointUser),SEEK_SET);  
	read(fd,&Userinfile,sizeof(JointUser));
	if(!strcmp(Userinfile.password,User.password) && !strcmp(Userinfile.status,"ACTIVE"))	
		flag=true;
	else						
		flag=false;
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);

	close(fd);
	return flag;
}

bool checkforAdminUser(AdminUser User)
{
	int offset=User.userID-1;
	int fd=open("AdminUsers",O_RDONLY,0744);
	bool flag;
	AdminUser Userinfile;
	
	int flocknum;
	struct flock lock;
	lock.l_type=F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(offset)*sizeof(AdminUser);    	     
	lock.l_len=sizeof(AdminUser);	           
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);
	lseek(fd,(offset)*sizeof(AdminUser),SEEK_SET); 
	read(fd,&Userinfile,sizeof(AdminUser));
	if(!strcmp(Userinfile.password,User.password))	
		flag=true;
	else						
		flag=false;
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);

	return flag;
}

bool deposit(int accType,int ID,float amount)
{
	int offset=ID-1;
	if(accType==1)
	{
		int fd=open("NormalUsers",O_RDWR,0744);
		bool flag;
		int flocknum;
		struct flock lock;
		lock.l_type=F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(offset)*sizeof(NormalUser);   
		lock.l_len=sizeof(NormalUser);	             
		lock.l_pid=getpid();
	
		flocknum=fcntl(fd,F_SETLKW,&lock);	
		NormalUser User;
		lseek(fd,(offset)*sizeof(NormalUser),SEEK_SET); 
		read(fd,&User,sizeof(NormalUser));	
		if(!strcmp(User.status,"ACTIVE"))
		{
			User.bal+=amount;
			lseek(fd,sizeof(NormalUser)*(-1),SEEK_CUR);
			write(fd,&User,sizeof(NormalUser));
			flag=true;
		}
		else	
			flag=false;
		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);

		return flag;		
	}
	else if(accType==2)
	{
		int fd=open("JointUsers",O_RDWR,0744);
		bool flag;
		int flocknum;
		struct flock lock;
		lock.l_type=F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(offset)*sizeof(JointUser);   
		lock.l_len=sizeof(JointUser);	            
		lock.l_pid=getpid();
	
		flocknum=fcntl(fd,F_SETLKW,&lock);
		JointUser User;
		lseek(fd,(offset)*sizeof(JointUser),SEEK_SET); 
		read(fd,&User,sizeof(JointUser));
		
		if(!strcmp(User.status,"ACTIVE"))
		{
			User.bal+=amount;
			lseek(fd,sizeof(JointUser)*(-1),SEEK_CUR);
			write(fd,&User,sizeof(JointUser));
			flag=true;
		}
		else	
			flag=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);

		return flag;	
	}
	return false;
}

bool withdraw(int accType,int ID,float amount)
{
	int offset=ID-1;
	if(accType==1)
	{
		int fd=open("NormalUsers",O_RDWR,0744);
		bool flag;
		int flocknum;
		struct flock lock;
		lock.l_type=F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(offset)*sizeof(NormalUser);    
		lock.l_len=sizeof(NormalUser);	             
		lock.l_pid=getpid();
	
		flocknum=fcntl(fd,F_SETLKW,&lock);
		NormalUser User;
		lseek(fd,(offset)*sizeof(NormalUser),SEEK_SET);  
		read(fd,&User,sizeof(NormalUser));
		
		if(!strcmp(User.status,"ACTIVE") && User.bal>=amount)
		{
			User.bal-=amount;
			lseek(fd,sizeof(NormalUser)*(-1),SEEK_CUR);
			write(fd,&User,sizeof(NormalUser));
			flag=true;
		}
		else	
			flag=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);

		return flag;	
	}
	else if(accType==2)
	{
		int fd=open("JointUsers",O_RDWR,0744);
		bool flag;
		int flocknum;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(offset)*sizeof(JointUser);   
		lock.l_len=sizeof(JointUser);	             
		lock.l_pid=getpid();
	
		flocknum=fcntl(fd,F_SETLKW,&lock);	
		JointUser User;
		lseek(fd,(offset)*sizeof(JointUser),SEEK_SET); 
		read(fd,&User,sizeof(JointUser));
		
		if(!strcmp(User.status,"ACTIVE") && User.bal>=amount)
		{
			User.bal-=amount;
			lseek(fd,sizeof(JointUser)*(-1),SEEK_CUR);
			write(fd,&User,sizeof(JointUser));
			flag=true;
		}
		else	
			flag=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);

		return flag;
	}
	return false;
}

float getBal(int accType,int ID)
{
	int offset=ID-1;
	float flag;
	if(accType==1)
	{
		int offset=ID-1;
		int fd=open("NormalUsers",O_RDONLY,0744);
		NormalUser Userinfile;
	
		int flocknum;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(offset)*sizeof(NormalUser);    	     
		lock.l_len=sizeof(NormalUser);	             
		lock.l_pid=getpid();
	
		flocknum=fcntl(fd,F_SETLKW,&lock);

		lseek(fd,(offset)*sizeof(NormalUser),SEEK_SET);  
		read(fd,&Userinfile,sizeof(NormalUser));
		if(!strcmp(Userinfile.status,"ACTIVE"))	
			flag=Userinfile.bal;
		else					
			flag=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);

		return flag;
	}
	else if(accType==2)
	{
		int offset=ID-1;
		int fd=open("JointUsers",O_RDONLY,0744);
		JointUser Userinfile;
	
		int flocknum;
		struct flock lock;
		lock.l_type = F_RDLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(offset)*sizeof(JointUser);    	     
		lock.l_len=sizeof(JointUser);	            
		lock.l_pid=getpid();
	
		flocknum=fcntl(fd,F_SETLKW,&lock);

		lseek(fd,(offset)*sizeof(JointUser),SEEK_SET);  
		read(fd,&Userinfile,sizeof(JointUser));
		if(!strcmp(Userinfile.status,"ACTIVE"))	
			flag=Userinfile.bal;
		else					
			flag=0;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);

		return flag;
	}
	return 0;
}

bool changePassword(int accType,int ID,char newpassword[20])
{
	int offset=ID-1;
	if(accType==1)
	{
		int fd=open("NormalUsers",O_RDWR,0744);
		bool flag;
		int flocknum;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(offset)*sizeof(NormalUser);   
		lock.l_len=sizeof(NormalUser);	             
		lock.l_pid=getpid();
	
		flocknum=fcntl(fd,F_SETLKW,&lock);	
		NormalUser User;
		lseek(fd,(offset)*sizeof(NormalUser),SEEK_SET);  
		read(fd,&User,sizeof(NormalUser));
		
		if(!strcmp(User.status,"ACTIVE"))
		{
			strcpy(User.password,newpassword);
			lseek(fd,sizeof(NormalUser)*(-1),SEEK_CUR);
			write(fd,&User,sizeof(NormalUser));
			flag=true;
		}
		else	
			flag=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);

		return flag;
	}
	else if(accType==2)
	{
		int fd=open("JointUsers",O_RDWR,0744);
		bool flag;
		int flocknum;
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence=SEEK_SET;
		lock.l_start=(offset)*sizeof(JointUser);    
		lock.l_len=sizeof(JointUser);	             
		lock.l_pid=getpid();
	
		flocknum=fcntl(fd,F_SETLKW,&lock);

		JointUser User;
		lseek(fd,(offset)*sizeof(JointUser),SEEK_SET); 
		read(fd,&User,sizeof(JointUser));
		
		if(!strcmp(User.status,"ACTIVE"))
		{
			strcpy(User.password,newpassword);
			lseek(fd,sizeof(JointUser)*(-1),SEEK_CUR);
			write(fd,&User,sizeof(JointUser));
			flag=true;
		}
		else	
			flag=false;

		lock.l_type=F_UNLCK;
		fcntl(fd,F_SETLK,&lock);
		close(fd);

		return flag;
	}
	return false;
}

bool addNormalUser(NormalUser User)
{
	int fd=open("NormalUsers",O_RDWR,0744);
	bool flag;
	
	int flocknum;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(NormalUser);    
	lock.l_len=sizeof(NormalUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);	
	NormalUser endUser;
	lseek(fd,(-1)*sizeof(NormalUser),SEEK_END); 
	read(fd,&endUser,sizeof(NormalUser));
		
	User.userID=endUser.userID+1;
	User.acc_num=endUser.acc_num+1;
	strcpy(User.status,"ACTIVE");
	
	int j=write(fd,&User,sizeof(NormalUser));
	if(j!=0)	
		flag=true;
	else	
		flag=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	close(fd);
	return flag;	
}

bool addJointUser(JointUser User)
{
	int fd=open("JointUsers",O_RDWR,0744);
	bool flag;
	
	int flocknum;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_END;
	lock.l_start=(-1)*sizeof(JointUser);    
	lock.l_len=sizeof(JointUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);	

	JointUser endUser;
	lseek(fd,(-1)*sizeof(JointUser),SEEK_END); 
	read(fd,&endUser,sizeof(JointUser));
		
	User.userID=endUser.userID+1;
	User.acc_num=endUser.acc_num+1;
	strcpy(User.status,"ACTIVE");
	int j=write(fd,&User,sizeof(JointUser));

	if(j!=0)	
		flag=true;
	else	
		flag=false;
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);

	return flag;	
}

bool deleteNormalUser(int ID)
{
	int offset=ID-1;
	int fd=open("NormalUsers",O_RDWR,0744);
	bool flag;
	
	int flocknum;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(offset)*sizeof(NormalUser);    
	lock.l_len=sizeof(NormalUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);	
	NormalUser User;
	lseek(fd,(offset)*sizeof(NormalUser),SEEK_SET); 
	read(fd,&User,sizeof(NormalUser));
	
	if(!strcmp(User.status,"ACTIVE"))
	{	
		strcpy(User.status,"CLOSED");
		User.bal=0;
		lseek(fd,(-1)*sizeof(NormalUser),SEEK_CUR); 
		int j=write(fd,&User,sizeof(NormalUser));

		if(j!=0)	
			flag=true;
		else		
			flag=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);
	return flag;	
}

bool deleteJointUser(int ID)
{
	int offset=ID-1;
	int fd=open("JointUsers",O_RDWR,0744);
	bool flag;
	
	int flocknum;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(offset)*sizeof(JointUser);    
	lock.l_len=sizeof(JointUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);	
	JointUser User;
	lseek(fd,(offset)*sizeof(JointUser),SEEK_SET); 
	read(fd,&User,sizeof(JointUser));
	
	if(!strcmp(User.status,"ACTIVE"))
	{	
		strcpy(User.status,"CLOSED");
		User.bal=0;
		lseek(fd,(-1)*sizeof(JointUser),SEEK_CUR); 
		int j=write(fd,&User,sizeof(JointUser));

		if(j!=0)	
			flag=true;
		else		
			flag=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);

	return flag;	
}

bool modifyNormalUser(NormalUser modUser)
{
	int offset=modUser.userID;
	int fd=open("NormalUsers",O_RDWR,0744);
	bool flag=false;
	
	int flocknum;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(offset)*sizeof(NormalUser);    
	lock.l_len=sizeof(NormalUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);	
	NormalUser User;
	lseek(fd,(offset)*sizeof(NormalUser),SEEK_SET); 
	read(fd,&User,sizeof(NormalUser));
	
	if(!strcmp(User.status,"ACTIVE") && (modUser.acc_num==User.acc_num))
	{	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(NormalUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(NormalUser));
		if(j!=0)	
			flag=true;
		else		
			flag=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);

	return flag;	
}

bool modifyJointUser(JointUser modUser)
{
	int offset=modUser.userID;
	int fd=open("JointUsers",O_RDWR,0744);
	bool flag=false;
	
	int flocknum;
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=(offset)*sizeof(JointUser);    
	lock.l_len=sizeof(JointUser);	             
	lock.l_pid=getpid();
	
	flocknum=fcntl(fd,F_SETLKW,&lock);	

	JointUser User;
	lseek(fd,(offset)*sizeof(JointUser),SEEK_SET); 
	read(fd,&User,sizeof(JointUser));
	
	if(!strcmp(User.status,"ACTIVE")  && (modUser.acc_num==User.acc_num))
	{	
		strcpy(modUser.status,"ACTIVE");
		lseek(fd,(-1)*sizeof(JointUser),SEEK_CUR); 
		int j=write(fd,&modUser,sizeof(JointUser));
		if(j!=0)	
			flag=true;
		else		
			flag=false;
	}
	
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	close(fd);

	return flag;	
}

void serverTask(int nsd)
{
	int lenUser,sel,type,choice,accType,UserID;
	bool flag;
	int running=1;
	while(running)
	{
		read(nsd,&choice,sizeof(choice));
		printf("Option: %i\n",choice);

		if(choice==1)
		{
			NormalUser User1;
			accType=1;
			lenUser=read(nsd,&User1,sizeof(NormalUser));
			printf("User ID received: %i\n",User1.userID);
			printf("Password received: %s\n",User1.password);
			UserID=User1.userID;
			flag=checkforNormalUser(User1);
			write(nsd,&flag,sizeof(flag));
		}
		else if(choice==2)
		{
			JointUser User2;
			accType=2;
			lenUser=read(nsd,&User2,sizeof(JointUser));
			UserID=User2.userID;
			printf("User ID received: %i\n",User2.userID);
			printf("Password recieved: %s\n",User2.password);
			flag=checkforJointUser(User2);
			write(nsd,&flag,sizeof(flag));
		}
		else if(choice==3)
		{
			AdminUser User3;
			accType=3;
			lenUser=read(nsd,&User3,sizeof(AdminUser));
			UserID=User3.userID;
			printf("User ID received: %i\n",User3.userID);
			printf("Password received: %s\n",User3.password);
			flag=checkforAdminUser(User3);
			write(nsd,&flag,sizeof(flag));
		}
		else
		{
			flag=false;
			write(nsd,&flag,sizeof(flag));
		}
		if(flag)	
			break;		
	}
	while(running)
	{
		read(nsd,&sel,sizeof(int));
		if(choice==1||choice==2)
		{
			if(sel==1)
			{
				float amount;
				read(nsd,&amount,sizeof(float));
				flag=deposit(accType,UserID,amount);
				write(nsd,&flag,sizeof(flag));
			}
			else if(sel==2)
			{
				float amount;
				read(nsd,&amount,sizeof(float));
				flag=withdraw(accType,UserID,amount);
				write(nsd,&flag,sizeof(flag));
			}
			else if(sel==3)
			{
				float amount;
				amount=getBal(accType,UserID);
				write(nsd,&amount,sizeof(float));
			}
			else if(sel==4)
			{
				char password[20];
				read(nsd,password,sizeof(password));
				flag=changePassword(accType,UserID,password);
				write(nsd,&flag,sizeof(flag));
			}
			else if(sel==5)
			{
				if(choice==1){
					NormalUser user1=getNormalUser(UserID);
					write(nsd,&user1,sizeof(NormalUser));
				}
				else if(choice==2){
					JointUser user2=getJointUser(UserID);
					write(nsd,&user2,sizeof(JointUser));
				}
			}
			else if(sel==6)	
				break;
		}
		else if(choice==3)
		{
			read(nsd,&type,sizeof(int));
			if(sel==1)
			{
				if(type==1)
				{
					NormalUser newUser1;
					read(nsd,&newUser1,sizeof(NormalUser));
					flag=addNormalUser(newUser1);
					write(nsd,&flag,sizeof(flag));
				}
				else if(type==2)
				{
					JointUser newUser2;
					read(nsd,&newUser2,sizeof(JointUser));
					flag=addJointUser(newUser2);
					write(nsd,&flag,sizeof(flag));
				}
			}
			else if(sel==2)
			{
				if(type==1)
				{
					int delUserID1;
					read(nsd,&delUserID1,sizeof(int));
					flag=deleteNormalUser(delUserID1);
					write(nsd,&flag,sizeof(flag));
				}
				else if(type==2)
				{
					int delUserID2;
					read(nsd,&delUserID2,sizeof(int));
					flag=deleteJointUser(delUserID2);
					write(nsd,&flag,sizeof(flag));
				}
			}
			else if(sel==3)
			{
				if(type==1)
				{
					NormalUser modUser1;
					read(nsd,&modUser1,sizeof(NormalUser));
					flag=modifyNormalUser(modUser1);
					write(nsd,&flag,sizeof(flag));
				}
				else if(type==2)
				{
					JointUser modUser2;
					read(nsd,&modUser2,sizeof(JointUser));
					flag=modifyJointUser(modUser2);
					write(nsd,&flag,sizeof(flag));
				}
			}
			else if(sel==4)
			{
				if(type==1)
				{
					NormalUser searchUser1;
					int userID1;
					read(nsd,&userID1,sizeof(int));
					searchUser1=getNormalUser(userID1);
					write(nsd,&searchUser1,sizeof(NormalUser));
				}
				else if(type==2)
				{
					JointUser searchUser2;
					int userID2;
					read(nsd,&userID2,sizeof(int));
					searchUser2=getJointUser(userID2);
					write(nsd,&searchUser2,sizeof(JointUser));
				}
			}
			else if(sel==5)	
				break;
		}
	}
	close(nsd);
	write(STDOUT_FILENO,"Closing connection with client\n",32);
	return;
}

void *connectionhandler(void *nsd) 
{
	int nsfd = *(int*)nsd;
	serverTask(nsfd);
}


int main()
{
	struct sockaddr_in server,client;
	int sd,nsd,clientLen;
	pthread_t threads;
	bool flag;
	sd=socket(AF_INET,SOCK_STREAM,0);

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(5555);

	bind(sd,(struct sockaddr*)&server,sizeof(server));
	listen(sd,5);
	
	write(STDOUT_FILENO,"Waiting to connect to the client.\n",35);
	int running=1;
	while(running)
	{
		clientLen=sizeof(client);
		nsd=accept(sd,(struct sockaddr *)&client,&clientLen);
		write(STDOUT_FILENO,"Connection with the client confirmed.\n",39);
		pthread_create(&threads,NULL,connectionhandler,(void*) &nsd);
	}
	pthread_exit(NULL);
	close(sd);
	return 0;
}