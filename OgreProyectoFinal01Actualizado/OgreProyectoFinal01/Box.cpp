#include "Box.h"
int box::n;
box::box(Ogre::SceneManager* sm, float x, float y, float z, float rx, float ry, float rz){
  _sceneManager = sm;
  posX = x;
  posY = y;
  posZ = z;
  rotX = rx;
  rotY = ry;
  rotZ = rz;
  i = n++;
  createBox();
}

std::string convertInt(int number){
	std::stringstream ss;//create a stringstream
	ss << number;//add number to the stream
	return ss.str();//return a string with the contents of the stream
}

void box::createBox(){
	obstacle = _sceneManager->createSceneNode("obstacle"+ convertInt(i));
	_sceneManager->getRootSceneNode()->addChild(obstacle);

	_nodeBody = _sceneManager->createSceneNode("body"+ convertInt(i));
	_entBody = _sceneManager->createEntity("box"+ convertInt(i),"Barrel.mesh");
	_nodeBody->attachObject(_entBody);

	obstacle->addChild(_nodeBody);
	obstacle->translate(posX,posY,posZ);


}