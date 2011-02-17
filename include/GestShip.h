#ifndef __GESTSHIP_H__
#define __GESTSHIP_H__

/*!
*  \file GestShip.h
*  \brief Ce fichier contient la déclaration de la classe GestShip. C'est la classe qui gère l'ensemble des vaiseaux
*/
#include <Ogre.h>
#include "ShipAbstract.h"

/*!
* \class GestShip
* \brief Classe gérant l'ensemble des vaiseaux via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs à tous les vaiseaux (mise à jour de la position après une frame par exemple.  
*/
class GestShip
{
    private:
		/*!
		 * \brief Liste des vaisseaux
		*/
        std::vector<ShipAbstract *> lstShip;

		/*!
		 *  \brief Instance de GestShip pour le singleton
		 */
		static GestShip * _instance ;

		/*!
		 * \brief Construction
		*/
        GestShip();

    public:
		/*!
		 *  \brief Retourne une instance du singleton
		 */
		static GestShip * getSingleton(void);

		
		/*!
		 * \brief Destructeur
		*/
        ~GestShip();
        
		/*!
		 * \brief Ajoute un vaisseau au gestionnaire
		 * \param ship Pointeur sur le vaisseau
		*/
        void addShip(ShipAbstract * ship);
		/*!
		 * \brief Récupère la liste des vaisseaux
		 * \return Liste des vaisseaux
		*/
        std::vector<ShipAbstract *> getAllShips()
		{
			return lstShip;
		}
		/*!
		 * \brief Met à jour la position de tous les vaisseaux
		*/
        void updateShips();
		/*!
		 * \brief Supprime tous les vaisseaux du gestionnaire
		*/
        void deleteAllShips();
};


#endif // __GESTSHIP_H__