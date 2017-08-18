#include "TableModel.h"
#include <QList>
#include <QtGui/QVector2D>

TableModel::TableModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
   return mTable.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0){
            return mTable.at(index.row())->x();
        }else{
            return mTable.at(index.row())->y();
        }
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return true;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void TableModel::setTableFromVES(const QList<ModelDataTable *> &table)
{
    beginResetModel();
    mTable.clear();
    for (int i = 0; i<table.count(); i++){
        mTable.append(table.at(i));
    }
    endResetModel();
}
