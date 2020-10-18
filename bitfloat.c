#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void print_array(int *arr, int length); // just for debugging

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
	// printf("\n\nf = %f\n", f);
	float abs_val = f;
	int sign;
	
	if (f >= 0){
		sign = 0;
	} else{
		sign = 1;
		abs_val *= -1;
	}
	
//                    0,  1,  2,  3, 4, 5, 6, 7,   8,    9,    10
  //float base[11] = {128, 64, 32, 16, 8, 4, 2, 1, 0.5, 0.25, 0.125, };
  //int rep[11] =    {  0,  0,  0,  0, 0, 0, 0, 0,   0,    0,     0};
  //                    1    1  0   0  0  0  0  0  0
  float base[64];
  int rep[64];
  
  //fill in above
  float temp = 4294967296;
  int last_int_index = 32;
  
  for(int i = 0; i < 64; i++){
  	base[i] = temp;
  	rep[i] = 0;
  	temp = temp / 2;
  }

  int int_ver = abs_val;
  
  float dec_part = abs_val - int_ver;
  
  float int_part = abs_val - dec_part;
  //printf("%d\n", int_ver);
  for (int i = 0; i < 64; i++){
  	if (i <= last_int_index){					// int part
  		if (int_part / base[i] >= 1){
  			rep[i] = 1;
  			abs_val -= base[i];
  		}
  	} else {						// decimal part
  		// printf("%f left. next is %f\n", abs_val, base[i]);
  		if (abs_val >= base[i] && abs_val / base[i] >= 0){
  			rep[i] = 1;
  			abs_val -= base[i];
  		}
  	}
  	
  	if (abs_val == 0){
  		break;
  	}
  }

  // find first 1
  bool first_found = false;
  int index = 0;
  int one_pos;
  for(int i = 0; i < 64; i++){
  	if (!first_found && rep[i] == 1){
  		first_found = true;
  		one_pos = i;
  	}
  }
  //printf("pos: %d\n", one_pos);
  //print_array(&(rep[0]), 32);
  if (sign == 0){
  	return last_int_index - one_pos + 127;
  }
  else {
  	return last_int_index - one_pos + 127;
  }
}

void print_array(int *arr, int length){
	printf("\n");
	for (int i = 0; i < length; i++){
		printf("%d\t", i);
	}
	printf("\n");
	for (int i = 0; i < length; i++){
		printf("%d\t", arr[i]);
	}
	printf("\n\n");
}

