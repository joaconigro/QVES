#include "PanelsDelegateMediator.h"

void PanelsDelegateMediator::delegateDataPanelConnections() const
{
    connect(mDataPanel, &DataPanel::currentVESModelIndexChanged, mDelegate, &QVESModelDelegate::changeCurrentModel);
    connect(mDataPanel, &DataPanel::rowSelectionChanged, mDelegate, &QVESModelDelegate::onSelectionChanged);
    connect(mDataPanel, &DataPanel::showedDataChanged, mDelegate, &QVESModelDelegate::showedTableDataChanged);
    connect(mDelegate, &QVESModelDelegate::currentVESNameChanged, mDataPanel, &DataPanel::loadVESNames);
    connect(mDelegate, &QVESModelDelegate::tableModelChanged, mDataPanel, &DataPanel::setMyModel);
    connect(mDelegate, &QVESModelDelegate::VESChanged, mDataPanel, &DataPanel::setMyModel);
    connect(mDelegate, &QVESModelDelegate::restoreSelection, mDataPanel, &DataPanel::restoreSelection);
}

void PanelsDelegateMediator::delegatePropertiesPanelConnections() const
{
    connect(mDelegate, &QVESModelDelegate::VESChanged, mPropertiesPanel, &VESPropertiesPanel::loadVES);
}

void PanelsDelegateMediator::delegateChartConnections() const
{
    connect(mDelegate, &QVESModelDelegate::selectionChanged, mChart, &MainChart::onSelectionChanged);
    connect(mDelegate, &QVESModelDelegate::currentVESNameChanged, mChart, &MainChart::setChartTitle);
    connect(mDelegate, &QVESModelDelegate::VESChanged, mChart, &MainChart::modelDelegateChanged);
}

void PanelsDelegateMediator::delegateUndoManagerConnections() const
{
    connect(mDelegate, &QVESModelDelegate::onVESDataChanged,  mCommandManager, &CommandsManager::onVESDataChanged);
}

void PanelsDelegateMediator::propertiesPanelManagerConnections() const
{
    connect(mPropertiesPanel, &VESPropertiesPanel::VESNameEdited, mCommandManager, &CommandsManager::onVESNameEdited);
}

void PanelsDelegateMediator::dataPanelManagerConnections() const
{
    connect(mDataPanel, &DataPanel::currentVESIndexChanged,  mCommandManager, &CommandsManager::currentVESChanged);
}

PanelsDelegateMediator::PanelsDelegateMediator(QVESModelDelegate *delegate, DataPanel *dataPanel, VESPropertiesPanel *propertiesPanel,
                                               MainChart *chart, CommandsManager *manager, QObject *parent) : mDelegate(delegate),
    mDataPanel(dataPanel), mPropertiesPanel(propertiesPanel), mChart(chart), mCommandManager(manager), QObject(parent)
{
    delegateDataPanelConnections();
    delegatePropertiesPanelConnections();
    delegateChartConnections();
    delegateUndoManagerConnections();
    propertiesPanelManagerConnections();
    dataPanelManagerConnections();
}
