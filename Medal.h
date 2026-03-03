#include "Medal.h"

Medal::Medal()
{
}

Medal::Medal(const QString &athleteName, const QString &teamName, const QString &event, const QDate &date, const QString &score, const QString &level)
    : m_athleteName(athleteName), m_teamName(teamName), m_event(event), m_date(date), m_score(score), m_level(level)
{
}

QString Medal::athleteName() const
{
    return m_athleteName;
}

void Medal::setAthleteName(const QString &athleteName)
{
    m_athleteName = athleteName;
}

QString Medal::teamName() const
{
    return m_teamName;
}

void Medal::setTeamName(const QString &teamName)
{
    m_teamName = teamName;
}

QString Medal::event() const
{
    return m_event;
}

void Medal::setEvent(const QString &event)
{
    m_event = event;
}

QDate Medal::date() const
{
    return m_date;
}

void Medal::setDate(const QDate &date)
{
    m_date = date;
}

QString Medal::score() const
{
    return m_score;
}

void Medal::setScore(const QString &score)
{
    m_score = score;
}

QString Medal::level() const
{
    return m_level;
}

void Medal::setLevel(const QString &level)
{
    m_level = level;
}