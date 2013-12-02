#include "customwindow.hpp"

CustomWindow::CustomWindow(QWidget *parent) :
    QMainWindow(parent)
{
}


QString CustomWindow::fileOpenDialog(QString root_dir="", QString filter="")
{
    return QFileDialog::getOpenFileName(this,
        tr("Open PNG Image"), root_dir, filter);
}

void CustomWindow::initializePlots()
{
}
