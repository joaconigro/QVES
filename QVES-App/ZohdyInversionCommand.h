#ifndef ZOHDYINVERSIONCOMMAND_H
#define ZOHDYINVERSIONCOMMAND_H

#include <QUndoCommand>
#include "QVESModelDelegate.h"
#include "ZohdyModel.h"

class ZohdyInversionCommand : public QUndoCommand
{
    ZohdyModel *model;
    const QVESModelDelegate *mDelegate;
    int mPreviousModelIndex;
    int mNewModelIndex;

public:
    ZohdyInversionCommand(const QVESModelDelegate *delegate, const int zohdyFilter, const bool autoDZ, const double autoDZThreshold);

    void undo() override;
    void redo() override;
};

#endif // ZOHDYINVERSIONCOMMAND_H
