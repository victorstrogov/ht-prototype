#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDialog>

namespace Ui {
class MainForm;
}

class MainForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    
private:
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
