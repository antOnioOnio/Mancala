/*
 * BotKaLimon.h
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "Bot.h"

#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_

struct nodo
{
	GameState estado;
	int movimiento;
	int padre;
	int nivel;
	int mejorHijo;
	int valor;
};

class BotKaLimon:Bot {
	
public:
	BotKaLimon();
	~BotKaLimon();

	void initialize();
	string getName();
	Move nextMove(const vector<Move> &adversary, const GameState &state);
	int alfaBeta(vector<nodo> &arbol, int &indiceActual, int alfa, int beta);
	int calcularHeuristica(nodo & nod, vector<nodo> &arbol);

	int calcularHeuristicaFinal(nodo & nod);
};

#endif /* MANUPCBOT_H_ */
