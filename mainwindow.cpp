#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QDateTime>
#include <windows.h>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    presetsG.addButton(ui->GpsL1CARB);
    presetsG.addButton(ui->Lte10RB);
    presetsG.addButton(ui->UmtsRB);
    presetsG.addButton(ui->NbiotRB);
    presetsG.addButton(ui->Dvbt2RB);
    usrpTypeG.addButton(ui->Usrp2RB);
    usrpTypeG.addButton(ui->UsrpB210RB);
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
    connect(ui->GpsL1CARB, &QPushButton::clicked, this, &MainWindow::setGPSParameters);
    connect(ui->Lte10RB, &QPushButton::clicked, this, &MainWindow::setLTEParameters);
    connect(ui->UmtsRB, &QPushButton::clicked, this, &MainWindow::setUMTSParameters);
    connect(ui->NbiotRB, &QPushButton::clicked, this, &MainWindow::setNbIotParameters);
    connect(ui->Dvbt2RB, &QPushButton::clicked, this, &MainWindow::setDVBParameters);

    this->setToolTips();
}

void MainWindow::setGPSParameters(){
    //if (presetsG.checkedButton() == ui->GpsL1CARB){
        ui->CarrierFreqEdit->setText("1575420000");
        ui->Int16RB->setChecked(true);
        ui->Sc16RB->setChecked(true);
        ui->SecondsRB->setChecked(true);
        ui->SecondsEdit->setText("20");
        ui->OffsetEdit->setText("0");
        ui->BandwidthEdit->setText("2500000");
        ui->ChannelEdit->setText("0");
        ui->SamplesBufferEdit->setText("2944");
        ui->SampleRateEdit->setText("5000000");
        ui->GainEdit->setText("35");
        ui->SetupTimeEdit->setText("3");
        this->readParameters();
   // }
}

void MainWindow::setLTEParameters(){
    ui->CarrierFreqEdit->setText("184400000");
    ui->Int8RB->setChecked(true);
    ui->Sc8RB->setChecked(true);
    ui->SecondsRB->setChecked(true);
    ui->SecondsEdit->setText("30");
    ui->OffsetEdit->setText("0");
    ui->BandwidthEdit->setText("10000000");
    ui->ChannelEdit->setText("0");
    ui->SamplesBufferEdit->setText("2944");
    ui->SampleRateEdit->setText("20000000");
    ui->GainEdit->setText("30");
    ui->SetupTimeEdit->setText("3");
    this->readParameters();
}

void MainWindow::setUMTSParameters(){
    ui->CarrierFreqEdit->setText("219200000");
    ui->Int8RB->setChecked(true);
    ui->Sc8RB->setChecked(true);
    ui->SecondsRB->setChecked(true);
    ui->SecondsEdit->setText("30");
    ui->OffsetEdit->setText("0");
    ui->BandwidthEdit->setText("5000000");
    ui->ChannelEdit->setText("0");
    ui->SamplesBufferEdit->setText("2944");
    ui->SampleRateEdit->setText("10000000");
    ui->GainEdit->setText("30");
    ui->SetupTimeEdit->setText("3");
    this->readParameters();
}

void MainWindow::setNbIotParameters(){
    ui->CarrierFreqEdit->setText("784000000");
    ui->Int8RB->setChecked(true);
    ui->Sc8RB->setChecked(true);
    ui->SecondsRB->setChecked(true);
    ui->SecondsEdit->setText("30");
    ui->OffsetEdit->setText("0");
    ui->BandwidthEdit->setText("10000000");
    ui->ChannelEdit->setText("0");
    ui->SamplesBufferEdit->setText("2944");
    ui->SampleRateEdit->setText("20000000");
    ui->GainEdit->setText("30");
    ui->SetupTimeEdit->setText("3");
    this->readParameters();
}

void MainWindow::setDVBParameters(){
    ui->CarrierFreqEdit->setText("546000000");
    ui->Int8RB->setChecked(true);
    ui->Sc8RB->setChecked(true);
    ui->SecondsRB->setChecked(true);
    ui->SecondsEdit->setText("30");
    ui->OffsetEdit->setText("0");
    ui->BandwidthEdit->setText("10000000");
    ui->ChannelEdit->setText("0");
    ui->SamplesBufferEdit->setText("2944");
    ui->SampleRateEdit->setText("20000000");
    ui->GainEdit->setText("30");
    ui->SetupTimeEdit->setText("3");
    this->readParameters();
}

void MainWindow::setToolTips(){
    int tipDuration = 10000;
    ui->PresetsGroup->setToolTip("By choosing one of the presets you can change all the parameters according to the chosen system in one click.");
    ui->PresetsGroup->setToolTipDuration(tipDuration);
    ui->UsrpTypeGroup->setToolTip("Choose the right type of USRP device. It influences some internal functions and parameters configuration.");
    ui->UsrpTypeGroup->setToolTipDuration(tipDuration);
    ui->IpLabel->setToolTip("USRP type 2 series device IP address.");
    ui->IpLabel->setToolTipDuration(tipDuration);
    ui->IpEdit->setToolTip("USRP type 2 series device IP address.");
    ui->IpEdit->setToolTipDuration(tipDuration);
    ui->FileNameLabel->setToolTip("The name and the type of file containing the recorded signal.");
    ui->FileNameLabel->setToolTipDuration(tipDuration);
    ui->FileNameEdit->setToolTip("The name and the type of file containing the recorded signal.");
    ui->FileNameEdit->setToolTipDuration(tipDuration);
    ui->FileNameButton->setToolTip("Click to change output file name according to the parameters selected below and current system time.");
    ui->FileNameButton->setToolTipDuration(tipDuration);
    ui->FilePathLabel->setToolTip("Path to directory containing the output file (by default path is equal to programm path)");
    ui->FilePathLabel->setToolTipDuration(tipDuration);
    ui->FilePathEdit->setToolTip("Path to directory containing the output file (by default path is equal to programm path)");
    ui->FilePathEdit->setToolTipDuration(tipDuration);
    ui->FilePathButton->setToolTip("Click to choose the output file directory.");
    ui->FilePathButton->setToolTipDuration(tipDuration);
    ui->DataFormatGroup->setToolTip("Output data format is the way of IQ samples stored in file.");
    ui->DataFormatGroup->setToolTipDuration(tipDuration);
    ui->WireFormatGroup->setToolTip("Wire format is the way of samples transmission to the computer over-the-wire. 32 bits of information are "
                                    "always transmited. For example, complex 8 bit means that there are two pair of 16 bit IQ samples are "
                                    "transmited (Q8_1 I8_1 Q8_0 I8_0). For complex 16 bit only one pair is transmitted (Q16 I16). So if you "
                                    "choose complex 8 bit format the maximum sampling rate could be 2 times greater.");
    ui->WireFormatGroup->setToolTipDuration(tipDuration);
    ui->RecordDurationGroup->setToolTip("Choose the constraint for signal recording: by time in seconds of by total amount of samples.");
    ui->RecordDurationGroup->setToolTipDuration(tipDuration);
    ui->CarrierFreqLabel->setToolTip("The central frequency of recorded signal. ");
    ui->CarrierFreqLabel->setToolTipDuration(tipDuration);
    ui->CarrierFreqEdit->setToolTip("The central frequency of recorded signal. ");
    ui->CarrierFreqEdit->setToolTipDuration(tipDuration);
    ui->OffsetLabel->setToolTip("Offset for frontend LO in Hz.");
    ui->OffsetLabel->setToolTipDuration(tipDuration);
    ui->OffsetEdit->setToolTip("Offset for frontend LO in Hz.");
    ui->OffsetEdit->setToolTipDuration(tipDuration);
    ui->BandwidthLabel->setToolTip("Analog frontend filter bandwidth in Hz.");
    ui->BandwidthLabel->setToolTipDuration(tipDuration);
    ui->BandwidthEdit->setToolTip("Analog frontend filter bandwidth in Hz.");
    ui->BandwidthEdit->setToolTipDuration(tipDuration);
    ui->ChannelLabel->setToolTip("USRP channel selection.");
    ui->ChannelLabel->setToolTipDuration(tipDuration);
    ui->ChannelEdit->setToolTip("USRP channel selection.");
    ui->ChannelEdit->setToolTipDuration(tipDuration);
    ui->SamplesBufferLabel->setToolTip("This parameter defines vector buffer size for sample storage. In this version two different threads"
                                       "are used to store samples in vector and write them to file. Default value of MTU for data transmission is 1472."
                                       "So it's recommended to select buffer size value equal to multiple of 1472. The greater this value the more"
                                       "RAM memory is needed to store temporary samples.");
    ui->SamplesBufferLabel->setToolTipDuration(tipDuration);
    ui->SamplesBufferEdit->setToolTip("This parameter defines vector buffer size for sample storage. In this version two different threads"
                                       "are used to store samples in vector and write them to file. Default value of MTU for data transmission is 1472."
                                       "So it's recommended to select buffer size value equal to multiple of 1472. The greater this value the more"
                                       "RAM memory is needed to store temporary samples.");
    ui->SamplesBufferEdit->setToolTipDuration(tipDuration);
    ui->SampleRateEdit->setToolTip("Rate of incoming samples.");
    ui->SampleRateEdit->setToolTipDuration(tipDuration);
    ui->SampleRateLabel->setToolTip("Rate of incoming samples.");
    ui->SampleRateLabel->setToolTipDuration(tipDuration);
    ui->GainLabel->setToolTip("Gain for the RF chain");
    ui->GainLabel->setToolTipDuration(tipDuration);
    ui->GainEdit->setToolTip("Gain for the RF chain");
    ui->GainEdit->setToolTipDuration(tipDuration);
    ui->SetupTimeLabel->setToolTip("USRP postpones the start of signal recording for the selected amount of seconds. It might be needed to let"
                                   "all the transient processes to finish in RF elements ");
    ui->SetupTimeLabel->setToolTipDuration(tipDuration);
    ui->SetupTimeEdit->setToolTip("USRP postpones the start of signal recording for the selected amount of seconds. It might be needed to let"
                                   "all the transient processes to finish in RF elements ");
    ui->SetupTimeEdit->setToolTipDuration(tipDuration);
    ui->AntennaGroup->setToolTip("Select one of the USRP antennas.");
    ui->AntennaGroup->setToolTipDuration(tipDuration);
    ui->SyncSourceGroup->setToolTip("Select the reference source of synchronization. ");
    ui->SyncSourceGroup->setToolTipDuration(tipDuration);
    ui->SubdeviceGroup->setToolTip("If there are more than one motherboards(for example with different firmware releases) you can "
                                   "choose the one you need.");
    ui->SubdeviceGroup->setToolTipDuration(tipDuration);
    ui->OptionsGroup->setToolTip("Select optional parameters of signal recording programm.");
    ui->OptionsGroup->setToolTipDuration(tipDuration);

}
void MainWindow::MakeRecord(){
    readParameters();
    if (usrpType == ui->Usrp2RB->objectName()){
        //rx_samples_to_file.exe --args addr="192.168.10.2" --file NbIoT_10_11_2020_18_19_10MHz_1chL1_int8_30s_bw5MHz_20dB_offs0MHz.dat
        //--type char --duration 30 --spb 2944 --rate 10000000 --freq 780000000 --lo-offset 0 --wirefmt sc8 --gain 20 --ant RX2
        //--subdev A:0 --bw 5000000   --setup 2 --progress --stats
        args = " --args addr=";
        args += (ip_addr + " --file ");
        args += (filepath + "/" + filename + " --type ");
        if (datafmt == ui->Int8RB->objectName())
            args += ("char ");
        else if (datafmt == ui->Int16RB->objectName())
            args += ("short ");
        else if (datafmt == ui->FloatRB->objectName())
            args += ("float ");
        else if (datafmt == ui->DoubleRB->objectName())
            args += ("double ");
        if (total_num_samps == "")
            args += ("--duration " + total_time + " --spb ");
        else
            args += ("--nsamps " + total_num_samps + " --spb ");
        args += (spb + " --rate ");
        args += (rate + " --freq ");
        args += (freq + " --lo-offset ");
        args += (lo_offset + " --gain ");
        args += (gain + " --ant ");
        args += (ant + " --subdev ");
        args += (subdev + " --channel ");
        args += (channel + " --bw ");
        args += (bw + " --ref ");
        args += (ref + " --wirefmt ");
        if (wirefmt == ui->Sc8RB->objectName())
            args += ("sc8 --setup ");
        else if (wirefmt == ui->Sc16RB->objectName())
            args += ("sc16 --setup ");
        args += setup_time;
        if (bw_progress)
            args += " --progress";
        if (stats)
            args += " --stats";
        if (enable_size_map)
            args += " --sizemap";
        if (null_wr)
            args += " --null";
        if (cont_on_bad_packet)
            args += " --continue";
        if (skiplo)
            args += " --skip-lo";
        if (intN)
            args += " --int-n";
        if (showParams)
            QMessageBox::information(this, tr("Usrp type USRP2"),"Application path:\n"
                                     + QCoreApplication::applicationDirPath() + "\nParameters:\n" + args);

        QString program = "cmd.exe";
        QStringList arguments;
        arguments << "/k" << QCoreApplication::applicationDirPath() + QDir::separator() + "rx_samples_to_file.exe" + args;
        //bool isStarted, isFinished;
        //qint64 pID;
        QProcess *sigRec = new QProcess(this);
        sigRec->setCreateProcessArgumentsModifier([] (QProcess::CreateProcessArguments *cr_args)
            {
                cr_args->flags |= CREATE_NEW_CONSOLE;
                cr_args->startupInfo->dwFlags &= ~STARTF_USESTDHANDLES;
                //cr_args->startupInfo->dwFlags |= STARTF_USEFILLATTRIBUTE;
                //cr_args->startupInfo->dwFillAttribute = BACKGROUND_DEFAULT | FOREGROUND_RED
                //                                           | FOREGROUND_INTENSITY;
            });
        sigRec->start(program, arguments);
        sigRec->waitForReadyRead(5000);
        sigRec->close();

        /*isFinished = sigRec->waitForFinished();
        if (isFinished){
            QString pidString;
            pidString.setNum(pID);
            QString killProcessUsingPid = "taskkill /PID ";
            killProcessUsingPid.append(pidString);
            system(killProcessUsingPid.toStdString().c_str());
        }
        //std::system((program + " " + args).toStdString().c_str());
        //QProcess *sigRec = new QProcess(this);
        //sigRec->execute(program, arguments);

        if (!isStarted){
            QMessageBox::critical(
              this,
              tr("Usrp type USRP2"),
              tr("ERROR! Something went wrong!") );
        }*/
    } else {
        QMessageBox::critical(
          this,
          tr("Usrp type B210"),
          tr("This type of USRP isn't supported yet! Sorry!") );
    }
}

void MainWindow::fillFromParams(){
    readParameters();
    QDateTime curTime;
    curTime = QDateTime::currentDateTime();
    QString curTimeStr = curTime.toString();
    QString dd, mm, yy, hh, mins;
    dd = curTimeStr[7];
    mm = QString(curTimeStr[3]) + curTimeStr[4] + curTimeStr[5];
    yy = QString(curTimeStr[18]) + curTimeStr[19] + curTimeStr[20] + curTimeStr[21];
    hh = QString(curTimeStr[9]) + curTimeStr[10];
    mins = QString(curTimeStr[12]) + curTimeStr[13];
    QString tmpBw, tmpRate;
    tmpBw.setNum(this->bw.toInt()/1e6, 'f', 2);
    tmpRate.setNum(this->rate.toInt()/1e6, 'f', 2);
    this->filename = "";
    // GPS_dd_mm_year_hh_mm_5MHz_1ch_int16_30s_bw2.5MHz_38dB_offs0MHz.dat
    this->filename = this->filename + "SIG_" +dd +"_"+mm+"_"+yy+"_"+hh+"_"+mins+"_"+ tmpRate + "MHz_" + \
            ui->ChannelEdit->text() + "ch_" + dataFormatG.checkedButton()->text() + "_bw" + \
            tmpBw + "MHz_" + ui->GainEdit->text() + "dB_offs" + ui->OffsetEdit->text() + "MHz.dat";
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
    bw_progress = false;
    stats = false;
    enable_size_map = false;
    null_wr = false;
    cont_on_bad_packet = false;
    skiplo = false;
    intN = false;
    showParams = false;
    this->usrpType = usrpTypeG.checkedButton()->objectName();
    this->ip_addr = ui->IpEdit->text();
    this->filepath = ui->FilePathEdit->text();
    this->filename = ui->FileNameEdit->text();
    this->datafmt = dataFormatG.checkedButton()->objectName();
    this->wirefmt = wireFormatG.checkedButton()->objectName();
    if (durationG.checkedButton() == ui->SecondsRB){
        this->total_time = ui->SecondsEdit->text();
        this->total_num_samps = "";
    } else {
        this->total_time = "";
        this->total_num_samps = ui->SamplesEdit->text();
    }
    this->freq = ui->CarrierFreqEdit->text();
    this->lo_offset = ui->OffsetEdit->text();
    this->bw = ui->BandwidthEdit->text();
    this->channel = ui->ChannelEdit->text();
    this->spb = ui->SamplesBufferEdit->text();
    this->rate = ui->SampleRateEdit->text();
    this->gain = ui->GainEdit->text();
    if (antennaG.checkedButton() == ui->RxtxRB){
        this->ant = "TX/RX";
    } else {
        this->ant = "RX2";
    }
    this->ref = sourceG.checkedButton()->text();
    this->subdev = subdeviceG.checkedButton()->text();
    this->setup_time = ui->SetupTimeEdit->text();
    if (ui->ProgressCB->isChecked()) this->bw_progress = true;
    if (ui->StatsCB->isChecked()) this->stats = true;
    if (ui->SizemapCB->isChecked()) this->enable_size_map = true;
    if (ui->NullCB->isChecked()) this->null_wr = true;
    if (ui->ContinueCB->isChecked()) this->cont_on_bad_packet = true;
    if (ui->SkipLOCB->isChecked()) this->skiplo = true;
    if (ui->IntNCB->isChecked()) this->intN = true;
    if (ui->ShowParamsCB->isChecked()) this->showParams = true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

