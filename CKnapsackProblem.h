#pragma once

#include <iostream>
#include <vector>

#include "CPrzedmiot.h"
#include "CGenotyp.h"
#include "CGeneticAlgorithm.h"

#include "Errors.h"

using namespace std;

class CKnapsackProblem {

public:

	CKnapsackProblem();

	CKnapsackProblem(int liczbaPrzedmiotow, int maxWeight);


	void setValues(int * values, CError* error_type = nullptr);
	void setWeights(int* weights, CError* error_type = nullptr);

	~CKnapsackProblem();

	int wartosc_rozw(CGenotyp genotyp);

	CGenotyp solveWith(CGeneticAlgorithm & algo);

	void wczytaj_z_pliku(string filename, CError* error_type = nullptr);

	CPrzedmiot* getPrzedmioty() { return przedmioty; }

	int getMaxWeight() {	return max_weight; }

	int getItemCount() { return liczba_przedmiotow; }

private:

	int liczba_przedmiotow;
	CPrzedmiot * przedmioty; // tablica przedmiotów, jakie mog¹ siê znaleŸæ w plecaku
	int max_weight;

};

