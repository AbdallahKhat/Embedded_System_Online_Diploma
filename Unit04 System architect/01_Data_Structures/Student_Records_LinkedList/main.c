/*
 * main.c
 *
 *  Created on: Feb 2, 2023
 *      Author: abdal
 */


#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"

struct Sdata{
	int ID;
	char name[40];
	float height;
};

struct SStudent
{
	struct Sdata student;
	struct SStudent* pNextStudent;
};

struct SStudent* gpFirststudent = NULL;

void Add_Student()
{
	struct SStudent* pNewStudent;
	struct SStudent* pLastStudent;
	char temp_text[40];
	//Check list is empty
	if(gpFirststudent == NULL){
		//assign new record
		pNewStudent = (struct SStudent*) malloc(sizeof(struct SStudent));
		//assign it to gpfirst
		gpFirststudent = pNewStudent;
	}
	else	//list contains records
	{
		//navigate until last record
		pLastStudent = gpFirststudent;
		while(pLastStudent->pNextStudent)
			pLastStudent=pLastStudent->pNextStudent;
		//create new record
		pNewStudent = (struct SStudent*) malloc(sizeof(struct SStudent));
		pLastStudent->pNextStudent=pNewStudent;
	}

	//fill new record
	printf("\nEnter student ID: ");
	gets(temp_text);
	pNewStudent->student.ID = atoi(temp_text);
	printf("\nEnter student name: ");
	gets(pNewStudent->student.name);
	printf("\nEnter student height: ");
	gets(temp_text);
	pNewStudent->student.height = atof(temp_text);


	//set the next pointer (newstudent) null
	pNewStudent->pNextStudent = NULL;

}

int delete_student()
{
	char temp_text[40];
	int selected_id;

	printf("\nSelect student ID to be deleted: ");
	gets(temp_text);
	selected_id = atoi(temp_text);

	//check if list is empty
	if(gpFirststudent)
	{
		struct SStudent* pSelectedStudent = gpFirststudent;
		struct SStudent* pPreviousStudent = NULL;

		//loop on all records
		while(pSelectedStudent)
		{
			//compare each node with selected ID
			if(pSelectedStudent->student.ID == selected_id)
			{
				if(pPreviousStudent)	//ID is not the first student
				{
					pPreviousStudent->pNextStudent=pSelectedStudent->pNextStudent;
				}
				else 	//ID = First Student
				{
					gpFirststudent= pSelectedStudent->pNextStudent;
				}
				free(pSelectedStudent);
				return 1;
			}
			pPreviousStudent=pSelectedStudent;
			pSelectedStudent=pSelectedStudent->pNextStudent;
		}
		printf("\nInvalid student ID");
		return 0;
	}
	printf("\nEmpty student records");
	return 0;
}

void view_students()
{
	int count = 0;
	struct SStudent* pCurrentStudent = gpFirststudent;

	if(gpFirststudent == NULL){
		printf("/nThe Record is Empty");
	}
	else{
		while(pCurrentStudent)
		{
			printf("\nRecord number %d",count + 1);
			printf("\n \t ID:%d",pCurrentStudent->student.ID);
			printf("\n \t Name:%s",pCurrentStudent->student.name);
			printf("\n \t Height:%f",pCurrentStudent->student.height);
			pCurrentStudent = pCurrentStudent->pNextStudent;
			count++;
		}
	}
}

void delete_all()
{
	int count = 0;
	struct SStudent* pCurrentStudent = gpFirststudent;

	if(gpFirststudent == NULL){
		printf("\nThe Record is Empty");
	}
	else
	{
		while(pCurrentStudent)
		{
			struct SStudent* pTempStudent = pCurrentStudent;
			pCurrentStudent = pCurrentStudent->pNextStudent;
			free(pTempStudent);
			count++;
		}
	}
}

void GetNth()
{
	int index, count = 1;
	char temp_text[40];
	struct SStudent* pCurrentStudent = gpFirststudent;

	printf("\nType Index number: ");

	gets(temp_text);
	index = atoi(temp_text);

	while(1)
	{
		if(pCurrentStudent)	//list is not empty
		{
			if(index == count)	//Print correct record number
			{
				printf("\nRecord number %d",count);
				printf("\n \t ID:%d",pCurrentStudent->student.ID);
				printf("\n \t Name:%s",pCurrentStudent->student.name);
				printf("\n \t Height:%f",pCurrentStudent->student.height);
				break;
			}
			else		//Index != count
			{
				pCurrentStudent=pCurrentStudent->pNextStudent;
				count++;
			}
		}
		else
		{
			printf("\nNo record");
			break;
		}
	}
}

int link_length(struct SStudent* pCurrentStudent)
{
	if(pCurrentStudent) //Reaches NULL or empty list
		return 0;
	else
		return 1 + link_length(pCurrentStudent->pNextStudent); //Recursive count
}

int GetNthBack()
{
	int index, count = 0;
	char temp_text[40];
	struct SStudent* pRef,* pMain;
	pRef = pMain = gpFirststudent;

	printf("\nType Index number: ");

	gets(temp_text);
	index = atoi(temp_text);

	//Increment pRef amount of index number
	while(count != index)	//Loop until Count = Index
	{
		if(pRef)	//pReference != NULL
		{
			pRef = pRef->pNextStudent;
			count++;
		}
		else		//pReference = NULL , count != index
		{
			printf("/nInvalid Index number");
			return 0;
		}
	}

	//Move pMain & pRef till pRef = NULL (End of List)
	while(pRef)
	{
		pRef=pRef->pNextStudent;
		pMain=pMain->pNextStudent;
	}

	//Print Correct record
	printf("\n \t ID:%d",pMain->student.ID);
	printf("\n \t Name:%s",pMain->student.name);
	printf("\n \t Height:%f",pMain->student.height);
	return 1;
}

int middle_record()
{
	struct SStudent* pFast,* pSlow;
	pFast = pSlow = gpFirststudent;
	int count = 1;

	if(gpFirststudent) // check if empty
	{
		while(pFast->pNextStudent)	//pFast isn't at last record
		{
			pFast = pFast->pNextStudent->pNextStudent;
			pSlow = pSlow->pNextStudent;
			count++;
			if(pFast) 				//in case of even no. of records
			{
				printf("\nRecord number %d",count);
				printf("\n \t ID:%d",pSlow->student.ID);
				printf("\n \t Name:%s",pSlow->student.name);
				printf("\n \t Height:%f",pSlow->student.height);
				return 1;
			}
			else if(pFast->pNextStudent) 	//in case of odd no. of records
			{
				printf("\nRecord number %d",count);
				printf("\n \t ID:%d",pSlow->student.ID);
				printf("\n \t Name:%s",pSlow->student.name);
				printf("\n \t Height:%f",pSlow->student.height);
				return 1;
			}
		}
		printf("\nRecord number %d",count);
		printf("\n \t ID:%d",pSlow->student.ID);
		printf("\n \t Name:%s",pSlow->student.name);
		printf("\n \t Height:%f",pSlow->student.height);
		return 1;
	}
	printf("\nList is empty");
	return 0;
}

int reverse_list()
{
	struct SStudent* pHead,* pNext,* pPrev;
	pHead = pNext = pPrev = gpFirststudent;

	//check if empty
	if(gpFirststudent)
	{
		pNext = pNext->pNextStudent;
		pHead = pNext;
		pPrev->pNextStudent = NULL;

		while(pNext)	//list with multiple records
		{
			pNext = pNext->pNextStudent;
			pHead->pNextStudent = pPrev;
			pPrev = pHead;
			pHead = pNext;

			if(pNext == NULL)
			{
				gpFirststudent = pPrev;
				printf("\nReverse is done");
				return 1;
			}
		}
		//list with one record only
		printf("\nReverse is done");
		return 1;

	}
	else
		printf("\nList is empty");
	return 0;
}

int main()
{

	char temp_text[40];

	while(1)
	{
		printf("\n========================");
		printf("\nSelection option from the following");
		printf("\n1 : Add Student");
		printf("\n2 : Delete Student");
		printf("\n3 : View Student");
		printf("\n4 : Delete all");
		printf("\n5 : View Nth Index");
		printf("\n6 : View length of list");
		printf("\n7 : View Nth Index from the end of list");
		printf("\n8 : View Middle record");
		printf("\n9 : Reverse list");
		printf("\n========================\n");

		gets(temp_text);
		printf("========================\n");

		switch(atoi(temp_text))
		{
		case 1:
			Add_Student();
			break;
		case 2:
			delete_student();
			break;
		case 3:
			view_students();
			break;
		case 4:
			delete_all();
			break;
		case 5:
			GetNth();
			break;
		case 6:
			printf("/nLength of list is = %d",link_length(gpFirststudent));
			break;
		case 7:
			GetNthBack();
			break;
		case 8:
			middle_record();
			break;
		case 9:
			reverse_list();
			break;
		default:
			printf("\nInvalid option.. try again");
			break;
		}
	}
	return 0;
}
