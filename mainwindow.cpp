#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializePlots();

//    spectrogram = new QwtPlotSpectrogram;

//    spectrogram->setColorMap( new ColorMap() );
//    spectrogram->setData(new RasterData());

//    spectrogram->attach(ui->plotSpectrum);
//    ui->plotSpectrum->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintSignal(const Aquila::SignalSource& source, size_t sampleRate)
{
    if (curvSignal != nullptr) {
        delete curvSignal;
    }

    curvSignal = new QwtPlotCurve(QString("A(t)"));
    curvSignal->setRenderHint(QwtPlotItem::RenderAntialiased);
    curvSignal->setPen(QRgb(0xff427dd3));

    QVector<double> x;
    QVector<double> y;

    double time = 0.;
    double step = 1. / sampleRate;
    for(auto signalCount : source) {
        x.push_back( time );
        y.push_back( signalCount );
        time += step;
    }

    curvSignal->setSamples(x, y);
    curvSignal->attach(ui->plotSignal);
    ui->plotSignal->replot();
}

void MainWindow::paintSpectrum(const Aquila::SignalSource& source)
{
//    if (curvSpectrum != nullptr) {
//        delete curvSpectrum;
//    }

//    curvSpectrum = new QwtPlotCurve(QString("A(t)"));
//    curvSpectrum->setRenderHint(QwtPlotItem::RenderAntialiased);
//    curvSpectrum->setPen(QPen(Qt::red));

//    QwtSymbol *symbol = new QwtSymbol();
//    symbol->setStyle(QwtSymbol::Ellipse);
//    symbol->setPen(QColor(Qt::black));
//    symbol->setSize(4);
//    curvSpectrum->setSymbol(symbol);

//    QVector<double> x;
//    QVector<double> y;

//    for(SignalCount signalCount : signal_I) {
//        x.push_back( signalCount.getTime() );
//        y.push_back( signalCount.getValue() );
//    }

////    ui->SpectrumPlot->setAxisScale(1,0.,x.back());
//    curvSpectrum->setSamples(x, y);
//    curvSpectrum->attach(ui->SpectrumPlot);
//    ui->SpectrumPlot->replot();
}

void MainWindow::initializePlots()
{
    ui->plotSignal->setTitle( tr("Input Signal") );
    ui->plotSpectrum->setTitle( tr("Signal Spectrum") );

    // Grid
    gridSignal = new QwtPlotGrid;
    gridSignal->enableXMin(true);
    gridSignal->setMajorPen(QPen(Qt::black,0,Qt::DotLine));
    gridSignal->setMinorPen(QPen(Qt::gray,0,Qt::DotLine));
    gridSignal->attach(ui->plotSignal);

    // Grid
    gridSpectrum = new QwtPlotGrid;
    gridSpectrum->enableXMin(true);
    gridSpectrum->setMajorPen(QPen(Qt::black,0,Qt::DotLine));
    gridSpectrum->setMinorPen(QPen(Qt::gray,0,Qt::DotLine));
    gridSpectrum->attach(ui->plotSpectrum);

    //Zoom
    zoomSignal = new QwtPlotZoomer(ui->plotSignal->canvas());

    curvSignal = nullptr;
    curvSpectrum = nullptr;
}

void MainWindow::on_buttonFile_clicked()
{
    m_fileName = QFileDialog::getOpenFileName(this,
        tr("Open PNG Image"), tr("/home/rain/work_dir"), tr("AUDIO Files (*.wav *.ogg *.mp3 *.flac)"));

    ui->labelFile->setText(m_fileName);

    Signal s;
    s.loadFromFile(m_fileName.toStdString());
    paintSignal(s, s.getSampleRate());

    QVector< QVector3D > map = s.getSpectrum();

    spectrogram = new QwtPlotSpectrogram;
    FftSpectrumData * r = new FftSpectrumData();
    r->setInterval(Qt::XAxis, QwtInterval(0., map.back().x()));
    r->setInterval(Qt::YAxis, QwtInterval(0., map.back().y()));
    r->setData( map );

    std::cout << map.back().x() << ";" << map.back().y() << ";" << map.back().z();

    spectrogram->setColorMap( new ColorMap() );
    spectrogram->setData(r);

    spectrogram->attach(ui->plotSpectrum);
    ui->plotSpectrum->replot();
}
