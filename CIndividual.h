#pragma once

#include <iostream>
#include <random>

#include "CGenotyp.h"
#include "CPrzedmiot.h"
#include "Errors.h"

// forward declaration to avoid circural including between CIndividual and CGeneticAlgorithm
class CGeneticAlgorithm; 

class CIndividual {

	
public:

	static const int NUM_OF_CHILDREN = 2;

	CIndividual();

	CIndividual(CGenotyp g);

	CIndividual(const CIndividual& cOther);

	~CIndividual();

	CGenotyp* getGenotyp();

	CIndividual& operator=(const CIndividual& cOther);

	// zwraca tablicê dzieci powsta³ych w wyniku krzy¿owania
	CIndividual* crossover(CIndividual & cOther, int pivot, CError* error_type = nullptr);
	
	// tutaj: zwykle robi to samo, co CKnapsackProblem::wartosc_rozwiazania
	int fitness(CPrzedmiot* lista_wag_i_wartosci, int max_weight);

	void mutation(double prawdop_mutacji);

	void setValue(int i);
	int getValue();

private:
	CGenotyp * genotype;
	
	int value; // 0, chyba ¿e zostanie specjalnie ustawione za pomoc¹ setValue()

};
