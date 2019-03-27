
# Project 1: Shell Project Part 2 

* **Author**: *Matt Masarik*
* **Class**:  *CS453/552 [Operating Systems] Section 002*
*Note - handing in 2 days late for 20% off.*



## Overview
This project is a simple shell implementation called `mydash` (**my d**ead **a**gain **sh**ell), which is
based on the **b**orne **a**gain **sh**ell, or `bash`. This repository contains a `Makefile` along with C source
files to build and run the `mydash` shell.  



> #### Extended Summary
> The functionality of this simple shell is achieved by providing a few 'built-in' commands that we have implemented
> ourselves (`cd`,`exit`,`jobs`), some features/commands that are partially self-implemented (e.g., command line
> editting and the `history` command which use/build on top of the `readline/history` library, and lastly
> if that command is not included in any of those, it is run by `fork`-ing and passing off to `exec`.  




## Manifest
```
.
├── doxygen-config
├── Makefile
├── mydash-src
│   ├── builtInFuncs.c              # built-in functions we implemented
│   ├── builtInFuncs.h
│   ├── error.c
│   ├── Job.c                       # Job methods
│   ├── Job.h                       # Job struct and typedef
│   ├── JobList.c                   # JobList methods
│   ├── JobList.h                   # JobList typdef
│   ├── Makefile
│   ├── mydash.c                    # main project routine
│   ├── mydash.h                    # main program header file
│   ├── tokenFuncs.c                # functions regarding parsing/tokenizing
│   ├── tokenFuncs.h
│   ├── utilityFuncs.c              # program flow / run functions, helper functions
│   └── utilityFuncs.h
├── README.md
└── valgrind.supp
```


## Building the project

The `mydash` shell can be built by running `make` at the command line in 
the `p1` directory:

```bash
$ make
```

a successful build will leave an executable file called `mydash`
in the top-level project directory, `p1`.  You can then run `mydash`
at the command line:

```bash
$ ./mydash
```

These `make` targets are also available for more functionality:
* `make mydash-project` - builds the `mydash` executable.
"[$USER@${HOSTNAME%%.*} msh]\$ "* `make dox` - generates project documentation from `doxygen`.
* `make all` - default target, identical to running `make` alone.  Builds
               the `mydash` executable as well as generates `doxygen` documentation.
* `make run` - builds `all`, then runs the `smash` executable.
* `make clean` - removes the executable as well as all intermediate files generated in the build.
* `make valgrind` - builds `all`, then runs `valgrind` with the `--leak-check` flag.
* `make konq-dox` - runs `doxygen` then opens the main file in `konqueror` web browser.



## Features and usage
###### Prompt
* **Default prompt** - If the user has not set the global parameter `DASH_PROMPT`, then the shell prompt will default to:
  `[msh]$ `.  This is a short-hand/acronym and further play on Linux shell names:  `msh` = "**m**att's mydash **sh**ell".
* **Custom prompt** - If the user has set/exported the shell environment parameter `DASH_PROMPT`, it's value will be used.
  I have the following setting in my `.bashrc`:  `DASH_PROMPT="[$USER@${HOSTNAME%%.*} msh]\$ ".`  In this case the prompt
  contains the username and *basename* of the host machine, as well as including `msh`. This last part of the prompt is added 
  solely so that you do not forget you are in the `mydash` shell since the prompt is very similar (minus the current sub-dir
  level) to that on the `onyx` cluster.  When I log into `onyxnode54`, my prompt appears like this: 
  `[mattmasarik@onyxnode54 msh]$`.


###### Version
By calling `mydash` with a single command line argument `-v`, with display a version number for the project.  The
version number in this case is the first 6 digits of the `git` SHA.
  ```bash
  $ ./mydash -v
  mydash vf7f10f
  $
  ```
    

###### Built-in Commands
* **cd** - change directory.  Without any arguments defaults to the users home directory.
     * ```bash
          Usage:   [msh]$ cd [<directory-path>]   # <directory-path> is optional
          
          Ex. 1:   [msh]$ cd                      # change directory: /home/$USER, default
                   /home/JohnSmith                # example output for $USER == JohnSmith
          Ex. 2:   [msh]$ cd /path/to/some/dir    # change directory: /path/to/some/dir
                   /path/to/some/dir              
       ```
* **exit** - cleans up, then invokes the system call `exit()`.
     * ```bash
          Usage:   [msh]$ exit                    # leave the msh shell
                   [johnsmith@onyx ~]$            # now back in shell that called ./mydash
       ```
* **jobs** - Displays any background jobs, their job number, and state since last `ENTER`.
     * ```bash
          Usage:   [msh]$ jobs                    # no arg needed / accepted at this time
                   [1] Done    echo hey you guy&  # example output for 3 background jobs submitted
                   [2] Done    sleep 30 &
                   [3] Running sleep 43 &
       ```
       
* **history** - prints the complete command history.  *Note: command line history recall was implemented for P1, this is
    new for P3.*
     * ```bash
          Usage:   [msh]$ history                 # no arg needed / accepted at this time
          Ex. 1:   1 ls                           # example output for 12 commands submitted
                   2 ls&
                   3 finger
                   4 echo hello world
                   5 pwd
                   6 cd ..
                   7 ls
                   8 ls -1 -l -r -d -t
                   9 sleep 63&
                   10 sleep 102 &
                   11 jobs
                   12 history
       ```


###### Background Jobs
* A command can be subitted to run in the background by including an *ampersand* '&' character at end.

    * ```bash
         Usage:   [msh]$ <some-cmd-string> &      # ignores whitespace or lack off around '&'
                  [4] 733468 some-cmd-string &    # status string when job first started in background
      ```


###### Command Line Editting / Command History Recall
* Using the library `readline/readline.h` provides the ability to edit on the command line within `mydash`,
  including `Ctrl` key inputs.  I found `Ctrl-L` gives the correct behavior of `clear`-ing the terminal.
* The library `readline/history.h` allows you to recall (up arrow, or `Ctrl-P`) previous commands in your
  command history.



###### Signals
Signal handling has been implemented for a subset of `Ctrl` key combinations, namely:
  * `Ctrl-D` - sends `SIGTERM` and will end the `mydash` shell session.
  * `Ctrl-C` - sends `SIGINT` and will `kill` a currently running foreground job, or if none, just display
     the message, "`Caught Control-c`".
  * `Ctrl-Z` - sends `SIGTSTP` and will suspend a currently running foreground job, or if none, just display
     the message, "`Caught Ctrl-z`".


## Testing
###### Prompt
Test the default prompt and custom prompt:
* **custom** - Before entering `mydash`, `export` the a parameter named `DASH_PROMPT` with your choice of a prompt.
  <br />
  Example:  `export DASH_PROMPT="[$USER@${HOSTNAME%%.*} msh]\$ "`
* **default** - Run `mydash` without exporting the custom prompt and verify it is: `[msh]$ `.

###### Version
Test the version number by invoking `mydash` with a single argument of `-v`.  It should return a 6-digit
version 'number', then exit.
```bash
$ ./mydash -v
mydash vf7f10f
$
```

###### Parsing
Some tests to check the general parsing functionality and specifically how it handles jobs with the background
character, '&'.
```bash
[msh]$ asdfasdfasfafsdgsdfgdgasfasdfasfasfafs           # really long token
[msh]$ asdfasdfaf fs f s f f ddd df ff fyt rew 333 5 5  # lots of tokens
[msh]$ ls  /sdfa   -g --h  %                            # special characters, some nonsense
                                                        #   here, but does it crash?
[msh]$                                                  # empty command
[msh]$ ls                                               # single command
[msh]$ _ _ _ _                                          # just whitespace characters
[msh]$ ls &                                             # bg: one space before &
[msh]$ pwd&                                             # bg: no space between &
[msh]$ echo hey you guy&_ _                             # bg: no space, &, then multiple spaces
[msh]$ finger &_ _                                      # bg: one space, &, then multiple spaces
[msh]$ who  & _ _ _                                     # bg: multiple spaces before and after &
```

###### Built-in Commands
* **jobs** -
> * Repeat the whitespace/ampersand tests from above once parsing has passed, now testing bg functionality
> * Try with `sleep`.  Vary the times and check for appropriate changes in status.
> * Try with a command you wouldn't normally put in the background (ex, `ls`, `pwd`). 
* **history**
> * Try with one of our other built-in commands, ex. `cd`.
> * Empty command.
> * Try with both background and foreground jobs.
> * Try nonsense commands
* **cd**
> * Try `cd` with no argument (should go to user's home directory)
> * Try `cd` with a full path (/usr/bin)
> * Try with a relative path (../p2)
> * Try with a directory in current working directory (`cd mydash-src`, no `./`)
> * Try with a non-existent directory (should give an appropriate message)
* **exit**
> * `exit` whenever
> * `exit` immediately
> * `exit` after a lot of commands
###### Non-Built-in Commands
> * Try nonsense commands                              # should give appropriate message
> * Try one token commands
> * Try multi-token commands (`mv thisFile thatFile`)
> * Try multi-token commands with options (`ls -r -1 -t -a -l`)
> * Try a text editor (`emacs newFile.txt`)
> * Recursive call, call `./mydash` from `mydash`.
###### Background Jobs
> * Verify start up message string when bg job is first submitted
> * Verify correct/complete listing of background jobs when `jobs` is entered
> * Verify single token, multi-token background jobs
###### Signals
> * `Ctrl-C` - with/without a foreground job
> * `Ctrl-Z` - with/without a foreground job
> * `Ctrl-D` - with/without a foreground job

###### Command Line Editting / History recall
> * `Ctrl-L` - should clear the terminal
> * `Ctrl-A` - move to start of command line
> * `Ctrl-E` - move to end of command line
> * `Ctrl-P` - recall previous command from history
> * `Ctrl-U` - clear command line
> * `Ctrl-K` - kill command line
> * `Ctrl-S` - lock your command line up (didn't try, just thought of it though..)
> * `Ctrl-Q` - unlock your command line if `Ctrl-S` succeeded in locking it
> * 'up arrow' - recall previous command from history (should be identical to `Ctrl-P`)
*Note: I could probably have spent even more time on spelling out the test cases, as well as writing out a
test plan (which I take to be a 'test strategy').  I ran out of time in general, and since testing is the
last thing you get to, I really ran out of time for this portion.*

### Known Bugs
Aka, Ran out of time to fix:
* `jobs`. Specifically I couldn't get the status updates to work. This affects them having the correct status,
  as well as the numbering, since they would never update, then I never was able to remove jobs that finished,
  so the numbering only increases (though the logic should be there to handle them correctly if the status 
  updates were working).
* Signal handling - `Ctrl-Z` is not functioning properly.
* Extra credit, `fg`/`bg` job control (ran out of time to try implementing).


## Discussion
#### Updates from P1 to P3
* **code modularity** - my p1 shell was written entirely modular, so strictly speaking I didn't have much to 
    to for this portion.  However, I did do a lot of 'refactoring' of the code, and that was in fact what probably
    took the largest amount of time I had to work on this.  Specifially, I removed some unnecessary routines and files
    (e.g., `JobNode.h`, `JobNode.c`), made code more concise and efficient (previously I had a routine to run `bg` jobs and
    one to run `fg` jobs in which most of the code was duplicated.  I now have a single routine `runJob()` which handles
    both `bg`/`fg` jobs and does so by taking a new argument, `bg_flag`).  I also hide some details in wrapper functions
    (ex., `parseInputToTokens`) and in general tried to do a lot of clean up to leave a much more clutter free and
    easy-to-follow program flow.  Below is a simplified schematic showing the main flow of the project.
    <br />
    **program flow schematic** *This platform does not support inline PDF's. Please visit link to view flow schematic*:
    <br />
    <a href="https://github.com/mmasarik/cs453-proto-repo/edit/p3/p3_program_flow.pdf"> main program flow PDF</a>.
* **test plan / test cases** - these have all been updated.
* **doxygen docs / javadoc comments** - all my `.h` files have now been fully documented with `javadoc` tags. 
* **README.md** - much more extensively filled out this time.
* **history** command - prints history list (minus empty commands)
* **Signal Handling** - not fully debugged though, specifically `Ctrl-z` needs work..
* **default prompt** - not hard, I didn't read carefully enough for P1 though. I choose `[msh]$ ` as explained above.


#### Biggest Challenges
* Updating status for background jobs.  I googled alot and tried everything I could think of.. I'm surprised I wasn't
  able to get this going.  I realized I wasn't leaving a lot of time for the signal handling or the Extra Credit 
  `fg`/`bg` job control, so I had to just move on at some point.


#### After Thoughts
* I realized once I got into the signal handling that I didn't need to have the backgrounds jobs completely solved
  (specifically the status update).  I got hung up on this and spent way too much time on it.  In the end I had
  to give up and move on anyway..  It's hard for me to give up on something like that, and it get's increasingly
  harder with the more time invested.  I think if I acknowledge that state sooner I'll be a more efficient programmer.
* As I mentioned for P1 I especially enjoy this shell project.  The reason why I think is because when I was just starting
  out as a scientist that was not exceptionally CS-saavy, the term `shell` seem to come up frequently and sometimes 
  referenced in different ways ("shell script", "open a shell", "what shell are you using, `bash`, `tcsh`?", 
  "you need to use a secure shell", etc.) that I found confusing at the time.  Because of this the 'shell' was 
  somewhat mysterious to me, though I knew it was an important concept so I always tried to understand more about it.
  When I took CS253 this summer I was literally blown away to learn that I could write a shell, in C, and even more
  the concepts were easily within reach for me to understand. 


#### What Started to Click
* Signals and signal handling.
* Javadocs/doxygen.  Not that there's anything tough about them, I just hadn't been exposed to them until this class.


## Sources used
###### Part 2
* [waitpid/WIFEXITED](https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.1.0/com.ibm.zos.v2r1.bpxbd00/rtwaip.htm)
* [pdf markdown inline](https://stackoverflow.com/questions/39777166/display-pdf-image-in-markdown)
* [tree in manifest](https://stackoverflow.com/questions/19699059/representing-directory-file-structure-in-markdown-syntax)
* [tree in manifest](https://meta.stackexchange.com/questions/147467/is-there-a-good-way-to-represent-file-structure-in-a-question-answer)
* [doxygen: main page](https://stackoverflow.com/questions/7151360/can-doxygen-process-pages-other-than-mainpage-dox)
* [javadocs: C struct](http://fnch.users.sourceforge.net/doxygen_c.html)



###### Part 1
* https://linux.die.net/man/3/getpwuid
* https://www.tutorialspoint.com/unix/unix-signals-traps.htm
* https://cnswww.cns.cwru.edu/php/chet/readline/history.html#SEC10
* http://cc.byexamples.com/2008/06/13/gnu-readline-how-to-keep-a-history-list-of-entered-command-lines/
* https://linux.die.net/man/2/waitpid
* https://stackoverflow.com/questions/4200373/just-check-status-process-in-c

