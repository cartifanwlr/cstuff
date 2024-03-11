  
#include<stdio.h>
 
int main()
{
  int arr[5] = { 0, 1, 2, 3, 4 };
  int *ptr = arr;
 
  printf("%p\n", ptr);

  int* nextptr = ptr + 3; 

  printf("%p\n", nextptr);

  int loc = (nextptr - ptr);

  printf("%p\n", loc);

  return 0;
}