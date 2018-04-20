#ifndef COMMANDSMANAGER_H
#define COMMANDSMANAGER_H

#include <QObject>
#include <QUndoStack>
#include "QVESModelDelegate.h"
#include "QVESSettings.h"
#include "Commands/ZohdyInversionCommand.h"
#include "Commands/ChangeCurrentVESCommand.h"
#include "Commands/EditVESNameCommand.h"
#include "Commands/EditVESDataCommand.h"

class CommandsManager : public QObject
{
    Q_OBJECT

    QUndoStack *mUndoStack;
    QVESModelDelegate *mDelegate;
    QVESSettings *mSettings;

public:
    CommandsManager(QVESModelDelegate *delegate, QVESSettings *settings, QObject *parent = nullptr);



public slots:
    void undo() const;
    void redo() const;
    void clear() const;


    void onZohdyInversion();
    void currentVESChanged(const int index);
    void onVESNameEdited(const QString& name);
    void onVESDataChanged(const QModelIndex &index, const int dataType, const double oldValue, const double newValue) const;

};

#endif // COMMANDSMANAGER_H
