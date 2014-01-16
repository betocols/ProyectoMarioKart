#include "Ogre\Ogre.h"
#include "OIS\OIS.h"

class kart{

private:
  Ogre::SceneNode* car;
  Ogre::SceneManager* _sceneManager;
  
  //Chasis
  Ogre::SceneNode* _nodeChasisCarro;
  Ogre::Entity* _entChasisCarro;

  //Left Wheels
  Ogre::SceneNode* _nodeLeftFrontWheel;
  Ogre::Entity* _entLeftFrontWheel;
  Ogre::SceneNode* _nodeLeftBackWheel;
  Ogre::Entity* _entLeftBackWheel;

  //Right Wheels
  Ogre::SceneNode* _nodeRightFrontWheel;
  Ogre::Entity* _entRightFrontWheel;
  Ogre::SceneNode* _nodeRightBackWheel;
  Ogre::Entity* _entRightBackWheel;
  
  //Left Wing
  Ogre::SceneNode* _nodeLeftWing;
  Ogre::ManualObject* _manualLeftWing;

  //Right Wing
  Ogre::SceneNode* _nodeRightWing;
  Ogre::ManualObject* _manualRightWing;

  float acceleration;
  float speed;
  float distance;
  float pos;
  float zone;
  int incl;
  bool folded;

public:
  kart(Ogre::SceneManager* sm);
  void createKart();
  void createBody();
  void createLeftFrontWheel();
  void createLeftBackWheel();
  void createRightFrontWheel();
  void createRightBackWheel();
  void createLeftWing();
  void createRightWing();

  void  setAcceleration(float n);
  void  setSpeed(float n);
  void  setDistance(float n);
  void  setPos(float n);
  void  setZone(int n);
  float getAcceleration();
  float getSpeed();
  float getDistance();
  float getPos();
  int getZone();

  void foldWings();
  void unfoldWings();

  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();

 Ogre::SceneNode* getKart();
};