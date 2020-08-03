/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlSearchUsers.c,v $
 * Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
 * Initial revision
 *
 *
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<ctype.h>

#include "gmtUmlTypes.h"
#include "gmtUmlConst.h"
#include "gmtUmlErrors.h"
#include "gmtUmlGetUsers.h"
#include "gmtUmlFunctions.h"

/*
 * gmtUmlErrorType
 * GmtUmlSearchUsers (gmtUmlConfigurationOptionsType *, char *, char *, gmtUmlProfileType, gmtUmlUserDataType **);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the struct containing the configuration options (I);
 * char * - name or part of the name (I);
 * char * - email or part of email (I);
 * gmtUmlProfileType - profile (I);
 * gmtUmlUserDataType ** - the user data threaded list (O);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * This function can be used by anyone to search another user's information.
 */

gmtUmlErrorType
GmtUmlSearchUsers (gmtUmlConfigurationOptionsType *configurationOptions, char *usrName, char *usrEmail, gmtUmlUserProfileType usrProfile, gmtUmlUserDataType **usersList)
{
  gmtUmlUserDataType *currentUser, *previousUser;
  gmtUmlErrorType validation;
  boolean seekUser, seekEmail, seekProfile, foundUser, foundEmail, foundProfile;
  unsigned index = 0;
  char nameBuffer [GMT_UML_MAX_NAME_LENGTH+1],
       emailBuffer [GMT_UML_MAX_EMAIL_LENGTH+1];

  if ((configurationOptions == NULL) || (usersList == NULL))
    return gmtUmlErrorNullPointer;

  if ((usrName == NULL) && (usrEmail == NULL) && (usrProfile == 0))
    return gmtUmlErrorNullPointer;

  if ((validation = GmtUmlGetUsers (usersList, configurationOptions)))
    return validation;

  currentUser = *usersList;
  previousUser = NULL;

  if (usrName == NULL)
    seekUser = False;
  else
  {
    if (strlen (usrName) == 0)
      seekUser = False;
    else
    {
      seekUser = True;

      for (index = 0; index < strlen (usrName); index++)
      {
        usrName [index] = toupper (usrName [index]);
      }
    }
  }

  if (usrEmail == NULL)
    seekEmail = False;
  else
  {
    if (strlen (usrEmail) == 0)
      seekEmail = False;
    else
    {
      seekEmail = True;

      for (index = 0; index < strlen (usrEmail); index++)
      {
        usrEmail [index] = toupper (usrEmail [index]);
      }
    }
  }

  if (usrProfile == 0)
    seekProfile = False;
  else
  {
    seekProfile = True;
  }

  #ifdef _DEBUG_
  if (seekUser)
    printf ("Seek user\n");
  if (seekEmail)
    printf ("Seek email\n");
  if (seekProfile)
    printf ("Seek profile\n");
  /*sleep (1000);*/
  #endif

  while (currentUser != NULL)
  {
    foundUser = True;
    foundEmail = True;
    foundProfile = True;

    #ifdef _DEBUG_
    printf ("Iteration...\n");
    #endif

    if ((seekProfile) && (usrProfile != currentUser->profile))
    {
      foundProfile = False;
    }

    if (seekUser)
    {
      for (index = 0; index < (strlen (currentUser->name) + 1); index++)
      {
        nameBuffer [index] = toupper (currentUser->name [index]);
      }

      #ifdef _DEBUG_
      printf ("Name: %s| Searching for: %s<br>", nameBuffer, usrName);
      #endif

      if (!strstr (nameBuffer, usrName))
      {
        foundUser = False;
        #ifdef _DEBUG_
        printf ("NAME FALSE <br>");
        #endif
      }
    }

    if (seekEmail)
    {
      for (index = 0; index < (strlen (currentUser->email) + 1); index++)
      {
        emailBuffer [index] = toupper (currentUser->email [index]);
      }

      #ifdef _DEBUG_
      printf ("Email: %s| Searching for: %s<br>", emailBuffer, usrEmail);
      #endif

      if (!strstr (emailBuffer, usrEmail))
      {
        foundEmail = False;
        #ifdef _DEBUG_
        printf ("EMAIL FALSE <br>");
        #endif
      }
    }

    if ((!foundUser) || (!foundEmail) || (!foundProfile))
    {
      if (previousUser != NULL)
        previousUser->next = currentUser->next;
      else
        *usersList = currentUser->next;

      #ifdef _DEBUG_
      printf ("%s is not what we are looking for...\n", currentUser->name);
      /*sleep (1000);*/
      #endif

      currentUser = currentUser->next;
      continue;
    }

    #ifdef _DEBUG_
    printf ("%s is what we are looking for...\n", currentUser->name);
    /*sleep (1000);*/
    #endif
    previousUser = currentUser;
    currentUser = currentUser->next;
  }

  /*while (currentUser != NULL)
  {
    if ((usrName == NULL) && (usrEmail == NULL))
    {
      if (currentUser->profile != usrProfile)
      {
        if (previousUser != NULL)
        {
          previousUser->next = currentUser->next;
        }
        else
        {
          *usersList = currentUser->next;
        }

        currentUser = currentUser->next;
      }
      else
      {
        previousUser = currentUser;
        currentUser = currentUser->next;
      }
    }

    if ((usrProfile == 0) && (usrEmail == NULL))
    {
      if (!GmtUmlCheckPrefix (usrName, currentUser->name))
      {
        if (previousUser != NULL)
          previousUser->next = currentUser->next;
        else
          *usersList = currentUser->next;

        currentUser = currentUser->next;
      }
      else
      {
        previousUser = currentUser;
        currentUser = currentUser->next;
      }
    }

    if ((usrName == NULL) && (usrProfile == 0))
    {
      if (!GmtUmlCheckPrefix (usrEmail, currentUser->email))
      {
        if (previousUser != NULL)
          previousUser->next = currentUser->next;
        else
          *usersList = currentUser->next;

        currentUser = currentUser->next;
      }
      else
      {
        previousUser = currentUser;
        currentUser = currentUser->next;
      }
    }
  }*/

  return gmtUmlOk;
}


 /* $RCSfile: gmtUmlSearchUsers.c,v $ */
