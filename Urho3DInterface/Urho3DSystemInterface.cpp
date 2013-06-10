#include "Urho3DSystemInterface.h"
#include "Context.h"
#include "Timer.h"

using namespace Urho3D;

// Get the number of seconds elapsed since the start of the application
float Urho3DSystemInterface::GetElapsedTime()
{
    Time* time = this->context->GetSubsystem<Time>();
    return time->GetElapsedTime();
}
