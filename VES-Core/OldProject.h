#ifndef OLDPROJECT_H
#define OLDPROJECT_H
#include "ves-core_global.h"
#include <QObject>
#include <QXmlStreamReader>
#include "Project.h"
#include "VES.h"
#include <QList>
#include "BasicData.h"
#include "SpliceData.h"
#include "ModelData.h"

class VESCORESHARED_EXPORT OldProject : public QObject
{
    Q_OBJECT

    void readOldSev(QXmlStreamReader *reader, Project *newProject);
    void readOldCoordinates(QXmlStreamReader *reader, VES *ves);
    QList<BasicData> readOldListaPuntoCampo(QXmlStreamReader *reader, const QString &stopName);
    InversionModel *readOldModelo(QXmlStreamReader *reader);
    QList<ModelData> readOldModeloSEVs(QXmlStreamReader *reader);

public:
    explicit OldProject(QObject *parent = nullptr);

    Project *readOldProject(const QString &filename);

signals:

public slots:
};

#endif // OLDPROJECT_H
