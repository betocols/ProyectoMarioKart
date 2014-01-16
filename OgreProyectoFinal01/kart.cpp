#include "kart.h"

kart::kart(Ogre::SceneManager* sm){
  _sceneManager = sm;
  acceleration = 0.0;
  speed = 0.0;
  distance = 0.0;
  pos = 0.0;
  zone = 0; //0-> x=130 z=0->200 || 1,2,3,7,8-> x=200 || 4-> x=2350->2900 ||  5-> x=30   ||  6-> x=30->200
  incl = 0;
  folded = false;
  createKart();
}

void kart::createBody(){
  _nodeChasisCarro = _sceneManager->createSceneNode("ChasisCarro");
  _entChasisCarro = _sceneManager->createEntity("ChasisCarro01", "chasisCarro.mesh");
  _nodeChasisCarro->attachObject(_entChasisCarro);

}

void kart::createRightFrontWheel(){
  _entRightFrontWheel = _sceneManager->createEntity("_entRightFrontWheel","ruedaDetallada.mesh");
  _nodeRightFrontWheel = _sceneManager->createSceneNode("_nodeRightFrontWheel");
  _nodeRightFrontWheel->translate(0.0,-0.5,18.0);
  _nodeRightFrontWheel->attachObject(_entRightFrontWheel);
}


void kart::createRightBackWheel(){
  _entRightBackWheel = _sceneManager->createEntity("_entRightBackWheel","ruedaDetallada.mesh");
  _nodeRightBackWheel = _sceneManager->createSceneNode("_nodeRightBackWheel");
  _nodeRightBackWheel->translate(0.0,-0.5,-1.0);
  _nodeRightBackWheel->attachObject(_entRightBackWheel);
}


void kart::createLeftFrontWheel(){
  _entLeftFrontWheel = _sceneManager->createEntity("_entLeftFrontWheel","ruedaDetallada.mesh");
  _nodeLeftFrontWheel = _sceneManager->createSceneNode("_nodeLeftFrontWheel");
  _nodeLeftFrontWheel->translate(13.5,-0.5,18.0);
  _nodeLeftFrontWheel->attachObject(_entLeftFrontWheel);
  // _nodeLeftFrontWheel->rotate(Ogre::Vector10(0.0,0.0,1.0), Ogre::Radian(Ogre::Degree(180.0)));
}

void kart::createLeftBackWheel(){
  _entLeftBackWheel = _sceneManager->createEntity("_entLeftBackWheel","ruedaDetallada.mesh");
  _nodeLeftBackWheel = _sceneManager->createSceneNode("_nodeLeftBackWheel");
  _nodeLeftBackWheel->translate(13.5,-0.5,-1.0);
  _nodeLeftBackWheel->attachObject(_entLeftBackWheel);
  // _nodeLeftBackWheel->rotate(Ogre::Vector10(0.0,0.0,1.0), Ogre::Radian(Ogre::Degree(180.0)));
}

void kart::createLeftWing(){
  float vertex0[3], vertex1[3], vertex2[3], vertex3[3], vertex4[3], vertex5[3], vertex6[3], vertex7[3];
  float normal0[3], normal1[3], normal2[3], normal3[3], normal4[3], normal5[3], normal6[3], normal7[3];
  float size;

  _nodeLeftWing = _sceneManager->createSceneNode();
  _manualLeftWing = _sceneManager->createManualObject("_manualLeftWing");
  _manualLeftWing->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  //Position of the vertexes
  vertex0[0] = 0.0;  //0
  vertex0[1] = 0.0;
  vertex0[2] = 0.0;
  vertex1[0] = 0.0;  //1
  vertex1[1] = 0.0;
  vertex1[2] = -6.0;
  vertex2[0] = 0.0;  //2
  vertex2[1] = 0.4;
  vertex2[2] = 0.0;
  vertex3[0] = 0.0;  //3
  vertex3[1] = 0.4;
  vertex3[2] = -6.0;
  vertex4[0] = -8.7;  //4
  vertex4[1] = 0.0;
  vertex4[2] = -2.0;
  vertex5[0] = -8.7;  //5
  vertex5[1] = 0.0;
  vertex5[2] = -6.0;
  vertex6[0] = -8.7;  //6
  vertex6[1] = 0.4;
  vertex6[2] = -2.0;
  vertex7[0] = -8.7;  //7
  vertex7[1] = 0.4;
  vertex7[2] = -6.0;

  //Calculating the normal for each vertex
  //normal0
  normal0[0] = (vertex1[0] + vertex2[0] + vertex3[0] - 3 * vertex0[0]) / (-3);
  normal0[1] = (vertex1[1] + vertex2[1] + vertex3[1] - 3 * vertex0[1]) / (-3);
  normal0[2] = (vertex1[2] + vertex2[2] + vertex3[2] - 3 * vertex0[2]) / (-3);
  size = sqrt(normal0[0]*normal0[0] + normal0[1]*normal0[1] + normal0[2]*normal0[2]);
  normal0[0] = normal0[0] / size;
  normal0[1] = normal0[1] / size;
  normal0[2] = normal0[2] / size;

  //normal1
  normal1[0] = (vertex0[0] + vertex2[0] + vertex3[0] + vertex4[0] + vertex5[0] - 5 * vertex1[0]) / (-5);
  normal1[1] = (vertex0[1] + vertex2[1] + vertex3[1] + vertex4[1] + vertex5[1] - 5 * vertex1[1]) / (-5);
  normal1[2] = (vertex0[2] + vertex2[2] + vertex3[2] + vertex4[2] + vertex5[2] - 5 * vertex1[2]) / (-5);
  size = sqrt(normal1[0]*normal1[0] + normal1[1]*normal1[1] + normal1[2]*normal1[2]);
  normal1[0] = normal1[0] / size;
  normal1[1] = normal1[1] / size;
  normal1[2] = normal1[2] / size;

  //normal2
  normal2[0] = (vertex0[0] + vertex1[0] + vertex3[0] + vertex4[0] + vertex6[0] - 5 * vertex2[0]) / (-5);
  normal2[1] = (vertex0[1] + vertex1[1] + vertex3[1] + vertex4[1] + vertex6[1] - 5 * vertex2[1]) / (-5);
  normal2[2] = (vertex0[2] + vertex1[2] + vertex3[2] + vertex4[2] + vertex6[2] - 5 * vertex2[2]) / (-5);
  size = sqrt(normal2[0]*normal2[0] + normal2[1]*normal2[1] + normal2[2]*normal2[2]);
  normal2[0] = normal2[0] / size;
  normal2[1] = normal2[1] / size;
  normal2[2] = normal2[2] / size;

  //normal3
  normal3[0] = (vertex1[0] + vertex2[0] + vertex5[0] + vertex6[0] + vertex7[0] - 5 * vertex3[0]) / (-5);
  normal3[1] = (vertex1[1] + vertex2[1] + vertex5[1] + vertex6[1] + vertex7[1] - 5 * vertex3[1]) / (-5);
  normal3[2] = (vertex1[2] + vertex2[2] + vertex5[2] + vertex6[2] + vertex7[2] - 5 * vertex3[2]) / (-5);
  size = sqrt(normal3[0]*normal3[0] + normal3[1]*normal3[1] + normal3[2]*normal3[2]);
  normal3[0] = normal3[0] / size;
  normal3[1] = normal3[1] / size;
  normal3[2] = normal3[2] / size;

  //normal4
  normal4[0] = (vertex0[0] + vertex1[0] + vertex2[0] + vertex5[0] + vertex6[0] - 5 * vertex4[0]) / (-5);
  normal4[1] = (vertex0[1] + vertex1[1] + vertex2[1] + vertex5[1] + vertex6[1] - 5 * vertex4[1]) / (-5);
  normal4[2] = (vertex0[2] + vertex1[2] + vertex2[2] + vertex5[2] + vertex6[2] - 5 * vertex4[2]) / (-5);
  size = sqrt(normal4[0]*normal4[0] + normal4[1]*normal4[1] + normal4[2]*normal4[2]);
  normal4[0] = normal4[0] / size;
  normal4[1] = normal4[1] / size;
  normal4[2] = normal4[2] / size;

  //normal5
  normal5[0] = (vertex1[0] + vertex3[0] + vertex4[0] + vertex6[0] + vertex7[0] - 5 * vertex5[0]) / (-5);
  normal5[1] = (vertex1[1] + vertex3[1] + vertex4[1] + vertex6[1] + vertex7[1] - 5 * vertex5[1]) / (-5);
  normal5[2] = (vertex1[2] + vertex3[2] + vertex4[2] + vertex6[2] + vertex7[2] - 5 * vertex5[2]) / (-5);
  size = sqrt(normal5[0]*normal5[0] + normal5[1]*normal5[1] + normal5[2]*normal5[2]);
  normal5[0] = normal5[0] / size;
  normal5[1] = normal5[1] / size;
  normal5[2] = normal5[2] / size;

  //normal6
  normal6[0] = (vertex2[0] + vertex3[0] + vertex4[0] + vertex5[0] + vertex7[0] - 5 * vertex6[0]) / (-5);
  normal6[1] = (vertex2[1] + vertex3[1] + vertex4[1] + vertex5[1] + vertex7[1] - 5 * vertex6[1]) / (-5);
  normal6[2] = (vertex2[2] + vertex3[2] + vertex4[2] + vertex5[2] + vertex7[2] - 5 * vertex6[2]) / (-5);
  size = sqrt(normal6[0]*normal6[0] + normal6[1]*normal6[1] + normal6[2]*normal6[2]);
  normal6[0] = normal6[0] / size;
  normal6[1] = normal6[1] / size;
  normal6[2] = normal6[2] / size;

  //normal7
  normal7[0] = (vertex3[0] + vertex5[0] + vertex6[0] - 3 * vertex7[0]) / (-3);
  normal7[1] = (vertex3[1] + vertex5[1] + vertex6[1] - 3 * vertex7[1]) / (-3);
  normal7[2] = (vertex3[2] + vertex5[2] + vertex6[2] - 3 * vertex7[2]) / (-3);
  size = sqrt(normal7[0]*normal7[0] + normal7[1]*normal7[1] + normal7[2]*normal7[2]);
  normal7[0] = normal7[0] / size;
  normal7[1] = normal7[1] / size;
  normal7[2] = normal7[2] / size;

  //Vertexs of the left wing
  //Right vertexes
  _manualLeftWing->position(vertex0[0], vertex0[1], vertex0[2]);  //0
  _manualLeftWing->position(vertex1[0], vertex1[1], vertex1[2]);  //1
  _manualLeftWing->position(vertex2[0], vertex2[1], vertex2[2]);  //2
  _manualLeftWing->position(vertex3[0], vertex3[1], vertex3[2]);  //3
  //Left vertexes
  _manualLeftWing->position(vertex4[0], vertex4[1], vertex4[2]);  //4
  _manualLeftWing->position(vertex5[0], vertex5[1], vertex5[2]);  //5
  _manualLeftWing->position(vertex6[0], vertex6[1], vertex6[2]);  //6
  _manualLeftWing->position(vertex7[0], vertex7[1], vertex7[2]);  //7

  //Normal of the vertexes
  //Right vertexes
  _manualLeftWing->normal(normal0[0], normal0[1], normal0[2]);
  _manualLeftWing->normal(normal1[0], normal1[1], normal1[2]);
  _manualLeftWing->normal(normal2[0], normal2[1], normal2[2]);
  _manualLeftWing->normal(normal3[0], normal3[1], normal3[2]);
  //Left vertexes
  _manualLeftWing->normal(normal4[0], normal4[1], normal4[2]);
  _manualLeftWing->normal(normal5[0], normal5[1], normal5[2]);
  _manualLeftWing->normal(normal6[0], normal6[1], normal6[2]);
  _manualLeftWing->normal(normal7[0], normal7[1], normal7[2]);

  //Creating the triangles
  //UpperFace
  _manualLeftWing->index(6);
  _manualLeftWing->index(2);
  _manualLeftWing->index(3);
  _manualLeftWing->index(6);
  _manualLeftWing->index(3);
  _manualLeftWing->index(7);
  //DownFace
  _manualLeftWing->index(4);
  _manualLeftWing->index(1);
  _manualLeftWing->index(0);
  _manualLeftWing->index(4);
  _manualLeftWing->index(5);
  _manualLeftWing->index(1);
  //LeftFace
  _manualLeftWing->index(6);
  _manualLeftWing->index(7);
  _manualLeftWing->index(5);
  _manualLeftWing->index(6);
  _manualLeftWing->index(5);
  _manualLeftWing->index(4);
  //RightFace
  _manualLeftWing->index(3);
  _manualLeftWing->index(2);
  _manualLeftWing->index(1);
  _manualLeftWing->index(0);
  _manualLeftWing->index(1);
  _manualLeftWing->index(2);
  //BackFace
  _manualLeftWing->index(0);
  _manualLeftWing->index(2);
  _manualLeftWing->index(4);
  _manualLeftWing->index(4);
  _manualLeftWing->index(2);
  _manualLeftWing->index(6);
  //FrontFace
  _manualLeftWing->index(5);
  _manualLeftWing->index(7);
  _manualLeftWing->index(3);
  _manualLeftWing->index(5);
  _manualLeftWing->index(3);
  _manualLeftWing->index(1);

  _manualLeftWing->end();
  _nodeLeftWing->attachObject(_manualLeftWing);
}

void kart::createRightWing(){
  float vertex0[3], vertex1[3], vertex2[3], vertex3[3], vertex4[3], vertex5[3], vertex6[3], vertex7[3];
  float normal0[3], normal1[3], normal2[3], normal3[3], normal4[3], normal5[3], normal6[3], normal7[3];
  float size;

  _nodeRightWing = _sceneManager->createSceneNode();
  _manualRightWing = _sceneManager->createManualObject("_manualRightWing");
  _manualRightWing->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
  
  //Position of the vertexes
  vertex0[0] = 11.5;  //0
  vertex0[1] = 0.1;
  vertex0[2] = -2.0;
  vertex1[0] = 11.5;  //1
  vertex1[1] = 0.1;
  vertex1[2] = -6.0;
  vertex2[0] = 11.5;  //2
  vertex2[1] = 0.5;
  vertex2[2] = -2.0;
  vertex3[0] = 11.5;  //3
  vertex3[1] = 0.5;
  vertex3[2] = -6.0;
  vertex4[0] = 2.8;  //4
  vertex4[1] = 0.1;
  vertex4[2] = 0.0;
  vertex5[0] = 2.8;  //5
  vertex5[1] = 0.1;
  vertex5[2] = -6.0;
  vertex6[0] = 2.8;  //6
  vertex6[1] = 0.5;
  vertex6[2] = 0.0;
  vertex7[0] = 2.8;  //7
  vertex7[1] = 0.5;
  vertex7[2] = -6.0;

  //Calculating the normal for each vertex
  //normal0
  normal0[0] = (vertex1[0] + vertex2[0] + vertex3[0] - 3 * vertex0[0]) / (-3);
  normal0[1] = (vertex1[1] + vertex2[1] + vertex3[1] - 3 * vertex0[1]) / (-3);
  normal0[2] = (vertex1[2] + vertex2[2] + vertex3[2] - 3 * vertex0[2]) / (-3);
  size = sqrt(normal0[0]*normal0[0] + normal0[1]*normal0[1] + normal0[2]*normal0[2]);
  normal0[0] = normal0[0] / size;
  normal0[1] = normal0[1] / size;
  normal0[2] = normal0[2] / size;

  //normal1
  normal1[0] = (vertex0[0] + vertex2[0] + vertex3[0] + vertex4[0] + vertex5[0] - 5 * vertex1[0]) / (-5);
  normal1[1] = (vertex0[1] + vertex2[1] + vertex3[1] + vertex4[1] + vertex5[1] - 5 * vertex1[1]) / (-5);
  normal1[2] = (vertex0[2] + vertex2[2] + vertex3[2] + vertex4[2] + vertex5[2] - 5 * vertex1[2]) / (-5);
  size = sqrt(normal1[0]*normal1[0] + normal1[1]*normal1[1] + normal1[2]*normal1[2]);
  normal1[0] = normal1[0] / size;
  normal1[1] = normal1[1] / size;
  normal1[2] = normal1[2] / size;

  //normal2
  normal2[0] = (vertex0[0] + vertex1[0] + vertex3[0] + vertex4[0] + vertex6[0] - 5 * vertex2[0]) / (-5);
  normal2[1] = (vertex0[1] + vertex1[1] + vertex3[1] + vertex4[1] + vertex6[1] - 5 * vertex2[1]) / (-5);
  normal2[2] = (vertex0[2] + vertex1[2] + vertex3[2] + vertex4[2] + vertex6[2] - 5 * vertex2[2]) / (-5);
  size = sqrt(normal2[0]*normal2[0] + normal2[1]*normal2[1] + normal2[2]*normal2[2]);
  normal2[0] = normal2[0] / size;
  normal2[1] = normal2[1] / size;
  normal2[2] = normal2[2] / size;

  //normal3
  normal3[0] = (vertex1[0] + vertex2[0] + vertex5[0] + vertex6[0] + vertex7[0] - 5 * vertex3[0]) / (-5);
  normal3[1] = (vertex1[1] + vertex2[1] + vertex5[1] + vertex6[1] + vertex7[1] - 5 * vertex3[1]) / (-5);
  normal3[2] = (vertex1[2] + vertex2[2] + vertex5[2] + vertex6[2] + vertex7[2] - 5 * vertex3[2]) / (-5);
  size = sqrt(normal3[0]*normal3[0] + normal3[1]*normal3[1] + normal3[2]*normal3[2]);
  normal3[0] = normal3[0] / size;
  normal3[1] = normal3[1] / size;
  normal3[2] = normal3[2] / size;

  //normal4
  normal4[0] = (vertex0[0] + vertex1[0] + vertex2[0] + vertex5[0] + vertex6[0] - 5 * vertex4[0]) / (-5);
  normal4[1] = (vertex0[1] + vertex1[1] + vertex2[1] + vertex5[1] + vertex6[1] - 5 * vertex4[1]) / (-5);
  normal4[2] = (vertex0[2] + vertex1[2] + vertex2[2] + vertex5[2] + vertex6[2] - 5 * vertex4[2]) / (-5);
  size = sqrt(normal4[0]*normal4[0] + normal4[1]*normal4[1] + normal4[2]*normal4[2]);
  normal4[0] = normal4[0] / size;
  normal4[1] = normal4[1] / size;
  normal4[2] = normal4[2] / size;

  //normal5
  normal5[0] = (vertex1[0] + vertex3[0] + vertex4[0] + vertex6[0] + vertex7[0] - 5 * vertex5[0]) / (-5);
  normal5[1] = (vertex1[1] + vertex3[1] + vertex4[1] + vertex6[1] + vertex7[1] - 5 * vertex5[1]) / (-5);
  normal5[2] = (vertex1[2] + vertex3[2] + vertex4[2] + vertex6[2] + vertex7[2] - 5 * vertex5[2]) / (-5);
  size = sqrt(normal5[0]*normal5[0] + normal5[1]*normal5[1] + normal5[2]*normal5[2]);
  normal5[0] = normal5[0] / size;
  normal5[1] = normal5[1] / size;
  normal5[2] = normal5[2] / size;

  //normal6
  normal6[0] = (vertex2[0] + vertex3[0] + vertex4[0] + vertex5[0] + vertex7[0] - 5 * vertex6[0]) / (-5);
  normal6[1] = (vertex2[1] + vertex3[1] + vertex4[1] + vertex5[1] + vertex7[1] - 5 * vertex6[1]) / (-5);
  normal6[2] = (vertex2[2] + vertex3[2] + vertex4[2] + vertex5[2] + vertex7[2] - 5 * vertex6[2]) / (-5);
  size = sqrt(normal6[0]*normal6[0] + normal6[1]*normal6[1] + normal6[2]*normal6[2]);
  normal6[0] = normal6[0] / size;
  normal6[1] = normal6[1] / size;
  normal6[2] = normal6[2] / size;

  //normal7
  normal7[0] = (vertex3[0] + vertex5[0] + vertex6[0] - 3 * vertex7[0]) / (-3);
  normal7[1] = (vertex3[1] + vertex5[1] + vertex6[1] - 3 * vertex7[1]) / (-3);
  normal7[2] = (vertex3[2] + vertex5[2] + vertex6[2] - 3 * vertex7[2]) / (-3);
  size = sqrt(normal7[0]*normal7[0] + normal7[1]*normal7[1] + normal7[2]*normal7[2]);
  normal7[0] = normal7[0] / size;
  normal7[1] = normal7[1] / size;
  normal7[2] = normal7[2] / size;

  //Vertexs of the right upper wing
  //Left vertexes
  _manualRightWing->position(vertex0[0], vertex0[1], vertex0[2]);  //0
  _manualRightWing->position(vertex1[0], vertex1[1], vertex1[2]);  //1
  _manualRightWing->position(vertex2[0], vertex2[1], vertex2[2]);  //2
  _manualRightWing->position(vertex3[0], vertex3[1], vertex3[2]);  //3
  //Right vertexes
  _manualRightWing->position(vertex4[0], vertex4[1], vertex4[2]);  //4
  _manualRightWing->position(vertex5[0], vertex5[1], vertex5[2]);  //5
  _manualRightWing->position(vertex6[0], vertex6[1], vertex6[2]);  //6
  _manualRightWing->position(vertex7[0], vertex7[1], vertex7[2]);  //7

  //Normal of the vertexes
  //Left vertexes
  _manualRightWing->normal(normal0[0], normal0[1], normal0[2]);
  _manualRightWing->normal(normal1[0], normal1[1], normal1[2]);
  _manualRightWing->normal(normal2[0], normal2[1], normal2[2]);
  _manualRightWing->normal(normal3[0], normal3[1], normal3[2]);
  //Right vertexes
  _manualRightWing->normal(normal4[0], normal4[1], normal4[2]);
  _manualRightWing->normal(normal5[0], normal5[1], normal5[2]);
  _manualRightWing->normal(normal6[0], normal6[1], normal6[2]);
  _manualRightWing->normal(normal7[0], normal7[1], normal7[2]);

  //Creating the triangles
  //UpperFace
  _manualRightWing->index(6);
  _manualRightWing->index(2);
  _manualRightWing->index(3);
  _manualRightWing->index(6);
  _manualRightWing->index(3);
  _manualRightWing->index(7);
  //DownFace
  _manualRightWing->index(4);
  _manualRightWing->index(1);
  _manualRightWing->index(0);
  _manualRightWing->index(4);
  _manualRightWing->index(5);
  _manualRightWing->index(1);
  //LeftFace
  _manualRightWing->index(6);
  _manualRightWing->index(7);
  _manualRightWing->index(5);
  _manualRightWing->index(6);
  _manualRightWing->index(5);
  _manualRightWing->index(4);
  //RightFace
  _manualRightWing->index(3);
  _manualRightWing->index(2);
  _manualRightWing->index(1);
  _manualRightWing->index(0);
  _manualRightWing->index(1);
  _manualRightWing->index(2);
  //BackFace
  _manualRightWing->index(0);
  _manualRightWing->index(2);
  _manualRightWing->index(4);
  _manualRightWing->index(4);
  _manualRightWing->index(2);
  _manualRightWing->index(6);
  //FrontFace
  _manualRightWing->index(5);
  _manualRightWing->index(7);
  _manualRightWing->index(3);
  _manualRightWing->index(5);
  _manualRightWing->index(3);
  _manualRightWing->index(1);

  _manualRightWing->end();
  _nodeRightWing->attachObject(_manualRightWing);
}

void kart::createKart(){
  car = _sceneManager->createSceneNode("car");
  _sceneManager->getRootSceneNode()->addChild(car);

  createBody();
  createLeftFrontWheel();
  createLeftBackWheel();
  createRightFrontWheel();
  createRightBackWheel();
  car->addChild(_nodeChasisCarro);
  car->addChild(_nodeLeftFrontWheel);
  car->addChild(_nodeLeftBackWheel);
  car->addChild(_nodeRightFrontWheel);
  car->addChild(_nodeRightBackWheel);
}


void kart::foldWings(){

  if((distance > 4000.0) && (folded == false)) {
    createLeftWing();
    createRightWing();
    folded = true;
  }

}

void kart::unfoldWings(){

  if((distance > 5000.0) && (folded == true)) {
    folded = false;
  }
}

void kart::moveRight(){
  if (pos > -125.0){
    // if (incl == -1){
    //   incl = 0;
    //   _nodeLeftFrontWheel->rotate(Ogre::Vector3(0.0,1.0,0.0), Ogre::Radian(Ogre::Degree(-90.0)));
    //   _nodeRightFrontWheel->rotate(Ogre::Vector3(0.0,1.0,0.0), Ogre::Radian(Ogre::Degree(-90.0)));
    // }

    // if (incl == 0){
    //   incl = 1;
    //   _nodeLeftFrontWheel->rotate(Ogre::Vector3(0.0,1.0,0.0), Ogre::Radian(Ogre::Degree(-45.0)));
    //   _nodeRightFrontWheel->rotate(Ogre::Vector3(0.0,1.0,0.0), Ogre::Radian(Ogre::Degree(-45.0)));
    // }
    
    // _nodeLeftFrontWheel->rotate(Ogre::Vector3(0.0,1.0,0.0), Ogre::Radian(Ogre::Degree(45.0)));
    // _nodeRightFrontWheel->rotate(Ogre::Vector3(0.0,1.0,0.0), Ogre::Radian(Ogre::Degree(45.0)));
    
    //Rota en direccion al movimiento
    _nodeLeftFrontWheel->yaw(Ogre::Radian(Ogre::Degree(-45.0)));
    _nodeRightFrontWheel->yaw(Ogre::Radian(Ogre::Degree(-45.0)));

    //_nodeLeftFrontWheel->yaw(Ogre::Radian(Ogre::Degree(45.0)));
    //_nodeRightFrontWheel->yaw(Ogre::Radian(Ogre::Degree(45.0)));

    //Rota sobre su eje
    // _nodeLeftFrontWheel->pitch(Ogre::Radian(Ogre::Degree(15.0)));
    // _nodeRightFrontWheel->pitch(Ogre::Radian(Ogre::Degree(15.0)));
    // _nodeLeftBackWheel->pitch(Ogre::Radian(Ogre::Degree(15.0)));
    // _nodeRightBackWheel->pitch(Ogre::Radian(Ogre::Degree(15.0)));
    
    // car->translate(-5.0,0.0,0.0);
    pos-=5.0;
  }
  
}

void kart::moveLeft(){
  if (pos < 125.0){
    // if (incl == 1){
    //   incl = 0;
    //   _nodeLeftFrontWheel->rotate(Ogre::Vector3(0.0,1.0,0.0), Ogre::Radian(Ogre::Degree(90.0)));
    //   _nodeRightFrontWheel->rotate(Ogre::Vector3(0.0,1.0,0.0), Ogre::Radian(Ogre::Degree(90.0)));
    // }

    // if (incl == 0){
    //   incl = -1;
    //   _nodeLeftFrontWheel->rotate(Ogre::Vector3(0.0,1.0,0.0), Ogre::Radian(Ogre::Degree(45.0)));
    //   _nodeRightFrontWheel->rotate(Ogre::Vector3(0.0,1.0,0.0), Ogre::Radian(Ogre::Degree(45.0)));
    // }
    //Rota en direccion al movimiento
    _nodeLeftFrontWheel->yaw(Ogre::Radian(Ogre::Degree(45.0)));
    _nodeRightFrontWheel->yaw(Ogre::Radian(Ogre::Degree(45.0)));

    //_nodeLeftFrontWheel->yaw(Ogre::Radian(Ogre::Degree(-45.0)));
    //_nodeRightFrontWheel->yaw(Ogre::Radian(Ogre::Degree(-45.0)));

    //Rota sobre su eje
    // _nodeLeftFrontWheel->pitch(Ogre::Radian(Ogre::Degree(15.0)));
    // _nodeRightFrontWheel->pitch(Ogre::Radian(Ogre::Degree(15.0)));
    // _nodeLeftBackWheel->pitch(Ogre::Radian(Ogre::Degree(15.0)));
    // _nodeRightBackWheel->pitch(Ogre::Radian(Ogre::Degree(15.0)));

    // car->translate(5.0,0.0,0.0);
    pos+=5.0;
  }
  
}

Ogre::SceneNode* kart::getKart(){
  return car;
}

void kart::setAcceleration(float n){
  acceleration = n;
}
void kart::setSpeed(float n){
  speed = n;
}
void kart::setDistance(float n){
  distance = n;
}
void kart::setPos(float n){
  pos = n;
}
void kart::setZone(int n){
  zone = n;
}

float kart::getAcceleration(){
  return acceleration;
}
float kart::getSpeed(){
  return speed;
}
float kart::getDistance(){
  return distance;
}
float kart::getPos(){
  return pos;
}
int kart::getZone(){
  return zone;
}