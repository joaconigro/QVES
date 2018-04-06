#include "ZohdyInversionCommand.h"

ZohdyInversionCommand::ZohdyInversionCommand(const QVESModelDelegate *delegate, const int zohdyFilter, const bool autoDZ, const double autoDZThreshold)
{
    mDelegate = delegate;
    mPreviousModelIndex = mDelegate->currentVES()->currentIndexModel();
    model = mDelegate->currentVES()->zohdyInversion(zohdyFilter, autoDZ, autoDZThreshold);
}

void ZohdyInversionCommand::undo()
{
    mDelegate->currentVES()->removeInversionModel(model, mPreviousModelIndex);
}

void ZohdyInversionCommand::redo()
{
    mDelegate->currentVES()->addInversionModel(model);
}
