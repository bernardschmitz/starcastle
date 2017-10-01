
echo #declare frm = %1 >frm

copy frm+laser.pov l%1.pov

echo Pause_when_Done = on >l.ini
echo Bounding_Threshold = 3 >>l.ini
echo Test_Abort=On >>l.ini
echo Test_Abort_Count=100 >>l.ini
echo Library_Path=C:\POVRAY3  >>l.ini
echo Library_Path=C:\POVRAY3\include  >>l.ini
echo Input_File_Name=l%1.pov >>l.ini
echo Initial_Frame=0 >>l.ini
echo Initial_Clock=0 >>l.ini
echo Final_Clock=1 >>l.ini
echo Cyclic_Animation=off >>l.ini
echo Post_Frame_Command=arj m laser.arj %%o >>l.ini
echo +v >>l.ini
echo +b64 >>l.ini
echo -p >>l.ini
echo +w112 >>l.ini
echo +h112 >>l.ini
echo +a0.3 >>l.ini
rem echo -a >>l.ini
echo -j0 >>l.ini
echo [go] >>l.ini
echo Final_Frame=6 >>l.ini

povray l.ini +kff6

del l%1.pov

