///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstrait.h
/// @author DGI-INF2990
/// @date 2007-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////////

/** @defgroup Noeud Noeud
*	@ingroup Arbre
*/

#ifndef __ARBRE_NOEUDS_NOEUDABSTRAIT_H__
#define __ARBRE_NOEUDS_NOEUDABSTRAIT_H__

#include<WS2tcpip.h> //include  this header first
#include <windows.h>
#include <GL/gl.h>
#include <string>
#include <vector>

#include "glm\glm.hpp"
#include "Utilitaire.h"

#include "AnimationNoeudsDefine.h"
#include "Modele3d.h"

#include "../../Visiteurs/VisiteurAbstrait.h"
#include "../../Commun/Utilitaire/AideCollision.h"

/// D�clarations avanc�es pour contenir un pointeur vers un mod�le3D et sa liste
/// d'affichage
namespace modele{
	namespace opengl_storage{
		class OpenGL_Liste;
	}
}

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilisee pour creer l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant etre present dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait
{
public:
	/// Constructeur.
	NoeudAbstrait(
		const std::string& type = std::string{ "" }
	);

	/// Destructeur.
	virtual ~NoeudAbstrait();

	/// Obtient le parent de ce noeud.
	inline NoeudAbstrait* obtenirParent();

	/// Obtient le parent de ce noeud (version constante).
	inline const NoeudAbstrait* obtenirParent() const;

	/// Assigne le parent de ce noeud.
	inline void assignerParent(NoeudAbstrait* parent);

	/// Obtient la position relative du noeud.
	inline const glm::dvec3& obtenirPositionRelative() const;

	/// Assigne la position relative du noeud.
	inline void assignerPositionRelative(const glm::dvec3& positionRelative);

	/// Obtient la vitesse du noeud
	inline glm::dvec3 obtenirVitesse() const;

	/// Assigne une vitesse au noeud
	inline void assignerVitesse(glm::dvec3 nouvelleVitesse);

	/// Obtient le type du noeud.
	inline const std::string& obtenirType() const;

	/// ecrit l'etat de l'affichage du du noeud.
	inline void assignerAffiche(bool affiche);

	/// Verifie si le noeud se fait afficher.
	inline bool estAffiche() const;

	/// ecrit l'etat de la selection du noeud.
	inline void assignerSelection(bool selectionne);

	/// Verifie si le noeud est selectionne.
	inline bool estSelectionne() const;

	/// Verifie si la positin du noeud est illegale
	inline bool estImpossible() const;

	/// Assigner le statut de possibilite
	inline void assignerImpossible(bool impossible);

	/// ecrit si le noeud peut etre selectionne ou non.
	inline void assignerEstSelectionnable(bool selectionnable);

	/// ecrit le zoom sur le noeud.
	inline void assignerEchelle(glm::dvec3 scale);

	/// ecrit le rotation sur le noeud.
	inline void assignerRotation(glm::dvec3 rotation);

	/// ecrit le rotation sur le noeud.
	inline void assignerRotationHard(glm::dvec3 rotation){ rotation_ = rotation; };

	/// ecrit le rotation 0,0,0 sur le noeud.
	inline void resetRotation();

	/// Verifie si le noeud est selectionnable.
	inline bool estSelectionnable() const;

	/// ecrit si le noeud peut etre modifie ou non.
	void assignerEstModifiable(bool modif) { modifiable_ = modif; };

	/// Verifie si le noeud est modifiable.
	bool estModifiable() const { return modifiable_; };

	/// ecrit si le noeud peut etre agrandi ou non.
	void assignerEstAjustable(bool ajust) { ajustable_ = ajust; };

	/// Verifie qu'on peut agrandir l'objet
	bool estAjustable() const { return ajustable_; }

	/// Assigne le modele3D et la liste d'affichage du noeud courant
	inline void assignerObjetRendu(modele::Modele3D const* modele, modele::opengl_storage::OpenGL_Liste const* liste);

	// Interface d'un noeud

	/// Calcule la profondeur de l'arbre sous le noeud courant.
	virtual unsigned int calculerProfondeur() const;

	/// Vide le noeud de ses enfants.
	virtual void vider();

	/// Efface le noeud passe en parametre.
	virtual void effacer(const NoeudAbstrait* noeud);

	/// Cherche un noeud par le type (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(const std::string& typeNoeud) const;

	/// Cherche un noeud par le type.
	virtual NoeudAbstrait* chercher(const std::string& typeNoeud);

	/// Cherche un noeud enfant selon l'indice (sur un noeud constant).
	virtual const NoeudAbstrait* chercher(unsigned int indice) const;

	/// Cherche un noeud enfant selon l'indice.
	virtual NoeudAbstrait* chercher(unsigned int indice);

	/// Ajoute un noeud enfant.
	virtual bool ajouter(NoeudAbstrait* enfant);

	/// Obtenir les enfants du noeud si il y a lieu
	virtual NoeudAbstrait* getEnfant(int position);

	/// Obtient le nombre d'enfants du noeud.
	virtual unsigned int obtenirNombreEnfants() const;

	/// Obtient le numero du noeud.
	int getNumero() const { return numeroNoeud_; };

	/// Forcer le compteur a prendre une certaine valeur
	static void changerNumero(int numero) { compteurNoeuds_ = numero; };

	/// Obtient le numero du noeud.
	void setNumero(int numero);

	/// Changer la selection du noeud.
	virtual void inverserSelection();

	/// Selectionne tous les enfants de meme que le noeud.
	virtual void selectionnerTout();

	/// Deselectionne tous les enfants de meme que le noeud.
	virtual void deselectionnerTout();

	/// Verifier si le noeud ou un de ses enfants est selectionne.
	virtual bool selectionExiste() const;

	/// Change le mode d'affichage des polygones.
	virtual void changerModePolygones(bool estForce);

	/// Assigne le mode d'affichage des polygones.
	virtual void assignerModePolygones(GLenum modePolygones);

	/// Affiche le noeud.
	virtual void afficher() const;

	/// Affiche le noeud de maniere concrete.
	virtual void afficherConcret() const;

	/// Appliquer les modificateurs OpenGL sur les objets
	virtual void appliquerAfficher() const;

	/// Anime le noeud.
	virtual void animer(float dt);

	/// Rend le noeud animable ou non le noeud.
	virtual void assignerAnimer(bool animer);

	/// Retourne si le noeud est animer
	virtual bool obtenirAnimer();

	/// Accepter un visiteur
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Obtenir jumeau
	virtual NoeudAbstrait* getTwin();

	/// Ajouter jumeau
	virtual void setTwin(NoeudAbstrait* twin);

	///Obtenir les 4 vecteurs de la boite englobante modifie
	virtual void obtenirVecteursBoite(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4);

	///Obtenir les 4 vecteurs de la boite englobante originale associee au modele.
	virtual void obtenirBoiteModele(glm::dvec3 &v1, glm::dvec3 &v2, glm::dvec3 &v3, glm::dvec3 &v4);

	/// Nouveau format pour les boites englobantes
	virtual std::vector<glm::dvec3> obtenirVecteursEnglobants();

	/// Verifie si un point est dans la boite englobante
	virtual bool pointEstDansBoite(glm::dvec3 point);

	/// Pour la detections des collisions
	virtual aidecollision::DetailsCollision detecterCollisions(NoeudAbstrait* noeud);

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float facteurRebond = 0.8);

	/// Obtenir couleur
	virtual int getColorShift();

	/// Selectionner couleur
	virtual void setColorShift(int colorShift);

	/// Obtenir transparence
	virtual bool getTransparent();

	/// Selectionner transparence
	virtual void setTransparent(bool transparent);

	/// Obtenir rouge
	virtual bool getImpossible();

	/// Selectionner rouge
	virtual void setImpossible(bool impossible);

	/// Obtenir modele
	modele::Modele3D const* obtenirModele() const;

	/// Obtenir agrandissement
	inline const glm::dvec3& obtenirAgrandissement() const;

	/// Obtenir rotation
	inline const glm::dvec3& obtenirRotation() const;

	/// Activer ou desactiver le mode debug.
	virtual void setDebug(bool debug);

	/// Activer ou desactiver le mode spotLight.
	virtual void setSpotLight(bool debug);

	/// Assigner Forces Externes
	inline void assignerForcesExternes(glm::dvec3 forcesExternes);

	/// Assigner l'attribut portailDorigine_ pour tenir compte du portail d'ou on est apparu.
	void assignerPortailDorigine(NoeudAbstrait* portail);

	/// Obtenir l'adresse du pointeurDorigine_ 
	NoeudAbstrait* obtenirPortailDorigine();

	/// trigger lors de l'ajout d'une bille
	virtual void genererBille();

	/// Obtenir le num�ro unique
	virtual int obtenirNumeroUnique() const;

	/// Assigner un num�ro unique
	virtual void assignerNumeroUnique(int numero);

protected:

	/// Si jumeau, autrement nullptr
	NoeudAbstrait* twin_{ nullptr };

	/// Type du noeud.
	std::string      type_;

	/// Mode d'affichage des polygones.
	GLenum           modePolygones_{ GL_FILL };

	/// Position relative du noeud.
	glm::dvec3         positionRelative_;

	/// Rescale relatif du noeud.
	glm::dvec3 		scale_;

	/// Rotation relative du noeud.
	glm::dvec3 		rotation_;

	/// Vrai si on doit afficher le noeud.
	bool             affiche_{ true };

	/// Selection du noeud.
	bool             selectionne_{ false };

	/// Vrai si le noeud est selectionnable.
	bool             selectionnable_{ true };

	/// Determine si l'objet peut etre modifie
	bool             modifiable_{ true };

	/// Determine si l'objet peut etre scale
	bool			ajustable_{ true };

	/// Pointeur vers le parent.
	NoeudAbstrait*   parent_{ nullptr };

	/// Modele 3D correspondant a ce noeud.
	modele::Modele3D const* modele_;

	/// Storage pour le dessin du modele
	modele::opengl_storage::OpenGL_Liste const* liste_ = nullptr;

	/// Compteur d'instances;
	static unsigned int compteurNoeuds_;

	/// Numero d'instance.
	int numeroNoeud_;

	///boite englobante
	utilitaire::BoiteEnglobante boite_;

	/// Couleur du noeud
	int colorShift_;

	/// Transparence
	bool transparent_;

	/// Impossibilite de position
	bool impossible_;

	/// Mode Debug de la bille ou du portail
	bool debug_{ false };

	/// Determine si on affiche ou non l'objet
	bool animer_{ true };

	/// Mode SpotLight de la bille
	bool spotLight_{ false };

	/// Vitesse du noeud utilisee pour l'animation
	glm::dvec3 vitesse_{ 0.0, 0.0, 0.0 };

	/// Forces externes causees par les portails
	glm::dvec3 forcesExternes_{ 0, 0, 0 };

	/// Masse utilisee pour modifier l'effet des forces dans l'animation
	double masse_{ 1 };

	/// Utilisee pour modifier la force de frottement dans l'animation
	double constanteDeFrottement_{ 1 };

	/// Utilise pour tenir compte du fait qu'on est apparu par un portail
	NoeudAbstrait* portailDorigine_{ nullptr };

	/// Num�ro unique pour le jeu en multijoueur
	int numeroUnique_;
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
///
/// Cette fonction retourne le pointeur vers le parent de ce noeud.
///
/// @return Le pointeur vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline NoeudAbstrait* NoeudAbstrait::obtenirParent()
{
	return parent_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
///
/// Cette fonction retourne le pointeur constant vers le parent de ce noeud.
///
/// @return Le pointeur constant vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
{
	return parent_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerParent( NoeudAbstrait* parent )
///
/// Cette fonction assigne le parent du noeud afin qu'il soit possible
/// de remonter dans l'arbre.
///
/// @param[in] parent : Le parent du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerParent(
	NoeudAbstrait* parent
	)
{
	parent_ = parent;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position relative du noeud par rapport
/// a son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirPositionRelative() const
{
	return positionRelative_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerPositionRelative( const glm::dvec3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport a son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerPositionRelative(
	const glm::dvec3& positionRelative
	)
{
	positionRelative_ = positionRelative;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline glm::dvec3 NoeudAbstrait::obtenirVitesse() const
///
/// Permet d'obtenir la vitesse du noeud;
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline glm::dvec3 NoeudAbstrait::obtenirVitesse() const
{
	return vitesse_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerVitesse(glm::dvec3 nouvelleVitesse)
///
/// @param nouvelleVitesse : La nouvelle vitesse a assigner.
///
/// @brief Cette fonction permet d'assigner la vitesse du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerVitesse(glm::dvec3 nouvelleVitesse)
{
	vitesse_ = nouvelleVitesse;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une chaine representante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& NoeudAbstrait::obtenirType() const
{
	return type_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'etat affiche ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerAffiche(bool affiche)
{
	affiche_ = affiche;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estAffiche() const
///
/// Cette fonction retourne l'etat que le noeud se fait afficher ou non.
///
/// @return L'etat affiche ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estAffiche() const
{
	return affiche_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'etat d'etre selectionne ou non du noeud.
///
/// @param selectionne : L'etat selectionne ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerSelection(bool selectionne)
{
	// Un objet non selectionnable n'est jamais selectionne.
	selectionne_ = (selectionne && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEchelle( double scale )
///
/// Cette fonction permet d'assigner un zoom a l'objet.
///
/// @param scale : L'echelle a appliquee.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEchelle(glm::dvec3 scale)
{
	scale_ = scale;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerRotation(glm::dvec3 rotation)
///
/// Cette fonction permet d'assigner une rotation a l'objet.
///
/// @param rotation : La rotation a appliquee.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerRotation(glm::dvec3 rotation)
{
	rotation_ += rotation;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::resetRotation()
///
/// Cette fonction permet d'assigner une rotation a l'objet.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::resetRotation()
{
	rotation_ = { 0.0, 0.0, 0.0 };
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'etat d'etre selectionne ou non du noeud.
///
/// @return L'etat selectionne ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionne() const
{
	// Un objet non selectionnable n'est jamais selectionne.
	return (selectionne_ && selectionnable_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'etat d'etre selectionnable ou non du noeud.
///
/// @param selectionnable : L'etat selectionnable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerEstSelectionnable(bool selectionnable)
{
	selectionnable_ = selectionnable;
	selectionne_ = selectionne_ && selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerImpossible( bool impossible )
///
/// Cette fonction permet d'assigner l'etat d'etre impossible ou non du noeud.
///
/// @param impossible : L'etat impossible ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerImpossible(bool impossible)
{
	impossible_ = impossible;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estImpossible() const
///
/// Cette fonction permet d'obtenir l'etat d'etre impossible ou non du noeud.
///
/// @return bool L'etat impossible ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estImpossible() const
{
	return impossible_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline bool NoeudAbstrait::estSelectionnable() const
///
/// Cette fonction retourne l'etat d'etre selectionnable ou non du noeud.
///
/// @return L'etat selectionnable ou non.
///
////////////////////////////////////////////////////////////////////////
inline bool NoeudAbstrait::estSelectionnable() const
{
	return selectionnable_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D* modele, modele::opengl_storage::OpenGL_Liste* liste)
///
/// Cette fonction assigne l'objet de rendu au modele, c'est-a-dire son
/// modele 3D et sa liste d'affichage
///
/// @param modele : le modele 3D
/// @param liste : la liste d'affichage OpenGL
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerObjetRendu(modele::Modele3D const* modele, modele::opengl_storage::OpenGL_Liste const* liste)
{
	modele_ = modele;
	liste_ = liste;
	boite_ = utilitaire::calculerBoiteEnglobante(*modele_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirAgrandissement() const
///
/// Cette fonction retourne l'agrandissement du noeud par rapport
/// a son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirAgrandissement() const
{
	return scale_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const glm::dvec3& NoeudAbstrait::obtenirRotation() const
///
/// Cette fonction retourne l'agrandissement du noeud par rapport
/// a son parent.
///
/// @return L'angle de rotation relatif.
///
////////////////////////////////////////////////////////////////////////
inline const glm::dvec3& NoeudAbstrait::obtenirRotation() const
{
	return rotation_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void NoeudAbstrait::assignerForcesExternes(glm::dvec3 forcesExternes)
///
/// @brief Assigne la resultante des forces externes agissant sur l'objet.
///
/// @param[in] forcesExternes Somme des forces creees par les portails.
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
inline void NoeudAbstrait::assignerForcesExternes(glm::dvec3 forcesExternes)
{
	forcesExternes_ = forcesExternes;
}

#endif // __ARBRE_NOEUDS_NOEUDABSTRAIT_H__