#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataManager.h"
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QStandardItemModel;
class QTableView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void addCountry();
    void removeCountry();
    void addMedal();
    void removeMedal();
    void saveData();
    void loadData();
    void searchByCountry();
    void searchByAthlete();
    void showMedalRanking();
    void updateMedalView(const QModelIndex &current, const QModelIndex &previous);

private:
    void setupUi();
    void updateTableView();

    Ui::MainWindow *ui;
    DataManager m_dataManager;
    QStandardItemModel *m_countryModel;
    QStandardItemModel *m_medalModel;
    QTableView *m_countryView;
    QTableView *m_medalView;
};
#endif // MAINWINDOW_H
