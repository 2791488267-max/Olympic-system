#include "DataManager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

DataManager::DataManager()
{
}

void DataManager::load(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open file for reading:" << fileName;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isArray()) {
        qDebug() << "Invalid JSON format in file:" << fileName;
        return;
    }

    m_countries.clear();
    QJsonArray countriesArray = doc.array();
    for (const QJsonValue &value : countriesArray) {
        if (!value.isObject()) continue;

        QJsonObject countryObj = value.toObject();
        Country country(
            countryObj["code"].toInt(),
            countryObj["threeLetterCode"].toString(),
            countryObj["chineseName"].toString(),
            countryObj["englishName"].toString(),
            countryObj["teamSize"].toInt()
        );

        QJsonArray medalsArray = countryObj["medals"].toArray();
        for (const QJsonValue &medalValue : medalsArray) {
            QJsonObject medalObj = medalValue.toObject();
            Medal medal(
                medalObj["athleteName"].toString(),
                medalObj["teamName"].toString(),
                medalObj["event"].toString(),
                QDate::fromString(medalObj["date"].toString(), Qt::ISODate),
                medalObj["score"].toString(),
                medalObj["level"].toString()
            );
            country.addMedal(medal);
        }

        m_countries.append(country);
    }
}

void DataManager::save(const QString &fileName)
{
    QJsonArray countriesArray;
    for (const Country &country : m_countries) {
        QJsonObject countryObj;
        countryObj["code"] = country.code();
        countryObj["threeLetterCode"] = country.threeLetterCode();
        countryObj["chineseName"] = country.chineseName();
        countryObj["englishName"] = country.englishName();
        countryObj["teamSize"] = country.teamSize();

        QJsonArray medalsArray;
        for (const Medal &medal : country.medals()) {
            QJsonObject medalObj;
            medalObj["athleteName"] = medal.athleteName();
            medalObj["teamName"] = medal.teamName();
            medalObj["event"] = medal.event();
            medalObj["date"] = medal.date().toString(Qt::ISODate);
            medalObj["score"] = medal.score();
            medalObj["level"] = medal.level();
            medalsArray.append(medalObj);
        }
        countryObj["medals"] = medalsArray;

        countriesArray.append(countryObj);
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open file for writing:" << fileName;
        return;
    }

    QJsonDocument doc(countriesArray);
    file.write(doc.toJson());
}

void DataManager::clear()
{
    m_countries.clear();
}

void DataManager::addCountry(const Country &country)
{
    m_countries.append(country);
}

void DataManager::removeCountry(int index)
{
    if (index >= 0 && index < m_countries.size()) {
        m_countries.removeAt(index);
    }
}

void DataManager::addMedal(int countryIndex, const Medal &medal)
{
    if (countryIndex >= 0 && countryIndex < m_countries.size()) {
        m_countries[countryIndex].addMedal(medal);
    }
}

void DataManager::removeMedal(int countryIndex, int medalIndex)
{
    if (countryIndex >= 0 && countryIndex < m_countries.size()) {
        m_countries[countryIndex].removeMedal(medalIndex);
    }
}

QList<Country> DataManager::countries() const
{
    return m_countries;
}