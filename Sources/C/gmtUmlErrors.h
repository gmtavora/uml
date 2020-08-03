/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlErrors.h,v $
 * Revision 1.3  2017/12/21 22:04:50  gabriel.tavora
 * *** empty log message ***
 *
 * Revision 1.2  2017/11/22 21:56:21  gabriel.tavora
 * Aula 1.1 finalizada.
 *
 * Revision 1.1  2017/11/15 02:19:45  gabriel.tavora
 * Initial revision
 *
 *
 */

#ifndef _GMTUMLERRORS_H
#define _GMTUMLERRORS_H "@(#)gmtUmlErrors.h $Revision: 1.3 $"

#include "gmtUmlTypes.h"

typedef enum {
      gmtUmlOk, /* 0 */
      gmtUmlErrorNullPointer, /* 1 */
      gmtUmlErrorInvalidPath, /* 2 */
      gmtUmlErrorInvalidFileName, /* 3 */
      gmtUmlErrorInvalidLength, /* 4 */
      gmtUmlErrorStringLength, /* 5 */
      gmtUmlErrorInvalidChar, /* 6 */
      gmtUmlErrorInvalidUsername, /* 7 */
      gmtUmlErrorInvalidEmail, /* 8 */
      gmtUmlErrorInvalidName, /* 9 */
      gmtUmlErrorInvalidEncryption, /* 10 */
      gmtUmlErrorInvalidPassword, /* 11 */
      gmtUmlErrorInvalidSalt, /* 12 */
      gmtUmlErrorUnsupportedAlgorithm, /* 13 */
      gmtUmlErrorPasswordsDontMatch, /* 14 */
      gmtUmlErrorInvalidConfigurationOption, /* 15 */
      gmtUmlErrorInvalidUserIdentifier, /* 16 */
      gmtUmlErrorNullArgument, /* 17 */
      gmtUmlErrorInvalidLanguage, /* 18 */
      gmtUmlErrorInvalidArgument, /* 19 */
      gmtUmlErrorInvalidConfigFile, /* 20 */
      gmtUmlErrorInvalidUser, /* 21 */
      gmtUmlErrorUsernamesDontMatch, /* 22 */
      gmtUmlErrorEmailsDontMatch, /* 23 */
      gmtUmlErrorTooFewArguments, /* 24 */
      gmtUmlErrorInvalidProfile, /* 25 */
      gmtUmlErrorInvalidFriendEmail, /* 26 */
      gmtUmlErrorInvalidNickname, /* 27 */
      gmtUmlErrorInvalidEnvironment, /* 28 */
      gmtUmlErrorOpeningFile, /* 29 */
      gmtUmlErrorInvalidUserData, /* 30 */
      gmtUmlErrorUsersFileExists, /* 31 */
      gmtUmlErrorCreatingTempFile, /* 32 */
      gmtUmlErrorAllocatingMemory, /* 33 */
      gmtUmlErrorCorruptedUserFile, /* 34 */
      gmtUmlErrorInvalidProjectName, /* 35 */
      gmtUmlErrorSendingEmail, /* 36 */
      gmtUmlErrorOptionNotSupported, /* 37 */
      gmtUmlErrorInvalidKey, /* 38 */
      gmtUmlErrorDuplicateArgument, /* 39 */
      gmtUmlErrorCannotCreateNickname, /* 40 */
      gmtUmlErrorUserNotFound, /* 41 */
      gmtUmlIncorrectPassword, /* 42 */
      gmtUmlErrorCreatingConfigFile, /* 43 */
      gmtUmlErrorPermissionDenied, /* 44 */
      gmtUmlErrorNoInvitations, /* 45 */
      gmtUmlErrorCorruptedInvitedUsersFile, /* 46 */
      gmtUmlErrorInvitationNotFound, /* 47 */
      gmtUmlErrorInvitationExpired, /* 48 */
      gmtUmlErrorNicknameAlreadyExists, /* 49 */
      gmtUmlErrorEmailAlreadyExists, /* 50 */
      gmtUmlErrorAlreadyConfigured, /* 51 */
      gmtUmlErrorSystemNotConfigured, /* 52 */
      gmtUmlErrorAwaitingApproval, /* 53 */
      gmtUmlErrorNoRequests, /* 54 */
      gmtUmlErrorRequestNotFound, /* 55 */
      gmtUmlErrorFriendNotFound, /* 56 */
      gmtUmlErrorAdminNotFound, /* 57 */
      gmtUmlErrorNotLoggedIn, /* 58 */
      gmtUmlErrorInvalidCookie, /* 59 */
      gmtUmlErrorCookieDoesntExist, /* 60 */
      gmtUmlErrorOpeningCookie, /* 61 */
      gmtUmlErrorCorruptedCookie, /* 62 */
      gmtUmlErrorExpiredCookie, /* 63 */
      gmtUmlErrorIncorrectCookie, /* 64 */
      gmtUmlErrorAmount
} gmtUmlErrorType;

char *
GmtUmlGetCliErrorMessage (gmtUmlErrorType, gmtUmlLanguageType);

char *
GmtUmlGetNcursesErrorMessage (gmtUmlErrorType, gmtUmlLanguageType);

char *
GmtUmlGetWebErrorMessage (gmtUmlErrorType, gmtUmlLanguageType);

#endif
