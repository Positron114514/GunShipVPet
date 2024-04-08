#ifndef VPETINTERFACE_H
#define VPETINTERFACE_H

#include "qheaders.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class VPetInterface;
}
QT_END_NAMESPACE

class VPetInterface : public QWidget
{
    Q_OBJECT

public:
    VPetInterface(QWidget *parent = nullptr);
    ~VPetInterface();

private:
    Ui::VPetInterface *ui;
};
#endif // VPETINTERFACE_H
