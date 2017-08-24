#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QDoubleValidator>
#include <QLineEdit>

class TableDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TableDelegate(QWidget *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TABLEDELEGATE_H
