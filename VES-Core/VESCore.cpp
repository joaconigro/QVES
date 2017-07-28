#include "VESCore.h"


VESCore::VESCore(QObject *parent) : QObject(parent)
{
}

Project *VESCore::project()
{
    return &mProject;
}

bool VESCore::openProject(const QString &filename)
{
    XmlSerializer serializer;
    mProject.setParent(this);
    serializer.load(mProject, filename);
    emit projectLoaded();
    return true;
}
