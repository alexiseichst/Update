#include "About.h"

About::About(QWidget *parent) : QDialog(parent)
{   
    QFont font;
    QPalette pal = palette();

    setModal(true);
    setMaximumSize(200,100);
    setMinimumSize(200,100);
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    setWindowTitle("About");

    m_qvnVersion = QVersionNumber(1, 0, 0);

    m_qvblMainLayout = new QVBoxLayout(this);
    m_qvblMainLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(m_qvblMainLayout);

    m_pbLogo = new PushButton(this,":/Icon/server.png",false);
    m_pbLogo->setMinimumSize(50,50);
    m_pbLogo->setIconSize(QSize(50,50));
    m_qvblMainLayout->addWidget(m_pbLogo);

    m_qlVersion = new QLabel("Version "+m_qvnVersion.toString(),this);
    font = m_qlVersion->font();
    font.setPointSize(10);
    font.setBold(true);
    m_qlVersion->setFont(font);
    m_qvblMainLayout->addWidget(m_qlVersion);

    show();
}
