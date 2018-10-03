
test.exe : testmain.cpp IRdata_template.cpp IRdata_Mitsubishi_Kirigamine.cpp
	g++ --std=c++0x -o test.exe testmain.cpp IRdata_template.cpp IRdata_Mitsubishi_Kirigamine.cpp
