#pragma once
#include "power_export.h"

#include <QObject>
#include <QList>
#include <QVariantMap>

class POWER_EXPORT PowerProfile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentProfile READ currentProfile NOTIFY currentProfileChanged)
    Q_PROPERTY(QStringList profileChoices READ profileChoices NOTIFY profileChoicesChanged FINAL)
    Q_PROPERTY(QString performanceInhibitedReason READ performanceInhibitedReason NOTIFY performanceInhibitedReasonChanged FINAL)
    Q_PROPERTY(QString performanceDegradedReason READ performanceDegradedReason NOTIFY performanceDegradedReasonChanged FINAL)
    Q_PROPERTY(QList<QVariantMap> profileHolds READ profileHolds NOTIFY profileHoldsChanged FINAL)

public:
    explicit PowerProfile(QObject *parent = nullptr);

    QString currentProfile() const;

    QStringList profileChoices() const;

    QString performanceInhibitedReason() const;

    QString performanceDegradedReason() const;

    QList<QVariantMap> profileHolds() const;

private Q_SLOTS:
    
    void setCurrentProfile(QString currentProfile);

    void setProfileChoices(QStringList profileChoices);

    void setPerformanceInhibitedReason(QString performanceInhibitedReason);

    void setPerformanceDegradedReason(QString performanceDegradedReason);

    void setProfileHolds(QList<QVariantMap> profileHolds);

public Q_SLOTS:
    void changeProfile(const QString &value);

private:
    QString m_currentProfile;

    QStringList m_profileChoices;

    QString m_performanceInhibitedReason;

    QString m_performanceDegradedReason;

    QList<QVariantMap> m_profileHolds;

    QHash<QString, QPair<QString, QString>> m_applicationInfo; // <appname, <pretty name, icon>>

    void populateApplicationData(const QString &name, QString *prettyName, QString *icon);

Q_SIGNALS:
    void currentProfileChanged(QString currentProfile);
    void profileChoicesChanged(QStringList profileChoices);
    void performanceInhibitedReasonChanged(QString performanceInhibitionReason);
    void performanceDegradedReasonChanged(QString performanceDegradedReason);
    void profileHoldsChanged(QList<QVariantMap> profileHolds);
};
