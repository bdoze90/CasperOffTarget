# **Download and Compile Boost v1.73**

**Mac and Linux**:
	- Download Boost v1.73 .gz folder (in Google Drive)
	-

**Windows (Visual Studio 2017)**:
	1. Download Boost v1.73 .zip folder (in Google Drive)
	2. Download zlib v1.2.11 .zip folder (in Google Drive)
	3. Extract boost files to folder "boost_1_73_0"
	4. Extract zlib files to folder "zlib-1.2.11"
	5. Open CMD
	6. CD to "boost_1_73_0" or wherever the boost files were extracted to
	7. Run the following command : "bootstrap.bat --with-libraries=atomic,chrono,context,coroutine,date_time,exception,filesystem,graph,graph_parallel,iostreams,locale,log,math,mpi,program_options,random,regex,serialization,system,test,thread,timer,wave"
	8. Build the boost library with the following command (works with Visual Studio 2017) :  "b2 -j15 --toolset=msvc --build-type=complete stage -s ZLIB_SOURCE="C:\Path\To\zlib-1.2.11" -s ZLIB_INCLUDE="C:\Path\To\zlib-1.2.11""




# **Download And Compile Sqlite3**
**Linux**: 
	- sudo apt-get install sqlite3

**Mac and Linux (if you did not use apt-get)**:
	- Download sqlite3 source code (also available in Google Drive)
	- Build the source code to get the .o file -> "gcc -c sqlite3.c"
	- The build command should generate a .o file that will be used with compiling OT.
	- Move the .o file to the OT source code folder

**Windows**:
	- Download sqlite3 source code (also available in Google Drive)
	- 



# **Compile OT**
**Linux (if you used apt-get install sqlite3)**:

g++ -std=c++11 CasperOffTargetWindows.cpp CSeqTranslate.cpp csprRef.cpp FileOp.cpp gRNA.cpp OffScoring.cpp pch.cpp RefSequences.cpp -pthread -lsqlite3 -lboost_system -lboost_iostreams -o OT

**Mac and Linux (if you manually built sqlite3 .o file, make sure sqlite3 .o file is in same folder as OT source code)**:

g++ -std=c++11 CasperOffTargetWindows.cpp CSeqTranslate.cpp csprRef.cpp FileOp.cpp gRNA.cpp OffScoring.cpp pch.cpp RefSequences.cpp -pthread sqlite3.o -lboost_system -lboost_iostreams -o OT

**Windows (Visual Studio 2017)**:
	- Set the following settings in VS (make setting changes apply to all releases):
	
	- Make sure release is x86 (32-bit)
	- Build project. 
	- .exe should be in project folder for Visual Studio


