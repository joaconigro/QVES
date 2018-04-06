#include "EditVESNameCommand.h"

EditVESNameCommand::EditVESNameCommand(const QVESModelDelegate *delegate, const QString newName)
{
    mDelegate = delegate;
    mNewName = newName;
    mPreviousName = mDelegate->currentVES()->name();
}

void EditVESNameCommand::undo()
{
    mDelegate->currentVES()->setName(mPreviousName);
}

void EditVESNameCommand::redo()
{
    mDelegate->currentVES()->setName(mNewName);
}
