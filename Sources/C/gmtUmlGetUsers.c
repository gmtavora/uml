/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlGetUsers.c,v $
 * Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "gmtUmlTypes.h"
#include "gmtUmlConst.h"
#include "gmtUmlErrors.h"
#include "gmtUmlFunctions.h"

/*
 * gmtUmlErrorType
 * GmtUmlGetUsers (gmtUmlUserDataType *, gmtUmlConfigurationOptionsType *);
 *
 * Arguments:
 * gmtUmlUserDataType * - the first element of an threaded list (O);
 * gmtUmlConfigurationOptionsType * - the struct containing the options (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - one of the arguments is a null pointer;
 * gmtUmlErrorOpeningFile - could not open user's data file;
 * gmtUmlErrorAllocatingMemory - could not allocate memory;
 * gmtUmlErrorCorruptedUserFile - user's data file is corrupted;
 *
 * Description:
 * Reads the user file, creating an threaded list.
 */

gmtUmlErrorType
GmtUmlGetUsers (gmtUmlUserDataType **list, gmtUmlConfigurationOptionsType *configurationOptions)
{
  FILE *gmtUmlUsersFile;
  gmtUmlErrorType gmtUmlValidation;
  char *token, *validation;
  gmtUmlUserDataType *readingFirst, *readingPrevious, *new;
  char fileDirectory [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1];

  char buffer [GMT_UML_USERS_FILE_LINE_LENGTH+1];

  if (configurationOptions == NULL)
  {
    gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (GMT_UML_DEFAULT_CONFIG_FILE, configurationOptions);
    if (gmtUmlValidation)
      return gmtUmlValidation;
  }

  if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (configurationOptions->gmtUmlDataDirectory, configurationOptions->gmtUmlUsersDataFilename, fileDirectory)))
    return gmtUmlValidation;

  if (!(gmtUmlUsersFile = fopen (fileDirectory, "r")))
    return gmtUmlErrorOpeningFile;

  /* Begin to read */
  readingFirst = NULL;
  readingPrevious = NULL;

  #ifdef _DEBUG_
  printf ("\nBuffer:\n");
  #endif

  while (fgets (buffer, GMT_UML_USERS_FILE_LINE_LENGTH+1, gmtUmlUsersFile))
  {
    if (!(new = (gmtUmlUserDataType *) malloc (sizeof (gmtUmlUserDataType))))
    {
      #ifdef _DEBUG_
      printf ("Could not allocate memory.\n");
      #endif
       
      fclose (gmtUmlUsersFile);
      return gmtUmlErrorAllocatingMemory;
    }

    /* Slicing the string */

    /* uid */
    token = GmtUmlSliceString (buffer, ":");
    
    if (token == NULL)
    {
      free (new);
      GmtUmlDestroyUserDataList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }
    
    new->id = strtoull (token, &validation, 10);

    if (*validation != '\0')
    {
      free (new);
      GmtUmlDestroyUserDataList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    /* nickname */
    token = GmtUmlSliceString (NULL, ":");
    
    if (token == NULL)
    {
      free (new);
      GmtUmlDestroyUserDataList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    strcpy (new->nickname, token);

    /* password */
    token = GmtUmlSliceString (NULL, ":");
    
    if (*token)
      strcpy (new->password, token);
    else
      memset (new->password, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);

    /* profile */
    token = GmtUmlSliceString (NULL, ":");

    if (token == NULL)
    {
      free (new);
      GmtUmlDestroyUserDataList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    new->profile = strtoull (token, &validation, 10);

    if (*validation != '\0')
    {
      free (new);
      GmtUmlDestroyUserDataList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    /* name */
    token = GmtUmlSliceString (NULL, ":");
    
    if (token == NULL)
    {
      free (new);
      GmtUmlDestroyUserDataList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    strcpy (new->name, token);

    /* email */
    token = GmtUmlSliceString (NULL, ":");

    if (token == NULL)
    {
      free (new);
      GmtUmlDestroyUserDataList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    if (token [strlen (token) - 1] == '\n')
      token [strlen (token) - 1] = '\0';

    strcpy (new->email, token);

    #ifdef _DEBUG_
    printf ("Id: %llu.\n", new->id);
    printf ("Name: %s.\n", new->name);
    printf ("Nickname: %s.\n", new->nickname);
    printf ("Email: %s.\n", new->email);
    printf ("Profile: %llu.\n", new->profile);
    printf ("-----\n");
    #endif

    new->next = NULL;

    if (readingFirst == NULL)
    {
      #ifdef _DEBUG_
      printf ("Finished reading first element...\n");
      #endif
      
      readingFirst = new;
      new->previous = NULL;
    }

    if (readingPrevious != NULL) /* if 'new' is not the first element */
    {
      #ifdef _DEBUG_
      printf ("Finished reading other element...\n");
      #endif
      
      readingPrevious->next = new;
      new->previous = readingPrevious;
    }
    readingPrevious = new;
  } /* while */

  *list = readingFirst;

  return gmtUmlOk;
}

 /* $RCSfile: gmtUmlGetUsers.c,v $ */