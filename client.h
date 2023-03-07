#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
void NormalUserLogin(int sd);
void JointUserLogin(int sd);
void AdminUserLogin(int sd);
void showMenu(int sd);
void deposit(int sd);
void withdraw(int sd);
void balEnquiry(int sd);
void changePassword(int sd);
void viewDetails(int sd);
void addAcc(int sd);
void deleteAcc(int sd);
void modifyAcc(int sd);
void searchforAcc(int sd);
int choice;
int UserID;