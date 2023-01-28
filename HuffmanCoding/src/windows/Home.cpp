

#include "Home.h"

Home::Home() {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, width(), height());
    setScene(scene);
    background = new Background(":/images/homeBG");
    scene->addItem(background);


    browseButton = new Button(160, 150, "white");
    browseButton->setPlainText("BROWSE");
    browseButton->setPos(height() / 10, height() / 10);
    connect(browseButton, &Button::press, this, &Home::browse);
    scene->addItem(browseButton);

    inAddressLabel = new Label(30, "white");
    inAddressLabel->setPlainText("");
    inAddressLabel->setPos(height() / 2, height() / 10);
    scene->addItem(inAddressLabel);


    convertButton = new Button(160, 150, "white");
    convertButton->setPlainText("CONVERT");
    convertButton->setPos(height() / 10, height() / 2.7);
    connect(convertButton, &Button::press, this, &Home::convertFile);
    scene->addItem(convertButton);
    convertButton->setVisible(false);

    resultLabel = new Label(40, "red");
    resultLabel->setPlainText("");
    resultLabel->setPos(height() / 2, height() / 1.5);
    scene->addItem(resultLabel);

    outAddressLabel = new Label(30, "white");
    outAddressLabel->setPlainText("");
    outAddressLabel->setPos(height() / 2, height() / 2.7);
    scene->addItem(outAddressLabel);


    exitButton = new Button(85, 100, "white");
    exitButton->setPlainText("EXIT");
    exitButton->setPos(width() / 2 - 50, 0);
    connect(exitButton, &Button::press, this, &Home::exitSlot);
    scene->addItem(exitButton);


}

Home::~Home() {
    delete background;
    delete browseButton;
    delete convertButton;
    delete resultLabel;
    delete exitButton;
    delete inAddressLabel;
    delete outAddressLabel;
    delete scene;
}


void Home::browse() {
    outAddressLabel->setPlainText("");
    inAddressLabel->setPlainText("");
    inputFilePath = QFileDialog::getOpenFileName(this, tr("Select Text"));
    QFile file(inputFilePath);
    inputFileSize = file.size();
    inAddressLabel->setPlainText(inputFilePath + "\n\n" + QString::number(inputFileSize) + " bytes");
    fileType = checkFile();
    if (!fileType.isEmpty()) {
        convertButton->setVisible(true);
        displayResult("Converting...");
    } else {
        outAddressLabel->setPlainText("");
        inAddressLabel->setPlainText("");
        displayResult("Error");
        convertButton->setVisible(false);
    }
}

void Home::convertFile() {
    if (!fileType.isEmpty()) {
        outputFilePath = QFileDialog::getSaveFileName(this, tr("Save as"));
        if (!outputFilePath.isEmpty()) {
            outputFilePath = outputFilePath + fileType;
            Huffman conversion(inputFilePath.toStdString(), outputFilePath.toStdString());
            conversion.startConversion(fileType);
            QFile file(outputFilePath);
            outputFileSize = file.size();
            outAddressLabel->setPlainText(outputFilePath + "\n\n" + QString::number(outputFileSize) + " bytes");
            displayPercent();
        }
    }
}

void Home::exitSlot() {
    exit(0);
}

QString Home::checkFile() {
    if (inputFilePath != "") {
        int size = inputFilePath.size();
        QString type = inputFilePath[size - 3];
        type.append(inputFilePath[size - 2]);
        type.append(inputFilePath[size - 1]);
        if (type == "txt")
            return ".cmp";
        else if (type == "cmp")
            return ".txt";
    }
    return "";
}


void Home::displayResult(QString text) {
    if (text == "Error") {
        resultLabel->setPlainText("Please choose correct file!  (.txt or .cmp)");
        if (resultLabel->defaultTextColor() != "red")
            resultLabel->setDefaultTextColor("red");
        else
            resultLabel->setDefaultTextColor("yellow");
        resultLabel->setPos(height() / 2, height() / 10);
    } else {
        resultLabel->setPlainText(text);
        resultLabel->setDefaultTextColor("#3B92E3");
        resultLabel->setPos(height() / 2, height() / 1.5);
    }
}

void Home::displayPercent() {
    int percent;
    displayResult("");
    if (fileType == ".cmp") {
        percent = (inputFileSize - outputFileSize) * 100 / inputFileSize;
        percent = percent < 0 ? 0 : percent;
        resultLabel->setPlainText("File Compressed and Decreased by " + QString::number(percent) + "%");
    } else {
        percent = (outputFileSize - inputFileSize) * 100 / outputFileSize;
        percent = percent < 0 ? 0 : percent;
        resultLabel->setPlainText("File Decompressed and Increased by " + QString::number(percent) + "%");
    }
    fileType = "";
}
