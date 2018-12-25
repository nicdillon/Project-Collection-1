
/* Program that reimplements C's float-->int type casting behavior.

   Author: Nic Dillon
*/

#include <stdio.h>
#include "io.h"
#define BINARY_SHIFT 24


/* Returns the bytes comprising the given floating point value.

   For example, returns 0x4048f5c3 for the input value 3.14.

   Parameters:
       val - the floating point value whose IEEE-754 byte-level representation
             is desired.

   Returns:
       An unsigned int containing the bytes representing val.
*/
unsigned int floatToBytes(float val) {
    return *((int*)&val);
}


/* Returns the IEEE-754 floating point interpretation of the given 32-bit value.

   For example, returns 3.14 for the input value 0x4048f5c3.

   Parameters:
       bytes - a 32-bit value to be interpreted using the IEEE-754 standard.

   Returns:
       A floating point interpretation of the input bytes.
*/
float bytesToFloat(unsigned int bytes) {
    return *((float*)&bytes);
}

int* bytesToBits(unsigned int floatBits) {
    //go hex bit by hex bit and create binary value for that bitboard
    //add binary value to array of floatBits
    //find out how to and then convert bits to integer, then return integer
    int* binary = (int*) malloc(sizeof(int) * 32);
    for(int i = 0; i < 32; i++) {
      if(floatBits & (32 >> i)) {
        binary[i] = 1;

      }
      else {
        binary[i] = 0;
      }
    }
    return binary;
}

/* Returns the value of (int)floatBits using bit-level operations.

   Parameters:
       floatBits - the 32-bit value to be cast to an integer.

   Returns:
       The result of performing (int) floatBits. If the resulting value cannot
       be represented as an integer (because it is out of range, or because
       floatBits denotes NaN or +/- infinity), then 0x80000000 is returned.
*/
int floatToInt(unsigned int floatBits) {
  int newInt = 1;
  int exponent = 0;
  int* mantissa = (int*) malloc(sizeof(int) * 23);
  if(floatBits >> BINARY_SHIFT == 0x000000FF ||
     floatBits >> BINARY_SHIFT == 0x0000007F) {
    return 0x80000000;
  }
  int* binary = bytesToBits(floatBits);
  if(binary[0] == 1) {
    newInt *= -1;
  }
  for(int i = 0; i <= 7; i++) {
    if(binary[1 + i]) {
      exponent += 2 ^ (7 - i);
    }
  }
  if(binary[1] == 0) {
    return 0;
  }
  for(int i = 0; i <= 23; i++) {
    if((2 ^ i) > exponent) {
      break;
    }
    if(binary[8 + i]) {
      mantissa[i] = (2 ^ (23 - i));
    }
    else {
      mantissa[i] = 0;
    }
  }
  for(int i = 0; i < 23; i++) {
    newInt += mantissa[i] ^ (exponent - i);
  }
  return newInt;
}


/* Tester function */
int main() {
    unsigned int bytes = floatToBytes(3.14);
    printf("Casting 3.14 produces %d\n", floatToInt(bytes)); // 3
    return 0;
}
