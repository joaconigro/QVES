#ifndef EDITVESNAMECOMMAND_H
#define EDITVESNAMECOMMAND_H

#include <QUndoCommand>
#include "QVESModelDelegate.h"

class EditVESNameCommand : public QUndoCommand
{
    QString mPreviousName;
    QString mNewName;
    const QVESModelDelegate *mDelegate;

public:
    EditVESNameCommand(const QVESModelDelegate *delegate, const QString newName);

    void undo() override;
    void redo() override;
};

#endif // EDITVESNAMECOMMAND_H
