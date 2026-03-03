#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AddCountryDialog.h"
#include "AddMedalDialog.h"
#include "SearchDialog.h"
#include "MedalRankingDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUi();
    loadData();
    updateTableView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUi()
{
    m_countryModel = new QStandardItemModel(this);
    m_countryView = ui->countryTableView;
    m_countryView->setModel(m_countryModel);

    m_medalModel = new QStandardItemModel(this);
    m_medalView = ui->medalTableView;
    m_medalView->setModel(m_medalModel);

    // 连接文件菜单动作
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::loadData);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveData);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);

    // 连接编辑菜单动作
    connect(ui->actionAddCountry, &QAction::triggered, this, &MainWindow::addCountry);
    connect(ui->actionRemoveCountry, &QAction::triggered, this, &MainWindow::removeCountry);
    connect(ui->actionAddMedal, &QAction::triggered, this, &MainWindow::addMedal);
    connect(ui->actionRemoveMedal, &QAction::triggered, this, &MainWindow::removeMedal);

    // 连接搜索菜单动作
    connect(ui->actionSearchByCountry, &QAction::triggered, this, &MainWindow::searchByCountry);
    connect(ui->actionSearchByAthlete, &QAction::triggered, this, &MainWindow::searchByAthlete);

    // 连接统计菜单动作
    connect(ui->actionMedalRanking, &QAction::triggered, this, &MainWindow::showMedalRanking);

    // 连接表格选择变化信号
    connect(m_countryView->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &MainWindow::updateMedalView);
}

void MainWindow::addCountry()
{
    AddCountryDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_dataManager.addCountry(dialog.country());
        updateTableView();
    }
}

void MainWindow::saveData()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("保存国家数据"),
        QDir::currentPath(),
        tr("JSON文件 (*.json)"));
    if (!fileName.isEmpty()) {
        m_dataManager.save(fileName);
        updateTableView();
    }
}

void MainWindow::loadData()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("打开国家数据"),
        QDir::currentPath(),
        tr("JSON文件 (*.json)"));
    if (!fileName.isEmpty()) {
        m_dataManager.load(fileName);
        updateTableView();
    }
}

void MainWindow::updateTableView()
{
    m_countryModel->clear();
    m_countryModel->setHorizontalHeaderLabels({"编号", "三字码", "中文名", "英文名", "团队规模", "奖牌数"});

    for (const auto &country : m_dataManager.countries()) {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(QString::number(country.code())));
        rowItems.append(new QStandardItem(country.threeLetterCode()));
        rowItems.append(new QStandardItem(country.chineseName()));
        rowItems.append(new QStandardItem(country.englishName()));
        rowItems.append(new QStandardItem(QString::number(country.teamSize())));
        rowItems.append(new QStandardItem(QString::number(country.medals().size())));
        m_countryModel->appendRow(rowItems);
    }
}

void MainWindow::newFile()
{
    m_dataManager.clear();
    updateTableView();
}

void MainWindow::removeCountry()
{
    QModelIndex currentIndex = m_countryView->currentIndex();
    if (currentIndex.isValid()) {
        int row = currentIndex.row();
        m_dataManager.removeCountry(row);
        updateTableView();
    }
}

void MainWindow::addMedal()
{
    QModelIndex currentIndex = m_countryView->currentIndex();
    if (currentIndex.isValid()) {
        AddMedalDialog dialog(this);
        QStringList countryNames;
        for (const auto &country : m_dataManager.countries()) {
            countryNames.append(country.chineseName());
        }
        dialog.setCountryList(countryNames);
        if (dialog.exec() == QDialog::Accepted) {
            int row = currentIndex.row();
            Medal medal(
                dialog.getAthlete(),
                m_dataManager.countries().at(row).chineseName(),  // 使用当前选中的国家名称
                dialog.getEvent(),
                dialog.getDate(),
                "",  // score
                dialog.getMedalType()
            );
            m_dataManager.addMedal(row, medal);
            updateTableView();
            updateMedalView(currentIndex, QModelIndex());
        }
    }
}

void MainWindow::removeMedal()
{
    QModelIndex countryIndex = m_countryView->currentIndex();
    QModelIndex medalIndex = m_medalView->currentIndex();
    if (countryIndex.isValid() && medalIndex.isValid()) {
        int countryRow = countryIndex.row();
        int medalRow = medalIndex.row();
        m_dataManager.removeMedal(countryRow, medalRow);
        updateTableView();
        updateMedalView(countryIndex, QModelIndex());
    }
}

void MainWindow::searchByCountry()
{
    SearchDialog dialog(this);
    QStringList countryNames;
    for (const auto &country : m_dataManager.countries()) {
        countryNames.append(country.chineseName());
    }
    dialog.setCountryList(countryNames);
    connect(&dialog, &SearchDialog::searchByCountry, this, [this](const QString &countryName) {
        // TODO: 实现按国家搜索的逻辑
        qDebug() << "Searching for country:" << countryName;
    });
    dialog.exec();
}

void MainWindow::searchByAthlete()
{
    SearchDialog dialog(this);
    connect(&dialog, &SearchDialog::searchByAthlete, this, [this](const QString &athleteName) {
        // TODO: 实现按运动员搜索的逻辑
        qDebug() << "Searching for athlete:" << athleteName;
    });
    dialog.exec();
}

void MainWindow::showMedalRanking()
{
    MedalRankingDialog dialog(this);
    
    // 创建排名模型
    QStandardItemModel *rankingModel = new QStandardItemModel(this);
    rankingModel->setHorizontalHeaderLabels({"国家", "金牌", "银牌", "铜牌", "总计"});
    
    // 统计各国奖牌数
    int totalGold = 0, totalSilver = 0, totalBronze = 0;
    for (const auto &country : m_dataManager.countries()) {
        int gold = 0, silver = 0, bronze = 0;
        for (const auto &medal : country.medals()) {
            if (medal.level() == "金牌") gold++;
            else if (medal.level() == "银牌") silver++;
            else if (medal.level() == "铜牌") bronze++;
        }
        
        if (gold > 0 || silver > 0 || bronze > 0) {
            QList<QStandardItem *> rowItems;
            rowItems.append(new QStandardItem(country.chineseName()));
            rowItems.append(new QStandardItem(QString::number(gold)));
            rowItems.append(new QStandardItem(QString::number(silver)));
            rowItems.append(new QStandardItem(QString::number(bronze)));
            rowItems.append(new QStandardItem(QString::number(gold + silver + bronze)));
            rankingModel->appendRow(rowItems);
            
            totalGold += gold;
            totalSilver += silver;
            totalBronze += bronze;
        }
    }
    
    // 按金牌数排序
    rankingModel->sort(1, Qt::DescendingOrder);
    
    // 更新对话框
    dialog.updateRanking(rankingModel);
    dialog.updateMedalCounts(totalGold, totalSilver, totalBronze);
    
    dialog.exec();
}

void MainWindow::updateMedalView(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    m_medalModel->clear();
    m_medalModel->setHorizontalHeaderLabels({"运动员", "团队", "项目", "日期", "成绩", "级别"});

    if (current.isValid()) {
        int row = current.row();
        QList<Country> countries = m_dataManager.countries();
        if (row >= 0 && row < countries.size()) {
            const Country &country = countries.at(row);
            for (const auto &medal : country.medals()) {
                QList<QStandardItem *> rowItems;
                rowItems.append(new QStandardItem(medal.athleteName()));
                rowItems.append(new QStandardItem(medal.teamName()));
                rowItems.append(new QStandardItem(medal.event()));
                rowItems.append(new QStandardItem(medal.date().toString(Qt::ISODate)));
                rowItems.append(new QStandardItem(medal.score()));
                rowItems.append(new QStandardItem(medal.level()));
                m_medalModel->appendRow(rowItems);
            }
        }
    }
}
