#include "Asteroid.h"

using namespace Ogre;

Asteroid::Asteroid(void) : speed(0), rotationSpeed(Utils::randRangeInt(-1,1)/100.0)
{
    this->typeObject = ObjectRoot::ASTEROID;
	Ogre::Quaternion quat;
	quat[0] = 1;//Ogre::Real(Utils::degreToRadian(0.01));
	quat[1] = (Utils::randRangeInt(1,10))/10.0;//randomiser
	quat[2] = (Utils::randRangeInt(1,10))/10.0;//randomiser
	quat[3] = (Utils::randRangeInt(1,10))/10.0;//randomiser
    this->entity = static_cast<Ogre::Entity *>(MeshLoader::getSingleton()->getNodedMovableObject(MeshLoader::ASTEROID));
    this->entitySmall = static_cast<Ogre::Entity *>(MeshLoader::getSingleton()->getMovableObject(MeshLoader::ASTEROID_SMALL));
    this->getNode()->attachObject(entitySmall);
    entitySmall->setVisible(false);
	this->getNode()->setOrientation(quat);
	this->getNode()->setScale(100,100,100);
    this->getNode()->setPosition(0, 0, 0);

}

Asteroid::~Asteroid(void)
{
	MeshLoader::getSingleton()->deleteNodedObject(MeshLoader::ASTEROID, this->getEntity());
	MeshLoader::getSingleton()->deleteNodedObject(MeshLoader::ASTEROID_SMALL, this->entitySmall);
}

Quaternion Asteroid::getOrientation(void)
{
	return this->getNode()->getOrientation();
}
void Asteroid::setOrientation(Ogre::Quaternion  q)
{
	this->getNode()->setOrientation(q);
}
void Asteroid::setOrientation(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real a)
{
	this->getNode()->setOrientation(x,y,z,a);
}

Ogre::Real Asteroid::getSpeed(void)
{
	return this->speed;
}
void Asteroid::setSpeed (Ogre::Real speed)
{
	this->speed = speed;
}

Ogre::Real Asteroid::getRotationSpeed(void)
{
	return this->rotationSpeed;
}

void Asteroid::setRotationSpeed (Ogre::Real rotationSpeed)
{
	this->rotationSpeed = rotationSpeed;
}

Ogre::Vector3 Asteroid::getPosition(void)
{
    return this->getNode()->getPosition();
}
void Asteroid::setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
    this->getNode()->setPosition(x, y, z);
}

void Asteroid::move(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Vector3 pos = this->getPosition();
	this->setPosition(pos[0]+x, pos[1]+y, pos[2]+z);
}
void Asteroid::move(const Ogre::Vector3 &vec)
{
	Vector3 pos = this->getPosition() + vec;
	this->setPosition(pos[0], pos[1], pos[2]);
}

void Asteroid::moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Ogre::Vector3 vec = Ogre::Vector3(x, y, z);
	this->moveRelative(vec);
}
void Asteroid::moveRelative(const Ogre::Vector3 &vec)
{
	Vector3 trans = this->getOrientation() * vec;
	Vector3 pos = this->getPosition() + trans;
	this->setPosition(pos[0], pos[1], pos[2]);
}


void Asteroid::rotateRelative(const Ogre::Radian angle)
{
    this->entity->getParentNode()->roll(angle);
}

void Asteroid::updatePosition(void)
{
    Ogre::Entity * visibleEntity = this->getEntity()->getVisible()?this->entity:this->entitySmall;
    Ogre::Real sizeViewed = GestSceneManager::getProjectedSize(visibleEntity, 500);

	if (this->getRotationSpeed() != 0)
	this->rotateRelative(Ogre::Radian(this->getRotationSpeed()));
	if (this->getSpeed() != 0)
	{
		this->moveRelative(0.0, 0.0, this->getSpeed());
	}
    //LOD
	if(sizeViewed > -1)
	{

        if(this->entity->getVisible() && sizeViewed<0.01)
        {

           this->entity->setVisible(false);
            this->entitySmall->setVisible(true);
        }
        if(!this->entity->getVisible() && sizeViewed>0.02)
        {
            this->entity->setVisible(true);
            this->entitySmall->setVisible(false);
        }
	}

    //mise à jour de la physique
    this->updateBounding();
}
