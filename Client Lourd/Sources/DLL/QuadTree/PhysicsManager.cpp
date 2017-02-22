////////////////////////////////////////////////
/// @file   PhysicsManager.cpp
/// @author The New Ballers
/// @date   2016-01-12
///
/// @ingroup QuadTree
////////////////////////////////////////////////

#include <ArbreRenduINF2990.h>
#include "PhysicsManager.h"
#include "FacadeModele.h"


////////////////////////////////////////////////////////////////////////
/// @fn PhysicsManager::PhysicsManager()
/// @brief Constructeur
/// @return Aucun, constructeur
////////////////////////////////////////////////////////////////////////
PhysicsManager::PhysicsManager()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn PhysicsManager::~PhysicsManager()
/// @brief Destructeur
/// @return Aucun, destructeur
////////////////////////////////////////////////////////////////////////
PhysicsManager::~PhysicsManager()
{

}


///////////////////////////////////////////////////////////////////////////////
/// @fn void PhysicsManager::traiterCollisions(float temps)
/// @brief Effectue la detection et reaction pour les collisions entre tous les noeuds.
/// @remark Les listes doivent etre construites et la liste de billes doit etre tenue a jour.
/// @param[in] temps : temps entre les calculs de physique.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void PhysicsManager::traiterCollisions(float temps)
{
	// Récupérer l'arbre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	bool miseAJourListeBillesRequise = false;

	// Pour chaque bille, 
	for (NoeudAbstrait* bille : listeBilles_)
	{
		// Obtenir une liste de noeuds a verifier avec la bille courante.
		std::vector<NoeudAbstrait*> noeudsAverifier;

		noeudsAverifier = listeNoeuds_;
		noeudsAverifier.push_back(arbre->chercher(0));

		bille->assignerImpossible(false);
		// Et la table :

		// Faire la detection et reaction pour chaque noeud de noeudsAVrifier
		for (NoeudAbstrait* noeudAVerifier : noeudsAverifier)
		{
			// Detecter les collisions entre le noeud et la bille
			aidecollision::DetailsCollision detail = noeudAVerifier->detecterCollisions(bille);

			if (detail.type != aidecollision::COLLISION_AUCUNE)
			{
				// Traiter (reagir à) la collision.
				noeudAVerifier->traiterCollisions(detail, bille);
				if (noeudAVerifier->obtenirType() == "trou") // MODIF
				{
					miseAJourListeBillesRequise = true;
					FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->retirerBille(bille->getColorShift());
					arbre->effacer(bille);
					break;                                   // MODIF
				}
			}
		}
		mettreAJourListeNoeuds();          // MODIF (Juste updater listeNoeuds_ pour pas avoir le assert de vector.
	}// Fin du for (NoeudAbstrait* bille : listeBilles_)

	if (miseAJourListeBillesRequise)
		mettreAJourListeBillesEtNoeuds(); // Cette methode est appelee a chaque frame dand animer(temps)
	// mais si on trouve toutes les places ou elle doit etre appelee, 
	// on n'aura plus besoin de l'appeler a chaque frame et donc ici serait le bon endroit pour l'appeler quand on a efface une bille.
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void PhysicsManager::updateForcesExternes() const
/// @brief Pour chaque bille, calcule la somme des forces exercees par les portails 
///		   sur celle-ci. Si la distance entre la bille et le portail est plus grande
///		   qu'une certaine valeur, la force de ce portail n'est pas comptee.
///		   Cette fonction considere aussi si un bille vien de sortir d'un portail.
///		   Tant que la bille ne s'est pas assez eloignee du portail d'ou elle est 
///		   apparue, ce portail de l'affectera pas.
/// @remark Les listes doivent etre construites et la liste de billes doit etre tenue a jour.
///		   (Pour l'instant elles sont mises a jour a chaque frame donc pas de problemes ici.)
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void PhysicsManager::updateForcesExternes()
{
	for (NoeudAbstrait* bille : listeBilles_)
	{
		glm::dvec2 sommeDesForces{ 0, 0 };
		glm::dvec2 positionBille = glm::dvec2{ bille->obtenirPositionRelative() };
		for (NoeudAbstrait* noeud : listeNoeuds_)
		{
			if (noeud->obtenirType() == "portail")
			{
				glm::dvec2 positionPortail = glm::dvec2{ noeud->obtenirPositionRelative() };
				double distance = glm::length(positionPortail - positionBille);
				if (distance < 3 * noeud->obtenirVecteursEnglobants()[0].x) // Constante a determiner en fonction du scale du portail
				{
					if (bille->obtenirPortailDorigine() != noeud)
					{
						glm::dvec2 force = MASSE_NOEUD_PORTAIL * MASSE_NOEUD_BILLE / distance * glm::normalize(positionPortail - positionBille);
						sommeDesForces += force;
					}
				}
				if (distance > 20 && noeud == bille->obtenirPortailDorigine())
					bille->assignerPortailDorigine(nullptr);
			}
		}
		bille->assignerForcesExternes(glm::dvec3{ sommeDesForces.x, sommeDesForces.y, 0 });
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void PhysicsManager::mettreAJourListeNoeuds()
/// @brief Met a jour la liste des noeuds a verifier pour les collisions.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void PhysicsManager::mettreAJourListeNoeuds()
{
	// Récupérer l'arbre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	listeNoeuds_.clear();
	for (unsigned int i = 0; i < arbre->getEnfant(0)->obtenirNombreEnfants(); i++)
	{
		NoeudAbstrait* noeud = arbre->getEnfant(0)->getEnfant(i);
		if (noeud->obtenirType() != "generateurbille")
			listeNoeuds_.push_back(noeud);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void PhysicsManager::mettreAJourListeBillesEtNoeuds()
/// @brief Met a jour la liste des billes
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void PhysicsManager::mettreAJourListeBillesEtNoeuds()
{
	// Récupérer l'arbre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	listeBilles_.clear();
	listeNoeuds_.clear();
	for (unsigned int i = 0; i < arbre->getEnfant(0)->obtenirNombreEnfants(); i++)
	{
		NoeudAbstrait* noeud = arbre->getEnfant(0)->getEnfant(i);
		listeNoeuds_.push_back(noeud);

		if (noeud->obtenirType() == "bille")
			listeBilles_.push_back(noeud);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void PhysicsManager::obtenirListeBilles()
/// @brief Retourne la liste des billes
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> PhysicsManager::obtenirListeBilles() const
{
	return listeBilles_;
}