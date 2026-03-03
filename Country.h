#include "Country.h"

Country::Country()
    : m_code(0), m_teamSize(0)
{
}

Country::Country(int code, const QString &threeLetterCode, const QString &chineseName, const QString &englishName, int teamSize)
    : m_code(code), m_threeLetterCode(threeLetterCode), m_chineseName(chineseName), m_englishName(englishName), m_teamSize(teamSize)
{
}

int Country::code() const
{
    return m_code;
}

void Country::setCode(int code)
{
    m_code = code;
}

QString Country::threeLetterCode() const
{
    return m_threeLetterCode;
}

void Country::setThreeLetterCode(const QString &threeLetterCode)
{
    m_threeLetterCode = threeLetterCode;
}

QString Country::chineseName() const
{
    return m_chineseName;
}

void Country::setChineseName(const QString &chineseName)
{
    m_chineseName = chineseName;
}

QString Country::englishName() const
{
    return m_englishName;
}

void Country::setEnglishName(const QString &englishName)
{
    m_englishName = englishName;
}

int Country::teamSize() const
{
    return m_teamSize;
}

void Country::setTeamSize(int teamSize)
{
    m_teamSize = teamSize;
}

QList<Medal> Country::medals() const
{
    return m_medals;
}

void Country::addMedal(const Medal &medal)
{
    m_medals.append(medal);
}

void Country::removeMedal(int index)
{
    if (index >= 0 && index < m_medals.size()) {
        m_medals.removeAt(index);
    }
}