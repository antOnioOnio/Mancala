/*
 * BotKaLimon.cpp
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "BotKaLimon.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

BotKaLimon::BotKaLimon()
{
	// Inicializar las variables necesarias para ejecutar la partida
}

BotKaLimon::~BotKaLimon()
{
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void BotKaLimon::initialize()
{
	// Inicializar el bot antes de jugar una partida
}

string BotKaLimon::getName()
{
	return "BotKaLimon"; // Sustituir por el nombre del bot
}


int BotKaLimon::calcularHeuristica(nodo &nod, vector<nodo> &arbol)
{
	Player yo = this->getPlayer();
	Player rival;
	int heuristica;
	int turnosExtra = 0;
	int fichasMiTablero = 0;

	//nodo aux = nod;

	// identificamos al rival

	if (yo == J1)
	{
		rival = J2;
	}
	else
	{
		rival = J1;
	}


	int semillas = nod.estado.getScore(yo);
	int semillasRival = nod.estado.getScore(rival);
	//int totalSemillas = semillas - semillasRival;
	if ( semillas >=  25){
		return 10000;
	}
	if (semillasRival >= 25){
		return -10000;
	} 
	if (nod.estado.getCurrentPlayer() == arbol[nod.padre].estado.getCurrentPlayer())
	{
		turnosExtra = 10;
	}


	heuristica = (int)(semillas + turnosExtra - semillasRival);

	return heuristica;
}



int BotKaLimon::alfaBeta(vector<nodo> &arbol, int &indiceActual, int alfa, int beta)
{

	Player yo = this->getPlayer();

	// si un nodo hoja calculamos la heuristica 
	if (arbol[indiceActual].estado.isFinalState() || arbol[indiceActual].nivel == 12 )
	{
		arbol[indiceActual].valor = calcularHeuristica(arbol[indiceActual], arbol);
		return arbol[indiceActual].valor;
	}
	
	// generamos hijos
	for (int i = 1; i < 7; i++)
	{

		nodo hijo = arbol[indiceActual];
		hijo.estado = hijo.estado.simulateMove((Move)i);

		if (hijo.estado.isValidState() && arbol[indiceActual].estado.getSeedsAt(arbol[indiceActual].estado.getCurrentPlayer(), (Position)i) > 0)
		{
			hijo.movimiento = i;
			hijo.padre = indiceActual;
			hijo.nivel++;

			arbol.push_back(hijo);

			int pos = arbol.size() - 1;
			int valorHijo = alfaBeta(arbol, pos, alfa, beta);

			if (arbol[indiceActual].estado.getCurrentPlayer() == yo)
			{ // buscamos MAX
				if (alfa < valorHijo)
				{
					alfa = valorHijo;
					arbol[indiceActual].mejorHijo = pos;
					arbol[indiceActual].valor = alfa;
				}
				if (alfa >= beta)
				{
					return beta;
				}
			}
			else
			{ // nodo a minimizar

				if (beta > valorHijo)
				{
					beta = valorHijo;
					// Actualizamos mejor hijo
					arbol[indiceActual].mejorHijo = pos;
					arbol[indiceActual].valor = beta;
					
				}
				if (beta <= alfa)
				{
					return alfa;
				}
			}
		}
	}

	if (arbol[indiceActual].estado.getCurrentPlayer() == yo)
	{ // Nodo MAX
		return alfa;
	}
	else
	{ //Nodo MIN
		return beta;
	}
}

Move BotKaLimon::nextMove(const vector<Move> &adversary, const GameState &state)
{

	Move movimiento = M_NONE;
	vector<nodo> arbol;
	Player yo = this->getPlayer();
	nodo raiz;
	raiz.estado = state;
	raiz.padre = -1;
	raiz.movimiento = 0;
	raiz.nivel = 0;
	raiz.valor = -1;
	raiz.mejorHijo = -1;

	int inf = 999999;
	int min_inf = -999999;
	arbol.push_back(raiz);
	int indice = 0;
	alfaBeta(arbol, indice, min_inf, inf);

	if ((Move)arbol[arbol[0].mejorHijo].movimiento > 0 && (Move)arbol[arbol[0].mejorHijo].movimiento < 7)
	{

		movimiento = (Move)arbol[arbol[0].mejorHijo].movimiento;
	}

	arbol.clear();

	// Implementar aquí la selección de la acción a realizar

	// OJO: Recordatorio. NO USAR  NI .
	// Para salidas por consola (debug) utilizar cerr. Ejemplo:
	// cerr<< "Lo que quiero mostrar"<<endl;

	// OJO: Recordatorio. El nombre del bot y de la clase deben coincidir.
	// En caso contrario, el bot no podrá participar en la competición.
	// Se deberá sustituir el nombre BotKaLimon como nombre de la clase por otro
	// seleccionado por el alumno. Se deberá actualizar también el nombre
	// devuelto por el método getName() acordemente.

	return movimiento;
}
