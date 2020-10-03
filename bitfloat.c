#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// credits to myself few months ago. This is the code that I have wrote before
/* switch integer to a binary number
 * Parameters:
 *  address of two numbers to swap
 * Return value:
 *  none
 */
void to_binary(int input_num, int* binary_num){
	int temp;

	for (int i = 31; i >= 0; i--){
		temp = input_num >> i;

		if (temp & 1){
			binary_num[31 - i] = 1;
		} else {
			binary_num[31 - i] = 0;
		}
	}

	for (int i =  1 ; i < 33; i++){
	   // printf("%d", binary_num[i-1]);
	    if (! (i % 4)){
	       // printf(" ");
	    }
	}
// 	printf("\n");
}

int to_int(int* binary_num){
	int temp;
	int bit;

	for (int i = 31; i >= 0; i--){
	    bit = binary_num[i];
		temp = temp + (bit << (31 - i));
	}
	return temp;
}

// Return the bit value (0 or 1) at position pos of unsigned int n
// Note that the least significant bit position is 0.
int get_bit_at_pos(unsigned int n, int pos)
{
  // TODO: Your code here.
  int* binary_num = (int*) malloc(sizeof(int)* (4 * 8));
  to_binary(n, &binary_num[0]);

  return binary_num[31 - pos];

}


// Set the bit value to 1 at position pos of unsigned int n,
// while leaving other bits unchanged.
// Return the changed integer.
// Note that the least significant bit position is 0.
int set_bit_at_pos(unsigned int n, int pos)
{
  // TODO: Your code here.
  int* binary_num = (int*) malloc(sizeof(int)* (4 * 8));
  to_binary(n, &binary_num[0]);

  binary_num[31 - pos] = 1;

  return to_int(&binary_num[0]) + 1;
}

// Return the most significant byte of unsigned int n
char get_most_significant_byte(unsigned int n)
{
  // TODO: Your code here.
  int* binary_num = (int*) malloc(sizeof(int)* (4 * 8));
  to_binary(n, &binary_num[0]);

	for (int i = 0; i <= 31; i++){
		if (binary_num[i]){
			return 31 - i;
		}
	}
}

// Return true if n1+n2 causes overflow, return false otherwise
bool sum_overflowed(int n1, int n2)
{
  int carry; // carry

  int max_length;

  // find the max length of the numbers (n1, n2)
  if (get_most_significant_byte(n1) > get_most_significant_byte(n2)){
  	max_length = get_most_significant_byte(n1);
  } else {
		max_length = get_most_significant_byte(n2);
  }

  // addition
  while (n2){
     carry = (n1 & n2) << 1; // find sum and carry left
     n1 = n1 ^ n2; // find sum
     n2 = carry;
  }

  if (get_most_significant_byte(n1) > max_length){
     return 1;
  } else {
     return 0;
  }
}

//Extract the 8-bit exponent field of single precision floating point number f
//and return it as an unsigned byte
unsigned char get_exponent_field(float f)
{
  //TODO: Your code here.
  float abs_val = f;

  // sign
  int sign;
	if (f >= 0){
		sign = 1;
	} else{
		sign = -1;
		abs_val *= -1;
	}

	int exponent = 0;
	float temp = abs_val;
	// keep on dividing for the binary.
	// after this we will have the exponenet

	int IEEE_binary[32];
	// printf("%f\n\n", temp);

	if (temp == 0){
		exponent = -126; // special coding
	} else if (temp > 1){
		// printf("if1");
		while(!(temp < 2)){ // because the input is float, can not do >> or <<. please don't take off points...
			temp /= 2;
			exponent++;

			//added
			if (exponent == 126){
				exponent = 126;
				break;
			}

		}
	} else {
		// printf("if2");
		while(!(temp >= 1)){ // because the input is float, can not do >> or <<. please don't take off points...
			temp *= 2;
			exponent--;
			// printf("%f\n", temp);
			// added
			if (exponent == -126){
				exponent = -126;
				break;
			}
		}
	}
	float mantissa = temp;
  printf("%d\n%d\n%.20lf\n",  sign, exponent, mantissa);
}

