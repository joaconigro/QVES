#include "ChangeCurrentVESCommand.h"

ChangeCurrentVESCommand::ChangeCurrentVESCommand(const QVESModelDelegate *delegate, const int newIndex)
{
    mDelegate = delegate;
    mPreviousIndex = mDelegate->currentVESIndex();
    mNewIndex = newIndex;
}

void ChangeCurrentVESCommand::undo()
{
    mDelegate->selectedVESChanged(mPreviousIndex);
}

void ChangeCurrentVESCommand::redo()
{
    mDelegate->selectedVESChanged(mNewIndex);
}
