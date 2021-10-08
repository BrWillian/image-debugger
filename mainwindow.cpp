#include "mainwindow.h"
#include "./ui_mainwindow.h"

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


void MainWindow::on_actionCarregar_Imagens_triggered()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!(path.toStdString() == ""))
    {
        std::thread t1(&file_utils::list_dir, path);
        t1.join();

        QStringList list;

        for(auto it=file_utils::list_of_images.begin(); it != file_utils::list_of_images.end(); it++)
        {
            list << *it;
        }

        ui->listView->setModel(new QStringListModel(list));

        if(!(file_utils::list_of_images.empty()))
        {
            image_utils::npos = 0;
            show_image(file_utils::list_of_images.at(image_utils::npos));
            QModelIndex ind = ui->listView->model()->index(image_utils::npos, 0);
            ui->listView->setCurrentIndex(ind);
            ui->listView->selectionModel()->select(ind, QItemSelectionModel::Select);
        }
    }

}

void MainWindow::on_actionO_Frota_Sabe_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Não pertube o Willian!");
    msgBox.setText("Chama o frota, ele sabe de tudo!\nOu o Diogo Satanista.");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}
void MainWindow::show_image(QString location)
{
    QPixmap img(location);
    ui->label_4->setPixmap(img.scaled(ui->label_4->width(),ui->label_4->height(),Qt::KeepAspectRatio));
    ui->label_4->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!file_utils::list_of_images.empty())
    {
        if(event->key() == Qt::Key_Right)
        {
            image_utils::npos = image_utils::npos+1;
            try{
                show_image(file_utils::list_of_images.at(image_utils::npos));
            }catch(const std::out_of_range& oor){
                image_utils::npos = file_utils::list_of_images.size()-1;
                QMessageBox::information(this, "Image Debugger", "You finished all images!");
            }
        }

        if(event->key() == Qt::Key_Left)
        {
            if(image_utils::npos >= 0)
                image_utils::npos = image_utils::npos-1;
            try{
                show_image(file_utils::list_of_images.at(image_utils::npos));
            }catch(const std::out_of_range& oor){
                image_utils::npos = 0;
            }
        }

        if(event->key() == Qt::Key_E)
        {
            std::cout<<"apertou o e"<<std::endl;
        }

        QModelIndex ind = ui->listView->model()->index(image_utils::npos, 0);
        ui->listView->setCurrentIndex(ind);
        ui->listView->selectionModel()->select(ind, QItemSelectionModel::Select);
    }
}
