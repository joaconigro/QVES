#include "TableDelegate.h"

TableDelegate::TableDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{
}

QWidget *TableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleValidator *dValidator = new QDoubleValidator(parent);
    dValidator->setBottom(0.0001);
    dValidator->setNotation(QDoubleValidator::Notation::StandardNotation);

    QLineEdit *editor = new QLineEdit(parent);
    editor->setFrame(false);
    editor->setValidator(dValidator);

    return editor;
}

void TableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::DisplayRole).toDouble();

    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QLocale qLoc;
    lineEdit->setText(qLoc.toString(value));
}

void TableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QLocale qLoc;
    double value = qLoc.toDouble(lineEdit->text());

    model->setData(index, value, Qt::EditRole);
}

void TableDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}
