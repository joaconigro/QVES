#ifndef CHARTDELEGATE_H
#define CHARTDELEGATE_H

#include <QObject>

class ChartDelegate : public QObject
{
    Q_OBJECT
public:
    explicit ChartDelegate(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CHARTDELEGATE_H