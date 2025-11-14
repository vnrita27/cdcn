#include <stdio.h>
#include <conio.h>
void qs();
void q1();
void q2();
void q3();
void q4();
void qs()
{
  char ch;
  scanf("%c", &ch);
  if (ch == '\n')
    printf("Not applicable");
  if (ch == 'a')
    q1();
  else
    q4();
}
void q1()
{
  char ch;
  scanf("%c", &ch);
  if (ch == '\n')
    printf("Not applicable");
  if (ch == 'b')
    q2();
  else
    q4();
}
void q2()
{
  char ch;
  scanf("%c", &ch);
  if (ch == '\n')
    printf("Not applicable");
  if (ch == 'b')
    q3();
  else
    q4();
}
void q3()
{
  char ch;
  scanf("%c", &ch);
  if (ch == '\n')
    printf("Accepted");
  if (ch == 'a' || ch == 'b')
    q3();
}
void q4()
{
  printf("Dead State");
}
void main()
{
  clrscr();
  printf("Enter the string consisting of a's and b's");
  qs();
  getch();
}