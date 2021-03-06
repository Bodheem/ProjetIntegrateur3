////////////////////////////////////////////////////////////////////////////////////
/// @file Camera.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0 
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_CAMERA_H__
#define __UTILITAIRE_CAMERA_H__

#include "glm/glm.hpp"

namespace vue {


	///////////////////////////////////////////////////////////////////////////
	/// @class Camera
	/// @brief Classe repr�sentant une cam�ra dans le monde en 3D.
	///
	/// Cette camera encapsule les diff�rentes op�rations qu'il est possible 
	/// de faire pour d�placer le point de vue de l'observateur � l'int�rieur
	/// de la sc�ne en 3D.
	///
	/// @author Martin Bisson
	/// @date 2006-12-15
	///////////////////////////////////////////////////////////////////////////
	class Camera
	{
	public:
		/// Constructeur � partir des coordonn�es cart�siennes.
		Camera(const glm::dvec3& position,
			const glm::dvec3& pointVise,
			const glm::dvec3& directionHautCamera,
			const glm::dvec3& directionHautMonde,
			float angleTheta,
			float anglePhi
			);

		/// Assignation par copie non-n�cessaire dans le contexte
		Camera& operator=(Camera const&) = delete;

		/// Destructeur virtuel vide.
		virtual ~Camera() {}

		/// Assigner la position de la cam�ra.
		inline void assignerPosition(const glm::dvec3& position);
		/// Assigner le point vis� de la cam�ra.
		inline void assignerPointVise(const glm::dvec3& pointVise);
		/// Assigner la direction du haut de la cam�ra.
		inline void assignerDirectionHaut(const glm::dvec3& directionHaut);
		/// Assigner la distance au point vis�
		inline void assignerDistance(const double newDist);
		/// Assigner l'angle theta
		inline void assignerTheta(const double theta);
		/// Assigner l'angle phi
		inline void assignerPhi(const double phi);

		/// Obtenir la position de la cam�ra.
		inline const glm::dvec3& obtenirPosition() const;
		/// Obtenir le point vis� de la cam�ra.
		inline const glm::dvec3& obtenirPointVise() const;
		/// Obtenir la direction du haut de la cam�ra.
		inline const glm::dvec3& obtenirDirectionHaut() const;
		/// Obtenir l'angle theta en radian de la cam�ra
		inline const double obtenirTheta() const;
		/// Obtenir l'angle phi en radian de la cam�ra
		inline const double obtenirPhi() const;
		/// Obtenir la distance au point vis�
		inline const double obtenirDistance() const;

		/// D�placement dans le plan perpendiculaire � la direction vis�e.
		static void deplacerXY(double deplacementX, double deplacementY);
		/// D�placement dans l'axe de la direction vis�e.
		void deplacerZ(double deplacement, bool bougePointVise);
		/// Rotation de la cam�ra autour de sa position.
		static void tournerXY(double rotationX, double rotationY, bool empecheInversion = true);
		/// Rotation de la position de la cam�ra autour de son point de vis�.
		void orbiterXY(double rotationX, double rotationY, bool empecheInversion = true);
		/// Appliquer la cam�ra orbite en fonction des angles
		void calculerPositionOrbite();



		/// Positionner la cam�ra (appel � gluLookAt) en mode perspective 
		void positionnerOrbite() const;
		/// Positionner la cam�ra (appel � gluLookAt) en mode ortho
		void positionnerOrtho() const;

	private:
		/// La position de la cam�ra.
		glm::dvec3 position_;
		/// La position du point vis� par la cam�ra.
		glm::dvec3 pointVise_;
		/// La direction du haut de la cam�ra.
		glm::dvec3 directionHaut_;
		/// La direction du haut du monde de la cam�ra.
		const glm::dvec3 directionHautMonde_;
		/// Angle phi de la cam�ra pour la vue perspective avec cam�ra orbite
		double phi_;
		/// Angle theta de la cam�ra pour la vue perspective avec cam�ra orbite
		double theta_;
		/// Distance entre la cam�ra et le point vis� par la cam�ra
		double dist_;

		// M�thode priv�e qui v�rifie et remet les angles correctement s'ils d�passent certaines valeurs
		void clampAngles();
	};




	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerPosition(const glm::dvec3& position)
	///
	/// Cette fonction permet d'assigner la position de la cam�ra.
	///
	/// @param[in] position : La nouvelle position de la cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerPosition(const glm::dvec3& position)
	{
		position_ = position;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerPointVise(const glm::dvec3& pointVise)
	///
	/// Cette fonction permet d'assigner le point de vis� de la cam�ra.
	///
	/// @param[in] pointVise : Le nouveau point de vis� de la cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerPointVise(const glm::dvec3& pointVise)
	{
		pointVise_ = pointVise;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerDirectionHaut(const glm::dvec3& directionHaut)
	///
	/// Cette fonction permet d'assigner la direction du haut de la cam�ra.
	///
	/// @param[in] directionHaut : La nouvelle direction du haut de la cam�ra.
	///
	/// @return Aucune.
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerDirectionHaut(const glm::dvec3& directionHaut)
	{
		directionHaut_ = directionHaut;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirPosition() const
	///
	/// Cette fonction permet d'obtenir la position de la cam�ra.
	///
	/// @return La position de la cam�ra.
	///
	////////////////////////////////////////////////////////////////////////
	inline const glm::dvec3& Camera::obtenirPosition() const
	{
		return position_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirPointVise() const
	///
	/// Cette fonction permet d'obtenir le point de vis� de la cam�ra.
	///
	/// @return Le point de vis� de la cam�ra.
	///
	////////////////////////////////////////////////////////////////////////
	inline const glm::dvec3& Camera::obtenirPointVise() const
	{
		return pointVise_;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirDirectionHaut() const
	///
	/// Cette fonction permet d'obtenir la direction du haut de la cam�ra.
	///
	/// @return La direction du haut de la cam�ra.
	///
	////////////////////////////////////////////////////////////////////////
	inline const glm::dvec3& Camera::obtenirDirectionHaut() const
	{
		return directionHaut_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirTheta() const
	///
	/// Cette fonction permet d'obtenir l'angle theta de la cam�ra
	///
	/// @return L'angle theta courant de la cam�ra
	///
	////////////////////////////////////////////////////////////////////////
	inline const double Camera::obtenirTheta() const
	{
		return theta_;
	}
	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirPhi() const
	///
	/// Cette fonction permet d'obtenir l'angle phi de la cam�ra
	///
	/// @return L'angle phi courant de la cam�ra
	///
	////////////////////////////////////////////////////////////////////////
	inline const double Camera::obtenirPhi() const
	{
		return phi_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline const glm::dvec3& Camera::obtenirDistance() const
	///
	/// Cette fonction permet d'obtenir la distance entre la position de la
	/// cam�ra et le point vis�, qui est un attribut de la cam�ra.
	///
	/// @return L'angle theta courant de la cam�ra
	///
	////////////////////////////////////////////////////////////////////////
	inline const double Camera::obtenirDistance() const
	{
		return dist_;
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerDistance(double newDist)
	///
	/// Cette fonction permet de r�gler la distance de la cam�ra par rapport
	/// au point vis�. 
	///
	/// @remark : Assigne la distance uniquement si elle est positive.
	///
	/// @param[in]	newDist		: La nouvelle distance d�sir�e
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerDistance(const double newDist)
	{
		if (newDist > 0.0)
			dist_ = newDist;
		// On fait le calcul des nouvelles coordonn�es
		calculerPositionOrbite();
		// Le calcul de position ne mets pas � jour la cam�ra, il faut donc la repositionner
		positionnerOrbite();
	}

	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerTheta(const double theta)
	///
	/// Cette fonction permet de r�gler l'angle theta de la cam�ra
	///
	/// @param[in]	theta		: Le nouvel angle theta
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerTheta(const double theta)
	{
		theta_ = theta;
	}
	
	////////////////////////////////////////////////////////////////////////
	///
	/// @fn inline void Camera::assignerTheta(const double phi)
	///
	/// Cette fonction permet de r�gler l'angle phi de la cam�ra
	///
	/// @param[in]	phi			: Le nouvel angle phi
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	inline void Camera::assignerPhi(const double phi)
	{
		phi_ = phi;
	}

} // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_CAMERA_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
