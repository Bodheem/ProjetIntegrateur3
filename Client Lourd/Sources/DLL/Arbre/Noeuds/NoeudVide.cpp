///////////////////////////////////////////////////////////////////////////
/// @file NoeudVide.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudVide.h"
#include "Utilitaire.h"
#include<WS2tcpip.h> //include  this header first
#include <windows.h>
#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudBille::NoeudBille(const std::string& typeNoeud)
///
/// @param[in] typeNoeud :  le type du noeud a creer.
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudVide::NoeudVide(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudVide::~NoeudVide()
///
/// Ce destructeur desallouee la liste d'affichage du noeud.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudVide::~NoeudVide()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudVide::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudVide::afficherConcret() const
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudVide::animer(float temps)
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps. Pas d'animation pour ce type de noeud.
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudVide::animer(float)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudVide::accepterVisiteur(VisiteurAbstrait* vis)
///
/// @brief Cette fonction appelle la methode traiter du visiteur.
///
/// @param[in] vis Pointeur sur le visiteur a accepter
///
/// @return reussi (TRUE)
///
////////////////////////////////////////////////////////////////////////
bool NoeudVide::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;
	
	if (vis->traiter(this))
		reussi = true;

	return reussi;
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
