#include "About.h"

About::About(QWidget *parent) : QDialog(parent)
{   
    QFont font;
    QPalette pal = palette();
    QPixmap pixmap(":/Icon/info.png");
    QIcon icon(pixmap);

    addLog("Affichage de à propos");

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setModal(true);
    setMaximumSize(200,100);
    setMinimumSize(200,100);
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    setWindowTitle("A propos");
    setWindowIcon(icon);

    m_qvnVersion = QVersionNumber(1, 5, 1);

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
