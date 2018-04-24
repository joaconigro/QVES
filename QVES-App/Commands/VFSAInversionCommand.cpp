#include "VFSAInversionCommand.h"

VFSAInversionCommand::VFSAInversionCommand(const QVESModelDelegate *delegate) :
    mDelegate(delegate)
{
    mDelegate->currentVES()->VFSAInversion();
}

void VFSAInversionCommand::undo()
{

}

void VFSAInversionCommand::redo()
{

}
