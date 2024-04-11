/**
Filename: pcolor.c (implementation of pcolor.h)
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 17/10/2019
Modified at: 23/10/2023
**/

#include <string>
using namespace std;
#include "pcolor.hpp"

void print_red(char c)
{
    printf("%s%c", RED, c);
    printf("%s", NORMAL);
}

void print_green(char c)
{
    printf("%s%c", GREEN, c);
    printf("%s", NORMAL);
}

void print_blue(char c)
{
    printf("%s%c", BLUE, c);
    printf("%s", NORMAL);
}

void print_reds(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        print_red(s[i]);
    }
}

void print_greens(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        print_green(s[i]);
    }
}

void print_blues(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        print_blue(s[i]);
    }
}
