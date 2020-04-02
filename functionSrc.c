#include "functionSrc.h"


/*
reads everything from a file appended as a formal param
including marks of students
launches additional function
that allocates students in a linked list
*/
void readStudents(FILE* fpInput, Node** ppHeadRef) {

// allocate student for filling the other ones
  Node* pStudInf;
  pStudInf = (Node*)malloc(sizeof(struct Student));

// checking for correct allocation
  if (!pStudInf) {
  	printf("[SysMsg Memory cannot be allocated!]\n");
  	exit(0);
  }
  if(fpInput) {
    fseek(fpInput, 0, SEEK_END);
    int sizeOfFile = ftell(fpInput);
    if(sizeOfFile == 0) {
        printf("[SysMsg File is empty!]\n");
        exit(0);
    }
    if(sizeOfFile > 10000) {
        printf("[SysMsg Too many characters. Not enough memory!]\n");
        exit(0);
    }
  }
  fseek(fpInput, 0, SEEK_SET);
// checking for the end of file
  while(!feof(fpInput)) {

    if(fscanf(fpInput, "%s %s %d %d %d",
      pStudInf->SStudent.szSurname,
      pStudInf->SStudent.szName,
      &(pStudInf->SStudent.stStudentBirthday.mDay),
	  &(pStudInf->SStudent.stStudentBirthday.mMonth),
      &(pStudInf->SStudent.stStudentBirthday.mYear)) != 5)
        exit(0);
    if( (pStudInf->SStudent.stStudentBirthday.mDay) > 31 || (pStudInf->SStudent.stStudentBirthday.mDay) < 1) {
      printf("Incorrect date");
      exit(0);
    }
    if( (pStudInf->SStudent.stStudentBirthday.mMonth) > 12 || (pStudInf->SStudent.stStudentBirthday.mMonth) < 1) {
      printf("Incorrect date");
      exit(0);
    }
    if( (pStudInf->SStudent.stStudentBirthday.mYear) > 2020) {
      printf("Incorrect date");
      exit(0);
    }
    if((pStudInf->SStudent.stStudentBirthday.mMonth) == 3) {
        if(((pStudInf->SStudent.stStudentBirthday.mDay) > 29) || ((pStudInf->SStudent.stStudentBirthday.mDay) < 1)) {
            printf("Incorrect date");
            exit(0);
        }
    }

// check whether the reading was successful

    float fAverage = 0;
    int counter = 0;
    int k = 0;



    while(fscanf(fpInput, "%d", &(pStudInf->SStudent.iMarks[k])) == 1) {


      counter++;
      if(pStudInf->SStudent.iMarks[k] > 5 || pStudInf->SStudent.iMarks[k] < 1) {
        printf("Incorrect input");
        exit(0);
      }
      fAverage += (pStudInf->SStudent.iMarks[k]);

       k++;
    }
    if(counter != SUBCOUNT) {
        printf("Incorrect number of marks\n");
        printf("%d", counter);
        exit(0);
      }
    counter = 0;
    fAverage /= SUBCOUNT;
    pStudInf->SStudent.fAvgMark = fAverage;

    insertStudentIntoList(ppHeadRef, pStudInf);
  }
  printf("\n\n[SysMsg Reading has been done successfully!]\n\n");
}



/*
inserts a single student into list
based on its average mark
Protected function from NULL-head
and other issues
*/
void insertStudentIntoList(Node** ppHeadRef, Node* pStud) {
  Node* pNewNode = (Node*)malloc(sizeof(struct Student));
// check for successful allocation
  if(pNewNode) {
    pNewNode->SStudent = pStud->SStudent;

    if(*ppHeadRef == NULL) {
      *ppHeadRef = pNewNode;
      pNewNode->mNext = NULL;
    } else {
      if(((*ppHeadRef)->SStudent.fAvgMark) <= (pNewNode->SStudent.fAvgMark)) {
        pNewNode->mNext = *ppHeadRef;
        *ppHeadRef = pNewNode;

      } else {
        Node* pTemp = *ppHeadRef;

        while(pTemp->mNext != NULL && (pTemp->mNext->SStudent.fAvgMark) > pNewNode->SStudent.fAvgMark) {
          pTemp = pTemp->mNext;
        }

        if(pTemp->mNext == NULL) {
          pNewNode->mNext = NULL;
          pTemp->mNext = pNewNode;

        } else {
          pNewNode->mNext = pTemp->mNext;
          pTemp->mNext = pNewNode;

        }
      }
    }
  } else {
      printf("[SysMsg Not enough memory for allocation!\n\nІ");
      exit(0);
  }

}
/*
function checks if there is a students
without any mark "5"
*/

void checkForLoser(Node* pHead) {
	// check for any element in the list
	if (pHead == NULL)
      return;
    Node* pTempNode = pHead;
    printf("You think you have bad marks? Check out these guys!\n");
    while(pTempNode) {
      int iFive = 0;
      for(int j = 0; j < SUBCOUNT; j++) {
        if(pTempNode->SStudent.iMarks[j] == 5) {
// checking whether student has at least 1 5-mark
          iFive++;
// if it's true quit the loop
          break;
        }
    }
    if(!iFive)
// if student has no 5 let this run

    printf("%10s | %10s | %02d | %02d | %4d | %2.2lf\n",
      pTempNode->SStudent.szName,
      pTempNode->SStudent.szSurname,
      pTempNode->SStudent.stStudentBirthday.mYear,
      pTempNode->SStudent.stStudentBirthday.mMonth,
      pTempNode->SStudent.stStudentBirthday.mDay,
      pTempNode->SStudent.fAvgMark);

// loop through
	pTempNode = pTempNode->mNext;
    }
}



/*
function that prints on the console
the information about current students
data base
*/

void showDataInList(Node* pHead) {

    if(pHead == NULL) {
        printf("The list is empty");
    }
    else {
        printf("The linked list data:\n");
        while(pHead){
          printf("%10s | %10s | %02d | %02d | %4d | %2.2lf\n",
            pHead->SStudent.szName,
            pHead->SStudent.szSurname,
            pHead->SStudent.stStudentBirthday.mYear,
            pHead->SStudent.stStudentBirthday.mMonth,
            pHead->SStudent.stStudentBirthday.mDay,
            pHead->SStudent.fAvgMark);


// loop through
            pHead = pHead->mNext;
        }
    }
}

/*
function contains a simple algorithm that allows it to compare
birthdays of two different students
*/

int compareBirthday(const Birthday *pBd1,const Birthday *pBd2) {

	if (pBd2->mYear - pBd1->mYear)
      return pBd2->mYear - pBd1->mYear;
	else if (pBd2->mMonth - pBd1->mYear)
	  return pBd2->mMonth - pBd1->mMonth;
// returns > 0 if Bd1 is older than Bd2
	else
	  return pBd2->mDay - pBd1->mDay;

}

/*
function determines the youngest and the oldest
students in the group
Protected from unexpected outcomes
Mutates state
Uses function "compareBirthday"
to determine who is older between two of the group
*/

void determineOldestYoungest(Node* pHead) {
	if (pHead == NULL)
	  return;

    Node* pTempNode = pHead;
    Node* pOldestStudent = pHead;
    Node* pYoungestStudent = pHead;
    while(pTempNode) {

      if(compareBirthday(&(pTempNode->SStudent.stStudentBirthday), &(pOldestStudent->SStudent.stStudentBirthday) ) > 0) {
                pOldestStudent = pTempNode;

      }
      if(compareBirthday(&(pTempNode->SStudent.stStudentBirthday), &(pOldestStudent->SStudent.stStudentBirthday) ) < 0) {
                pYoungestStudent = pTempNode;

      }

// loop through
       pTempNode = pTempNode->mNext;
    }
    printf("\nThe oldest student from this list is: %s %s\n", pOldestStudent->SStudent.szName,
        pOldestStudent->SStudent.szSurname);
    printf("\nThe youngest student from this list is: %s %s\n\n", pYoungestStudent->SStudent.szName,
        pYoungestStudent->SStudent.szSurname);
}

/*
function is created whether the current
student has mark "3" on first and third exams
doesn't mutate state
pure function
*/
int checkCondition(const int iMarks[]) {
// function-checker for first and third exam
    int iFlag = 0;
    if((iMarks[0] == 3) && (iMarks[2] == 3)) {
      iFlag = 1;
    }
    return iFlag;
}
/*
function for deleting student from list
based on condition that can be changed
impure function
mutates state
Protected from unexpected data
*/

void deleteNodeFromList(Node** ppHeadRef) {
    Node* pCurrentNode = *ppHeadRef, *pPrevNode;

// check whether head itself holds any occurrences of the key
    while(pCurrentNode && (checkCondition(pCurrentNode->SStudent.iMarks) > 0)) {
      *ppHeadRef = pCurrentNode->mNext;
      free(pCurrentNode);
      pCurrentNode = *ppHeadRef;

    }

// deleting all other occurrences
    while(pCurrentNode) {

        while(pCurrentNode && (checkCondition(pCurrentNode->SStudent.iMarks) == 0)) {
          pPrevNode = pCurrentNode;
          pCurrentNode = pCurrentNode->mNext;
        }

        if(pCurrentNode == NULL)
          return;

        pPrevNode->mNext = pCurrentNode->mNext;
        free(pCurrentNode);
        pCurrentNode = pPrevNode->mNext;

    }
}

/*
prints everything that is left in list to the file
pure function
doesn't mutate state
*/
void printWholeListToFile(Node* pHead, FILE* fpFileName) {
    while(pHead){
      fprintf(fpFileName, "%10s | %10s | %02d | %02d | %4d | %2.2lf\n",
              pHead->SStudent.szName,
              pHead->SStudent.szSurname,
              pHead->SStudent.stStudentBirthday.mYear,
			  pHead->SStudent.stStudentBirthday.mMonth,
			  pHead->SStudent.stStudentBirthday.mDay,
			  pHead->SStudent.fAvgMark);

// loop through
      pHead = pHead->mNext;
    }
}

/*
Function deletes everything from the list
and NULLs the head
MIGHT BE DANGEROUS WHEN USING WITHOUT
AWARENESS
MUTATES STATE COMPLETELY
*/
void deleteWholeList(Node** ppHeadRef) {
    Node* pCurrentNode = *ppHeadRef;
    Node* pNextNode;


// traverse the list and free all incoming nodes
    while(pCurrentNode) {
      pNextNode = pCurrentNode->mNext;
      free(pCurrentNode);
      pCurrentNode = pNextNode;
    }

    *ppHeadRef = NULL;
    printf("\n\n [SysMsg The list has been deleted successfully. Allocated memory is now free] \n");
}

/*
function that checks whether the input path
to the file is correct
*/

void correctString(char* ptr,const int iSizeOfPtr) {
    for (int i = 0; i < iSizeOfPtr; ++i) {
      if (ptr[i]== '\n') {
        ptr[i] = '\0';
        break;
      }
    }
}


