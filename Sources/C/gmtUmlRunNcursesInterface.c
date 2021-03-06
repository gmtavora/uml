/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlRunNcursesInterface.c,v $
 * Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
 * Initial revision
 *
 *
 */
 
 #include <ncurses.h>
 
 #include "gmtUmlTypes.h"
 #include "gmtUmlErrors.h"
 
 /*
  * gmtUmlErrorType
  * GmtUmlRunNcursesInterface (gmtUmlConfigurationOptionsType *, char *, gmtUmlLanguageType)
  *
  * Arguments:
  * gmtUmlConfigurationOptionsType * - the current configuration options (I);
  * char * - the user nickname (I);
  * gmtUmlLanguageType - the current language;
  *
  * Returned code:
  * gmtUmlOk - success;
  * 
  */
 
 WINDOW *gmtUmlNcursesCreateNewWindow (int gmtUmlNumberOfLines, int gmtUmlNumberOfCols, int gmtUmlInitialY, int gmtUmlInitialX)
 {
   WINDOW *gmtUmlWindow;
   
   gmtUmlWindow = newwin (gmtUmlNumberOfLines, gmtUmlNumberOfCols, gmtUmlInitialY, gmtUmlInitialX);
   
   box (gmtUmlWindow, 0, 0);
   
   wrefresh (gmtUmlWindow);
   
   return gmtUmlWindow;
 }
 
 void gmtUmlNcursesDestroyWindow (WINDOW *gmtUmlWindow)
 {
   wborder (gmtUmlWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
   wrefresh (gmtUmlWindow);
   delwin (gmtUmlWindow);
 }
 
 gmtUmlErrorType
 GmtUmlRunNcursesInterface (gmtUmlConfigurationOptionsType *configurationOptions, char * userNickname, gmtUmlLanguageType language)
 {
   WINDOW *my_win;
   int gmtUmlInitialX, gmtUmlInitialY, gmtUmlWidth, gmtUmlHeight;
   int ch;
   
   initscr ();
   cbreak ();
   keypad (stdscr, TRUE);
   
   gmtUmlHeight = LINES;
   gmtUmlWidth = COLS;
   gmtUmlInitialX = (COLS - gmtUmlWidth) / 2;
   gmtUmlInitialY = (LINES - gmtUmlHeight) / 2;
   
   switch (language)
   {
     default:
     case gmtUmlEnglish:
     printw ("Press F1 to exit.");
     break;
     
     case gmtUmlPortuguese:
     printw ("Pressione F1 para sair.");
     break;
   }
   
   refresh ();
   my_win = gmtUmlNcursesCreateNewWindow (gmtUmlHeight, gmtUmlWidth, gmtUmlInitialY, gmtUmlInitialX);
   
   while ((ch = getch ()) != KEY_HOME) {}
   
   endwin ();
   return gmtUmlOk;
 }
 
 /* $RCSfile: gmtUmlRunNcursesInterface.c,v $ */