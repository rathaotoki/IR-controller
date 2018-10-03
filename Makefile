
ir_core.exe : testmain.cpp IRdata_template.cpp IRdata_Mitsubishi_Kirigamine.cpp
	g++ --std=c++0x -o ir_core.exe testmain.cpp IRdata_template.cpp IRdata_Mitsubishi_Kirigamine.cpp
