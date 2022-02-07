#include <stdio.h> 
#include <stdlib.h> 
#include <cmath> 
#include <iostream>
 
/*  
Лабораторная работа №15. 
Вариант - 4. 
 
Ввести последовательность натуральных чисел. 
Если последовательность упорядочена по не убыванию первой или последней цифры,  
удалить из последовательности числа, 
в которые не входят цифры 2,4 и 6, и продублировать числа, 
содержащие цифры 6 и 9.  
В противном случае упорядочить последовательность по не убыванию. 
Последовательность хранить в двусвязном циклическом списке с фиктивным элементом. 

*/ 



using namespace std; 
 


struct List  
{ 
  int data; 
  struct List *next, *pred; 
};



typedef List *PList; 
 


void readToFile(PList &head)
{ 
  FILE *Fin; 
  Fin = fopen("input15.txt", "r"); 
  
  int temp; 

  PList pFirst; 
  PList pSecond; 
  
  head = new List; 

  head->data = 0; 
  head->next = NULL; 
  head->pred=NULL; 
  
  while (!feof(Fin)) 
  { 
    fscanf(Fin, "%d", &temp); 
    
    pFirst = new List; 
    pFirst->data = temp; 
     
    if (head->next == NULL) 
    { 
      head->next = pFirst; 
      pFirst->pred = head; 
    } 
     
    else 
    { 
     pSecond->next = pFirst; 
     pFirst->pred = pSecond; 
    } 
     
    pSecond = pFirst; 
  } 
   
  pFirst->next = head; 
  head->pred = pFirst; 

  fclose(Fin); 
} 



void writeToFile(PList &head)
{ 
  FILE *fileOut; 
  
  fileOut = fopen("output15.txt", "w"); 

  PList p; 
  p = head->next; 
   
  while (p != head) 
  { 
    fprintf(fileOut, "%d  ", p->data); 
    p = p->next; 
  } 
   
  fclose(fileOut); 
} 
 


bool checkDigital2_4_6(int value)
{  
  while (value > 0) 
  { 
    int lastNum = value % 10; 
     
    if 
      (
        lastNum == 2 || 
        lastNum == 4 || 
        lastNum == 6
      ) 
    { 
      return true;
    } 
     
    value /= 10; 
  } 
   
  return false; 
} 


 
void remove(PList &head, bool(*candition)(int)) 
{ 
  PList pFirst;
  PList pSecond;

  pFirst = head->next; 
   
  while (pFirst != head) 
  { 
    if (!checkDigital2_4_6(pFirst->data)) 
    { 
      pSecond = pFirst; 
      pFirst = pFirst->next; 
      
      pSecond->pred->next = pFirst; 
      pFirst->pred = pSecond->pred; 

      delete(pSecond); 
    } 
    else 
    {
      pFirst = pFirst->next;
    }  
  } 
} 
 


bool checkDigital6_9(int value) // проверка наличия цифр 6, 9 
{ 
  int temp; 
   
  while (value > 0) 
  { 
    temp = value % 10; 
     
    if (temp == 6 || temp == 9) 
    {  
      return true; 
    } 
     
    value = value / 10; 
  } 
   
  return false; 
} 
 


void dublication(PList &head, bool(*check)(int))
{ 
  PList pFirst; 
  PList pSecond;

  pFirst = head->next; 
   
  while (pFirst != head) 
  { 
    if (check(pFirst->data)) 
    { 
      pSecond = new List; 

      pSecond->data = pFirst->data; 
      pSecond->next = pFirst->next; 

      pFirst->next->pred = pSecond; 
      pFirst->next = pSecond; 

      pSecond->pred = pFirst; 

      pFirst = pFirst->next->next; 
    }  
    else 
    {
      pFirst = pFirst->next;
    } 
  } 
} 
 


int firstDigitalOnNum(int value) 
{  
  while (value > 9) {
    value /= 10;
  }
     
  return value; 
} 
 


int lastDigitalOnNum(int value) 
{      
  return value % 10;    
} 
 


bool checkTaskAlgorithm(PList &head) 
{ 
  PList pFirst;
  PList pSecond; 

  pFirst = head->next; 
  pSecond = pFirst->next; 
   
  while (pSecond != head) 
  { 
    if 
      (
        (firstDigitalOnNum(pFirst->data) > firstDigitalOnNum(pSecond->data)) || 
        (lastDigitalOnNum(pFirst->data) > lastDigitalOnNum(pSecond->data))
      ) 
    {  
      return true; 
    } 
     
    pFirst = pSecond; 
    pSecond = pSecond->next; 
  } 
   
  return false; 
} 


 
void Sort(PList &head) // упорядочивание по не убыванию 
{ 
  PList pActual;
  PList pNext; 

  pActual = head->next; 
   
  while (pActual->next != head) 
  { 
    pNext = pActual->next; 
     
    while (pNext != head) 
    { 
      if (pActual->data > pNext->data) 
      { 
        // Swap
        int x = pActual->data; 
        pActual->data = pNext->data; 
        pNext->data = x; 
      } 
       
      pNext = pNext->next; 
    } 
     
    pActual = pActual->next; 
  } 
} 



void displayList(PList &head) 
{
  PList p = head->next; 
   
  while (p != head) 
  { 
    std::cout << p->data << " ";

    p = p->next; 
  } 

  std::cout << std::endl;
}
 


int main () 
{ 
  PList head; 
  readToFile(head); 

  // TODO: For test
  std::cout << "Start list:" << std::endl;
  displayList(head);

  if (checkTaskAlgorithm(head))
  {
    remove(head, &checkDigital2_4_6); 
    dublication(head, &checkDigital6_9); 
  } 
  else 
  {
    Sort(head);
  }
     

  // TODO: For test
  std::cout << std::endl << "Finish list:" << std::endl;
  displayList(head);
     
  writeToFile(head); 

  return 0;
}