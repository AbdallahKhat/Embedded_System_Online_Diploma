/*
 * Student_Management.h
 *
 *  Created on: Jul 21, 2023
 *      Author: Abdallah Khater
 */

#ifndef STUDENT_MANAGEMENT_H_
#define STUDENT_MANAGEMENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Macro to define max number of students to be registered
#define MaxStudents 55

//Student Details Structure
struct sinfo
{
	char fname[50];
	char lname[50];
	int roll;
	float GPA;
	int cid[5];
};

//APIs
void add_student_file();
void add_student_manually();
void find_rl();
void find_fn();
void find_c();
void tot_s();
void del_s();
void up_s();
void show_s();


#endif /* STUDENT_MANAGEMENT_H_ */
