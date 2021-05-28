#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QInputDialog>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_menu_open_triggered();
    void on_menu_save_triggered();
    void on_menu_saveas_triggered();
    void on_menu_exit_triggered();
    void on_tableView_entered(const QModelIndex &index);

    void on_editButton_clicked();

private:
    Ui::MainWindow *ui;
    QString openedFile = "";
    QList<QMap<QString, QString>> data;
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *modItem;
    QList<QString> keys = {"Surname", "Name", "Lastname", "PostIndex", "Country", "Region", "City", "Street", "House", "Flat", "Phone"};

    void CSVToData(QString fileName);
    void DataToCSV(QString fileName);
    void ShowTable();
    QString getFileName();
};
#endif // MAINWINDOW_H
