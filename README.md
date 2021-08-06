# User Management Library

This is an user management library written in C. It can be used in command line or on the Web through CGI.

# Help

To display this information in other language, you can use `gmtUml -h language=value`.

      Short   Long            Action
      
      -h      --help          Displays the help.
      -N      --Ncurses       Run Ncurses interface. (not avaiable)
      -C      --configure     Create user's files.
      -a      --add           Add user.
      -i      --invite        Invite user.
      -t      --accept        Accept invitation.
      -j      --reject        Reject invitation.
      -n      --new           Request registration.
      -q      --request       Get pending registration requests per user.
      -Q      --Request       Get pending registration requests.
      -v      --approve       Approve registration request.
      -d      --disapprove    Disapprove registration request.
      -U      --Unlocking     Get unlocking requests.
      -l      --lock          Lock user account.
      -u      --unlock        Unlock user account.
      -p      --password      Change user password.
      -r      --reset         Reset user password.
      -m      --modify        Change user name.
      -e      --edit          Change user email.
      -c      --confirm       Confirm email change.
      -g      --group         Change user profile.
      -s      --show          Get user informations.
      -S      --Search        Search user.
 
 The help file is avaiable in:
 
 ```
      Portuguese - Brazil
      English
 ```
 
 # Make
 
 First, edit the following file, replacing the original directory with yours:
 
 ```
 ~uml/Sources/C/Makefile
 ```
 
 Then, execute:
 
 ```
 make all
 ```

# License

MIT
