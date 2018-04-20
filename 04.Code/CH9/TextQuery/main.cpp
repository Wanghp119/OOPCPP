#include <iostream>
#include "TextQuery.h"
#include <fstream>

using namespace std;

//==========================================================//
//		Text Query Function:								//
// 1.���ı��ļ������ж�ȡ���ݣ����򱣴��кź�ÿ�е�����	//
// 2.��ÿ�����ݰ����ʷֽ⣬����¼ÿ���������ڵ��к�			//
// 3.���뵥�ʣ��ܲ�ѯ�õ������ڵ������кţ�����������		//
// 4.�����кţ���������õ��������е�����					//
//==========================================================//
int main(int argc, char** argv)
{	
	//�ж���������Ϸ���
	if (argc < 2)
	{
		cerr << "No Input file!" << endl;
		return 1;
	}

	// ���ı��ļ�
	ifstream	ifs;
	ifs.open(argv[1]);
	if (ifs.is_open())
	{
		cerr << "Open File Failed!" << endl;
		return 2;
	}

	// ���ļ����ݣ�����<����-������>��map
	TextQuery	tq;
	tq.read_file(ifs);
	ifs.close();

	// ѭ�������ѯ���ʣ������ѯ���
	while(true)
	{
		// ��ѯ����
		cout << "enter word to look for, or q to quit: ";
		string	str;
		cin >> str;

		// "q" is quit
		if (!cin || str=="!q")
			break;

		// ִ�в�ѯ
		set<TextQuery::line_no> locs = tq.run_query(str);

		//�����ѯ���
		print_results(locs, str, tq);
	}

	return 0;
}