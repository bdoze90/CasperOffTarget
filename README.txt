Download and Compile Boost v1.73
Mac and Linux:
	- Download Boost v1.73 (available in Google Drive)
	-

Windows:
	- Download Boost v1.73 (available in Google Drive)




Download And Compile Sqlite3
Linux: 
	- sudo apt-get install sqlite3

Mac and Linux (if you did not use apt-get):
	- Download sqlite3 source code (also available in Google Drive)
	- Build the source code to get the .o file -> "gcc -c sqlite3.c"
	- The build command should generate a .o file that will be used with compiling OT.
	- Move the .o file to the OT source code folder

Windows:
	- Download sqlite3 source code (also available in Google Drive)
	- 



Compile Code
Linux (if you used apt-get install sqlite3):

g++ -std=c++11 CasperOffTargetWindows.cpp CSeqTranslate.cpp csprRef.cpp FileOp.cpp gRNA.cpp OffScoring.cpp pch.cpp RefSequences.cpp -pthread -lsqlite3 -lboost_system -lboost_iostreams -o OT

Mac and Linux (if you manually built sqlite3 .o file, make sure sqlite3 .o file is in same folder as OT source code):

g++ -std=c++11 CasperOffTargetWindows.cpp CSeqTranslate.cpp csprRef.cpp FileOp.cpp gRNA.cpp OffScoring.cpp pch.cpp RefSequences.cpp -pthread sqlite3.o -lboost_system -lboost_iostreams -o OT

Windows (Visual Studio):
	- Set the following settings in VS (make setting changes apply to all releases):
	
	- Make sure release is x86 (32-bit)
	- Build project. 
	- .exe should be in project folder for Visual Studio


