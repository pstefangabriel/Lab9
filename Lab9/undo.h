#pragma once
#include "Medicament.h"
#include "medrepo.h"


class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	//destructorul e virtual pentru a ne asigura ca daca dau delete se apeleaza destructorul din clasa care trebuie
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Medicament medAdaugat;
	MedRepo& rep;
public:
	UndoAdauga(MedRepo& rep, const  Medicament& med) :rep{ rep }, medAdaugat{ med } {}

	void doUndo() override {
		rep.sterge(medAdaugat);
	}
};

class UndoSterge : public ActiuneUndo {
	Medicament medSters;
	MedRepo& rep;
public:
	UndoSterge(MedRepo& rep, const  Medicament& med) :rep{ rep }, medSters{ med } {}
	void doUndo() override {
		rep.add(medSters);
	}
};

class UndoModifica : public ActiuneUndo {
	Medicament medVechi, medCurent;
	MedRepo& rep;
public:
	UndoModifica(MedRepo& repo, const Medicament& med_vechi, const Medicament& med_curent) : rep{repo}, 
		medVechi { med_vechi }, medCurent{ med_curent } {
	}
	void doUndo() override {
		rep.mod(medCurent.get_denumire(), medCurent.get_producator(), medCurent.get_substanta_activa(), medVechi);
	}
};