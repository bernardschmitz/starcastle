
echo #declare frm = %1 >frm

copy frm+sfire.pov shoot%1.pov

echo Pause_when_Done = on >shoot.ini
echo Bounding_Threshold = 3 >>shoot.ini
echo Test_Abort=On >>shoot.ini
echo Test_Abort_Count=100 >>shoot.ini
echo Library_Path=C:\POVRAY3  >>shoot.ini
echo Library_Path=C:\POVRAY3\include  >>shoot.ini
echo Input_File_Name=shoot%1.pov >>shoot.ini
echo Initial_Frame=0 >>shoot.ini
echo Initial_Clock=0 >>shoot.ini
echo Final_Clock=1 >>shoot.ini
echo Cyclic_Animation=off >>shoot.ini
echo Post_Frame_Command=arj m sfire.arj %%o >>shoot.ini
echo +v >>shoot.ini
echo +b64 >>shoot.ini
echo -p >>shoot.ini
echo +w64 >>shoot.ini
echo +h64 >>shoot.ini
echo +a0.01 >>shoot.ini
echo -j0 >>shoot.ini
echo [go] >>shoot.ini
echo Final_Frame=7 >>shoot.ini

povray shoot.ini +kff7

del shoot%1.pov

