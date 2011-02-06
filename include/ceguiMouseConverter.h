/*!
 **  \file  ceguiMouseConverter.h
 **  \brief Contient la déclaration de fonctions pour la conversion d'événement de OIS à CEGUI
 **  \author Guillaume Smaha
 **  \author Romain Bourreau
 **  \version 1.0
 **/
#ifndef __CEGUI_MOUSE_CONVERTER_H__
#define __CEGUI_MOUSE_CONVERTER_H__

#include <OISMouse.h>
#include <CEGUI.h>

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

#endif //__CEGUI_MOUSE_CONVERTER_H__
