#pragma once

#include <iostream>

#include "CIndividual.h"
#include "Errors.h"

// forward declaration to avoid circural including between CKnapsachProblem and CGeneticAlgorithm
class CKnapsackProblem; 

class CGeneticAlgorithm{

public:

	static const int SEED = 1;
	static const int ITERATIONS = 20;

	CGeneticAlgorithm();

	CGeneticAlgorithm(int populationSize, double crossoverProbability,
		double mutationProbability);
		
	~CGeneticAlgorithm();

	CGenotyp optimize(CKnapsackProblem* problem, CError* error_type = nullptr);


	// true, jezeli nalezy zakonczyc. false, jezeli kontynuowac
	bool kryterium_zatrzymania(int remaining_iterations);
	
	void generuj_populacjê();

	CGenotyp najlepsze_rozwiazanie_w_populacji(CError * error_type = nullptr);
	
	void update_values(CPrzedmiot* wagi_i_wartosci, int max_weight);

	
	void krzyzuj_populacje();	
	void mutuj_populacje();		
	void drukuj_populacje();

	void set_liczba_iteracji(int i) { iteration_count = i; }
	void set_crossover_probability(double p) {crossover_probability = p;}
	void set_mutation_probability(double p) {mutation_probability = p;}
	void set_genotype_size(int i) { genotype_size = i;}
	void set_backpack_fullness(double d) { initial_backpack_fullness = d; }
	void set_population_size(int i) { population_size = i; }

private:

	int population_size;
	double crossover_probability;
	double mutation_probability;
	int genotype_size;
	double initial_backpack_fullness;

	int iteration_count;

	CIndividual* population;

};

