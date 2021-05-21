# HOW TO COMPILE:
1. cd to current directory.
2. Run "make" command.
3. Execute shell by typing "./myShell" command.
4. Everytime there's an update in any .c file, please repeat Step 1 to 3.
5. In case above steps doesn't work, please run following commands one by one:
      * gcc myShell.c -o myShell
      * gcc checkcpupercentage.c -o checkcpupercentage
      * gcc checkresidentmemory.c -o checkresidentmemory
      * gcc executeCommands.c -o executeCommands
      * gcc io.c -o io
      * gcc listFiles.c -o listFiles
      * gcc sortFile.c -o sortFile

# CUSTOM COMMANDS:
1. **checkcpupercentage {pid}**: This command accepts a process identifier as an argument and returns the percentage CPU used by the process with identifier {pid} in user mode and system mode.
2. **checkresidentmemory {pid}**: This command accepts a pid of a process and output the resident set size which is the physical memory that the task has used.
3. **listFiles**: This command will save all the files and folders, in the current working directory to a file named files.txt.
4. **sortFile**: This command get the file’s contents sorted line by line and print it to STDOUT.
5. **executeCommands**: This command takes a filename as an argument and executes all the commands listed in the file sequentially in the same order as given in the file.

# GENERAL POINTS:
1. If a command itself doesn't give error in case of invalid arguements then this shell also won't. For example,
in "ps -p 500 -o rss" where 500 is a pid which doesn't exist, ps doesn't throw an error and so will this shell.

2. This shell doesn't trim quotes for commands. For example, ls and "ls" are different commands for this shell
and it won't run "ls".

3. grep identifies pattern enclosed in double quotes, single quotes or passed directly.
