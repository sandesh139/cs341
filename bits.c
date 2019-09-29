 /* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Ratiing: 2
 */
int allEvenBits(int x) {
/*here the patteren of 0101 0101 0101... is made for 32 bits by using 0x5 and then "AND" with the ones complement of x. so, if all even bits are one then the result will get to zero. And the result is returned. 
*/  
return !(((((((0x5<<4)|0x5)<<8)|((0x5<<4|0x5)))<<16)|((((0x5<<4)|0x5)<<8)|((0x5<<4|0x5))))&(~x));
}


/*
 *: bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {

/*Doing Xor in first half number(16) of bits to its other half(16). And then the bits are 
 * shifted for another xor in between 8 first bits of second half 16 bits. and so on until we shift by 1 
*/
x = x^(x>>16);
x =x^(x>>8);
x = x^(x>>4);
x = x^(x>>2);
x = x^(x>>1);
return x&0x1;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
//making the truth table of &, ^, and | gives total sense for this answer.
  return (~(x&y))&(~(~x&~y));
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 b<= c <= 255
 *   Legal ops: ! ~ vim & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
   return (~(0xFF<< (n<<3))&x)|(c<<(n<<3));
}
/* 
 * TMax - return maximum two's cemplement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  return ~(1<<((1<<5)-1));
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
/*here we will see if x remains same as befors if xold - xnew =0 then we return !0. since negative sign is not allowed we do -x = ~x +1.
*/
   return !(x + (~((x<<(32+~n+1))>>(32+~n+1)))+1);
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
//if x-y=0 then they are equal. Here -y = ~y+1
  return !(x+~y+1);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
//we will just check the first bit for the problem
  return !(x&(1<<31))&(!(!x));

}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {

/*here we donot have the overflow if both number are positive or if both number are negative so if we Xor the x>>31 and y>>31 we can return the logical not, which is true with value 1. Then we can or with another part. For Second par, we will only check two cases: case 1. if x is positive and y is negative the result should be positive since x-(-y) = x+y when there is no overflow. case 2. If x is negative then y should be positive and the result x-y should be negative. SO, we can do the XOR in between the sign bit of x and result. and return the not logical of result. 
*/
  return (!((x>>31)^(y>>31))|(!(((x+(~y)+1)>>31)^(x>>31))));
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
/*if there is any negative number, we will convert it to its two bits complement in the following lines of code.
*/

int positive = x ^(x>>31);

/* now we will check if it requires more than 16 bits or not. if it requires more than 16 bit, we will get at least 16 bit in a1 variable and then shift bit by 16. Otherwise a1 will be left as zero.
*/
int a1 = (!(!(positive>> 16)))<<4;

//now we can shift positive by 16 or 0. If a1 is 16 then by 16 otherwise 0.

positive = positive >>a1;

//now we will do the same checking and shifting for 8 as we did for 16
int a2 = (!(!(positive>> 8)))<<3;
positive = positive >>a2;

//now for 4.
int a3 = (!(!(positive>> 4)))<<2;
positive = positive >>a3;

//now for 2.
int a4 = (!(!(positive>> 2)))<<1;
positive = positive >>a4;

//now for 1.
int a5 = (!(!(positive>> 1)));

//now we can return the total sum of the a1 through a5 and the sign bit and for the last a5.
int sum = a1 +a2+a3+a4+a5+2;
int checkZero = (!(!(positive))<<31)>>31;

int ifZero = !positive;
  return (sum&checkZero)|ifZero;
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
//first making the number positive
unsigned positive = uf & 0x7FFFFFFF;
/*we know number when exponent(Exp) is 1111111 with hexadecmial representation of greater than 0x7f800000.
*/
if (positive>0x7f800000)
{
    return uf;
}
return positive;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {

/* in this problem we mainly deal with the exponent and fraction part.*/
 unsigned exponent = uf & 0x7f800000;       //this gives the exponent part(first bit is taken care in following 2nd step)
unsigned fraction = uf & 0x7fffff;          //this gives the fraction part
unsigned signUf = (uf>>31)&0x1;             //this gives the first bit.
if(exponent ==0x7f800000){                 //this is exponent with all ones in it, which is not a number NaN
return uf;
}
if(exponent==0)                             //denormailzed case
{
	fraction =fraction<<1;
	fraction = fraction & 0x7fffff;     //getting 23 fraction
	if(fraction & 0x00400000){
		exponent = 0x00800000;  //getting exponent as 1
	}
} else{
	unsigned exponentTest = exponent + 0x00800000;  // adding an one in exponent gives
	if(exponentTest==0x7f800000){      //checking if exp gets to infinity                  
		fraction = 0;               
	}
	exponent = exponent+ 0x00800000;
}
return (signUf<<31)|exponent|fraction;
}



/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x)
{

	int allOnesorZero = (x>>31);
	int eighth = x>>3;
	int remainder = x&0x7;
	int fiveTimesEighth  = (eighth<<2)+eighth;
	remainder = (remainder << 2)+remainder;
	int add = allOnesorZero & 0x7;
	remainder = remainder + add;
	remainder = remainder>>(0x3);
	int result = fiveTimesEighth+remainder;

return result;
}

