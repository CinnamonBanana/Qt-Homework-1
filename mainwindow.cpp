#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CSVToData(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть файл. " + file.errorString());
        return;
    }
    else
    {
        data.clear();
        QTextStream in(&file);
        while (!in.atEnd())
        {
                QString line = in.readLine();
                int i = 0;
                data.append(QMap<QString, QString>{});
                for (QString item : line.split(";"))
                {
                    data.last().insert(keys.at(i), item);
                    i++;
                }
            }
            file.close();
    }
}

void MainWindow::DataToCSV(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть файл. " + file.errorString());
        return;
    }
    else
    {
            QTextStream out(&file);
            for (QMap<QString, QString> item: data)
            {
                for (QString key : keys)
                {
                    out << item[key];
                    if(key != keys.last())
                        out << ";";
                }
                if(item != data.last())
                    out << Qt::endl;
            }
            file.close();
    }
}

void MainWindow::ShowTable()
{
    model->setHorizontalHeaderLabels(keys);
    model->setRowCount(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data.at(i).size(); j++)
        {
            modItem = new QStandardItem(QString(data.at(i)[keys[j]]));
            model->setItem(i, j, modItem);
        }
    }
    ui->tableView->setModel(model);
    ui->tableView->show();
}

QString MainWindow::getFileName()
{
    return openedFile.mid(openedFile.lastIndexOf("/")+1);
}

void MainWindow::on_addButton_clicked()
{
    data.append(QMap<QString, QString>{});
    ShowTable();
}

void MainWindow::on_editButton_clicked()
{
    if(ui->tableView->currentIndex().isValid())
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Введите новые данные."),
                                                 tr("Ввод:"), QLineEdit::Normal,
                                                 "", &ok);
        if (ok && !text.isEmpty())
        {
            qDebug() << text;
            data[ui->tableView->currentIndex().row()][keys.at(ui->tableView->currentIndex().column())] = text;
        }
        ShowTable();
    }
    else {
        QMessageBox::warning(this, "Ошибка!", "Выберите элемент.");
    }
}

void MainWindow::on_deleteButton_clicked()
{
    if(ui->tableView->currentIndex().isValid())
    {
        qDebug() << ui->tableView->currentIndex().row();
        data.removeAt(ui->tableView->currentIndex().row());
        ShowTable();
    }
    else {
        QMessageBox::warning(this, "Ошибка!", "Выберите элемент.");
    }
}

void MainWindow::on_menu_open_triggered()
{
    openedFile = QFileDialog::getOpenFileName(this, "Открыть файл...", "", "*.csv");
    setWindowTitle(getFileName());
    CSVToData(openedFile);
    ShowTable();
}

void MainWindow::on_menu_save_triggered()
{
    if (openedFile.isEmpty())
    {
        openedFile = QFileDialog::getSaveFileName(this, "Сохранить как...", "", "*.csv");
    }
    setWindowTitle(getFileName());
    DataToCSV(openedFile);
}

void MainWindow::on_menu_saveas_triggered()
{
    openedFile = QFileDialog::getSaveFileName(this, "Сохранить как...", "", "*.csv");
    setWindowTitle(getFileName());
    DataToCSV(openedFile);
}

void MainWindow::on_menu_exit_triggered()
{
    this->close();
}




