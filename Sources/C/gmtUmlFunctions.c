/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL 270 - Computacao II - Turma 2017/2
 *
 * $Author: gabriel.tavora $
 * $Date: 2017/12/21 22:04:50 $
 * $Log: gmtUmlFunctions.c,v $
 * Revision 1.3  2017/12/21 22:04:50  gabriel.tavora
 * *** empty log message ***
 *
 * Revision 1.2  2017/11/22 21:56:21  gabriel.tavora
 * Aula 1.1 finalizada.
 *
 * Revision 1.1  2017/11/15 02:01:34  gabriel.tavora
 * Initial revision
 *
 *
 */ 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<unistd.h>
#include<limits.h>

#include "gmtUmlConst.h"
#include "gmtUmlErrors.h"
#include "gmtUmlTypes.h"
#include "gmtUmlConfig.h"
#include "gmtUmlFunctions.h"
#include "gmtUmlCliUserInterface.h"
#include "gmtUmlGetUsers.h"

#define EOS '\0'

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
GmtUmlGetLanguageIndex (char * language)
{
  if (language == NULL)
    return gmtUmlEnglish;

  if (strlen(language) == 0)
    return gmtUmlEnglish;

  if (!strcmp(language, "gmtUmlEnglish") || !strcmp(language, "english") || !strcmp (language, "0"))
    return gmtUmlEnglish;
  else if (!strcmp(language, "gmtUmlPortuguese") || !strcmp(language, "portuguese") || !strcmp (language, "1"))
    return gmtUmlPortuguese;
  else
    return gmtUmlEnglish; 
}

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
GmtUmlGetAbsoluteFileName (char * path, char * fileName, char *absolutePath)
{
  if ((path == NULL) || (fileName == NULL))
    return gmtUmlErrorNullPointer;

  if (GmtUmlCheckStringField (path, GMT_UML_FILE_NAME_VALID_CHARS, 1, GMT_UML_MAX_PATH_LENGTH))
    return gmtUmlErrorInvalidPath;

  if (GmtUmlCheckStringField (fileName, GMT_UML_FILE_NAME_VALID_CHARS, 1, GMT_UML_MAX_FILE_NAME_LENGTH))
    return gmtUmlErrorInvalidFileName;

  snprintf (absolutePath, GMT_UML_MAX_PATH_LENGTH + GMT_UML_MAX_FILE_NAME_LENGTH - 1, "%s%s", path, fileName);
  
  return gmtUmlOk;
}


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
GmtUmlCheckStringField (char * string, char * validChar, size_t minLength, size_t maxLength)
{
  int stringIndex,
      validCharIndex;

  boolean found;

  if ((validChar == NULL) || (string == NULL))
    return gmtUmlErrorNullPointer;

  if ((minLength > maxLength) || (minLength <= 0) || (maxLength < 0))
    return gmtUmlErrorInvalidLength;

  if ((strlen (string) < minLength) || (strlen (string) > maxLength))
    return gmtUmlErrorStringLength;

  for(stringIndex = 0; stringIndex < strlen (string); stringIndex++)
  {
    found = False;

    for(validCharIndex = 0; validCharIndex < strlen (validChar); validCharIndex++)
      if (string[stringIndex] == validChar[validCharIndex])
      {
        found = True;
        break;
      }

    if (!found)
      return gmtUmlErrorInvalidChar;
  }

  return gmtUmlOk;
}


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
GmtUmlCheckNickname (char * username, char * validChar, size_t minLength, size_t maxLength)
{
  int index,
      count = 0;

  if ((minLength > maxLength) || (minLength < 0) || (maxLength < 0))
    return gmtUmlErrorInvalidLength;

  if (GmtUmlCheckStringField (username, validChar, minLength, maxLength))
    return gmtUmlErrorInvalidUsername;

  for (index = 0; index < strlen (username); index++)
    if (username [index] == '.')
      count++;
  
  if (count > 1)
    return gmtUmlErrorInvalidUsername;

  return gmtUmlOk;
}

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
GmtUmlCheckEmail (char * email, char * validChar, size_t minLength, size_t maxLength)
{
  int index,
      count = 0;

  if ((minLength > maxLength) || (minLength < 0) || (maxLength < 0))
    return gmtUmlErrorInvalidLength;

  if (GmtUmlCheckStringField (email, validChar, minLength, maxLength))
    return gmtUmlErrorInvalidEmail;

  for (index = 0; index < strlen (email); index++)
    if (email [index] == '@')
      count++;

  if (count > 1)
    return gmtUmlErrorInvalidEmail;

  return gmtUmlOk;
}

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
GmtUmlCreateRandomString (char * validChar, size_t length, char * randomString)
{
  unsigned count;

  if ((validChar == NULL) || (randomString == NULL))
    return gmtUmlErrorNullPointer;

  if (length < 1)
    return gmtUmlErrorInvalidLength;

  srand ((unsigned) time (NULL));

  for (count = 0; count < length; count++)
    randomString [count] = validChar [rand () % strlen (validChar)];

  randomString [count] = 0;

  return gmtUmlOk;
}

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
GmtUmlCreateNickname (char *rawName, char *firstUsername, char *secondUsername)
{
  char names [6][256],
       lowerName [GMT_UML_MAX_NAME_LENGTH+1],
       *token;

  unsigned short index = 0,
		 count = 0;

  #ifdef _DEBUG_
  printf ("Creating nicknames...\n");
  #endif

  if ((rawName == NULL) || (firstUsername == NULL))
    return gmtUmlErrorNullPointer;

  #ifdef _DEBUG_
  printf ("Name: %s.\n", rawName);
  #endif

  if (GmtUmlCheckStringField (rawName, GMT_UML_NAME_VALID_CHARS, 3, 256))
    return gmtUmlErrorInvalidName;

  memset (lowerName, 0x00, GMT_UML_MAX_NAME_LENGTH+1);
  memset (firstUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH+1);

  if (secondUsername != NULL)
    memset (secondUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH+1);

  while (rawName [index] != EOS)
  {
    lowerName [index] = (char) tolower (rawName [index]);
    index++;
  }

  token = strtok (lowerName, " ");

  if (!token)
    return gmtUmlErrorInvalidName;

  strcpy (names [count], token);
  count++;

  do
  {
    token = strtok (NULL, " ");

    if (token)
    {
      if (strlen (token) > 3)
      {
        strcpy (names [count], token);
        count++;
      }
    }
  } while (token);

  if (count < 3)
    return gmtUmlErrorInvalidName;

  strcpy (firstUsername, names [0]);
  firstUsername[strlen (names [0])] = '.';
  strcat (firstUsername, names [count-1]);

  #ifdef _DEBUG_
  printf ("First username option: %s.\n", firstUsername);
  #endif

  if (secondUsername != NULL)
  {
    strcpy (secondUsername, names [0]);
    secondUsername[strlen (names [0])] = '.';
    strcat (secondUsername, names [count-2]);
    #ifdef _DEBUG_
    printf ("Second username option: %s.\n", secondUsername);
    #endif
  }
  
  return gmtUmlOk;
}

/*
 * gmtUmlErrorType
 * GmtUmlGetCryptAlgorithm (char *, gmtUmlCryptAlgorithms *);
 *
 * Arguments:
 * char * - the hash to verify (I)
 * gmtUmlCryptAlgorithms * - the identified algorithm (O);
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 * gmtUmlErrorNullPointer - one of the arguments is a null pointer;
 * gmtUmlErrorInvalidEncryption - the function could not recognize the encryption of the string;
 *
 * Description:
 * This function returns the algorithm used to crypt a string.
 *
 */

gmtUmlErrorType
GmtUmlGetCryptAlgorithm (char *encryptedPassword, gmtUmlCryptAlgorithms *algorithm)
{
  if ((encryptedPassword == NULL) || (algorithm == NULL))
    return gmtUmlErrorNullPointer;

  if (encryptedPassword [0] != '$')
  {
    #ifdef _DEBUG_
    printf ("Checking hash's length.\n");
    #endif
    if (GmtUmlCheckStringField (encryptedPassword, GMT_UML_DES_VALID_CHARS, 13, 13))
      return gmtUmlErrorInvalidEncryption;

    #ifdef _DEBUG_
    printf ("The encryption is valid.\n");
    #endif

    *algorithm = gmtUmlDes;
    return gmtUmlOk;
  }

  if (encryptedPassword [1] != '1' && encryptedPassword [1] != '5' && encryptedPassword [1] != '6')
    return gmtUmlErrorInvalidEncryption;

  *algorithm = encryptedPassword [1] - '0';

  return gmtUmlOk;
}

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
GmtUmlEncodePasswordWithSpecificAlgorithm (char * rawPassword, gmtUmlCryptAlgorithms algorithm, char * encryptedPassword)
{
  char saltDes [2+1],
       saltMd5 [8+3+1],
       saltSha256 [19+3+1],
       saltSha512 [19+3+1];

  #ifdef _DEBUG_
  printf ("Encoding password...\n");
  #endif

  if ((rawPassword == NULL) || (encryptedPassword == NULL))
    return gmtUmlErrorNullPointer;

  if (GmtUmlCheckStringField (rawPassword, GMT_UML_PASSWORD_VALID_CHARS, GMT_UML_MIN_PASSWORD_LENGTH, GMT_UML_MAX_PASSWORD_LENGTH))
    return gmtUmlErrorInvalidPassword;

  switch (algorithm)
  {
    case gmtUmlDes:
      #ifdef _DEBUG_
      printf ("Using DES...\n");
      #endif

      GmtUmlCreateRandomString (GMT_UML_DES_VALID_CHARS, 2, saltDes);
      
      #ifdef _DEBUG_
      printf ("Salt: %s.\n", saltDes);
      #endif

      snprintf (encryptedPassword, 14, "%s", crypt (rawPassword, saltDes));
    break;

    case gmtUmlMd5:
      #ifdef _DEBUG_
      printf ("Using MD5...\n");
      #endif

      GmtUmlCreateRandomString (GMT_UML_MD5_VALID_CHARS, 9, saltMd5);
      saltMd5 [0] = '$';
      saltMd5 [1] = '1';
      saltMd5 [2] = '$';
      snprintf (encryptedPassword, 33, "%s", crypt (rawPassword, saltMd5));
    break;

    case gmtUmlSha256:
      #ifdef _DEBUG_
      printf ("Using Sha256...\n");
      #endif

      GmtUmlCreateRandomString (GMT_UML_SHA256_VALID_CHARS, 22, saltSha256);
      saltSha256 [0] = '$';
      saltSha256 [1] = '5';
      saltSha256 [2] = '$';
      snprintf (encryptedPassword, 65, "%s", crypt (rawPassword, saltSha256));
    break;

    case gmtUmlSha512:
      #ifdef _DEBUG_
      printf ("Using Sha512...\n");
      #endif

      GmtUmlCreateRandomString (GMT_UML_SHA512_VALID_CHARS, 22, saltSha512);
      saltSha512 [0] = '$';
      saltSha512 [1] = '6';
      saltSha512 [2] = '$';
      snprintf (encryptedPassword, 109, "%s", crypt (rawPassword, saltSha512));
    break;

    default:
    #ifdef _DEBUG_
    printf ("Invalid encryption algorithm...\n");
    #endif
    return gmtUmlErrorInvalidEncryption;
  }

  #ifdef _DEBUG_
  printf ("Encrypted password: %s\n", encryptedPassword);
  #endif

  return gmtUmlOk;
}

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
GmtUmlEncodePasswordWithSpecificSalt (char * rawPassword, char * salt, char * encryptedPassword)
{
  unsigned saltIdentifier;

  if ((rawPassword == NULL) || (salt == NULL) || (encryptedPassword == NULL))
    return gmtUmlErrorNullPointer;

  if (!GmtUmlCheckStringField (encryptedPassword, GMT_UML_SALT_VALID_CHARS, 2, 19+3+1))
    return gmtUmlErrorInvalidSalt;

  #ifdef _DEBUG_
  printf ("Encoding password with specific salt.\n");
  #endif

  if (salt [0] == '$')
  {
    if (salt [2] == '$')
    {
      saltIdentifier = salt [1] - '0';

      switch (saltIdentifier)
      {
        case gmtUmlMd5:
        case gmtUmlSha256:
        case gmtUmlSha512:
          strcpy (encryptedPassword, crypt (rawPassword, salt));
	  #ifdef _DEBUG_
          printf ("Hash: %s.\n", encryptedPassword);
          #endif

        break;

        default:
	#ifdef _DEBUG_
        printf ("Unsupported algorithm.\n");
        #endif

        return gmtUmlErrorUnsupportedAlgorithm;
      }
    }
    else
    {
      #ifdef _DEBUG_
      printf ("Invalid salt.\n");
      #endif

      return gmtUmlErrorInvalidSalt;
    }
  }
  else
  {
    if (strlen (salt) != 2)
    {
      #ifdef _DEBUG_
      printf ("Invalid salt. Salt length: %lu.\n", strlen (salt));
      #endif

      return gmtUmlErrorInvalidSalt;
    }

    strcpy (encryptedPassword, crypt (rawPassword, salt));

    #ifdef _DEBUG_
    printf ("Hash: %s.\n", encryptedPassword);
    #endif
  }

  return gmtUmlOk;
}

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
GmtUmlCheckPassword (char *rawPassword, char *encryptedPassword)
{
  char newEncrypted [107],
       salt [21];

  unsigned validation;

  gmtUmlCryptAlgorithms algorithm;

  #ifdef _DEBUG_
  printf ("Checking password...\n");
  #endif

  if ((rawPassword == NULL) || (encryptedPassword == NULL))
    return gmtUmlErrorNullPointer;

  if (GmtUmlCheckStringField (encryptedPassword, GMT_UML_ENCRYPTED_PASSWORD_VALID_CHARS, 3, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH))
    return gmtUmlErrorInvalidPassword;

  if((validation = GmtUmlGetCryptAlgorithm (encryptedPassword, &algorithm)))
    return validation;
  
  #ifdef _DEBUG_
  printf ("Algorithm %i...\n", algorithm);
  #endif

  switch (algorithm)
  {
    case gmtUmlDes:
    snprintf (salt, 2, "%s", encryptedPassword);
    salt [3] = '\0';
    break;

    case gmtUmlMd5:
    snprintf (salt, 9, "%s", encryptedPassword);
    salt [10] = '\0';
    break;

    case gmtUmlSha256:
    snprintf (salt, 20, "%s", encryptedPassword);
    salt [20] = '\0';
    break;

    default:
    case gmtUmlSha512:
    snprintf (salt, 20, "%s", encryptedPassword);
    salt [20] = '\0';
    break;
  }

  GmtUmlEncodePasswordWithSpecificSalt (rawPassword, salt, newEncrypted);

  if (strcmp (encryptedPassword, newEncrypted))
    return gmtUmlErrorPasswordsDontMatch;

  return gmtUmlOk;
}

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
GmtUmlGetConfigurationOptionsValues (char *fileName, gmtUmlConfigurationOptionsType *configurationOptions)
{
  FILE *leitura;
  unsigned lineMaxLength = 2048;
  
  unsigned long conversionResult;
  
  char buffer [lineMaxLength],
       option [lineMaxLength],
       value [lineMaxLength],
       *validation,
       *token;

  if (configurationOptions == NULL)
    return gmtUmlErrorNullPointer;

  memset (buffer, 0x00, lineMaxLength);
  memset (option, 0x00, lineMaxLength);
  memset (value, 0x00, lineMaxLength);
  
  configurationOptions->gmtUmlAdministratorUserIdentifier = GMT_UML_ADMINISTRATOR_USER_IDENTIFIER;
  strcpy(configurationOptions->gmtUmlPrivateRootDirectory, GMT_UML_PRIVATE_ROOT_DIRECTORY);
  strcpy(configurationOptions->gmtUmlDataDirectory, GMT_UML_DATA_DIRECTORY);
  strcpy(configurationOptions->gmtUmlCookiesDirectory, GMT_UML_COOKIES_DIRECTORY);
  strcpy(configurationOptions->gmtUmlUsersDataFilename, GMT_UML_USERS_DATA_FILENAME);
  strcpy(configurationOptions->gmtUmlInvitedUsersDataFilename, GMT_UML_INVITED_USERS_DATA_FILENAME);
  strcpy(configurationOptions->gmtUmlRequestingUsersDataFilename, GMT_UML_REQUESTING_USERS_DATA_FILENAME);
  strcpy(configurationOptions->gmtUmlLockedUsersDataFilename, GMT_UML_LOCKED_USERS_DATA_FILENAME);

  if (fileName != NULL) /* If no file name was informed, use the default configuration file */
    leitura = fopen (fileName, "r");
  else
    leitura = fopen (GMT_UML_DEFAULT_CONFIG_FILE, "r");
  
  if (!leitura)
    return gmtUmlErrorOpeningFile;
  
  while (fgets (buffer, lineMaxLength+1, leitura))
  {
    if (buffer [0] == '#')
      continue;

    if (buffer [0] == '\n')
      continue;
    
    token = strtok (buffer, "=");
    
    if (!token)
      return gmtUmlErrorInvalidConfigurationOption;
    
    strcpy (option, token);
    token = strtok (NULL, " ");
    
    if (!token)
      return gmtUmlErrorInvalidConfigurationOption;
    
    strcpy (value, token);
    
    if (value [strlen (value)-1] == '\n')
      value [strlen (value)-1] = '\0';

    #ifdef _DEBUG_
    printf ("Option: %s | Value: %s.\n", option, value);
    #endif

    if (!strcmp (option, "GMT_UML_ADMINISTRATOR_USER_IDENTIFIER"))
    {
      conversionResult = strtoul (value, &validation, 10);
      
      if (*validation != '\0')
        return gmtUmlErrorInvalidUserIdentifier;
        
      configurationOptions->gmtUmlAdministratorUserIdentifier = conversionResult;
    }
    else if (!strcmp (option, "GMT_UML_PRIVATE_ROOT_DIRECTORY"))
    {
      if (!GmtUmlCheckStringField (value, GMT_UML_FILE_NAME_VALID_CHARS, 1, GMT_UML_MAX_PATH_LENGTH))
        strcpy(configurationOptions->gmtUmlPrivateRootDirectory, value);
      else
        return gmtUmlErrorInvalidPath;
    }
    else if (!strcmp (option, "GMT_UML_DATA_DIRECTORY"))
    {
      if (!GmtUmlCheckStringField (value, GMT_UML_FILE_NAME_VALID_CHARS, 1, GMT_UML_MAX_PATH_LENGTH))
        strcpy(configurationOptions->gmtUmlDataDirectory, value);
      else
        return gmtUmlErrorInvalidPath;
    }
    else if (!strcmp (option, "GMT_UML_COOKIES_DIRECTORY"))
    {
      if (!GmtUmlCheckStringField (value, GMT_UML_FILE_NAME_VALID_CHARS, 1, GMT_UML_MAX_PATH_LENGTH))
        strcpy(configurationOptions->gmtUmlCookiesDirectory, value);
      else
        return gmtUmlErrorInvalidPath;
    }
    else if (!strcmp (option, "GMT_UML_USERS_DATA_FILENAME"))
    {
      if (!GmtUmlCheckStringField (value, GMT_UML_FILE_NAME_VALID_CHARS, 1, GMT_UML_MAX_PATH_LENGTH))
        strcpy(configurationOptions->gmtUmlUsersDataFilename, value);
      else
        return gmtUmlErrorInvalidFileName;
    }
    else if (!strcmp (option, "GMT_UML_INVITED_USERS_DATA_FILENAME"))
    {
      if (!GmtUmlCheckStringField (value, GMT_UML_FILE_NAME_VALID_CHARS, 1, GMT_UML_MAX_PATH_LENGTH))
        strcpy(configurationOptions->gmtUmlInvitedUsersDataFilename, value);
      else
        return gmtUmlErrorInvalidFileName;
    }
    else if (!strcmp (option, "GMT_UML_REQUESTING_USERS_DATA_FILENAME"))
    {
      if (!GmtUmlCheckStringField (value, GMT_UML_FILE_NAME_VALID_CHARS, 1, GMT_UML_MAX_PATH_LENGTH))
        strcpy(configurationOptions->gmtUmlRequestingUsersDataFilename, value);
      else
        return gmtUmlErrorInvalidFileName;
    }
    else if (!strcmp (option, "GMT_UML_LOCKED_USERS_DATA_FILENAME"))
    {
      if (!GmtUmlCheckStringField (value, GMT_UML_FILE_NAME_VALID_CHARS, 1, GMT_UML_MAX_PATH_LENGTH))
        strcpy(configurationOptions->gmtUmlLockedUsersDataFilename, value);
      else
        return gmtUmlErrorInvalidFileName;
    }
    else if (!strcmp (option, "GMT_UML_PROJECT_NAME"))
    {
      if (!GmtUmlCheckStringField (value, GMT_UML_NAME_VALID_CHARS, 1, GMT_UML_MAX_NAME_LENGTH))
        strcpy(configurationOptions->gmtUmlProjectName, value);
      else
        return gmtUmlErrorInvalidProjectName;
    }
    else if (!strcmp (option, "GMT_UML_DEFAULT_ENCODING_ALGORITHM"))
    {
      if (!strcmp (value, "gmtUmlDes") || !strcmp (value, "0"))
        configurationOptions->gmtUmlCryptAlgorithm = gmtUmlDes;
      else if (!strcmp (value, "gmtUmlMd5") || !strcmp (value, "1"))
        configurationOptions->gmtUmlCryptAlgorithm = gmtUmlMd5;
      else if (!strcmp (value, "gmtUmlSha256") || !strcmp (value, "5"))
        configurationOptions->gmtUmlCryptAlgorithm = gmtUmlSha256;
      else if (!strcmp (value, "gmtUmlSha512") || !strcmp (value, "6"))
        configurationOptions->gmtUmlCryptAlgorithm = gmtUmlSha512;
      else
        return gmtUmlErrorUnsupportedAlgorithm;
    }
    else
    {
      #ifdef _DEBUG_
      printf ("Option: %s.\n", option);
      #endif

      return gmtUmlErrorInvalidConfigurationOption;
    } /* if */
  } /* while */
  
  return gmtUmlOk;
}

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
GmtUmlSliceString (char * string, const char * delimiter)
{
    static char * source = NULL;
    char * p = NULL;
    char * ret = NULL;

    if(string)
        source = string;

    if(!source)
        return NULL;

    p = strpbrk(source, delimiter);

    if(p)
    {
        *p = 0;
        ret = source;
        source = ++p;
    }
    else if(*source)
    {
        ret = source;
        source = NULL;
    }

    return ret;
}

/*
 * gmtUmlErrorType
 * GmtUmlDestroyUserDataList (gmtUmlUserDataType *);
 *
 * Arguments:
 * gmtUmlUserDataType * - the first element of an threaded list;
 *
 * Returned code:
 * gmtUmlOk - Function has been executed successfully;
 *
 * Description:
 * Deletes an entire threaded list.
 */

gmtUmlErrorType
GmtUmlDestroyUserDataList (gmtUmlUserDataType *list)
{
  gmtUmlUserDataType *element = list;
  gmtUmlUserDataType *nextElement;

  while (element != NULL)
  {
    nextElement = element->next;
    free (element);
    element = nextElement;
  }

  return gmtUmlOk;
}

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
GmtUmlWriteUsersFile (gmtUmlUserDataType *usersList, gmtUmlConfigurationOptionsType *configurationOptions)
{
  FILE *gmtUmlUsersReadFile, *gmtUmlUsersWriteFile;
  char gmtUmlBackupName [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       readFilePath [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       writeFilePath [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1];
  int gmtUmlTempFile;
  boolean fileExists = False;
  gmtUmlUserDataType *current;
  gmtUmlErrorType gmtUmlValidation;

  if (configurationOptions == NULL)
  {
    gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (GMT_UML_DEFAULT_CONFIG_FILE, configurationOptions);
    if (gmtUmlValidation)
      return gmtUmlValidation;
  }

  if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (configurationOptions->gmtUmlDataDirectory, "gmtUmlUserDataFile.XXXXXX", writeFilePath)))
    return gmtUmlValidation;

  gmtUmlTempFile = mkstemp (writeFilePath);

  if (gmtUmlTempFile == -1)
    return gmtUmlErrorCreatingTempFile;

  if (!(gmtUmlUsersWriteFile = fdopen (gmtUmlTempFile, "w")))
    return gmtUmlErrorCreatingTempFile;

  if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (configurationOptions->gmtUmlDataDirectory, configurationOptions->gmtUmlUsersDataFilename, readFilePath)))
    return gmtUmlValidation;

  if ((gmtUmlUsersReadFile = fopen (readFilePath, "r")))
  {
    fclose (gmtUmlUsersReadFile);
    fileExists = True;
  }

  current = usersList;

  while (current->next != NULL)
  {
    #ifdef _DEBUG_
    printf ("%llu:%s:%s:%llu:%s:%s\n", current->id, current->nickname, current->password, current->profile, current->name, current->email);
    #endif
     
    fprintf (gmtUmlUsersWriteFile, "%llu:%s:%s:%llu:%s:%s\n", current->id, current->nickname, current->password, current->profile, current->name, current->email);

    current = current->next;
  }
  
  #ifdef _DEBUG_
  printf ("%llu:%s:%s:%llu:%s:%s\n", current->id, current->nickname, current->password, current->profile, current->name, current->email);
  #endif
  fprintf (gmtUmlUsersWriteFile, "%llu:%s:%s:%llu:%s:%s", current->id, current->nickname, current->password, current->profile, current->name, current->email);

  /* Renames the files, creating a backup*/
  #ifdef _DEBUG_
  printf ("Renaming the file.\n");
  #endif
   
  fclose (gmtUmlUsersWriteFile);

  snprintf (gmtUmlBackupName, GMT_UML_MAX_FILE_NAME_LENGTH+1, "%s%s.backup", configurationOptions->gmtUmlDataDirectory, configurationOptions->gmtUmlUsersDataFilename);

  if (fileExists)
    rename (readFilePath, gmtUmlBackupName);

  GmtUmlGetAbsoluteFileName (configurationOptions->gmtUmlDataDirectory, configurationOptions->gmtUmlUsersDataFilename, readFilePath);

  rename (writeFilePath, readFilePath);

  return gmtUmlOk;
}

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
GmtUmlWriteInvitationsFile (gmtUmlInvitationType *usersList, gmtUmlConfigurationOptionsType *configurationOptions)
{
  FILE *gmtUmlUsersReadFile, *gmtUmlUsersWriteFile;
  char gmtUmlBackupName [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       readFilePath [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
       writeFilePath [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1];
  int gmtUmlTempFile;
  boolean fileExists = False;
  gmtUmlInvitationType *current;
  gmtUmlErrorType gmtUmlValidation;

  if (configurationOptions == NULL)
  {
    gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (GMT_UML_DEFAULT_CONFIG_FILE, configurationOptions);
    if (gmtUmlValidation)
      return gmtUmlValidation;
  }

  if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (configurationOptions->gmtUmlDataDirectory, "gmtUmlInvitedUsersFile.XXXXXX", writeFilePath)))
    return gmtUmlValidation;

  gmtUmlTempFile = mkstemp (writeFilePath);

  if (gmtUmlTempFile == -1)
    return gmtUmlErrorCreatingTempFile;

  if (!(gmtUmlUsersWriteFile = fdopen (gmtUmlTempFile, "w")))
    return gmtUmlErrorCreatingTempFile;

  if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (configurationOptions->gmtUmlDataDirectory, configurationOptions->gmtUmlUsersDataFilename, readFilePath)))
    return gmtUmlValidation;

  if ((gmtUmlUsersReadFile = fopen (readFilePath, "r")))
  {
    fclose (gmtUmlUsersReadFile);
    fileExists = True;
  }

  current = usersList;

  while (current->next != NULL)
  {
    #ifdef _DEBUG_
    printf ("%llu:%s:%llu\n", current->id, current->tempPassword, current->expirationDate);
    #endif
     
    fprintf (gmtUmlUsersWriteFile, "%llu:%s:%llu\n", current->id, current->tempPassword, current->expirationDate);

    current = current->next;
  }
  
  #ifdef _DEBUG_
  printf ("%llu:%s:%llu\n", current->id, current->tempPassword, current->expirationDate);
  #endif
  fprintf (gmtUmlUsersWriteFile, "%llu:%s:%llu", current->id, current->tempPassword, current->expirationDate);

  /* Renames the files, creating a backup*/
  #ifdef _DEBUG_
  printf ("Renaming the file.\n");
  #endif
   
  fclose (gmtUmlUsersWriteFile);

  snprintf (gmtUmlBackupName, GMT_UML_MAX_FILE_NAME_LENGTH+1, "%s%s.backup", configurationOptions->gmtUmlDataDirectory, configurationOptions->gmtUmlInvitedUsersDataFilename);

  if (fileExists)
    rename (readFilePath, gmtUmlBackupName);

  GmtUmlGetAbsoluteFileName (configurationOptions->gmtUmlDataDirectory, configurationOptions->gmtUmlUsersDataFilename, readFilePath);

  rename (writeFilePath, readFilePath);

  return gmtUmlOk;
}

/*
 * gmtUmlErrorType
 * GmtUmlDestroyInvitationList (gmtUmlInvitationType *list);
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
GmtUmlDestroyInvitationList (gmtUmlInvitationType *list)
{
  gmtUmlInvitationType *element = list;
  gmtUmlInvitationType *nextElement;

  while (element != NULL)
  {
    nextElement = element->next;
    free (element);
    element = nextElement;
  }

  return gmtUmlOk;
}

/*
 * gmtUmlErrorType
 * GmtUmlDestroyRequestList (gmtUmlRequestType **list);
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
GmtUmlDestroyRequestList (gmtUmlRequestType *list)
{
  gmtUmlRequestType *element = list;
  gmtUmlRequestType *nextElement;

  while (element != NULL)
  {
    nextElement = element->next;
    free (element);
    element = nextElement;
  }

  return gmtUmlOk;
}

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
GmtUmlGetInvitationList (gmtUmlInvitationType **list, gmtUmlConfigurationOptionsType *configurationOptions)
{
  FILE *gmtUmlInvitedUsersFile;
  gmtUmlErrorType gmtUmlValidation;
  char *token, *validation;
  gmtUmlInvitationType *readingFirst, *readingPrevious, *new;

  char buffer [GMT_UML_USERS_FILE_LINE_LENGTH+1],
       filePath [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1];

  if (list == NULL)
    return gmtUmlErrorNullPointer;

  if (configurationOptions == NULL)
  {
    gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (GMT_UML_DEFAULT_CONFIG_FILE, configurationOptions);
    if (gmtUmlValidation)
      return gmtUmlValidation;
  }

  if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (configurationOptions->gmtUmlDataDirectory, configurationOptions->gmtUmlInvitedUsersDataFilename, filePath)))
    return gmtUmlValidation;

  if (!(gmtUmlInvitedUsersFile = fopen (filePath, "r")))
    return gmtUmlErrorOpeningFile;

  /* Begin to read */
  readingFirst = NULL;
  readingPrevious = NULL;

  #ifdef _DEBUG_
  printf ("\nBuffer:\n");
  #endif

  while (fgets (buffer, GMT_UML_USERS_FILE_LINE_LENGTH+1, gmtUmlInvitedUsersFile))
  {
    if (strlen (buffer) == 0)
      continue;
    
    if (!(new = (gmtUmlInvitationType *) malloc (sizeof (gmtUmlUserDataType))))
    {
      #ifdef _DEBUG_
      printf ("Could not allocate memory.\n");
      #endif
       
      fclose (gmtUmlInvitedUsersFile);
      return gmtUmlErrorAllocatingMemory;
    }

    /* Slicing the string */

    /* uid */
    token = GmtUmlSliceString (buffer, ":");
    
    if (token == NULL)
    {
      #ifdef _DEBUG_
      printf ("Error: invalid uid.\n");
      #endif
      free (new);
      GmtUmlDestroyInvitationList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }
    
    new->id = strtoull (token, &validation, 10);

    if (*validation != '\0')
    {
      #ifdef _DEBUG_
      printf ("Error: invalid uid.\n");
      #endif
      free (new);
      GmtUmlDestroyInvitationList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    /* password */
    token = GmtUmlSliceString (NULL, ":");
    
    strcpy (new->tempPassword, token);

    #ifdef _DEBUG_
    printf ("Password: %s.\n", token);
    #endif

    /* expirationDate */
    token = GmtUmlSliceString (NULL, ":");

    if (token == NULL)
    {
      free (new);
      GmtUmlDestroyInvitationList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    if (token [strlen (token) - 1] == '\n')
      token [strlen (token) - 1] = '\0';

    new->expirationDate = strtoull (token, &validation, 10);

    if (*validation != '\0')
    {
      #ifdef _DEBUG_
      printf ("Error: invalid expiration date. Validation: %c.\n", *validation);
      #endif
      free (new);
      GmtUmlDestroyInvitationList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    #ifdef _DEBUG_
    printf ("Id: %llu.\n", new->id);
    printf ("Password: %s.\n", new->tempPassword);
    printf ("Expiration date: %llu.\n", new->expirationDate);
    printf ("-----\n");
    #endif

    new->next = NULL;

    if (readingFirst == NULL)
    {
      #ifdef _DEBUG_
      printf ("Finished reading first element...\n");
      #endif
      
      readingFirst = new;
    }

    if (readingPrevious != NULL) /* if 'new' is not the first element */
    {
      #ifdef _DEBUG_
      printf ("Finished reading other element...\n");
      #endif
      
      readingPrevious->next = new;
    }
    readingPrevious = new;
  } /* while */

  *list = readingFirst;

  return gmtUmlOk;
}

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
GmtUmlGetRequestList (gmtUmlRequestType **requestList, gmtUmlConfigurationOptionsType *configurationOptions)
{
  FILE *gmtUmlRequestingUsersFile;
  gmtUmlErrorType gmtUmlValidation;
  char *token, *validation;
  gmtUmlRequestType *readingFirst, *readingPrevious, *new;

  char buffer [GMT_UML_USERS_FILE_LINE_LENGTH+1],
       filePath [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1];

  if (requestList == NULL)
    return gmtUmlErrorNullPointer;

  if (configurationOptions == NULL)
  {
    gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (GMT_UML_DEFAULT_CONFIG_FILE, configurationOptions);
    if (gmtUmlValidation)
      return gmtUmlValidation;
  }

  if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (configurationOptions->gmtUmlDataDirectory, configurationOptions->gmtUmlRequestingUsersDataFilename, filePath)))
    return gmtUmlValidation;

  if ((access (filePath, F_OK) == -1))
  {
    #ifdef _DEBUG_
    printf ("Requests file doesn\'t exist.\n");
    #endif

    if (!(gmtUmlRequestingUsersFile = fopen (filePath, "w")))
      return gmtUmlErrorOpeningFile;

    *requestList = NULL;
    return gmtUmlOk;
  }

  #ifdef _DEBUG_
  printf ("Requests file does exist.\n");
  #endif

  if (!(gmtUmlRequestingUsersFile = fopen (filePath, "r")))
    return gmtUmlErrorOpeningFile;

  /* Begin to read */
  readingFirst = NULL;
  readingPrevious = NULL;

  #ifdef _DEBUG_
  printf ("\nBuffer:\n");
  #endif

  while (fgets (buffer, GMT_UML_USERS_FILE_LINE_LENGTH+1, gmtUmlRequestingUsersFile))
  {
    if (!(new = (gmtUmlRequestType *) malloc (sizeof (gmtUmlRequestType))))
    {
      #ifdef _DEBUG_
      printf ("Could not allocate memory.\n");
      #endif
       
      fclose (gmtUmlRequestingUsersFile);
      return gmtUmlErrorAllocatingMemory;
    }

    /* Slicing the string */

    /* expirationDate */
    token = GmtUmlSliceString (buffer, ":");
    
    if (token == NULL)
    {
      free (new);
      GmtUmlDestroyRequestList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }
    
    new->expirationDate = strtoull (token, &validation, 10);

    if (*validation != '\0')
    {
      free (new);
      GmtUmlDestroyRequestList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    #ifdef _DEBUG_
    printf ("Expiration date: %s\n", token);
    #endif

    /* checkerId */
    token = GmtUmlSliceString (NULL, ":");
    
    if (token == NULL)
    {
      free (new);
      GmtUmlDestroyRequestList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }
    
    new->checkerId = strtoull (token, &validation, 10);

    if (*validation != '\0')
    {
      free (new);
      GmtUmlDestroyRequestList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    #ifdef _DEBUG_
    printf ("Checker id: %s\n", token);
    #endif

    /* newUserId */
    token = GmtUmlSliceString (NULL, ":");
    
    if (token == NULL)
    {
      free (new);
      GmtUmlDestroyRequestList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }
    
    new->newUserId = strtoull (token, &validation, 10);

    if (*validation != '\0')
    {
      free (new);
      GmtUmlDestroyRequestList (readingFirst);
      return gmtUmlErrorCorruptedUserFile;
    }

    #ifdef _DEBUG_
    printf ("New user id: %s\n", token);
    #endif

    /* password */
    token = GmtUmlSliceString (NULL, ":");

    #ifdef _DEBUG_
    printf ("%s...\n", token);
    #endif
    
    if (strlen (token) == 0)
      return gmtUmlErrorCorruptedUserFile;

    if (token [strlen (token) - 1] == '\n')
      token [strlen (token) - 1] = '\0';

    strcpy (new->password, token);

    #ifdef _DEBUG_
    printf ("Checker Id: %llu.\n", new->checkerId);
    printf ("New User\'s Id: %llu.\n", new->newUserId);
    printf ("Password: %s.\n", new->password);
    printf ("Expiration date: %llu.\n", new->expirationDate);
    printf ("-----\n");
    #endif

    new->next = NULL;

    if (readingFirst == NULL)
    {
      #ifdef _DEBUG_
      printf ("Finished reading first element...\n");
      #endif
      
      readingFirst = new;
    }

    if (readingPrevious != NULL) /* if 'new' is not the first element */
    {
      #ifdef _DEBUG_
      printf ("Finished reading other element...\n");
      #endif
      
      readingPrevious->next = new;
    }
    readingPrevious = new;
  } /* while */

  *requestList = readingFirst;

  return gmtUmlOk;
}

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
GmtUmlSelectNickname (char *name, char *nickname, gmtUmlConfigurationOptionsType *gmtUmlConfiguration)
{
  gmtUmlErrorType gmtUmlValidation;
  gmtUmlUserDataType *usersList, *current;
  char firstOption [GMT_UML_MAX_NICKNAME_LENGTH+1], secondOption [GMT_UML_MAX_NICKNAME_LENGTH+1];
  boolean isFirstOptionPossible = True, isSecondOptionPossible = True;

  if (name == NULL)
    return gmtUmlErrorInvalidName;

  if (nickname == NULL)
    return gmtUmlErrorInvalidNickname;

  #ifdef _DEBUG_
  printf ("Selecting nickname...\n");
  #endif

  if (gmtUmlConfiguration == NULL)
  {
    gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (GMT_UML_DEFAULT_CONFIG_FILE, gmtUmlConfiguration);
    if (gmtUmlValidation)
      return gmtUmlValidation;
  }

  if ((gmtUmlValidation = GmtUmlGetUsers (&usersList, gmtUmlConfiguration)))
    return gmtUmlValidation;

  if (GmtUmlCreateNickname (name, firstOption, secondOption))
    return gmtUmlErrorCannotCreateNickname;

  current = usersList;

  while (current != NULL)
  {
    if (!strcmp (firstOption, current->nickname))
      isFirstOptionPossible = False;
    if (!strcmp (secondOption, current->nickname))
      isSecondOptionPossible = False;
    current = current->next;
  }

  GmtUmlDestroyUserDataList (usersList);

  #ifdef _DEBUG_
  printf ("First option: %s.\n", firstOption);
  printf ("Second option: %s.\n", secondOption);
  #endif

  if (isFirstOptionPossible)
    strcpy (nickname, firstOption);
  else if (isSecondOptionPossible)
    strcpy (nickname, secondOption);
  else
    return gmtUmlErrorCannotCreateNickname;

  return gmtUmlOk;
}

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
GmtUmlValidateUserInformation (gmtUmlUserDataType *newUser)
{
  if (newUser->nickname == NULL)
    return gmtUmlErrorInvalidNickname;

  if ((newUser->password == NULL) || (newUser->passwordConfirmation == NULL))
    return gmtUmlErrorInvalidPassword;

  if ((newUser->name == NULL) || (newUser->nameConfirmation == NULL))
    return gmtUmlErrorInvalidName;

  if ((newUser->email == NULL) || (newUser->emailConfirmation == NULL))
    return gmtUmlErrorInvalidEmail;

  if (strcmp (newUser->password, newUser->passwordConfirmation))
    return gmtUmlErrorInvalidPassword;

  if (strcmp (newUser->name, newUser->nameConfirmation))
    return gmtUmlErrorInvalidName;

  if (strcmp (newUser->email, newUser->emailConfirmation))
    return gmtUmlErrorInvalidEmail;

  return gmtUmlOk;
}

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
GmtUmlCreatePassword (char *gmtUmlEncryptedPassword, gmtUmlLanguageType gmtUmlLanguage, gmtUmlConfigurationOptionsType *gmtUmlConfiguration)
{
  char gmtUmlPassword[GMT_UML_MAX_PASSWORD_LENGTH + 1], gmtUmlConfirmPassword[GMT_UML_MAX_PASSWORD_LENGTH + 1];
  char *gmtUmlTemp;

  gmtUmlErrorType gmtUmlValidation;
  
  if ((gmtUmlEncryptedPassword == NULL) || (gmtUmlConfiguration == NULL))
    return gmtUmlErrorNullPointer;

  memset (gmtUmlEncryptedPassword, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);

  gmtUmlTemp = getpass (GmtUmlGetCliUserInterface (gmtUmlInformNewUsersPassword, gmtUmlLanguage));

  strcpy (gmtUmlPassword, gmtUmlTemp);

  #ifdef _DEBUG_
  printf ("Password: \"%s\"\n", gmtUmlPassword);
  #endif

  memset (gmtUmlTemp, 0x00, strlen (gmtUmlTemp));

  gmtUmlTemp = getpass (GmtUmlGetCliUserInterface (gmtUmlConfirmNewUsersPassword, gmtUmlLanguage));
  
  strcpy (gmtUmlConfirmPassword, gmtUmlTemp);

  #ifdef _DEBUG_
  printf ("Password: \"%s\"\n", gmtUmlConfirmPassword);
  #endif

  memset (gmtUmlTemp, 0x00, strlen (gmtUmlTemp));

  if(strcmp (gmtUmlPassword, gmtUmlConfirmPassword))
    return gmtUmlErrorPasswordsDontMatch;

  memset (gmtUmlConfirmPassword, 0x00, strlen (gmtUmlPassword));
  
  if ((gmtUmlValidation = GmtUmlEncodePasswordWithSpecificAlgorithm (gmtUmlPassword, gmtUmlConfiguration->gmtUmlCryptAlgorithm, gmtUmlEncryptedPassword)))
    return gmtUmlValidation;
  
  memset (gmtUmlPassword, 0x00, strlen (gmtUmlPassword));

  return gmtUmlOk;
}

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
GmtUmlLogin (char *gmtUmlNickname, char *gmtUmlPassword, gmtUmlConfigurationOptionsType *gmtUmlConfiguration, gmtUmlUserDataType *gmtUmlUserData)
{
  char buffer [GMT_UML_USERS_FILE_LINE_LENGTH+1],
       filePath [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1];
  char *validation, *token;
  FILE *gmtUmlUsersFile;
  boolean found = False;

  char gmtUmlEncryptedPassword [GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1];
  char salt [19+3+1];

  gmtUmlCryptAlgorithms algorithm;
  gmtUmlErrorType gmtUmlValidation;
  gmtUmlUserDataType current;
  gmtUmlRequestType *requestsList, *currentRequest;

  if ((gmtUmlNickname == NULL) || (gmtUmlPassword == NULL) || (gmtUmlUserData == NULL))
    return gmtUmlErrorNullPointer;

  if (gmtUmlConfiguration == NULL)
  {
    gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (GMT_UML_DEFAULT_CONFIG_FILE, gmtUmlConfiguration);
    if (gmtUmlValidation)
      return gmtUmlValidation;
  }

  if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (gmtUmlConfiguration->gmtUmlDataDirectory, gmtUmlConfiguration->gmtUmlUsersDataFilename, filePath)))
    return gmtUmlValidation;

  if (!(gmtUmlUsersFile = fopen (filePath, "r"))) 
    return gmtUmlErrorOpeningFile;

  memset (&current, 0x00, sizeof (gmtUmlUserDataType));

  while (fgets (buffer, GMT_UML_USERS_FILE_LINE_LENGTH+1, gmtUmlUsersFile))
  {
    /* Slicing the string */

    /* uid */
    token = GmtUmlSliceString (buffer, ":");
    
    if (token == NULL)
      return gmtUmlErrorCorruptedUserFile;
    
    current.id = strtoull (token, &validation, 10);

    if (*validation != '\0')
      return gmtUmlErrorCorruptedUserFile;

    /* nickname */
    token = GmtUmlSliceString (NULL, ":");
    
    if (token == NULL)
      return gmtUmlErrorCorruptedUserFile;

    strcpy (current.nickname, token);

    /* password */
    token = GmtUmlSliceString (NULL, ":");
    
    if (!(strcmp (token, ":")))
      strcpy(current.password, "");
    else
      strcpy (current.password, token);

    /* profile */
    token = GmtUmlSliceString (NULL, ":");

    if (token == NULL)
      return gmtUmlErrorCorruptedUserFile;

    current.profile = strtoull (token, &validation, 10);

    if (*validation != '\0')
      return gmtUmlErrorCorruptedUserFile;

    /* name */
    token = GmtUmlSliceString (NULL, ":");
    
    if (token == NULL)
      return gmtUmlErrorCorruptedUserFile;

    strcpy (current.name, token);

    /* email */
    token = GmtUmlSliceString (NULL, ":");

    if (token == NULL)
      return gmtUmlErrorCorruptedUserFile;

    if (token [strlen (token) - 1] == '\n')
      token [strlen (token) - 1] = '\0';

    strcpy (current.email, token);

    #ifdef _DEBUG_
    printf ("Id: %llu.\n", current.id);
    printf ("Name: %s.\n", current.name);
    printf ("Nickname: %s.\n", current.nickname);
    printf ("Email: %s.\n", current.email);
    printf ("Profile: %llu.\n", current.profile);
    printf ("-----\n");
    #endif

    if (!strcmp (gmtUmlNickname, current.nickname))
    {
      found = True;
      break;
    }
  }

  if (!found)
    return gmtUmlErrorUserNotFound;

  /* Checks if user is still awaiting for approval */
  #ifdef _DEBUG_
  printf ("Checking requests file.\n");
  #endif

  if ((gmtUmlValidation = GmtUmlGetRequestList (&requestsList, gmtUmlConfiguration)))
    return gmtUmlValidation;

  #ifdef _DEBUG_
  printf ("1.\n");
  #endif

  currentRequest = requestsList;

  while (currentRequest != NULL)
  {
    #ifdef _DEBUG_
  printf ("2.\n");
  #endif
    if (currentRequest->newUserId == current.id)
      return gmtUmlErrorAwaitingApproval;
    #ifdef _DEBUG_
  printf ("3.\n");
  #endif

    currentRequest = currentRequest->next;
  }

  if (requestsList != NULL)
    GmtUmlDestroyRequestList (requestsList);

  GmtUmlGetCryptAlgorithm (current.password, &algorithm);

  #ifdef _DEBUG_
  printf ("Encrypted password: %s\n", current.password);
  #endif

  switch (algorithm)
  {
    case gmtUmlDes:
    snprintf (salt, 2, "%s", current.password);
    #ifdef _DEBUG_
    printf ("Salt: %s\n", salt);
    #endif
    break;

    case gmtUmlMd5:
    snprintf (salt, 11, "%s", current.password);
    #ifdef _DEBUG_
    printf ("Salt: %s\n", salt);
    #endif
    break;

    default:
    case gmtUmlSha256:
    case gmtUmlSha512:
    snprintf (salt, 20, "%s", current.password);
    #ifdef _DEBUG_
    printf ("Salt: %s\n", salt);
    #endif
    break;
  }
  
  if ((gmtUmlValidation = GmtUmlEncodePasswordWithSpecificSalt (gmtUmlPassword, salt, gmtUmlEncryptedPassword)))
    return gmtUmlValidation;
  
  memset (gmtUmlPassword, 0x00, strlen (gmtUmlPassword));

  if (strcmp (gmtUmlEncryptedPassword, current.password))
    return gmtUmlIncorrectPassword;

  gmtUmlUserData->id = current.id;
  gmtUmlUserData->profile = current.profile;
  strcpy (gmtUmlUserData->nickname, current.nickname);
  strcpy (gmtUmlUserData->password, current.password);
  strcpy (gmtUmlUserData->name, current.name);
  strcpy (gmtUmlUserData->email, current.email);

  return gmtUmlOk;
}

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
GmtUmlCliAskUserCredentials (char *gmtUmlNickname, char *gmtUmlPassword, gmtUmlLanguageType gmtUmlLanguage)
{
  char gmtUmlTemp [GMT_UML_MAX_PASSWORD_LENGTH+1];
  
  if ((gmtUmlNickname == NULL) || (gmtUmlPassword == NULL))
    return gmtUmlErrorNullPointer;

  printf ("%s", GmtUmlGetCliUserInterface (gmtUmlInformYourNickname, gmtUmlLanguage));
  fgets (gmtUmlTemp, GMT_UML_MAX_NICKNAME_LENGTH+2, stdin);

  if (gmtUmlTemp [strlen (gmtUmlTemp)-1] == '\n')
    gmtUmlTemp [strlen (gmtUmlTemp)-1] = '\0';

  if (GmtUmlCheckStringField (gmtUmlTemp, GMT_UML_NICKNAME_VALID_CHARS, 1, GMT_UML_MAX_NICKNAME_LENGTH))
    return gmtUmlErrorInvalidNickname;

  strcpy (gmtUmlNickname, gmtUmlTemp);
  memset (gmtUmlTemp, 0x00, strlen (gmtUmlTemp));

  strcpy (gmtUmlTemp, getpass (GmtUmlGetCliUserInterface (gmtUmlInformYourPassword, gmtUmlLanguage)));

  if (GmtUmlCheckStringField (gmtUmlTemp, GMT_UML_PASSWORD_VALID_CHARS, GMT_UML_MIN_PASSWORD_LENGTH, GMT_UML_MAX_PASSWORD_LENGTH))
    return gmtUmlErrorInvalidPassword;

  strcpy(gmtUmlPassword, gmtUmlTemp);
  memset(gmtUmlTemp, 0x00, strlen(gmtUmlTemp));

  return gmtUmlOk;
}

/*
 * char
 * GmtUmlCheckPrefix (char *, char *);
 *
 * Arguments:
 * char * - the string to check (I);
 * char * - the main string (I);
 *
 * Returned code:
 * 0 - the first string is prefix of the second one;
 *
 * Description:
 * Check if a string contains another;
 */

char
GmtUmlCheckPrefix (char *smaller, char *longer)
{
  unsigned index;

  for (index = 0; smaller [index] == longer [index]; index++)
    if (smaller [index] == '\0') return '\0';

  if (smaller [index] == '\0') return '\0';
    else return smaller [index] - longer [index];
}