#ifndef ROCKETURHO3DSYSTEMINTERFACE_H
#define ROCKETURHO3DSYSTEMINTERFACE_H

#include <Rocket/Core/SystemInterface.h>
#include "Context.h"

/**
	A custom system interface for Rocket. This provides timing information.
 */

class Urho3DSystemInterface : public Rocket::Core::SystemInterface
{
private:
    Urho3D::Context* context;
    
public:
    Urho3DSystemInterface(Urho3D::Context* context)
        : context(context) {};
   
	/// Get the number of seconds elapsed since the start of the application
	/// @returns Seconds elapsed
	virtual float GetElapsedTime();
};

#endif
