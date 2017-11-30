#ifndef _TEXT_QUERY_H_
#define _TEXT_QUERY_H_

#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream>

//////////////////////////////////////////////////////////////////////////
// class TextQuery														//
//////////////////////////////////////////////////////////////////////////
class TextQuery
{
public:
	typedef std::vector<std::string>::size_type	line_no;	//�������ͱ���

	void read_file(std::ifstream &is){		//���ı��ļ����ݣ���������->�к�map
		store_file(is);	make_map();
	}

	std::set<line_no>	run_query(const std::string& ) const;	//ִ�в�ѯ�������к��б�
	std::string	text_line(line_no) const;	//�����кţ����ظ�������

private:
	void store_file(std::ifstream&);	//���ļ�����
	void make_map();					//��������->�к�map

	std::vector<std::string>	lines_of_text;			//�ı����ݣ����д�ţ�
	std::map< std::string, std::set<line_no> > word_map;//����->�к��б� map
};

// �����ѯ����Ľӿ�
void print_results(const std::set<TextQuery::line_no>& locs, const std::string& sought, const TextQuery& file);

#endif	//#ifndef _TEXT_QUERY_H_