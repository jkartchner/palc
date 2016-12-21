/* Hex, Dec, Oct, and Bin Calculator 02-13-2013 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void fromdec(int value, char *out, int base);
int todec(char *value);
int all2dec(char *value, int base);
char decdigit2hexdigit(int value);
int hexdigit2decdigit(char value);
int power(int base, unsigned int power);



int main( int argc, char *argv[] )
{
  enum Output { dec, hex, bin, oct };
  enum Output output;

  enum Operation { mult, div, add, sub, mod };
  enum Operation operator[3];
  int opcounter = 0;
  int values[4];
  int valcounter = 0;

  if(argc < 2)
  {
    printf("\nThis program requires at least two arguments to function.\nType 'palc --help' for more info.\n\n");
    return 0;
  }  int n;


    if(!strcmp(argv[1], "-h"))
        output = hex;
    else if(!strcmp(argv[1], "-d"))
        output = dec;
    else if(!strcmp(argv[1], "-o"))
        output = oct;
    else if(!strcmp(argv[1], "-b"))
        output = bin;
    else if(!strcmp(argv[1], "--help"))
    {
        printf("\n|----------------------Hex Calc------------------------|\n\nPalc is a hex calculator and converter. It converts decimal, binary, hex, and octal in addition to standard mathematical calculations. \n\n");
        printf("**Note - Palc does not execute in the mathematical order of operations\n\n");
        printf("Palc usage: palc [output format] [value 1] [operator] [value 2] ...\n\n");
        printf("Output Format: -d (Decimal) -b (Binary) -h (Hexadecimal) -o (Octal)\nValue: 0x000 (Hexadecimal) 0b0000 (Binary) 0o0000 (Octal) 0000 (Decimal)\nOperator: *(x) / + - %%\n\nImportant: You must escape the * (multiplication symbol) by writing /*. Alternatively, you can write x for multiplication.\n\nExample:      palc -h 12002 x 0x12d1\n\n|----------------------Hex Calc-------------------------|\n\n");
        return 0;
    }
    else
    {
        printf("\nInvalid syntax. Type 'palc --help' for more info.\n\n");
        return 0;
    }

  for(n = 2; n < argc; n++)
  {
    if(!strcmp(argv[n], "*") || !strcmp(argv[n], "x"))
    {
        operator[opcounter] = mult;
        opcounter++;
    }
    else if(!strcmp(argv[n], "/"))
    {
        operator[opcounter] = div;
        opcounter++;
    }
    else if(!strcmp(argv[n], "+"))
    {
        operator[opcounter] = add;
        opcounter++;
    }
    else if(!strcmp(argv[n], "-"))
    {
        operator[opcounter] = sub;
        opcounter++;
    }
    else if(!strcmp(argv[n], "%"))
    {
        operator[opcounter] = mod;
        opcounter++;
    }
    else
    {
        values[valcounter] = todec(argv[n]);   // convert the argument from whatever to decimal integer
        valcounter++;
    }
  }
  
 
  int result = values[0];
  int k;
  for(k = 0; k < opcounter; k++)
  {
    switch(operator[k])
    {
      case add:
        result += values[k + 1];    // the indices of the value array will always be k and k + 1
        break;
      case sub:
        result -= values[k + 1];
        break;
      case mult:
        result *= values[k + 1];
        break;
      case div:
        result /= values[k + 1];
        break;
      case mod:
        result %= values[k + 1];
        break;
    }
  }
  
  // finally output the value, after proper conversion
  char *out = malloc( sizeof(char) * 256);
  switch(output)
  {
    case dec:
      printf("\n  =     %d\n\n", result);
      break;
    case hex:
      fromdec(result, out, 16);
      printf("\n  =     %s\n\n", out);
      break;
    case oct:
      fromdec(result, out, 8);
      printf("\n  =     %s\n\n", out);
      break;
    case bin:
      fromdec(result, out, 2);
      printf("\n  =     %s\n\n", out);
      break;
  }

  free( out );
  return 0;
}

void fromdec(int value, char *out, int base)
{
  int decplace = 0;
  int revdecplace = 0;
  int found = 0;
  while( value > 0 || decplace >= 0)   // work as long as either condition is present
  {
    if(value >= 1 * power(base, (unsigned int)decplace) && value <= (base * power(base, (unsigned int)decplace)) - 1)
    {
      int placevalue = value / power(base, decplace);   // no matter what, placevalue < base
      out[revdecplace] = decdigit2hexdigit(placevalue);

      value = value % power(base, decplace);            // set value lower for the next dec place

      revdecplace++;
      decplace--;
      found = 1;
    }
    else if(!found)
      decplace++;
    else
    {
      out[revdecplace] = '0';
      revdecplace++;
      decplace--;
    }
  }

  return;
}


int todec(char *value)
{
  if(value[1] != 'b' && value[1] != 'x' && value[1] != 'o')
    return atoi(value);
  
  switch(value[1])
  {
    case 'b':
      return all2dec(value, 2); 
    case 'x':
      return all2dec(value, 16);
    case 'o':
      return all2dec(value, 8);
  } 
}

int all2dec(char *value, int base)
{
  int decimal = 0;
  unsigned int pow = 0;
  int level = 0;   // an integer to hold the real value of any (hex) number or letter
  
  int length;
  for(length = strlen( value ) - 1; length > 1; length--)
  {
    //level = (int)value[length] - '0';      // C standard compliant; takes ascii char value and puts to real int
    level = hexdigit2decdigit(value[length]);
    decimal += level * power(base, pow);   // 
    pow++;

  }
  return decimal;
}

char decdigit2hexdigit(int value)
{
  switch(value)
  {
    case 0:
      return '0';
    case 1:
      return '1';
    case 2:
      return '2';
    case 3:
      return '3';
    case 4:
      return '4';
    case 5:
      return '5';
    case 6:
      return '6';
    case 7:
      return '7';
    case 8:
      return '8';
    case 9:
      return '9';
    case 10:
      return 'A';
    case 11:
      return 'B';
    case 12:
      return 'C';
    case 13:
      return 'D';
    case 14:
      return 'E';
    case 15:
      return 'F';
  }
}

int hexdigit2decdigit(char value)
{
  switch(value)
  {
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    case 'a':
      return 10;
    case 'A':
      return 10;
    case 'b':
      return 11;
    case 'B':
      return 11;
    case 'c':
      return 12;
    case 'C':
      return 12;
    case 'd':
      return 13;
    case 'D':
      return 13;
    case 'e':
      return 14;
    case 'E':
      return 14;
    case 'f':
      return 15;
    case 'F':
      return 15;
  }
}

int power(int base, unsigned int exp)
{
  int i, result = 1;
  for(i = 0; i < exp; i++)
    result *= base;
  return result;
}
