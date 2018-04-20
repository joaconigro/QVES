#include "CommandsManager.h"

CommandsManager::CommandsManager(QVESModelDelegate *delegate, QVESSettings *settings, QObject *parent) :
    QObject(parent), mDelegate(delegate), mSettings(settings)
{
    mUndoStack = new QUndoStack(this);
}

void CommandsManager::undo() const
{
    mUndoStack->undo();
}

void CommandsManager::redo() const
{
    mUndoStack->redo();
}

void CommandsManager::clear() const
{
    mUndoStack->clear();
}

void CommandsManager::onZohdyInversion()
{
    auto command = new ZohdyInversionCommand(mDelegate, mSettings->zohdyFilter(), mSettings->autoDarZarrouk(), mSettings->autoDarZarroukThreshold());
    mUndoStack->push(command);
}

void CommandsManager::currentVESChanged(const int index)
{
    auto command = new ChangeCurrentVESCommand(mDelegate, index);
    mUndoStack->push(command);
}

void CommandsManager::onVESNameEdited(const QString &name)
{
    auto command = new EditVESNameCommand(mDelegate, name);
    mUndoStack->push(command);
}

void CommandsManager::onVESDataChanged(const QModelIndex &index, const int dataType, const double oldValue, const double newValue) const
{
    auto command = new EditVESDataCommand(mDelegate, index, oldValue, newValue, dataType);
    mUndoStack->push(command);
}
