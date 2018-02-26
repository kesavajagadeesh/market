#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include "QTcpServer"
#include "QTcpSocket"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);



    void sortbyvolume(void);

     void sortbyname(void);

     void sortbycapital(void);

    void deleteaction(void);
    void on_pushButton_2_clicked();

    void on_pushButton_send_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
