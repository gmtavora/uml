/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlGetPendingRegistrationRequests.c,v $
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
#include "gmtUmlGetPendingRegistrationRequests.h"

/*
 * gmtUmlErrorType
 * GmtUmlGetPendingRegistrationRequests (gmtUmlConfigurationOptionsType *, char *, gmtUmlUserDataType *);
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
 * Prints all the valid registration requests.
 */

gmtUmlErrorType 
GmtUmlGetPendingRegistrationRequests (gmtUmlConfigurationOptionsType *configurationOptions, gmtUmlUserDataType **usersList)
{
  gmtUmlErrorType gmtUmlValidation;
  gmtUmlRequestType *requestsList = NULL, *currentRequest;
  gmtUmlUserDataType *tempUser, *currentUser, *previousUser;
  boolean foundUser;

  if ((gmtUmlValidation = GmtUmlGetRequestList (&requestsList, configurationOptions)))
    return gmtUmlValidation;

  if (requestsList == NULL)
    return gmtUmlErrorNoRequests;

  if ((gmtUmlValidation = GmtUmlGetUsers (usersList, configurationOptions)))
    return gmtUmlValidation;

  if (*usersList == NULL)
    return gmtUmlErrorSystemNotConfigured;

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