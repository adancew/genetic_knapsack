#include "CGeneticAlgorithm.h"
#include "CKnapsackProblem.h"
#include <iostream>
#include <random>

CGeneticAlgorithm::CGeneticAlgorithm() {

	population_size = 0;
	crossover_probability = 0;
	mutation_probability = 0;
	genotype_size = 0;
	iteration_count = ITERATIONS;
	initial_backpack_fullness = 0.5;

	population = nullptr;
}

CGeneticAlgorithm::CGeneticAlgorithm(int populationSize, double crossoverProbability,
	double mutationProbability) {

	if (populationSize < 0)
		throw std::invalid_argument("incorrect parameter");

	population_size = populationSize;
	crossover_probability = crossoverProbability;
	mutation_probability = mutationProbability;
	genotype_size = 0;
	iteration_count = ITERATIONS;
	initial_backpack_fullness = 0.5;

	population = nullptr;
}

CGeneticAlgorithm::~CGeneticAlgorithm() {
	delete[] population;
}


bool CGeneticAlgorithm::kryterium_zatrzymania(int remaining_iterations) {
	//Jako kryterium przyjeto liczbê iteracji metody
	if (remaining_iterations <= 0) return true;
	else return false;
}

void CGeneticAlgorithm::generuj_populacjê() {

	if (population != nullptr) delete[] population;

	population = new CIndividual[population_size];

	for (int i = 0; i < population_size; i++) {
		population[i].getGenotyp()->setSize(genotype_size);
	}

	//std::default_random_engine generator(SEED); // do testow
	std::random_device rd;  //potrzebne aby uzyskaæ ziarno.
	std::default_random_engine generator(rd()); 
	std::uniform_real_distribution<> float_distribution(0.0, 1.0);

	CGenotyp * geny_osobnika;
	
	for (int nr_osobnika = 0; nr_osobnika < population_size; nr_osobnika++) {
		geny_osobnika = population[nr_osobnika].getGenotyp();
		for (int nr_genu = 0; nr_genu < genotype_size; nr_genu++) {
			if(float_distribution(generator) >= initial_backpack_fullness)
				geny_osobnika->setGene(nr_genu, 0);
			else
				geny_osobnika->setGene(nr_genu, 1);
		}	
	}
}

CGenotyp CGeneticAlgorithm::najlepsze_rozwiazanie_w_populacji(CError* error_type) {

	if (population == nullptr) {
		if (error_type != nullptr) *error_type = CError::dereferencja_nullptr;
		return CGenotyp(0); // pusty genotyp
	}

	int indeks_kandydata = 0;
	int max_wartosc = 0;
	
	for (int i = 0; i < population_size; i++) {
		if (population[i].getValue() > max_wartosc) {
			indeks_kandydata = i;
			max_wartosc = population[i].getValue();
		}
	}
	
	return *population[indeks_kandydata].getGenotyp();
}

void CGeneticAlgorithm::update_values(CPrzedmiot* wagi_i_wartosci, int max_weight) {
	// oblicz i ustaw przystosowanie osobników w populacji 
	for (int i = 0; i < population_size; i++) {
		population[i].setValue(population[i].fitness(wagi_i_wartosci, max_weight));
	}
}

void CGeneticAlgorithm::krzyzuj_populacje() {

	//std::default_random_engine generator(SEED); // do testow
	std::random_device rd; 
	std::default_random_engine generator(rd());
	
	std::uniform_int_distribution<int> elem_distribution(0, population_size - 1);
	std::uniform_real_distribution<> float_distribution(0.0, 1.0);
	std::uniform_int_distribution<> pivot_distribution(0, genotype_size - 1);

	CIndividual* new_population = new CIndividual[population_size];

	CIndividual* candidate1 = nullptr;
	CIndividual* candidate2 = nullptr;
	CIndividual* parent1 = nullptr;
	CIndividual* parent2 = nullptr;

	CIndividual* children = nullptr;

	/* dwukrotnie wylosuj po dwa osobniki z populacji.
		lepiej dostosowany z ka¿dej pary zostaje rodzicem.
		'new_population' to tablica na ich dzieci
		pary s¹ wybierane do zape³nienia siê tablicy 'new_population'.
	*/

	for (int i = 0; i * 2 + 1 < population_size; i++) {
		
		// wybór 1go rodzica
		candidate1 = &(population[elem_distribution(generator)]);
		candidate2 = &(population[elem_distribution(generator)]);

		if (candidate1->getValue() > candidate2->getValue())
			parent1 = candidate1;
		else
			parent1 = candidate2;

		// wybór 2go rodzica
		candidate1 = &(population[elem_distribution(generator)]);
		candidate2 = &(population[elem_distribution(generator)]);

		if (candidate1->getValue() > candidate2->getValue())
			parent2 = candidate1;
		else
			parent2 = candidate2;

		// krzyzowanie zachodzi
		if (float_distribution(generator) < crossover_probability) {
			
			children = parent1->crossover(*parent2, pivot_distribution(generator));
			new_population[2 * i] = children[0];
			new_population[2 * i + 1] = children[1];
			
			delete[] children;
		}
		// krzyzowanie nie zachodzi - rodzice s¹ kopiowani
		else {
			new_population[2 * i] = *parent1;
			new_population[2 * i + 1] = *parent2;
		}	
	}

	// jeœli 'new_population' ma nieparzyst¹ liczbê elementów,
	// to na ostatnie miejsce jest kopiowany ostatnio wybrany rodzic
	// a jeœli takowego nie ma, pierwszy element 'starej' populacji
	if (population_size % 2 != 0) {
		if(parent2!= nullptr)
			new_population[population_size - 1] = * parent2;
		else
			new_population[population_size - 1] = population[0];
	}

	delete[] population;
	population = new_population;
}

void CGeneticAlgorithm::mutuj_populacje() {

	//std::default_random_engine generator(CGeneticAlgorithm::SEED);
	std::random_device rd;
	std::default_random_engine generator(rd());
	
	std::uniform_real_distribution<double> float_distribution(0.0, 1.0);

	for (int i = 0; i < population_size; i ++) {
		// sprawdzenie, czy mutacja zachodzi dla osobnika:
		if (float_distribution(generator) < mutation_probability)
			population[i].mutation(mutation_probability);
	}
}

CGenotyp CGeneticAlgorithm::optimize(CKnapsackProblem * problem, CError* error_type) {

	if (problem == nullptr) {
		if (error_type != nullptr) *error_type = CError::dereferencja_nullptr;
		return CGenotyp(0); // pusty genotyp
	}

	genotype_size = problem->getItemCount();
	population_size = 2 * problem->getItemCount();

	int licznik_iteracji = iteration_count;
	
	generuj_populacjê();

	while (!kryterium_zatrzymania(licznik_iteracji)) {

		update_values(problem->getPrzedmioty(), problem->getMaxWeight());
		krzyzuj_populacje();
		mutuj_populacje();

		licznik_iteracji--;
	} 

	update_values(problem->getPrzedmioty(), problem->getMaxWeight());

	return najlepsze_rozwiazanie_w_populacji();
}

void CGeneticAlgorithm::drukuj_populacje() {
	if (!population) return;

	for (int i = 0; i < population_size; i++) {
		population[i].getGenotyp()->print_genotype();
		std::cout << " , wartosc = " << population[i].getValue() << '\n';
	}
}

