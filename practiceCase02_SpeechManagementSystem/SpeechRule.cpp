#include "SpeechRule.h"

SpeechRule::SpeechRule()
{
}

SpeechRule::~SpeechRule()
{
}

void SpeechRule::setRule()
{
    Rule::RuleErrorType ret = Rule::RULE_OK;
    do
    {
        cout << "\n------------- ������������ -------------\n"
            << "ԭ��\n"
            << "1. (��ѡ������ / ��ѡ������) - ��ѡÿ��������� > 1\n"
            << "2. (��ѡÿ��������� * ��ѡ������) % ���������� = 0\n"
            << "3. ���������� * ����ÿ��������� > 3" << endl;
        cout << ">>�����뺣ѡ��������";
        cin >> this->m_auditionNum;
        cout << ">>�����뺣ѡ��������";
        cin >> this->m_auditionGrpNum;
        cout << ">>�����뺣ѡÿ�����������";
        cin >> this->m_auditionNextNum;
        this->m_semi_finalsNum = this->m_auditionGrpNum * this->m_auditionNextNum;
        cout << ">>�����븴����������";
        cin >> this->m_sfGrpNum;
        cout << ">>�����븴��ÿ�����������";
        cin >> this->m_sfNextNum;
        this->m_finalsNum = this->m_sfGrpNum * this->m_sfNextNum;
        ret = checkRule();
        while (ret == Rule::RULE_SF_CANT_AVG)
        {
            cout << ">>�����븴����������";
            cin >> this->m_sfGrpNum;
            cout << ">>�����븴��ÿ�����������";
            cin >> this->m_sfNextNum;
            this->m_finalsNum = this->m_sfGrpNum * this->m_sfNextNum;
            ret = checkRule();
        }
    } while (Rule::RULE_OK != ret);
    showRules();

    system("pause");
}

void SpeechRule::showRules()
{
    cout << "\n------------- �������� -------------\n"
        << "|=��ѡ=                            |\n"
        << "|  ����������: \t\t" << this->m_auditionNum << "\t ��|\n"
        << "|  ����������: \t\t" << this->m_auditionGrpNum << "\t ��|\n"
        << "|  ÿ���������: \t" << this->m_auditionNextNum << "\t ��|\n"
        << "|=����=                            |\n"
        << "|  ����������: \t\t" << this->m_semi_finalsNum << "\t ��|\n"
        << "|  ����������: \t\t" << this->m_sfGrpNum << "\t ��|\n"
        << "|  ÿ���������: \t" << this->m_sfNextNum << "\t ��|\n"
        << "|=����=                            |\n"
        << "|  ����������: \t\t" << this->m_finalsNum << "\t ��|\n"
        << "|  �ھ����Ǿ���������\t1\t ��|\n"
        << "------------------------------------" << endl;
}

void SpeechRule::saveRule()
{
}

Rule::RuleErrorType SpeechRule::checkRule()
{
    if (this->m_auditionGrpNum <= 0 ||
        this->m_auditionNextNum <= 0 ||
        this->m_auditionNum <= 0)
    {
        cout << "����������������\n"
            << "��ѡ����������ѡ��������ѡÿ���������С�ڵ���0��" << endl;
        return Rule::RULE_ZERO_NUMBER;
    }
    else if (this->m_auditionNum <= ((this->m_auditionNextNum + 1) * this->m_auditionGrpNum))
    {
        cout << "����������������\n"
            << "��ѡ���������٣����������ͽ���ԭ��(������ / ������) - ÿ��������� > 1��" << endl;
        return Rule::RULE_TOTAL_LESS;
    }
    else
    {
        // ��ѡ���Ϲ��򣬽��и���������
        if (this->m_sfGrpNum <=0 ||
            this->m_sfNextNum <=0)
        {
            cout << "����������������\n"
                << "��������������ÿ���������С�ڵ���0��" << endl;
            return Rule::RULE_ZERO_NUMBER;
        }
        else if(((this->m_auditionNextNum * this->m_auditionGrpNum) % this->m_sfGrpNum) != 0)
        {
            map<int, int> commonDivisor;
            this->getCommonDivisor(this->m_semi_finalsNum, commonDivisor);
            cout << "���󣡸��������޷����ȷ��飡\n"
                << "�Ƽ�������Ϊ��\n������\tÿ������\n";
            for (auto it = commonDivisor.begin(); it != commonDivisor.end(); it++)
            {
                cout << it->first << "\t" << it->second << endl;
            }
            return Rule::RULE_SF_CANT_AVG;
        }
        else if ((this->m_sfGrpNum * this->m_sfNextNum) <= 3)
        {

        }
        return Rule::RULE_OK;
    }
    return Rule::RULE_OK;
}

void SpeechRule::getCommonDivisor(const int &src, map<int, int>& dst)
{
    dst.clear();
    for (int i = 1; i * i <= src; i++)
    {
        if (src % i == 0)
        {
            int value = src / i;
            dst.insert(pair<int, int>(i, value));
            if (i *i != src)
            {
                value = i;
                dst.insert(pair<int, int>(src / i, value));
            }
        }
    }
}
