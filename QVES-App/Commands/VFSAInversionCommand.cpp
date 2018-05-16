#include "VFSAInversionCommand.h"

VFSAInversionCommand::VFSAInversionCommand(const QVESModelDelegate *delegate, const QVESSettings *settings) :
    mDelegate(delegate)
{
    mSettingsParameters.setInitialTemperature(settings->vFSAInitialTemperature());
    mSettingsParameters.setIterationsPerTemperature(settings->vFSAIterationsPerTemperature());
    mSettingsParameters.setMaximunError(settings->vFSAMaximunError());
    mSettingsParameters.setMovesPerTemperature(settings->vFSAMovesPerTemperature());
    mSettingsParameters.setNumberOfBeds(settings->vFSANumberOfBeds());
    mSettingsParameters.setNumberOfParameters(settings->vFSANumberOfBeds() * 2 - 1);
    mSettingsParameters.setSolutions(settings->vFSASolutions());


    VFSAInversionDialog dialog(mDelegate->currentVES(), mSettingsParameters);
    if (dialog.exec()){
        models.append(dialog.finalModels());
        mNewVESParameters = dialog.currentParameters();
    }


   // mDelegate->currentVES()->VFSAInversion();
}

void VFSAInversionCommand::undo()
{
    if (models.count() > 0){
        foreach (auto m, models) {
            mDelegate->currentVES()->removeInversionModel(m);
        }
        mDelegate->currentVES()->setCurrentParameters(mNewVESParameters);
    }
}

void VFSAInversionCommand::redo()
{
    if (models.count() > 0){
        foreach (auto m, models) {
            mDelegate->currentVES()->addInversionModel(m);
        }
        mDelegate->currentVES()->setCurrentParameters(mNewVESParameters);
    }
}
