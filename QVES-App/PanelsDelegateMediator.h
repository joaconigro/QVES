#ifndef PANELSDELEGATEMEDIATOR_H
#define PANELSDELEGATEMEDIATOR_H

#include <QObject>
#include "MainChart.h"
#include "QVESModelDelegate.h"
#include "DataPanel.h"
#include "VESPropertiesPanel.h"

class PanelsDelegateMediator : public QObject
{
    Q_OBJECT

    QVESModelDelegate *mDelegate;
    DataPanel *mDataPanel;
    VESPropertiesPanel *mPropertiesPanel;
    MainChart *mChart;


    void delegateDataPanelConnections() const;
    void delegatePropertiesPanelConnections() const;
    void delegateChartConnections() const;

public:
    explicit PanelsDelegateMediator(QVESModelDelegate *delegate, DataPanel *dataPanel, VESPropertiesPanel *propertiesPanel,
                                    MainChart *chart, QObject *parent = nullptr);

signals:

public slots:
};

#endif // PANELSDELEGATEMEDIATOR_H
