////////////////////////////////////////////////
/// @file   VisiteurDeselectionnerTout.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////
#include "VisiteurConstruireListes.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"


////////////////////////////////////////////////////////////////////////
/// @fn VisiteurDeselectionnerTout::VisiteurDeselectionnerTout()
/// @brief Constructeur par defaut (vide).
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
VisiteurConstruireListes::VisiteurConstruireListes(std::vector<std::vector<NoeudPaletteG*>>& palettesGauches, std::vector<std::vector<NoeudPaletteD*>>& palettesDroite)
{
	palettesGauches_ = &palettesGauches;
	palettesDroites_ = &palettesDroite;

	if ((*palettesGauches_).size() == 0)
	{
		std::vector<NoeudPaletteG*> gauche;
		(*palettesGauches_).push_back(gauche);	// Palette de colorshift = 0
		(*palettesGauches_).push_back(gauche);	// Palette de colorshift = 1
		(*palettesGauches_).push_back(gauche);	// Palette de colorshift = 2
		(*palettesGauches_).push_back(gauche);	// Palette de colorshift = 3
	}

	if ((*palettesDroites_).size() == 0)
	{
		std::vector<NoeudPaletteD*> droite;
		(*palettesDroites_).push_back(droite);	// Palette de colorshift = 0
		(*palettesDroites_).push_back(droite);	// Palette de colorshift = 1
		(*palettesDroites_).push_back(droite);	// Palette de colorshift = 2
		(*palettesDroites_).push_back(droite);	// Palette de colorshift = 3
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn VisiteurDeselectionnerTout::~VisiteurDeselectionnerTout()
/// @brief Destructeur vide.
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
VisiteurConstruireListes::~VisiteurConstruireListes()
{
	palettesGauches_ = nullptr;
	palettesDroites_ = nullptr;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool VisiteurDeselectionnerTout::traiter(ArbreRenduINF2990* arbre)
/// @brief Cette fonction traite l'arbre de rendu pour visiter ses enfants.
/// @brief Cette fonction retourne true pour dire que l'operation s'est
///		   faite correctement.
/// @param[in] arbre : L'arbre de rendu a traiter.
/// @return Retourne toujours true
////////////////////////////////////////////////////////////////////////
bool VisiteurConstruireListes::traiter(ArbreRenduINF2990* arbre)
{
	// Clean up des anciens palettes
	for (int i = 0; i < (*palettesGauches_).size(); ++i)
	{
		(*palettesGauches_)[i].clear();
	}

	// Clean up des anciens palettes
	for (int i = 0; i < (*palettesDroites_).size(); ++i)
	{
		(*palettesDroites_)[i].clear();
	}

	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurDeselectionnerTout::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu.
///
/// Cette fonction retourne true pour dire que l'operation s'est
/// faite correctement.
///
/// @param[in] table : Le noeud de type Table a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurConstruireListes::traiter(NoeudTable* table)
{
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		table->getEnfant(i)->accepterVisiteur(this);
	}
	return true;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool VisiteurDeselectionnerTout::traiter(NoeudAbstrait* noeud)
/// @brief Ce visiteur deselectionne un noeud.
/// @param[in] noeud : Noeud de l'arbre a traiter.
/// @return Retourne toujours true.
////////////////////////////////////////////////////////////////////////
bool VisiteurConstruireListes::traiter(NoeudAbstrait*)
{
	return true;
}


bool VisiteurConstruireListes::traiter(NoeudPaletteG* noeud)
{
	int colorshift = noeud->getColorShift();

	(*palettesGauches_)[colorshift].push_back(noeud);
	return true;
}

bool VisiteurConstruireListes::traiter(NoeudPaletteD* noeud)
{
	int colorshift = noeud->getColorShift();

	(*palettesDroites_)[colorshift].push_back(noeud);
	return true;
}