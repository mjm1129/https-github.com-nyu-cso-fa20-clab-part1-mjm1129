#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "ptr.h"

// Return the sum of all elements in the given array.  The array
// "arr" has "n" elements.  We must explicitly pass in the array size
// because C array does not contain size information.
//
// Here, we use pointer "arr", which points to the first element of array,
// to represent the array.  One can also write the function's signature as
// int array_sum(int array[], int n)
int array_sum(int *arr, int n)
{
  // TODO: Your code here.
  int temp = 0;
  for(int i = 0; i < n; i++){
    temp = temp + arr[i];
  }
  return temp;
}

// Copy the first n elements of array "src" into array "dst".
// We assume caller has already allocated an array
// of at least n elements as "dst".
void array_cpy(int *dst, int *src, int n)
{
  // TODO: Your code here.
  for(int i = 0; i < n; i++){
    src[i] = dst[i];
  }

}

// bubble_sort implements the bubble sort algorithm.
// https://en.wikipedia.org/wiki/Bubble_sort
// It is given an integer array "arr" of "n" elements.
// Upon return, the integer array should contain the sorted numbers
// in increasing order.
// You should use swap_int function you've already implemented in ptr.c
// when implementing bubble_sort (that's why we included ptr.h here)
void bubble_sort(int *arr, int n)
{
  // TODO: Your code here.
  int temp;
  for(int i = 0; i < n; i++){
    for(int j = 1; j <= n - 1; j++){
      if (arr[j-1] > arr[j]){
        swap_int(&arr[j-1], &arr[j]);
      }
    }
  }
}

//arr is a 4 byte array containing an integer in big endian format,
//i.e. arr[0] has the most significant byte...
//Convert the integer to little endian and return the converted int.
char big_to_little_endian(char *arr)
{
  // TODO: Your code here.
  int temp;
  for (int i = 0; i < 2; i++){
    temp = arr[i];
    arr[i] = arr[3-i];
    arr[3-i] = temp;
  }

  int* binary_num = (int*) malloc(sizeof(int)* (4 * 8));
  int current_num;
  int* temp_binary = (int*) malloc(sizeof(int)* (8));
  int pos = 0;

  int x;
  int bit;

  for (int i = 0; i < 4; i++){
    current_num = arr[i];

    for (int j = 7; j >= 0; j--){
      x = current_num >> j;

      if (x & 1){
        temp_binary[7 - j] = 1;
      } else {
        temp_binary[7 - j] = 0;
      }
    }


    for (int j = 0; j < 8; j++){
      bit = temp_binary[j];
      // printf("%d", temp_binary[j]);
      binary_num[pos] = bit;
      pos = pos+1;
      printf("pos %d = %d\n", pos, binary_num[pos]);
    }
    printf("\n");

  }
  // printf("\n");

  // for(int i = 0; i < 4; i++){
  //   for(int j = 0; j < 8; j++){
  //     printf("%d", temp_binary[j]);
  //     // binary_num[pos] = temp_binary[j];
  //     // pos = pos+1;
  //   }
  //   printf("\n");
  // }
  // printf("\n");

  for (int i = 0; i < 32; i++){
    printf("%d", temp_binary[i]);
  }
  printf("\n");

  return 0x0;
}


// for (int i = 31; i >= 0; i--){
// 		temp = input_num >> i;

// 		if (temp & 1){
// 			binary_num[31 - i] = 1;
// 		} else {
// 			binary_num[31 - i] = 0;
// 		}
// 	}