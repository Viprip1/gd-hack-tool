#ifndef GDHACKS_H
#define GDHACKS_H
#include "ProcMem.h"
#include <vector>

struct hack {
	DWORD adr;
	DWORD orig;
	DWORD hacked;
	hack(DWORD a, DWORD b, DWORD c) {
		adr = a;
		orig = b;
		hacked = c;
	}
	
	int hackState(ProcMem &mem) {
		DWORD read = mem.Read<DWORD>(adr);
		if(read == orig) return 0;
		else if(read == hacked) return 1;
		return -1;
	}
	void toggle(ProcMem &mem) {
		int state = this->hackState(mem);
		if(state == 1) {
			mem.Write<DWORD>(adr, orig); 
		} else if(state == 0) {
			mem.Write<DWORD>(adr, hacked);
		} else {
			std::cout << "Unsupported GD version" << std::endl;
		}
	}
};

std::vector<hack> getVector(hack* hacks, int hacksCount) {
	std::vector<hack> vec(hacks, hacks + hacksCount);
	return vec;
}

struct gdhack {
private:
	std::vector<hack> _hacks;
	ProcMem _mem;
public:
	void toggle() {
		std::cout << _hacks.size() << std::endl;
		for(int i = 0; i < _hacks.size(); i++) {
			_hacks[i].toggle(_mem);
		}
	}
	gdhack(ProcMem &mem, std::vector<hack> hacks) {
		_hacks = hacks;
		_mem = mem;
	}
	gdhack(ProcMem &mem, hack* hacks, int hacksCount) {
		_hacks = getVector(hacks, hacksCount);
		_mem = mem;
	}
};


#endif