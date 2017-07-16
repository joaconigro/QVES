#include "Project.h"

Project::Project(QObject *parent) : QObject(parent)
{

}

Project::Project(const Project &pr)
{
    mName = pr.name();
    mVESs = pr.vess();
    mCurrentVES = pr.currentVES();
    mCurrentIndex = pr.currentIndex();
    mCurrentePath = pr.currentePath();
    mSaved = pr.saved();
    this->setParent(pr.parent());
}

QString Project::name() const
{
    return mName;
}

QList<VES> Project::vess() const
{
    return mVESs;
}

VES *Project::currentVES() const
{
    return mCurrentVES;
}

int Project::currentIndex() const
{
    return mCurrentIndex;
}

QString Project::currentePath() const
{
    return mCurrentePath;
}

bool Project::saved() const
{
    return mSaved;
}

void Project::setName(const QString value)
{
    mName = value;
}

void Project::setCurrentePath(const QString value)
{
    mCurrentePath = value;
}

QVariant Project::toVariant() const
{
    QVariantMap map;
    map.insert("mName", mName);

    return map;
}

void Project::fromVariant(const QVariant &variant)
{

}
