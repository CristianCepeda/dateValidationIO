output: readingDatesFile.o writingDatesFile.o
	gcc readingDatesFile.o -o readingDatesFile
	gcc writingDatesFile.o -o writingDatesFile

readingDatesFile.o: readingDatesFile.c
	gcc -c readingDatesFile.c

writingDatesFile.o: writingDatesFile.c
	gcc -c writingDatesFile.c

clean:
	rm *.o readingDatesFile writingDatesFile

# if anything is changed in the file writingDatesFile.c
# when you enter "make" in terminal then only that file will compile
#
# The same goes with readingDatesFile.c if anything is changed then you
# just enter "make" in the terminal and it will only compile the necessary
# files.
#
# with what I just explain if a file changes then when you run "make" it will
# update the object files that correspond to the source code
#
# the output tag means that anytime any of those two object files change then
# compile the files. provide underneath
