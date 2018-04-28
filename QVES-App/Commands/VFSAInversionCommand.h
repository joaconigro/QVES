#ifndef VFSAINVERSIONCOMMAND_H
#define VFSAINVERSIONCOMMAND_H

#include <QUndoCommand>
#include "QVESModelDelegate.h"
#include "QVESSettings.h"
#include "VFSA/VFSAParameters.h"
#include <QList>
#include "VFSAInversionModel.h"
#include "Dialogs/VFSAInversionDialog.h"

class VFSAInversionCommand : public QUndoCommand
{
    const QVESModelDelegate *mDelegate;
    //const QVESSettings *mSettings;

    VFSAParameters mSettingsParameters;
    VFSAParameters mVESParameters;
    VFSAParameters mNewVESParameters;

    QList<VFSAInversionModel *> models;

public:
    VFSAInversionCommand(const QVESModelDelegate *delegate, const QVESSettings *settings);

    void undo() override;
    void redo() override;
};

#endif // VFSAINVERSIONCOMMAND_H
