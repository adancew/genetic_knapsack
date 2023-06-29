#include <iostream>

#include "CIndividual.h"
#include "CGeneticAlgorithm.h"


CIndividual::CIndividual(CGenotyp g) {
	genotype = new CGenotyp(g);
	value = 0;
	
}

CIndividual::CIndividual() {
	genotype = new CGenotyp();
	value = 0;

}

CIndividual::CIndividual(const CIndividual& cOther) {
	genotype = new CGenotyp(* cOther.genotype);
	value = cOther.value;
}

CIndividual::~CIndividual() {
	delete genotype;
}

CIndividual& CIndividual::operator=(const CIndividual& cOther) {
	if (genotype != cOther.genotype) {
		delete genotype;
		genotype = new CGenotyp(*cOther.genotype);
		value = cOther.value;
	}
	return *this;
}

CGenotyp* CIndividual:: getGenotyp() { 
	return genotype; 
}


CIndividual* CIndividual::crossover(CIndividual& cOther, int pivot, CError* error_type) {
	if (genotype->getSize() != cOther.genotype->getSize()) {
		if (error_type) *error_type = CError::niedopasowany_parametr;
		return nullptr;
	}

	if (pivot < 0) {
		if (error_type) *error_type = CError::indeks_poza_zasiegiem;
		return nullptr;
	}

	int genotype_size = genotype->getSize();
	int temp_for_swapping;

	CIndividual child_one(*this);
	CIndividual child_two(cOther);

	for (int i = pivot; i < genotype_size; i++) {
		temp_for_swapping = child_one.genotype->getGene(i);
		child_one.genotype->setGene(i, child_two.genotype->getGene(i));
		child_two.genotype->setGene(i, temp_for_swapping);
	}

	CIndividual* results = new CIndividual[NUM_OF_CHILDREN]{ child_one, child_two };

	return results;
}

int CIndividual::fitness(CPrzedmiot * lista_wag_i_wartosci, int max_weight) {

	int suma_mas = 0;
	int suma_wartosci = 0;
	int* geny_ptr = genotype->getGenes();

	for (int i = 0; i < genotype->getSize(); i++) {
		suma_mas += (*geny_ptr) * lista_wag_i_wartosci[i].GetWeight();
		suma_wartosci += (*geny_ptr) * lista_wag_i_wartosci[i].GetValue();

		geny_ptr++;
	}

	if (suma_mas > max_weight) return 0;
	else return suma_wartosci;
}

void CIndividual::mutation(double prawdop_mutacji) {
	//std::default_random_engine generator(CGeneticAlgorithm::SEED); // do testow
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_real_distribution<double> float_distribution(0.0, 1.0);

	int rozmiar_genotypu = genotype->getSize();

	double p;
	// dla ka¿dego genu w genotypie osobnika:
	for (int j = 0; j < rozmiar_genotypu; j++) {
		// sprawdzenie, czy mutacja zachodzi dla genu:
		p = float_distribution(generator);

		if (p < prawdop_mutacji) {
			genotype->swapGene(j);
		}
	}
}

void CIndividual::setValue(int i)  throw (std::invalid_argument) {
	if (i < 0) throw std::invalid_argument("incorrect value");

	value = i;
}

int CIndividual::getValue() {
	return value;
}