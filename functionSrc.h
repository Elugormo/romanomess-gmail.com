#ifndef FUNCTIONSRC_H_INCLUDED
#define FUNCTIONSRC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define SIZE 200
#define SUBCOUNT 8
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct {
    int mYear, mMonth, mDay;
} Birthday;

struct Person {
    char szName[SIZE];
    char szSurname[SIZE];
    Birthday stStudentBirthday;
    int iMarks[SIZE];
    float fAvgMark;
};

typedef struct Student {
    struct Person SStudent;
    struct Student* mNext;
} Node;

void deleteWholeList(Node** ppHeadRef);
int checkCondition(const int iMarks[]);
void deleteNodeFromList(Node** ppHead);
void checkForLoser(Node* pHead);
void readStudents(FILE* fInput, Node** ppHead);
void insertStudentIntoList(Node** ppHead, Node* pStud);
void printList(Node*);
void determineOldestYoungest(Node* pHead);
int compareBirthday(const Birthday *pBd1,const Birthday *pBd2);
void printWholeListToFile(Node* pHead, FILE* fpFileName);

#endif // FUNCTIONSRC_H_INCLUDED
