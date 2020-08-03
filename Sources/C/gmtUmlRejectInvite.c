/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlRejectInvite.c,v $
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
#include "gmtUmlConfig.h"
#include "gmtUmlFunctions.h"
#include "gmtUmlGetUsers.h"
#include "gmtUmlRejectInvite.h"
#include "./Libraries/sendmail.h"

#define MAX_EMAIL_SUBJECT_LENGTH 512
#define MAX_EMAIL_BODY_LENGTH 1024*5

/*
 * gmtUmlErrorType
 * GmtUmlRejectInvite (gmtUmlConfigurationOptionsType *, char *, char *);
 *
 * Arguments:
 * gmtUmlConfigurationOptionsType * - the struct containing the configuration options (I);
 * char * - the user's nickname (I);
 * char * - the temp password (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Reject invitation.
 */

gmtUmlErrorType 
GmtUmlRejectInvite (gmtUmlConfigurationOptionsType *gmtUmlConfiguration, gmtUmlUserDataType *gmtUmlUserData, char *tempPassword)
{
  FILE *gmtUmlUsersWriteFile;
  gmtUmlErrorType gmtUmlValidation;
  gmtUmlInvitationType *gmtUmlInvitationsList = NULL, *currentInvitation;
  gmtUmlUserDataType *gmtUmlUsersList = NULL, *currentUser;
  boolean found = False;
  char *token;

  char clientDomain [GMT_UML_MAX_EMAIL_LENGTH];
  char smtpServer [GMT_UML_MAX_EMAIL_LENGTH] = "smtp.del.ufrj.br";
  char messageSubject [MAX_EMAIL_SUBJECT_LENGTH+1];
  char messageBody [MAX_EMAIL_BODY_LENGTH+1];

  if (gmtUmlUserData == NULL)
    return gmtUmlErrorNullPointer;

  if (gmtUmlConfiguration == NULL)
  {
    gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (GMT_UML_DEFAULT_CONFIG_FILE, gmtUmlConfiguration);
    if (gmtUmlValidation)
      return gmtUmlValidation;
  }

  if ((gmtUmlValidation = GmtUmlGetInvitationList (&gmtUmlInvitationsList, gmtUmlConfiguration)))
    return gmtUmlValidation;

  currentInvitation = gmtUmlInvitationsList;

  while (currentInvitation != NULL)
  {
    if (currentInvitation->id == gmtUmlUserData->id)
    {
      found = True;
      break;
    }
    currentInvitation = currentInvitation->next;
  }

  if (!found)
    return gmtUmlErrorInvitationNotFound;

  /* Rewrite invite file */
  if (!(gmtUmlUsersWriteFile = fopen (gmtUmlConfiguration->gmtUmlInvitedUsersDataFilename, "w")))
    return gmtUmlErrorOpeningFile;

  currentInvitation = gmtUmlInvitationsList;

  while (currentInvitation != NULL)
  {
    if (currentInvitation->id != gmtUmlUserData->id)
      fprintf (gmtUmlUsersWriteFile, "%llu:%s:%llu\n", currentInvitation->id, currentInvitation->tempPassword, currentInvitation->expirationDate);
    currentInvitation = currentInvitation->next;
  }

  fclose (gmtUmlUsersWriteFile);
  GmtUmlDestroyInvitationList (gmtUmlInvitationsList);

  /* Rewrite user file */
  if ((gmtUmlValidation = GmtUmlGetUsers (&gmtUmlUsersList, gmtUmlConfiguration)))
    return gmtUmlValidation;

  if (!(gmtUmlUsersWriteFile = fopen (gmtUmlConfiguration->gmtUmlUsersDataFilename, "w")))
    return gmtUmlErrorOpeningFile;

  currentUser = gmtUmlUsersList;

  while (currentUser != NULL)
  {
    if (currentUser->id != gmtUmlUserData->id)
      fprintf (gmtUmlUsersWriteFile, "%llu:%s:%s:%llu:%s:%s\n", currentUser->id, currentUser->nickname, currentUser->password, currentUser->profile, currentUser->name, currentUser->email);
    currentUser = currentUser->next;
  }

  fclose (gmtUmlUsersWriteFile);
  GmtUmlDestroyUserDataList (gmtUmlUsersList);

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

  snprintf (messageBody, MAX_EMAIL_BODY_LENGTH+1,"Hello, %s\n\n Your data was removed from our system. Thanks for your attention.\n\nOla, %s\n\n seus dados foram removidos do nosso sistema. Obrigado pela atencao.\n\nHallo, %s\n\nIhre Informationen wurden aus unserer Datenbank entfernt. Danke fur Ihre Aufmerksamkeit.", gmtUmlUserData->nickname, gmtUmlUserData->nickname, gmtUmlUserData->nickname);

  #ifdef _DEBUG_
  printf ("Sending email...\n");
  #endif

  if (sendMail (clientDomain, smtpServer, 25, GMT_UML_ADMIN_EMAIL, gmtUmlUserData->email, "", "", messageSubject, messageBody, ""))
    return gmtUmlErrorSendingEmail;
  
  #ifdef _DEBUG_
  printf ("Done.\n");
  #endif

  return gmtUmlOk;
}

 /* $RCSfile: gmtUmlRejectInvite.c,v $ */