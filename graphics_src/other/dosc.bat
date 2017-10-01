
echo #declare frm = %1 >frm

copy frm+sc.pov sc%1.pov

echo Pause_when_Done = on >sc.ini
echo Bounding_Threshold = 3 >>sc.ini
echo Test_Abort=On >>sc.ini
echo Test_Abort_Count=100 >>sc.ini
echo Library_Path=C:\POVRAY3  >>sc.ini
echo Library_Path=C:\POVRAY3\include  >>sc.ini
echo Input_File_Name=sc%1.pov >>sc.ini
echo Initial_Frame=0 >>sc.ini
echo Initial_Clock=0 >>sc.ini
echo Final_Clock=1 >>sc.ini
echo Cyclic_Animation=off >>sc.ini
echo Post_Frame_Command=arj m sc.arj %%o >>sc.ini
echo +v >>sc.ini
echo +b64 >>sc.ini
echo -p >>sc.ini
echo +w112 >>sc.ini
echo +h112 >>sc.ini
echo +a0.01 >>sc.ini
echo -j0 >>sc.ini
echo [go] >>sc.ini
echo Final_Frame=15 >>sc.ini

povray sc.ini +kff15

del sc%1.pov

