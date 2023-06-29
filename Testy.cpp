#include "Testy.h"

#include <iostream>

void Testy::run() {
	//std::cout << "bool test_genotyp() = \t" << test_genotyp() <<  "\n\n";
	//std::cout << "bool test_przedmiot() = \t" << test_przedmiot() <<  "\n\n";
	
	//std::cout << "test_individual_krzyzowanie() = \t" << test_individual_krzyzowanie() <<  "\n\n";
	//std::cout << "bool test_individual() = \t" << test_individual() <<  "\n\n";

	//std::cout << "test_algo_generuj_populacje() = \t" << test_algo_generuj_populacje() <<  "\n\n";
	//std::cout << "bool test_algo_mutuj_populacje() = \t" << test_algo_mutuj_populacje() <<  "\n\n";
	//std::cout << "bool test_algo_najlepsze_rozwiazanie_w_populacji() = \t" << test_algo_najlepsze_rozwiazanie_w_populacji() <<  "\n\n";
	//std::cout << "bool test_algo_najlepsze_rozwiazanie_w_populacji() = \t" << test_algo_najlepsze_rozwiazanie_w_populacji() <<  "\n\n";
	//std::cout << "bool test_algo_optimize() = \t" << test_algo_optimize() <<  "\n\n";
	std::cout << "bool test_algo_krzyzuj_populacje() = \t" << test_algo_krzyzuj_populacje() <<  "\n\n";

	//std::cout << "test_problem_wartosc_rozw() = \t" <<test_problem_wartosc_rozw() <<  "\n\n";
	//std::cout << "bool test_plik() = \t" << test_plik() <<  "\n\n";
	//std::cout << "bool test_problem() = \t" << test_problem() <<  "\n\n";
	
}



bool Testy::test_problem() {

	
	try {
		CKnapsackProblem * r = new CKnapsackProblem(-5, -10);
		delete r;
	}
	catch (std::invalid_argument) {
		std::cout << "\tok\n";
	}

	
	int wagi[4] = { 4,5,3,2 };
	int wartosci[4] = { 5,4,3,3 };
	int* w = wagi;
	int* v = wartosci;
	
	CKnapsackProblem p(4, 5); // liczbaPrzedmiotow, maxWeight
	p.setValues(v);
	p.setWeights(w); 
	
	int zepsute_wagi[4] = { 4,-5,3,2 };
	p.setWeights(zepsute_wagi);

	int zepsute_wartosci[4] = { 4,-5,3,2 };
	CError error_type;
	p.setValues(zepsute_wartosci, &error_type);
	if (error_type == CError::niedopasowany_parametr)
		return true;
	return false;
	
}

bool test_individual_konstr() {
	std::cout<<"\ttest_individual_konstr\n";
		
		// konstr domyslny
	CIndividual* g = new CIndividual();
	delete g;

	// poprawny konstr param.
	CIndividual* h = new CIndividual(CGenotyp(3));
	delete h;

	// niepoprawny konstr param.
	CIndividual* i;
	try {
		i = new CIndividual(CGenotyp(-3));
		delete i;
	}
	catch (std::invalid_argument) {
		return true;
	}

	return false;

}

bool test_individual_setValue() {
	std::cout << "\ttest_individual_setValue\n";

	// poprawny setValue
	CIndividual* j = new CIndividual();
	j->setValue(10);
	delete j;
	// niepoprawny setValue
	try {
		CIndividual* k = new CIndividual();
		k->setValue(-10);
		delete k;
	}
	catch (std::invalid_argument) {
		std::cout << "ok ";
		return true;
	}

	return false;
}

bool Testy::test_individual() {

	
	bool res = (test_individual_konstr() &&
		test_individual_setValue() &&
		test_individual_krzyzowanie());
	
	std::cout << '\n' << res << '\n';

	return res;
}

bool Testy::test_przedmiot() {

	// konstr domyslny
	CPrzedmiot* g = new CPrzedmiot();
	delete g;
	// poprawny konstr param.
	CPrzedmiot* h = new CPrzedmiot(3,4);
	delete h;
	// niepoprawny konstr param.
	CPrzedmiot* i;
	try {
		i = new CPrzedmiot(-3, -4);
		delete i;
	}
	catch (std::invalid_argument) {
		std::cout << "ok ";
	}
	// poprawny setSize
	CPrzedmiot* j = new CPrzedmiot();
	j->SetValue(10);
	j->SetWeight(2);
	delete j;
	// niepoprawny setSize
	try {
		CPrzedmiot* k = new CPrzedmiot();
		k->SetValue(-10);
		delete k;
	}
	catch (std::invalid_argument) {
		std::cout << "ok ";
	}

	return true;


}

bool Testy::test_genotyp() {

	// konstr domyslny
	CGenotyp* g = new CGenotyp();
	delete g;
	// poprawny konstr param.
	CGenotyp* h = new CGenotyp(3);
	delete h;
	// niepoprawny konstr param.
	CGenotyp* i;
	try {
		i = new CGenotyp(-3);
		std::cout << i->getSize() << '\n';
		std::cout << i->getGene(1) << '\n';
		delete i;
	}
	catch (std::invalid_argument) {
		std::cout << "ok ";
	}
	// poprawny setSize
	CGenotyp* j = new CGenotyp();
	j->setSize(10);
	j->setSize(2);
	delete j;
	// niepoprawny setSize
	try{
		CGenotyp* k = new CGenotyp();
		k->setSize(-10);
		delete k;
	}
	catch (std::invalid_argument) {
		std::cout << "ok ";
	}

	return true;

}

bool test_plik1() {

	
	CKnapsackProblem problem; // liczbaPrzedmiotow, maxWeight, wagi, wartosci

	CError error_code;

	problem.wczytaj_z_pliku("nie_istnieje", &error_code);
	

	if (error_code == CError::brak_pliku)
		return true;
	else
		return false;

}

bool test_plik2() {


	CKnapsackProblem problem; // liczbaPrzedmiotow, maxWeight, wagi, wartosci

	CError error_code;

	problem.wczytaj_z_pliku("plik_zly_naglowek", &error_code);


	if (error_code == CError::niepoprawny_plik)
		return true;
	else
		return false;

}

bool test_plik3() {


	CKnapsackProblem problem; // liczbaPrzedmiotow, maxWeight, wagi, wartosci

	CError error_code;

	problem.wczytaj_z_pliku("plik_ujemna_wartosc", &error_code);


	if (error_code == CError::niepoprawny_plik)
		return true;
	else
		return false;

}

bool test_plik4() {


	CKnapsackProblem problem; // liczbaPrzedmiotow, maxWeight, wagi, wartosci

	CError error_code;

	problem.wczytaj_z_pliku("plik_ujemna_waga", &error_code);


	if (error_code == CError::niepoprawny_plik)
		return true;
	else
		return false;

}

bool test_plik5() {


	CKnapsackProblem problem; // liczbaPrzedmiotow, maxWeight, wagi, wartosci

	CError error_code;

	problem.wczytaj_z_pliku("plik_za_krotki", &error_code);


	if (error_code == CError::niepoprawny_plik)
		return true;
	else
		return false;

}

bool test_plik6() {


	CKnapsackProblem problem; // liczbaPrzedmiotow, maxWeight, wagi, wartosci

	CError error_code;

	problem.wczytaj_z_pliku("plik_bez_pary", &error_code);


	if (error_code == CError::niepoprawny_plik)
		return true;
	else
		return false;

}

bool test_plik7() {


	CKnapsackProblem problem; // liczbaPrzedmiotow, maxWeight, wagi, wartosci

	CError error_code = CError::sukces;

	problem.wczytaj_z_pliku("plik", &error_code);

	if (error_code == CError::sukces)
		return true;
	else
		return false;

}

bool Testy::test_plik() {

	bool wyniki [7] = { test_plik1(), test_plik2(), test_plik3(), 
		test_plik4(), test_plik5(), test_plik6(), test_plik7() };
	
	for (int i = 0; i < 7; i++) std::cout << wyniki[i] << ' ';

	return 1;
}

bool Testy::test_algo_optimize() {

	int wagi[4] = { 4,5,3,2 };
	int wartosci[4] = { 5,4,3,3 };
	int* w = wagi;
	int* v = wartosci;
	CKnapsackProblem problem(4, 5);
	problem.setValues(v);
	problem.setWeights(w); // liczbaPrzedmiotow, maxWeight, wagi, wartosci

	CGeneticAlgorithm algo(1.0, 0.5, 4); // rozmiarPopulacji, prawdopKrzyzowania, prawdopMutacji, rozmiarGenotypu

	algo.set_liczba_iteracji(4);

	CGenotyp solution = problem.solveWith(algo);

	algo.drukuj_populacje();

	for (int i = 0; i < 4; i++) {
		std::cout << solution.getGene(i) << ' ';
	}
	

	return true;
}

bool Testy::test_algo_najlepsze_rozwiazanie_w_populacji() {

	int wagi[4] = { 4,5,3,2 };
	int wartosci[4] = { 5,4,3,3 };
	int* w = wagi;
	int* v = wartosci;
	CKnapsackProblem problem(4, 5);
	problem.setValues(v);
	problem.setWeights(w);

	CGeneticAlgorithm algo(1.0, 0.5, 4);

	algo.generuj_populacjê();

	algo.drukuj_populacje();

	algo.update_values(problem.getPrzedmioty(), 10);

	algo.drukuj_populacje();

	return true;

}

bool Testy::test_algo_mutuj_populacje() {

	int wagi[4] = { 4,5,3,2 };
	int wartosci[4] = { 5,4,3,3 };
	int* w = wagi;
	int* v = wartosci;
	CKnapsackProblem problem(4, 5);
	problem.setValues(v);
	problem.setWeights(w);

	CGeneticAlgorithm algo( 1.0, 0.5, 4);

	algo.generuj_populacjê();

	algo.mutuj_populacje();

	algo.drukuj_populacje();

	return true;
}

bool Testy::test_algo_krzyzuj_populacje() {

	int wagi[4] = { 4,5,3,2 };
	int wartosci[4] = { 5,4,3,3 };
	int* w = wagi;
	int* v = wartosci;
	CKnapsackProblem problem(4, 5);
	problem.setValues(v);
	problem.setWeights(w);

	CGeneticAlgorithm algo(5, 1.0, 0.0);
	algo.set_genotype_size(4);

	algo.generuj_populacjê();
	algo.krzyzuj_populacje();
	algo.update_values(problem.getPrzedmioty(), 5);

	algo.drukuj_populacje();

	return true;
}

bool Testy::test_individual_krzyzowanie() {

	
	std::cout << "\ntest 1\n";
	CGenotyp g(4);
	g.setGene(0, 0); g.setGene(1, 0); g.setGene(2, 0); g.setGene(3, 0); // 0 0 0 0

	CGenotyp h(4);
	h.setGene(0, 1); h.setGene(1, 1); h.setGene(2, 1); h.setGene(3, 1); // 1 1 1 1 

	CIndividual osob1(g);
	CIndividual osob2(h);
	
	CIndividual* results;

	results = osob1.crossover(osob2,2); // powstaje 0 0 1 1  oraz 1 1 0 0 

	for (int i = 0; i < 4; i++) { std::cout << results[0].getGenotyp()->getGene(i) << ' '; }
	std::cout << '\n';
	for (int i = 0; i < 4; i++) { std::cout << results[1].getGenotyp()->getGene(i) << ' '; }
	std::cout << '\n';
	std::cout << '\n';
	
	
	std::cout << "\ntest 2\n";

	CIndividual* results2;
	results2 = results[0].crossover(results[1],1); // powstaje 0 1 0 0  oraz 1 0 1 1 

	for (int i = 0; i < 4; i++) { std::cout << results2[0].getGenotyp()->getGene(i) << ' '; }
	std::cout << '\n';
	for (int i = 0; i < 4; i++) { std::cout << results2[1].getGenotyp()->getGene(i) << ' '; }
	std::cout << '\n';
	
	delete[] results;
	delete[] results2;


	// po dodaniu obs³ugi b³êdów:
	std::cout << "\ntest 3\n";
	
	CError krzyzowanie_blad;

	CGenotyp gen1(4); gen1.setGene(0, 1); gen1.setGene(2, 1); // 1010
	CGenotyp gen2(4); gen2.setGene(0, 1); gen2.setGene(1, 1); gen2.setGene(3, 1); // 1101
	CIndividual m1(gen1);
	CIndividual m2(gen2);

	m1.getGenotyp()->print_genotype();	// 1010
	m2.getGenotyp()->print_genotype();  // 1101

	// poprawne krzyzowanie - rozmiar 0 - "zamiana miejsc"
	std::cout << "\ntest 4\n";
	
	results = m1.crossover(m2, 0);
	results[0].getGenotyp()->print_genotype();	// 1101
	results[1].getGenotyp()->print_genotype();  // 1010
	delete[] results;
	
	
	std::cout << "\ntest 5\n";

	// poprawne krzyzowanie - rozmiar 2
	results = m1.crossover(m2, 2);
	results[0].getGenotyp()->print_genotype();	// 1110
	results[1].getGenotyp()->print_genotype();  // 1001
	delete[] results;
	
	
	// niepoprawne krzyzowanie - ujemny pivot
	std::cout << "\ntest 6\n";
	results = m1.crossover(m2, -3, &krzyzowanie_blad);
	if (krzyzowanie_blad == CError::indeks_poza_zasiegiem)
		std::cout << "ok";
	else
		return false;
	delete[] results;

	
	// za duzy pivot - nic sie nie zmienia
	std::cout << "\ntest 7\n";

	krzyzowanie_blad = CError::sukces;
	results = m1.crossover(m2, 5, &krzyzowanie_blad);
	if (krzyzowanie_blad == CError::sukces)
		std::cout << "ok";
	else
		return false;

	results[0].getGenotyp()->print_genotype();	// 1110
	results[1].getGenotyp()->print_genotype();  // 1001
	delete[] results;

	// niepoprawne krzyzowanie - rozne rozmiary genotypu
	std::cout << "\ntest 8\n";

	krzyzowanie_blad = CError::sukces;

	CGenotyp gen3(3); gen1.setGene(0, 1); gen1.setGene(2, 1); // 101
	CIndividual m3(gen3);

	results = m1.crossover(m3, 5, &krzyzowanie_blad);
	if (krzyzowanie_blad == CError::niedopasowany_parametr)
		std::cout << "ok";
	else
		return false;
	delete[] results;
	

	return true;
}

bool Testy::test_algo_generuj_populacje() {

	int wagi[4] = { 4,5,3,2 };
	int wartosci[4] = { 5,4,3,3 };
	int* w = wagi;
	int* v = wartosci;
	CKnapsackProblem problem(4, 5);
	problem.setValues(v);
	problem.setWeights(w);

	CGeneticAlgorithm algo(0.1, 0.1, 4);
	algo.set_genotype_size(4);


	CGenotyp result = problem.solveWith(algo);

	return true;

}

bool Testy::test_problem_wartosc_rozw() {
	/*

		nr	masa	wartosc
		0	4		5
		1	5		4
		2	3		3
		3	2		3

		*/

	int wagi[4] = { 4,5,3,2 };
	int wartosci[4] = { 5,4,3,3 };
	int* w = wagi;
	int* v = wartosci;
	CKnapsackProblem problem(4, 5);
	problem.setValues(v);
	problem.setWeights(w);

	CGenotyp g1(4);
	g1.setGene(0, 0); g1.setGene(1, 0); g1.setGene(2, 0); g1.setGene(3, 0);

	if (problem.wartosc_rozw(g1) != 0) return false;

	g1.setGene(0, 1);
	if (problem.wartosc_rozw(g1) != 5) return false;

	g1.setGene(0, 0); g1.setGene(2, 1); g1.setGene(3, 1);
	if (problem.wartosc_rozw(g1) != 6) return false;

	g1.setGene(0, 1);
	if (problem.wartosc_rozw(g1) != 0) return false;

	return true;
}


