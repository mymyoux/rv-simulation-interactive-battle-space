#ifndef __MESH_LOADER_H__
#define __MESH_LOADER_H__

#include <Ogre.h>
#include "Utils.h"

class MeshLoader
{
	public:	
		/*!
		 *  \brief Définit les différents types de mesh
		 */
		enum MeshType {
			SHIP = 0,
			POMPIDOU = 2, //peut etre a modifier
			ARLEQUIN = 3,
			SHIP_TOUCHED = 4,
			PLANET = 5,
			PLANET2 = 6,
			PLANET3 = 7
		} ;
	
	private:
		Ogre::SceneManager * sceneMgr;
		static MeshLoader * _instance ;
		
	public:
		static MeshLoader * getSingleton(void);
		
		
		MeshLoader(Ogre::SceneManager * sceneMgr);
		~MeshLoader(void);
		
		
		Ogre::Entity * getEntity(MeshLoader::MeshType meshType, bool random = false)
		{
			return getEntity(meshType, "object"+Utils::unique(), random);
		}
		
		Ogre::Entity * getEntity(MeshLoader::MeshType meshType, Ogre::String name,  bool random = false);
		
		Ogre::Entity * getNodedEntity(MeshLoader::MeshType meshType, bool random = false)
		{
			return getNodedEntity(meshType, "node"+Utils::unique(), random);
		}
		
		Ogre::Entity * getNodedEntity(MeshLoader::MeshType meshType, Ogre::String nodeName, bool random = false)
		{
			return getNodedEntity(meshType, nodeName, "object"+Utils::unique(), random);
		}
		
		Ogre::Entity * getNodedEntity(MeshLoader::MeshType meshType, Ogre::String nodeName, Ogre::String meshName,  bool random = false);
		
		Ogre::SceneManager * getSceneManager()
		{
			return sceneMgr;
		}
		
		void setMaterial(Ogre::Entity * entity, MeshLoader::MeshType meshType);
};

#endif // __MESH_LOADER_H__