#pragma once



#include "Errors.h"

#include "CGenotyp.h"
#include "CPrzedmiot.h"

#include "CIndividual.h"
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"



class Testy
{
public:

	void run();

	bool test_genotyp();

	bool test_przedmiot();

	bool test_individual();
	bool test_individual_krzyzowanie();

	
	bool test_algo_generuj_populacje();
	bool test_algo_krzyzuj_populacje();
	bool test_algo_mutuj_populacje();
	bool test_algo_najlepsze_rozwiazanie_w_populacji();
	bool test_algo_optimize();

	bool test_problem();
	bool test_plik();
	bool test_problem_wartosc_rozw();
};



