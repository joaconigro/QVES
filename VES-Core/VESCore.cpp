#include "VESCore.h"
#include <QFileInfo>

QString VESCore::projectPath() const
{
    return mProjectPath;
}

QString VESCore::projectFileName() const
{
    return mProjectFileName;
}

VESCore::VESCore(QObject *parent) : QObject(parent)
{
    mProject = nullptr;
}

Project *VESCore::project()
{
    return mProject;
}

bool VESCore::openProject(const QString &filename)
{
    QFileInfo file(filename);
    mProjectPath = file.absolutePath();

    if (mProject) {
        delete mProject;
        mProject = new Project(this);
        emit projectClosed();
    }

    if (filename.endsWith(".sev", Qt::CaseInsensitive)){
        auto *old = new OldProject;
        mProject = old->readOldProject(filename);
        mProjectFileName = "";
        emit projectLoaded();
        return true;
    } else {
        XmlSerializer serializer;
        if (!mProject){
            mProject = new Project(this);
        }
        mProject->setParent(this);
        serializer.load(*mProject, filename);
        mProjectFileName = file.absoluteFilePath();
        emit projectLoaded();
        return true;
    }
}

bool VESCore::saveProject(const QString &filename)
{
    XmlSerializer xml;
    xml.save(*mProject, filename, "Project");
    mProjectFileName = filename;
    QFileInfo file(filename);
    mProjectPath = file.absolutePath();
    return true;
}

bool VESCore::saveProject()
{
    XmlSerializer xml;
    xml.save(*mProject, mProjectFileName, "Project");
    return true;
}

void VESCore::changeDataForCurrentVES(const int row, const int column, const int dataType, const double value)
{
   mProject->currentVES()->dataEdited(dataType, row, column, value);

}
