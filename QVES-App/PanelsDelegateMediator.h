#ifndef PANELSDELEGATEMEDIATOR_H
#define PANELSDELEGATEMEDIATOR_H

#include <QObject>
#include "MainChart.h"
#include "QVESModelDelegate.h"
#include "DataPanel.h"
#include "VESPropertiesPanel.h"
#include "Commands/CommandsManager.h"

class PanelsDelegateMediator : public QObject
{
    Q_OBJECT

    QVESModelDelegate *mDelegate;
    DataPanel *mDataPanel;
    VESPropertiesPanel *mPropertiesPanel;
    MainChart *mChart;
    CommandsManager *mCommandManager;

    void delegateDataPanelConnections() const;
    void delegatePropertiesPanelConnections() const;
    void delegateChartConnections() const;
    void delegateUndoManagerConnections() const;
    void propertiesPanelManagerConnections() const;
    void dataPanelManagerConnections() const;

public:
    explicit PanelsDelegateMediator(QVESModelDelegate *delegate, DataPanel *dataPanel, VESPropertiesPanel *propertiesPanel,
                                    MainChart *chart, CommandsManager *manager, QObject *parent = nullptr);

signals:

public slots:
};

#endif // PANELSDELEGATEMEDIATOR_H
