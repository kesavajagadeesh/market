#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QDebug"
#include"QMessageBox"
#include"QFile"
#include"QTextStream"
#include"QMenu"
#include"QModelIndexList"
#include"QModelIndex"
#include"QTableWidgetItem"

int rowcount,volume,updaterow,flag,save,tflag,fsave;
float capital,credit;
 QString name;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,100);
    
    QFile file("/home/jagadeesh/Desktop/file1.csv");
       if(!file.open(QIODevice::ReadOnly))
       {
           QMessageBox::warning(this,"file","file not created");
       }
     QTextStream in(&file);
     while(!in.atEnd())
     {
         QStringList data=in.readLine().split("\t");
         ui->tableWidget->setRowCount(rowcount+1);
         ui->tableWidget->setColumnCount(4);

         ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(data[0]));
         ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(data[1]));
         ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(data[2]));
         ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(data[3]));

           rowcount++;
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    
    fsave=0;
     name=ui->lineEdit->text();
     volume=ui->lineEdit_2->text().toInt();
    capital=ui->lineEdit_3->text().toFloat();
    credit=ui->lineEdit_4->text().toFloat();


    if(name !="" &&volume!=0 && capital!=0 && credit!=0)
    {


        if(ui->pushButton->text()=="ADD")
        {


            if(save==0)
            {
                if(rowcount==0)
                {
                    goto first;
                }
                for(int j=0;j<rowcount;j++)
                {
                    QString tname=ui->tableWidget->item(j,0)->text();
                    if(name==tname)
                    {
                        tflag=1;
                        break;
                    }
                    else if(name!=tname)
                    {
                        tflag=2;
                    }
                }

                if(tflag==1)
                {
                    QMessageBox::warning(this,"product name details","this product name already exits");
                }

                if(tflag==2)
                {
                    first:
                    ui->tableWidget->setRowCount(rowcount+1);
                    ui->tableWidget->setColumnCount(4);

                    ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(name));
                    ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(volume)));
                    ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(capital)));
                    ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(credit)));

                      rowcount++;
                }


            }
            else
            {

                for(int j=0;j<rowcount;j++)
                {
                    QString tname=ui->tableWidget->item(j,0)->text();
                    if(name==tname)
                    {
                        tflag=1;
                        break;
                    }
                    else if(name!=tname)
                    {
                        tflag=2;
                    }
                }

                if(tflag==1)
                {
                    QMessageBox::warning(this,"product name details","this product name already exits");
                }

                if(tflag==2)
                {
                    if(save==1)
                    {
                        QFile file("/home/jagadeesh/Desktop/file1.csv");
                           if(!file.open(QIODevice::ReadOnly))
                           {
                               QMessageBox::warning(this,"file","file not created");
                           }

                        QTextStream in(&file);

                        while(!in.atEnd())
                        {

                            QString fnamestring=in.readLine();
                            QStringList fname=fnamestring.split("\t");
                            if(name==fname[0])
                            {
                                flag=1;
                                break;
                            }
                            else if(name!=fname[0])
                            {
                                flag=2;
                            }
                        }
                    }
                    if(flag==1)
                    {
                        QMessageBox::warning(this,"product name details","this product name already exits");
                    }
                    if(flag==2)
                    {

                        ui->tableWidget->setRowCount(rowcount+1);
                        ui->tableWidget->setColumnCount(4);

                        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(name));
                        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(volume)));
                        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(capital)));
                        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(credit)));

                          rowcount++;
                    }
                }

            }

            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");


        }

        if(ui->pushButton->text()=="Update")
        {
              ui->tableWidget->setItem(updaterow,0,new QTableWidgetItem(name));
              ui->tableWidget->setItem(updaterow,1,new QTableWidgetItem(QString::number(volume)));
              ui->tableWidget->setItem(updaterow,2,new QTableWidgetItem(QString::number(capital)));
              ui->tableWidget->setItem(updaterow,3,new QTableWidgetItem(QString::number(credit)));


            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");

            ui->pushButton->setText("ADD");

        }

    }
    else
    {
        QMessageBox::warning(this,"warning","please insert correct product details");
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        ui->lineEdit_3->setText("");
        ui->lineEdit_4->setText("");
    }

}

void MainWindow::on_pushButton_3_clicked()
{
  QFile file("/home/jagadeesh/Desktop/file1.csv");
     if(!file.open(QIODevice::WriteOnly))
     {
         QMessageBox::warning(this,"file","file not created");
     }
     else
     {
          QTextStream out(&file);
          for(int r=0;r<rowcount;r++)
          {
            
                  out<<ui->tableWidget->item(r,0)->text()<<"\t";
                  out<< ui->tableWidget->item(r,1)->text()<<"\t";
                  out<< ui->tableWidget->item(r,2)->text()<<"\t";
                  out<< ui->tableWidget->item(r,3)->text()<<"\t";
                  out<<"\n";


          }
          file.close();
            save=1;
            fsave=1;
          QMessageBox::information(this,"save","sucessfullay saved");
     }
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    ui->pushButton->setText("Update");
    QString tname=ui->tableWidget->item(row,0)->text();
    QString tvolume=ui->tableWidget->item(row,1)->text();
    QString tcapital=ui->tableWidget->item(row,2)->text();
    QString tcredit=ui->tableWidget->item(row,3)->text();

    name=tname;
    volume=tvolume.toInt();
    capital=tcapital.toInt();
    credit=tcredit.toInt();

    ui->lineEdit->setText(tname);
    ui->lineEdit_2->setText(tvolume);
    ui->lineEdit_3->setText(tcapital);
    ui->lineEdit_4->setText(tcredit);
    updaterow=row;
}



void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{

    QMenu *menu=new QMenu();

    QAction *deleteaction=new QAction("DELETE",this);
    QAction *sortbyname=new QAction("sort by name",this);
    QAction *sortbyvolume=new QAction("Sort by Volume",this);
    QAction *sortbycapital=new QAction("Sort by Capital",this);

    connect(deleteaction,SIGNAL(triggered(bool)),SLOT(deleteaction()));
    connect(sortbyname,SIGNAL(triggered(bool)),SLOT(sortbyname()));
    connect(sortbyvolume,SIGNAL(triggered(bool)),SLOT(sortbyvolume()));
    connect(sortbycapital,SIGNAL(triggered(bool)),SLOT(sortbycapital()));

    menu->addAction(deleteaction);
    menu->addAction(sortbyname);
    menu->addAction(sortbyvolume);
    menu->addAction(sortbycapital);

    menu->exec(QCursor::pos());

}

void MainWindow::deleteaction(void)
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    rowcount--;
}


void MainWindow::sortbyvolume(void)
{
    QString tname,tvolume,tcepital,tcredit,iname,ivolume,icepital,icredit;
    int checkvolume_int,rowvolume;
    QString checkvolume_string;

    for(int r=0;r<rowcount;r++)
    {

        for(int i=0;i<rowcount;i++)
        {
            checkvolume_string=ui->tableWidget->item(r,1)->text();

            rowvolume=checkvolume_string.toInt();

            checkvolume_string=ui->tableWidget->item(i,1)->text();

            checkvolume_int=checkvolume_string.toInt();

                if(rowvolume<checkvolume_int)
                {

                    tname=ui->tableWidget->item(r,0)->text();
                    tvolume=ui->tableWidget->item(r,1)->text();
                    tcepital=ui->tableWidget->item(r,2)->text();
                    tcredit=ui->tableWidget->item(r,3)->text();


                    iname=ui->tableWidget->item(i,0)->text();
                    ivolume=ui->tableWidget->item(i,1)->text();
                    icepital=ui->tableWidget->item(i,2)->text();
                    icredit=ui->tableWidget->item(i,3)->text();

                    ui->tableWidget->setItem(r,0,new QTableWidgetItem(iname));
                    ui->tableWidget->setItem(r,1,new QTableWidgetItem(ivolume));
                    ui->tableWidget->setItem(r,2,new QTableWidgetItem(icepital));
                    ui->tableWidget->setItem(r,3,new QTableWidgetItem(icredit));


                    ui->tableWidget->setItem(i,0,new QTableWidgetItem(tname));
                    ui->tableWidget->setItem(i,1,new QTableWidgetItem(tvolume));
                    ui->tableWidget->setItem(i,2,new QTableWidgetItem(tcepital));
                    ui->tableWidget->setItem(i,3,new QTableWidgetItem(tcredit));


                }
        }
    }
            
}


void MainWindow::sortbycapital(void)
{
    QString tname,tvolume,tcepital,tcredit,iname,ivolume,icepital,icredit;
    int checkcapital_int,rowcapital;
    QString checkcapital_string;

    for(int r=0;r<rowcount;r++)
    {

        for(int i=0;i<rowcount;i++)
        {
            checkcapital_string=ui->tableWidget->item(r,2)->text();

            rowcapital=checkcapital_string.toInt();

            checkcapital_string=ui->tableWidget->item(i,2)->text();

            checkcapital_int=checkcapital_string.toInt();

                if(rowcapital<checkcapital_int)
                {

                    tname=ui->tableWidget->item(r,0)->text();
                    tvolume=ui->tableWidget->item(r,1)->text();
                    tcepital=ui->tableWidget->item(r,2)->text();
                    tcredit=ui->tableWidget->item(r,3)->text();


                    iname=ui->tableWidget->item(i,0)->text();
                    ivolume=ui->tableWidget->item(i,1)->text();
                    icepital=ui->tableWidget->item(i,2)->text();
                    icredit=ui->tableWidget->item(i,3)->text();

                    ui->tableWidget->setItem(r,0,new QTableWidgetItem(iname));
                    ui->tableWidget->setItem(r,1,new QTableWidgetItem(ivolume));
                    ui->tableWidget->setItem(r,2,new QTableWidgetItem(icepital));
                    ui->tableWidget->setItem(r,3,new QTableWidgetItem(icredit));


                    ui->tableWidget->setItem(i,0,new QTableWidgetItem(tname));
                    ui->tableWidget->setItem(i,1,new QTableWidgetItem(tvolume));
                    ui->tableWidget->setItem(i,2,new QTableWidgetItem(tcepital));
                    ui->tableWidget->setItem(i,3,new QTableWidgetItem(tcredit));


                }
        }
    }

}


void MainWindow::sortbyname(void)
{
    QString tname,tvolume,tcepital,tcredit,iname,ivolume,icepital,icredit;

    QString checkname_string,rowname_string;

    for(int r=0;r<rowcount;r++)
    {

        for(int i=0;i<rowcount;i++)
        {
            rowname_string=ui->tableWidget->item(r,0)->text();

            checkname_string=ui->tableWidget->item(i,0)->text();

                if(rowname_string<checkname_string)
                {

                    tname=ui->tableWidget->item(r,0)->text();
                    tvolume=ui->tableWidget->item(r,1)->text();
                    tcepital=ui->tableWidget->item(r,2)->text();
                   tcredit=ui->tableWidget->item(r,3)->text();

                    iname=ui->tableWidget->item(i,0)->text();
                    ivolume=ui->tableWidget->item(i,1)->text();
                    icepital=ui->tableWidget->item(i,2)->text();
                    icredit=ui->tableWidget->item(i,3)->text();

                    ui->tableWidget->setItem(r,0,new QTableWidgetItem(iname));
                    ui->tableWidget->setItem(r,1,new QTableWidgetItem(ivolume));
                    ui->tableWidget->setItem(r,2,new QTableWidgetItem(icepital));
                    ui->tableWidget->setItem(r,3,new QTableWidgetItem(icredit));


                    ui->tableWidget->setItem(i,0,new QTableWidgetItem(tname));
                    ui->tableWidget->setItem(i,1,new QTableWidgetItem(tvolume));
                    ui->tableWidget->setItem(i,2,new QTableWidgetItem(tcepital));
                    ui->tableWidget->setItem(i,3,new QTableWidgetItem(tcredit));


                }
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    if(fsave==0)
    {
        QMessageBox::critical(this,"save","please save product details");
    }
    else if(fsave==1)
    {
        this->close();
    }
}

void MainWindow::on_pushButton_send_clicked()
{
    if(fsave==1)
            {
            socket = new QTcpSocket(this);
            socket->connectToHost("127.0.0.1", 1234);
           ui->label_status->setText("Connecting.....");
            if(socket->waitForConnected(3000))
            {
                ui->label_status->setText("Connected");

                // send
                QFile file("/home/jagadeesh/Desktop/file1.csv");
                if(!file.open(QIODevice::ReadOnly))
                {
                    qDebug()<<"file was not open";
                }

                QTextStream in(&file);

                while(!in.atEnd())
                {
                    ui->label_status->setText("Sending......");
                    QStringList text=in.readLine().split("\t");
                   // int sl=qstrlen(text[0]);
                   char *buff;
                    int l;
                  QByteArray ba;
                  ba=text[0].toLatin1();        //converting QSTring to char
                  buff=ba.data();

                    l=strlen(buff);
                    buff[l]=0;
                    socket->write(buff);
                     socket->write("\n");

                     ba=text[1].toLatin1();      //converting QSTring to char
                     buff=ba.data();
                     l=strlen(buff);
                    buff[l]=0;
                     socket->write(buff);
                     socket->write("\n");

                     ba=text[2].toLatin1();      //converting QSTring to char
                     buff=ba.data();
                     l=strlen(buff);
                    buff[l]=0;
                     socket->write(buff);
                     socket->write("\n");

                     ba=text[3].toLatin1();      //converting QSTring to char
                     buff=ba.data();
                     l=strlen(buff);
                    buff[l]=0;
                     socket->write(buff);
                     socket->write("\n");

                }

                socket->waitForBytesWritten(3000);

                socket->flush();
                socket->close();
                file.close();
                ui->label_status->setText("Disconnected");
            }
            else
            {
                qDebug() << "Not connected!";
            }
    }
    else if(fsave==0)
    {
         QMessageBox::critical(this,"save","please save product details fisrt and than send");
    }
}


