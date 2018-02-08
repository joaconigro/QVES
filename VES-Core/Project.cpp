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

Project::~Project()
{
    if (mCurrentVES)
        mCurrentVES = nullptr;
    mVESs.clear();
}

QString Project::name() const
{
    return mName;
}

QList<VES *> Project::vess() const
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

void Project::setCurrentIndex(const int value)
{
    if (value >= 0 && value < mVESs.count()){
        if (mCurrentIndex != value) {
            mCurrentIndex = value;
            mCurrentVES = mVESs[mCurrentIndex];
            emit currentVESChanged();
        }
    }
}

QVariant Project::toVariant() const
{
    QVariantMap map;
    map.insert("mName", mName);
    map.insert("mCurrentIndex", mCurrentIndex);
    map.insert("mCurrentePath", mCurrentePath);

    QVariantList list;
    for (const auto& v : mVESs) {
    list.append(v->toVariant());
    }
    map.insert("mVESs", list);

    return map;
}

void Project::fromVariant(const QVariant &variant)
{
    QVariantMap map = variant.toMap();
    mName = map.value("mName").toString();
    mCurrentePath = map.value("mCurrentePath").toString();

    QVariantList list = map.value("mVESs").toList();
    for(const QVariant& data : list) {
        VES* v = new VES(this);
        v->fromVariant(data);
//        for (int i=0; i<v.models().count();i++)
//            v.models()[i]->setParent(&v);
        this->addVES(v);
        //mVESs.append(v);
    }

    setCurrentIndex(map.value("mCurrentIndex").toInt());
}

void Project::addVES(VES* ves)
{
    ves->setParent(this);
    mVESs.append(ves);
}
