#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtWidgets>
#include <thread>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <map>
#include <QStringListModel>
#include <image_utils.h>
#include <iomanip>

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
    void on_actionCarregar_Imagens_triggered();

    void on_actionO_Frota_Sabe_triggered();
private:
    Ui::MainWindow *ui;
    void show_image(QString location);
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
