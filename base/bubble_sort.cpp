#include <stdio.h>

void printArr(int arr[], int size){
  for(int j = 0; j < size; j++){
   printf("%d ", arr[j]);
 }
 printf("\n");
}

int main(){
  char y;
  int arr[10];
  int i = 0;
  do{
   scanf("%d", &arr[i]);
   i++;
  }while((y=getchar()) != '\n');
  
 printArr(arr, i); 

 int n = i;
 bool sorted = false;
 while(!sorted){
 sorted = true;
 for(int j =1; j < n; j++){
    if(arr[j-1] > arr[j]){
      int x = arr[j-1];
      arr[j-1] = arr[j];
      arr[j] = x;
      sorted = false;
    }
 }
printArr(arr, i); 
 n--;

 }
 
}
