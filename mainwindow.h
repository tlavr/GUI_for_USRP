#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void MakeRecord();
    void getFilePath();
    void hideItems();
    void showItems();
    void fillFromParams();
    void setToolTips();
    void setGPSParameters();
    void setLTEParameters();
    void setUMTSParameters();
    void setNbIotParameters();
    void setDVBParameters();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();  

private:
    Ui::MainWindow *ui;
    QButtonGroup dataFormatG, wireFormatG, durationG, antennaG, sourceG, subdeviceG, usrpTypeG, presetsG;
    // variables to be set by po
    QString ip_addr, filename, filepath, datafmt, ant, subdev, ref, wirefmt, args, usrpType;
    QString channel, total_num_samps, spb;
    QString rate, freq, gain, bw, total_time, setup_time, lo_offset;
    bool bw_progress, stats, null_wr, enable_size_map, cont_on_bad_packet, skiplo, intN, showParams;
    void readParameters();
};
#endif // MAINWINDOW_H
