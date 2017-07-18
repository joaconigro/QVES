#ifndef PANELDELEGATE_H
#define PANELDELEGATE_H

#include <QObject>

class PanelDelegate : public QObject
{
    Q_OBJECT
public:
    explicit PanelDelegate(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PANELDELEGATE_H