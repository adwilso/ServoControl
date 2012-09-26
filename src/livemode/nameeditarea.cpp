#include "nameeditarea.h"
#include "ui_nameeditarea.h"


NameEditArea::NameEditArea(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::NameEditArea)
{
    ui->setupUi(this);

    label = new ClickLabel(this);
    label->resize(113,21);
    label->move(2,0);
    label->setVisible(true);
    label->setAlignment(Qt::AlignVCenter | Qt::AlignJustify );
    ui->lineEdit->setAlignment(Qt::AlignVCenter | Qt::AlignJustify );
    ui->lineEdit->setVisible(false);

    ui->lineEdit->setInputMask("Nnnnnnnnnnnnnnnnnn");//20 char max
    QFont shell("MS Shell Dlg 2",8);
    label->setFont(shell);
    ui->lineEdit->setFont(shell);

    connect(label, SIGNAL(clicked()),SLOT(labelClicked()));
    connect(ui->lineEdit,SIGNAL(editingFinished()),SLOT(editFinished()));
    label->setText("Position 1");
}

NameEditArea::~NameEditArea()
{
    delete ui;
}

QString NameEditArea::getName()
{
    return this->label->text();
}

void NameEditArea::lostFocus()
{
    if (this->label->isVisible())
    {
        return;
    }
    this->editFinished();
}

void NameEditArea::labelClicked()
{
    ui->lineEdit->setVisible(true);
    label->setVisible(false);
    ui->lineEdit->setText(label->text());
    ui->lineEdit->setFocus();
    emit this->focusShifted(0);
}
void NameEditArea::editFinished()
{
    label->setVisible(true);
    ui->lineEdit->setVisible(false);
    label->setText(ui->lineEdit->text());
    emit this->valueEntered(ui->lineEdit->text());
}
/*!
 * \brief Sets the text that will be displayed by the label and it avaible for
 * editing by the line text edit.
 *
 * There is a maximum of 20 characters that can be displayed at any time, but
 * no checks are done before display. Make sure the calling function confirms
 * the length before sending it.
 */
void NameEditArea::valueChanged(QString newValue)
{
    label->setText(newValue);
    ui->lineEdit->setText(newValue);
}
