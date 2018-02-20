//https://doc.qt.io/qt-5.10/qtcharts-piechart-example.html

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPieSeries *series = new QPieSeries();
    series->append("Setor 1", 1);
    series->append("Setor 2", 1);
    series->append("Setor 3", 1);
    series->append("Setor 4", 1);
    series->append("Setor 5", 2);

//    QPieSlice *slice = series->slices().at(4);
//    slice->setExploded();
//    slice->setLabelVisible();
//    slice->setPen(QPen(Qt::darkGreen, 2));
//    slice->setBrush(Qt::green);

    for (auto i_slice : series->slices())
        i_slice->setLabelVisible();

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pivo Krebsfer");
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
