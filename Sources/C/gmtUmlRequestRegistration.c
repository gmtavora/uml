/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlRequestRegistration.c,v $
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

#include "gmtUmlTypes.h"
#include "gmtUmlConst.h"
#include "gmtUmlErrors.h"
#include "gmtUmlConfig.h"
#include "gmtUmlFunctions.h"
#include "gmtUmlRequestRegistration.h"
#include "gmtUmlGetUsers.h"
#include "./Libraries/sendmail.h"

#define MAX_EMAIL_SUBJECT_LENGTH 512
#define MAX_EMAIL_BODY_LENGTH 1024*5

/*
 * gmtUmlErrorType
 * GmtUmlRequestRegistration(gmtUmlConfigurationOptionsType *, char *, gmtUmlUserDataType *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - pointer to the struct containing the configuration options (I);
 * char * - email of the user responsible for the verification (I);
 * gmtUmlUserDataType * - pointer to the struct containing the new user's information (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Requests a new registration.
 */

gmtUmlErrorType 
GmtUmlRequestRegistration (gmtUmlConfigurationOptionsType *configurationOptions, char *checkerEmail, gmtUmlUserDataType *newUser)
{
  FILE *requestsFile;
  gmtUmlRequestType *requestsList, *currentRequest, *newRequest;
  gmtUmlUserDataType *usersList, *currentUser, *checkerData = NULL;
  gmtUmlErrorType gmtUmlValidation;
  unsigned long long expirationDate;
  char *token;

  char clientDomain [GMT_UML_MAX_EMAIL_LENGTH];
  char smtpServer [GMT_UML_MAX_EMAIL_LENGTH] = "smtp.del.ufrj.br";
  char messageSubject [MAX_EMAIL_SUBJECT_LENGTH+1];
  char messageBody [MAX_EMAIL_BODY_LENGTH+1];

  if ((checkerEmail == NULL) || (newUser == NULL) || (configurationOptions == NULL))
    return gmtUmlErrorNullPointer;

  if ((gmtUmlValidation = GmtUmlValidateUserInformation (newUser)))
    return gmtUmlValidation;

  if ((gmtUmlValidation = GmtUmlGetRequestList (&requestsList, configurationOptions)))
    return gmtUmlValidation;

  if ((gmtUmlValidation = GmtUmlGetUsers (&usersList, configurationOptions)))
    return gmtUmlValidation;

  #ifdef _DEBUG_
  printf ("Ready to request.\n");
  #endif

  currentUser = usersList;

  if (currentUser == NULL)
    return gmtUmlErrorSystemNotConfigured;

  if (!(newRequest = (gmtUmlRequestType *) malloc (sizeof (gmtUmlRequestType))))
  {
    if (requestsList != NULL)
      GmtUmlDestroyRequestList (requestsList);
    GmtUmlDestroyUserDataList (usersList);
    return gmtUmlErrorAllocatingMemory;
  }

  #ifdef _DEBUG_
  printf ("Adding new request to list.\n");
  #endif

  newRequest->next = NULL;

  currentRequest = requestsList;

  while (currentRequest != NULL)
  {
    currentRequest = currentRequest->next;

    if (currentRequest->next == NULL)
    {
      currentRequest->next = newRequest;
      break;
    }

    currentRequest = currentRequest->next;
  }

  #ifdef _DEBUG_
  printf ("Adding new user to list.\n");
  #endif

  if (requestsList == NULL)
    requestsList = newRequest;

  newUser->id = 0;

  while (currentUser != NULL)
  {
    if (strcmp (checkerEmail, currentUser->email))
    {
      checkerData = currentUser;
    }

    if (currentUser->previous != NULL)
    {
      if (currentUser->previous->id != (currentUser->id - 1))
      {
        newUser->previous = (currentUser->previous);
        currentUser->previous->next = newUser;
        newUser->next = currentUser;
        newUser->id = (currentUser->id - 1);
      }
    }

    if ((currentUser->next == NULL) && (newUser->id == 0))
    {
      newUser->id = (currentUser->id + 1);
      currentUser->next = newUser;
      break;
    }

    currentUser = currentUser->next;
  }

  if (checkerData == NULL)
  {
    if (requestsList != NULL)
      GmtUmlDestroyRequestList (requestsList);
    GmtUmlDestroyUserDataList (usersList);
    return gmtUmlErrorUserNotFound;
  }

  #ifdef _DEBUG_
  printf ("Friend found.\n");
  #endif

  expirationDate = (time (NULL) + 7*24*60*60);

  newRequest->checkerId = checkerData->id;
  newRequest->newUserId = newUser->id;
  newRequest->expirationDate = expirationDate;
  strcpy (newRequest->password, newUser->password);

  #ifdef _DEBUG_
  printf ("Writing requests file.\n");
  #endif

  requestsFile = fopen (configurationOptions->gmtUmlRequestingUsersDataFilename, "w");

  if (!requestsFile)
  {
    if (requestsList != NULL)
      GmtUmlDestroyRequestList (requestsList);
    GmtUmlDestroyUserDataList (usersList);
    return gmtUmlErrorOpeningFile;
  }

  currentRequest = requestsList;

  while (currentRequest != NULL)
  {
    #ifdef _DEBUG_
    printf ("%llu:%llu:%llu:%s\n", currentRequest->expirationDate, currentRequest->checkerId, currentRequest->newUserId, currentRequest->password);
    #endif
     
    fprintf (requestsFile, "%llu:%llu:%llu:%s\n", currentRequest->expirationDate, currentRequest->checkerId, currentRequest->newUserId, currentRequest->password);

    currentRequest = currentRequest->next;
  }

  fclose (requestsFile);
  if (requestsList != NULL)
      GmtUmlDestroyRequestList (requestsList);

  #ifdef _DEBUG_
  printf ("Rewriting users data file.\n");
  #endif

  if ((gmtUmlValidation = GmtUmlWriteUsersFile (usersList, configurationOptions)))
    return gmtUmlValidation;

  #ifdef _DEBUG_
  printf ("Done.\n");
  #endif

  /* Sending email */
  #ifdef _DEBUG_
  printf ("Ready to send email.\n");
  #endif

  token = GmtUmlSliceString (checkerData->email, "@");
  token = GmtUmlSliceString (NULL, "@");

  strcpy (clientDomain, token);
  /* strcat (smtpServer, clientDomain); */

  #ifdef _DEBUG_
  printf ("Domain: %s || SMTP Server: %s.\n", clientDomain, smtpServer);
  printf ("Preparing email\'s subject...\n");
  #endif

  snprintf (messageSubject, MAX_EMAIL_SUBJECT_LENGTH+1, "%s", configurationOptions->gmtUmlProjectName);

  #ifdef _DEBUG_
  printf ("Preparing email\'s body.\n");
  #endif

  snprintf (messageBody, MAX_EMAIL_BODY_LENGTH+1, "Hi,\nuser %s has requested to register on the system. Please approve his request.\n\nOla,\no usuario %s solicitou cadastro no sistema. Por favor, aprove ou nao sua solicitacao.\n\nHallo,\nBenutzer %s hat angefordert, auf dem System zu registrieren. Bitte genehmigen Sie Ihre Anfrage.", newUser->name, newUser->name, newUser->name);

  #ifdef _DEBUG_
  printf ("Sending email...\n");
  #endif

  if (sendMail (clientDomain, smtpServer, 25, GMT_UML_ADMIN_EMAIL, checkerData->email, "", "", messageSubject, messageBody, ""))
  {
    if (usersList != NULL)
      GmtUmlDestroyUserDataList (usersList);
    return gmtUmlErrorSendingEmail;
  }
  
  #ifdef _DEBUG_
  printf ("Done.\n");
  #endif

  GmtUmlDestroyUserDataList (usersList);

  return gmtUmlOk;
}

/* $RCSfile: gmtUmlRequestRegistration.c,v $ */