..\bin\Bgcc1.exe -quiet -std=c99 -fno-builtin -O2 -I..\include binary_search_tree.c
..\bin\Bgcc1.exe -quiet -std=c99 -fno-builtin -O2 -I..\include task_scheduler.c 
..\bin\Bgcc1.exe -quiet -std=c99 -fno-builtin -O2 -I..\include main.c

..\bin\Bas.exe -x -datarota=2 binary_search_tree.s
..\bin\Bas.exe -x -datarota=2 task_scheduler.s
..\bin\Bas.exe -x -datarota=2 main.s 
..\bin\Bld.exe -o source.out -codebase=1000 -datafloat ..\lib\base.o main.o binary_search_tree.o task_scheduler.o -L../lib -lmc -lc -lgcc
..\bin\Bimg.exe source.out
del aaab
ren source.img aaab
del source.out
del *.s
del *.o
pause
