#include "define.h"

bool pingPc(QDir dir)
{
    QString ipHost= "";
    int index=-1;
    bool rt=false;

    ipHost = dir.path();

    if (ipHost.indexOf("//")==0) //Distant
    {
        index=ipHost.indexOf("/",2);
        if (index==-1)
        {
            rt=false; // Erreur dans le chemin
        }
        else
        {
            ipHost = ipHost.mid(2,index-2);
            if (!ipHost.isEmpty())
            {
                QString nParameter = "-n";
                QString pingCount = "1"; //(int)
                QString wParameter = "-w";
                QString pingWaitTime = "10"; //(ms)
                QStringList param;
                QProcess Processping;
                int exitCode=0;

                param<<ipHost<<nParameter<<pingCount<<wParameter<<pingWaitTime;
                exitCode = Processping.execute("ping",param);
                if (exitCode==0)
                {
                    rt=true;
                }
                else
                {
                    rt=false;
                }
            }
            else
            {
                rt=false; // Erreur dans le chemin
            }
        }
    }
    else
    {
        rt=true; // Local
    }
    return rt;
}
