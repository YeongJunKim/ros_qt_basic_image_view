/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/imageView_example/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace imageView_example {
extern bool isRecv;

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));
    qnode.init();

    if(qnode.img_qnode != NULL) qnode.img_qnode = NULL;

    QObject::connect(&qnode, SIGNAL(recvImg()), this, SLOT(updateImg()));
}

MainWindow::~MainWindow() {}

void MainWindow::updateImg()
{
    Mat imgOrg(*qnode.img_qnode); //qnode-> receive
    if(!qnode.img_qnode->empty() && !imgOrg.empty() && isRecv)
    {

        QImage qimageOrg((const unsigned char*)(imgOrg.data), imgOrg.cols, imgOrg.rows, QImage::Format_RGB888);
        ui.labelOrg->setPixmap(QPixmap::fromImage(qimageOrg.rgbSwapped()));

    }

    delete qnode.img_qnode;
    if(qnode.img_qnode != NULL) qnode.img_qnode = NULL;
    isRecv = false;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
	QMainWindow::closeEvent(event);
}

}  // namespace imageView_example


