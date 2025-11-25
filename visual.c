#include "visual.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void menu(void) {
  system("cls");
  int choice;
  printf("Welcome to the Candy Game !\n");
  printf("1. Rules\n");
  printf("2. New Game\n");  
  printf("3. Load Game\n");
  printf("4. Exit\n");
  scanf("%d",choice);  
  if (choice == 1) {
      rules();
  } else if (choice == 2) {
      NewGame();
  } else if (choice == 3) {
      Chargegame();
  } else {
      leave();
  }
}

