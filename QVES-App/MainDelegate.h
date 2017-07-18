#ifndef MAINDELEGATE_H
#define MAINDELEGATE_H

#include <QObject>

class MainDelegate : public QObject
{
    Q_OBJECT
public:
    explicit MainDelegate(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MAINDELEGATE_H