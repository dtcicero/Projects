/* 
 * The Data Lab, Tulane CMPS 2300, Spring 2023
 * 
 **********
 * STEP 0 * YOU MUST READ the rest of this comment and then put your name
 *        * in the place intended below.
 **********
 *
 * By putting your name below you agree that you understand the rules below:
 * 
 *
 * You must comment your code! Your solutions will receive no credit if they
 * are not accompanied (in this file) by adequate comments which explain
 * WHY your solution works.
 * 
 * Please note the emphasis above on the word why. Comments which merely
 * restate what the code does (“shift left by 31 bits”, “add one”) are not 
 * sufficient; these are obvious to your instructors who can also read C. 
 * Your comment must explain why you decided to perform that operation.
 *
 * Now please put your name and Tulane email address here, replacing
 * the example below:
 *
 *  DANIEL CICERO <dcicero@tulane.edu>
 */

/*
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will edit and hand in.
 *
 * NOTE: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0 /* Do not edit anything until you reach step 2 */
/******************************************************
 * STEP 1: Read the following instructions carefully. *
 ******************************************************/

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

You will ONLY turn in this file (bits.c), everything else
is provided to help you check your work.

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

REMINDER: Use the ./btest program to check your functions
          for correctness after making any changes. The
          program ./driver.pl will check for illegal
          operators and give you your final score.
#endif

/******************************************************************************
 * STEP 2: Modify the following functions according to the coding rules given *
 *                                                                            *
 *         You MUST explain each function in a comment                        *
 *         if you want to receive credit                                      *
 *****************************************************************************/

/***************************************************
 * BOOLEAN operations (8 puzzles, 18 points total) *
 ***************************************************/
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
/* ~(x & y) = (~x) | (~y) according to DeMorgan, and another ~ cancels this to (x | y) */ 
  int result = ~(~x & ~y);
  return result;
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
/* This works for the same reason as above, adhering to DeMorgan's Laws */
  int result = ~(~x | ~y);
  return result;
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 2
 */
int bitXor(int x, int y) {
/*This works because between (x&y) and (~x&~y), all values where the x bit
 * equals the y bit are selected for. We then take the opposite of these
 * with a further round of ~ to find where x != y, or XOR*/
  int result = ~(x & y) & ~(~x & ~y);
  return result;
}
/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
  /*This program works initially by determining the XOR between x and y. If
   *this value is 0, x = y, and the first ! operator returns 1. A second !
   *is then added, returning 0 for x = y and 1 for x != y */
  int result = !!(x ^ y);
  return result;
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
/* This works by first applying a bit mask to x by using (x & 1) to reveal the
 * LSB of x. This bit was then left shifted by 31, then right-shifted by 31
 * back to copy all bits to itself. */
  int result = (x & 1) << 31;
  return (result >> 31);
}
/* 
 * specialBits - return bit pattern 0xffca3fff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int specialBits(void) {
/* This function works by taking the number 215, or 0xD7 in hexadecimal, which
 * is represented in bits as 1101 0111. These bits are then left-shifted 14
 * places  to create 0000 0000 0011 0101 1100 0000 0000 0000. This number is 
 * chosen because it has 1s precisely where the 0s of 0xffca3fff are. In other
 * words, 215 is the complement of 0xffca3fff, so applying ~ gets the answer*/
  return ~(0xD7 << 14);
}
/* 
 * conditional - same as x ? y : z (ternary operator)
 *   Examples: conditional(2,4,5) = 4
 *             conditional(0,4,5) = 5
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 4
 */
int conditional(int x, int y, int z) {
/* The "result" variable first assesses whether or not x == 0 with !x
 * x is then left-shifted 31 places, so that the result is either
 * a 1 or 0 followed by 31 0s. The bit is then right-shifted so the result is
 * 32 1s or 32 0s. If 1s, result is -1 and can be & to z because & with all 1s
 * is an identity property. Similarly,~result is 0 and cancels y entirely w/ &. 
 * Otherwise, result is all zeros, and is inverted to all 1s with ~, 
 * then & to y in the same identity process as above, while z is also cancelled
 * Finally, | chooses the non-cancelled int to complete the conditional */
  int result = ((!x) << 31) >> 31; 
  int answer = (~result & y) | (result & z);
  return answer;
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
/* This function works by successively folding x in half with bit-shifts, then 
 * using ^ to store the parity of the sections being compared. These bit-shifts
 *  move the "parity bit" right until it is the LSB, then a mask of & 1 is 
 * applied to get the final value into result. */
 int result = x ^ (x >> 1);
  result = result ^ (result >> 2);
  result = result ^ (result >> 4);
  result = result ^ (result >> 8);
  result = result ^ (result >> 16);  
  return result & 1;
}
/*******************************************
 * INTEGERS *
 *******************************************/
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {
/*This works by flipping all the 0 bits of 0 to 1, which signifies -1*/
  return ~0;
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
/* Because of the signed bit being the MSB, the max 2s complement integer is 0
 * followed by 31 1s. (1 << 31) gets us 1 followed by 31 0s, and taking the 
 * complement with ~ gives us the answer */
 int result = ~(1 << 31);
  return result;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
/* This formula (~x + 1) works as an abstraction of Two's complement, which
 * negates x */
  int result = (~x + 1);
  return result;
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
/*This program works by first moving the sign bit by 31 bits to the right,
 * and then masking to select for just that bit with & 1. If that bit
 * (the sign bit) is 1, x is negative. Otherwise, the bit is 0 and x is >= 0*/
  int result =(x >> 31) & 1;
  return result;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int isPositive(int x) {
/* This function determines if an integer is positive by first testing to make
 * sure it is non-negative and non-zero. The zero test (!) is built in, 
 * and I have just implemented a negative test above. Therefore, if a # is 
 * non-negative, OR (|) 0, it is positive and result is 1. */ 
  int result = !((x >> 31) & 1 | !x); 
  return result;
}

/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int addOK(int x, int y) {
  int result = !((x >> 31) ^ (y >> 31)) | (x >> 31) ^ ((x + y) >> 31);

  return result;
}

int absVal(int x) {
/* This function works by first using a bit mask of x >> 31 to determine the 
/* sign bit of x, which would also be all the other bits of x after the right
/* shift. If x >= 0, this bit pattern will be 00000000 etc..., which after
/* addition and XOR will not affect value. If x < 0, bit pattern will be
/* 11111111. (Result + x) adds the negative x to result. 
/* XOR with result preserves only the 0s of (result + x), which correlate to
/* the absolute value of x*/ 
  int result = x >> 31;
 
  
  return (result + x) ^ result;
}
/*************************************************************
