#include <iostream>
#include "QueryObj.h"

using namespace std;

// ��������use-case ����
//�ı���ѯ
//1.���ļ�
//2.������
//3.Query.

//
int main()
{
    //1. open file
    string  strFilePath;
    cin >> strFilePath;

    ifstream    ifs;
    ifs.open(strFilePath.c_str());

    QueryObj    qo;
    // 2. Read File
    try
    {
        //1. load_file;
        if (!qo.load_file(ifs))
        {
            throw 1;
        }
        ifs.close();
    }
    catch(...)
    {
        ifs.close();
        cerr << "Read File Failed.";
    }

    //2. query
    string  strWord("");
    cin >> strWord;
    do
    {
        set<QueryObj::line_no>  setLines;
        setLines = qo.query(strWord);

        set<QueryObj::line_no>::iterator    iter;
        for (iter=setLines.begin(); iter!=setLines.end(); ++iter)
        {
            cout << *iter << "\t";
        }
        cout << endl;
    }
    while(strWord!="!q");

    return 0;
}
