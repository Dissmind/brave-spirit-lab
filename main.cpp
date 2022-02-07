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
 


bool Digit_2_4_6(int x) // проверка наличия цифр 2, 4, 6 
{ 
  bool flag = false; 
  int s; 
   
  while (x > 0) 
  { 
    s = x % 10; 
     
    if (s == 2 || s == 4 || s == 6) 
    { 
      flag = true; 
      break; 
    } 
     
    x = x / 10; 
  } 
   
  return flag; 
} 


 
void Del(PList &head) // удаление 
{ 
  PList pFirst;
  PList pSecond;

  pFirst = head->next; 
   
  while (pFirst != head) 
  { 
    if (!Digit_2_4_6(pFirst->data)) 
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
 


bool Digit_6_9(int value) // проверка наличия цифр 6, 9 
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
 


void Dubl(PList &head) // дублирование 
{ 
  PList pFirst; 
  PList pSecond;

  pFirst = head->next; 
   
  while (pFirst != head) 
  { 
    if (Digit_6_9(pFirst->data) == true) 
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
 


int Perv_Cifr(int value) 
{  
  while (value > 9) {
    value /= 10;
  }
     
  return value; 
} 
 


int Posled_Cifr(int value) 
{      
  return value % 10;    
} 
 


bool Proverka(PList &head) 
{ 
  PList pFirst;
  PList pSecond; 

  pFirst = head->next; 
  pSecond = pFirst->next; 
   
  while (pSecond != head) 
  { 
    if ((Perv_Cifr(pFirst->data) > Perv_Cifr(pSecond->data)) || (Posled_Cifr(pFirst->data) > Posled_Cifr(pSecond->data))) 
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
  // std::cout << "Start list:" << std::endl;
  // displayList(head);

  if (Proverka(head))
  {
    Del(head); 
    Dubl(head); 
  } 
  else 
  {
    Sort(head);
  }
     

  // TODO: For test
  // std::cout << std::endl << "Finish list:" << std::endl;
  // displayList(head);
     
  writeToFile(head); 

  return 0;
}