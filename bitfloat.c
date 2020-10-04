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
	// printf("\n");
}

int range_int(int* binary_num, int a, int b){
	int temp = 0;
	int temp_bin[8];
	int j = 0;

	for (int i = a; i< b; i++){
		// printf("%d", binary_num[i]);
		temp_bin[j] = binary_num[i];
		j = j+1;
	}

	for (int x = 0; x < 8; x++){
		if (temp_bin[x]){
			temp = temp + (1 << (7 - x));
		}
	}
	// printf("\n");
	return temp;
}

int to_int(int* binary_num){
	int temp = 0;

	for (int i = 31; i >= 0; i--){
		if (binary_num[i]){
			temp = temp + (1 << (31 - i));
			// printf("bit 1 at pos %d. temp = %d\n", 31-i, temp);
		}
		// temp = temp + (bit << (31 - i));
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

	// for(int i = 0; i < 32; i++){
	// 	printf("%d", binary_num[i]);
	// }
	// printf("\n");

	// printf("%d\n", to_int(&binary_num[0]) + 1);
	// printf("done\n");
  return to_int(&binary_num[0]);
}

// Return the most significant byte of unsigned int n
char get_most_significant_byte(unsigned int n)
{
  // TODO: Your code here.
  int* binary_num = (int*) malloc(sizeof(int)* (4 * 8));
  to_binary(n, &binary_num[0]);
  int most_sig_bit = 0;

	for (int i = 0; i <= 31; i++){
		if (binary_num[i]){
			most_sig_bit =  31 - i;
			break;
		}
	}

	// printf("\nmost sig bit = %d\n", most_sig_bit);
	int temp = most_sig_bit + 1;

	while ((temp - 8) > 7){
		temp = temp - 8;
	}

	// for check
	if (temp - 8 != 0){
		temp = temp - 8;
	}

	// for(int i = 0; i < 32; i++){
	// 	printf("%d", binary_num[i]);
	// }
	// printf("\n");
	// printf("temp = %d\n", temp);

	int temp2 = 0;
	if(temp < 8){
		return range_int(&binary_num[0], 0, 8);
	} else if (temp < 16){
		return range_int(&binary_num[0], 8, 16);
	} else if (temp < 24){
		return range_int(&binary_num[0], 16, 24);
	} else {
		return range_int(&binary_num[0], 24, 32);
	}
}


// Return true if n1+n2 causes overflow, return false otherwise
bool sum_overflowed(int n1, int n2)
{
  int result = n1 + n2;
  if (n1 > 0 && n2 > 0 && result < 0){
  	return 1;
  } else if (n1 < 0 && n2 < 0 && result > 0){
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

	return exponent;
  //printf("%d\n%d\n%.20lf\n",  sign, exponent, mantissa);
}

