#include "CGenotyp.h"

#include <iostream>

CGenotyp::CGenotyp() {
	size = 0;
	genotype = new int[size];
	for (int i = 0; i < size; i++) genotype[i] = 0;
}

CGenotyp::CGenotyp(int s) throw (std::invalid_argument) {
	if (s < 0) throw std::invalid_argument("incorrect size");

	size = s;
	genotype = new int[size];
	for (int i = 0; i < size; i++) genotype[i] = 0;
}

CGenotyp::CGenotyp(const CGenotyp& cOther) {
	size = cOther.size;
	genotype = new int[size];
	for (int i = 0; i < size; i++) {
		genotype[i] = cOther.genotype[i];
	}
}

CGenotyp::~CGenotyp(){ 
	delete[] genotype; 
}

CGenotyp& CGenotyp::operator=(CGenotyp& cOther) {
	if (cOther.genotype != genotype) {

		delete[] genotype;

		size = cOther.size;
		genotype = new int[size];

		for (int i = 0; i < size; i++) {
			genotype[i] = cOther.genotype[i];
		}
	}
	return *this;
}

bool CGenotyp::swapGene(int i) {
	if (i >= 0 && i < size) {

		if (genotype[i] == 0) genotype[i] = 1;
		else if (genotype[i] == 1) genotype[i] = 0;
		
		return true;
	}
	return false;
}

bool CGenotyp::setGene(int i, int v) {
	if (i >= 0 && i < size) {
		genotype[i] = v;
		return true;
	}
	return false;
}

int CGenotyp::getGene(int i){ 
	return genotype[i];  
}

void CGenotyp::setSize(int new_size) throw (std::invalid_argument) {
	if (new_size < 0) throw std::invalid_argument("incorrect array size");

	// jesli nowy rozmiar jest wiekszy od dotychczasowego, 
	// utworz nowa tablice i przekopiuj do niej dotychczasow¹ zawartoœæ
	if (new_size > size) {
		int* new_genotyp = new int[new_size];
		for (int i = 0; i < size; i++) 
			new_genotyp[i] = genotype[i];
		for (int i = size; i < new_size; i++)
			new_genotyp[i] = 0;

		delete[] genotype;
		genotype = new_genotyp;
	}

	size = new_size;
}

void CGenotyp::print_genotype() {
	std::cout << '[';
	for (int i = 0; i < size; i++) std::cout << genotype[i] << ' ';
	std::cout << ']';
}