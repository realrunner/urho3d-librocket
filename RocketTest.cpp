#include "Camera.h"
#include "Context.h"
#include "CoreEvents.h"
#include "Engine.h"
#include "Font.h"
#include "Input.h"
#include "Light.h"
#include "Material.h"
#include "Model.h"
#include "Octree.h"
#include "ProcessUtils.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Scene.h"
#include "StaticModel.h"
#include "Text.h"
#include "UI.h"
#include "Main.h"
#include "DebugNew.h"
#include "Graphics.h"
#include "GraphicsEvents.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


#include "Urho3DInterface/Urho3DRenderInterface.h"
#include "Urho3DInterface/Urho3DSystemInterface.h"
#include <Rocket/Core.h>

using namespace Urho3D;

class HelloWorld : public Object
{
    OBJECT(HelloWorld);
    
    Rocket::Core::Context* rocketContext;
    Urho3DSystemInterface rocketSystemInterface;
    Urho3DRenderInterface rocketRenderer;
    
    
public:
    HelloWorld(Context* context);
    void Start();
    void Stop();
    void CreateObjects();
    void CreateText();
    void SubscribeToEvents();
    void HandleUpdate(StringHash eventType, VariantMap& eventData);
    void HandlePostRender(StringHash eventType, VariantMap& eventData);
    SharedPtr<Scene> helloScene_;
    SharedPtr<ResourceCache> cache_;
};

int Run()
{
    SharedPtr<Context> context(new Context());
    SharedPtr<Engine> engine(new Engine(context));
    VariantMap engineParameters = Engine::ParseParameters(GetArguments());
    engineParameters["WindowTitle"] = "HelloWorld";
    engineParameters["LogName"] = "HelloWorld.log";
//    engineParameters["WindowWidth"] = 1024;
//    engineParameters["WindowHeight"] = 768;
//    engineParameters["FullScreen"] = false;
    engine->Initialize(engineParameters);
    SharedPtr<HelloWorld> helloWorld(new HelloWorld(context));
    helloWorld->Start();
    while (!engine->IsExiting())
        engine->RunFrame();
    
    helloWorld->Stop();
    return 0;
}
DEFINE_MAIN(Run())

OBJECTTYPESTATIC(HelloWorld);
HelloWorld::HelloWorld(Context* context) :
    Object(context),
    rocketContext(),
    rocketSystemInterface(context),
    rocketRenderer(context),
    cache_(GetSubsystem<ResourceCache>())
{
}

void HelloWorld::Start()
{
    helloScene_ = new Scene(context_);
    CreateObjects();
    CreateText();
    SubscribeToEvents();
    
    
    //Rocket stuff
    Rocket::Core::SetRenderInterface(&rocketRenderer);
    Rocket::Core::SetSystemInterface(&rocketSystemInterface);
    
    Rocket::Core::Initialise();
    int w = GetSubsystem<Graphics>()->GetWidth();
    int h = GetSubsystem<Graphics>()->GetHeight();
    rocketContext = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(w, h));
    if(rocketContext == NULL)
    {
        Rocket::Core::Shutdown();
        throw "Dead in the water";
    }
    
    Rocket::Core::FontDatabase::LoadFontFace("Data/Fonts/Delicious-Bold.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Data/Fonts/Delicious-BoldItalic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Data/Fonts/Delicious-Italic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Data/Fonts/Delicious-Roman.otf");
    
    Rocket::Core::ElementDocument *Document = rocketContext->LoadDocument("Data/UI/rocketDemo.html");
    
    if(Document)
    {
        Document->Show();
        Document->RemoveReference();
    };
}

void HelloWorld::Stop()
{
    rocketContext->RemoveReference();
    Rocket::Core::Shutdown();
}

void HelloWorld::CreateObjects()
{
    helloScene_->CreateComponent<Octree>();
    auto objectNode = helloScene_->CreateChild();
    Node* lightNode = helloScene_->CreateChild();
    Node* cameraNode = helloScene_->CreateChild();
    StaticModel* object = objectNode->CreateComponent<StaticModel>();
    object->SetModel(cache_->GetResource<Model>("Models/Mushroom.mdl"));
    object->SetMaterial(cache_->GetResource<Material>("Materials/Mushroom.xml"));
    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    lightNode->SetDirection(Vector3(-1.0f, -1.0f, -1.0f));
    Camera* camera = cameraNode->CreateComponent<Camera>();
    cameraNode->SetPosition(Vector3(0.0f, 0.3f, -3.0f));
    GetSubsystem<Renderer>()->SetViewport(0, new Viewport(context_, helloScene_, camera));
}

void HelloWorld::CreateText()
{
    SharedPtr<Text> helloText(new Text(context_));
    helloText->SetFont(cache_->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 30);
    helloText->SetText("Hello World from Urho3D");
    helloText->SetColor(Color(0.0f, 1.0f, 0.0f));
    helloText->SetHorizontalAlignment(HA_CENTER);
    helloText->SetVerticalAlignment(VA_CENTER);
    GetSubsystem<UI>()->GetRoot()->AddChild(helloText);
}

void HelloWorld::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, HANDLER(HelloWorld, HandleUpdate));
    SubscribeToEvent(E_ENDRENDERING, HANDLER(HelloWorld, HandlePostRender));
}

void HelloWorld::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    //float timeStep = eventData[Update::P_TIMESTEP].GetFloat();        
    rocketContext->Update();
    
    if (GetSubsystem<Input>()->GetKeyDown(KEY_ESC))
        GetSubsystem<Engine>()->Exit();
}

void HelloWorld::HandlePostRender(StringHash eventType, VariantMap &eventData)
{
    rocketContext->Render();
}

