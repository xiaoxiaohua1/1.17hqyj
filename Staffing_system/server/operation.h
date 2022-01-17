#ifndef OPERATION_H
#define OPERATION_H

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <sys/types.h>
#include <sys/socket.h>

int mode_selection(char str[],sqlite3 *db,int newfd);
int admin_login_inform_insert(char buf[],sqlite3* db,int newfd);
int enter_inform_verify(char buf[],sqlite3 *db,int newfd);
int admin_insert_staff_inform(char buf[],sqlite3* db,int newfd);
int admin_delete_staff_inform(char buf[],sqlite3* db,int newfd);
int admin_mod_staff_inform(char buf[],sqlite3* db,int newfd);
int admin_check_staff_inform(char buf[],sqlite3* db,int newfd);
int admin_check_all_staff_inform(sqlite3* db,int newfd);
int staff_modify_personal_inform(char buf[],sqlite3* db,int newfd);

#endif
