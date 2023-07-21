/*
 * Student_Management.c
 *
 *  Created on: Jul 21, 2023
 *      Author: Abdallah Khater
 */


#include "Student_Management.h"

//================ Static global variables ===============

static int StudentCount;

//============== Student Details structures ===============

static struct sinfo st[MaxStudents];

//============== Global Const Variables ===============

const static struct sinfo st_del = {0}; //Struct to delete a student

//================== API Implementation ==================

void add_student_file()
{
	FILE *fh;
	struct sinfo temp_st;
	char temp_arr[50], temp_roll, EOF_flag = 0;
	int i , j = 0, op_count = 0;

	fh = fopen("Students_List.txt","r");

	if(fh != NULL)
	{
		for(i = 0; i < 50 ; i++)
		{
			temp_arr[i] = fgetc(fh);

			if(temp_arr[i] == ' ' || temp_arr[i] == '\n' || temp_arr[i] == EOF)
			{
				if(temp_arr[i] == '\n')
					temp_arr[i] = '\0';

				else if(temp_arr[i] == EOF)
				{
					temp_arr[i] = '\0';
					EOF_flag = 1;
				}

				switch(op_count)
				{
				case 0:
					temp_roll = atoi(temp_arr);
					temp_st.roll = temp_roll;
					op_count++;
					i = -1; // will get incremented to 0 to start from the beginning
					break;

				case 1:
					temp_arr[i] = '\0';
					strcpy(temp_st.fname, temp_arr);
					op_count++;
					i = -1; // will get incremented to 0 to start from the beginning
					break;

				case 2:
					temp_arr[i] = '\0';
					strcpy(temp_st.lname, temp_arr);
					op_count++;
					i = -1; // will get incremented to 0 to start from the beginning
					break;

				case 3:
					temp_st.GPA = atof(temp_arr);
					op_count++;
					i = -1; // will get incremented to 0 to start from the beginning
					break;

				case 4:

					temp_st.cid[j] = atoi(temp_arr);
					j++;
					i = -1; // will get incremented to 0 to start from the beginning

					if(j == 5)
					{
						if(st[temp_roll - 1].roll == 0)
						{
							st[temp_roll - 1] = temp_st;
							StudentCount++;
							printf("[INFO] Roll Number %d saved successfully\n", temp_roll);
						}
						else
							printf("[ERROR] Roll Number %d is already taken\n", temp_roll);

						j = 0;
						op_count = 0;
					}
					break;
				}
			}
			if(EOF_flag == 1)
				break;
		}
		fclose(fh);
	}
	else
	{
		printf("[ERROR] Opening Students_List.txt file is unsuccessful!");
	}

	printf("-----------------------------------\n");
	printf("[INFO] The total number of students is %d\n", StudentCount);
	printf("[INFO] You can add up to %d students\n", MaxStudents);
	printf("[INFO] You can add %d more students\n", MaxStudents - StudentCount);

}
void add_student_manually()
{
	int Temp_roll, i;
	printf("-----------------------------------\n");
	printf("Add the Students Details\n");
	printf("-----------------------------------\n");
	printf("Enter the Roll Number: ");

	scanf("%d",&Temp_roll);

	if(Temp_roll <= MaxStudents && Temp_roll > 0)
	{
		if(st[Temp_roll - 1].roll == 0)
		{
			st[Temp_roll - 1].roll = Temp_roll;

			printf("Enter the first name of the student: ");
			scanf("%s",st[Temp_roll - 1].fname);

			printf("Enter the last name of the student: ");
			scanf("%s",st[Temp_roll - 1].lname);

			printf("Enter obtained GPA of student: ");
			scanf("%f",&st[Temp_roll - 1].GPA);

			printf("Enter the course ID of each course\n");

			for(i = 0; i < 5 ; i++)
			{
				printf("Course %d ID: ", i + 1);
				scanf("%d",&st[Temp_roll - 1].cid[i]);
			}

			printf("[INFO] Student Details is added successfully\n");
			printf("-----------------------------------\n");
			printf("[INFO] The total number of students is %d\n", ++StudentCount);
			printf("[INFO] You can add up to %d students\n", MaxStudents);
			printf("[INFO] You can add %d more students\n", MaxStudents - StudentCount);

		}
		else
			printf("[ERROR] Roll Number already exists!\n");
	}
	else
		printf("[ERROR] Roll number out of bounds! Roll number has to be from [1 - %d]\n",MaxStudents);


}

void find_rl()
{
	int Temp_roll, i;

	printf("Enter the Roll number of the student: ");
	scanf("%d",&Temp_roll);
	printf("-----------------------------------\n");

	if(st[Temp_roll - 1].roll != 0)
	{
		printf("The Student's Details are:\n");
		printf("The First name is %s\n",st[Temp_roll - 1].fname);
		printf("The Last name is %s\n",st[Temp_roll - 1].lname);
		printf("The GPA is %f\n",st[Temp_roll - 1].GPA);
		printf("ID of each course \n");

		for(i = 0; i < 5 ; i++)
			printf("Course %d ID: %d\n", i + 1, st[Temp_roll - 1].cid[i]);
	}
	else
	{
		printf("[ERROR] Roll Number %d not found!\n",Temp_roll);
	}
}
void find_fn()
{
	int i, j;
	char temp_fname[50], fn_flag = 0;

	printf("Enter the First name of the student: ");
	scanf("%s",temp_fname);
	printf("-----------------------------------\n");

	for(i = 0 ; i < MaxStudents ; i++)
	{
		if(st[i].roll != 0 && strcmp(st[i].fname, temp_fname) == 0)
		{
			printf("The Student's Details are:\n");
			printf("The First name is %s\n", st[i].fname);
			printf("The Last name is %s\n", st[i].lname);
			printf("The GPA is %f\n", st[i].GPA);
			printf("ID of each course \n");

			for(j = 0; j < 5 ; j++)
				printf("Course %d ID: %d\n", j + 1, st[i].cid[j]);

			fn_flag = 1;
		}
	}

	if(fn_flag == 0)
		printf("[ERROR] First name %s not found!\n", temp_fname);

}

void find_c()
{
	int temp_cid ,i, j;
	char cid_flag = 0;

	printf("Enter the course ID: ");
	scanf("%d",&temp_cid);
	printf("-----------------------------------\n");

	for(i = 0 ; i < MaxStudents ; i++)
	{
		if(st[i].roll != 0)
		{
			for(j = 0 ; j < 5 ; j++)
			{
				if(st[i].cid[j] == temp_cid)
				{
					printf("The Student's Details are:\n");
					printf("The First name is %s\n", st[i].fname);
					printf("The Last name is %s\n", st[i].lname);
					printf("The GPA is %f\n", st[i].GPA);
					printf("-----------------------------------\n");

					cid_flag = 1;
					break;
				}
			}
		}
	}

	if(cid_flag == 0)
		printf("[ERROR] Course ID %d not found!\n", temp_cid);

}
void tot_s()
{
	printf("[INFO] The total number of students is %d\n", StudentCount);
	printf("[INFO] You can add up to %d students\n", MaxStudents);
	printf("[INFO] You can add %d more students\n", MaxStudents - StudentCount);

}
void del_s()
{
	int temp_roll;

	printf("Enter the Roll Number which you want to delete: ");
	scanf("%d",&temp_roll);
	printf("-----------------------------------\n");

	if(st[temp_roll - 1].roll != 0)
	{
		st[temp_roll - 1] = st_del; // delete student entry using an empty student struct
		printf("[INFO] STUDENT DELETED!\n");
	}
	else
	{
		printf("[ERROR] This Roll Number %d is not found!\n", temp_roll);
	}

}
void up_s()
{
	int temp_roll, up_choice, new_roll, i;

	printf("Enter the Roll Number to update the entry: ");
	scanf("%d",&temp_roll);
	printf("-----------------------------------\n");

	if(temp_roll <= MaxStudents && temp_roll > 0)
	{
		if(st[temp_roll - 1].roll != 0)
		{

			printf("which info do you want to update?\n");
			printf("1. First Name\n");
			printf("2. Last Name\n");
			printf("3. Roll Number\n");
			printf("4. GPA\n");
			printf("5. Course IDs\n");
			printf("choose from [1 - 5]: ");
			scanf("%d",&up_choice);

			switch(up_choice)
			{
			case 1:
				printf("Enter the new first name: ");
				scanf("%s",st[temp_roll -1].fname);
				printf("[INFO] UPDATED SUCCESSFULLY!\n");
				break;

			case 2:
				printf("Enter the new last name: ");
				scanf("%s",st[temp_roll -1].lname);
				printf("[INFO] UPDATED SUCCESSFULLY!\n");
				break;

			case 3:
				printf("Enter the new roll number: ");
				scanf("%d",&new_roll);

				if(st[new_roll - 1].roll == 0)
				{
					st[new_roll - 1] = st[temp_roll - 1]; //switch structure to new roll number index
					st[new_roll - 1].roll = new_roll;     //assigning new roll number
					st[temp_roll - 1] = st_del;           //delete old structure

					printf("[INFO] UPDATED SUCCESSFULLY!\n");
				}
				else
				{
					printf("[ERROR] Roll Number already exists!\n");
				}
				break;

			case 4:
				printf("Enter the new GPA: ");
				scanf("%f",&st[temp_roll - 1].GPA);
				printf("[INFO] UPDATED SUCCESSFULLY!\n");
				break;

			case 5:
				for(i = 0; i < 5 ; i++)
				{
					printf("Enter New Course %d ID: ", i + 1);
					scanf("%d",&st[temp_roll - 1].cid[i]);
				}
				printf("[INFO] UPDATED SUCCESSFULLY!\n");
				break;

			default:
				printf("[ERROR] Invalid choice!\n");
				break;
			}
		}
		else
			printf("[ERROR] Roll Number is not registered!\n");

	}
	else
		printf("[ERROR] Roll number out of bounds! Roll number has to be from [1 - %d]\n",MaxStudents);
}
void show_s()
{
	int i, j;
	char show_flag = 0;

	for(i = 0 ; i < MaxStudents ; i++)
	{
		if(st[i].roll != 0)
		{
			printf("-----------------------------------\n");
			printf("The Student's Details are:\n");
			printf("The Roll Number is %d\n", st[i].roll    );
			printf("The First name is %s\n", st[i].fname);
			printf("The Last name is %s\n", st[i].lname);
			printf("The GPA is %f\n", st[i].GPA);
			printf("ID of each course \n");

			for(j = 0; j < 5 ; j++)
				printf("Course %d ID: %d \n", j + 1, st[i].cid[j]);

			show_flag = 1;
		}
	}

	if(show_flag == 0)
		printf("[No Registered Students]\n");

}
