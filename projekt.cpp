#include <iostream>
#include <random>
#include <string>
#include <iomanip>

#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"

#include "Testy.h"

void manual_setting_example();
void low_dimensional_problems();
void large_scale_uncorrelated_problems();
void large_scale_weakly_correlated_problems();
void large_scale_strongly_correlated_problems();
void large_scale_problems();

int main(){
	
	low_dimensional_problems();
	//large_scale_problems();
	
	return 0;
}

void large_scale_uncorrelated_problems() {

	std::cout << "\nlarge scale uncorrelated problems\n\n";

	const int NUM_OF_FILES = 7;

	string filenames[NUM_OF_FILES] = {
		"knapPI_1_100_1000_1",		
		"knapPI_1_200_1000_1",
		"knapPI_1_500_1000_1",		
		"knapPI_1_1000_1000_1",		
		"knapPI_1_2000_1000_1",		
		"knapPI_1_5000_1000_1",
		"knapPI_1_10000_1000_1"
	};

	int answers[NUM_OF_FILES] = {
		9147, 11238, 28857, 54503, 
		110625, 276457, 563647
	};

	double blad_wzgledny = 0;

	CKnapsackProblem problem;

	CGeneticAlgorithm algo(0, 0.5, 0.15);

	algo.set_liczba_iteracji(35);
	algo.set_backpack_fullness(0.01);
	algo.set_population_size(2 * problem.getItemCount());
	
	CError error_code = CError::sukces;

	std::cout << left << setw(25) << "nazwa pliku" <<
		left << setw(10) << "ma byc" <<
		left << setw(10) << "otrzymano" <<
		left << setw(10) << "blad wzgl.\n";

	for (int i = 0; i < 4; i++) {

		problem.wczytaj_z_pliku("large_scale\\" + filenames[i], &error_code);



		if (error_code != CError::sukces) {
			std::cout << left << setw(25) << filenames[i];
			if (error_code == CError::brak_pliku) {
				std::cout << "brak pliku\n";
			}
			else if (error_code == CError::niepoprawny_plik) {
				std::cout << "niepoprawny plik\n";
			}
			else if (error_code == CError::niedopasowany_parametr) {
				std::cout << "niepoprawny plik\n";
			}
			else {
				std::cout << "nieznany blad\n";
			}
			error_code = CError::sukces;
		}
		else {
			CGenotyp wynik = problem.solveWith(algo);
			int val = problem.wartosc_rozw(wynik);
			blad_wzgledny = 100 * (double)(answers[i] - val) / answers[i];

			std::cout << left << setw(25) << filenames[i] <<
				left << setw(10) << answers[i] <<
				left << setw(10) << val <<
				left << setw(6) << fixed << setprecision(2) << blad_wzgledny <<
				"%\n";


		}

	}

				

}

void large_scale_weakly_correlated_problems() {

	std::cout << "\nlarge scale weakly correlated problems\n\n";

	const int NUM_OF_FILES = 7;

	string filenames[NUM_OF_FILES] = {
		"knapPI_2_100_1000_1",
		"knapPI_2_200_1000_1",
		"knapPI_2_500_1000_1",
		"knapPI_2_1000_1000_1",
		"knapPI_2_2000_1000_1",
		"knapPI_2_5000_1000_1",
		"knapPI_2_10000_1000_1"
	};

	int answers[NUM_OF_FILES] = {
		1514, 1634, 4566, 9052,
		18051, 44356, 90204
	};

	double blad_wzgledny = 0;

	CKnapsackProblem problem;

	CGeneticAlgorithm algo(0, 0.5, 0.15);

	algo.set_liczba_iteracji(35);
	algo.set_backpack_fullness(0.01);
	algo.set_population_size(2 * problem.getItemCount());

	CError error_code = CError::sukces;

	std::cout << left << setw(25) << "nazwa pliku" <<
		left << setw(10) << "ma byc" <<
		left << setw(10) << "otrzymano" <<
		left << setw(10) << "blad wzgl.\n";

	for (int i = 0; i < 4; i++) {

		problem.wczytaj_z_pliku("large_scale\\" + filenames[i], &error_code);

		if (error_code != CError::sukces) {
			std::cout << left << setw(25) << filenames[i];
			if (error_code == CError::brak_pliku) {
				std::cout << "brak pliku\n";
			}
			else if (error_code == CError::niepoprawny_plik) {
				std::cout << "niepoprawny plik\n";
			}
			else if (error_code == CError::niedopasowany_parametr) {
				std::cout << "niepoprawny plik\n";
			}
			else {
				std::cout << "nieznany blad\n";
			}
			error_code = CError::sukces;
		}
		else {
			CGenotyp wynik = problem.solveWith(algo);
			int val = problem.wartosc_rozw(wynik);
			blad_wzgledny = 100 * (double)(answers[i] - val) / answers[i];

			std::cout << left << setw(25) << filenames[i] <<
				left << setw(10) << answers[i] <<
				left << setw(10) << val <<
				left << setw(6) << fixed << setprecision(2) << blad_wzgledny <<
				"%\n";
		}
	}
}

void large_scale_strongly_correlated_problems() {

	std::cout << "\nlarge scale strongly correlated problems\n\n";

	const int NUM_OF_FILES = 7;

	string filenames[NUM_OF_FILES] = {
		"knapPI_3_100_1000_1",
		"knapPI_3_200_1000_1",
		"knapPI_3_500_1000_1",
		"knapPI_3_1000_1000_1",
		"knapPI_3_2000_1000_1",
		"knapPI_3_5000_1000_1",
		"knapPI_3_10000_1000_1"
	};

	int answers[NUM_OF_FILES] = {
		2397, 2697, 7117, 14390,
		28919, 72505, 146919
	};

	double blad_wzgledny = 0;

	CKnapsackProblem problem;

	CGeneticAlgorithm algo(0, 0.5, 0.15);

	algo.set_liczba_iteracji(35);
	algo.set_backpack_fullness(0.01);
	algo.set_population_size(2 * problem.getItemCount());

	CError error_code = CError::sukces;

	std::cout << left << setw(25) << "nazwa pliku" <<
		left << setw(10) << "ma byc" <<
		left << setw(10) << "otrzymano" <<
		left << setw(10) << "blad wzgl.\n";


	for (int i = 0; i < 4; i++) {

		problem.wczytaj_z_pliku("large_scale\\" + filenames[i], &error_code);

		if (error_code != CError::sukces) {
			std::cout << left << setw(25) << filenames[i];
			if (error_code == CError::brak_pliku) {
				std::cout << "brak pliku\n";
			}
			else if (error_code == CError::niepoprawny_plik) {
				std::cout << "niepoprawny plik\n";
			}
			else if (error_code == CError::niedopasowany_parametr) {
				std::cout << "niepoprawny plik\n";
			}
			else {
				std::cout << "nieznany blad\n";
			}
			error_code = CError::sukces;
		}
		else {
			CGenotyp wynik = problem.solveWith(algo);
			int val = problem.wartosc_rozw(wynik);
			blad_wzgledny = 100 * (double)(answers[i] - val) / answers[i];

			std::cout << left << setw(25) << filenames[i] <<
				left << setw(10) << answers[i] <<
				left << setw(10) << val <<
				left << setw(6) << fixed << setprecision(2) << blad_wzgledny <<
				"%\n";

		}
	}

}

void large_scale_problems() {
	large_scale_uncorrelated_problems();
	large_scale_weakly_correlated_problems();
	large_scale_strongly_correlated_problems();
}

void low_dimensional_problems() {

	std::cout << "\nlow dimensional problems\n\n";

	const int NUM_OF_FILES = 9;

	string filenames[NUM_OF_FILES] = {
		"f1_l-d_kp_10_269",		// [0 1 1 1 0 0 0 1 1 1 ]
		"f2_l-d_kp_20_878",
		"f3_l-d_kp_4_20",		// [1 1 0 1 ]
		"f4_l-d_kp_4_11",		// [0 1 0 1 ]
		"f6_l-d_kp_10_60",		// [0 0 1 0 1 1 1 1 1 1 ]
		"f7_l-d_kp_7_50",
		"f8_l-d_kp_23_10000",
		"f9_l-d_kp_5_80",		// [1 1 1 1 0 ]
		"f10_l-d_kp_20_879"		// [1 1 1 1 1 1 1 1 1 0 1 1 1 1 0 1 0 1 1 1 ]
	};

	int answers[NUM_OF_FILES] = {
		295, 1024, 35, 23,
		52, 107, 9767, 130, 1025
	};

	double blad_wzgledny = 0;

	CKnapsackProblem problem;

	CGeneticAlgorithm algo(0, 0.5, 0.2);
	algo.set_liczba_iteracji(20);

	CError error_code = CError::sukces;

	std::cout << left << setw(25)<<"nazwa pliku"<<
		left << setw(10)<<"ma byc"<<
		left << setw(10)<<"otrzymano"<<
		left << setw(10)<<"blad wzgl."<<
		left << setw(10) << "\tgenotyp"<<"\n";

	
	for (int i = 0; i < NUM_OF_FILES; i++) {
		
		problem.wczytaj_z_pliku("low-dimensional\\" + filenames[i], &error_code);

		if (error_code != CError::sukces) {
			std::cout << left << setw(25) << filenames[i];
			if (error_code == CError::brak_pliku) {
				std::cout << "brak pliku\n";
			} 
			else if (error_code == CError::niepoprawny_plik) {
				std::cout << "niepoprawny plik\n";
			}
			else if (error_code == CError::niedopasowany_parametr) {
				std::cout << "niepoprawny plik\n";
			}
			else {
				std::cout << "nieznany blad\n";
			}
			error_code = CError::sukces;
		}
		else {
			CGenotyp wynik = problem.solveWith(algo);
			int val = problem.wartosc_rozw(wynik);
			blad_wzgledny = 100 * (double)(answers[i] - val) / answers[i];

			std::cout << left << setw(25) << filenames[i] <<
				left << setw(10) << answers[i] <<
				left << setw(10) << val <<
				left << setw(6) << fixed << setprecision(2) << blad_wzgledny << "%\t";

			wynik.print_genotype();
			std::cout << '\n';
		}
	}


}

void manual_setting_example() {

	// optymalne rozwiazanie: 0011, wartoœæ 6
	int wagi[4] = { 4,5,3,2 };
	int wartosci[4] = { 5,4,3,3 };
	int* w = wagi;
	int* v = wartosci;

	CKnapsackProblem problem(4, 5);
	problem.setValues(v);
	problem.setWeights(w);

	CGeneticAlgorithm algo(10, 0.5, 0.5);
	algo.set_genotype_size(4);

	CGenotyp result = problem.solveWith(algo);
	
	std::cout << "optymalne rozwiazanie: [0 0 1 1] , wartosc: 6\nznalezione rozwiazanie to: ";
	result.print_genotype();
	std::cout << ", wartosc: " << problem.wartosc_rozw(result);

}