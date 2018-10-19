#include "define.h"

void addLog(QString log)
{
      static int checkSize=0;
      QFile file(LOGFILE);
      QFile oldFile(OLDLOGFILE);

      if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
      {
          QTextStream stream(&file);
          if (!log.isEmpty())
            stream << QDate::currentDate().toString("dd.MM.yyyy") << " " << QTime::currentTime().toString("hh:mm:ss.zzz") << " : " << log << "\n";
          else
            stream << "\n\n";

          checkSize++;
          if (checkSize>=LOGCHECKSIZE)
          {
              int size = file.size();
              if (size>LOGSIZEMAX)
              {
                  if (oldFile.exists())
                      oldFile.remove();
                  file.copy(OLDLOGFILE);
                  file.remove();
              }
              checkSize=0;
          }
          file.close();
      }
      qDebug() << log;
}
