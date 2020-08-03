/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlApproveRegistrationRequest.c,v $
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
#include "gmtUmlGetUsers.h"
#include "gmtUmlApproveRegistrationRequest.h"
#include "./Libraries/sendmail.h"

#define MAX_EMAIL_SUBJECT_LENGTH 512
#define MAX_EMAIL_BODY_LENGTH 1024*5

/*
 * gmtUmlErrorType
 * GmtUmlApproveRegistrationRequests (gmtUmlConfigurationOptionsType *, char *, char *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - pointer to the struct containing the configuration options (I);
 * char * - friend's nickname (I);
 * char * - user's nickname (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Approves a registration request.
 */

gmtUmlErrorType 
GmtUmlApproveRegistrationRequest (gmtUmlConfigurationOptionsType *configurationOptions, char *friendNickname, char *userNickname)
{
  FILE *requestsFile;
  gmtUmlErrorType gmtUmlValidation;
  gmtUmlRequestType *requestsList = NULL, *currentRequest, *previousRequest = NULL;
  gmtUmlUserDataType *usersList, *currentUser, *userData = NULL, *friendData = NULL;
  boolean foundRequest = False;
  char *token;

  char clientDomain [GMT_UML_MAX_EMAIL_LENGTH];
  char smtpServer [GMT_UML_MAX_EMAIL_LENGTH] = "smtp.del.ufrj.br";
  char messageSubject [MAX_EMAIL_SUBJECT_LENGTH+1];
  char messageBody [MAX_EMAIL_BODY_LENGTH+1];

  if ((friendNickname == NULL) || (userNickname == NULL))
    return gmtUmlErrorNullPointer;

  if ((gmtUmlValidation = GmtUmlGetRequestList (&requestsList, configurationOptions)))
    return gmtUmlValidation;

  if ((gmtUmlValidation = GmtUmlGetUsers (&usersList, configurationOptions)))
    return gmtUmlValidation;

  #ifdef _DEBUG_
  printf ("Searching for user and his friend...\n");
  #endif

  currentUser = usersList;

  while (currentUser != NULL)
  {
    if (strcmp (currentUser->nickname, userNickname) == 0)
      userData = currentUser;

    if (strcmp (currentUser->nickname, friendNickname) == 0)
      friendData = currentUser;

    currentUser = currentUser->next;
  }

  if (friendData == NULL)
    return gmtUmlErrorFriendNotFound;

  if (userData == NULL)
    return gmtUmlErrorUserNotFound;

  #ifdef _DEBUG_
  printf ("Searching for request...\n");
  #endif

  currentRequest = requestsList;

  while (currentRequest != NULL)
  {
    if ((currentRequest->newUserId == userData->id) && (currentRequest->checkerId == friendData->id))
    {
      foundRequest = True;
      break;
    }

    previousRequest = currentRequest;
    currentRequest = currentRequest->next;
  }

  if (!foundRequest)
    return gmtUmlErrorRequestNotFound;

  #ifdef _DEBUG_
  printf ("Request found. Removing from list...\n");
  #endif

  if (previousRequest == NULL)
  {
    if (currentRequest->next == NULL)
      requestsList = NULL;
    else
      requestsList =  currentRequest->next;
  }
  else
    previousRequest->next = currentRequest->next;

  free (currentRequest);

  #ifdef _DEBUG_
  printf ("Request and users found. Removing from requesting users file...\n");
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

  if (requestsList != NULL)
      GmtUmlDestroyRequestList (requestsList);

  #ifdef _DEBUG_
  printf ("Sending email...\n");
  #endif

  /* Sending email */
  #ifdef _DEBUG_
  printf ("Ready to send email.\n");
  #endif

  token = GmtUmlSliceString (userData->email, "@");
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

  snprintf (messageBody, MAX_EMAIL_BODY_LENGTH+1, "Hi,\nuser %s has approved your request. Welcome to the system!.\n\nOla,\no usuario %s aprovou sua solicitacao. Bem-vindo ao sistema!\n\nHallo,\nBenutzer %s hat Ihre Anfrage genehmigt. Willkommen im System!", friendData->name, friendData->name, friendData->name);

  #ifdef _DEBUG_
  printf ("Sending email...\n");
  #endif

  if (sendMail (clientDomain, smtpServer, 25, GMT_UML_ADMIN_EMAIL, userData->email, "", "", messageSubject, messageBody, ""))
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

/* $RCSfile: gmtUmlApproveRegistrationRequest.c,v $ */