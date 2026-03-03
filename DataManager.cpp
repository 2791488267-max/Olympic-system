#ifndef COUNTRY_H
#define COUNTRY_H

#include <QString>
#include <QList>
#include "Medal.h"

class Country
{
public:
    Country();
    Country(int code, const QString &threeLetterCode, const QString &chineseName, const QString &englishName, int teamSize);

    int code() const;
    void setCode(int code);

    QString threeLetterCode() const;
    void setThreeLetterCode(const QString &threeLetterCode);

    QString chineseName() const;
    void setChineseName(const QString &chineseName);

    QString englishName() const;
    void setEnglishName(const QString &englishName);

    int teamSize() const;
    void setTeamSize(int teamSize);

    QList<Medal> medals() const;
    void addMedal(const Medal &medal);
    void removeMedal(int index);

private:
    int m_code;
    QString m_threeLetterCode;
    QString m_chineseName;
    QString m_englishName;
    int m_teamSize;
    QList<Medal> m_medals;
};

#endif // COUNTRY_H
