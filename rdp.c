// (a) E -> E + T | T, T -> T * F | F, F -> id
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char input[100];
int i = 0;
void E(), Eprime(), T(), Tprime(), F();
void error()
{
  printf("Syntax Error near position %d ('%c')\n", i, input[i]);
  exit(0);
}
void match(char c)
{
  if (input[i] == c)
    i++;
  else
    error();
}
void E()
{
  T();
  Eprime();
}
void Eprime()
{
  if (input[i] == '+')
  {
    match('+');
    T();
    Eprime();
  }
}
void T()
{
  F();
  Tprime();
}
void Tprime()
{
  if (input[i] == '*')
  {
    match('*');
    F();
    Tprime();
  }
}
void F()
{
  if (input[i] == 'i' && input[i + 1] == 'd')
    i += 2;
  else
    error();
}
int main()
{
  printf("Enter input string (use 'id' for identifiers, end with $): ");
  scanf("%s", input);
  E();
  if (input[i] == '$')
    printf("Valid syntax\n");
  else
    printf("Invalid syntax\n");
  return 0;
}