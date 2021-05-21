myShell: shellread shellfunc checkcpupercentage myShell.c
		gcc myShell.c -o myShell

checkcpupercentage: checkresidentmemory checkcpupercentage.c
		gcc checkcpupercentage.c -o checkcpupercentage

checkresidentmemory: executeCommands checkresidentmemory.c
		gcc checkresidentmemory.c -o checkresidentmemory

executeCommands: io executeCommands.c
		gcc executeCommands.c -o executeCommands

io: listFiles io.c
		gcc io.c -o io

listFiles: sortFile listFiles.c
		gcc listFiles.c -o listFiles

sortFile: sortFile.c
		gcc sortFile.c -o sortFile

shellread: shellread.c
		touch shellread.c

shellfunc: shellfunc.c
		touch shellfunc.c
