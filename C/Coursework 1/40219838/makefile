compileCW:
	cl miniGrep.c

cleanAll:
	del *.obj
	del *.exe
	del *.asm
	del output.txt
	
cleanOutput:
	del output.txt

YeatsDemo:
	miniGrep clo -i Yeats.txt -o output.txt
	Yeats.txt
	output.txt
	
TolkienDemo:
	miniGrep gAnDaLF -i Tolkien.txt -o output.txt -c
	Tolkien.txt
	output.txt	
	
longStringDemo:
	miniGrep b -i superString.txt -o output.txt
	superString.txt
	output.txt	
	
defaultDemo:
	miniGrep bored

endlessDemo:
	miniGrep abc -e