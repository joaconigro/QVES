#ifndef VESCORE_H
#define VESCORE_H

#include "ves-core_global.h"
#include "Project.h"
#include "OldProject.h"
#include <QObject>
#include "XmlSerializer.h"

class VESCORESHARED_EXPORT VESCore: public QObject
{
    Q_OBJECT

    Project *mProject;
public:
    VESCore(QObject *parent);

    Project *project();

signals:
    void projectLoaded();

public slots:
    bool openProject(const QString &filename);
};

#endif // VESCORE_H
