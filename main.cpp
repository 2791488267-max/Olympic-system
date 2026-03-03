#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "Country.h"
#include <QList>
#include <QString>

class DataManager
{
public:
    DataManager();

    void load(const QString &fileName);
    void save(const QString &fileName);
    void clear();

    void addCountry(const Country &country);
    void removeCountry(int index);
    void addMedal(int countryIndex, const Medal &medal);
    void removeMedal(int countryIndex, int medalIndex);
    QList<Country> countries() const;

private:
    QList<Country> m_countries;
};

#endif // DATAMANAGER_H
