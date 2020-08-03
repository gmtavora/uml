/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlGetPendingRegistrationRequestsPerUser.c,v $
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
#include "gmtUmlGetPendingRegistrationRequestsPerUser.h"

/*
 * gmtUmlErrorType
 * GmtUmlGetPendingRegistrationRequestsPerUser (gmtUmlConfigurationOptionsType *, char *, gmtUmlUserDataType *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - pointer to the struct containing the configuration options (I);
 * char * - user's nickname (I);
 * gmtUmlUserDataType * - pointer to the first elementof the list containing the pending requests (O);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Requests a new registration.
 */

gmtUmlErrorType 
GmtUmlGetPendingRegistrationRequestsPerUser (gmtUmlConfigurationOptionsType *configurationOptions, char *userNickname, gmtUmlUserDataType **usersList)
{
  gmtUmlErrorType gmtUmlValidation;
  gmtUmlRequestType *requestsList = NULL, *currentRequest, *previousRequest, *tempRequest;
  gmtUmlUserDataType *tempUser, *currentUser, *previousUser, *friendData = NULL;
  boolean foundUser = False;

  if ((gmtUmlValidation = GmtUmlGetRequestList (&requestsList, configurationOptions)))
    return gmtUmlValidation;

  if (requestsList == NULL)
    return gmtUmlErrorNoRequests;

  if ((gmtUmlValidation = GmtUmlGetUsers (usersList, configurationOptions)))
    return gmtUmlValidation;

  if (*usersList == NULL)
    return gmtUmlErrorSystemNotConfigured;

  #ifdef _DEBUG_
  printf ("Reading users list...\n");
  #endif

  currentUser = *usersList;

  while (currentUser != NULL)
  {
    if (strcmp (currentUser->nickname, userNickname) == 0)
    {
      friendData = currentUser;
      foundUser = True;
      break;
    }
    currentUser = currentUser->next;
  }

  if (!foundUser)
  {
    GmtUmlDestroyRequestList (requestsList);
    GmtUmlDestroyUserDataList (*usersList);
    return gmtUmlErrorUserNotFound;
  }

  #ifdef _DEBUG_
  printf ("Reading requests list...\n");
  #endif

  currentRequest = requestsList;
  previousRequest = NULL;

  while (currentRequest != NULL)
  {
    if (currentRequest->checkerId != friendData->id)
    {
      #ifdef _DEBUG_
      printf ("Not what we are looking for...\n");
      #endif

      if (previousRequest == NULL)
        requestsList = currentRequest->next;
      else
        previousRequest->next = currentRequest->next;

      tempRequest = currentRequest;
      currentRequest = currentRequest->next;
      free (tempRequest);
      continue;
    }

    currentRequest = currentRequest->next;
  }

  #ifdef _DEBUG_
  printf ("Editing user's list...\n");
  #endif

  currentUser = *usersList;
  previousUser = NULL;

  while (currentUser != NULL)
  {
    #ifdef _DEBUG_
    printf ("Iteration...\n");
    #endif

    foundUser = False;

    currentRequest = requestsList;

    while (currentRequest != NULL)
    {
      if (currentRequest->newUserId == currentUser->id)
      {
        foundUser = True;
        break;
      }
      
      currentRequest = currentRequest->next;
    }

    if (!foundUser)
    {
      #ifdef _DEBUG_
      printf ("Not what we are looking for...\n");
      #endif

      if (previousUser == NULL)
        *usersList = currentUser->next;
      else
        previousUser->next = currentUser->next;

      tempUser = currentUser;
      currentUser = currentUser->next;
      free (tempUser);
      continue;
    }

    currentUser = currentUser->next; 
  }

  GmtUmlDestroyRequestList (requestsList);

  return gmtUmlOk;
}