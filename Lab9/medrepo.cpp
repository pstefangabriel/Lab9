#include "medrepo.h"
#include <assert.h>


int MedRepo::index(const string& den, const string& prod,
	const string& subst) {
	for (int i = 0; i < size(all); i++) {
		if (all[i].get_denumire() == den && all[i].get_producator() == prod
			&& all[i].get_substanta_activa() == subst) {
			return i;
		}
	}
	return -1;
}


void MedRepo::add(Medicament& m) {
	if (index(m.get_denumire(), m.get_producator(),
		m.get_substanta_activa()) == -1) {
		all.push_back(m);
	}
	else {
		throw MedException("Medicamentul exista deja!");
	}
}


const Medicament& MedRepo::get(const string& den, const string& prod,
	const string& subst) {
	for (auto& m : all) {
		if (m.get_denumire() == den && m.get_producator() == prod
			&& m.get_substanta_activa() == subst) {
			return m;
		}
	}
	throw MedException("Nu exista medicamentul cautat!");
}


void MedRepo::del(const string& den, const string& prod,
	const string& subst) { // intreaba daca e ok, daca dai delete e 
	// fara const?
	int pozitia = index(den, prod, subst);
	vector<Medicament>::iterator it = all.begin();
	if (pozitia != -1) {
		all.erase(it + pozitia);
	}
}


void MedRepo::mod(const string& den, const string& prod,
	const string& subst, const Medicament& nou) {

	// trebuia sa folosesc mai mult iteratorul?
	int pozitie = index(den, prod, subst);
	if (pozitie != -1) {
		all[pozitie].set_denumire(nou.get_denumire());
		all[pozitie].set_producator(nou.get_producator());
		all[pozitie].set_substanta_activa(nou.get_substanta_activa());
		all[pozitie].set_pret(nou.get_pret());
		//all[pozitie] = nou;
	}
}


void MedRepo::sterge(const Medicament& med) {
	auto found = std::find_if(all.begin(), all.end(), [med](const Medicament& m) {
		return m.get_denumire() == med.get_denumire() && m.get_producator() == med.get_producator();
		});
	if (found == all.end()) {
		throw MedException{ "Medicament inexistent!!!" };
	}
	//stergem pet
	auto rez = all.erase(found);
}


const vector<Medicament>& MedRepo::get_all(){
	return all;
}


const Medicament& MedRepo::get(const string& den){
	for (auto& m : all) {
		if (m.get_denumire() == den) {
			return m;
		}
	}
	throw MedException("Nu exista medicamentul cautat!");
}


RepoNou::RepoNou(float prob) : probabilitate{ prob } {
	all.clear();
}


void RepoNou::determinaSanse() {
	const auto prob = int(probabilitate * 10);
	const int nr = rand() % 10;
	if (nr <= prob) {
		return;
	}
	throw MedException("Nu a mers\n");
}


int RepoNou::index(const string& den, const string& prod,
	const string& subst) {
	determinaSanse();
	for (int i = 0; i < size(all); i++) {
		if (all[i].get_denumire() == den && all[i].get_producator() == prod
			&& all[i].get_substanta_activa() == subst) {
			return i;
		}
	}
	return -1;
}


void RepoNou::add(Medicament& m) {
	determinaSanse();
	if (index(m.get_denumire(), m.get_producator(),
		m.get_substanta_activa()) == -1) {
		all.push_back(m);
	}
	else {
		throw MedException("Medicamentul exista deja!");
	}
}


const Medicament& RepoNou::get(const string& den, const string& prod,
	const string& subst) {
	determinaSanse();
	for (auto& m : all) {
		if (m.get_denumire() == den && m.get_producator() == prod
			&& m.get_substanta_activa() == subst) {
			return m;
		}
	}
	throw MedException("Nu exista medicamentul cautat!");
}


void RepoNou::del(const string& den, const string& prod,
	const string& subst) { // intreaba daca e ok, daca dai delete e 
	// fara const?
	determinaSanse();
	int pozitia = index(den, prod, subst);
	vector<Medicament>::iterator it = all.begin();
	if (pozitia != -1) {
		all.erase(it + pozitia);
	}
}


void RepoNou::mod(const string& den, const string& prod,
	const string& subst, const Medicament& nou) {

	// trebuia sa folosesc mai mult iteratorul?
	determinaSanse();
	int pozitie = index(den, prod, subst);
	if (pozitie != -1) {
		all[pozitie].set_denumire(nou.get_denumire());
		all[pozitie].set_producator(nou.get_producator());
		all[pozitie].set_substanta_activa(nou.get_substanta_activa());
		all[pozitie].set_pret(nou.get_pret());
		//all[pozitie] = nou;
	}
}


void RepoNou::sterge(const Medicament& med) {
	determinaSanse();
	auto found = std::find_if(all.begin(), all.end(), [med](const Medicament& m) {
		return m.get_denumire() == med.get_denumire() && m.get_producator() == med.get_producator();
		});
	if (found == all.end()) {
		throw MedException{ "Medicament inexistent!!!" };
	}
	//stergem pet
	auto rez = all.erase(found);
}


const vector<Medicament>& RepoNou::get_all() {
	determinaSanse();
	return all;
}


const Medicament& RepoNou::get(const string& den) {
	determinaSanse();
	for (auto& m : all) {
		if (m.get_denumire() == den) {
			return m;
		}
	}
	throw MedException("Nu exista medicamentul cautat!");
}


void teste_repo() {
	// de ce nu modifica si obiectele efectiv
	// gen modifica doar ce e in repo
	// dar in repo se retin referinte deci de ce nu se 
	// modifica si obiectele
	MedRepo rep;
	Medicament med2{ "idk", "smt", "ceva", 21.30 };
	rep.add(med2);
	assert(rep.get_all().size() == 1);
	assert(rep.get("idk", "smt", "ceva").get_pret() == 21.30);

	Medicament med{ "idk1", "sec", "ter", 30.6 };
	Medicament med3{ "idk2", "sec", "ter", 30.6 };
	rep.add(med);
	assert(rep.get_all().size() == 2);

	rep.del(med.get_denumire(), med.get_producator(),
		med.get_substanta_activa());
	assert(rep.get_all().size() == 1);
	//assert(med.get_denumire() == "idk1");

	rep.mod(med2.get_denumire(), med2.get_producator(),
		med2.get_substanta_activa(), med3);
	vector<Medicament> all = rep.get_all();
	assert(all[0].get_denumire() == "idk2");
	//assert(med2.get_denumire() == "idk2");
	try {
		rep.add(med2);
		rep.add(med2);
	}
	catch (MedException& e) {
		assert(e.getMsg() == "Medicamentul exista deja!");
	}
	try {
		rep.get("idk10", "sec", "ter");
	}
	catch (MedException& e) {
		assert(e.getMsg() == "Nu exista medicamentul cautat!");
	}
	try {
		rep.sterge(med2);
		rep.sterge(med2);
	}
	catch (MedException& e) {
		assert(true);
	}
	
	
	Medicament m1{ "Paracetamol", "Biofarm", "Paracetamol", 12 };
	auto rep1 = RepoNou(1);
	rep1.add(m1);
	const auto& l = rep1.get_all();
	assert(l.size() == 1);
	assert(l[0].get_denumire() == "Paracetamol");

	rep1.mod("Paracetamol", "Biofarm", "Paracetamol", med2);
	assert(l[0].get_denumire() == "idk");
	Medicament mm = rep1.get("idk", "smt", "ceva");
	assert(mm.get_producator() == "smt");

	int index = rep1.index("idk", "smt", "ceva");
	assert(index == 0);

	med2 = rep1.get("idk");
	assert(med2.get_producator() == "smt");

	rep1.del("idk", "smt", "ceva");
	const auto& l1 = rep1.get_all();
	assert(l1.size() == 0);
	rep1.add(m1);
	rep1.sterge(m1);

	try {
		rep1.get("sdg", "aaa", "ccc");
		assert(false);
	}
	catch (MedException e) {
		assert(true);
	}
	try {
		rep1.get("dfhasdfh");
		assert(false);
	}
	catch (MedException e) {
		assert(true);
	}
	try {
		rep1.add(med2);
		rep1.add(med2);
		assert(false);
	}
	catch (MedException e) {
		assert(true);
	}
	try {
		rep1.sterge(med3);
		assert(false);
	}
	catch (MedException e) {
		assert(true);
	}

	rep1 = RepoNou((int)0.0);
	try {
		rep1.add(m1);
		assert(false);
	}
	catch (MedException e) {
		assert(true);
	}
}