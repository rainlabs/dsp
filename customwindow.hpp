#ifndef CUSTOMWINDOW_HPP
#define CUSTOMWINDOW_HPP

#include <QMainWindow>
#include <iostream>

#include <qwt_plot_canvas.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_zoomer.h>
#include <qwt_raster_data.h>
#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>
#include <QFileDialog>

class CustomWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CustomWindow(QWidget *parent = 0);

protected:
    QMap<QString, QwtPlotGrid *>  m_gridPlot;    // hash of name -> grid plot
    QMap<QString, QwtPlotCurve *> m_curvPlot;    // hash of name -> curv plot

    QString fileOpenDialog(QString root_dir, QString filter);
    void initializePlots();
};

#endif // CUSTOMWINDOW_HPP
