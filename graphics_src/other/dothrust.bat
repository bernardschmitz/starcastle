
echo #declare frm = %1 >frm

copy frm+smove.pov move%1.pov

echo Pause_when_Done = on >move.ini
echo Bounding_Threshold = 3 >>move.ini
echo Test_Abort=On >>move.ini
echo Test_Abort_Count=100 >>move.ini
echo Library_Path=C:\POVRAY3  >>move.ini
echo Library_Path=C:\POVRAY3\include  >>move.ini
echo Input_File_Name=move%1.pov >>move.ini
echo Initial_Frame=0 >>move.ini
echo Initial_Clock=0 >>move.ini
echo Final_Clock=1 >>move.ini
echo Cyclic_Animation=off >>move.ini
echo Post_Frame_Command=arj m smove.arj %%o >>move.ini
echo +v >>move.ini
echo +b64 >>move.ini
echo -p >>move.ini
echo +w64 >>move.ini
echo +h64 >>move.ini
echo +a0.01 >>move.ini
echo -j0 >>move.ini
echo [go] >>move.ini
echo Final_Frame=7 >>move.ini

povray move.ini +kff7

del move%1.pov

