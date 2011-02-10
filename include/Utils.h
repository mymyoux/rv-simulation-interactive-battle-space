/**
 *  \file  Utils.h
 *  \brief Utilities file
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <Ogre.h>
#include <math.h>
#include <time.h>
#include <sstream>
#include <iostream>

/**
 * \class Utils
 * \brief A tools class
 */
class Utils
{
	private:
		/**
		 * Initialize the rand function
		 */
		static int initialize(void);

		/**
		 * Value of a unique counter
		 */
		static int _count;

		/**
		 * Chemin du fichier de log
		 */
		static Ogre::String _logFile;
	public:
		/**
		* Returns an int between min and max (inclusive)
		* \param min lower bound
		* \param max upper bound
		* \return An int between min and max (inclusive)
		*/
		static int randRangeInt(int min, int max);
		/**
		 * Returns an unique int
		 * \return unique int
		 */
		static int unique(void);

		/*!
		* \brief Affiche un message de log sur la console
		* \param text Texte � afficher
		*/
		static void log(Ogre::String text);
		
		/*!
		* \brief Initialise le fichier de sortie de log
		* \param file Chemin du fichier
		*/
		static void logFileInit(Ogre::String file);
		/*!
		* \brief Enregistre un message de log dans le fichier de sortie
		* \param text Texte � afficher
		*/
		static void logFile(Ogre::String text);
		
		/*!
		* \brief Transforme une valeur en une chaine de caract�re.
		* \param Value valeur � chainer
		*/
		template <typename T> static Ogre::String toString( const T & Value );
		/*!
		* \brief Transforme un entier en une chaine de caract�re.
		* \param Value valeur � chainer
		*/
		static Ogre::String toString( int Value);
};


#endif // __UTILS_H__
