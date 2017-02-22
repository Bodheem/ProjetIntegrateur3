//////////////////////////////////////////////////////////////////////////////
/// @file CommsControl.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Client
//////////////////////////////////////////////////////////////////////////////
#include "Utilitaire.h"
#include <sstream>
#include <iostream>
namespace Utilitaire {

	/// Vérifie si une addresse IP est entrée dans un format IPv4 Légal
	bool Utilitaire::addresseCorrecte(std::string addresse)
	{
		auto rest = addresse;
		for (int i = 0; i < 4; i++)
		{
			auto addressSection = rest.substr(0, rest.find_first_of('.'));
			if (!stringBetween(addressSection, 0, 256))
				return false;

			if (rest.length() == addressSection.length())
			{
				if (i < 3)
					return false;
			}
			else
				rest = rest.substr(addressSection.length() + 1);
		}
		return true;
	}

	/// Vérifie si un string contient un chiffre entre deux valeurs fournies
	bool Utilitaire::stringBetween(std::string numeralString, int lowerBound, int upperBound)
	{
		auto stream = std::stringstream(numeralString);
		int stringValue;

		try
		{
			stream >> stringValue;
		}
		catch (...)
		{
			return false;
		}

		if (stringValue < lowerBound || stringValue >= upperBound)
			return false;

		return true;
	}

	/// Sépare un string selon un charactère ou string de délimitation
	std::vector<std::string> Utilitaire::stringSplit(std::string in, std::string delim)
	{
		std::vector<std::string> out;
		std::string rest = in;

		while (!rest.empty())
		{
			std::string stringPart = rest.substr(0, rest.find_first_of(delim));

			if (!stringPart.empty())
				out.push_back(stringPart);

			if (rest.length() == stringPart.length())
				break;

			rest = rest.substr(stringPart.length() + 1);
		}

		return out;
	}

	/// Demande à l'utilisateur d'entrer ses informations de connections dans la console
	void Utilitaire::obtenirInformationsConnection(std::string& addresse, std::string& port)
	{
		do
		{
			while (true)
			{
				addresse = "";

				std::cout << "Veuillez entrer l'addresse IP a laquelle vous voulez vous connecter" << std::endl;
				std::cout << "afin de voter. Veuillez separer l'addresse par des '.' (ex.: 000.000.000.000)" << std::endl << std::endl;
				std::cout << "Entrez 'quitter' pour quitter" << std::endl;
				std::cout << "Addresse: ";

				std::cin >> addresse;

				if (addresse == "quitter")
					return;

				if (Utilitaire::addresseCorrecte(addresse))
					break;

				system("cls");	// I regret nothing

				std::cout << "L'addresse que vous avec rentre est incorrecte. Veuillez la rentrer de nouveau." << std::endl << std::endl;
			}

			system("cls");	// I regret nothing

			port = "5000";
		} while (addresse.empty() || port.empty());
	}

	/// Encryption et decryption
	std::string Utilitaire::encryptDecrypt(std::string toEncrypt) {
		char key[8] = { 'D', 'I', 'C', 'K', 'B', 'U', 'T', 'T' }; //Any chars will work
		std::string output = toEncrypt;

		for (unsigned int i = 0; i < toEncrypt.size(); i++)
			output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

		return output;
	}

}