#include "gdhacks.h"
#include <string>
#include <sstream>


std::string allhacks = 
"-1: Exit\r\n\
0: Read memory \r\n\
1: Toggle object limit bypass (only place, not copy)\r\n\
2: Toggle noclip";

int main()
{
	ProcMem mem;
	mem.Process("GeometryDash.exe");
	SetConsoleTitle("Geometry Dash Hack");
	hack objLimHacks[] = {hack(0x469910,0xCE8B0D74,0xCE8B0DEB)}; /*
	address, original value, modded value. 
	Use 4 bytes, 
	so if you want to mod CC to CE at address 0x653, 
	you need to write hack(0x653, 0x??????CC, 0x??????CE), 
	where ?? are the other bytes
	you need to write them, or they will be replaced by zeros
	I'll fix it later
	Probably you'll need to enter patched bytes amount
	*/
	gdhack object_limit = gdhack(mem, objLimHacks, 1);//1 hack

	hack noClipHacks[] = {hack(0x57B591, 0x0313850F, 0x000314E9),hack(0x57B595,0x758B0000,0x758B9000)};
	/*
	the hacks are near, but since you can't use more then 4 bytes
	they have to be separated.
	As I said before, gonna fix it later
	*/
	gdhack no_clip(mem, noClipHacks, 2);//2 hacks

	while(1) {
		std::cout << allhacks << std::endl;
		int n;
		std::cin >> n;
		std::string adrS;
		std::stringstream ss;

		switch(n) {
		default:
			return 0;
			break;
		case 0:
			std::cout << "Enter address:" << std::endl;
			DWORD adr;
			std::cin >> adrS;
			if(adrS[1] == 'x') {
				ss << std::hex << adrS.substr(2, adrS.length() - 2); //convert from hex string
			} else {
				ss << std::dec << adrS; //convert from dec string
			}
			
			ss >> adr;
			std::cout << "0x" << std::hex << mem.Read<DWORD>(adr) << std::endl;
		case 1:
			object_limit.toggle();
			break;
		case 2:
			no_clip.toggle();
			break;
		}
	}
}