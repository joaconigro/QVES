#include "ChartDelegate.h"
#include "ModelDataTable.h"
#include <QList>
#include <QtMath>

ChartDelegate::ChartDelegate(QObject *parent) : QObject(parent)
{
    mFieldChartModel = nullptr;
    mSpliceChartModel = nullptr;
    mCalculatedChartModel = nullptr;
    mModeledChartModel = nullptr;
    mHighlightedXYChartModel = nullptr;
    mHighlightedLineChartModel = nullptr;
}

TableModel *ChartDelegate::fieldChartModel() const
{
    return mFieldChartModel;
}

TableModel *ChartDelegate::spliceChartModel() const
{
    return mSpliceChartModel;
}

TableModel *ChartDelegate::calculatedChartModel() const
{
    return mCalculatedChartModel;
}

TableModel *ChartDelegate::modeledChartModel() const
{
    return mModeledChartModel;
}

TableModel *ChartDelegate::highlightedXYChartModel() const
{
    return mHighlightedXYChartModel;
}

TableModel *ChartDelegate::highlightedLineChartModel() const
{
    return mHighlightedLineChartModel;
}

double ChartDelegate::chartMinX() const
{
    return mChartMinX;
}

double ChartDelegate::chartMinY() const
{
    return mChartMinY;
}

double ChartDelegate::chartMaxX() const
{
    return mChartMaxX;
}

double ChartDelegate::chartMaxY() const
{
    return mChartMaxY;
}

QString ChartDelegate::vesName() const
{
    return mVESName;
}

void ChartDelegate::setFieldChartModel(TableModel *table)
{
    mFieldChartModel = table;
}

void ChartDelegate::setSpliceChartModel(TableModel *table)
{
    mSpliceChartModel = table;
}

void ChartDelegate::setCalculatedChartModel(TableModel *table)
{
    mCalculatedChartModel = table;
}

void ChartDelegate::setModeledChartModel(TableModel *table)
{
    mModeledChartModel = table;
}

void ChartDelegate::setHighlightedXYChartModel(TableModel *table)
{
    mHighlightedXYChartModel = table;
}

void ChartDelegate::setHighlightedLineChartModel(TableModel *table)
{
    mHighlightedLineChartModel = table;
}

void ChartDelegate::configureModelsFromVES(const VES *ves)
{
    mVESName = ves->name();

    mChartMinX = pow(10, floor(log10(ves->minX())));
    mChartMinY = pow(10, floor(log10(ves->minY())));
    mChartMaxX = pow(10, ceil(log10(ves->maxX())));
    mChartMaxY = pow(10, ceil(log10(ves->maxY())));

    QList<ModelDataTable *> tempTable;

    mFieldChartModel = new TableModel(this);
    foreach (const auto &item, ves->fieldData()) {
        ModelDataTable *value = new ModelDataTable(item.ab2Distance(), item.resistivity());
        tempTable.append(value);
    }
    mFieldChartModel->setTableFromVES(tempTable);

    tempTable.clear();
    mSpliceChartModel = new TableModel(this);
    foreach (const auto &item, ves->splices()) {
        ModelDataTable *value = new ModelDataTable(item.ab2Distance(), item.resistivity());
        tempTable.append(value);
    }
    mSpliceChartModel->setTableFromVES(tempTable);

    tempTable.clear();
    mCalculatedChartModel = new TableModel(this);
    foreach (const auto &item, ves->currentModel()->calculatedData()) {
        ModelDataTable *value = new ModelDataTable(item.ab2Distance(), item.resistivity());
        tempTable.append(value);
    }
    mCalculatedChartModel->setTableFromVES(tempTable);

    tempTable.clear();
    mModeledChartModel = new TableModel(this);
    foreach (const auto &item, ves->currentModel()->model()) {
        if (item.from() == 0.0){
            ModelDataTable *value1 = new ModelDataTable(mChartMinX, item.resistivity());
            tempTable.append(value1);
        } else {
            ModelDataTable *value1 = new ModelDataTable(item.from(), item.resistivity());
            tempTable.append(value1);
        }
        if (item.until() == qInf()){
            ModelDataTable *value2 = new ModelDataTable(mChartMaxX, item.resistivity());
            tempTable.append(value2);
        } else {
            ModelDataTable *value2 = new ModelDataTable(item.until(), item.resistivity());
            tempTable.append(value2);
        }

    }
    mModeledChartModel->setTableFromVES(tempTable);

    emit modelsChanged();
}
