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

#ifndef _GMTUMLCOMPARECOOKIE_H
#define _GMTUMLCOMPARECOOKIE_H "@(#)gmtUmlCompareCookie.h $Revision$"

#include "gmtUmlTypes.h"
#include "gmtUmlErrors.h"

/*
 * boolean
 * GmtUmlCompareCookieValues (char *cookiesDirectory, gmtUmlUserIdentifierType userId, char *receivedValue);
 *
 * Arguments:
 * char * - the cookie's directory (I)
 * gmtUmlUserIdentifierType - user id (I)
 * char * - the received value (I)
 *
 * Returned code:
 * true - the cookie is valid;
 * false - the cookie is invalid;
 *
 * Description:
 * Compares the informed cookie with the stored value, and returns true or false.
 */

gmtUmlErrorType
GmtUmlCompareCookie (char *, gmtUmlUserIdentifierType, char *);

#endif

/* $RCSfile$ */
