#include "VESCore.h"


VESCore::VESCore(QObject *parent) : QObject(parent)
{
}

Project *VESCore::project()
{
    return mProject;
}

bool VESCore::openProject(const QString &filename)
{
    if (filename.endsWith(".sev", Qt::CaseInsensitive)){
        OldProject *old = new OldProject;
        mProject = old->readOldProject(filename);
        emit projectLoaded();
        return true;
    } else {
        XmlSerializer serializer;
        mProject->setParent(this);
        serializer.load(*mProject, filename);
        emit projectLoaded();
        return true;
    }
}
