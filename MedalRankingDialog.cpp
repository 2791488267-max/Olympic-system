#ifndef MEDAL_H
#define MEDAL_H

#include <QString>
#include <QDate>

class Medal
{
public:
    Medal();
    Medal(const QString &athleteName, const QString &teamName, const QString &event, const QDate &date, const QString &score, const QString &level);

    QString athleteName() const;
    void setAthleteName(const QString &athleteName);

    QString teamName() const;
    void setTeamName(const QString &teamName);

    QString event() const;
    void setEvent(const QString &event);

    QDate date() const;
    void setDate(const QDate &date);

    QString score() const;
    void setScore(const QString &score);

    QString level() const;
    void setLevel(const QString &level);

private:
    QString m_athleteName;
    QString m_teamName;
    QString m_event;
    QDate m_date;
    QString m_score;
    QString m_level;
};

#endif // MEDAL_H
