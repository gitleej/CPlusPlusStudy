/**
 * @file    main.cpp
 * @brief   �ݽ��������̹���ϵͳ
 * @detail  ����ϵͳʱ���ȼ���Ƿ������ڽ��еı���������б�����ѡ����Ҫ��������
            �ı�����ʼ�µı�����
 * @section �������򷢲�
 * -# ��ʼ����ǰ�ƶ��������򣬱�����Ϊ��ѡ�������;�����
 * -# ��ѡ���� > ��ѡ���� X (ÿ��������� + 1)��
 * -# 3 < (�������� X ÿ���������) < �������������ұ���ÿ������һ�£�
 * -# ���������ھ����Ǿ��ͼ�����
 * @section ѡ����Ϣ����
 * -# ѡ����Ϣ���������������䡢���֤�ź���ϵ�绰��
 * -# ���ѡ�ֵ������趨������ֹͣ��ļѡ�֣�
 * -# ֧���˳�ϵͳ��������ļ��
 * -# ֧��ɾ��ѡ����Ϣ��
 * -# ֧���޸�ѡ����Ϣ��
 * -# ֧�ֲ���ѡ����Ϣ�������������䡢���֤�ź���ϵ�绰���ң�
 * @section ��ʼ����
 * -# ѡ�������ǩ������飻
 * -# ������б�������10����ί��֣�ȥ��һ����߷ֺ�һ����ͷ֣���ƽ����Ϊ���յ÷֣�
 * -# ��Ӧ��������������
 * -# ÿ�ֱ�������ʾÿ�����ѡ����Ϣ��
 * -# ֧��������
 * -# ֧����;ͣ����
 * @section �鿴���������¼
 * -# �鿴���м�¼��
 * -# �鿴��ѡ��¼��
 * -# �鿴������¼��
 * -# �鿴������¼��
 * @section ��ձ�����¼
 * -# �ٴ�ȷ���Ƿ������
 * @section �˳�ϵͳ
 */
#include "SpeechManager.h"

#include <iostream>
#include <algorithm>
#include <ctime>

int main(int argc, char **argv)
{
    // �����������
    srand((unsigned int)time(NULL));

    // ��������ʵ��
    SpeechManager sm;
    // �˵�ѡ���־
    int choise = -1;
    
    while (true)
    {
        // ����Ƿ���δ��ɵı������������ʾδ��ɵı��������û�У���ʾ��ʼ�±����Ĳ˵�
        if (sm.m_unfinishedContests.size() != 0) {
            cout << "�����ѡ�����ǰ��һ��Ϊ��ɵı�����" << endl;
            sm.coutHistoryRecord(sm.m_unfinishedContests);
            sm.showMenu(CONTINUE_MENU);
            // ���ܲ˵�����
            cout << "����������ѡ��" << endl;
            cin >> choise;
            if (choise == 0) {
                sm.exitSystem();
                break;
            } else if (choise == 1) {
                sm.startNewContest();
            }else if(choise == 2) {
                sm.continueContest();
            }
        }

    }
    system("pause");
    return 0;
}