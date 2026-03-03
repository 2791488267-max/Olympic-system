#ifndef ADDMEDALDIALOG_H
#define ADDMEDALDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class AddMedalDialog;
}

class AddMedalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMedalDialog(QWidget *parent = nullptr);
    ~AddMedalDialog();

    QString getCountry() const;
    QString getAthlete() const;
    QString getEvent() const;
    QString getMedalType() const;
    QDate getDate() const;

    void setCountryList(const QStringList &countries);

private:
    Ui::AddMedalDialog *ui;
};

#endif // ADDMEDALDIALOG_H