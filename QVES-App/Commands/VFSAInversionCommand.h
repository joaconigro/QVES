#ifndef VFSAINVERSIONCOMMAND_H
#define VFSAINVERSIONCOMMAND_H

#include <QUndoCommand>
#include "QVESModelDelegate.h"

class VFSAInversionCommand : public QUndoCommand
{
    const QVESModelDelegate *mDelegate;

public:
    VFSAInversionCommand(const QVESModelDelegate *delegate);

    void undo() override;
    void redo() override;
};

#endif // VFSAINVERSIONCOMMAND_H
