////////////////////////////////////////////////
/// @file   ParserXML.cpp
/// @author The New Ballers
/// @date   2016-01-12
///
/// @ingroup Sauvegarde
////////////////////////////////////////////////

#include "ParserXML.h"
#include "Propriete.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
/// @fn ParserXML::enregistrerXML
/// @brief 
/// @return Une instance de la classe
////////////////////////////////////////////////////////////////////////
void ParserXML::enregistrerXML(const std::string& nomFichier, const ArbreRenduINF2990& arbre, const Propriete& propriete)
{
	// Initialiser un document XML pour l'enregistrement
	tinyxml2::XMLDocument document; 
	tinyxml2::XMLElement* root { document.NewElement("root") };
	document.LinkEndChild(root);

	enregistrerPropriete(document, *root, propriete);
	enregistrerArbre(document, *root, arbre);
	
	// Enregistrer le document
	document.SaveFile(nomFichier.c_str());
}


////////////////////////////////////////////////////////////////////////
/// @fn ParserXML::lireXML
/// @brief 
/// @return Une instance de la classe
////////////////////////////////////////////////////////////////////////
bool ParserXML::lireXML(const std::string& nomFichier, ArbreRenduINF2990& arbre, Propriete& propriete)
{
	if (!utilitaire::fichierExiste(nomFichier))
	{
		std::cout << "Le fichier n'existe pas. " << std::endl;
		return false;
	}
	else
	{
		// Initialiser un document XML pour la lecture
		tinyxml2::XMLDocument document; 
		document.LoadFile(nomFichier.c_str());

		tinyxml2::XMLElement* root = document.FirstChildElement("root");

		lirePropriete(document, *root, propriete);
		lireArbre(document, *root, arbre);

		return true;
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn ParserXML::enregistrerArbre
/// @brief 
/// @return Une instance de la classe
////////////////////////////////////////////////////////////////////////
void ParserXML::enregistrerArbre(tinyxml2::XMLDocument& document, tinyxml2::XMLElement& root, const ArbreRenduINF2990& arbre)
{
	const std::string position_ = "Position";
	const std::string angle_ = "Angle";
	const std::string scale_ = "Scale";
	const std::string color_ = "Color";

	// ElementArbre sera la racine
	tinyxml2::XMLElement* elementArbreRendu = document.NewElement(arbre.obtenirType().c_str());

	unsigned int nombreEnfants = arbre.obtenirNombreEnfants();
	NoeudAbstrait* noeudCourant;

	// Traiter les enfants de l'arbre
	for (unsigned int i = 0; i < nombreEnfants; i++)
	{
		noeudCourant = arbre.getEnfant(i);

		// Creer le noeud XML pour les enfants de l'arbre
		tinyxml2::XMLElement* enfant{ document.NewElement(noeudCourant->obtenirType().c_str()) };

		// Si le noeud a des enfants (entre autre, la table)
		if (noeudCourant->getEnfant(0))
		{
			enfant->SetAttribute("nbEnfants", noeudCourant->obtenirNombreEnfants());
			NoeudAbstrait* enfantCourant;

			// Enregistrer les enfants
			for (unsigned int j = 0; j < noeudCourant->obtenirNombreEnfants(); j++)
			{
				enfantCourant = noeudCourant->getEnfant(j);

				// Creer le noeud pour l'enfant de l'enfant
				tinyxml2::XMLElement* petitEnfant{ document.NewElement(enfantCourant->obtenirType().c_str()) };
				petitEnfant->SetAttribute("id", j);

				tinyxml2::XMLElement* position{ document.NewElement(position_.c_str()) };
				position->SetAttribute("X", enfantCourant->obtenirPositionRelative().x);
				position->SetAttribute("Y", enfantCourant->obtenirPositionRelative().y);
				position->SetAttribute("Z", enfantCourant->obtenirPositionRelative().z);

				tinyxml2::XMLElement* scale{ document.NewElement(scale_.c_str()) };
				scale->SetAttribute("X", enfantCourant->obtenirAgrandissement().x);
				scale->SetAttribute("Y", enfantCourant->obtenirAgrandissement().y);
				scale->SetAttribute("Z", enfantCourant->obtenirAgrandissement().z);

				tinyxml2::XMLElement* angle{ document.NewElement(angle_.c_str()) };
				angle->SetAttribute("X", enfantCourant->obtenirRotation().x);
				angle->SetAttribute("Y", enfantCourant->obtenirRotation().y);
				angle->SetAttribute("Z", enfantCourant->obtenirRotation().z);

				tinyxml2::XMLElement* color{ document.NewElement(color_.c_str()) };
				color->SetAttribute("ColorShift", enfantCourant->getColorShift());

				petitEnfant->LinkEndChild(position);
				petitEnfant->LinkEndChild(scale);
				petitEnfant->LinkEndChild(angle);
				petitEnfant->LinkEndChild(color);

				enfant->LinkEndChild(petitEnfant);
			}
		}
		// Lier l'arbre a la table
		elementArbreRendu->LinkEndChild(enfant);
	}

	// Lier la racine au document XML
	root.LinkEndChild(elementArbreRendu);
}


////////////////////////////////////////////////////////////////////////
/// @fn ParserXML::enregistrerPropriete
/// @brief 
/// @return Une instance de la classe
////////////////////////////////////////////////////////////////////////
void ParserXML::enregistrerPropriete(tinyxml2::XMLDocument& document, tinyxml2::XMLElement& root, const Propriete& propriete)
{
	std::map<std::string, std::string> prop = propriete.getPropriete();
	auto iter = prop.begin();

	// Creer le noeud propriete
	tinyxml2::XMLElement* elementPropriete{ document.NewElement("Proprietes") };

	while (iter != prop.end())
	{
		// Creer un element XML pour chaque propriete
		tinyxml2::XMLElement* element{ document.NewElement(iter->first.c_str()) };
		element->SetAttribute("Valeur", iter->second.c_str());
		elementPropriete->LinkEndChild(element);

		++iter;
	}

	root.LinkEndChild(elementPropriete);
}


////////////////////////////////////////////////////////////////////////
/// @fn ParserXML::lireArbre
/// @brief 
/// @return Une instance de la classe
////////////////////////////////////////////////////////////////////////
void ParserXML::lireArbre(tinyxml2::XMLDocument& document, tinyxml2::XMLElement& root, ArbreRenduINF2990& arbre)
{
	// Obtenir l'element "arbreRenduINF2990"
	tinyxml2::XMLElement* elementArbre = root.FirstChildElement(arbre.obtenirType().c_str());

	if (elementArbre != nullptr)
	{
		// Vider l'ancien arbre de rendu
		arbre.vider();

		// Tenter d'obtenir l'element table, puis l'attribut nbEnfants
		const tinyxml2::XMLElement* elementTable{ elementArbre->FirstChildElement("table") };

		if (elementTable != nullptr)
		{
			// Creer la table et l'ajouter a l'arbre de rendu
			NoeudAbstrait* table{ arbre.creerNoeud(elementTable->Name()) };
			arbre.ajouter(table);

			// Recuperer le nombre d'enfants
			int nombreEnfants = elementTable->FirstAttribute()->IntValue();

			// Premier enfant de la table
			const tinyxml2::XMLElement* enfant{ elementTable->FirstChildElement() };

			const char* X = "X";
			const char* Y = "Y";
			const char* Z = "Z";

			// Creer les enfants et les ajouter a la table
			for (int i = 0; i < nombreEnfants; i++)
			{
				// Construire le noeud concret
				NoeudAbstrait* noeudConcret{ arbre.creerNoeud(enfant->Name()) };
				noeudConcret->assignerNumeroUnique(enfant->FirstAttribute()->IntValue());

				const tinyxml2::XMLElement* position{ enfant->FirstChildElement() };
				const tinyxml2::XMLElement* scale{ position->NextSiblingElement() };
				const tinyxml2::XMLElement* angle{ scale->NextSiblingElement() };
				const tinyxml2::XMLElement* color{ angle->NextSiblingElement() };

				// Assigner les proprietes de l'enfant
				noeudConcret->assignerPositionRelative({ 
					position->FindAttribute(X)->DoubleValue(),
					position->FindAttribute(Y)->DoubleValue(),
					position->FindAttribute(Z)->DoubleValue() });

				noeudConcret->assignerEchelle({ 
					scale->FindAttribute(X)->DoubleValue(),
					scale->FindAttribute(Y)->DoubleValue(),
					scale->FindAttribute(Z)->DoubleValue() });

				noeudConcret->assignerRotation({ 
					angle->FindAttribute(X)->DoubleValue(),
					angle->FindAttribute(Y)->DoubleValue(),
					angle->FindAttribute(Z)->DoubleValue() });

				noeudConcret->setColorShift(color->FirstAttribute()->BoolValue());

				// Ajouter l'enfant a la table
				table->ajouter(noeudConcret);

				// Le cas ou le noeud cree est un portail
				if (noeudConcret->obtenirType() == "portail")
				{
					// Nombre actuel d'enfants de la table
					unsigned int enfantsTable = arbre.getEnfant(0)->obtenirNombreEnfants();

					// Interroger l'enfant au dessus de lui
					if (table->chercher(enfantsTable - 2)->obtenirType() == "portail"
						&& table->chercher(enfantsTable - 2)->getTwin() == nullptr)
					{
						// Si c'est un portail et qu'il n'est pas relie, les relier tous les deux
						noeudConcret->setTwin(table->chercher(enfantsTable - 2));
						table->chercher(enfantsTable - 2)->setTwin(noeudConcret);
					}
				}

				// Traiter le frere de droite de l'enfant
				enfant = enfant->NextSiblingElement();
			}
		}

		// Tenter d'obtenir l'element couvercle
		const tinyxml2::XMLElement* elementCouvercle{ elementArbre->LastChildElement("couvercle") };

		if (elementCouvercle != nullptr)
		{
			NoeudAbstrait* couvercle{ arbre.creerNoeud(elementCouvercle->Name()) };
			arbre.ajouter(couvercle);
		}
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn ParserXML::lirePropriete
/// @brief 
/// @return Une instance de la classe
////////////////////////////////////////////////////////////////////////
void ParserXML::lirePropriete(tinyxml2::XMLDocument& document, tinyxml2::XMLElement& root, Propriete& propriete)
{
	// Charger les proprietes de la zone de jeu
	tinyxml2::XMLElement* elementPropriete = root.FirstChildElement("Proprietes");
	tinyxml2::XMLElement* element = elementPropriete->FirstChildElement();
	bool hasNext = true;

	while (hasNext)
	{
		propriete.setPropriete(element->Name(), element->FirstAttribute()->Value());
		element = element->NextSiblingElement();

		if (element == nullptr)
			hasNext = false;
	}
}