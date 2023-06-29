#include "CKnapsackProblem.h"

#include <iostream>
#include <fstream> 
#include <string> 

CKnapsackProblem::CKnapsackProblem() {
	liczba_przedmiotow = 0;
	max_weight = 0;
	przedmioty = new CPrzedmiot[liczba_przedmiotow];
}

CKnapsackProblem::CKnapsackProblem(int liczbaPrzedmiotow, int maxWeight) {
	if (liczbaPrzedmiotow < 0 || maxWeight < 0) 
		throw std::invalid_argument("incorrect parameter");

	liczba_przedmiotow = liczbaPrzedmiotow;
	max_weight = maxWeight;
	przedmioty = new CPrzedmiot[liczba_przedmiotow];
}

void CKnapsackProblem::setValues(int* values, CError* error_type) {

	// proba wykonania SetValue mo¿e wyrzuciæ std::invalid_argument
	try {
		for (int i = 0; i < liczba_przedmiotow; i++) {
			try {
				przedmioty[i].SetValue(values[i]);
			}
			catch (std::invalid_argument) {
				przedmioty[i].SetValue(0);
			}
		}
	}
	catch (std::invalid_argument ext) {
		if (error_type) *error_type = CError::niedopasowany_parametr;
	}
}

void CKnapsackProblem::setWeights(int* weights, CError* error_type) {

	// proba wykonania SetValue mo¿e wyrzuciæ std::invalid_argument
	try {
		for (int i = 0; i < liczba_przedmiotow; i++) {
			try {
				przedmioty[i].SetWeight(weights[i]);
			}
			catch (std::invalid_argument) {
				przedmioty[i].SetWeight(0);
			}
		}
	}
	catch (std::invalid_argument ext) {
		if(error_type) *error_type = CError::niedopasowany_parametr;
	}

}

CKnapsackProblem::~CKnapsackProblem() {
	delete[] przedmioty;
}

int CKnapsackProblem::wartosc_rozw(CGenotyp genotyp) {
	
	int suma_mas = 0;
	int suma_wartosci = 0;
	int* geny_ptr = genotyp.getGenes();
	int geny_size = genotyp.getSize();

	for (int i = 0; i < liczba_przedmiotow && i < geny_size; i++) {
		suma_mas += geny_ptr[i] * przedmioty[i].GetWeight();
		suma_wartosci += geny_ptr[i] * przedmioty[i].GetValue();
	}

	if(suma_mas > max_weight) return 0;
	else return suma_wartosci;
}

CGenotyp CKnapsackProblem::solveWith(CGeneticAlgorithm & algo) {
	return algo.optimize(this);
}

void CKnapsackProblem::wczytaj_z_pliku(string filename, CError * error_type) {

	/* 
	plik jest w formacie:
		n wmax
		v1 w1
		v2 w2
		: :
		vi wi
		: :
		vn wn
	n: number of items; wmax: knapsack capacity; vi: profit of item i; wi: weight of item i
	*/


	ifstream myFile;
	
	myFile.open(filename);

	if (!myFile.is_open()) {
		if (error_type) *error_type = CError::brak_pliku;
		return;
	}
	
	int nowa_liczba_przedmiotow, nowa_masa_maksymalna;

	myFile >> nowa_liczba_przedmiotow;
	myFile >> nowa_masa_maksymalna;
	
	if (nowa_liczba_przedmiotow < 0 || nowa_masa_maksymalna < 0) {
		if (error_type) *error_type = CError::niepoprawny_plik;

		myFile.close();
		return;
	}

	CPrzedmiot * nowe_przedmioty;
	nowe_przedmioty = new CPrzedmiot[nowa_liczba_przedmiotow];

	int wartosc, masa;
	int index = 0;

	try{
		while (index < nowa_liczba_przedmiotow) {

			// sprawdzenie, czy da sie wczytac 1-sz¹ liczbê
			if (!myFile.eof())
				myFile >> wartosc;
			else {
				if (error_type) *error_type = CError::niepoprawny_plik;
				delete[] nowe_przedmioty;
				myFile.close();
				return;
			}
			// sprawdzenie, czy da sie wczytac 2-g¹ liczbê
			if (!myFile.eof())
				myFile >> masa;
			else {
				if (error_type) *error_type = CError::niepoprawny_plik;
				delete[] nowe_przedmioty;
				myFile.close();
				return;
			}

			nowe_przedmioty[index].SetValue(wartosc);
			nowe_przedmioty[index].SetWeight(masa);

			index++;
		}
		
	}
	catch (std::invalid_argument ext) {
		if (error_type) *error_type = CError::niedopasowany_parametr;
		delete[] nowe_przedmioty;
		myFile.close();
		return;
	}
	
	// poni¿sze siê wykonuje, je¿eli wczytywanie z pliku zakoñczy³o siê sukcesem:
	liczba_przedmiotow = nowa_liczba_przedmiotow;
	max_weight = nowa_masa_maksymalna;
	delete[] przedmioty;
	przedmioty = nowe_przedmioty;

	myFile.close();
}

