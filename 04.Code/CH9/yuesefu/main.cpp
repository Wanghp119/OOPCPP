#include <iostream>
#include <deque>
using namespace std;
int findLast(int n, int k, int m) //���庯������������int���βΣ�������int�ͣ�ʵ�ֵĹ������ҵ������е���һ����
{
    deque<int> ideq; //����deque�����������kΪ�׵�n��Ԫ��
    for (int x = k; x != n + 1; ++x)
    {
        ideq.push_back(x);
    }
    for (int y = 1; y != k; ++y)
    {
        ideq.push_back(y);
    }
    deque<int>::iterator iter = ideq.begin(); //���������
    while (ideq.size() != 1)//һֱѭ����ֱ������ֻʣ��һ��Ԫ��Ϊֹ
    {
        for (int cnt = 1; cnt != m; ++cnt)//ѭ����m-1����
        {
            ideq.push_back(*iter); //��β����ӵ�ǰ��������ָ���Ԫ��
            iter = ideq.erase(iter); //ɾ����ǰλ�õ�Ԫ�أ����صĵ�����ָ����һλ��
        }
        iter = ideq.erase(iter); // �˴���Ϊ����m����ֱ�ӳ���
    }
    return *iter; //����ʣ�µ����һ��Ԫ��
}
int main()
{
    cout << "The last person:" << endl;
    cout << findLast(9, 1, 5) << endl;
    return 0;
}
