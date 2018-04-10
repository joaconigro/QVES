#include "EditVESDataCommand.h"

EditVESDataCommand::EditVESDataCommand(QVESModelDelegate *delegate, const QModelIndex &index, const double oldValue, const double newValue, const int dataType)
{
    mDelegate = delegate;
    mPreviousValue = oldValue;
    mNewValue = newValue;
    mIndex = index;
    mDataType = dataType;
}

void EditVESDataCommand::undo()
{
    mDelegate->updateVESData(mIndex, mDataType, mPreviousValue);
}

void EditVESDataCommand::redo()
{
    mDelegate->updateVESData(mIndex, mDataType, mNewValue);
}
