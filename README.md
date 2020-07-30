# **Download and Compile Boost v1.73**

**Mac and Linux**:
1. Download Boost v1.73 .gz folder (in Google Drive)


**Windows (Visual Studio 2017)**:
1. Download Boost v1.73 .zip folder (in Google Drive)
2. Download zlib v1.2.11 .zip folder (in Google Drive)
3. Extract boost files to folder "boost_1_73_0"
4. Extract zlib files to folder "zlib-1.2.11"
5. Open CMD
6. CD to "boost_1_73_0" or wherever the boost files were extracted to
7. Run the following command : `bootstrap.bat --with-libraries=atomic,chrono,context,coroutine,date_time,exception,filesystem,graph,graph_parallel,iostreams,locale,log,math,mpi,program_options,random,regex,serialization,system,test,thread,timer,wave`
8. Build the boost library with the following command (works with Visual Studio 2017) :  `b2 -j15 --toolset=msvc --build-type=complete stage -s ZLIB_SOURCE="C:\Path\To\zlib-1.2.11" -s ZLIB_INCLUDE="C:\Path\To\zlib-1.2.11"`




# **Download And Compile Sqlite3**
**Linux**: 
1. sudo apt-get install sqlite3

**Mac and Linux (if you did not use apt-get)**:
1. Download sqlite3 source code (also available in Google Drive)
2. Build the source code to get the .o file -> "gcc -c sqlite3.c"
3. The build command should generate a .o file that will be used with compiling OT.
4. Move the .o file to the OT source code folder

**Windows**:
1. Download sqlite3 source code (also available in Google Drive)



# **Download and Compile OT**
**Linux (if you used apt-get install sqlite3)**:
1. Download OT source code for Linux (available in Google Drive)
2. CD to OT source code folder
3. Run Command to compile OT: `g++ -std=c++11 CasperOffTargetWindows.cpp CSeqTranslate.cpp csprRef.cpp FileOp.cpp gRNA.cpp OffScoring.cpp pch.cpp RefSequences.cpp -pthread -lsqlite3 -lboost_system -lboost_iostreams -o OT`

**Mac and Linux (if you manually built sqlite3 .o file, make sure sqlite3 .o file is in same folder as OT source code)**:
1. Download OT source code for Mac or Linux (available in Google Drive)
2. CD to OT source code folder
3. Run command to compile OT: `g++ -std=c++11 CasperOffTargetWindows.cpp CSeqTranslate.cpp csprRef.cpp FileOp.cpp gRNA.cpp OffScoring.cpp pch.cpp RefSequences.cpp -pthread sqlite3.o -lboost_system -lboost_iostreams -o OT`

**Windows (Visual Studio 2017)**:
1. Set the following settings in VS (make setting changes apply to all releases):
	* Make sure release is x86 (32-bit)
	* Build project. 
	* .exe should be in project folder for Visual Studio


