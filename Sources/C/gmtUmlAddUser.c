/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlAddUser.c,v $
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
#include "./Libraries/sendmail.h"
#include "gmtUmlAddUser.h"

#define TEMP_PASSWORD_LENGTH  16
#define MAX_EMAIL_SUBJECT_LENGTH 512
#define MAX_EMAIL_BODY_LENGTH 1024*5

gmtUmlErrorType
GmtUmlAddUser (gmtUmlConfigurationOptionsType *gmtUmlConfiguration, gmtUmlUserDataType *gmtUmlUserData)
{
  FILE *gmtUmlUsersReadFile, *gmtUmlUsersWriteFile;
  gmtUmlErrorType gmtUmlValidation;
  char *token, *validation;
  int gmtUmlTempFile;
  gmtUmlUserDataType *readingFirst, *readingPrevious, *new, *current;
  gmtUmlUserIdentifierType targetId = 0, index = 0;
  boolean found = False;
  char gmtUmlBackupName [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       readFilePath [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       writeFilePath [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1];

  char buffer [GMT_UML_USERS_FILE_LINE_LENGTH+1];
  
  char tempPassword [TEMP_PASSWORD_LENGTH+1];
  char tempEncryptedPassword [GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1];

  char clientDomain [GMT_UML_MAX_EMAIL_LENGTH];
  char smtpServer [GMT_UML_MAX_EMAIL_LENGTH] = "smtp.del.ufrj.br";
  char messageSubject [MAX_EMAIL_SUBJECT_LENGTH+1];
  char messageBody [MAX_EMAIL_BODY_LENGTH+1];

  unsigned long long expirationDate;
  
  if (gmtUmlUserData == NULL)
  	return gmtUmlErrorInvalidUserData;

  if (gmtUmlConfiguration == NULL)
  {
  	gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (GMT_UML_DEFAULT_CONFIG_FILE, gmtUmlConfiguration);
  	if (gmtUmlValidation)
  		return gmtUmlValidation;
  }

  if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (gmtUmlConfiguration->gmtUmlDataDirectory, gmtUmlConfiguration->gmtUmlUsersDataFilename, readFilePath)))
      return gmtUmlValidation;

  if ((gmtUmlUsersReadFile = fopen (readFilePath, "r")))
  {
    #ifdef _DEBUG_
  	printf ("Users file exists.\n");
    #endif 
    
    if (gmtUmlUserData->profile == 1) /* profile 1 is the permanent admin */
  	  return gmtUmlErrorUsersFileExists;
  }
  else
  {
    #ifdef _DEBUG_
  	printf ("Writing new users file.\n");
    #endif 
    
    if (gmtUmlUserData->profile != 1)
      return gmtUmlErrorInvalidProfile;
    
    gmtUmlUsersWriteFile = fopen (readFilePath, "w");
    fprintf (gmtUmlUsersWriteFile, "0:%s:%s:%llu:%s:%s", gmtUmlUserData->nickname, gmtUmlUserData->password, gmtUmlUserData->profile, gmtUmlUserData->name, gmtUmlUserData->email);
    fclose (gmtUmlUsersWriteFile);
    return gmtUmlOk;
  }

  /* Creates a temp file to rewrite data */
  if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (gmtUmlConfiguration->gmtUmlDataDirectory, "gmtUmlUserDataFile.XXXXXX", writeFilePath)))
    return gmtUmlValidation;

  gmtUmlTempFile = mkstemp (writeFilePath);

  if (gmtUmlTempFile == -1)
  	return gmtUmlErrorCreatingTempFile;

  if (!(gmtUmlUsersWriteFile = fdopen (gmtUmlTempFile, "w")))
  	return gmtUmlErrorCreatingTempFile;

  /* Begin to read */
  readingFirst = NULL;
  readingPrevious = NULL;

  new = readingFirst;

  #ifdef _DEBUG_
  printf ("\nBuffer:\n");
  #endif

  while (fgets (buffer, GMT_UML_USERS_FILE_LINE_LENGTH+1, gmtUmlUsersReadFile))
  {
  	if (!(new = (gmtUmlUserDataType *) malloc (sizeof (gmtUmlUserDataType))))
  	{
      #ifdef _DEBUG_
  	  printf ("Could not allocate memory.\n");
      #endif
       
  	  fclose (gmtUmlUsersReadFile);
  	  fclose (gmtUmlUsersWriteFile);
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

    if (strcmp (new->nickname, gmtUmlUserData->nickname) == 0)
    {
      GmtUmlDestroyUserDataList (readingFirst);
      free (new);
      return gmtUmlErrorNicknameAlreadyExists;
    }

    if (strcmp (new->email, gmtUmlUserData->email) == 0)
    {
      GmtUmlDestroyUserDataList (readingFirst);
      free (new);
      return gmtUmlErrorEmailAlreadyExists;
    }

    new->next = NULL;

    if (readingFirst == NULL)
    {
      #ifdef _DEBUG_
  	  printf ("Finished reading first element...\n");
      #endif
      
    	readingFirst = new;
    }

    if (readingPrevious != NULL) /* if 'new' is not the first element */
    {
      #ifdef _DEBUG_
  	  printf ("Finished reading other element...\n");
      #endif
      
    	readingPrevious->next = new;
    }
    
    if (readingPrevious)
      if (new->id != (readingPrevious->id + 1)) /* targetId indicates where the new element will be writen */
      {
      	  #ifdef _DEBUG_
      	  printf ("Found!\n");
      	  #endif

          targetId = readingPrevious->id+1;
          found = True;
      }

    if (!found)
      targetId++;

    readingPrevious = new;
  } /* while */

  gmtUmlUserData->id = targetId;

  /* Places the new user in the right position */
  current = readingFirst;

  while (index < targetId)
  {
    readingPrevious = current;
    current = current->next;
    index++;
  }

  readingPrevious->next = gmtUmlUserData;
  gmtUmlUserData->next = current;

  /* Begin to write the new file */
  current = readingFirst;

  while (current->next != NULL)
  {
    #ifdef _DEBUG_
  	printf ("%llu:%s:%s:%llu:%s:%s\n", current->id, current->nickname, current->password, current->profile, current->name, current->email);
    #endif
     
    fprintf (gmtUmlUsersWriteFile, "%llu:%s:%s:%llu:%s:%s\n", current->id, current->nickname, current->password, current->profile, current->name, current->email);

  	current = current->next;
  }
  
  #ifdef _DEBUG_
  printf ("%llu:%s:%s:%llu:%s:%s\n", current->id, current->nickname, current->password, current->profile, current->name, current->email);
  #endif
  fprintf (gmtUmlUsersWriteFile, "%llu:%s:%s:%llu:%s:%s", current->id, current->nickname, current->password, current->profile, current->name, current->email);

  /* Renames the files, creating a backup*/
  #ifdef _DEBUG_
 	printf ("Renaming the file.\n");
  #endif
   
  fclose (gmtUmlUsersWriteFile);
  fclose (gmtUmlUsersReadFile);

  snprintf (gmtUmlBackupName, GMT_UML_MAX_FILE_NAME_LENGTH+1, "%s.backup", gmtUmlConfiguration->gmtUmlUsersDataFilename);
  rename (readFilePath, gmtUmlBackupName);
  rename (writeFilePath, readFilePath);

  /* If the length of the password's string is zero, includes the user in the invited.users file and sends an email to him */
  #ifdef _DEBUG_
  printf ("Including user in invited.users file.\n");
  #endif
  
  if (strlen (gmtUmlUserData->password) == 0)
  {
    if ((gmtUmlUsersReadFile = fopen (GMT_UML_INVITED_USERS_DATA_FILENAME, "r")))
    {
      fclose (gmtUmlUsersReadFile);
      gmtUmlUsersWriteFile = fopen (GMT_UML_INVITED_USERS_DATA_FILENAME, "a");
    }
    else
    {
      gmtUmlUsersWriteFile = fopen (GMT_UML_INVITED_USERS_DATA_FILENAME, "w");
    }
  
    #ifdef _DEBUG_
    printf ("Generating random password.\n");
    #endif
    
    GmtUmlCreateRandomString (GMT_UML_PASSWORD_VALID_CHARS, 16, tempPassword);
    GmtUmlEncodePasswordWithSpecificAlgorithm (tempPassword, GMT_UML_DEFAULT_ENCODING_ALGORITHM, tempEncryptedPassword);

    expirationDate = (time (NULL) + 72*60*60);
  
    #ifdef _DEBUG_
    printf ("Expiration date: %llu.\n", expirationDate);
    #endif

    fprintf (gmtUmlUsersWriteFile, "%llu:%s:%llu\n", gmtUmlUserData->id, tempEncryptedPassword, expirationDate);
    
    fclose (gmtUmlUsersWriteFile);

    /* Sending email */
    #ifdef _DEBUG_
    printf ("Ready to send email.\n");
    #endif
    token = GmtUmlSliceString (gmtUmlUserData->email, "@");
    token = GmtUmlSliceString (NULL, "@");

    strcpy (clientDomain, token);
    /* strcat (smtpServer, clientDomain); */
  
    #ifdef _DEBUG_
    printf ("Domain: %s || SMTP Server: %s.\n", clientDomain, smtpServer);
    printf ("Preparing email\'s subject...\n");
    #endif
  
    snprintf (messageSubject, MAX_EMAIL_SUBJECT_LENGTH+1, "%s", gmtUmlConfiguration->gmtUmlProjectName);
  
    #ifdef _DEBUG_
    printf ("Preparing email\'s body.\n");
    #endif

    snprintf (messageBody, MAX_EMAIL_BODY_LENGTH+1,"Hello,\nYou have been invited to our system. If you want to join us, click in the following link.\nYour temp password is %s and it\'s valid for 72 hours.\n\nOla,\nVoce foi convidado para o nosso sistema. Se voce deseja juntar-se a nos, clique no link abaixo.\nSua senha temporaria e %s e e valida por 72 horas.\n\nHallo,\nSie wurden zu unserem System eingeladen. Wenn Sie sich uns anschliessen m�chten, klicken Sie auf den folgenden Link.\nIhr Tempor�res Passwort ist %s und es ist 72 Stunden lang g�ltig.\n\nhttp://www02.del.ufrj.br/~gabriel.tavora/CGIs/gmtUmlAcceptInvite.cgi?user=%s", tempPassword, tempPassword, tempPassword, gmtUmlUserData->nickname);

    #ifdef _DEBUG_
    printf ("Sending email...\n");
    #endif

    if (sendMail (clientDomain, smtpServer, 25, GMT_UML_ADMIN_EMAIL, gmtUmlUserData->email, "", "", messageSubject, messageBody, ""))
      return gmtUmlErrorSendingEmail;
    
    #ifdef _DEBUG_
    printf ("Done.\n");
    #endif
  }

  GmtUmlDestroyUserDataList (readingFirst);

  return gmtUmlOk;
}
 
 /* $RCSfile: gmtUmlAddUser.c,v $ */