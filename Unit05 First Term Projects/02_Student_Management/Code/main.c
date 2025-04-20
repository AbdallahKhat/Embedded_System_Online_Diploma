/*
 * main.c
 *
 *  Created on: Jul 21, 2023
 *      Author: Abdallah Khater
 */


#include <stdio.h>
#include <stdlib.h>

#include "Student_Management.h"

int main()
{
	int choice;
	char exit_flag = 0;

	printf("Welcome to the Student Management System\n");
	while(1)
	{
	    printf("-----------------------------------\n");
		printf("Choose The Task that you want to perform\n");
		printf("1. Add the Student Details from Text File\n");
		printf("2. Add the Student Details Manually\n");
		printf("3. Find the Student Details by Roll Number\n");
		printf("4. Find the Student Details by First Name\n");
		printf("5. Find the Student Details by Course ID\n");
		printf("6. Find the Total number of Students\n");
		printf("7. Delete a Student's Details by Roll Number\n");
		printf("8. Update a Student's Details by Roll Number\n");
		printf("9. Show all the information\n");
		printf("10. To Exit\n");
		printf("Enter your choice to perform the task: ");

		/* receive user input for option selection */
		scanf("%d",&choice);

		printf("-----------------------------------\n");

		switch(choice)
		{
		case 1:
			add_student_file();
			break;

		case 2:
			add_student_manually();
			break;

		case 3:
			find_rl();
			break;

		case 4:
			find_fn();
			break;

		case 5:
			find_c();
			break;

		case 6:
			tot_s();
			break;

		case 7:
			del_s();
			break;

		case 8:
			up_s();
			break;

		case 9:
			show_s();
			break;

		case 10:
			exit_flag = 1;
			break;

		default:
			printf("[ERROR] Option not found! Please select a Task from [1 - 10]\n");
			break;
		}
		if(exit_flag == 1)
			break;
	}

	return 0;
}
