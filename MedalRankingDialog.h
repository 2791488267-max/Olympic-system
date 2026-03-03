#include "MedalRankingDialog.h"
#include "ui_MedalRankingDialog.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MedalRankingDialog::MedalRankingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedalRankingDialog),
    rankingModel(nullptr)
{
    ui->setupUi(this);
}

MedalRankingDialog::~MedalRankingDialog()
{
    delete ui;
}

void MedalRankingDialog::updateRanking(QStandardItemModel *model)
{
    rankingModel = model;
    ui->rankingTableView->setModel(rankingModel);
    ui->rankingTableView->resizeColumnsToContents();
}

void MedalRankingDialog::updateMedalCounts(int gold, int silver, int bronze)
{
    ui->goldLabel->setText(QString("金牌：%1").arg(gold));
    ui->silverLabel->setText(QString("银牌：%1").arg(silver));
    ui->bronzeLabel->setText(QString("铜牌：%1").arg(bronze));
}

void MedalRankingDialog::on_exportButton_clicked()
{
    if (!rankingModel) {
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("导出奖牌排名"),
        QString(),
        tr("CSV文件 (*.csv)"));

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"), tr("无法创建文件！"));
        return;
    }

    QTextStream out(&file);

    // 写入表头
    QStringList headers;
    for (int i = 0; i < rankingModel->columnCount(); ++i) {
        headers << rankingModel->headerData(i, Qt::Horizontal).toString();
    }
    out << headers.join(",") << "\n";

    // 写入数据
    for (int row = 0; row < rankingModel->rowCount(); ++row) {
        QStringList fields;
        for (int col = 0; col < rankingModel->columnCount(); ++col) {
            QString data = rankingModel->data(rankingModel->index(row, col)).toString();
            // 如果数据中包含逗号，用引号括起来
            if (data.contains(",")) {
                data = '"' + data + '"';
            }
            fields << data;
        }
        out << fields.join(",") << "\n";
    }

    file.close();
    QMessageBox::information(this, tr("成功"), tr("数据已成功导出！"));
}