#ifndef EDITVESDATACOMMAND_H
#define EDITVESDATACOMMAND_H

#include <QUndoCommand>
#include "QVESModelDelegate.h"

class EditVESDataCommand : public QUndoCommand
{

    double mPreviousValue;
    double mNewValue;
    int mDataType;
    QModelIndex mIndex;
    QVESModelDelegate *mDelegate;

public:
    EditVESDataCommand(QVESModelDelegate *mDelegate, const QModelIndex &index, const double oldValue, const double newValue, const int dataType);

    void undo() override;
    void redo() override;
};

#endif // EDITVESDATACOMMAND_H
