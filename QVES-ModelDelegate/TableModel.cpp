#include "TableModel.h"
#include <QList>
#include <QtGui/QVector2D>

TableModel::TableModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mTable.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                if (mTypeOfData == DataType::Model){
                    return tr("Profundidad");
                } else {
                    return tr("Distancia AB/2");
                }
            case 1:
                return tr("Resistividad");

            default:
                return QVariant();
        }
    } else if (orientation == Qt::Vertical) {
        return (section + 1);
    }
    return QVariant();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole){
        if (index.column() == 0){
            return mTable.at(index.row())->x();
        }else{
            return mTable.at(index.row())->y();
        }
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignRight;
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        XYDataTable *temp = new XYDataTable(mTable.at(index.row())->x(), mTable.at(index.row())->y());
        double tempValue = value.toDouble();
        if (index.column() == 0) {
            if (index.row() == 0){
                if (tempValue < mTable.at(index.row() + 1)->x()){
                    temp->setX(tempValue);
                }
            }else if (index.row() == mTable.count() - 1) {
                if (tempValue > mTable.at(index.row() - 1)->x()){
                    temp->setX(tempValue);
                }
            } else if ((tempValue > mTable.at(index.row() - 1)->x()) && (tempValue < mTable.at(index.row() + 1)->x())){
                temp->setX(tempValue);
            } else {
                return false;
            }
        } else if (index.column() == 1) {
            if (tempValue > 0.0)
                temp->setY(tempValue);
        } else
            return false;

        mTable.replace(index.row(), temp);
        emit myTableChanged(index);
        emit dataChanged(index, index);
        return true;
    }

    return false;

}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void TableModel::setTableFromVES(const QList<XYDataTable *> &table, DataType type)
{
    beginResetModel();
    mTypeOfData = type;
    mTable.clear();
    for (int i = 0; i<table.count(); i++){
        mTable.append(table.at(i));
    }
    endResetModel();
}

//TableModel *TableModel::modelFromSelection(const QList<int> &indices, QObject *parent)
//{
//    TableModel *selectedData = new TableModel(parent);
//    QList<XYDataTable *> newTable;
//    foreach (auto i, indices) {
//        newTable.append(mTable.at(i));
//    }
//    selectedData->setTableFromVES(newTable, mTypeOfData);
//    return selectedData;
//}
