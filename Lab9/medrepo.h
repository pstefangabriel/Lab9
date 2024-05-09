#pragma once
#include "Medicament.h"
#include <vector>
#include <map>
#include <string>
#include <ostream>
using std::vector;
using std::string;
using std::ostream;


class RepoAbstract {
public:
	virtual int index(const string& den, const string& prod,
		const string& subst) = 0;
	
	virtual void add(Medicament& m) = 0;

	virtual void del(const string& den, const string& prod,
		const string& subst) = 0;

	virtual void mod(const string& den, const string& prod,
		const string& subst, const Medicament& nou) = 0;

	virtual const Medicament& get(const string& den, const string& prod,
		const string& subst) = 0;

	virtual const vector<Medicament>& get_all() = 0;

	virtual void sterge(const Medicament& med) = 0;

	virtual const Medicament& get(const string& den) = 0;

	virtual ~RepoAbstract() = default;
};


class MedRepo : public RepoAbstract{

private:
	vector<Medicament> all;


public:
	MedRepo() = default;


	// nu permitem copiere de obiecte
	MedRepo(const MedRepo& o) = delete;


	virtual int index(const string& den, const string& prod,
		const string& subst) override;


	virtual void add(Medicament& m) override;


	virtual void del(const string& den, const string& prod,
		const string& subst) override;


	virtual void mod(const string& den, const string& prod,
		const string& subst, const Medicament& nou) override;


	virtual const Medicament& get(const string& den, const string& prod,
		const string& subst) override;


	virtual const Medicament& get(const string& den) override;


	virtual const vector<Medicament>& get_all() override;

	virtual void sterge(const Medicament& med) override;
};


class RepoNou : public RepoAbstract {
private:
	float probabilitate;
	vector<Medicament> all;
	void determinaSanse();
public:
	RepoNou() = default;

	RepoNou(float prob);
	int index(const string& den, const string& prod,
		const string& subst) override;


	void add(Medicament& m) override;


	void del(const string& den, const string& prod,
		const string& subst) override;


	void mod(const string& den, const string& prod,
		const string& subst, const Medicament& nou) override;


	const Medicament& get(const string& den, const string& prod,
		const string& subst) override;


	const Medicament& get(const string& den);


	const vector<Medicament>& get_all();

	void sterge(const Medicament& med) override;
};

void teste_repo();