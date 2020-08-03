/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlDisapproveRegistrationRequest.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#ifndef _GMTUMLCREATECOOKIEFILE_H
#define _GMTUMLCREATECOOKIEFILE_H "@(#)gmtUmlCreateCookieFile.h $Revision$"

#include "gmtUmlErrors.h"
#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlCreateCookieFile (char *cookiesDirectory, gmtUmlUserIdentifierType userId, unsigned long long expiration);
 *
 * Arguments:
 * char * - the directory to store the cookie (I)
 * gmtUmlUserIdentifierType - user id (I)
 * unsigned long long - expiration in seconds (I)
 * char * - the value generated (O)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Saves a cookie file in the specified directory. The file name will be the user id.
 */

gmtUmlErrorType
GmtUmlCreateCookieFile (char *cookiesDirectory, gmtUmlUserIdentifierType userId, unsigned long long expiration, char *generatedValue);

/* $RCSfile$ */

#endif