#include "AddCountryDialog.h"
#include "ui_AddCountryDialog.h"

AddCountryDialog::AddCountryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCountryDialog)
{
    ui->setupUi(this);
}

AddCountryDialog::~AddCountryDialog()
{
    delete ui;
}

Country AddCountryDialog::country() const
{
    return Country(ui->codeEdit->text().toInt(),
                   ui->threeLetterCodeEdit->text(),
                   ui->chineseNameEdit->text(),
                   ui->englishNameEdit->text(),
                   ui->teamSizeEdit->text().toInt());
}
