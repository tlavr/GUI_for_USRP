#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataFormatG.addButton(ui->Int8RB);
    dataFormatG.addButton(ui->Int16RB);
    dataFormatG.addButton(ui->FloatRB);
    dataFormatG.addButton(ui->DoubleRB);
    wireFormatG.addButton(ui->Sc8RB);
    wireFormatG.addButton(ui->Sc16RB);
    durationG.addButton(ui->SecondsRB);
    durationG.addButton(ui->SamplesRB);
    antennaG.addButton(ui->RxtxRB);
    antennaG.addButton(ui->Rx2RB);
    sourceG.addButton(ui->InternalRB);
    sourceG.addButton(ui->ExternalRB);
    sourceG.addButton(ui->MimoRB);
    sourceG.addButton(ui->GpsRB);
    subdeviceG.addButton(ui->A0RB);
    subdeviceG.addButton(ui->A1RB);

    ui->FilePathEdit->setText(QDir::currentPath());
    connect(ui->MakeRecordButton, &QPushButton::clicked, this, &MainWindow::MakeRecord);
    connect(ui->FilePathButton, &QPushButton::clicked, this, &MainWindow::getFilePath);
    connect(ui->UsrpB210RB, &QPushButton::clicked, this, &MainWindow::hideItems);
    connect(ui->Usrp2RB, &QPushButton::clicked, this, &MainWindow::showItems);
    connect(ui->FileNameButton, &QPushButton::clicked, this, &MainWindow::fillFromParams);
}

void MainWindow::MakeRecord(){
    readParameters();
}

void MainWindow::fillFromParams(){
    readParameters();
    this->filename = "";
    // GPS_dd_mm_year_hh_mm_5MHz_1ch_int16_30s_bw2.5MHz_38dB_offs0MHz.dat
    this->filename = this->filename + "SIG_dd_mm_year_hh_mm_" + QString::fromStdString(std::to_string(this->rate/1e6)) + "MHz_" + \
            ui->ChannelEdit->text() + "ch_" + dataFormatG.checkedButton()->objectName() + "_bw" + \
            QString::fromStdString(std::to_string(this->bw/1e6)) + "MHz_" + \
            ui->GainEdit->text() + "dB_offs" + ui->OffsetEdit->text() + "MHz.dat";
    ui->FileNameEdit->setText(this->filename);

}

void MainWindow::getFilePath(){
    this->filepath = QFileDialog::getExistingDirectory();
    ui->FilePathEdit->setText(this->filepath);
}

void MainWindow::hideItems(){
    ui->IpLabel->setDisabled(true);
    ui->IpEdit->setDisabled(true);
}

void MainWindow::showItems(){
    ui->IpLabel->setEnabled(true);
    ui->IpEdit->setEnabled(true);
}

void MainWindow::readParameters(){
    this->ip_addr = ui->IpEdit->text();
    this->filepath = ui->FilePathEdit->text();
    this->filename = ui->FileNameEdit->text();
    this->datafmt = dataFormatG.checkedButton()->objectName();
    this->wirefmt = wireFormatG.checkedButton()->objectName();
    if (durationG.checkedButton() == ui->SecondsRB){
        this->total_time = ui->SecondsEdit->text().toDouble();
        this->total_num_samps = 0;
    } else {
        this->total_time = 0;
        this->total_num_samps = ui->SamplesEdit->text().toInt();
    }
    this->freq = ui->CarrierFreqEdit->text().toDouble();
    this->lo_offset = ui->OffsetEdit->text().toDouble();
    this->bw = ui->BandwidthEdit->text().toDouble();
    this->channel = ui->ChannelEdit->text().toInt();
    this->spb = ui->SamplesBufferEdit->text().toInt();
    this->rate = ui->SampleRateEdit->text().toDouble();
    this->gain = ui->SetupTimeEdit->text().toDouble();
    if (antennaG.checkedButton() == ui->RxtxRB){
        this->ant = "RX/TX";
    } else {
        this->ant = "RX2";
    }
    this->ref = sourceG.checkedButton()->objectName();
    this->subdev = subdeviceG.checkedButton()->objectName();
    if (ui->ProgressCB->isChecked()) this->bw_progress = true;
    if (ui->StatsCB->isChecked()) this->stats = true;
    if (ui->SizemapCB->isChecked()) this->enable_size_map = true;
    if (ui->NullCB->isChecked()) this->null = true;
    if (ui->ContinueCB->isChecked()) this->cont_on_bad_packet = true;
    if (ui->SkipLOCB->isChecked()) this->skiplo = true;
    if (ui->IntNCB->isChecked()){
        this->intN = true;
        this->intN_num = ui->IntNEdit->text().toInt();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

