#include <stdio.h> 
#include <stdlib.h> 
#include <cmath> 
 
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
 
void Spisok(PList &head) 
{ 
  FILE *Fin; 
  Fin = fopen("input15.txt", "r"); 
  int x; 
  PList p, p1; 
  head = new List; 
  head->data = 0; 
  head->next = NULL; 
  head->pred=NULL; 
  
  while (!feof(Fin)) 
  { 
    fscanf(Fin, "%d", &x); 
    p = new List; 
    p->data = x; 
     
    if ((head->next) == NULL) 
    { 
      head->next = p; 
      p->pred = head; 
    } 
     
    else 
    { 
     p1->next = p; 
     p->pred = p1; 
    } 
     
    p1 = p; 
  } 
   
  p->next = head; 
  head->pred = p; 
  fclose(Fin); 
} 
 
void print_Spisok(PList &head) 
{ 
  FILE *Fout; 
  Fout = fopen("output15.txt", "w"); 
  PList p; 
  p = head->next; 
   
  while (p != head) 
  { 
    fprintf(Fout, "%d  ", p->data); 
    p = p->next; 
  } 
   
  fclose(Fout); 
} 
 
bool Digit_2_4_6(int x) // проверка наличия цифр 2, 4, 6 
{ 
  bool flag = false; 
  int s; 
   
  while (x > 0) 
  { 
    s = x % 10; 
     
    if (s == 2  s == 4  s == 6) 
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
  PList p, p1; 
  p = head->next; 
   
  while (p != head) 
  { 
    if (Digit_2_4_6(p->data) == false) 
    { 
      p1 = p; 
      p = p->next; 
      p1->pred->next = p; 
      p->pred = p1->pred; 
      delete(p1); 
    } 
     
    else p = p->next; 
  } 
} 
 
bool Digit_6_9(int x) // проверка наличия цифр 6, 9 
{ 
  bool flag = false; 
  int s; 
   
  while (x > 0) 
  { 
    s = x % 10; 
     
    if (s == 6 || s == 9) 
    { 
      flag = true; 
      break; 
    } 
     
    x = x / 10; 
  } 
   
  return flag; 
} 
 
void Dubl(PList &head) // дублирование 
{ 
  PList p, p1; 
  p = head->next; 
   
  while (p != head) 
  { 
    if (Digit_6_9(p->data) == true) 
    { 
      p1 = new List; 
      p1->data = p->data; 
      p1->next = p->next; 
      p->next->pred = p1; 
      p->next = p1; 
      p1->pred = p; 
      p = p->next->next; 
    } 
     
    else  
      p = p->next; 
  } 
} 
 
int Perv_Cifr(int x) 
{ 
  int y = x; 
   
  while (y > 9) 
    y = y / 10; 
     
  return y; 
} 
 
int Posled_Cifr(int x) 
{ 
  int y = x; 
   
  y = y % 10; 
     
  return y;    
} 
 
bool Proverka(PList &head) 
{ 
  bool flag = false; 
  PList p, p1; 
  p = head->next; 
  p1 = p->next; 
   
  while (p1 != head) 
  { 
    if ((Perv_Cifr(p->data) > Perv_Cifr(p1->data)) || (Posled_Cifr(p->data) > Posled_Cifr(p1->data))) 
    { 
      flag = true; 
      break; 
    } 
     
    p = p1; 
    p1 = p1->next; 
  } 
   
  return flag; 
} 
 
void Sort(PList &head) // упорядочивание по не убыванию 
{ 
  PList p, p1; 
  int x; 
  p = head->next; 
   
  while ((p->next) != head) 
  { 
    p1 = p->next; 
     
    while (p1 != head) 
    { 
      if ((p->data) > (p1->data)) 
      { 
        x = p->data; 
        p->data = p1->data; 
        p1->data = x; 
      } 
       
      p1 = p1->next; 
    } 
     
    p = p->next; 
  } 
} 
 
main () 
{ 
  PList head; 
  Spisok(head); 
   
  if (Proverka(head) == true) 
  { 
    Del(head); 
    Dubl(head); 
  } 
   
  else 
    Sort(head); 
     
  print_Spisok(head); 
}