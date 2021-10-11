#include "WorkerManager.h"

WorkerManager::WorkerManager() :m_empNum(0), m_empArray(NULL), m_fileIsEmpty(false)
{
    // 构造时加载本地数据
    ifstream ifs;
    // 打开文件
    ifs.open(FILENAME, ios::in);

    // 检查文件是否存在
    if (!ifs.is_open())
    {
        cout << FILENAME << "文件不存在" << endl;
        // 初始化成员属性
        this->m_empNum = 0;
        this->m_empArray = NULL;
        this->m_fileIsEmpty = true;
        // 关闭文件
        /*ifs.close();
        return;*/
    }
    else // 文件存在
    {
        char ch;
        ifs >> ch;
        if (ifs.eof())	// 检查是否到文件结尾，如果到文件结尾，则文件为空
        {
            cout << FILENAME << "文件存在，但无内容。" << endl;
            // 初始化成员属性
            this->m_empNum = 0;
            this->m_empArray = NULL;
            this->m_fileIsEmpty = true;
            // 关闭文件
            /*ifs.close();
            return;*/
        }
        else // 文件存在且不为空
        {
            cout << FILENAME << "文件存在，且不为空。" << endl;
            // 初始化成员属性
            this->m_empNum = getLocalEmpNum();
            this->m_empArray = new Worker*[this->m_empNum];
            initEmpInfoFromLocal();
        }
    }

    // 关闭文件
    ifs.close();
    cout << "[info] WorkerManager类构造" << endl;
}

WorkerManager::~WorkerManager()
{
    // 需要先释放二级指针
    if (this->m_empArray != NULL)
    {
        // 释放二级指针
        for (int i = 0; i < this->m_empNum; i++)
        {
            delete this->m_empArray[i];
            this->m_empArray[i] = NULL;
        }
        // 释放一级指针
        delete[] this->m_empArray;
        this->m_empArray = NULL;
    }
    cout << "[info] WorkerManager类析构" << endl;
}

// 获取职工数量
int WorkerManager::getEmpNum()
{
    return this->m_empNum;
}

bool WorkerManager::getFileIsEmptyFlag()
{
    return this->m_fileIsEmpty;
}

// 展示菜单
void WorkerManager::Show_Menu()
{
    cout << "******************************************" << endl;
    cout << "********** 欢迎使用职工管理系统 **********" << endl;
    cout << "************* 0.退出管理程序 *************" << endl;
    cout << "************* 1.增加职工信息 *************" << endl;
    cout << "************* 2.显示职工信息 *************" << endl;
    cout << "************* 3.删除职工信息 *************" << endl;
    cout << "************* 4.修改职工信息 *************" << endl;
    cout << "************* 5.查找职工信息 *************" << endl;
    cout << "************* 6.按照编号排序 *************" << endl;
    cout << "************* 7.清空所有文档 *************" << endl;
    cout << "******************************************" << endl;

    // 获取职工数量
    cout << "当前在职员工数量为：" << this->getEmpNum() << endl;

    // 获取文件状态
    cout << "文件是否存在信息：" << this->getFileIsEmptyFlag() << endl;

    cout << endl;
}

void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用。" << endl;
    system("pause");
    exit(0);
}

// 添加职工
void WorkerManager::addEmp()
{
    cout << "请输入添加职工数量：" << endl;
    int addNum = 0;
    cin >> addNum;

    if (addNum > 0)	// 添加
    {
        // 计算新空间大小
        int newSize = this->m_empNum + addNum;

        // 开辟新空间
        Worker** newEmpArray = new Worker*[newSize];

        // 保存原有数据
        if (this->m_empArray != NULL)
        {
            for (int i = 0; i < m_empNum; i++)
            {
                newEmpArray[i] = this->m_empArray[i];
            }
        }

        // 添加新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;		// 职工ID
            string name;	// 职工姓名
            int departId;	// 部门id

            while (true)
            {
                cout << "请输入第（" << i + 1 << ")个新职工的员工编号：" << endl;
                cin >> id;

                if (isEmpExist(id) == -1)
                {
                    break;
                }
                else
                {
                    cout << "该职工编号已存在，请重新输入。" << endl;
                }
            }

            cout << "请输入第（" << i + 1 << ")个新职工的员工姓名：" << endl;
            cin >> name;
            cout << "请选择第（" << i + 1 << ")个新职工的岗位："
                << "\n1.普通员工"
                << "\n2.经理"
                << "\n3.老板" << endl;
            cin >> departId;

            // 实例化新职工
            Worker *worker = NULL;
            switch (departId)
            {
            case 1:	// 普通员工
                worker = new Employee(id, name, departId);
                break;
            case 2:	// 经理
                worker = new Manager(id, name, departId);
                break;
            case 3:	// 老板
                worker = new Boss(id, name, departId);
                break;
            default:
                cout << "输入错误，请重试。";
                break;
            }

            // 将新职工保存到新数组中
            newEmpArray[this->m_empNum + i] = worker;
            // 更新文件不为空的标志
            this->m_fileIsEmpty = false;
        }

        // 释放原有空间
        delete[] this->m_empArray;

        // 更改原有空间指向
        this->m_empArray = newEmpArray;

        // 更新职工人数
        this->m_empNum = newSize;

        // 保存数据到本地
        this->save();

        // 提示
        cout << "成功添加 " << addNum << " 名新职工" << endl;
    }
    else
    {
        cout << "输入错误，请重试。" << endl;
    }

    system("pause");
    system("cls");
}

// 保存职工信息到本地
void WorkerManager::save()
{
    ofstream ofs;
    // 打开文件
    ofs.open(FILENAME, ios::out);

    // 写入文件
    for (int i = 0; i < m_empNum; i++)
    {
        ofs << this->m_empArray[i]->m_Id << " "
            << this->m_empArray[i]->m_name << " "
            << this->m_empArray[i]->m_departId << " " << endl;
    }

    // 关闭文件
    ofs.close();
}

// 从本地文件种获取职工人数
int WorkerManager::getLocalEmpNum()
{
    // 检查文件是否为空
    if (this->m_fileIsEmpty == true)
    {
        return 0;
    }

    // 文件不为空时读取
    int empNum = 0;	// 计数器
    int id;	// 职工编号
    string name;	// 职工姓名
    int departId;	// 职工岗位

    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    while (ifs >> id && ifs >> name && ifs >> departId)	// 按空格分隔
    {
        empNum++;
    }

    return empNum;
}

void WorkerManager::initEmpInfoFromLocal()
{
    // 读取文件
    ifstream ifs;
    // 打开文件
    ifs.open(FILENAME, ios::in);

    int index = 0;	// 计数器
    int id;	// 职工ID
    string name;	// 职工姓名
    int departId;	// 职工岗位ID

    // 读取文件，按空格分割元素
    while (ifs >> id && ifs >> name && ifs >> departId)
    {
        Worker *worker = NULL;
        // 选择分支
        switch (departId)
        {
        case 1:	// 普通员工
            worker = new Employee(id, name, departId);
            break;
        case 2:	// 经理
            worker = new Manager(id, name, departId);
            break;
        case 3:	// 老板
            worker = new Boss(id, name, departId);
            break;
        default:
            break;
        }

        // 更新到数组中
        this->m_empArray[index] = worker;
        index++;
    }

    // 关闭文件
    ifs.close();
}

// 显示员工信息
void WorkerManager::showEmpInfo()
{
    // 检查是否为空
    if (this->m_fileIsEmpty)
    {
        cout << "不存在职工信息" << endl;
    }
    else
    {
        for (int i = 0; i < this->m_empNum; i++)
        {
            this->m_empArray[i]->showInfo();
        }
    }

    system("pause");
    system("cls");
}

// 删除职工信息
void WorkerManager::delEmpInfo()
{
    if (this->m_fileIsEmpty)
    {
        cout << "不存在职工信息" << endl;
    }
    else
    {
        // 按照编号删除职工
        cout << "请输入需要删除职工的编号：" << endl;
        int id = -1;	// 待删除职工id
        cin >> id;		// 接收输入
        int index = this->isEmpExist(id);	// 获取员工编号
        if (index != -1)
        {
            cout << "编号为 " << id << " 的职工信息将删除" << endl;
            this->m_empArray[index]->showInfo();
            // 更新信息
            this->m_empNum--;
            for (int i = index; i < this->m_empNum; i++)
            {
                this->m_empArray[i] = this->m_empArray[i + 1];
            }
            // 更新到本地
            this->save();
            // 检查员工数量
            if (this->m_empNum == 0)
            {
                this->m_fileIsEmpty = true;
            }

            // 提示
            cout << "删除成功！" << endl;
        }
        else
        {
            cout << "未找到编号为 " << id << " 的职工信息" << endl;
        }
    }

    system("pause");
    system("cls");
}

int WorkerManager::isEmpExist(int id)
{
    int index = -1;
    // 检查是否存在职工信息
    if (this->m_fileIsEmpty)
    {
        cout << "不存在职工信息" << endl;
        return index;
    }

    for (int i = 0; i < this->m_empNum; i++)
    {
        if (this->m_empArray[i]->m_Id == id)
        {
            index = i;
            break;
        }
    }

    return index;
}

// 按姓名查找
int WorkerManager::isEmpExist(string name, vector<int>& dstIndex)
{
    bool flag = false;
    int index = -1;
    // 检查是否存在职工信息
    if (this->m_fileIsEmpty)
    {
        cout << "不存在职工信息" << endl;
        return index;
    }

    for (int i = 0; i < this->m_empNum; i++)
    {
        if (this->m_empArray[i]->m_name == name)
        {
            dstIndex.push_back(i);
            flag = true;
        }
    }

    // 检查是否查找到
    if (flag)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

// 修改职工信息
void WorkerManager::modEmpInfo()
{
    if (this->m_fileIsEmpty)
    {
        cout << "不存在职工信息" << endl;
    }
    else
    {
        // 按照编号修改员工信息
        cout << "请输入需要修改职工的编号：" << endl;
        int id = -1;	// 待修改职工id
        cin >> id;		// 接收输入

        int index = this->isEmpExist(id);
        if (index != -1)
        {
            // 正确找到员工编号
            // 清除原始信息
            delete this->m_empArray[index];

            int newId;
            string newName;
            int newDepartId;
            while (true)
            {
                cout << "查到：" << id << " 职工，请输入职工新编号：" << endl;
                cin >> newId;
                // 检查id是否重复
                if (this->isEmpExist(newId) == -1)
                {
                    break;
                }
                else
                {
                    cout << "该职工编号已存在，请重新输入。" << endl;
                }
            }

            cout << "请输入职工姓名：" << endl;
            cin >> newName;

            cout << "请选择职工的岗位："
                << "\n1.普通员工"
                << "\n2.经理"
                << "\n3.老板" << endl;
            cin >> newDepartId;

            Worker * worker = NULL;
            // 选择分支
            switch (newDepartId)
            {
            case 1:	// 普通职工
                worker = new Employee(newId, newName, newDepartId);
                break;
            case 2:	// 经理
                worker = new Manager(newId, newName, newDepartId);
                break;
            case 3:	// 老板
                worker = new Boss(newId, newName, newDepartId);
                break;
            default:
                break;
            }
            // 更新数据到数组中
            this->m_empArray[index] = worker;

            // 更新到文件
            this->save();

            // 提示
            cout << "修改成功！" << endl;
        }
        else
        {
            // 查无此人
            cout << "未找到编号为 " << id << " 的职工信息，修改失败" << endl;
        }
    }

    system("pause");
    system("cls");
}

// 查找员工信息
void WorkerManager::findEmpInfo()
{
    // 检查是否存在职工信息
    if (this->m_fileIsEmpty)
    {
        cout << "不存在职工信息" << endl;
    }
    else
    {
        // 查找方式
        int findType = -1;
        while (true)
        {
            cout << "请选择查找方式：\n"
                << "1.按编号查找\n"
                << "2.按姓名查找" << endl;
            cin >> findType;

            if (findType == 1 || findType == 2)
            {
                break;
            }
            else
            {
                cout << "查找方式选择错误，请重新选择查找方式。" << endl;
            }
        }

        // 分支选择
        switch (findType)
        {
        case 1:	// 按编号查找
        {
            cout << "请输入需查找职工编号：" << endl;
            int id = -1;
            cin >> id;

            int index = this->isEmpExist(id);
            if (index != -1)
            {
                this->m_empArray[index]->showInfo();
            }
            else
            {
                cout << "未找到编号为 " << id << " 的职工信息" << endl;
            }

            break;
        }
        case 2:
        {
            cout << "请输入需查找职工姓名：" << endl;
            string name;
            cin >> name;

            vector<int> result;
            int ret = isEmpExist(name, result);
            if (ret != -1)
            {
                for (auto it = result.begin(); it != result.end(); it++)
                {
                    this->m_empArray[*it]->showInfo();
                }
            }
            else
            {
                cout << "未找到姓名为 " << name << " 的职工信息" << endl;
            }
        }
        default:
            break;
        }
    }

    system("pause");
    system("cls");
}

// 排序员工信息
void WorkerManager::sortEmpInfo()
{
    // 检查是否存在职工信息
    if (this->m_fileIsEmpty)
    {
        cout << "不存在职工信息" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        int sortType = -1;
        while (true)
        {
            cout << "请选择排序方式：\n"
                << "1.升序\n"
                << "2.降序" << endl;
            cin >> sortType;
            if (sortType == 1 || sortType == 2)
            {
                break;
            }
            else
            {
                cout << "排序方式选择错误，请重新输入" << endl;
            }
        }

        // 利用选择排序算法进行排序
        for (int i = 0; i < m_empNum; i++)
        {
            // 选则最大值或最小值
            int minOrMax = i;
            for (int j = i + 1; j < m_empNum; j++)
            {
                if (sortType == 1)	// 升序
                {
                    if (this->m_empArray[minOrMax]->m_Id > this->m_empArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else // 降序
                {
                    if (this->m_empArray[minOrMax]->m_Id < this->m_empArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                if (i != minOrMax)
                {
                    Worker *temp = this->m_empArray[i];
                    this->m_empArray[i] = this->m_empArray[minOrMax];
                    this->m_empArray[minOrMax] = temp;
                }
            }
        }

        // 更新结果到本地
        this->save();

        // 显示排序结果
        this->showEmpInfo();
    }
}

// 清空所有信息
void WorkerManager::claenAllInfo()
{
    cout << "确认清空所有职工信息？\n"
        << "0.取消"
        << "1.确认" << endl;
    bool confirm = false;
    cin >> confirm;

    if (confirm)
    {
        // 删除原文件并新建
        ofstream ofs;
        ofs.open(FILENAME, ios::trunc);
        ofs.close();

        // 释放内存空间
        if (this->m_empArray != NULL)
        {
            // 清理二级指针
            for (int i = 0; i < this->m_empNum; i++)
            {
                if (this->m_empArray[i] != NULL)
                {
                    delete this->m_empArray[i];
                    this->m_empArray[i] = NULL;
                }
            }
            // 更新计数器
            this->m_empNum = 0;
            // 清理一级指针
            delete[] this->m_empArray;
            this->m_empArray = NULL;
            this->m_fileIsEmpty = true;
        }

        // 提示
        cout << "数据清理成功！" << endl;
    }
    else
    {
        cout << "操作已取消！" << endl;
    }

    system("pause");
    system("cls");
}
