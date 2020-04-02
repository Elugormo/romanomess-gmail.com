#include <stdio.h>
#include <stdlib.h>
#include "functionSrc.c"
#include <string.h>



int main()
{

    FILE *fin;
    FILE *fout;
    fout = fopen("result.txt", "w+");
    Node *pHead = NULL;
    char cAddress[SIZE];
    int iVal = 1;
    do {
      if (iVal) {
        printf("Enter address of text file\t\n");
        --iVal;
      } else {
          printf("Something went wrong. File was not opened. Try again\t\n");
        }
      fgets(cAddress, SIZE - 1, stdin);
      correctString(cAddress, SIZE);
      fin = fopen(cAddress, "r");
    } while(!fin);

    readStudents(fin, &pHead);
    showDataInList(pHead);
    checkForLoser(pHead);
    determineOldestYoungest(pHead);
    deleteNodeFromList(&pHead);
    showDataInList(pHead);
    printWholeListToFile(pHead, fout);
    deleteWholeList(&pHead);
    return 0;
}
