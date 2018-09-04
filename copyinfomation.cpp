#include "copyinfomation.h"

CopyInfomation::CopyInfomation(QWidget *parent,QString result) : QDialog(parent)
{
    QFont font;
    QPalette pal = palette();
    QPixmap pixmap(":/Icon/info.png");
    QIcon icon(pixmap);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setModal(true);
    setMaximumSize(450,450);
    setMinimumSize(450,450);
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    setWindowTitle("Informations sur la copie");
    setWindowIcon(icon);

    m_qsResult=result;

    m_qvblMainLayout = new QVBoxLayout();
    this->setLayout(m_qvblMainLayout);

    m_qlTitle = new QLabel(m_qsResult.isEmpty()?"Tous les fichiers sont copiés":"Erreur",this);
    m_qlTitle->setAlignment(Qt::AlignCenter);
    font = m_qlTitle->font();
    font.setPointSize(10);
    font.setBold(true);
    m_qlTitle->setFont(font);
    m_qvblMainLayout->addWidget(m_qlTitle);

    if (!m_qsResult.isEmpty())
    {
        m_qteDetail = new QTextEdit(this);
        m_qteDetail->setPlainText(m_qsResult);
        boldSrcDest();
        m_qvblMainLayout->addWidget(m_qteDetail);
        m_qteDetail->setReadOnly(true);
    }

    m_qhblButtonsLayout = new QHBoxLayout();
    m_qvblMainLayout->addLayout(m_qhblButtonsLayout);

    m_qpbExit= new QPushButton("Quitter",this);
    m_qhblButtonsLayout->addWidget(m_qpbExit,0,Qt::AlignRight);
    connect(m_qpbExit,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void CopyInfomation::boldSrcDest()
{
    QString textTmp;

    textTmp = m_qteDetail->toHtml();
}
