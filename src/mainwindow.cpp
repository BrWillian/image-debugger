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

    image_utils::images.clear();

    if(!(path.toStdString() == ""))
    {
        std::thread t1(&image_utils::list_dir, path);
        t1.join();

        QStringList list;

        for (auto &p : image_utils::images){
            list << QString::fromStdString(p.first);
        }

        ui->listView->setModel(new QStringListModel(list));

        if(!(image_utils::images.empty()))
        {
            image_utils::npos = 0;
            show_image(QString::fromStdString(image_utils::get_map_from_index(0)->first));
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
    if(!image_utils::images.empty())
    {
        if(event->key() == Qt::Key_Right)
        {
            image_utils::npos = image_utils::npos+1;
            if(image_utils::npos >= image_utils::images.size())
            {
                image_utils::npos = image_utils::images.size()-1;
                ui->label->setText(QString::number(image_utils::npos - image_utils::get_error()+1));

                std::thread t2(&image_utils::write_result);
                t2.join();

                QMessageBox::information(this, "Image Debugger", "Imagens finalizadas!\nAproveitamento: "+QString::number(image_utils::get_result(), 'f', 2)+"%");
            }
            ui->label->setText(QString::number(image_utils::npos - image_utils::get_error()));
            show_image(QString::fromStdString(image_utils::get_map_from_index(image_utils::npos)->first));


        }
        if(event->key() == Qt::Key_E){
            image_utils::get_map_from_index(image_utils::npos)->second = false;
        }

        if(event->key() == Qt::Key_Left)
        {
            if(image_utils::npos > 0)
                image_utils::npos = image_utils::npos-1;

            show_image(QString::fromStdString(image_utils::get_map_from_index(image_utils::npos)->first));
            image_utils::get_map_from_index(image_utils::npos)->second = true;
            ui->label->setText(QString::number(image_utils::npos - image_utils::get_error()));
        }

        ui->label_3->setText(QString::number(image_utils::get_error()));

        QModelIndex ind = ui->listView->model()->index(image_utils::npos, 0);
        ui->listView->setCurrentIndex(ind);
        ui->listView->selectionModel()->select(ind, QItemSelectionModel::Select);
    }
}
