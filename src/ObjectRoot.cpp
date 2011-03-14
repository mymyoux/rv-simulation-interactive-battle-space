#include "ObjectRoot.h"
#include "ListenerCollision.h"

using namespace Ogre;
using namespace OgreBulletCollisions;


std::map<OgreBulletDynamics::RigidBody *, ObjectRoot *> ObjectRoot::lstRigidbodyToObject = std::map<OgreBulletDynamics::RigidBody *, ObjectRoot *>();


void ObjectRoot::addRelationRigidbodyToObject(OgreBulletDynamics::RigidBody * rigidBody, ObjectRoot * object)
{
	std::pair<OgreBulletDynamics::RigidBody *, ObjectRoot *> relation(rigidBody, object);
	lstRigidbodyToObject.insert(relation);
}

ObjectRoot * ObjectRoot::getObjectWithRigidBody(OgreBulletDynamics::RigidBody * rigidBody)
{
	return lstRigidbodyToObject[rigidBody];
}

std::map<OgreBulletDynamics::RigidBody *, ObjectRoot *> ObjectRoot::getAllRigidbodyToObject()
{
	return lstRigidbodyToObject;
}


ObjectRoot::ObjectRoot()
{
    shape = NULL;
    rigidBody = NULL;
}

ObjectRoot::~ObjectRoot()
{
    if(shape != NULL)
        delete shape;

    if(rigidBody != NULL)
        delete rigidBody;
}


void ObjectRoot::createCollisionObject(ListenerCollision * listenerCollision, int size)
{

    std::cout<<"size="<<size<<"ObjectType: "<<typeObject<<std::endl;
    Ogre::Vector3 pos = this->getNode()->getPosition();

	switch(this->typeObject)
	{
		case SHIP_PLAYER :
		case SHIP_IA :
		{
			OgreBulletCollisions::StaticMeshToShapeConverter * shapeConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(this->getEntity());

			OgreBulletCollisions::ConvexHullCollisionShape * convexCollisionShape = shapeConverter->createConvex();
			this->shape = (OgreBulletCollisions::CollisionShape *) convexCollisionShape;

			delete shapeConverter;
			break;
		}
		case SHIP_BATTLE_STATION :
		{
			Ogre::Matrix4 mat = Ogre::Matrix4::IDENTITY;
			for(int i = 0 ; i < 3 ; i ++)
				mat[i][i] *= this->getNode()->_getDerivedScale()[i];
			
			OgreBulletCollisions::StaticMeshToShapeConverter * shapeConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(this->getEntity(), mat);

			OgreBulletCollisions::ConvexHullCollisionShape * convexCollisionShape = shapeConverter->createConvex();
			this->shape = (OgreBulletCollisions::CollisionShape *) convexCollisionShape;

			delete shapeConverter;
			break;
		}
		
		case PLANET :
			this->shape = new OgreBulletCollisions::SphereCollisionShape(size);
			break;
			
		case ASTEROID :
			this->shape = new OgreBulletCollisions::SphereCollisionShape(size);
			break;
			
		case MISSILE :
			this->shape = new OgreBulletCollisions::SphereCollisionShape(10.0);
			break;
			
		case LASER :
			this->shape = new OgreBulletCollisions::SphereCollisionShape(10.0);
			break;
	}


    std::ostringstream rigidBodyString;
    rigidBodyString << "RigidObjectRoot" << Utils::toString(this->typeObject) << "_" << Utils::toString(Utils::unique());
    std::cout<<"nom: "<<rigidBodyString.str()<<std::endl;
    this->rigidBody = new OgreBulletDynamics::RigidBody(rigidBodyString.str() ,listenerCollision->getWorld());

    this->rigidBody->setStaticShape (this->getNode(),  this->shape, 0.6, 0.6, pos ,Quaternion(0,0,0,1));
    //this->rigidBody->setKinematicObject(true);
    this->getEntity()->setCastShadows(true);
    
    ObjectRoot::addRelationRigidbodyToObject(this->rigidBody, this);
}


void ObjectRoot::updateBounding(void)
{
//    if(this->typeObject==ObjectRoot::SHIP_PLAYER){
//        std::cout<<"pos :"<<this->rigidBody->getCenterOfMassPosition()<<std::endl;
//    }

    Ogre::Vector3 posOgre=(this->getNode()->getPosition());
    Ogre::Quaternion dirOgre=(this->getNode()->getOrientation());
    btVector3 posBt(posOgre[0], posOgre[1], posOgre[2]);
    btQuaternion dirBt(dirOgre.x, dirOgre.y, dirOgre.z, dirOgre.w);



    this->rigidBody->getBulletObject()->getWorldTransform().setOrigin(posBt);
    this->rigidBody->getBulletObject()->getWorldTransform().setRotation(dirBt);
//
//    btTransform transform = this->rigidBody->getCenterOfMassTransform();
//    transform.setOrigin(posBt);
//    transform.setRotation(dirBt);
//    rigidBody->getBulletRigidBody()->setCenterOfMassTransform(transform);
//    rigidBody->setTransform(posBt, dirBt);
//
    //this->rigidBody->getBulletObject()->getWorldTransform().setOrigin(posBt);
    //this->rigidBody->getBulletObject()->getWorldTransform().setRotation(btQuaternion(dirOgre.x, dirOgre.y, dirOgre.z, dirOgre.w));

//


    this->rigidBody->getBulletDynamicsWorld()->removeRigidBody(this->rigidBody->getBulletRigidBody());
    this->rigidBody->getBulletObject()->getWorldTransform().setOrigin(posBt);
    this->rigidBody->getBulletObject()->getWorldTransform().setRotation(dirBt);
    this->rigidBody->getBulletDynamicsWorld()->addRigidBody(this->rigidBody->getBulletRigidBody());
}


