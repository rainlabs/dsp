#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QFileDialog>

#include <qwt_plot_canvas.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_zoomer.h>
#include <qwt_raster_data.h>
#include <qwt_matrix_raster_data.h>
#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>

#include "signal.hpp"

class FftSpectrumData: public QwtRasterData
{
public:
    FftSpectrumData()
    {
        setInterval(Qt::ZAxis, QwtInterval(-1., 0.));
    }

    virtual double value( double x, double y ) const
    {
        return findMin(x, y);
    }

    float findMin(double x, double y) const {
        return std::min_element(m_spectrumData.begin(), m_spectrumData.end(), [&](const QVector3D _a, const QVector3D _b) {
            double dist_a = pow( (_a.x() - x), 2.) + pow( (_a.y() - y), 2.);
            double dist_b = pow( (_b.x() - x), 2.) + pow( (_b.y() - y), 2.);

            return dist_a < dist_b;
        })->z() / -90.;
    }

    void setData(QVector< QVector3D > data) {
        m_spectrumData = data;
    }

protected:
    QVector< QVector3D > m_spectrumData;
};

class ColorMap: public QwtLinearColorMap
{
public:
    ColorMap():
        QwtLinearColorMap( Qt::darkCyan, Qt::red )
        {
            addColorStop( 0.1, Qt::cyan );
            addColorStop( 0.6, Qt::green );
            addColorStop( 0.95, Qt::yellow );
        }
        // Matlab ColorMap(jet)
//        QwtLinearColorMap(QColor(0,0,189), QColor(132,0,0)) {
//        addColorStop(1.0/13.0*1.0, QColor(0,0,255));
//        addColorStop(1.0/13.0*2.0, QColor(0,66,255));
//        addColorStop(1.0/13.0*3.0, QColor(0,132,255));
//        addColorStop(1.0/13.0*4.0, QColor(0,189,255));
//        addColorStop(1.0/13.0*5.0, QColor(0,255,255));
//        addColorStop(1.0/13.0*6.0, QColor(66,255,189));
//        addColorStop(1.0/13.0*7.0, QColor(132,255,132));
//        addColorStop(1.0/13.0*8.0, QColor(189,255,66));
//        addColorStop(1.0/13.0*9.0, QColor(255,255,0));
//        addColorStop(1.0/13.0*10.0, QColor(255,189,0));
//        addColorStop(1.0/13.0*12.0, QColor(255,66,0));
//        addColorStop(1.0/13.0*13.0, QColor(189,0,0));
//    }
};

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
    void on_buttonFile_clicked();

private:
    Ui::MainWindow *ui;

    QString m_fileName;

    QwtPlotGrid *gridSignal, *gridSpectrum;
    QwtPlotCurve *curvSignal, *curvSpectrum;
    QwtPlotZoomer *zoomSignal;
    QwtPlotSpectrogram *spectrogram;

    void paintSignal(const Aquila::SignalSource& source, size_t sampleRate);
    void paintSpectrum(const Aquila::SignalSource& source);
    void initializePlots();
};

#endif // MAINWINDOW_H
