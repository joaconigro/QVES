#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include "ves-core_global.h"
#include "Serializable.h"
#include "VES.h"
#include <QList>

class VESCORESHARED_EXPORT Project : public QObject, public Serializable
{
    Q_OBJECT

    QString mName;
    QList<VES> mVESs;
    VES *mCurrentVES;
    int mCurrentIndex;
    QString mCurrentePath;
    bool mSaved;


public:
    explicit Project(QObject *parent = nullptr);
    Project(const Project& pr);

    //Getters
    QString name() const;
    QList<VES> vess() const;
    VES *currentVES() const;
    int currentIndex() const;
    QString currentePath() const;
    bool saved() const;

    //Setters
    void setName(const QString value);
    void setCurrentePath(const QString value);

    QVariant toVariant() const override;
    void fromVariant(const QVariant& variant) override;
signals:

public slots:
};

Q_DECLARE_METATYPE(Project)

#endif // PROJECT_H
