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
#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>

#include "signal.hpp"

class FftSpectrumData: public QwtRasterData
{
public:
    FftSpectrumData()
    {
        index = 0;
        setInterval(Qt::ZAxis, QwtInterval(0., 10.));
    }

    virtual double value( double x, double y ) const
    {
        if (index >= m_fft.size() || m_fft[index].size() == 0) {
            index = 0;
            return 0.;
        }
        return m_fft[index++].back();
    }

    void setFft(QVector< QVector<double> > v)
    {
        m_fft = v;
    }

protected:
    mutable int index;
    QVector< QVector<double> > m_fft;
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
