#ifndef CHARTDELEGATE_H
#define CHARTDELEGATE_H

#include <QObject>
#include "qves-modeldelegate_global.h"
#include "TableModel.h"
#include "VES.h"
#include <QString>

class QVESMODELDELEGATESHARED_EXPORT ChartDelegate : public QObject
{
    Q_OBJECT
    TableModel *mFieldChartModel;
    TableModel *mSpliceChartModel;
    TableModel *mCalculatedChartModel;
    TableModel *mModeledChartModel;
    TableModel *mHighlightedXYChartModel;
    TableModel *mHighlightedLineChartModel;
    double mChartMinX;
    double mChartMinY;
    double mChartMaxX;
    double mChartMaxY;
    QString mVESName;

public:
    explicit ChartDelegate(QObject *parent = nullptr);

    //Getters
    TableModel *fieldChartModel() const;
    TableModel *spliceChartModel() const;
    TableModel *calculatedChartModel() const;
    TableModel *modeledChartModel() const;
    TableModel *highlightedXYChartModel() const;
    TableModel *highlightedLineChartModel() const;
    double chartMinX() const;
    double chartMinY() const;
    double chartMaxX() const;
    double chartMaxY() const;
    QString vesName() const;

    //Setters
    void setFieldChartModel(TableModel *table);
    void setSpliceChartModel(TableModel *table);
    void setCalculatedChartModel(TableModel *table);
    void setModeledChartModel(TableModel *table);
    void setHighlightedXYChartModel(TableModel *table);
    void setHighlightedLineChartModel(TableModel *table);

signals:
    void modelsChanged();

public slots:
    void configureModelsFromVES(const VES *ves);

};

#endif // CHARTDELEGATE_H
