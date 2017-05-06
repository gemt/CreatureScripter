#include "eventaidefcommon.h"

#ifdef ELYSIUM
#include "eventaidefelysium.h"
#else
#include "eventaidefcmangos.h"
#endif

namespace EventAI
{

const Parameter EventAI_event::phaseMask = Parameter{ParameterType::EVENT_PHASE_MASK, "Phase Mask", phase_mask_tooltip};
const Parameter EventAI_event::eventFlags = Parameter{ParameterType::EVENT_FLAGS, "Event Flags", ""};


}
