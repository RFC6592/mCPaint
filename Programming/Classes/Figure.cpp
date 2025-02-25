/** 
* @author EZZAYRI Sami 2226
* @date 9/10/20
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "Ecran.h"
#include "Figure.h"
#include "Couleur.h"
#include "Point.h"

using namespace std;

#include <regex>
#include "./Exception/BaseException.h"
#include "./Template/Iterateur.h"
#include "./Template/Liste.h"
#include <fstream>
/**
* @brief Initialisation du compteur 
*/
int Figure::compteur = 0; // Initialisation c'est à ce stade que l'emplacement memoire est reserve

/** 
* @brief Methode static qui se charge de retourner le nb d'objets de type Couleur 
* @return int compteur
*/
int Figure::getCompteur(){ return compteur; }
	




/**
* @brief Constructeur par defaut
* @param void
* @return void 
*/
Figure::Figure()
{
	setId("F_0");
	setPosition(Point());

	this->pCouleur = NULL;
   compteur++;
}



/** 
* @brief Constructeur d'initialisation avec 3 parametres 
* @param const char *pId
* @param const Point &position
* @param const Couleur *pCouleur
*/
Figure::Figure(const char *pId, const Point &position, const Couleur *pCouleur)
{

	setId(pId);
	setPosition(position);

	this->pCouleur = NULL;
	setCouleur(pCouleur);
	compteur++;
}



/** 
* @brief Constructeur d'initialisation avec 2 parametres 
* @param const char *newPid
* @param const Point &position
*/
Figure::Figure(const char *newPid, const Point &position)
{
	compteur++;
	if(newPid == NULL) {
		throw invalid_argument("Erreur pId !");
	} else {
		compteur++;
		setId(newPid);	
		setPosition(position);
		this->pCouleur = NULL;
	}
	
}



/**
* @brief Constructeur de copie de la classe Figure 
*/
Figure::Figure(const Figure &f) 
{
	
	setId(f.getId());
	setPosition(f.getPosition());
	setCouleur(f.getCouleur());

	compteur++;
}



/** 
* @brief Destructeur de la classe Figure 
*/
Figure::~Figure()
{
	if(pId) pId[0] = 0;
	compteur--;
}



/** 
* @brief Setters 
*/
void Figure::setId(const char *newpId)
{
	strcpy(pId, newpId);
}


Figure::Figure(const Point &p, const Couleur *pCouleur)
{
	this->pCouleur = NULL;
	setCouleur(pCouleur);
	setPosition(p);
	compteur++;
}

Figure::Figure(const Point &p)
{
	setPosition(p);
}


/** 
* @brief Methode qui permet de donner une nouvelle position
* @param const Point& pos
*/
void Figure::setPosition(const Point &pos)
{

	this->position = pos;
}



/** 
* @brief Methode qui permet de donner une nouvelle Couleur
* @param const Couleur *pCouleur
*/
void Figure::setCouleur(const Couleur *pCouleur)
{
	this->pCouleur = pCouleur;
}



/** 
* @brief Getters
*/
const char* Figure::getId() const { return pId; }
Point Figure::getPosition() const { return this->position; }
const Couleur* Figure::getCouleur() const { return this->pCouleur; }



/** 
* @brief Afficher l'Id, la position(x,y) et la couleur 
*/
void Figure::Affiche() const
{

	cout << "\x1b[33m> Id : " << getId() << endl;

	getPosition().Affiche();

	if(getCouleur() != NULL) 
		getCouleur()->Affiche();
}



/**
* @brief Methode qui permet de modifier l'objet courant par une autre Figure
* @param const Figure& f
* @return retourne l'objet courant
*/
Figure& Figure::operator=(const Figure& f)
{

	setId(f.pId);
	setPosition(f.position);
	setCouleur(f.pCouleur);
	
	return (*this); // Retourne l'objet courant
}


ostream& operator<<(ostream& s, const Figure& f)
{
	s << f.getId() << " [Position : " << f.position.getX() << ", " << f.position.getY() << "]";
	if(f.pCouleur != NULL) {
		s << "[Couleur : " << f.pCouleur->getRouge() << ", " << f.pCouleur->getVert() << ", " << f.pCouleur->getBleu() << "]"; 
	}
	return s;
}



void Figure::Save(std::ofstream& fichier) const
{
	fichier.write((char *)pId, 5); 
	this->position.Save(fichier); // Encodage de la Position (Point)
	fichier.write((char*)&compteur, sizeof(int));
	
}

void Figure::Load(std::ifstream& fichier)
{
	
	fichier.read((char*)pId, 5);
	position.Load(fichier); // Lecture de la Position
	fichier.read((char*)&compteur, sizeof(int));
	 
}



