#ifndef OPERATION_H
#define OPERATION_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int admin_login(int sfd);
int admin_enter(int sfd,char admin);
int staff_enter(int sfd);
int add_staff_inform(int sfd);
int delete_staff_inform(int sfd);
int mod_staff_inform(int sfd);
int check_staff_inform(int sfd);
int check_all_staff_inform(int sfd);
int check_personal_inform(int sfd);
int mod_personal_inform(int sfd);

#endif
