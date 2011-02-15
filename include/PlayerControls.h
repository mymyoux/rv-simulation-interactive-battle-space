#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H
#include "Signal.h"
#include "ListenerMouse.h"
#include "ObjectRoot.h"
#include "ListenerKeyboard.h"
#include <OISInputManager.h>
#include <OISKeyboard.h>
class ListenerKeyboard;
class ListenerMouse;
/*!
* \class PlayerControls
* \brief Class Permettant de gérer le contrôle de manière "haut niveau" du joueur au d'utiliser directement les évènements de base de Ogre
* Permettra par la suite de facilemet modifier les contrôles pour chaque joueur (enregistrés dans un fichier par exemple)
* Par la suite il faudra donc écouter les évènements (signaux) de PlayerControls et non plus directement de mouse et keyboard
*/
class PlayerControls: public ObjectRoot
{
    public:
        /*!
         * \brief Constructor
         * \param mouse MouseListener
         * \param keyboard KeyboardListener
         */
        PlayerControls(ListenerMouse* mouse, ListenerKeyboard* keyboard);
        /*!
         * \brief Destructor
         */
        virtual ~PlayerControls();
		/// Définit les différents types de contrôles
		enum Controls
		{
			NONE = 0,
			SHOOT1 = 1,
			SHOOT2 = 2,
			ACCELERATION = 3,
			BRAKE = 4,
			LEFT = 5,
			RIGHT = 6,
            UP =7,
            DOWN =8,
			QUIT = 9
		};
		/*!
		 * \brief Emet un dispatche lorsqu'une touche est préssée  Signal(PlayerControls::Controls key)
		 */
        Signal<PlayerControls::Controls> signalKeyPressed;
        /*!
		 * \brief Emet un dispatche lorsqu'une touche est relâchée  Signal(PlayerControls::Controls key)
		 */
        Signal<PlayerControls::Controls> signalKeyReleased;
         /*!
		 * \brief Emet un dispatche lorsque la souris est bougée  Signal(Ogre::Vector3)
		 */
        Signal<Ogre::Vector3> signalMouseMoved;
    protected:
    private:
         /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est pressée et le transmet à signalKeyPressed
		 * \param evt Event OIS
		 */
        void keyboardPressed(const OIS::KeyEvent &evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche du clavier est relâchée et le transmet à signalKeyReleased
		 * \param evt Event OIS
		 */
        void keyboardReleased(const OIS::KeyEvent &evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'un la souris est bougée et le transmet à signalMouseMoved
		 * \param evt Vector3(X, Y, Z)
		 */
        void mouseMoved(Ogre::Vector3 vect);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est pressée et le transmet à signalKeyPressed
		 * \param evt Event OIS
		 */
        void mousePressed(OIS::MouseButtonID evt);
        /*!
		 * \brief Reçoit un dispatche lorsqu'une touche de la souris est relâchée et le transmet à signalKeyReleased
		 * \param evt Event OIS
		 */
        void mouseReleased(OIS::MouseButtonID evt);
        /*!
		 * \brief Convertit un évènement OIS::KeyEvent en PlayerControls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Event OIS
		 * \return PlayerControls::Controls key correspondante
		 */
        PlayerControls::Controls OISEventToControlKey(const OIS::KeyEvent &evt);
        /*!
		 * \brief Convertit un id IS::MouseButtonID en PlayerControls::Controls pour se défaire du couplage aux touches physiques
		 * \param evt Mouse button ID (OIS)
		 * \return PlayerControls::Controls key correspondante
		 */
        PlayerControls::Controls OISEventToControlKey(OIS::MouseButtonID evt);

};

#endif // PLAYERCONTROLS_H