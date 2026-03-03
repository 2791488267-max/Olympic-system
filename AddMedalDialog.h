#include "AddMedalDialog.h"
#include "ui_AddMedalDialog.h"

AddMedalDialog::AddMedalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMedalDialog)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

AddMedalDialog::~AddMedalDialog()
{
    delete ui;
}

QString AddMedalDialog::getCountry() const
{
    return ui->countryComboBox->currentText();
}

QString AddMedalDialog::getAthlete() const
{
    return ui->athleteLineEdit->text();
}

QString AddMedalDialog::getEvent() const
{
    return ui->eventLineEdit->text();
}

QString AddMedalDialog::getMedalType() const
{
    return ui->medalTypeComboBox->currentText();
}

QDate AddMedalDialog::getDate() const
{
    return ui->dateEdit->date();
}

void AddMedalDialog::setCountryList(const QStringList &countries)
{
    ui->countryComboBox->clear();
    ui->countryComboBox->addItems(countries);
}