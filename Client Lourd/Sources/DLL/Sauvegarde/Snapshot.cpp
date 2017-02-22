//////////////////////////////////////////////////////////////////////////////
/// @file MapSnapShot.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////


#include "Snapshot.h"
#include "tinyxml2.h"
#include "../ArbreRenduINF2990.h"
#include <FacadeModele.h>
#include <vector>
#include <FacadeReseau.h>

int Snapshot::tick_ = 0;
int Snapshot::receiveTick_ = 0;

////////////////////////////////////////////////////////////////////////
/// @fn MapSnapShot::MapSnapShot(int tick)
/// @brief Constructeur qui initialise les attributs (version serveur)
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Snapshot::Snapshot()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn MapSnapShot::~MapSnapShot()
/// @brief Destructeur
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Snapshot::~Snapshot()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn MapSnapShot::~MapSnapShot()
/// @brief Obtenir l'information formatée
/// @return Aucun
////////////////////////////////////////////////////////////////////////
std::string Snapshot::toString(ArbreRenduINF2990* arbre)
{
	// Structure XML pour l'envoi du message
	tinyxml2::XMLDocument document;

	// Pour savoir quel est le tick
	tinyxml2::XMLElement* root{ document.NewElement("root") };
	root->SetAttribute("tick", tick_);

	// Incrémenter le tick
	++tick_;

	// L'ajouter au document XML
	document.LinkEndChild(root);

	// Les informations concernant les changements sur les noeuds
	tinyxml2::XMLElement* noeuds{ document.NewElement("Node") };

	// Les informations concernant la partie. Ex. Points, nombre de billes
	tinyxml2::XMLElement* info{ document.NewElement("Info") };

	root->LinkEndChild(noeuds);
	root->LinkEndChild(info);

	const std::string position_ = "Pos";
	const std::string angle_ = "Ang";
	const std::string scale_ = "Sca";
	const std::string color_ = "Col";
	const std::string vitesse_ = "Spe";

	int XMLNoeudSize = 0;
	NoeudAbstrait* noeudCourant = nullptr;

	for (unsigned int i = 0; i < arbre->getEnfant(0)->obtenirNombreEnfants(); ++i)
	{
		noeudCourant = arbre->getEnfant(0)->getEnfant(i);

		if (noeudCourant->obtenirType() == "bille")
		{
			++XMLNoeudSize;

			tinyxml2::XMLElement* element{ document.NewElement(noeudCourant->obtenirType().c_str()) };
			element->SetAttribute("id", noeudCourant->obtenirNumeroUnique());

			tinyxml2::XMLElement* position{ document.NewElement(position_.c_str()) };
			position->SetAttribute("X", noeudCourant->obtenirPositionRelative().x);
			position->SetAttribute("Y", noeudCourant->obtenirPositionRelative().y);
			position->SetAttribute("Z", noeudCourant->obtenirPositionRelative().z);

			tinyxml2::XMLElement* angle{ document.NewElement(angle_.c_str()) };
			angle->SetAttribute("X", noeudCourant->obtenirRotation().x);
			angle->SetAttribute("Y", noeudCourant->obtenirRotation().y);
			angle->SetAttribute("Z", noeudCourant->obtenirRotation().z);

			tinyxml2::XMLElement* color{ document.NewElement(color_.c_str()) };
			color->SetAttribute("Color", noeudCourant->getColorShift());

			tinyxml2::XMLElement* vitesse{ document.NewElement(vitesse_.c_str()) };
			vitesse->SetAttribute("X", noeudCourant->obtenirVitesse().x);
			vitesse->SetAttribute("Y", noeudCourant->obtenirVitesse().y);
			vitesse->SetAttribute("Z", noeudCourant->obtenirVitesse().z);

			element->LinkEndChild(position);
			element->LinkEndChild(angle);
			element->LinkEndChild(color);
			element->LinkEndChild(vitesse);

			noeuds->LinkEndChild(element);
		}
		else if (noeudCourant->obtenirType() == "paletteg" || noeudCourant->obtenirType() == "paletted")
		{
			++XMLNoeudSize;

			tinyxml2::XMLElement* element{ document.NewElement(noeudCourant->obtenirType().c_str()) };
			element->SetAttribute("id", noeudCourant->obtenirNumeroUnique());

			tinyxml2::XMLElement* angle{ document.NewElement(angle_.c_str()) };
			angle->SetAttribute("X", noeudCourant->obtenirRotation().x);
			angle->SetAttribute("Y", noeudCourant->obtenirRotation().y);
			angle->SetAttribute("Z", noeudCourant->obtenirRotation().z);

			element->LinkEndChild(angle);
			noeuds->LinkEndChild(element);
		}
		else if (noeudCourant->obtenirType() == "ressort")
		{
			++XMLNoeudSize;

			tinyxml2::XMLElement* element{ document.NewElement(noeudCourant->obtenirType().c_str()) };
			element->SetAttribute("id", noeudCourant->obtenirNumeroUnique());

			tinyxml2::XMLElement* position{ document.NewElement(position_.c_str()) };
			position->SetAttribute("X", noeudCourant->obtenirPositionRelative().x);
			position->SetAttribute("Y", noeudCourant->obtenirPositionRelative().y);
			position->SetAttribute("Z", noeudCourant->obtenirPositionRelative().z);

			tinyxml2::XMLElement* scale{ document.NewElement(scale_.c_str()) };
			scale->SetAttribute("X", noeudCourant->obtenirAgrandissement().x);
			scale->SetAttribute("Y", noeudCourant->obtenirAgrandissement().y);
			scale->SetAttribute("Z", noeudCourant->obtenirAgrandissement().z);

			element->LinkEndChild(position);
			element->LinkEndChild(scale);
			noeuds->LinkEndChild(element);
		}
	}

	/// Informations de partie
	const std::string player = "Play";
	const std::string point = "Point";
	const std::string nombreBilleCourante = "Courant";
	const std::string nombreBillePerdue = "Perdu";

	auto globalePartie = FacadeModele::obtenirInstance()->obtenirGlobalesPartie();

	for (int i = 0; i < 4; ++i)
	{
		tinyxml2::XMLElement* element{ document.NewElement(player.c_str()) };
		element->SetAttribute("Color", i);

		tinyxml2::XMLElement* points{ document.NewElement(point.c_str()) };
		points->SetAttribute("Value", globalePartie->getPointsJoueur(i));

		tinyxml2::XMLElement* billeCourante{ document.NewElement(nombreBilleCourante.c_str()) };
		billeCourante->SetAttribute("Value", globalePartie->obtenirNombreBilleCourante(i));

		tinyxml2::XMLElement* billePerdu{ document.NewElement(nombreBillePerdue.c_str()) };
		billePerdu->SetAttribute("Value", globalePartie->obtenirNombreDeBillesPerdues(i));

		element->LinkEndChild(points);
		element->LinkEndChild(billeCourante);
		element->LinkEndChild(billePerdu);
		info->LinkEndChild(element);
	}

	// Bonus et malus courant
	tinyxml2::XMLElement* bonus{ document.NewElement("Bonus") };
	tinyxml2::XMLElement* malus{ document.NewElement("Malus") };
	bonus->SetAttribute("Courant", globalePartie->obtenirBonusCourant().c_str());
	malus->SetAttribute("Courant", globalePartie->obtenirMalusCourant().c_str());
	info->LinkEndChild(bonus);
	info->LinkEndChild(malus);

	tinyxml2::XMLPrinter printer;
	document.Accept(&printer);

	return printer.CStr();
}


////////////////////////////////////////////////////////////////////////
/// @fn MapSnapShot::MapSnapShot(std::string data)
/// @brief Constructeur qui initialise les attributs (version client)
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void Snapshot::applySnapshot(std::string data, ArbreRenduINF2990* arbre)
{
	// Structure XML pour l'envoi du message
	tinyxml2::XMLDocument document;

	// Reconstruire le document XML a partir de la string
	document.Parse(data.c_str(), data.size());

	/// Obtenir la racine
	tinyxml2::XMLElement* root = document.RootElement();

	// Obtenir le tick
	int tick = root->FirstAttribute()->IntValue();

	if (tick < receiveTick_)
		return;

	receiveTick_ = tick;

	// Pour track les billes reçus VS ceux qui sont présents dans l'arbre de rendu
	std::vector<int> billesRecues;

	// Récupérer la liste des numero de billes courantes
	std::vector<int> billesCourantes;

	if (arbre->getEnfant(0) == nullptr)
		return;

	for (unsigned int i = 0; i < arbre->getEnfant(0)->obtenirNombreEnfants(); ++i)
	{
		if (arbre->getEnfant(0)->getEnfant(i)->obtenirType() == "bille")
			billesCourantes.push_back(arbre->getEnfant(0)->getEnfant(i)->obtenirNumeroUnique());
	}

	if (root != nullptr)
	{
		// Aller chercher les informations sur les noeuds et les informations de partie
		tinyxml2::XMLElement* noeuds { root->FirstChildElement() };
		tinyxml2::XMLElement* info{ noeuds->NextSiblingElement() };

		// Element XML courant
		tinyxml2::XMLElement* currentElement = noeuds->FirstChildElement();

		if (currentElement == nullptr)
			return;

		// Noeud auquel il faut appliquer les changements
		NoeudAbstrait* node = nullptr;

		const char* X = "X";
		const char* Y = "Y";
		const char* Z = "Z";
		bool hasNext = true;
		int id = 0;

		/// Traiter premièrement tous les noeuds
		while (hasNext)
		{
			std::string name = currentElement->Value();
			id = currentElement->FirstAttribute()->IntValue();
			node = arbre->obtenirSelonNumeroUnique(id);

			if (node != nullptr)
			{
				if (name == "bille")
				{
					billesRecues.push_back(id);
					const tinyxml2::XMLElement* position{ currentElement->FirstChildElement() };
					const tinyxml2::XMLElement* angle{ position->NextSiblingElement() };
					const tinyxml2::XMLElement* color{ angle->NextSiblingElement() };
					const tinyxml2::XMLElement* vitesse{ color->NextSiblingElement() };

					node->assignerPositionRelative({
						position->FindAttribute(X)->DoubleValue(),
						position->FindAttribute(Y)->DoubleValue(),
						position->FindAttribute(Z)->DoubleValue() });

					node->assignerRotationHard({
						angle->FindAttribute(X)->DoubleValue(),
						angle->FindAttribute(Y)->DoubleValue(),
						angle->FindAttribute(Z)->DoubleValue() });

					node->assignerVitesse({
						vitesse->FindAttribute(X)->DoubleValue(),
						vitesse->FindAttribute(Y)->DoubleValue(),
						vitesse->FindAttribute(Z)->DoubleValue() });
				}
				else if (name == "paletteg" || name == "paletted")
				{
					const tinyxml2::XMLElement* angle{ currentElement->FirstChildElement() };

					node->assignerRotationHard({
						angle->FindAttribute(X)->DoubleValue(),
						angle->FindAttribute(Y)->DoubleValue(),
						angle->FindAttribute(Z)->DoubleValue() });
				}
				else if (name == "ressort")
				{
					const tinyxml2::XMLElement* position{ currentElement->FirstChildElement() };
					const tinyxml2::XMLElement* scale{ position->NextSiblingElement() };

					node->assignerPositionRelative({
						position->FindAttribute(X)->DoubleValue(),
						position->FindAttribute(Y)->DoubleValue(),
						position->FindAttribute(Z)->DoubleValue() });

					node->assignerEchelle({
						scale->FindAttribute(X)->DoubleValue(),
						scale->FindAttribute(Y)->DoubleValue(),
						scale->FindAttribute(Z)->DoubleValue() });
				}
			}
			else if (node == nullptr && name == "bille")
			{
				const tinyxml2::XMLElement* color{ currentElement->FirstChildElement()->NextSiblingElement()->NextSiblingElement() };
				int colorshift = color->FirstAttribute()->IntValue();

				if (FacadeModele::obtenirInstance()->preparerBille(colorshift))
				{
					GlobalesPartie::compteurNumeroBille = id;
					FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->ajouterBille(colorshift);
					FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->afficherBille(colorshift);
				}
			}

			currentElement = currentElement->NextSiblingElement();

			if (currentElement == nullptr)
				hasNext = false;
		}
		
		// Synchronisation des billes
		bool found = false;
		int nodeToDelete = 0;

		for (unsigned int i = 0; i < billesCourantes.size(); ++i)
		{
			for (unsigned int j = 0; j < billesRecues.size(); ++j)
			{
				if (billesCourantes[i] == billesRecues[j])
					found = true;
			}
			if (!found)
			{
				NoeudAbstrait* noeud = arbre->obtenirSelonNumeroUnique(billesCourantes[i]);
				FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->retirerBille(noeud->getColorShift());
				arbre->effacer(noeud);
			}
			found = false;
		}

		//////////////////////////////
		// Informations de partie
		//////////////////////////////
		currentElement = info->FirstChildElement();
		int colorshiftPlayer = FacadeReseau::obtenirInstance()->obtenirNumeroJoueur() - 1;
		auto informations = FacadeModele::obtenirInstance()->obtenirGlobalesPartie();

		for (int i = 0; i < 4; ++i)
		{
			const tinyxml2::XMLElement* point{ currentElement->FirstChildElement() };
			const tinyxml2::XMLElement* billeCourante{ point->NextSiblingElement() };
			const tinyxml2::XMLElement* billePerdu{ billeCourante->NextSiblingElement() };

			int points = point->FirstAttribute()->IntValue();
			int courant = billeCourante->FirstAttribute()->IntValue();
			int perdu = billePerdu->FirstAttribute()->IntValue();
			informations->setPointsJoueur(points, i);
			informations->assignerBillesCourantes(courant, i);
			informations->assignerBillesPerdues(perdu, i);

			currentElement = currentElement->NextSiblingElement();
		}

		/// Traiter les bonus et malus
		if (informations->obtenirBonusCourant() == "")
		{
			informations->assignerTempsAffichageBonus(std::clock());
			informations->assignerBonusCourant(currentElement->FirstAttribute()->Value());
		}
		if (informations->obtenirMalusCourant() == "")
		{
			currentElement = currentElement->NextSiblingElement();
			informations->assignerTempsAffichageMalus(std::clock());
			informations->assignerMalusCourant(currentElement->FirstAttribute()->Value());
		}
	}
}