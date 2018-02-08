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
    QString mProjectFileName;
    QString mProjectPath;

public:
    VESCore(QObject *parent);

    Project *project();
    QString projectPath() const;
    QString projectFileName() const;

signals:
    void projectLoaded();
    void projectClosed();

public slots:
    bool openProject(const QString &filename);
    bool saveProject(const QString &filename);
    bool saveProject();
    void changeDataForCurrentVES(const int row, const int column, const int dataType, const double value);
};

#endif // VESCORE_H
