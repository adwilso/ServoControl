#include "editarea.h"
#include "ui_editarea.h"

EditArea::EditArea(QWidget *parent,int index) :
    QFrame(parent),
    ui(new Ui::EditArea),
    m_index(index)
{
    ui->setupUi(this);
    label = new ClickLabel(this);
    label->resize(21,19);
    label->move(1,1);
    label->setVisible(true);
    label->setAlignment(Qt::AlignCenter);
    ui->lineEdit->setVisible(false);

    ValueValidator* v = new ValueValidator(ui->lineEdit);
    ui->lineEdit->setValidator(v);

    connect(label, SIGNAL(clicked()),SLOT(labelClicked()));
    connect(ui->lineEdit,SIGNAL(editingFinished()),SLOT(editFinished()));
    label->setText("49");

    this->setFocusPolicy(Qt::StrongFocus);
}

EditArea::~EditArea()
{
    delete ui;
}
int EditArea::getValue()
{
   return this->label->text().toInt();
}

void EditArea::valueChanged(int newValue)
{
    if (newValue < 1 || newValue > 97)
    {
        return;
    }
    ui->lineEdit->setText(QString("%1").arg(newValue));
    label->setText(QString("%1").arg(newValue));
}
void EditArea::focusShifted(int index)
{
    if (index == this->m_index)
    {
        if (label->isVisible())
        {
            this->labelClicked();
        }
        return;
    }
    if (label->isVisible())
    {
        return; //Nothing to do here.
    }
    int t(0);
    QString string = ui->lineEdit->text();
    if (QValidator::Acceptable == ui->lineEdit->validator()->validate(string,t))
    {
        this->editFinished();
        return;
    }
    else
    {
        label->setVisible(true);
        ui->lineEdit->setVisible(false);
        ui->lineEdit->setText(label->text());
    }

}

void EditArea::labelClicked()
{
    ui->lineEdit->setVisible(true);
    label->setVisible(false);
    ui->lineEdit->setText(label->text());
    ui->lineEdit->setFocus();
    emit this->gotFocus(m_index);
}
void EditArea::editFinished()
{
    label->setVisible(true);
    ui->lineEdit->setVisible(false);
    label->setText(ui->lineEdit->text());
    emit this->valueEntered(ui->lineEdit->text().toInt(),m_index);
}

