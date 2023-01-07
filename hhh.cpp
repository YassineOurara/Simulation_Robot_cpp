#include <Windows.h>
#include <string>
std::string alarmSound = "C:\\Users\\smart asus\\OneDrive\\Documents\\GitHub\\Simulation_Robot_cpp\\sound.wav";
PlaySound(alarmSound.c_str(), NULL, SND_FILENAME);
