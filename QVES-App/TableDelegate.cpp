#include "TableDelegate.h"

TableDelegate::TableDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{
}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    Q_UNUSED(option)
    auto dValidator = new QDoubleValidator(parent);
    dValidator->setBottom(0.0001);
    dValidator->setNotation(QDoubleValidator::Notation::StandardNotation);

    auto editor = new QLineEdit(parent);
    editor->setFrame(false);
    editor->setValidator(dValidator);

    return editor;
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::DisplayRole).toDouble();

    auto lineEdit = static_cast<QLineEdit*>(editor);
    QLocale qLoc;
    lineEdit->setText(qLoc.toString(value));
}

void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto lineEdit = static_cast<QLineEdit*>(editor);
    QLocale qLoc;
    QString tempText = lineEdit->text();
    tempText.replace(".", qLoc.decimalPoint());
    tempText.replace(",", qLoc.decimalPoint());
    double value = qLoc.toDouble(tempText);

    model->setData(index, value, Qt::EditRole);
}

void TableDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}
