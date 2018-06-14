#include "settingsView.h"

SettingsView::SettingsView(QWidget *parent) : QDialog(parent)
{   
    QFont font;
    QPalette pal = palette();
    QPixmap pixmap(":/Icon/settings.png");
    QIcon icon(pixmap);

    setModal(true);
    setMaximumSize(300,500);
    setMinimumSize(300,500);
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    setWindowTitle("Settings");
    setWindowIcon(icon);

    m_qvblMainLayout = new QVBoxLayout(this);
    m_qvblMainLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(m_qvblMainLayout);

    show();
}
