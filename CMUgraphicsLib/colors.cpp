/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include "colors.h"

bool operator==(color a, color b) {

  return ((a.ucRed == b.ucRed) && (a.ucGreen == b.ucGreen) && (a.ucBlue == b.ucBlue));

}

bool operator!=(color a, color b) {

  return !(a == b);
  
}
