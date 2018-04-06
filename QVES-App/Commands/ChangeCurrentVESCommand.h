#ifndef CHANGECURRENTVESCOMMAND_H
#define CHANGECURRENTVESCOMMAND_H

#include <QUndoCommand>
#include "QVESModelDelegate.h"

class ChangeCurrentVESCommand : public QUndoCommand
{
    int mPreviousIndex;
    int mNewIndex;
    const QVESModelDelegate *mDelegate;

public:
    ChangeCurrentVESCommand(const QVESModelDelegate *delegate, const int newIndex);

    void undo() override;
    void redo() override;
};

#endif // CHANGECURRENTVESCOMMAND_H
