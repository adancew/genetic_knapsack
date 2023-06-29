#include "CPrzedmiot.h"

CPrzedmiot::CPrzedmiot() {
	value = 0;
	weight = 0;
}

CPrzedmiot::CPrzedmiot(int w, int v) {
	
	if (w < 0) throw std::invalid_argument("incorrect weight");
	if (v < 0) throw std::invalid_argument("incorrect value");
		
	weight = w;
	value = v;
}


void CPrzedmiot::SetValue(int v)  throw (std::invalid_argument) {
	if (v < 0) throw std::invalid_argument("incorrect value");
	value = v;
}

void CPrzedmiot::SetWeight(int w)  throw (std::invalid_argument) {
	if (w < 0) throw std::invalid_argument("incorrect weight");
	weight = w;
}