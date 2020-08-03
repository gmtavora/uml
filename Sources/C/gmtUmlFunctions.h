/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:08:41 $
 * $Log: gmtUmlFunctions.h,v $
 * Revision 1.5  2017/12/21 22:08:41  gabriel.tavora
 * *** empty log message ***
 *
 * Revision 1.4  2017/11/22 21:56:21  gabriel.tavora
 * Aula 1.1 finalizada.
 *
 * Revision 1.3  2017/11/15 01:59:03  gabriel.tavora
 * *** empty log message ***
 *
 * Revision 1.2  2017/11/14 11:55:43  gabriel.tavora
 * *** empty log message ***
 *
 * Revision 1.1  2002/01/06 20:27:11  gabriel.tavora
 * Initial revision
 *
 *
 */ 

#ifndef _GMTUMLFUNCTIONS_H
#define _GMTUMLFUNCTIONS_H "@(#)gmtUmlFunctions.h $Revision: 1.5 $"

/*
 *  gmtUmlLanguageType
 *  GmtUmlGetLanguageIndex (char *);
 *
 *  Arguments:
 *  char * - language (I)
 *
 *  Returned code:
 *  gmtUmlEnglish - selects english language;
 *  gmtUmlPortuguese - selects portuguese language;
 *
 *  Description:
 *  This function receives the language name and returns the language code.
 */

gmtUmlLanguageType
GmtUmlGetLanguageIndex (char * language);

/*
 * gmtUmlErrorType
 * GmtUmlGetAbsolutFileName (char *, char *, char *);
 *
 * Arguments:
 * char * - directory (I)
 * char * - file name (I)
 * char * - absolute file path (O)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlNullPointer - trying to use a NULL pointer as an argument;
 * gmtUmlErrorInvalidPath - the argument contains a string smaller/greater than limits, or invalid characters;
 * gmtUmlErrorInvalidFileName - the argument contains a string smaller/greater than limits, or invalid characters;
 *
 * Description:
 * This function concatenates the directory and the file name.
 */

gmtUmlErrorType
GmtUmlGetAbsoluteFileName (char *, char *, char *);

/*
 * gmtUmlErrorType
 * GmtUmlCheckStringField (char *, char *, size_t, size_t);
 *
 * Arguments:
 * char * - the string to check (I)
 * char * - valid set of characters (I)
 * size_t - min length (I)
 * size_t - max length (I)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlNullPointer - trying to use a NULL pointer as an argument;
 * gmtUmlErrorInvalidLength - the informed length is a negative number, or the min is greater than the max;
 * gmtUmlErrorStringLength - the string is outside min/max boundaries;
 * gmtUmlErrorInvalidChar - the string contains at least one characterer that doesn't belong to the valid set of chars;
 *
 * Description:
 * Given a set of chars, this function determinates whether or not a string is valid.
 */

gmtUmlErrorType
GmtUmlCheckStringField (char *, char *,  size_t, size_t);

/*
 * gmtUmlErrorType
 * GmtUmlGetCheckNickname (char *, char *, size_t, size_t);
 *
 * Arguments:
 * char * - the string to check (I)
 * char * - valid set of characters (I)
 * size_t - min length (I)
 * size_t - max length (I)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorInvalidLength - the informed length is a negative number, or the min is greater than the max;
 * gmtUmlErrorInvalidUsername - the string contain a char that does not belong to the valid set of characters,
 *                              or its length is outside the boundaries;
 *
 * Description:
 * Given a set of chars, this function determinates whether or not the username is valid.
 *
 */

gmtUmlErrorType
GmtUmlCheckNickname (char *, char *, size_t, size_t);

/*
 * gmtUmlErrorType
 * GmtUmlGetCheckEmail (char *, char *, size_t, size_t);
 *
 * Arguments:
 * char * - the string to check (I)
 * char * - valid set of characters (I)
 * size_t - min length (I)
 * size_t - max length (I)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorInvalidLength - the informed length is a negative number, or the min is greater than the max;
 * gmtUmlErrorInvalidEmail - the string contain a char that does not belong to the valid set of characters,
 *                           more than one '@', or its length is outside the boundaries;
 *
 * Description:
 * Given a set of chars, this function determinates whether or not the email is valid.
 *
 */

gmtUmlErrorType
GmtUmlCheckEmail (char *, char *, size_t, size_t);

/*
 * gmtUmlErrorType
 * GmtUmlCreateRandomString (char *, size_t, char *);
 *
 * Arguments:
 * char * - valid set of characters (I)
 * size_t - string length (I)
 * char * - random string generated (O)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - the first argument is NULL;
 * gmtUmlErrorInvalidLength - the informed length is smaller than 1;
 *
 * Description:
 * Given a set of chars, this function determinates whether or not the email is valid.
 *
 */

gmtUmlErrorType
GmtUmlCreateRandomString (char *, size_t, char *);

/*
 * gmtUmlErrorType
 * GmtUmlCreateNickname (char *, char *, char *);
 *
 * Arguments:
 * char * - full name (I)
 * char * - first nickname (O)
 * char * - second nickname (O)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - one of the arguments is a null pointer;
 * gmtUmlErrorInvalidName - the string contains at least one characterer that doesn't belong to the valid set of chars, is greater/smaller than the
                            max/min or it's not in a regular name format (First Middle Last);
 *
 * Description:
 * Given a name, this function returns two valid usernames.
 *
 */
 
gmtUmlErrorType
GmtUmlCreateNickname (char *, char *, char *);

/*
 * gmtUmlErrorType
 * GmtUmlGetCryptAlgorithm (char *, gmtUmlCryptAlgorithms *);
 *
 * Arguments:
 * char * - full name (I)
 * gmtUmlCryptAlgorithms * - the identified algorithm (O);
 *
 * Returned code:
 * gmtUmlOk - success;
 * gmtUmlErrorInvalidArgument - the first argument is NULL, or contains an invalid name (only letters, spaces and "-'" are allowed).
 *                              Each name must contains at least 3 characters;
 *
 * Description:
 * Given a name, this function returns two valid usernames.
 * 
 */

gmtUmlErrorType
GmtUmlGetCryptAlgorithm (char *, gmtUmlCryptAlgorithms *);

/*
 * gmtUmlErrorType
 * GmtUmlEncodePasswordWithSpecificAlgorithm (char *, gmtUmlCryptAlgorithms, char *);
 *
 * Arguments:
 * char * - password (I)
 * gmtUmlCryptAlgorithms * - the algorithm identification (I);
 * char * - encrypted password (O)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - one of the arguments is a null pointer;
 * gmtUmlErrorInvalidPassword - the password isn't in the expected format;
 * gmtUmlErrorInvalidEncryption - the function could not recognize the encryption of the string;
 *
 * Description:
 * This function encrypts a password using the informed algorithm.
 *
 */

gmtUmlErrorType
GmtUmlEncodePasswordWithSpecificAlgorithm (char *, gmtUmlCryptAlgorithms, char *);

/*
 * gmtUmlErrorType
 * GmtUmlEncodePasswordWithSpecificSalt (char *, char *, char *);
 *
 * Arguments:
 * char * - password (I)
 * char * - salt (I)
 * char * - encrypted password (O)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - one of the arguments is a null pointer;
 * gmtUmlErrorInvalidSalt - the function could not recognize the salt used to encode the string;
 *
 * Description:
 * This function encrypts a password using the informed salt.
 *
 */

gmtUmlErrorType
GmtUmlEncodePasswordWithSpecificSalt (char *, char *, char *);

/*
 * gmtUmlErrorType
 * GmtUmlCheckPassword (char *, char *);
 *
 * Arguments:
 * char * - password (I)
 * char * - encrypted password (O)
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - one of the arguments is a null pointer;
 * gmtUmlErrorInvalidPassword - the password isn't in the specified format;
 * gmtUmlErrorPasswordsDontMatch - the password is incorrect;
 *
 * Description:
 * Checks if the informed password is correct.
 */

gmtUmlErrorType
GmtUmlCheckPassword (char *, char *);

/*
 * gmtUmlErrorType
 * GmtUmlGetConfigurationOptionsValues (char *, gmtUmlConfigurationOptionsType *);
 *
 * Arguments:
 * char * - configuration file name (I)
 * gmtUmlConfigurationOptionsType * - the structure containing the values;
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - one of the arguments is a null pointer;
 * gmtUmlErrorOpeningFile - could not open the file;
 * gmtUmlErrorInvalidConfigurationOption - the specified configuration file contains an invalid line;
 * gmtUmlErrorInvalidUserIdentifier - the user identified contains invalid characters;
 * gmtUmlErrorInvalidPath - one of the paths contains invalid characters;
 * gmtUmlErrorInvalidFileName - one of the file names contains invalid characters;
 *
 * Description:
 * Loads the configuration options.
 */

gmtUmlErrorType
GmtUmlGetConfigurationOptionsValues (char *, gmtUmlConfigurationOptionsType *);

 /*
 * char *
 * GmtUmlSliceString (char *, const char *);
 *
 * Arguments:
 * char * - the string to slice (I);
 * const char * - the string cointaining the tokens;
 *
 * Returned code:
 * char * - the sliced string;
 *
 * Description:
 * This function works just like strtok, but if it finds two adjacent tokens, it returns a NULL pointer.
 */

char *
GmtUmlSliceString (char *, const char *);

/*
 * gmtUmlErrorType
 * GmtUmlDestroyUserDataList (gmtUmlUserDataType *);
 *
 * Arguments:
 * char * - the first element of an threaded list;
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Deletes an entire threaded list.
 */

gmtUmlErrorType
GmtUmlDestroyUserDataList (gmtUmlUserDataType *);

/*
 * gmtUmlErrorType
 * GmtUmlDestroyRequestList (gmtUmlRequestType **list);
 *
 * Arguments:
 * gmtUmlRequestType * - the first element of an threaded list;
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Deletes an entire threaded list.
 */

gmtUmlErrorType
GmtUmlDestroyRequestList (gmtUmlRequestType *list);

/*
 * gmtUmlErrorType
 * GmtUmlDestroyInvitationList (gmtUmlRequestType **list);
 *
 * Arguments:
 * gmtUmlInvitationType * - the first element of an threaded list;
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Deletes an entire threaded list.
 */

gmtUmlErrorType
GmtUmlDestroyInvitationList (gmtUmlInvitationType *list);

/*
 * gmtUmlErrorType
 * GmtUmlGetUserDataList (gmtUmlUserDataType *, gmtUmlConfigurationOptionsType *);
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
GmtUmlGetUserDataList (gmtUmlUserDataType **list, gmtUmlConfigurationOptionsType *configurationOptions);

/*
 * gmtUmlErrorType
 * GmtUmlGetInvitationList (gmtUmlInvitationType *, gmtUmlConfigurationOptionsType *);
 *
 * Arguments:
 * gmtUmlInvitationType * - the first element of an threaded list (O);
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
 * Reads the invited users file, creating an threaded list.
 */

gmtUmlErrorType
GmtUmlGetInvitationList (gmtUmlInvitationType **list, gmtUmlConfigurationOptionsType *configurationOptions);

/*
 * gmtUmlErrorType
 * GmtUmlGetRequestList (gmtUmlInvitationType *, gmtUmlConfigurationOptionsType *);
 *
 * Arguments:
 * gmtUmlRequestType * - the first element of an threaded list (O);
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
 * Reads the requesting users file, creating an threaded list.
 */

gmtUmlErrorType
GmtUmlGetRequestList (gmtUmlRequestType **requestList, gmtUmlConfigurationOptionsType *configurationOptions);

/*
 * gmtUmlErrorType
 * GmtUmlWriteUsersFile (gmtUmlUsersDataType *, gmtUmlConfigurationOptionsType *);
 *
 * Arguments:
 * gmtUmlUsersDataType * - the users threaded list (I);
 * gmtUmlConfigurationOptionsType * - the struct containing the options (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Rewrites users file.
 */

gmtUmlErrorType
GmtUmlWriteUsersFile (gmtUmlUserDataType *, gmtUmlConfigurationOptionsType *);

/*
 * gmtUmlErrorType
 * GmtUmlWriteUsersFile (gmtUmlInvitationType *, gmtUmlConfigurationOptionsType *);
 *
 * Arguments:
 * gmtUmlInvitationType * - the invitations threaded list (I);
 * gmtUmlConfigurationOptionsType * - the struct containing the options (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Rewrites invitations file.
 */

gmtUmlErrorType
GmtUmlWriteInvitationsFile (gmtUmlInvitationType *, gmtUmlConfigurationOptionsType *);

/*
 * gmtUmlErrorType
 * GmtUmlSelectNickname (char *, char *);
 *
 * Arguments:
 * char * - user full name (I)
 * char * - nickname (O);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorCannotCreateNickname - it was not possible to create a nickname;
 *
 * Description:
 * Checks if there is no occurrence of the nicknames, then returns the possible option.
 */

gmtUmlErrorType
GmtUmlSelectNickname (char *, char *, gmtUmlConfigurationOptionsType *);

/*
 * gmtUmlErrorType
 * GmtUmlValidateUserInformation (gmtUmlUserDataType *);
 *
 * Arguments:
 * gmtUmlUserDataType * - the structure containing the user data;
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorInvalidNickname - nickname is NULL;
 * gmtUmlErrorInvalidPassword - passwords dont match;
 * gmtUmlErrorInvalidName - names dont match;
 * gmtUmlErrorInvalidEmail - emails dont match;
 *
 * Description:
 * Validates user's informations.
 */

gmtUmlErrorType
GmtUmlValidateUserInformation (gmtUmlUserDataType *);

/*
 * gmtUmlErrorType
 * GmtUmlCreatePassword (char *, gmtUmlLanguageType);
 *
 * Arguments:
 * char * - the encrypted password (O);
 * gmtUmlLanguageType - the language (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - the first argument is a null pointer;
 * gmtUmlErrorPasswordsDontMatch - the user entered two different passwords;
 *
 * Description:
 * Create new password.
 */

gmtUmlErrorType
GmtUmlCreatePassword (char *, gmtUmlLanguageType, gmtUmlConfigurationOptionsType *);

/*
 * gmtUmlErrorType
 * GmtUmlLogin (gmtUmlUserIdentifierType, gmtUmlConfigurationOptionsType *, gmtUmlUserProfileType *);
 *
 * Arguments:
 * char * - the user's nickname (I);
 * char * - the user's password (I);
 * gmtUmlConfigurationOptionsType * - configuration options (I);
 * gmtUmlUserDataType * - the user struct (O);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - one of the arguments is a null pointer;
 * gmtUmlErrorOpeningFile - could not open user's data file;
 * gmtUmlErrorCorruptedUserFile - user's data file is corrupted;
 * gmtUmlErrorUserNotFound - the nickname doesn't exist;
 * gmtUmlIncorrectPassword - incorrect password;
 *
 * Description:
 * Checks if the user exists. If so, check if the informed password is correct.
 */


gmtUmlErrorType
GmtUmlLogin (char *, char *, gmtUmlConfigurationOptionsType *, gmtUmlUserDataType *);

/*
 * gmtUmlErrorType
 * GmtUmlCliAskUserCredentials (char *, char *, gmtUmlLanguageType);
 *
 * Arguments:
 * char * - the user's nickname (O);
 * char * - the user's password (O);
 * gmtUmlLanguageType - the language (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - one of the arguments is a null pointer;
 * gmtUmlErrorInvalidNickname - the nickname isn't valid;
 * gmtUmlErrorInvalidPassword - the password isn't valid;
 *
 * Description:
 * Ask user's nickname and password.
 */

gmtUmlErrorType
GmtUmlCliAskUserCredentials (char *, char *, gmtUmlLanguageType);

/*
 * char
 * GmtUmlCheckPrefix (char *, char *);
 *
 * Arguments:
 * char * - the string to check (I);
 * char * - the main string (I);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * 0 - the first string is prefix of the second one;
 *
 * Description:
 * Check if a string contains another;
 */

char
GmtUmlCheckPrefix (char *, char *);

#endif