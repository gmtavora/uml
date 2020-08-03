/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlTypes.h,v $
 * Revision 1.4  2017/12/21 22:04:50  gabriel.tavora
 * *** empty log message ***
 *
 * Revision 1.3  2017/11/22 21:56:21  gabriel.tavora
 * Aula 1.1 finalizada.
 *
 * Revision 1.2  2017/11/15 02:46:47  gabriel.tavora
 * User types included.
 *
 * Revision 1.1  2002/01/06 20:19:45  gabriel.tavora
 * Initial revision
 *
 *
 */

#ifndef _GMTUMLTYPES_H
#define _GMTUMLTYPES_H "@(#)gmtUmlTypes.h $Revision: 1.4 $"

#include "gmtUmlConst.h"

typedef enum {gmtUmlEnglish, gmtUmlPortuguese, gmtUmlLanguageAmount} gmtUmlLanguageType;

typedef enum {False, True} boolean;

typedef unsigned long long gmtUmlUserIdentifierType;

typedef unsigned long long gmtUmlUserProfileType;

typedef enum {gmtUmlDes, gmtUmlMd5, gmtUmlSha256 = 5, gmtUmlSha512 = 6} gmtUmlCryptAlgorithms;

typedef struct gmtUmlUserDataType {
  gmtUmlUserIdentifierType id;

  char nickname [GMT_UML_MAX_NICKNAME_LENGTH + 1],
       password [GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH + 1],
       passwordConfirmation [GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH + 1];

  gmtUmlUserProfileType profile;
  
  char name [GMT_UML_MAX_NAME_LENGTH + 1],
       nameConfirmation [GMT_UML_MAX_NAME_LENGTH + 1],
       email [GMT_UML_MAX_EMAIL_LENGTH + 1],
       emailConfirmation [GMT_UML_MAX_EMAIL_LENGTH + 1];

  struct gmtUmlUserDataType *previous, *next;
} gmtUmlUserDataType;

typedef struct gmtUmlInvitationType
{
  gmtUmlUserIdentifierType id;
  char tempPassword [GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1];
  unsigned long long expirationDate;

  struct gmtUmlInvitationType *next;
} gmtUmlInvitationType;

typedef struct gmtUmlRequestType
{
  gmtUmlUserIdentifierType newUserId, checkerId;
  char password [GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1];
  unsigned long long expirationDate;

  struct gmtUmlRequestType *next;
} gmtUmlRequestType;

typedef struct {
  unsigned long gmtUmlAdministratorUserIdentifier;
  gmtUmlCryptAlgorithms gmtUmlCryptAlgorithm;
  char gmtUmlPrivateRootDirectory [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlDataDirectory [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlCookiesDirectory [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlUsersDataFilename [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlInvitedUsersDataFilename [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlRequestingUsersDataFilename [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlLockedUsersDataFilename [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       gmtUmlProjectName [GMT_UML_MAX_NAME_LENGTH+1];
} gmtUmlConfigurationOptionsType;

#endif   
