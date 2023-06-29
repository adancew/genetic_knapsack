#pragma once

#include <iostream>

class CPrzedmiot{

public:
	CPrzedmiot();

	CPrzedmiot(int w, int v);

	int GetValue() { return value; }
	int GetWeight() { return weight; }

	void SetValue(int v);
	void SetWeight(int w);

private:
	int value;
	int weight;
};

