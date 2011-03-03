 #include "SpeedCompteur.h"
 
using namespace Ogre;


SpeedCompteur::SpeedCompteur(ShipAbstract * ship, ListenerTime * listenerTime)
{
    this->ship = ship;

    OverlayManager& overlayManager = OverlayManager::getSingleton();
    OverlayContainer* panelCompteur = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelCompteur"));
    panelCompteur->setMetricsMode(Ogre::GMM_RELATIVE);
    panelCompteur->setPosition(0.85, 0.85);
    panelCompteur->setDimensions(0.15, 0.15);
    panelCompteur->setMaterialName("jaugeVide");

    OverlayContainer * panelJauge= static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelJauge"));
    panelJauge->setMetricsMode(Ogre::GMM_RELATIVE);
    panelJauge->setPosition(0.875, 0.86);
    panelJauge->setDimensions(0.10, 0.13);
    panelJauge->setMaterialName("jaugePleine");


    Overlay* overlay = overlayManager.create("OverlayName");
    overlay->add2D(panelCompteur);
    overlay->add2D(panelJauge);
    overlay->show();


    listenerTime->signalTimerElapsed.add(&SpeedCompteur::miseAJour,this);
}

SpeedCompteur::~SpeedCompteur()
{

}


void SpeedCompteur::miseAJour(void * useless)
{
    OverlayManager& overlayManager = OverlayManager::getSingleton();
    OverlayContainer * jauge= static_cast<OverlayContainer*>(overlayManager.getOverlayElement("PanelJauge"));
    Ogre::Real acSpeed=this->ship->getSpeed();
    Ogre::Real coef= acSpeed/ShipAbstract::MAXSPEED;
    jauge->setPosition(0.875, (0.99-0.13*coef));
    jauge->setDimensions(0.10, 0.13*coef);
}

