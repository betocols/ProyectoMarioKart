#include "Ogre\Ogre.h"
#include "OIS\OIS.h"

class box{



private:
  static int n;
  int i;
  float posX;
  float posY;
  float posZ;
  float rotX;
  float rotY;
  float rotZ;

  Ogre::SceneNode* obstacle;
  Ogre::SceneManager* _sceneManager;

  Ogre::SceneNode* _nodeBody;
  Ogre::Entity* _entBody;

  Ogre::SceneNode* collisioner;

public:
  box(Ogre::SceneManager* sm, float x, float y, float z, float rx, float ry, float rz);
  void createBox();
};