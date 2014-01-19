#include "Ogre\Ogre.h"
#include "OIS\OIS.h"
#include "Kart.h"
#include "box.h"

kart* carting;
box* caja1;
box* caja2;
box* caja3;

class AppFrameListener : public Ogre::FrameListener
{

private:

  Ogre::SceneManager* _sManager;
  OIS::InputManager* _InputManager;
  OIS::Keyboard* _Keyboard;
  OIS::Mouse* _Mouse;
  Ogre::Camera* _Cam;
  Ogre::SceneNode* _node;
  float _movementspeed;

public:

    AppFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::SceneNode* node, Ogre::SceneManager* _sceneManager){

    OIS::ParamList parameters;
    unsigned int windowHandle = 0;
    std::ostringstream windowHandleString;
    win->getCustomAttribute("WINDOW", &windowHandle);
    windowHandleString << windowHandle;
    parameters.insert(std::make_pair("WINDOW", windowHandleString.str()));
    _InputManager = OIS::InputManager::createInputSystem(parameters);
    _Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject( OIS::OISKeyboard, false ));
    _Mouse = static_cast<OIS::Mouse*>(_InputManager->createInputObject( OIS::OISMouse, false ));
    _sManager = _sceneManager;
    _Cam = cam;
    _node = node;
    _movementspeed = 25;


    }


  ~AppFrameListener(){
    _InputManager->destroyInputObject(_Keyboard);
    _InputManager->destroyInputObject(_Mouse);
    OIS::InputManager::destroyInputSystem(_InputManager);
  }

  bool intersection(float distancia, float diametro){

    if (distancia > diametro) 
      return false;
    else
      return true;


  }

  std::string convertInt(int number){
    std::stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
  }

  bool frameStarted(const Ogre::FrameEvent& evt){
    
    Ogre::Vector3 translate(0,0,0);
    
    _Keyboard->capture();
      

    if(_Keyboard->isKeyDown(OIS::KC_ESCAPE)){
      return false;
    }


    if(_Keyboard->isKeyDown(OIS::KC_W)){
      if (_Cam->getPosition().z < 400.0)
        translate += Ogre::Vector3(0,0,-0.01);
      printf("adelante z=%f\n",_Cam->getPosition().z);
    }

    if(_Keyboard->isKeyDown(OIS::KC_S)){
      
      translate += Ogre::Vector3(0,0,0.1);
      printf("Atras z=%f\n",_Cam->getPosition().z);
  
    }

    if(_Keyboard->isKeyDown(OIS::KC_A)){
      if (_Cam->getPosition().x < 30.0)
        carting->moveLeft();
        //translate += Ogre::Vector3(-0.1,0,0);
      printf("x=%f\n",carting->getPos());
    }

    if(_Keyboard->isKeyDown(OIS::KC_D)){
      if (_Cam->getPosition().x > -30.0)
        carting->moveRight();
        //translate += Ogre::Vector3(0.1,0,0);
      printf("x=%f\n",carting->getPos());
    }

    


    _Cam->moveRelative(translate*evt.timeSinceLastFrame * 6000);

    _Mouse->capture();
    float rotX = _Mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1 /1000;
    float rotY = _Mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1 /1000;
    _Cam->yaw(Ogre::Radian(rotX));
    _Cam->pitch(Ogre::Radian(rotY));


    return true;
  }
  

  bool frameEnded(const Ogre::FrameEvent& evt){
    //std::cout << "Frame ended" << std::endl;
    return true;
  }

  bool frameRenderingQueued(const Ogre::FrameEvent& evt){
    //std::cout << "Frame queued" << std::endl;
    return true;
  }


};

class cAplicacion {

  private:
    Ogre::SceneManager* _sceneManager;
    Ogre::Root* _root;
    AppFrameListener* _listener;
    Ogre::Camera* camera;
    bool _keepRunning;
    

    public:

      // Constructor de la clase
      cAplicacion(){
        _sceneManager = NULL;
        _root = NULL;
        _listener = NULL;
      }

      ~cAplicacion(){
        delete _root;
        delete _listener;
      }

      // Funcion que permite cargar los recursos de OGRE esto simplifica tener que cargarlos uno por uno
      void loadResources(){
        Ogre::ConfigFile cf;
        cf.load("resources_d.cfg");

        Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
        Ogre::String sectionName, typeName, dataname;
        
        while (sectionIter.hasMoreElements()){
          sectionName = sectionIter.peekNextKey();
          Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
          Ogre::ConfigFile::SettingsMultiMap::iterator i;

          for (i = settings->begin(); i != settings->end(); ++i){
            typeName = i->first;
            dataname = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataname, typeName, sectionName);
          }
        
        }

        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
      }


      // funcion que configura la camara
      void createCamera(Ogre::RenderWindow* window){
        camera = _sceneManager->createCamera("Camera");
        camera->setPosition(Ogre::Vector3(0,60,-100));
        camera->lookAt(Ogre::Vector3(0,0,50));
        camera->setNearClipDistance(5);

        Ogre::Viewport* viewport = window->addViewport(camera);
        viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
        camera->setAspectRatio(Ogre::Real(viewport->getActualWidth())/Ogre::Real(viewport->getActualHeight()));

      }

      // funcion donde se coloca lo que se desea desplegar.
      void createScene(){
                

        _sceneManager->setAmbientLight(Ogre::ColourValue(0.2,0.2,0.2));
        _sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
        

      
        // LUZ
        

        Ogre::Light* LuzPuntual01 = _sceneManager->createLight("Luz01");
        LuzPuntual01->setType(Ogre::Light::LT_DIRECTIONAL);
        LuzPuntual01->setDiffuseColour(1.0,1.0,1.0);
        LuzPuntual01->setDirection(Ogre::Vector3( 1, -1, -1 ));

        Ogre::Light* LuzPuntual02 = _sceneManager->createLight("Luz02");
        LuzPuntual02->setType(Ogre::Light::LT_DIRECTIONAL);
        LuzPuntual02->setDiffuseColour(1.0,1.0,1.0);
        LuzPuntual02->setDirection(Ogre::Vector3( -1, -1, -1 ));

        //BordePista
        Ogre::SceneNode* _nodeBPista = _sceneManager->createSceneNode("BordePista");
        _sceneManager->getRootSceneNode()->addChild(_nodeBPista);
        
        Ogre::Entity* _entBPista = _sceneManager->createEntity("BordePista01", "bordePista.mesh");
        _nodeBPista->attachObject(_entBPista);


        //PisoObstaculo
        Ogre::SceneNode* _nodePObstaculo = _sceneManager->createSceneNode("PistaObstaculo");
        _sceneManager->getRootSceneNode()->addChild(_nodePObstaculo);
        
        Ogre::Entity* _entPObstaculo = _sceneManager->createEntity("PistaObstaculo", "pisoObstaculo01.mesh");
        _nodePObstaculo->attachObject(_entPObstaculo);

        //PisoNOObstaculo
        Ogre::SceneNode* _nodePNObstaculo = _sceneManager->createSceneNode("PistaNoObstaculo");
        _sceneManager->getRootSceneNode()->addChild(_nodePNObstaculo);
        
        Ogre::Entity* _entPNOObstaculo = _sceneManager->createEntity("PistaNoObstaculo", "pisoNoObstaculo01.mesh");
        _nodePNObstaculo->attachObject(_entPNOObstaculo);


        //PosterInicioFinal
        Ogre::SceneNode* _nodePoster = _sceneManager->createSceneNode("PosterInicioFinal");
        _sceneManager->getRootSceneNode()->addChild(_nodePoster);
        
        Ogre::Entity* _entPoster = _sceneManager->createEntity("PosterInicioFinal", "posterInicioFinal.mesh");
        _nodePoster->attachObject(_entPoster);

        
        //BanderaInicial
        Ogre::SceneNode* _nodeBInicial = _sceneManager->createSceneNode("BanderaInicial");
        _sceneManager->getRootSceneNode()->addChild(_nodeBInicial);
        
        Ogre::Entity* _entBanderaI = _sceneManager->createEntity("BanderaInicial", "banderaInicial.mesh");
        _nodeBInicial->attachObject(_entBanderaI);

        //BanderaFinal
        Ogre::SceneNode* _nodeBFinal = _sceneManager->createSceneNode("BanderaFinal");
        _sceneManager->getRootSceneNode()->addChild(_nodeBFinal);
        
        Ogre::Entity* _entBanderaF = _sceneManager->createEntity("BanderaFinal", "banderaFinal.mesh");
        _nodeBFinal->attachObject(_entBanderaF);

        carting = new kart(_sceneManager);
		caja1 = new box(_sceneManager, -15.0, 5.0, 0.0, 0.0, 0.0, 0.0);
		caja2 = new box(_sceneManager, -25.0, 5.0, 0.0, 0.0, 0.0, 0.0);
		caja3 = new box(_sceneManager, -35.0, 5.0, 0.0, 0.0, 0.0, 0.0);


      }


      void renderOneFrame(){
        Ogre::WindowEventUtilities::messagePump();
        _keepRunning = _root->renderOneFrame();
      }

      bool keepRunning(){
        return _keepRunning;
      }

      //Funcion que inicializa la aplicacion
      int startup(){
        _root = new Ogre::Root("plugins_d.cfg");
        
        //Muestra la ventana inicial...
        
        //if(!_root->showConfigDialog()){
        //  return -1;
        //}


        // Evitan cargar la ventana inicial...
        Ogre::RenderSystem* _rs = _root->getRenderSystemByName("Direct3D9 Rendering Subsystem");
        // or use "OpenGL Rendering Subsystem"
        _root->setRenderSystem(_rs);
        _rs->setConfigOption("Full Screen", "No");
        _rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
        _rs->setConfigOption("FSAA", "0");
        _rs->setConfigOption("Floating-point mode", "Fastest");
        _rs->setConfigOption("Use Multihead", "Auto");
        _rs->setConfigOption("VSync", "No");
        _rs->setConfigOption("VSync Interval", "1");


      
        Ogre::RenderWindow* window = _root->initialise(true,"Ventana de Ogre3D");
        _sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);

        
        loadResources();
        createScene();
        createCamera(window);

        //Agrego el nodo de la camara al nodo del carro
        Ogre::SceneNode* nodeCamara = _sceneManager->createSceneNode("nodeCamara");
        nodeCamara->attachObject(camera);
        (carting->getKart())->addChild(nodeCamara);

        _listener = new AppFrameListener(window,camera,carting->getKart(),_sceneManager);
        _root->addFrameListener(_listener);       


        //_root->startRendering();
        return 0;

        
      }


};




int main (void)
{
  cAplicacion app;
  app.startup();

  while(app.keepRunning()){
    app.renderOneFrame();
  }

  return 0;
    
}