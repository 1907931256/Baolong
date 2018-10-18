#ifndef ALARMDRIVER_H
#define ALARMDRIVER_H

#include "DataCommunication/TcpServer.h"
#include "DataHelper/LogFile.h"
#include "DataHelper/ParseCsv.h"
#include "DataHelper/MySQLHelper.h"

using namespace std;

//class ThreadFxPlc;

class AlarmInfo
{
public:
    string Dispatch_No;                 //�ɹ�����
    string Part_No;                     //����
    string Production_Line;             //��Ʒ��
    string Work_Center_No;              //��������
    string Alarm_Level;                 //�����ȼ�
    string Alarm_Content;               //��������
    string Alarm_Category;              //����Ŀ¼
    string Alarm_Processing_Method;     //������ʽ
    string Enter_User;                  //�û���
    string MCH_Code;                    //�豸����
};

class AlarmDriver
{
public:
    AlarmDriver();
    ~AlarmDriver();

    bool Start();
    bool Stop();
    void threadprocess();
    static void *Start_Thread(void*arg);

    bool saveAlarmInfoToSql(AlarmInfo &ai);         //���뱨�����ݵ����ݿ�
    void initSqlPara(AlarmInfo &ai);                //��ʼ�����ݿ����
    void communicateAlarm(AlarmInfo &comAi);        //�豸ͨ�ű���
    void plcPointAlarm(AlarmInfo &plcAi);           //PLC��λ����
    void tcpServerAlarm();                          //��λ������
    void deviceParaAlarm(AlarmInfo &paraAi);        //�豸��������
    void deviceInitAlarm(AlarmInfo &devAi);         //�豸��ʼ������

    void initPara();
    void initCommPara();                            //��ʼ��ͨ�ű�������
    void initPlcPara();                             //��ʼ��PLC��������
    void initDevicePara();                          //��ʼ���豸��������
    void initDeviceError();                              //��ʼ���豸��ʼ����������

    void checkDevPara(AlarmInfo &paraAi, DeviceInfo &di);
    void checkDevTestPara(AlarmInfo &paraAi, DeviceInfo &di);

private:
    pthread_t pth;
    bool _stop;
    bool alarmFlag;    
    vector<string> m_preConnectStatus;      //��һ���豸ͨ��״̬����
    vector<int> m_prePLcAlarmValue;         //��һ��PLC����������
    int _counter;                           //�豸����
    string m_plcCommOK;                     //�����ָ���
    string m_plcCommERR;                    //������
    int m_startAddress;                     //��ʼ��ַ
    vector<string> m_deviceAlarmName;       //�豸������
    bool m_devFlag;
    bool m_testFlag;
    bool m_initFlag;

};

#endif // ALARMDRIVER_H
