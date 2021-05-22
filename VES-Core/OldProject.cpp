#include "OldProject.h"
#include "VES.h"
#include <QString>
#include <QFile>
#include "LocationData.h"
#include <QVariant>
#include "XmlSerializer.h"
#include "VFSAInversionModel.h"
#include "ZohdyModel.h"

void OldProject::readOldSev(QXmlStreamReader *reader, Project *newProject)
{
    auto *newVes = new VES(nullptr);
    bool read = true;
    reader->readNextStartElement();

    while (read) {
        switch (reader->tokenType()) {
        case QXmlStreamReader::TokenType::Characters:
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::StartElement:
            if (reader->name().toString() == "nombre"){
                newVes->setName(reader->readElementText());
            } else if (reader->name().toString() == "vacio") {
                QString empty = reader->readElementText().toLower();
                if (empty == "true"){
                    newProject->addVES(newVes);
                    return;
                }
            } else if (reader->name().toString() == "coord") {
                readOldCoordinates(reader, newVes);
            } else if (reader->name().toString() == "listaPuntoCampo") {
                newVes->setFieldData(readOldListaPuntoCampo(reader, "listaPuntoCampo"));
                newVes->createSplices();
            } else if (reader->name().toString() == "listaModelos") {
                QList<InversionModel*> tempList;
                bool modelRead = true;
                reader->readNextStartElement();
                while (modelRead) {
                    if (reader->name().toString() == "listaModelos" && reader->tokenType() == QXmlStreamReader::TokenType::EndElement) {
                        modelRead = false;
                    } else {
                        InversionModel* im = readOldModelo(reader);
                        if (im){
                            im->updateModelError(newVes->splices());
                            if (im->usedAlgorithm() == InversionModel::InversionAlgorithm::Vfsa){
                                tempList.append(static_cast<VFSAInversionModel*>(im));
                            }else {
                                tempList.append(static_cast<ZohdyModel*>(im));
                            }
                        }
                    }
                    reader->readNext();
                }

                newVes->setModels(tempList);
            } else if (reader->name().toString() == "modeloSeleccionado") {
                QVariant temp = reader->readElementText();
                newVes->setCurrentIndexModel(temp.toInt());
            } else {
                reader->skipCurrentElement();
            }
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::EndElement:
            if (reader->name().toString() == "SEV"){
                read = false;
            }
            reader->readNext();
            break;
        default:
            reader->readNext();
            break;
        }
    }

    newProject->addVES(newVes);
}

void OldProject::readOldCoordinates(QXmlStreamReader *reader, VES *ves)
{
    LocationData newLoc(ves);
    QVariant tempVariant;

    bool read = true;
    reader->readNextStartElement();
    while (read) {
        switch (reader->tokenType()) {
        case QXmlStreamReader::TokenType::Characters:
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::StartElement:
            if (reader->name().toString() == "coordX"){
                tempVariant = reader->readElementText();
                newLoc.setLocalX(tempVariant.toDouble());
            } else if (reader->name().toString() == "coordY") {
                tempVariant = reader->readElementText();
                newLoc.setLocalY(tempVariant.toDouble());
            } else if (reader->name().toString() == "coordZ") {
                tempVariant = reader->readElementText();
                newLoc.setZ(tempVariant.toDouble());
            } else if (reader->name().toString() == "lat") {
                tempVariant = reader->readElementText();
                newLoc.setDecimalLatitude(tempVariant.toDouble());
            } else if (reader->name().toString() == "lng") {
                tempVariant = reader->readElementText();
                newLoc.setDecimalLongitude(tempVariant.toDouble());
            } else {
                reader->skipCurrentElement();
            }
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::EndElement:
            if (reader->name().toString() == "coord"){
                read = false;
            }
            reader->readNext();
            break;
        default:
            reader->readNext();
            break;
        }
    }
    ves->setLocation(newLoc);
}

QList<BasicData> OldProject::readOldListaPuntoCampo(QXmlStreamReader *reader, const QString &stopName)
{
    QList<BasicData> list;
    QVariant tempVariant;

    bool read = true;
    reader->readNextStartElement();
    while (read) {
        switch (reader->tokenType()) {
        case QXmlStreamReader::TokenType::Characters:
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::StartElement:
            if (reader->name().toString() == "puntoDato"){
                reader->readNextStartElement();
                BasicData bd;
                if (reader->name().toString() == "distAB2") {
                    tempVariant = reader->readElementText();
                    bd.setAb2Distance(tempVariant.toDouble());
                    reader->readNextStartElement();
                }
                if (reader->name().toString() == "res") {
                    tempVariant = reader->readElementText();
                    bd.setResistivity(tempVariant.toDouble());
                }
                list.append(bd);
            }
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::EndElement:
            if (reader->name() == stopName){
                read = false;
            }
            reader->readNext();
            break;
        default:
            reader->readNext();
            break;
        }
    }

    return list;
}

InversionModel * OldProject::readOldModelo(QXmlStreamReader *reader)
{
    QVariant tempVariant;

    bool read = true;
    QString tempName;
    int inversionAlgorithm = 0;
    QList<BasicData> basicDataList;
    QList<ModelData> modeledList;
    reader->readNextStartElement();
    if (reader->isEndElement()){
        return nullptr;
    }
    while (read) {
        switch (reader->tokenType()) {
        case QXmlStreamReader::TokenType::Characters:
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::StartElement:
            if (reader->name().toString() == "nombre"){
                tempName = reader->readElementText();
            } else if (reader->name().toString() == "tipo") {
                tempVariant = reader->readElementText();
                inversionAlgorithm = tempVariant.toInt();
            } else if (reader->name().toString() == "listaPuntoCalculado"){
                basicDataList = readOldListaPuntoCampo(reader, "listaPuntoCalculado");
            } else if (reader->name().toString() == "listaModeloSEVs"){
                modeledList = readOldModeloSEVs(reader);
            } else {
                reader->skipCurrentElement();
            }
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::EndElement:
            if (reader->name().toString() == "modelo"){
                read = false;
            }
            reader->readNext();
            break;
        default:
            reader->readNext();
            break;
        }
    }

    InversionModel* tempModel;
    if (inversionAlgorithm == 0){
        auto *zm = new ZohdyModel(tempName);
        tempModel = zm;
    } else {
        auto *vm = new VFSAInversionModel(tempName);
        tempModel = vm;
    }
    tempModel->setCalculatedData(basicDataList);
    tempModel->setModelData(modeledList);

    return tempModel;
}

QList<ModelData> OldProject::readOldModeloSEVs(QXmlStreamReader *reader)
{
    QList<ModelData> list;
    QVariant tempVariant;

    bool read = true;
    reader->readNextStartElement();
    while (read) {
        switch (reader->tokenType()) {
        case QXmlStreamReader::TokenType::Characters:
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::StartElement:
            if (reader->name().toString() == "puntoModelo"){
                reader->readNextStartElement();
                ModelData md;
                if (reader->name().toString() == "desdeM") {
                    tempVariant = reader->readElementText();
                    md.setFrom(tempVariant.toDouble());
                    reader->readNextStartElement();
                }
                if (reader->name().toString() == "hastaM") {
                    tempVariant = reader->readElementText();
                    md.setUntil(tempVariant.toDouble());
                    reader->readNextStartElement();
                }
                if (reader->name().toString() == "resCalc") {
                    tempVariant = reader->readElementText();
                    md.setResistivity(tempVariant.toDouble());
                    reader->readNextStartElement();
                }
                if (reader->name().toString() == "espesor") {
                    tempVariant = reader->readElementText();
                    md.setThickness(tempVariant.toDouble());
                    reader->readNextStartElement();
                }
                if (reader->name().toString() == "profundidad") {
                    tempVariant = reader->readElementText();
                    md.setDepth(tempVariant.toDouble());
                    reader->readNextStartElement();
                }
//                if (reader->name() == "resistenciaTrasnveral") {
//                    tempVariant = reader->readElementText();
//                    md.setTransverseResistence(tempVariant.toDouble());
//                    reader->readNextStartElement();
//                }
//                if (reader->name() == "conductanciaLongitudinal") {
//                    tempVariant = reader->readElementText();
//                    md.setLongitudinalConductance(tempVariant.toDouble());
//                }
                list.append(md);
            }
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::EndElement:
            if (reader->name().toString() == "listaModeloSEVs"){
                read = false;
            }
            reader->readNext();
            break;
        default:
            reader->readNext();
            break;
        }
    }

    return list;
}

OldProject::OldProject(QObject *parent) : QObject(parent)
{

}

Project *OldProject::readOldProject(const QString &filename)
{
    QFile file(filename);
    QXmlStreamReader *reader;
    if (file.exists() && file.open(QFile::ReadOnly | QFile::Text)){
        reader = new QXmlStreamReader(file.readAll());
    }else {
        return nullptr;
    }


    auto *newProject = new Project;
    reader->readNextStartElement();
    reader->readNextStartElement();
    bool read = true;
    while (!reader->atEnd() && read) {
        switch (reader->tokenType()) {
        case QXmlStreamReader::TokenType::Characters:
            reader->readNext();
            break;
        case QXmlStreamReader::TokenType::StartElement:
            if (reader->name().toString() == "listaSEVs"){
                reader->readNextStartElement();
                bool vesRead = true;
                while (vesRead) {
                    if (reader->name().toString() == "listaSEVs" && reader->tokenType() == QXmlStreamReader::TokenType::EndElement) {
                        vesRead = false;
                    } else {
                        readOldSev(reader, newProject);
                    }
                    reader->readNext();
                }
            } else if (reader->name().toString() == "nombre") {
                newProject->setName(reader->readElementText());
            } else if (reader->name().toString() == "sevSeleccionado") {
                QVariant index = reader->readElementText();
                newProject->setCurrentIndex(index.toInt());
            } else {
                reader->skipCurrentElement();
            }
            break;
        case QXmlStreamReader::TokenType::EndElement:
            if (reader->name().toString() == "proyectoSEVs"){
                read = false;
            }
            reader->readNext();
            break;
        default:
            reader->readNext();
            break;
        }
    }

    return newProject;
}
