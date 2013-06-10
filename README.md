urho3d-librocket
================

libRocket integration for urho3d.

Includes
---------
* CMakeLists.txt -- For integrating into urho3d cmake build 
* Urho3DRenderInterface -- For rendering pipeline integration 
* Urho3DSystemInterface -- For system/timing integration
* RocketTest.cpp	-- Example urho3d application demonstrating the integration

Usage
-------
Download the libRocket source and place it in your urho3d/ThirdParty directory.
Drop in this CMakeLists.txt file into the libRocket directory (i.e urho3d/ThirdParty/libRocket).
Include a reference in your application CMakeLists.txt file for libRocket's include directory
	set (LIBS ../Engine/Container ... ../ThirdParty/libRocket/Include)

Put Urho3DRenderInterface.h/.cpp and Urho3DSystemInterface.h/.cpp in your project somewhere.

Instantiate Urho3DRenderInterface and Urho3DSystemInterface with urho3d's context.
Register them with libRocket: 
````c++
Rocket::Core::SetRenderInterface(&rocketRenderer);
Rocket::Core::SetSystemInterface(&rocketSystemInterface);
````

Setup libRocket as normal (look at the examples).
	
Subscribe to the E_ENDRENDERING event:

````c++
SubscribeToEvent(E_ENDRENDERING, HANDLER(HelloWorld, HandlePostRender));
````
  
and call rocket's render method in HandlePostRender.

If you want to run the RocketTest.cpp example you need to merge the Data/* directory with the Bin/Data directory that comes with Urho3D.

Notes
--------
This integration excludes python. 
It also makes no assumptions about user input. See the libRocket docs for user input integration: http://librocket.com/wiki/documentation/C%2B%2BManual/Input
