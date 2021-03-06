/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlChangeUserPassword.c,v $
 * Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include <stdio.h>
#define XOPEN_SOURCE 600
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "gmtUmlTypes.h"
#include "gmtUmlConst.h"
#include "gmtUmlErrors.h"
#include "gmtUmlConfig.h"
#include "gmtUmlFunctions.h"
#include "gmtUmlChangeUserPassword.h"
#include "gmtUmlGetUsers.h"
#include "./Libraries/sendmail.h"

#define TEMP_PASSWORD_LENGTH  16
#define MAX_EMAIL_SUBJECT_LENGTH 512
#define MAX_EMAIL_BODY_LENGTH 1024*5

/*
 * gmtUmlErrorType
 * GmtUmlChangeUserPassword (gmtUmlConfigurationOptionsType *, char *, char*, char *, char *, char *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the struct containing the configuration options (I);
 * char * - administrator's nickname (I);
 * char * - user's nickname (I);
 * char * - current password (I);
 * char * - new password (I);
 * char * - new password confirmation (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Changes user's password. An administrator can change any user's password. When used by admin, his nickname needs to be
 * informed, otherwise the argument can be NULL.
 */

gmtUmlErrorType 
GmtUmlChangeUserPassword (gmtUmlConfigurationOptionsType *configurationOptions, char *admNickname, char *usrNickname, char *currentPassword, char *newPassword, char *newPasswordConfirmation)
{
  gmtUmlErrorType gmtUmlValidation;
  gmtUmlUserDataType *usersList = NULL, *currentUser, *user, *admin;
  boolean isAdmin;
  boolean foundUser = False, foundAdmin = False;
  char newEncryptedPassword [GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1];

  if (usrNickname == NULL)
    return gmtUmlErrorNullPointer;

  if ((admNickname == NULL) && (currentPassword == NULL))
    return gmtUmlErrorNullPointer;

  if ((usrNickname == NULL) || (newPasswordConfirmation == NULL))
    return gmtUmlErrorNullPointer;

  if (admNickname == NULL)
    isAdmin = False;
  else
  {
    if (strlen (admNickname) == 0)
      isAdmin = False;
    else
      isAdmin = True;
  }

  #ifdef _DEBUG_
  printf ("Arguments:\n");
  if (usrNickname)
    printf ("User nickname: %s\n", usrNickname);
  #endif

  GmtUmlGetUsers (&usersList, configurationOptions);

  #ifdef _DEBUG_
  printf ("User data list loaded...\n");
  #endif

  currentUser = usersList;

  while (currentUser != NULL)
  {
    #ifdef _DEBUG_
    printf ("Iteration...\n");
    printf ("Nickname: %s.\n", currentUser->nickname);
    #endif

    if (!strcmp (currentUser->nickname, usrNickname))
    {
      foundUser = True;
      user = currentUser;

      if (foundAdmin)
        break;
    }

    if (isAdmin)
    {
      if (!strcmp (currentUser->nickname, admNickname))
      {
        if (currentUser->profile != 2)
        {
          GmtUmlDestroyUserDataList (usersList);
          return gmtUmlErrorPermissionDenied;
        }
      
        foundAdmin = True;
        admin = currentUser;
      
        if (foundUser)
          break;
      }
    }

    currentUser = currentUser->next;
  }

  if (!foundUser)
  {
    #ifdef _DEBUG_
    printf ("User not found...\n");
    #endif

    GmtUmlDestroyUserDataList (usersList);
    return gmtUmlErrorUserNotFound;
  }

  if (isAdmin)
  {
    if (!foundAdmin)
    {
      #ifdef _DEBUG_
      printf ("Admin not found...\n");
      #endif
      GmtUmlDestroyUserDataList (usersList);
      return gmtUmlErrorUserNotFound;
    }
    
    if (admin->profile > 2)
    {
      #ifdef _DEBUG_
      printf ("Not an admin...\n");
      #endif
      GmtUmlDestroyUserDataList (usersList);
      return gmtUmlErrorPermissionDenied;
    }
  }

  /* Changes the password */

  if (strcmp (newPassword, newPasswordConfirmation))
  {
    GmtUmlDestroyUserDataList (usersList);
    return gmtUmlErrorPasswordsDontMatch;
  }

  GmtUmlEncodePasswordWithSpecificAlgorithm (newPassword, configurationOptions->gmtUmlCryptAlgorithm, newEncryptedPassword);

  if (isAdmin)
  {
    /* The admin is changing someone else's password */
    strcpy (user->password, newEncryptedPassword);
  }
  else
  {
    /* The user is changing his own password */
    if (strcmp (currentPassword, user->password))
    {
      GmtUmlDestroyUserDataList (usersList);
      return gmtUmlIncorrectPassword;
    }

    strcpy (user->password, newEncryptedPassword);
  }

  /* Rewrite users file */
  if ((gmtUmlValidation = GmtUmlWriteUsersFile (usersList, configurationOptions)))
  {
    GmtUmlDestroyUserDataList (usersList);
    return gmtUmlValidation;
  }

  return gmtUmlOk;
}

 /* $RCSfile: gmtUmlChangeUserPassword.c,v $ */