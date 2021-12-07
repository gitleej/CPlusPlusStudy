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
        ret = checkRule(0);
        while (ret == Rule::RULE_SF_CANT_AVG || ret == Rule::RULE_TOTAL_LESS || ret == Rule::RULE_ZERO_NUMBER) {
            cout << ">>�����뺣ѡ��������";
            cin >> this->m_auditionNum;
            cout << ">>�����뺣ѡ��������";
            cin >> this->m_auditionGrpNum;
            cout << ">>�����뺣ѡÿ�����������";
            cin >> this->m_auditionNextNum;
            ret = checkRule(0);
        }
        this->m_semi_finalsNum = this->m_auditionGrpNum * this->m_auditionNextNum;
        cout << ">>�����븴����������";
        cin >> this->m_sfGrpNum;
        cout << ">>�����븴��ÿ�����������";
        cin >> this->m_sfNextNum;
        this->m_finalsNum = this->m_sfGrpNum * this->m_sfNextNum;
        ret = checkRule(1);
        while (ret == Rule::RULE_SF_CANT_AVG || ret == Rule::RULE_SF_LESS_FINAL)
        {
            cout << ">>�����븴����������";
            cin >> this->m_sfGrpNum;
            cout << ">>�����븴��ÿ�����������";
            cin >> this->m_sfNextNum;
            this->m_finalsNum = this->m_sfGrpNum * this->m_sfNextNum;
            ret = checkRule(1);
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

void SpeechRule::saveRule(string filename)
{
    string filepath = "./data/rules/" + filename + ".csv";

    ofstream ofs;
    ofs.open(filepath.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        cout << "�����󡿣��ļ������ڡ�" << filepath << endl;
        return;
    }

    ofs << this->m_auditionNum << "," << this->m_auditionGrpNum << ","
        << this->m_auditionNextNum << endl;
    ofs << this->m_semi_finalsNum << "," << this->m_sfGrpNum << ","
        << this->m_sfNextNum << endl;
    ofs << this->m_finalsNum << endl;

    ofs.close();
}

void SpeechRule::loadRule(string filename) {
    string filepath = "./data/rules/" + filename + ".csv";

    ifstream ifs;
    ifs.open(filepath.c_str(), std::ios::in);
    if (!ifs.is_open()) {
        cout << "�����󡿣��ļ������ڡ�" << filepath << endl;
        return;
    }

    string line;
    vector<string> tempStrSplitResult;
    getline(ifs, line);
    tempStrSplitResult = Utils::Utils::strSplit(line, ',');
    this->m_auditionNum = stoi(tempStrSplitResult[0]);
    this->m_auditionGrpNum = stoi(tempStrSplitResult[1]);
    this->m_auditionNextNum = stoi(tempStrSplitResult[2]);
    getline(ifs, line);
    tempStrSplitResult = Utils::Utils::strSplit(line, ',');
    this->m_semi_finalsNum = stoi(tempStrSplitResult[0]);
    this->m_sfGrpNum = stoi(tempStrSplitResult[1]);
    this->m_sfNextNum = stoi(tempStrSplitResult[2]);
    getline(ifs, line);
    tempStrSplitResult = Utils::Utils::strSplit(line, ',');
    this->m_finalsNum = stoi(tempStrSplitResult[0]);

    ifs.close();
}

Rule::RuleErrorType SpeechRule::checkRule(int level)
{
    if (this->m_auditionGrpNum <= 0 ||
        this->m_auditionNextNum <= 0 ||
        this->m_auditionNum <= 0)
    {
        cout << "����������������\n"
            << "��ѡ����������ѡ��������ѡÿ���������С�ڵ���0��" << endl;
        return Rule::RULE_ZERO_NUMBER;
    } 
    else if (this->m_auditionNum % this->m_auditionGrpNum != 0) {
        cout << "����������������\n"
             << "��ѡ�����޷����֣������ԣ�" << endl;
        return Rule::RULE_SF_CANT_AVG;
    }
    else if (this->m_auditionNum <= ((this->m_auditionNextNum + 1) * this->m_auditionGrpNum))
    {
        cout << "����������������\n"
            << "��ѡ���������٣����������ͽ���ԭ��(������ / ������) - ÿ��������� > 1��" << endl;
        return Rule::RULE_TOTAL_LESS;
    }
    else if(level == 1)
    {
        // ��ѡ���Ϲ��򣬽��и���������
        map<int, int> commonDivisor;
        if (this->m_sfGrpNum <=0 ||
            this->m_sfNextNum <=0)
        {
            cout << "����������������\n"
                << "��������������ÿ���������С�ڵ���0��" << endl;
            return Rule::RULE_ZERO_NUMBER;
        }
        else if(((this->m_auditionNextNum * this->m_auditionGrpNum) % this->m_sfGrpNum) != 0)
        {
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
            this->getCommonDivisor(this->m_semi_finalsNum, commonDivisor);
            cout << "���󣡸�����������С�ڵ���3�ˣ����������ø������鷽����\n"
                 << "�Ƽ�������Ϊ��\n������\tÿ������\n";
            for (auto it = commonDivisor.begin(); it != commonDivisor.end(); it++)
            {
                cout << it->first << "\t" << it->second << endl;
            }
            return Rule::RULE_SF_LESS_FINAL;
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
