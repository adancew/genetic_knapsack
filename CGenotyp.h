#pragma once
class CGenotyp{

public:
	CGenotyp();
	
	CGenotyp(int s);

	CGenotyp(const CGenotyp& cOther);

	~CGenotyp();

	CGenotyp& operator=(CGenotyp& cOther);

	int getSize() { return size; }

	int* getGenes() { return genotype; }

	bool swapGene(int i);

	bool setGene(int i, int v);

	int getGene(int i);

	void setSize(int i);

	void print_genotype();

private:
	int size;
	int * genotype;

};

