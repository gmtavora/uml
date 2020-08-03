/*
* Universidade Federal do Rio de Janeiro
* Escola Politecnica
* Departamento de Eletronica e de Computacao
* Prof. Marcelo Luiz Drumond Lanza
* EEL 270 - Computacao II - Turma 2017/2
*
* $Author: gabriel.tavora $
* $Date: 2017/12/21 22:04:50 $
* $Log: gmtUml.c,v $
* Revision 1.1  2017/12/21 22:04:50  gabriel.tavora
* Initial revision
*
*
*/ 

#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <pwd.h>

#include "gmtUmlTypes.h"
#include "gmtUmlErrors.h"
#include "gmtUmlConst.h"
#include "gmtUmlFunctions.h"
#include "gmtUmlConfig.h"

#include "gmtUmlShowCliHelp.h"
#include "gmtUmlCliUserInterface.h"
#include "gmtUmlRunNcursesInterface.h"
#include "gmtUmlShowConfigurationValues.h"
#include "gmtUmlAddUser.h"
#include "gmtUmlGetUsers.h"
#include "gmtUmlSearchUsers.h"
#include "gmtUmlRejectInvite.h"
#include "gmtUmlChangeUserPassword.h"
#include "gmtUmlAcceptInvite.h"
#include "gmtUmlRequestRegistration.h"
#include "gmtUmlGetPendingRegistrationRequestsPerUser.h"
#include "gmtUmlGetPendingRegistrationRequests.h"
#include "gmtUmlApproveRegistrationRequest.h"
#include "gmtUmlDisapproveRegistrationRequest.h"

#define EOS '\0'

typedef enum
{
	gmtUmlArgumentConfiguration,
	gmtUmlArgumentLanguage,
	gmtUmlArgumentUid,
	gmtUmlArgumentNickname,
	gmtUmlArgumentUsername,
	gmtUmlArgumentConfirmUsername,
	gmtUmlArgumentEmail,
	gmtUmlArgumentConfirmEmail,
	gmtUmlArgumentProfile,
	gmtUmlArgumentFriendEmail,
	gmtUmlArgumentKey
} gmtUmlArgumentIndexes;

gmtUmlErrorType
GmtUmlValidateArgument(char* gmtUmlArgumentList, char* gmtUmlArgumentValue, int gmtUmlMinLength, int gmtUmlMaxLength, char* gmtUmlValidChars,
	char *gmtUmlArgument, gmtUmlErrorType gmtUmlErrorCode)
{
	gmtUmlErrorType test;

	if (strlen(gmtUmlArgument) > 0)
		return gmtUmlErrorDuplicateArgument;

	if ((test = GmtUmlCheckStringField (gmtUmlArgumentValue, gmtUmlValidChars,  gmtUmlMinLength, gmtUmlMaxLength)))
		return gmtUmlErrorInvalidArgument;

	strcpy (gmtUmlArgument, gmtUmlArgumentValue);

	#ifdef __FreeBSD__
	if (strlen (gmtUmlArgumentList) > 0)
	{
		if ((strlen (gmtUmlArgument) + 1 + strlen (gmtUmlArgumentList)) > gmtUmlMaxLength)
			return gmtUmlErrorCode;

		strcat (gmtUmlArgument, " ");
		strcat (gmtUmlArgument, gmtUmlArgumentList);								
	}
	#endif

	return gmtUmlOk;
}

int
main (int argc, char **argv)
{
	const char *gmtUmlOptions = "hoNCaitjnqQvdUluprmecgsS";

	static struct option gmtUmlLongOptions [25] = {
		{"help", 0, NULL, 'h'},
		{"options", 0, NULL, 'o'},
		{"Ncurses", 0, NULL, 'N'},
		{"Configure", 0, NULL, 'C'},
		{"add", 0, NULL, 'a'},
		{"invite", 0, NULL, 'i'},
		{"accept", 0, NULL, 't'},
		{"reject", 0, NULL, 'j'},
		{"new", 0, NULL, 'n'},
		{"request", 0, NULL, 'q'},
		{"Request", 0, NULL, 'Q'},
		{"approve", 0, NULL, 'v'},
		{"disapprove", 0, NULL, 'd'},
		{"unlocking", 0, NULL, 'U'},
		{"lock", 0, NULL, 'l'},
		{"unlock", 0, NULL, 'u'},
		{"password", 0, NULL, 'p'},
		{"reset", 0, NULL, 'r'},
		{"modify", 0, NULL, 'm'},
		{"edit", 0, NULL, 'e'},
		{"confirm", 0, NULL, 'c'},
		{"group", 0, NULL, 'g'},
		{"show", 0, NULL, 's'},
		{"Search", 0, NULL, 'S'},
		{NULL, 0, NULL, 0}
	};

	char *gmtUmlArgumentNames [] = 
	{
		"configuration",
		"language",
		"uid",
		"user",
		"username",
		"confirm-username",
		"email",
		"confirm-email",
		"profile",
		"friend-email",
		"key",
		NULL
	};

	int gmtUmlOption,
	    gmtUmlLongOption,
	    gmtUmlArgumentIndex,
	    gmtUmlArgumentsSet,
	    index;

	char *gmtUmlArguments, *gmtUmlArgumentValue;

	char gmtUmlConfiguration [GMT_UML_MAX_FILE_NAME_LENGTH + 1],
			 gmtUmlLanguageName [GMT_UML_MAX_LANGUAGE_LENGTH + 1],
	     gmtUmlNickname [GMT_UML_MAX_NICKNAME_LENGTH + 1],
	     gmtUmlNewUserNickname [GMT_UML_MAX_NICKNAME_LENGTH + 1],
	     gmtUmlUsername [GMT_UML_MAX_NAME_LENGTH + 1],
	     gmtUmlConfirmUsername [GMT_UML_MAX_NAME_LENGTH + 1],
	     gmtUmlEmail [GMT_UML_MAX_EMAIL_LENGTH + 1],
	     gmtUmlConfirmEmail [GMT_UML_MAX_EMAIL_LENGTH + 1],
	     gmtUmlProfile [GMT_UML_MAX_PROFILE_LENGTH + 1],
	     gmtUmlFriendEmail [GMT_UML_MAX_EMAIL_LENGTH + 1],
	     gmtUmlKey [GMT_UML_MAX_KEY_LENGTH + 1],
	     gmtUmlEncryptedPassword [GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH + 1],
	     gmtUmlNewPassword [GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH + 1],
	     gmtUmlNewPasswordConfirmation [GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH + 1],
	     gmtUmlPassword [GMT_UML_MAX_PASSWORD_LENGTH + 1],
	     gmtUmlFilePath [GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1],
	     gmtUmlUid [GMT_UML_MAX_ID_LENGTH+1];
	opterr = 0;

	memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
	memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
	memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
	memset (gmtUmlNewUserNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
	memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
	memset (gmtUmlConfirmUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
	memset (gmtUmlEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
	memset (gmtUmlConfirmEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
	memset (gmtUmlProfile, 0x00, GMT_UML_MAX_PROFILE_LENGTH + 1);
	memset (gmtUmlFriendEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
	memset (gmtUmlKey, 0x00, GMT_UML_MAX_KEY_LENGTH + 1);
	memset (gmtUmlEncryptedPassword, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH + 1);
	memset (gmtUmlNewPassword, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH + 1);
	memset (gmtUmlNewPasswordConfirmation, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH + 1);
	memset (gmtUmlPassword, 0x00, GMT_UML_MAX_PASSWORD_LENGTH + 1);
	memset (gmtUmlFilePath, 0x00, GMT_UML_MAX_PATH_LENGTH+GMT_UML_MAX_FILE_NAME_LENGTH+1);
	memset (gmtUmlUid, 0x00, GMT_UML_MAX_ID_LENGTH+1);

	gmtUmlConfigurationOptionsType gmtUmlConfigurationOptions;
	gmtUmlUserDataType gmtUmlUserData, gmtUmlNewUser, *gmtUmlUsersList, *gmtUmlCurrentUser;
	gmtUmlLanguageType gmtUmlLanguage = gmtUmlEnglish;
	gmtUmlUserProfileType gmtUmlUserProfile;

	gmtUmlErrorType gmtUmlValidation;
	char *validation;
	boolean found = False;

	FILE *gmtUmlNewConfigFile;

	while ((gmtUmlOption = getopt_long (argc, argv, gmtUmlOptions, gmtUmlLongOptions, &gmtUmlLongOption)) != -1)
	{
		switch (gmtUmlOption)
		{
			case 'h':
	    #ifdef _DEBUG_
			printf ("HELP.\n");
	    #endif
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(gmtUmlArgumentValue == NULL)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:

					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 1, GMT_UML_MAX_LANGUAGE_LENGTH,
						GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);		
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					break;
				}
				optind++;
			}
			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf (" > While reading %s...\n", gmtUmlConfiguration);
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			GmtUmlShowCliHelp (&gmtUmlConfigurationOptions, GmtUmlGetLanguageIndex(gmtUmlLanguageName));

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			break;

			case 'o':
			#ifdef _DEBUG_
			printf ("PRINT CONFIGURATION OPTIONS.\n");
	    #endif
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(gmtUmlArgumentValue == NULL)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;
				}
				optind++;
			}
			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

	#ifdef _DEBUG_
			printf ("Language: %s | Configuration: %s.\n", gmtUmlLanguageName, gmtUmlConfiguration);
	#endif

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf (" > While reading %s...\n", gmtUmlConfiguration);
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			GmtUmlShowConfigurationValues (&gmtUmlConfigurationOptions, gmtUmlLanguage);

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			break;

			case 'N':
			#ifdef _DEBUG_
			printf ("NCURSES.\n");
			#endif

			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(gmtUmlArgumentValue == NULL)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
				  {
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;
			}

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			if (gmtUmlArgumentsSet != 1)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit (gmtUmlErrorTooFewArguments);
			}

	#ifdef _DEBUG_
			printf ("Nickname: %s | Language: %s | Configuration: %s.\n", gmtUmlNickname, gmtUmlLanguageName, gmtUmlConfiguration);
	#endif

			GmtUmlRunNcursesInterface (&gmtUmlConfigurationOptions, gmtUmlNickname, gmtUmlLanguage);

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			break;

			case 'C':
	#ifdef _DEBUG_
			printf ("CREATE USER FILE.\n");
	#endif

			gmtUmlArgumentsSet = 0;

			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(gmtUmlArgumentValue == NULL)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);							
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlUsername, gmtUmlErrorInvalidUsername);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentConfirmUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlConfirmUsername, gmtUmlErrorUsernamesDontMatch);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlEmail, gmtUmlErrorInvalidEmail);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentConfirmEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlConfirmEmail, gmtUmlErrorEmailsDontMatch);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;
			}

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			if (gmtUmlArgumentsSet != 4)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

      if ((access (gmtUmlConfiguration, F_OK) == -1))
      {
        /* The configuration file doesn't exist. This code will create one with the default configuration options. */
        gmtUmlNewConfigFile= fopen (gmtUmlConfiguration, "w");

        if (!gmtUmlNewConfigFile)
        {
          printf ("ERROR (#%i): %s.\n", gmtUmlErrorCreatingConfigFile, GmtUmlGetCliErrorMessage (gmtUmlErrorCreatingConfigFile, gmtUmlLanguage));
          exit (gmtUmlErrorCreatingConfigFile);
        }

        fprintf(gmtUmlNewConfigFile, "GMT_UML_ADMINISTRATOR_USER_IDENTIFIER=%i\n", GMT_UML_ADMINISTRATOR_USER_IDENTIFIER);
        fprintf(gmtUmlNewConfigFile, "GMT_UML_PRIVATE_ROOT_DIRECTORY=%s\n", GMT_UML_PRIVATE_ROOT_DIRECTORY);
        fprintf(gmtUmlNewConfigFile, "GMT_UML_DATA_DIRECTORY=%s\n", GMT_UML_DATA_DIRECTORY);
        fprintf(gmtUmlNewConfigFile, "GMT_UML_COOKIES_DIRECTORY=%s\n", GMT_UML_COOKIES_DIRECTORY);
        fprintf(gmtUmlNewConfigFile, "GMT_UML_USERS_DATA_FILENAME=%s\n", GMT_UML_USERS_DATA_FILENAME);
        fprintf(gmtUmlNewConfigFile, "GMT_UML_INVITED_USERS_DATA_FILENAME=%s\n", GMT_UML_INVITED_USERS_DATA_FILENAME);
        fprintf(gmtUmlNewConfigFile, "GMT_UML_REQUESTING_USERS_DATA_FILENAME=%s\n", GMT_UML_REQUESTING_USERS_DATA_FILENAME);
        fprintf(gmtUmlNewConfigFile, "GMT_UML_LOCKED_USERS_DATA_FILENAME=%s\n", GMT_UML_LOCKED_USERS_DATA_FILENAME);
        fprintf(gmtUmlNewConfigFile, "GMT_UML_PROJECT_NAME=%s\n", GMT_UML_PROJECT_NAME);
        fprintf(gmtUmlNewConfigFile, "GMT_UML_DEFAULT_ENCODING_ALGORITHM=%i\n", GMT_UML_DEFAULT_ENCODING_ALGORITHM);

        fclose (gmtUmlNewConfigFile);
      }

      if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf (" > While reading %s...\n", gmtUmlConfiguration);
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			if ((gmtUmlValidation = GmtUmlGetAbsoluteFileName (gmtUmlConfigurationOptions.gmtUmlPrivateRootDirectory, gmtUmlConfigurationOptions.gmtUmlUsersDataFilename, gmtUmlFilePath)))
    		return gmtUmlValidation;

      if ((access (gmtUmlFilePath, F_OK) == 0))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorAlreadyConfigured, GmtUmlGetCliErrorMessage (gmtUmlErrorAlreadyConfigured, gmtUmlLanguage));
				exit(gmtUmlErrorAlreadyConfigured);
			}

			strcpy(gmtUmlProfile, "1");

			strcpy (gmtUmlUserData.nickname, "admin");
			gmtUmlUserData.profile = 1;
			strcpy (gmtUmlUserData.name, gmtUmlUsername);
			strcpy (gmtUmlUserData.nameConfirmation, gmtUmlConfirmUsername);
			strcpy (gmtUmlUserData.email, gmtUmlEmail);
			strcpy (gmtUmlUserData.emailConfirmation, gmtUmlConfirmEmail);
			memset (gmtUmlUserData.password, 0x00, GMT_UML_MAX_PASSWORD_LENGTH+1);
			memset (gmtUmlUserData.passwordConfirmation, 0x00, GMT_UML_MAX_PASSWORD_LENGTH+1);

	#ifdef _DEBUG_
			printf ("Language: %s | Configuration: %s.\n", gmtUmlLanguageName, gmtUmlConfiguration);
			printf ("Username: %s | Email: %s.\n", gmtUmlUsername, gmtUmlEmail);
			printf ("Profile: %s.\n", gmtUmlProfile);
	#endif

			if(GMT_UML_ADMINISTRATOR_USER_IDENTIFIER == getuid())
			{
				if(!(gmtUmlValidation = GmtUmlValidateUserInformation (&gmtUmlUserData)))
				{
					if(!(gmtUmlValidation = GmtUmlCreatePassword (gmtUmlEncryptedPassword, GmtUmlGetLanguageIndex (gmtUmlLanguageName), &gmtUmlConfigurationOptions)))
					{
					  GmtUmlCreateNickname (gmtUmlUserData.name, gmtUmlUserData.nickname, NULL);
						strcpy (gmtUmlUserData.password, gmtUmlEncryptedPassword);
						strcpy (gmtUmlUserData.passwordConfirmation, gmtUmlEncryptedPassword);
						strcpy (gmtUmlUserData.email, gmtUmlEmail);
						strcpy (gmtUmlUserData.emailConfirmation, gmtUmlConfirmEmail);
				  	gmtUmlValidation = GmtUmlAddUser (&gmtUmlConfigurationOptions, &gmtUmlUserData);

				  	if (gmtUmlValidation)
				  	{
							printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
							exit (gmtUmlValidation);
						}
						else
							printf ("%s %s %s.\n", GmtUmlGetCliUserInterface (gmtUmlAccountCreatedSuccessfully, gmtUmlLanguage), GmtUmlGetCliUserInterface (gmtUmlYourNicknameIs, gmtUmlLanguage), gmtUmlUserData.nickname);
					}
					else
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit (gmtUmlValidation);
					}
				}
				else
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
					exit (gmtUmlValidation);
				}
			}	
			else
			{
				printf("Permission denied.\n");
				exit (gmtUmlValidation);
			}

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
			memset (gmtUmlConfirmUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
			memset (gmtUmlEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlConfirmEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlProfile, 0x00, GMT_UML_MAX_PROFILE_LENGTH + 1);
			break;

			case 'a':
	#ifdef _DEBUG_
			printf ("ADD USER.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlUsername, gmtUmlErrorInvalidUsername);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentConfirmUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlConfirmUsername, gmtUmlErrorUsernamesDontMatch);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlEmail, gmtUmlErrorInvalidEmail);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentConfirmEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlConfirmEmail, gmtUmlErrorEmailsDontMatch);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentProfile:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_PROFILE_LENGTH, GMT_UML_PROFILE_VALID_CHARS, gmtUmlProfile, gmtUmlErrorInvalidProfile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					gmtUmlArgumentsSet++;
					break;
				}
				optind++;
			}

			#ifdef _DEBUG_
			printf ("%i\n", gmtUmlArgumentsSet);
			#endif

			if (gmtUmlArgumentsSet != 5)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			memset (&gmtUmlNewUser, 0x00, sizeof (gmtUmlUserData));

			gmtUmlNewUser.id = strtoull (gmtUmlUid, &validation, 10);

			if (*validation != '\0')
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
			  exit (gmtUmlErrorInvalidArgument);
			}

      gmtUmlNewUser.profile = strtoull (gmtUmlProfile, &validation, 10);

      if (*validation != '\0')
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
			  exit (gmtUmlErrorInvalidArgument);
			}

      strcpy (gmtUmlNewUser.email, gmtUmlEmail);
      strcpy (gmtUmlNewUser.emailConfirmation, gmtUmlConfirmEmail);
      strcpy (gmtUmlNewUser.name, gmtUmlUsername);
      strcpy (gmtUmlNewUser.nameConfirmation, gmtUmlUsername);

			if (GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions))
      {
        printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidConfigFile, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidConfigFile, gmtUmlLanguage));
			  exit (gmtUmlErrorInvalidConfigFile);
      }

      /* Ask user's credentials */
      GmtUmlCliAskUserCredentials (gmtUmlNickname, gmtUmlPassword, gmtUmlLanguage);

      /* Add user */
	  	if (!(gmtUmlValidation = GmtUmlLogin (gmtUmlNickname, gmtUmlPassword, &gmtUmlConfigurationOptions, &gmtUmlUserData)))
			{
				if(gmtUmlUserData.profile <= gmtUmlNewUser.profile) /* One user can only add other with same profile or less */
				{
					if(!(gmtUmlValidation = GmtUmlValidateUserInformation (&gmtUmlNewUser)))
					{
						if(!(gmtUmlValidation = GmtUmlSelectNickname (gmtUmlNewUser.name, gmtUmlNewUser.nickname, &gmtUmlConfigurationOptions)))
						{
							if(!(gmtUmlValidation = GmtUmlCreatePassword (gmtUmlNewUser.password, gmtUmlLanguage, &gmtUmlConfigurationOptions)))
							{
								memset(&gmtUmlUserData, 0x00, sizeof (gmtUmlUserDataType));

								if (!(gmtUmlValidation = GmtUmlAddUser (&gmtUmlConfigurationOptions, &gmtUmlNewUser)))
                {
                  printf ("%s %s %s.\n", GmtUmlGetCliUserInterface (gmtUmlAccountCreatedSuccessfully, gmtUmlLanguage), GmtUmlGetCliUserInterface (gmtUmlNewUserNicknameIs, gmtUmlLanguage), gmtUmlNewUser.nickname);
                }
                else
                {
                  printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
                  exit (gmtUmlValidation);
                }

							}
              else
              {
              	#ifdef _DEBUG_
              	printf ("Invalid new user\'s password.\n");
              	#endif

                printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
                exit (gmtUmlValidation);
              }
						}
            else
            {
            	#ifdef _DEBUG_
              printf ("Could not create new nickname.\n");
              #endif

              printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
              exit (gmtUmlValidation);
            } 
				  }
          else
          {
          	#ifdef _DEBUG_
            printf ("Could not validate new user\'s information.\n");
            #endif

            printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
            exit (gmtUmlValidation);
          }
			  }
			  else
			  {
			  	#ifdef _DEBUG_
          printf ("The new user\'s profile is lower than yours.\n");
          #endif
          printf ("ERROR (#%i): %s.\n", gmtUmlErrorPermissionDenied, GmtUmlGetCliErrorMessage (gmtUmlErrorPermissionDenied, gmtUmlLanguage));
          exit (gmtUmlErrorPermissionDenied);
			  }
			}
      else
      {
      	#ifdef _DEBUG_
        printf ("Password %s.\n", gmtUmlEncryptedPassword);
        #endif

        printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
        exit (gmtUmlValidation);
      }

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
			memset (gmtUmlConfirmUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
			memset (gmtUmlEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlConfirmEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlProfile, 0x00, GMT_UML_MAX_PROFILE_LENGTH + 1);
			break;

			case 'i':
	#ifdef _DEBUG_
			printf ("INVITE USER.\n");
	#endif
			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);			
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlUsername, gmtUmlErrorInvalidUsername);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentConfirmUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlConfirmUsername, gmtUmlErrorUsernamesDontMatch);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlEmail, gmtUmlErrorInvalidEmail);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentConfirmEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlConfirmEmail, gmtUmlErrorEmailsDontMatch);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentProfile:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_PROFILE_LENGTH, GMT_UML_PROFILE_VALID_CHARS, gmtUmlProfile, gmtUmlErrorInvalidProfile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;
			}

			if (gmtUmlArgumentsSet != 5)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			memset (&gmtUmlNewUser, 0x00, sizeof (gmtUmlUserData));

			gmtUmlNewUser.id = strtoull (gmtUmlUid, &validation, 10);

			if (*validation != '\0')
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
			  exit (gmtUmlErrorInvalidArgument);
			}

      gmtUmlNewUser.profile = strtoull (gmtUmlProfile, &validation, 10);

      if (*validation != '\0')
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
			  exit (gmtUmlErrorInvalidArgument);
			}

      strcpy (gmtUmlNewUser.email, gmtUmlEmail);
      strcpy (gmtUmlNewUser.emailConfirmation, gmtUmlConfirmEmail);
      strcpy (gmtUmlNewUser.name, gmtUmlUsername);
      strcpy (gmtUmlNewUser.nameConfirmation, gmtUmlUsername);
      memset (gmtUmlNewUser.password, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);
      memset (gmtUmlNewUser.passwordConfirmation, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);

			if (GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions))
      {
        printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidConfigFile, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidConfigFile, gmtUmlLanguage));
			  exit (gmtUmlErrorInvalidConfigFile);
      }
			/* Ask user's credentials */
      GmtUmlCliAskUserCredentials (gmtUmlNickname, gmtUmlPassword, gmtUmlLanguage);

      /* Add user */
	  	if (!(gmtUmlValidation = GmtUmlLogin (gmtUmlNickname, gmtUmlPassword, &gmtUmlConfigurationOptions, &gmtUmlUserData)))
			{
				if(gmtUmlUserData.profile <= gmtUmlNewUser.profile) /* One user can only add other with same profile or less */
				{
					if(!(gmtUmlValidation = GmtUmlValidateUserInformation (&gmtUmlNewUser)))
					{
						if(!(gmtUmlValidation = GmtUmlSelectNickname (gmtUmlNewUser.name, gmtUmlNewUser.nickname, &gmtUmlConfigurationOptions)))
						{
							memset(&gmtUmlUserData, 0x00, sizeof (gmtUmlUserDataType));

							if (!(gmtUmlValidation = GmtUmlAddUser (&gmtUmlConfigurationOptions, &gmtUmlNewUser)))
              {
                printf ("%s %s %s.\n", GmtUmlGetCliUserInterface (gmtUmlUserInvitedSuccessfully, gmtUmlLanguage), GmtUmlGetCliUserInterface (gmtUmlNewUserNicknameIs, gmtUmlLanguage), gmtUmlNewUser.nickname);
              }
              else
              {
                printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
                exit (gmtUmlValidation);
              }
						}
            else
            {
            	#ifdef _DEBUG_
              printf ("Could not create new nickname.\n");
              #endif

              printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
              exit (gmtUmlValidation);
            } 
				  }
          else
          {
          	#ifdef _DEBUG_
            printf ("Could not validate new user\'s information.\n");
            #endif

            printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
            exit (gmtUmlValidation);
          }
			  }
			  else
			  {
			  	#ifdef _DEBUG_
          printf ("The new user\'s profile is lower than yours.\n");
          #endif
          printf ("ERROR (#%i): %s.\n", gmtUmlErrorPermissionDenied, GmtUmlGetCliErrorMessage (gmtUmlErrorPermissionDenied, gmtUmlLanguage));
          exit (gmtUmlErrorPermissionDenied);
			  }
			}
      else
      {
      	#ifdef _DEBUG_
        printf ("Password %s.\n", gmtUmlEncryptedPassword);
        #endif

        printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
        exit (gmtUmlValidation);
      }

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
			memset (gmtUmlConfirmUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
			memset (gmtUmlEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlConfirmEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlProfile, 0x00, GMT_UML_MAX_PROFILE_LENGTH + 1);
			break;

			case 't':
	#ifdef _DEBUG_
			printf ("ACCEPT INVITE.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1,  GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1,  GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;
			}

			if (gmtUmlArgumentsSet != 1)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			#ifdef _DEBUG_
			printf ("Language: %s.\n", gmtUmlLanguageName);
			#endif

			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			strcpy (gmtUmlPassword, getpass (GmtUmlGetCliUserInterface (gmtUmlInformYourPassword, gmtUmlLanguage)));

		  if (GmtUmlCheckStringField (gmtUmlPassword, GMT_UML_PASSWORD_VALID_CHARS, GMT_UML_MIN_PASSWORD_LENGTH, GMT_UML_MAX_PASSWORD_LENGTH))
	  	{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidPassword, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidPassword, gmtUmlLanguage));
				exit(gmtUmlErrorInvalidPassword);
			}

			/* Checking credentials */

			#ifdef _DEBUG_
			printf ("Reading user\'s file...\n");
			#endif

			if ((gmtUmlValidation = GmtUmlGetUsers (&gmtUmlUsersList, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			gmtUmlCurrentUser = gmtUmlUsersList;

			while (gmtUmlCurrentUser != NULL)
			{
				if (strcmp (gmtUmlCurrentUser->nickname, gmtUmlNickname) == 0)
				{
					found = True;
					break;
				}
				gmtUmlCurrentUser = gmtUmlCurrentUser->next;
			}

			if (!found)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvitationNotFound, GmtUmlGetCliErrorMessage (gmtUmlErrorInvitationNotFound, gmtUmlLanguage));
				exit(gmtUmlErrorInvitationNotFound);
			}

			gmtUmlUserData.id = gmtUmlCurrentUser->id;
			strcpy (gmtUmlUserData.email, gmtUmlCurrentUser->email);
			strcpy (gmtUmlUserData.emailConfirmation, gmtUmlCurrentUser->email);
			strcpy (gmtUmlUserData.name, gmtUmlCurrentUser->name);
			strcpy (gmtUmlUserData.nameConfirmation, gmtUmlCurrentUser->name);

			GmtUmlDestroyUserDataList (gmtUmlUsersList);

			strcpy (gmtUmlNewPassword, getpass (GmtUmlGetCliUserInterface (gmtUmlInformNewPassword, gmtUmlLanguage)));
			strcpy (gmtUmlNewPasswordConfirmation, getpass (GmtUmlGetCliUserInterface (gmtUmlConfirmNewPassword, gmtUmlLanguage)));

			if (strcmp (gmtUmlNewPassword, gmtUmlNewPasswordConfirmation))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorPasswordsDontMatch, GmtUmlGetCliErrorMessage (gmtUmlErrorPasswordsDontMatch, gmtUmlLanguage));
				exit(gmtUmlErrorPasswordsDontMatch);
			}

			#ifdef _DEBUG_
			printf ("Passwords match...\n");
			#endif

			if ((gmtUmlValidation = GmtUmlEncodePasswordWithSpecificAlgorithm (gmtUmlNewPassword, gmtUmlConfigurationOptions.gmtUmlCryptAlgorithm, gmtUmlEncryptedPassword)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			strcpy (gmtUmlUserData.password, gmtUmlEncryptedPassword);
			strcpy (gmtUmlUserData.passwordConfirmation, gmtUmlEncryptedPassword);

			if ((gmtUmlValidation = GmtUmlAcceptInvite (&gmtUmlConfigurationOptions, gmtUmlEncryptedPassword, &gmtUmlUserData)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			printf ("%s\n", GmtUmlGetCliUserInterface (gmtUmlWelcome, gmtUmlLanguage));

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlPassword, 0x00, GMT_UML_MAX_PASSWORD_LENGTH + 1);
			memset (gmtUmlNewPassword, 0x00, GMT_UML_MAX_PASSWORD_LENGTH + 1);
			memset (gmtUmlNewPasswordConfirmation, 0x00, GMT_UML_MAX_PASSWORD_LENGTH + 1);
			break;

			case 'j':
	#ifdef _DEBUG_
			printf ("REJECT INVITE.\n");
	#endif
			gmtUmlArgumentsSet = 0;

			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1,  GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1,  GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;
				}
				optind++;
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			GmtUmlGetLanguageIndex (gmtUmlLanguageName);
			
			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf (" > While reading %s...\n", gmtUmlConfiguration);
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			strcpy (gmtUmlUserData.password, getpass (GmtUmlGetCliUserInterface (gmtUmlInformYourPassword, gmtUmlLanguage)));
			strcpy (gmtUmlUserData.passwordConfirmation, gmtUmlUserData.password);

			#ifdef _DEBUG_
			 printf ("Nickname: %s\n", gmtUmlNickname);
			#endif
			
			if ((gmtUmlValidation = GmtUmlGetUsers (&gmtUmlUsersList, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
			  exit (gmtUmlValidation);
			}

			#ifdef _DEBUG_
			printf ("Users lists loaded...\n");
			#endif

			gmtUmlCurrentUser = gmtUmlUsersList;

			while (gmtUmlCurrentUser != NULL)
			{
				if ((strcmp (gmtUmlCurrentUser->nickname, gmtUmlNickname) == 0))
				{
					found = True;
					break;
				}
				gmtUmlCurrentUser = gmtUmlCurrentUser->next;
			}

			if (!found)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvitationNotFound, GmtUmlGetCliErrorMessage (gmtUmlErrorInvitationNotFound, gmtUmlLanguage));
			  exit (gmtUmlErrorInvitationNotFound);
			}

			gmtUmlUserData.id = gmtUmlCurrentUser->id;
			strcpy (gmtUmlUserData.name, gmtUmlCurrentUser->name);
			strcpy (gmtUmlUserData.email, gmtUmlCurrentUser->email);

			GmtUmlDestroyUserDataList (gmtUmlUsersList);

			if ((gmtUmlValidation = GmtUmlRejectInvite (&gmtUmlConfigurationOptions, &gmtUmlUserData, gmtUmlPassword)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit (gmtUmlValidation);
			}

			printf ("%s.\n", GmtUmlGetCliUserInterface (gmtUmlInvitationRejected, gmtUmlLanguage));

			memset (gmtUmlPassword, 0x00, GMT_UML_MAX_PASSWORD_LENGTH + 1);
			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			break;

			case 'n':
	#ifdef _DEBUG_
			printf ("REQUEST REGISTRATION.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);	
					}
					break;

					case gmtUmlArgumentUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlUsername, gmtUmlErrorInvalidUsername);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentConfirmUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlConfirmUsername, gmtUmlErrorUsernamesDontMatch);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlEmail, gmtUmlErrorInvalidEmail);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentConfirmEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlConfirmEmail, gmtUmlErrorEmailsDontMatch);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentFriendEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlFriendEmail, gmtUmlErrorInvalidFriendEmail);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;
			}

			if (gmtUmlArgumentsSet != 5)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			#ifdef _DEBUG_
			printf ("Language: %s.\n", gmtUmlLanguageName);
			#endif

			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			#ifdef _DEBUG_
			printf ("Configuration options: ok.\n");
			#endif

			gmtUmlUserData.profile = 4;
			strcpy (gmtUmlUserData.name, gmtUmlUsername);
			strcpy (gmtUmlUserData.nameConfirmation, gmtUmlConfirmUsername);
			strcpy (gmtUmlUserData.email, gmtUmlEmail);
			strcpy (gmtUmlUserData.emailConfirmation, gmtUmlConfirmEmail);

			if ((gmtUmlValidation = GmtUmlSelectNickname (gmtUmlUserData.name, gmtUmlUserData.nickname, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			#ifdef _DEBUG_
			printf ("Nickname: %s.\n", gmtUmlUserData.nickname);
			#endif

			if((gmtUmlValidation = GmtUmlCreatePassword (gmtUmlEncryptedPassword, GmtUmlGetLanguageIndex (gmtUmlLanguageName), &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			#ifdef _DEBUG_
			printf ("Password: ok.\n");
			#endif

			strcpy (gmtUmlUserData.password, gmtUmlEncryptedPassword);
			strcpy (gmtUmlUserData.passwordConfirmation, gmtUmlEncryptedPassword);

			if((gmtUmlValidation = GmtUmlRequestRegistration (&gmtUmlConfigurationOptions, gmtUmlFriendEmail, &gmtUmlUserData)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			#ifdef _DEBUG_
			printf ("Request registered.\n");
			#endif

			printf ("%s %s %s\n", GmtUmlGetCliUserInterface (gmtUmlRequestRegistered, gmtUmlLanguage), GmtUmlGetCliUserInterface (gmtUmlNewUserNicknameIs, gmtUmlLanguage), gmtUmlUserData.nickname);

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
			memset (gmtUmlConfirmUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
			memset (gmtUmlEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlConfirmEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlProfile, 0x00, GMT_UML_MAX_PROFILE_LENGTH + 1);
			memset (gmtUmlUserData.password, 0x00, GMT_UML_MAX_PASSWORD_LENGTH+1);
			memset (gmtUmlUserData.passwordConfirmation, 0x00, GMT_UML_MAX_PASSWORD_LENGTH+1);
			memset (gmtUmlEncryptedPassword, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);
			break;

			case 'q':
	#ifdef _DEBUG_
			printf ("GET PENDING REGISTRATION REQUESTS PER USER.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:

					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);		
					}
					break;

					case gmtUmlArgumentConfiguration:

					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:

					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					gmtUmlArgumentsSet++;
					break;
				}
				optind++;

			}
			if (gmtUmlArgumentsSet != 1)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			if ((gmtUmlValidation = GmtUmlGetPendingRegistrationRequestsPerUser (&gmtUmlConfigurationOptions, gmtUmlNickname, &gmtUmlUsersList)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			printf ("%s %s:\n\n", GmtUmlGetCliUserInterface (gmtUmlUserPendingRegistrationRequests, gmtUmlLanguage), gmtUmlNickname);
			printf ("    %-20s%-40s%-40s\n", "NICKNAME", "NAME", "EMAIL");

			gmtUmlCurrentUser = gmtUmlUsersList;
			index = 0;

			while (gmtUmlCurrentUser != NULL)
			{
				printf("%2i. %-20s%-40s%-40s\n", ++index, gmtUmlCurrentUser->nickname, gmtUmlCurrentUser->name, gmtUmlCurrentUser->email);
				gmtUmlCurrentUser = gmtUmlCurrentUser->next;
			}

			printf ("\n %s: %i.\n", GmtUmlGetCliUserInterface (gmtUmlTotal, gmtUmlLanguage), index);

			GmtUmlDestroyUserDataList (gmtUmlUsersList);

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			break;

			case 'Q':
	#ifdef _DEBUG_
			printf ("GET PENDING REGISTRATION REQUESTS.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;
				}
				optind++;
			}
			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			if ((gmtUmlValidation = GmtUmlGetPendingRegistrationRequests (&gmtUmlConfigurationOptions, &gmtUmlUsersList)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			printf ("%s:\n\n", GmtUmlGetCliUserInterface (gmtUmlUserPendingRegistrationRequests, gmtUmlLanguage));
			printf ("    %-20s%-40s%-40s\n", "NICKNAME", "NAME", "EMAIL");

			gmtUmlCurrentUser = gmtUmlUsersList;
			index = 0;

			while (gmtUmlCurrentUser != NULL)
			{
				printf("%2i. %-20s%-40s%-40s\n", ++index, gmtUmlCurrentUser->nickname, gmtUmlCurrentUser->name, gmtUmlCurrentUser->email);
				gmtUmlCurrentUser = gmtUmlCurrentUser->next;
			}

			printf ("\n %s: %i.\n", GmtUmlGetCliUserInterface (gmtUmlTotal, gmtUmlLanguage), index);

			GmtUmlDestroyUserDataList (gmtUmlUsersList);

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);			
			break;

			case 'v':
	#ifdef _DEBUG_
			printf ("APPROVE REGISTRATION REQUEST.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNewUserNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlUsername, gmtUmlErrorInvalidUsername);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;

			}

			if (gmtUmlArgumentsSet != 2)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			if ((gmtUmlValidation = GmtUmlCliAskUserCredentials (gmtUmlNickname, gmtUmlPassword, gmtUmlLanguage)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

      /* Login */
	  	if ((gmtUmlValidation = GmtUmlLogin (gmtUmlNickname, gmtUmlPassword, &gmtUmlConfigurationOptions, &gmtUmlUserData)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			if ((gmtUmlValidation = GmtUmlApproveRegistrationRequest (&gmtUmlConfigurationOptions, gmtUmlNickname, gmtUmlNewUserNickname)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			printf ("%s\n", GmtUmlGetCliUserInterface (gmtUmlRegistrationRequestApproved, gmtUmlLanguage));

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			break;

			case 'd':
	#ifdef _DEBUG_
			printf ("DISAPPROVE REGISTRATION REQUEST.\n");
	#endif
			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNewUserNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlUsername, gmtUmlErrorInvalidUsername);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;

			}

			if (gmtUmlArgumentsSet != 2)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			if ((gmtUmlValidation = GmtUmlCliAskUserCredentials (gmtUmlNickname, gmtUmlPassword, gmtUmlLanguage)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

      /* Login */
	  	if ((gmtUmlValidation = GmtUmlLogin (gmtUmlNickname, gmtUmlPassword, &gmtUmlConfigurationOptions, &gmtUmlUserData)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}
			
			if ((gmtUmlValidation = GmtUmlDisapproveRegistrationRequest (&gmtUmlConfigurationOptions, gmtUmlNickname, gmtUmlNewUserNickname)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			printf ("%s\n", GmtUmlGetCliUserInterface (gmtUmlRegistrationRequestDisapproved, gmtUmlLanguage));

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			break;

			case 'U':
	#ifdef _DEBUG_
			printf ("SHOW UNLOCKING REQUESTS.\n");
	#endif
			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;
				}
				optind++;

			}
			if (gmtUmlArgumentsSet != 1)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			break;

			case 'l':
	#ifdef _DEBUG_
			printf ("LOCK USER ACCOUNT.\n");
	#endif
			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;
				}
				optind++;
			}

			if (gmtUmlArgumentsSet != 1)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			if (strlen(gmtUmlNickname) == 0)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidNickname, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidNickname, gmtUmlLanguage));
				exit (gmtUmlErrorInvalidNickname);
			}

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			break;

			case 'u':
	#ifdef _DEBUG_
			printf ("UNLOCK USER ACCOUNT.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);			
					}
					break;

					case gmtUmlArgumentConfiguration:			
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;
				}
				optind++;
			}
			if (gmtUmlArgumentsSet != 1)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			if (strlen(gmtUmlNickname) == 0)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidNickname, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidNickname, gmtUmlLanguage));
				exit (gmtUmlErrorInvalidNickname);
			}

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			break;

			case 'p':
	#ifdef _DEBUG_
			printf ("CHANGE USER PASSWORD.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);

			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			if ((gmtUmlValidation = GmtUmlCliAskUserCredentials (gmtUmlNickname, gmtUmlPassword, gmtUmlLanguage)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

      /* Login */
	  	if ((gmtUmlValidation = GmtUmlLogin (gmtUmlNickname, gmtUmlPassword, &gmtUmlConfigurationOptions, &gmtUmlUserData)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			if (gmtUmlArgumentsSet == 0)
			{
				#ifdef _DEBUG_
				printf ("Trying to change your own password...\n");
				#endif

				strcpy (gmtUmlNewPassword, getpass (GmtUmlGetCliUserInterface (gmtUmlInformNewPassword, gmtUmlLanguage)));
				strcpy (gmtUmlNewPasswordConfirmation, getpass (GmtUmlGetCliUserInterface (gmtUmlConfirmNewPassword, gmtUmlLanguage)));

				if ((gmtUmlValidation = GmtUmlChangeUserPassword (&gmtUmlConfigurationOptions, NULL, gmtUmlUserData.nickname, gmtUmlUserData.password, gmtUmlNewPassword, gmtUmlNewPasswordConfirmation)))
				{
					memset (gmtUmlNewPassword, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);
					memset (gmtUmlNewPasswordConfirmation, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);
					printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
			  	exit (gmtUmlValidation);
				}
			}
			else
			{
				#ifdef _DEBUG_
				printf ("Trying to change someone else\'s password...\n");
				#endif

				if (gmtUmlUserData.profile != 2)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorPermissionDenied, GmtUmlGetCliErrorMessage (gmtUmlErrorPermissionDenied, gmtUmlLanguage));
					exit(gmtUmlErrorPermissionDenied);
				}

				strcpy (gmtUmlNewPassword, getpass (GmtUmlGetCliUserInterface (gmtUmlInformNewPassword, gmtUmlLanguage)));
				strcpy (gmtUmlNewPasswordConfirmation, getpass (GmtUmlGetCliUserInterface (gmtUmlConfirmNewPassword, gmtUmlLanguage)));

				if ((gmtUmlValidation = GmtUmlChangeUserPassword (&gmtUmlConfigurationOptions, gmtUmlUserData.nickname, gmtUmlNickname, NULL, gmtUmlNewPassword, gmtUmlNewPasswordConfirmation)))
				{
					memset (gmtUmlNewPassword, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);
					memset (gmtUmlNewPasswordConfirmation, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);
					printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
			  	exit (gmtUmlValidation);
				}
			}

			printf ("%s\n", GmtUmlGetCliUserInterface(gmtUmlUserPasswordChanged, gmtUmlLanguage));

			memset (gmtUmlNewPassword, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);
			memset (gmtUmlNewPasswordConfirmation, 0x00, GMT_UML_MAX_ENCRYPTED_PASSWORD_LENGTH+1);
			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			break;

			case 'r':
	#ifdef _DEBUG_
			printf ("RESET USER PASSWORD.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;
				}
				optind++;
			}

			if (gmtUmlArgumentsSet != 1)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			if (strlen(gmtUmlNickname) == 0)
			{
				printf ("ERROR (#%i): %s.\n",gmtUmlErrorInvalidNickname, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidNickname, gmtUmlLanguage));
				exit (gmtUmlErrorInvalidNickname);
			}

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			break;

			case 'm':
	#ifdef _DEBUG_
			printf ("CHANGE USER NAME.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);							
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlUsername, gmtUmlErrorInvalidUsername);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentConfirmUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlConfirmUsername, gmtUmlErrorUsernamesDontMatch);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;
			}

			if (gmtUmlArgumentsSet != 3)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			if (strlen(gmtUmlNickname) == 0)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidNickname, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidNickname, gmtUmlLanguage));
				exit (gmtUmlErrorInvalidNickname);
			}

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
			memset (gmtUmlConfirmUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);
			break;

			case 'e':
	#ifdef _DEBUG_
			printf ("CHANGE USER EMAIL.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);							
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlEmail, gmtUmlErrorInvalidEmail);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentConfirmEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlConfirmEmail, gmtUmlErrorEmailsDontMatch);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;
			}

			if (gmtUmlArgumentsSet != 3)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlNickname) == 0)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidNickname, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidNickname, gmtUmlLanguage));
				exit (gmtUmlErrorInvalidNickname);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlConfirmEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			break;

			case 'c':
	#ifdef _DEBUG_
			printf ("CONFIRM EMAIL CHANGE.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentKey:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_KEY_LENGTH, GMT_UML_KEY_VALID_CHARS, gmtUmlKey, gmtUmlErrorInvalidKey);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;
				}
				optind++;

			}

			if (gmtUmlArgumentsSet != 2)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlNickname) == 0)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidNickname, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidNickname, gmtUmlLanguage));
				exit (gmtUmlErrorInvalidNickname);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlKey, 0x00, GMT_UML_MAX_KEY_LENGTH+1);
			break;

			case 'g':
	#ifdef _DEBUG_
			printf ("CHANGE USER PROFILE.\n");
	#endif

			gmtUmlArgumentsSet = 0;
			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentNickname:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NICKNAME_LENGTH, GMT_UML_NICKNAME_VALID_CHARS, gmtUmlNickname, gmtUmlErrorInvalidNickname);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

					case gmtUmlArgumentProfile:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_PROFILE_LENGTH, GMT_UML_PROFILE_VALID_CHARS, gmtUmlProfile, gmtUmlErrorInvalidProfile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}

					gmtUmlArgumentsSet++;
					break;

				}
				optind++;

			}

			if (gmtUmlArgumentsSet != 3)
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlErrorTooFewArguments, GmtUmlGetCliErrorMessage (gmtUmlErrorTooFewArguments, gmtUmlLanguage));
				exit(gmtUmlErrorTooFewArguments);
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlNickname, 0x00, GMT_UML_MAX_NICKNAME_LENGTH + 1);
			memset (gmtUmlProfile, 0x00, GMT_UML_MAX_PROFILE_LENGTH + 1);
			break;

			case 's':
	#ifdef _DEBUG_
			printf ("SHOW USERS.\n");
	#endif

			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;
				}
				optind++;
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			#ifdef _DEBUG_
			printf ("Language: %s\n", gmtUmlLanguageName);
			#endif

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			#ifdef _DEBUG_
			printf ("Config file: %s\n", gmtUmlConfiguration);
			#endif

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);
			
			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf (" > While reading %s...\n", gmtUmlConfiguration);
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			if ((gmtUmlValidation = GmtUmlGetUsers (&gmtUmlUsersList, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
			  exit (gmtUmlValidation);
			}

			printf("%s\n\n", GmtUmlGetCliUserInterface (gmtUmlCliAllUsers, gmtUmlLanguage));
			printf ("    %-20s%-40s%-40s%-8s\n", "NICKNAME", "NAME", "EMAIL", "PROFILE");

			gmtUmlCurrentUser = gmtUmlUsersList;
			index = 1;

			while (gmtUmlCurrentUser != NULL)
			{
				printf("%2i. %-20s%-40s%-40s%-2llu\n", index++, gmtUmlCurrentUser->nickname, gmtUmlCurrentUser->name, gmtUmlCurrentUser->email, gmtUmlCurrentUser->profile);
				gmtUmlCurrentUser = gmtUmlCurrentUser->next;
			}

			if (gmtUmlUsersList != NULL)
				GmtUmlDestroyUserDataList (gmtUmlUsersList);

			printf ("\n %i %s.\n", index, GmtUmlGetCliUserInterface (gmtUmlResults, gmtUmlLanguage));

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);			
			memset (gmtUmlEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlProfile, 0x00, GMT_UML_MAX_PROFILE_LENGTH + 1);
			break;

			case 'S':
	#ifdef _DEBUG_
			printf ("SEARCH USER.\n");
	#endif

			while (optind < argc)
			{
				gmtUmlArguments = argv [optind];
				gmtUmlArgumentIndex = getsubopt (&gmtUmlArguments, gmtUmlArgumentNames, &gmtUmlArgumentValue);

				if(!gmtUmlArgumentValue)
				{
					printf ("ERROR (#%i): %s.\n",gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
					exit(gmtUmlErrorInvalidArgument);
				}

				switch (gmtUmlArgumentIndex)
				{
					case gmtUmlArgumentLanguage:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_LANGUAGE_LENGTH, GMT_UML_LANGUAGE_VALID_CHARS, gmtUmlLanguageName, gmtUmlErrorInvalidLanguage);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentConfiguration:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_FILE_NAME_LENGTH, GMT_UML_FILE_NAME_VALID_CHARS, gmtUmlConfiguration, gmtUmlErrorInvalidConfigFile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentUsername:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_NAME_LENGTH, GMT_UML_NAME_VALID_CHARS, gmtUmlUsername, gmtUmlErrorInvalidUsername);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentEmail:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_EMAIL_LENGTH, GMT_UML_EMAIL_VALID_CHARS, gmtUmlEmail, gmtUmlErrorInvalidEmail);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;

					case gmtUmlArgumentProfile:
					gmtUmlValidation = GmtUmlValidateArgument(gmtUmlArguments, gmtUmlArgumentValue, 
						1, GMT_UML_MAX_PROFILE_LENGTH, GMT_UML_PROFILE_VALID_CHARS, gmtUmlProfile, gmtUmlErrorInvalidProfile);

					if (gmtUmlValidation)
					{
						printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
						exit(gmtUmlValidation);
					}
					break;
				}
				optind++;
			}

			if (strlen(gmtUmlLanguageName) == 0)
				strcpy(gmtUmlLanguageName, GMT_UML_DEFAULT_LANGUAGE);

			#ifdef _DEBUG_
			printf ("Language: %s\n", gmtUmlLanguageName);
			#endif

			if (strlen(gmtUmlConfiguration) == 0)
				strcpy(gmtUmlConfiguration, GMT_UML_DEFAULT_CONFIG_FILE);

			#ifdef _DEBUG_
			printf ("Config file: %s\n", gmtUmlConfiguration);
			#endif

			gmtUmlLanguage = GmtUmlGetLanguageIndex (gmtUmlLanguageName);
			
			if ((gmtUmlValidation = GmtUmlGetConfigurationOptionsValues (gmtUmlConfiguration, &gmtUmlConfigurationOptions)))
			{
				printf (" > While reading %s...\n", gmtUmlConfiguration);
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
				exit(gmtUmlValidation);
			}

			if ((gmtUmlValidation = GmtUmlGetUsers (&gmtUmlUsersList, &gmtUmlConfigurationOptions)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
			  exit (gmtUmlValidation);
			}

			if (strlen (gmtUmlProfile) > 0)
			{
				gmtUmlUserProfile = strtoull (gmtUmlProfile, &validation, 10);

      	if (*validation != '\0')
				{
					printf ("ERROR (#%i): %s.\n", gmtUmlErrorInvalidArgument, GmtUmlGetCliErrorMessage (gmtUmlErrorInvalidArgument, gmtUmlLanguage));
				  exit (gmtUmlErrorInvalidArgument);
				}
			}
			else
			{
				gmtUmlUserProfile = 0;
			}

			#ifdef _DEBUG_
			printf ("Profile: %llu\n", gmtUmlUserProfile);
			#endif

			if ((gmtUmlValidation = GmtUmlSearchUsers (&gmtUmlConfigurationOptions, gmtUmlUsername, gmtUmlEmail, gmtUmlUserProfile, &gmtUmlUsersList)))
			{
				printf ("ERROR (#%i): %s.\n", gmtUmlValidation, GmtUmlGetCliErrorMessage (gmtUmlValidation, gmtUmlLanguage));
			  exit (gmtUmlValidation);
			}

			printf("%s\n\n", GmtUmlGetCliUserInterface (gmtUmlCliSearchResults, gmtUmlLanguage));
			printf ("    %-20s%-34s%-40s%-8s\n", "NICKNAME", "NAME", "EMAIL", "PROFILE");

			gmtUmlCurrentUser = gmtUmlUsersList;
			index = 0;

			while (gmtUmlCurrentUser != NULL)
			{
				printf("%2i. %-20s%-40s%-40s%-2llu\n", ++index, gmtUmlCurrentUser->nickname, gmtUmlCurrentUser->name, gmtUmlCurrentUser->email, gmtUmlCurrentUser->profile);
				gmtUmlCurrentUser = gmtUmlCurrentUser->next;
			}

			printf ("\n %s: %i.\n", GmtUmlGetCliUserInterface (gmtUmlTotal, gmtUmlLanguage), index);

			if (gmtUmlUsersList != NULL)
				GmtUmlDestroyUserDataList (gmtUmlUsersList);

			memset (gmtUmlConfiguration, 0x00, GMT_UML_MAX_FILE_NAME_LENGTH + 1);
			memset (gmtUmlLanguageName, 0x00, GMT_UML_MAX_LANGUAGE_LENGTH + 1);
			memset (gmtUmlUsername, 0x00, GMT_UML_MAX_NAME_LENGTH + 1);			
			memset (gmtUmlEmail, 0x00, GMT_UML_MAX_EMAIL_LENGTH + 1);
			memset (gmtUmlProfile, 0x00, GMT_UML_MAX_PROFILE_LENGTH + 1);
			break;

			default:
			printf("Invalid option. Type -h or --help for help.\n");
			exit(gmtUmlErrorOptionNotSupported);
		}
	}

	return 0;
}
