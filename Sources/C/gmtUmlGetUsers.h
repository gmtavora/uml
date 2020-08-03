/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlGetUsers.h,v $
 * Revision 1.1  2017/12/21 22:08:41  gabriel.tavora
 * Initial revision
 *
 *
 *
 */ 

#include "gmtUmlTypes.h"

/*
 * gmtUmlErrorType
 * GmtUmlGetUsers (gmtUmlUserDataType *, gmtUmlConfigurationOptionsType *);
 *
 * Arguments:
 * gmtUmlUserDataType * - the first element of an threaded list (O);
 * gmtUmlConfigurationOptionsType * - the struct containing the options (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - one of the arguments is a null pointer;
 * gmtUmlErrorOpeningFile - could not open user's data file;
 * gmtUmlErrorAllocatingMemory - could not allocate memory;
 * gmtUmlErrorCorruptedUserFile - user's data file is corrupted;
 *
 * Description:
 * Reads the user file, creating an threaded list.
 */

gmtUmlErrorType
GmtUmlGetUsers (gmtUmlUserDataType **, gmtUmlConfigurationOptionsType *);

 /* $RCSfile: gmtUmlGetUsers.h,v $ */