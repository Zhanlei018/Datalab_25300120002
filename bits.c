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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  /*把1左移31位，得到最高位掩码*/
  int ans = 1 << 31;
  return ans;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /*x^y=~(~(x & ~y) & ~(~x & y))公式实现*/
  int Lpart = x & ~y;
  int Rpart = ~x & y;
  int All = ~Lpart & ~Rpart;
  All = ~All;
  return All;
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /*先求x的符号位掩码，1是负数，0是正数。然后将它与x的补码经过与门，得到答案*/
  int Xsign = x >> 31;
  int Xnega = ~x + 1;
  int ans =  Xsign & Xnega;
  return ans;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /*先算出X在src与dst的实际的左移量，然后把目标的被复制字节移到对应字节，再清空目标字节，二者取或，得到答案*/
  int Xsrc = src << 3;
  int Xdst = dst << 3;
  int Beifuzhi = (x >> Xsrc) & 255;
  int Xfuzhi = Beifuzhi << Xdst;
  int Mubiao = x & ~(255 << Xdst);
  int ans = Mubiao | Xfuzhi;
  return ans;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /*先得到X右移n位的数字，然后算x的符号掩码。把掩码右移n-1位，取反码求与*/
  int Xshift = x >> n;
  int all1 = 1 << 31;
  int high0 = (all1 >> n) << 1;
  int ans = Xshift & ~high0;
  return ans;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  /*助教我先做的19题，其实思路一样，先构造4位掩码wei4=11110000111100001111000011110000
  *然后用x右移4位与掩码 或上 x与掩码左移四位，即可得到四位交换
  */
  int wei4 = 0x0F;
  wei4 = wei4 + (wei4 << 8); 
  wei4 = wei4 + (wei4 << 16);
  x = ((x >> 4) & wei4) | ((x & wei4) << 4);
  return x;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /*用公式~x&(x+1)得到最低位的0，然后让x加上最低为0来抹去这个0，最后重复一遍上述操作，得到的就是倒数第二个0的mask*/
  int Xnega = ~x;
  int Xleast0 = Xnega & (x + 1);
  x = x + Xleast0;
  Xleast0 = Xnega & (x + 1);
  return Xleast0;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /*设立一个Xhalf，通过右移得到X的左半边，与x本身进行异或。重复5次，就可以得到一个两位的数字
  *这个两位的数字取与1，得到一个数，反转后就是要求的答案
  */
  int Xhalf = x >> 16;
  x = x ^ Xhalf;
  Xhalf = x >> 8;
  x = x ^ Xhalf;
  Xhalf = x >> 4;
  x = x ^ Xhalf;
  Xhalf = x >> 2;
  x = x ^ Xhalf;
  Xhalf = x >> 1;
  x = x ^ Xhalf;
  int ans = x & 1;
  return !ans;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /*先把n处理成31以内的正整数，然后把前半部分右移，掩码补0，后半部分左移，加起来就是答案*/
  n = n & 31;
  int Xlef = x << (33 + ~n);
  int Xrig = x >> n;
  int X0 = (1 << (33 + ~n)) + ~0;
  Xrig = Xrig & X0;
  int ans = Xlef + Xrig;
  return ans;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /*只要四舍五入后输出最高位的1就可以了，加上他自己的一般对应的2的n-1次方。商为偶数进位*/
  int Xhalf = 1 << (n + ~0);
  int Xquot = x >> n;
  int lef = (Xquot & 1) + Xhalf + ~0;
  int ans = x + lef;
  ans = ans >> n;
  ans = ans << n;
  return ans;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /*先算出x和y的向下取整的平均值，用(x & y) + ((x ^ y) >> 1)公式来防止溢出
  *然后提取X^Y的最高位，算出是谁大，运算求得xy
  *判断x+y是否为奇数，用它们算出偏移量是0还是1。与midpoint加上即可得到towardfirst的结果
  */
  int Midpoint = (x & y) + ((x ^ y) >> 1);
  int sign = (x ^ y) >> 31;
  int XYs = (sign & (x >> 31)) | (~sign & ((x + ~y + 1) >> 31));
  int XYji = (x ^ y) & 1;
  int Toward = ~XYs & XYji;
  Midpoint = Midpoint + Toward;
  return Midpoint;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /*先取abx的符号位，然后算AX和BX是否同号。然后用几个式子表达AXB三个数的单调小于关系，反转后得到大于等于关系
  *如果AB正好能把X放在比较中间，那么就输出1
  */
  int Xsign = x >> 31;
  int Asign = a >> 31;
  int Bsign = b >> 31;
  int SignAX = Xsign ^ Asign;
  int SignBX = Xsign ^ Bsign;
  int XjianA = x + ~a + 1;
  int AjianX = a + ~x + 1;
  int XjianB = x + ~b + 1;
  int BjianX = b + ~x + 1;
  int XxiaoyuA = (SignAX & Xsign) | (~SignAX & (XjianA >> 31));
  int XxiaoyuB = (SignBX & Xsign) | (~SignBX & (XjianB >> 31));
  int AxiaoyuX = (SignAX & Asign) | (~SignAX & (AjianX >> 31));
  int BxiaoyuX = (SignBX & Bsign) | (~SignBX & (BjianX >> 31));
  int XdayudengyuA = !XxiaoyuA;
  int BdayudengyuX = !BxiaoyuX;
  int XdayudengyuB = !XxiaoyuB;
  int AdayudengyuX = !AxiaoyuX;
  int AXB = XdayudengyuA & BdayudengyuX;
  int BXA = XdayudengyuB & AdayudengyuX;
  int ans = (AXB | BXA) & 1;
  return ans;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  /*这道题目太难了，试了几十次，终于做出来
  *先算出x的上限和下限，然后得到X和溢出进位的符号，算出是否会进位泄露，若都无则无泄漏
  *然后只有无泄漏，才能算5x输出
  *有泄露，则按位比较泄露和最大或者最小数输出
  */
  int MIN = 1 << 31;
  int MAX = ~MIN;
  int Limit1 = (0x19 << 24) | (0x99 << 16) | (0x99 << 8) | 0x99;
  int Limit2 = ~Limit1;
  int Xsign = x >> 31;
  int Xleak1 = ~Xsign & ~((x + Limit2 + 1) >> 31);
  int Xleak2 = Xsign & ((x + Limit1 + 1) >> 31);
  int Noleak = ~(Xleak1 | Xleak2);
  int Xmul5 = Noleak & ((x << 2) + x);
  int ans = (Xleak1 & MAX) | (Xleak2 & MIN) | Xmul5;
  return ans;
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /*拆成两次和运算，然后求五个值的符号位。将符号位处理得到两次和运算的进位与否，再算三次的加法是否产生溢出
  *有溢出就判断往哪里溢出，输出正负1；无溢出就输出0
  */
  int Add1 = x + y;
  int Add2 = Add1 + z;
  int Xsign = x >> 31;
  int Ysign = y >> 31;
  int Zsign = z >> 31;
  int A1sign = Add1 >> 31;
  int A2sign = Add2 >> 31;
  int Jinwei1 = (Xsign & Ysign) | ((Xsign | Ysign) & ~A1sign);
  int Jinwei2 = (A1sign & Zsign) | ((A1sign | Zsign) & ~A2sign);
  int Jinweians = Xsign + Ysign + Zsign + ~Jinwei1 + ~Jinwei2 + 2 + (A2sign & 1);
  int ans = Jinweians >> 31;
  ans = ans | (!Jinweians ^ 1);
  return ans;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned s = uf >> 31;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;
    unsigned M, E, M3, keep, drop, temp;
    unsigned new_frac, result;
    int p, shift;
    if (exp == 0xFF) return uf;
    if (exp == 0 && frac == 0) return uf;
    if (exp == 0) {
        M = frac;
        E = -126;
    } else {
        M = (1 << 23) | frac;
        E = exp - 127;
    }
    M3 = M * 3;
    p = 0;
    temp = M3;
    while (temp > 1) {
      temp >>= 1;
      p = p + 1;
    }
    if (p <= 23) {
      new_frac = (M3 >> 1) + ((M3 & 1) && ((M3 >> 1) & 1));
      return (s << 31) | new_frac;
    }
    shift = p - 23;
    keep = M3 >> shift;
    drop = M3 & ((1 << shift) - 1);
    if (drop > (1 << (shift - 1)) || (drop == (1 << (shift - 1)) && (keep & 1))) {
      keep = keep + 1;
      if (keep == (1 << 24)) {
        keep = keep >> 1;
        shift = shift + 1;
      }
    }
    E = E + shift - 1 + 127;
    if (E >= 0xFF) {
        return (s << 31) | (0xFF << 23);
    }
    result = (s << 31) | (E << 23) | (keep & 0x7FFFFF);
    return result;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  /*先把输入的uf拆开变成s，exp，frac三个部分，然后判断是否是整数或者infinity，如果是的话，直接原样输出
  *再判断uf是不是纯小数，是的话就判断是否为负数（输出-0）在0.5左侧（输出0）右侧（输出1）
  *然后对于不是纯小数，左移直到它是一个大整数，切掉小数，判断往哪里进位
  *进位溢出就向exp进位，然后frac归位。阶码要是变成0xFF就是无穷大，直接返回
  */
  unsigned s = uf >> 31;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
  if(exp == 0xFF) return uf;
  if(exp >= 150) return uf;
  if (exp < 127) {
    if (exp < 126 || frac == 0) return s << 31;
    else return (s << 31) | (127 << 23);
  }
  unsigned m = (1 << 23) | frac;
  int shift = 150 - exp;
  unsigned ufmask = (1 << shift) - 1;
  unsigned ufdrop = m & ufmask;
  unsigned ufbaoliu = m >> shift; 
  unsigned half = 1 << (shift - 1); 
  int roundUp = 0;
  if (ufdrop > half) roundUp = 1;       
  else if (ufdrop == half) {
    if (ufbaoliu & 1) roundUp = 1;         
  }
  if (roundUp == 1) {
    ufbaoliu = ufbaoliu + 1;
    if (ufbaoliu == (1 << 24)) {  
      ufbaoliu = 1 << 23;  
      exp = exp + 1;
      if (exp == 0xFF) return (s << 31) | (0xFF << 23); 
    }
  }
  int p = 0;
  unsigned temp = ufbaoliu;
  while (temp > 1) {
    temp >>= 1;
    p = p + 1;
  }
  exp = 127 + p;                     
  frac = (ufbaoliu << (23 - p)) & 0x7FFFFF;
  unsigned ans = (s << 31) | (exp << 23);
  ans = ans | frac;
  return ans;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  /*其实和17题差不多，复用了大部分17题的代码*/
  unsigned s = 0, exp = 0, frac = 0;
  int Purex = x;
  int temp = 0, p = 0;
  if (x == 0) return 0;
  if (x == 0x80000000) return 0xCF000000;
  if (x < 0) {
    Purex = -x;
    s = 1;
  }
  temp = Purex;
  while (temp > 1) {
    temp >>= 1;
    p = p + 1;
  }
  exp = 127 + p;
  if(p <= 23) frac = (Purex << (23 - p)) & 0x7FFFFF;
  else{
    int shift = p - 23;
    unsigned baoliu = Purex >> shift;             
    unsigned Xdrop = Purex & ((1 << shift) - 1);
    unsigned half = 1 << (shift - 1); 
    int round_up = 0;
    if (Xdrop > half) round_up = 1;
    else if (Xdrop == half) {
      if (baoliu & 1) round_up = 1;
    }
    if (round_up) {
      baoliu = baoliu + 1;
      if (baoliu == (1 << 24)) { 
        baoliu = baoliu >> 1;
        exp = exp + 1;
      }
    }
    frac = baoliu & 0x7FFFFF; 
  }
  unsigned ans = (s << 31) | (exp << 23);
  ans = ans | frac;
  return ans;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /*先构建五个掩码，见第十九题注释部分。
  *掩码用来保留每组的第0位。x右移1位再和掩码做与运算，两者相加就是这两位里1的总个数。
  *以此类推，得到32位里面1的总个数
  */
  int count;
  int wei4 = 0x0F;
  int wei16 = 0xFF;
  wei16 = wei16 + (wei16 << 8);
  int wei8 = wei16 ^ (wei16 << 8);
  wei4 = wei4 + (wei4 << 8); 
  wei4 = wei4 + (wei4 << 16);
  int wei2 = wei4 ^ (wei4 << 2);
  int wei1 = wei2 ^ (wei2 << 1);
  count = (x & wei1) + ((x >> 1) & wei1);
  count = (count & wei2) + ((count >> 2) & wei2);
  count = (count & wei4) + ((count >> 4) & wei4);
  count = (count & wei8) + ((count >> 8) & wei8);
  count = (count & wei16) + ((count >> 16) & wei16);
  return count;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  /*先构造出五个掩码，分别是wei1=10101010101010101010101010101010;wei2=11001100110011001100110011001100
  *wei4=11110000111100001111000011110000;wei8=111111111000000001111111100000000
  *wei16=11111111111111111111111111111111
  *然后借助掩码运算，先交换x相邻1位，然后相邻2位，然后相邻4位，然后相邻8位，最后相邻16位。得到反序32位二进制
  */
  int wei4 = 0x0F;
  int wei16 = 0xFF;
  wei16 = wei16 + (wei16 << 8);
  int wei8 = wei16 ^ (wei16 << 8);
  wei4 = wei4 + (wei4 << 8); 
  wei4 = wei4 + (wei4 << 16);
  int wei2 = wei4 ^ (wei4 << 2);
  int wei1 = wei2 ^ (wei2 << 1);
  x = ((x >> 1) & wei1) | ((x & wei1) << 1);
  x = ((x >> 2) & wei2) | ((x & wei2) << 2);
  x = ((x >> 4) & wei4) | ((x & wei4) << 4);
  x = ((x >> 8) & wei8) | ((x & wei8) << 8);
  x = ((x >> 16) & wei16) | (x << 16);
  return x;
}
