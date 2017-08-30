/*
* Copyright (c) 2017,  ����������Ϣ�������޹�˾���һ��
* All rights reserved.
*
* �ļ����ƣ�QueryHandle.h
* �ļ���ʶ��
* ժ Ҫ����ѯ����ģ���ͷ�ļ�
*
* ��ǰ�汾��1.0
* �� �ߣ��
* ������ڣ�2017��08��30��
*
*/


#ifndef QUERYHANDLE_H
#define QUERYHANDLE_H
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

typedef struct
{
    char inquire_kind; //��ѯ���� 0����H264�����������չ��
    char inquire_type;//��ѯ�������� 0-��ѯ�����Ƿ���ڣ�1-����֡ͷ����
    string inquire_data; //Ҫ��ѯ�����ݺͷ��صĽ�������ڽ���ģ����������ѯ���264��ѯģ�����������ҽ��
}InquireInterface;

class QueryHandle
{
public:
    QueryHandle();
    ~QueryHandle();
    void handle_msg();

private:
    //char *rev_msg; //���ڽ���CSģ�鷢�͵���Ϣ
    //string send_msg; //���ڸ�CS������Ϣ
   // UdsClient *uds_client; //��CSͨ�Ž���ͨ�ŵ���
    void print_queryby_ari_time();
    void print_input_ari_time();
    void print_input_time();
    void print_input_moment();

    int find_char(string &input, char fchar);  //����ĳ���ַ����У�����fchar�ĸ���
    int check_input_1(string &input, int type);  //��ѯ�Ƿ������Ƶ����ʱ���ж��û������Ƿ���ȷ,��ȷ����0
    int check_input_2(string &input);  //��ѯ��Ƶ֡ͷʱ���ж��û������Ƿ���ȷ����ȷ����0
    void print_result(string &input, int print_type); //�����û��������ѯ��ʽ����ӡ���صĲ�ѯ���
    void split_string(string &input);


    InquireInterface inquireInterface;

    int input_type; //�����ж��û��������ѯ��ʽ
    vector<string> result_buf;

};

#endif // QUERYHANDLE_H
