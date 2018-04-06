#include "PanelsDelegateMediator.h"

void PanelsDelegateMediator::delegateDataPanelConnections() const
{
    connect(mDataPanel, &DataPanel::currentVESModelIndexChanged, mDelegate, &QVESModelDelegate::changeCurrentModel);
    connect(mDataPanel, &DataPanel::rowSelectionChanged, mDelegate, &QVESModelDelegate::onSelectionChanged);
    connect(mDataPanel, &DataPanel::showedDataChanged, mDelegate, &QVESModelDelegate::showedTableDataChanged);
    connect(mDelegate, &QVESModelDelegate::currentVESNameChanged, mDataPanel, &DataPanel::loadVESNames);
    connect(mDelegate, &QVESModelDelegate::tableModelChanged, mDataPanel, &DataPanel::setMyModel);
    connect(mDelegate, &QVESModelDelegate::VESChanged, mDataPanel, &DataPanel::setMyModel);
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

PanelsDelegateMediator::PanelsDelegateMediator(QVESModelDelegate *delegate, DataPanel *dataPanel, VESPropertiesPanel *propertiesPanel,
                                               MainChart *chart, QObject *parent) : mDelegate(delegate),
    mDataPanel(dataPanel), mPropertiesPanel(propertiesPanel), mChart(chart), QObject(parent)
{
    delegateDataPanelConnections();
    delegatePropertiesPanelConnections();
    delegateChartConnections();

}
