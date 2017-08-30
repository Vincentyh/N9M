#include <iostream>
#include "QueryHandle.h"
#include <cstdlib>
#include <cstring>
#include <vector>

QueryHandle::QueryHandle()
{
    //初始化显示页面
    cout << "*******************************************************\n";
    cout << "*                                                     *\n";
    cout << "* 1. 查询指定通道和时间下是否存在视频数据；           *\n";
    cout << "*                                                     *\n";
    cout << "* 2. 查询某一时刻的帧信息；                           *\n";
    cout << "*                                                     *\n";
    cout << "*******************************************************\n";
    cout << "请输入1或者2选择查询内容：" << endl;

    inquireInterface.inquire_kind = 0;
}

QueryHandle::~QueryHandle()
{

}

void QueryHandle::handle_msg()
{
    string input;
    while(1)
    {
        cin >> input;
        cout << input << endl;
        if("1" == input)
        {
            inquireInterface.inquire_type = 0;
            print_queryby_ari_time();
            cin >> input;
            if("1" == input)
            {
                print_input_ari_time();
                cin >> input;
                while(check_input_1(input,1))
                {
                    cout << "输入格式不正确，请重新输入：" << endl;
                    cin >> input;
                }
                cout << input << endl;
                inquireInterface.inquire_data = input;
                //接下来调用CS发送接口发送inquireInterface
                //用result模拟发送查询命令给CS后，接受到的查询结果信息 x:xx,xx;x:xx,xx;x:xx,xx,xx;x: xx,xx,xx
                print_result(input, 1);
            }
            else if("2" == input)
            {
                cout << "22" << endl;
                print_input_time();
                cin >> input;
                while(check_input_1(input,0))
                {
                    cout << "输入格式不正确，请重新输入：" << endl;
                    cin >> input;
                }
                cout << input << endl;
                inquireInterface.inquire_data = input;
                //接下来调用CS发送接口发送inquireInterface
                //用result模拟发送查询命令给CS后，接受到的查询结果信息 x:xx,xx;x:xx,xx;x:xx,xx,xx;x: xx,xx,xx
                print_result(input, 0);
            }else{
                cout << "输入错误，请重新输入：" << endl;
            }
        }
        else if("2" == input)
        {
            inquireInterface.inquire_type = 1;
            print_input_moment();
            cin >> input;
            while(check_input_2(input))
                
            {
                cout << "输入错误，请重新输入：" << endl;
                cin >> input;
            }
            cout << input << endl;
            print_result(input,1);
        }else{
            cout << "输入错误，请重新输入：" << endl;
        }

    }

}


//根据返回结果，解析并打印出结果，其中print_type为0时检查不带通道格式的查询的返回值，1检查带
//通道格式的查询的返回值
void QueryHandle::print_result(string &input, int print_type)
{
    string result = "0:02,06;2:08,10;";
    //string result = "0:2014/10/12/10:10:12-2014/11/12/09:10:12,2014/10/12/10:10:12-2014/11/12/09:10:12;1:2015/10/12/10:10:12-2014/11/12/09:10:12";
    if(0 == print_type)
    {
        if(0 == input_type)
        {
            cout << input << "年在以下通道和月份存在视频信息：" << endl;
            for(int i =0; i < result.size(); i++)
            {
                if(',' == result[i])
                {
                    cout << result.substr(i-2,2) << "月   ";
                }
                else if(';' == result[i])
                {
                    cout << result.substr(i-2,2) << "月   ";
                    cout << endl;
                }
                else if(':' == result[i])
                {

                    cout << result[i-1] << "通道：";
                }
            }
        }
        else if(1 == input_type)
        {
            char year[10];
            char month[10];
            sscanf((char*)input.c_str(), "%[^/]/%s", year, month);
            cout << year << "年" << month << "月在以下通道和日期存在视频信息" << endl;
            for(int i =0; i < result.size(); i++)
            {
                if(',' == result[i])
                {
                    cout << result.substr(i-2,2) << "日   ";
                }
                else if(';' == result[i])
                {
                    cout << result.substr(i-2,2) << "日   ";
                    cout << endl;
                }
                else if(':' == result[i])
                {
                    cout << result[i-1] << "通道：";
                }
            }
        }
        else if(2 == input_type)
        {
            char year[10];
            char month[10];
            char day[10];
            sscanf((char*)input.c_str(), "%[^/]/%[^/]/%s", year, month,day);
            cout << year << "年" << month << "月" << day << "日在以下通道和小时存在视频信息" << endl;
            for(int i =0; i < result.size(); i++)
            {
                if(',' == result[i])
                {
                    cout << result.substr(i-2,2) << "时   ";
                }
                else if(';' == result[i])
                {
                    cout << result.substr(i-2,2) << "时   ";
                    cout << endl;
                }
                else if(':' == result[i])
                {
                    cout << result[i-1] << "通道：";
                }
            }
        }
        else if(3 == input_type)
        {
//string result = "0:2014/10/12/10:10:12-2014/11/12/09:10:12,2014/10/12/10:10:12-2014/11/12/09:10:12;1:2015/10/12/10:10:12-2014/11/12/09:10:12";
            cout << "时间段" << input << "在以下通道的以下时间段存在视频信息：" << endl;
            for(int i =0; i < result.size(); i++)
            {
                if('-' == result[i])
                {
                    cout << result.substr(i-19,39) << "   ";
                }
                else if(';' == result[i])
                {
                   // cout << result.substr(i-39,39) << "   ";
                    cout << endl;
                }
                else if(':' == result[i])
                {
                    if('/' != result[i-3] && ':' != result[i-3])
                        cout << result[i-1] << "通道：";
                }
            }
        }
    }
    else if(1 == print_type)
    {
        char aisle[10];
        char time[50];
        sscanf((char*)input.c_str(), "%[^:]:%s", aisle, time);
        cout << "aidsle" << aisle << endl;
        cout << "time" << time << endl;
        if(4 == input_type)
        {
       //     cout << result << endl;
            cout << time << "年和" << aisle << "通道在以下月份和通道存在视频信息：" << endl;

            for(int i =0; i < result.size(); i++)
            {
                if(',' == result[i])
                {
                    cout << result.substr(i-2,2) << "月   ";
                }
                else if(';' == result[i])
                {
                    cout << result.substr(i-2,2) << "月   ";
                    cout << endl;
                }
                else if(':' == result[i])
                {

                    cout << result[i-1] << "通道：";
                }
            }
        }
        else if(5 == input_type)
        {
            char year[10];
            char month[10];
            sscanf(time, "%[^/]/%s", year, month);
            cout << year << "年" << month << "月和" << aisle << "通道在以下日期和通道存在视频信息：" << endl;

            for(int i =0; i < result.size(); i++)
            {
                if(',' == result[i])
                {
                    cout << result.substr(i-2,2) << "日   ";
                }
                else if(';' == result[i])
                {
                    cout << result.substr(i-2,2) << "日   ";
                    cout << endl;
                }
                else if(':' == result[i])
                {
                    cout << result[i-1] << "通道：";
                }
            }
        }
        else if(6 == input_type)
        {
            char year[10];
            char month[10];
            char day[10];
            sscanf(time, "%[^/]/%[^/]/%s", year, month,day);
            cout << year << "年" << month << "月" << day << "日和" << aisle << "通道在以下小时和通道存在视频信息" << endl;

            for(int i =0; i < result.size(); i++)
            {
                if(',' == result[i])
                {
                    cout << result.substr(i-2,2) << "时   ";
                }
                else if(';' == result[i])
                {
                    cout << result.substr(i-2,2) << "时   ";
                    cout << endl;
                }
                else if(':' == result[i])
                {
                    cout << result[i-1] << "通道：";
                }
            }
        }
        else if(7 == input_type)
        {
            cout << "时间段" << time << "和" << aisle << "通道在以下时间段和通道存在视频信息：" << endl;

            for(int i =0; i < result.size(); i++)
            {
                if('-' == result[i])
                {
                    cout << result.substr(i-19,39) << "   ";
                }
                else if(';' == result[i])
                {
                   // cout << result.substr(i-39,39) << "   ";
                    cout << endl;
                }
                else if(':' == result[i])
                {
                    if('/' != result[i-3] && ':' != result[i-3])
                        cout << result[i-1] << "通道：";
                }
            }

        }
        else if(8 == input_type)
        {
            cout << aisle << "通道下的" << time << "时刻的帧头信息如下所示：" << endl;
        }
    }


}

void QueryHandle::split_string(string &input)
{
    int pos = 0;
    for(int i = 0; i < input.size(); i++)
    {
        if(';' == input[i])
        {
            result_buf.push_back(input.substr(pos,(i-pos)));
            pos = i + 1;
        }
    }
}

void QueryHandle::print_queryby_ari_time()
{
    cout << "*******************************************************\n";
    cout << "*                                                     *\n";
    cout << "*  1. 查询所需通道下的视频信息；                      *\n";
    cout << "*                                                     *\n";
    cout << "*  2. 查询某一时间下的视频信息；                      *\n";
    cout << "*                                                     *\n";
    cout << "*******************************************************\n";
    cout << "请输入1或者2选择查询的方式：" << endl;
}

void QueryHandle::print_input_ari_time()
{
    cout << "****************************************************************************\n";
    cout << "*                                                                          *\n";
    cout << "*  请输入需要查询的通道(0~3)与时间信息                                     *\n";
    cout << "*  请按照以下格式输入：                                                    *\n";
    cout << "*  按年查询：   x,x,…:xxxx                                                 *\n";
    cout << "*  按月查询：   x,x,…:xxxx/xx                                              *\n";
    cout << "*  按日查询：   x,x,…:xxxx/xx/xx                                           *\n";
    cout << "*  按小时查询： x,x,…:xxxx/xx/xx/xx                                        *\n";
    cout << "*  按精确到秒的时间段查询：  x,x,…:xxxx/xx/xx/xx:xx:xx—xxxx/xx/xx/xx:xx:xx *\n";
    cout << "*                                                                          *\n";
    cout << "****************************************************************************\n";
}

void QueryHandle::print_input_time()
{
    cout << "****************************************************************************\n";
    cout << "*                                                                          *\n";
    cout << "*  请输入需要查询的时间信息                                                *\n";
    cout << "*  请按照以下格式输入：                                                    *\n";
    cout << "*  按年查询：   xxxx                                                       *\n";
    cout << "*  按月查询：   xxxx/xx                                                    *\n";
    cout << "*  按日查询：   xxxx/xx/xx                                                 *\n";
    cout << "*  按小时查询： xxxx/xx/xx/xx                                              *\n";
    cout << "*  按精确到秒的时间段查询：  xxxx/xx/xx/xx:xx:xx—xxxx/xx/xx/xx:xx:xx       *\n";
    cout << "*                                                                          *\n";
    cout << "****************************************************************************\n";
}

void QueryHandle::print_input_moment()
{
    cout << "****************************************************************************\n";
    cout << "*                                                                          *\n";
    cout << "*  请输入需要查询视频信息的时刻                                            *\n";
    cout << "*  请按照以下格式输入：                                                    *\n";
    cout << "*  x:xxxx/xx/xx/xx:xx:xx                                                   *\n";
    cout << "*                                                                          *\n";
    cout << "****************************************************************************\n";
}


int QueryHandle::check_input_1(string &input, int type)
{
    //type为0的时候，检查不带通道的格式；如果为1检查带通道的格式,输入正确返回0
    if(0 == type)
    {
        if(0 == find_char(input, '/'))
        {
         //   cout << "0/" << endl;
            char buf[30];
            strcpy(buf,input.c_str());
            int year_int = atoi(buf);
            cout << "int input" << year_int << endl;
            if(0 > year_int || 4000 < year_int)
            {
                return 1;
            }else
            {
                input_type = 0;
                return 0;
            }
        }
        else if(1 == find_char(input, '/'))
        {
        //    cout << "1/" << endl;
            char year[10];
            char month[10];
            sscanf((char*)input.c_str(), "%[^/]/%s", year, month);
            int year_int = atoi(year);
            int month_int = atoi(month);
            cout << year_int << "   " << month_int << endl;
            if(0 <= year_int && 4000 >= year_int && 1 <= month_int && 12 >= month_int)
            {
                input_type = 1;
                return 0;
            }else
            {
                return 1;
            }

        }
        else if(2 == find_char(input, '/'))
        {
        //    cout << "2/" << endl;
            char year[10];
            char month[10];
            char day[10];
            sscanf((char*)input.c_str(), "%[^/]/%[^/]/%s", year, month,day);
            int year_int = atoi(year);
            int month_int = atoi(month);
            int day_int = atoi(day);
            if(0 <= year_int && 4000 >= year_int && 1 <= month_int && 12 >= month_int
                    && 0 < day_int && 31 >= day_int) //因为考虑只要时间符合格式要求就可以去查，因此这里没有考虑大小月以及闰月的天数不同的情况
            {
                input_type = 2;
                return 0;
            }else
            {
                return 1;
            }
        }
        else if(1 == find_char(input, '-'))
        {
           // cout << "-";
            char year[10];
            char month[10];
            char day[10];
            char hour[10];
            char min[10];
            char sec[10];  //xxxx/xx/xx/xx:xx:xx
            char temp[30];
            sscanf((char*)input.c_str(), "%[^/]/%[^/]/%[^/]/%[^:]:%[^:]:%[^-]-%s",year, month,day,hour,min,sec,temp);
            int year_int = atoi(year);
            int month_int = atoi(month);
            int day_int = atoi(day);
            int hour_int = atoi(hour);
            int min_int = atoi(min);
            int sec_int = atoi(sec);
            if('-' == input[19])
            {
                if(0 <= year_int && 4000 >= year_int && 1 <= month_int && 12 >= month_int
                        && 0 < day_int && 31 >= day_int && 0 <= hour_int && 24 >= hour_int
                        && 0 <= min_int && 60 >= min_int && 0 <= sec_int && 60 >= sec_int)
                {
               //     cout << "t" << endl;
                    char year1[10];
                    char month1[10];
                    char day1[10];
                    char hour1[10];
                    char min1[10];
                    char sec1[10];
                    sscanf(temp, "%[^/]/%[^/]/%[^/]/%[^:]:%[^:]:%s",year1, month1,day1,hour1,min1,sec1);
                    int year_int1 = atoi(year1);
                    int month_int1 = atoi(month1);
                    int day_int1 = atoi(day1);
                    int hour_int1 = atoi(hour1);
                    int min_int1 = atoi(min1);
                    int sec_int1 = atoi(sec1);
                    if(0 <= year_int1 && 4000 >= year_int1 && 1 <= month_int1 && 12 >= month_int1
                            && 0 < day_int1 && 31 >= day_int1 && 0 <= hour_int1 && 24 >= hour_int1
                            && 0 <= min_int1 && 60 >= min_int1 && 0 <= sec_int1 && 60 >= sec_int1)
                    {
                        input_type = 3;
                        return 0;  //没有进行时间的比较
                    }
                    else
                    {
                        return 1;
                    }
                }else
                {
                    return 1;
                }
            }else
            {
                return 1;
            }
//            cout << year << endl;
//            cout << month << endl;
//            cout << day << endl;
//            cout << hour << endl;
//            cout << min << endl;
//            cout << sec << endl;
//            cout << temp << endl;
        }
        else
        {
            cout << "error" << endl;
            return 1;
        }

    }
    else if(1 == type)
    {
        char aisle[10];
        char temp[50];
        if(0 == find_char(input, ':'))
            return 1;
        sscanf((char*)input.c_str(), "%[^:]:%s", aisle, temp);
        string aisle_string = aisle;
        string temp_string = temp;

        int aisle_num = find_char(aisle_string, ',') + 1;
        int j = 0;
        int aisle_int = 0;
        for(int i = 0; i < aisle_num; i++)
        {
            aisle_int = atoi(aisle + j);
            cout << "aisle_int:" << aisle_int <<endl;
            if(0 <= aisle_int && 3>= aisle_int)
            {

            }
            else
            {
                cout << "return1;"<< endl;
                return 1;
            }
            j += 2;
        }
//        cout << aisle << endl;
//        cout << temp << endl;

        if(0 == find_char(temp_string, '/'))
        {
       //     cout << "0/" << endl;
            int year_int = atoi(temp);
            //cout << "int input" << year_int << endl;
            if(0 > year_int || 4000 < year_int)
            {
                return 1;
            }else
            {
                input_type = 4;
                return 0;
            }
        }
        else if(1 == find_char(temp_string, '/'))
        {
         //   cout << "1/" << endl;
            char year[10];
            char month[10];
            sscanf(temp, "%[^/]/%s", year, month);
            int year_int = atoi(year);
            int month_int = atoi(month);
            cout << year_int << "   " << month_int << endl;
            if(0 <= year_int && 4000 >= year_int && 1 <= month_int && 12 >= month_int)
            {
                input_type = 5;
                return 0;
            }else
            {
                return 1;
            }

        }
        else if(2 == find_char(temp_string, '/'))
        {
         //   cout << "2/" << endl;
            char year[10];
            char month[10];
            char day[10];
            sscanf(temp, "%[^/]/%[^/]/%s", year, month,day);
            int year_int = atoi(year);
            int month_int = atoi(month);
            int day_int = atoi(day);
            if(0 <= year_int && 4000 >= year_int && 1 <= month_int && 12 >= month_int
                    && 0 < day_int && 31 >= day_int) //因为考虑只要时间符合格式要求就可以去查，因此这里没有考虑大小月以及闰月的天数不同的情况
            {
                input_type = 6;
                return 0;
            }else
            {
                return 1;
            }
        }
        else if(1 == find_char(temp_string, '-'))
        {
         //   cout << "-" << endl;
            char year[10];
            char month[10];
            char day[10];
            char hour[10];
            char min[10];
            char sec[10];  //xxxx/xx/xx/xx:xx:xx
            char temp1[30];
            sscanf(temp, "%[^/]/%[^/]/%[^/]/%[^:]:%[^:]:%[^-]-%s",year, month,day,hour,min,sec,temp1);
            int year_int = atoi(year);
            int month_int = atoi(month);
            int day_int = atoi(day);
            int hour_int = atoi(hour);
            int min_int = atoi(min);
            int sec_int = atoi(sec);
            if('-' == input[20 + strlen(aisle)])
            {
                if(0 <= year_int && 4000 >= year_int && 1 <= month_int && 12 >= month_int
                        && 0 < day_int && 31 >= day_int && 0 <= hour_int && 24 >= hour_int
                        && 0 <= min_int && 60 >= min_int && 0 <= sec_int && 60 >= sec_int)
                {
                    if( 24 == hour_int && (0 <= min_int || 0 <= sec_int))
                    {
                        return 1;
                    }
             //       cout << "t" << endl;
                    char year1[10];
                    char month1[10];
                    char day1[10];
                    char hour1[10];
                    char min1[10];
                    char sec1[10];
                    sscanf(temp1, "%[^/]/%[^/]/%[^/]/%[^:]:%[^:]:%s",year1, month1,day1,hour1,min1,sec1);
                    int year_int1 = atoi(year1);
                    int month_int1 = atoi(month1);
                    int day_int1 = atoi(day1);
                    int hour_int1 = atoi(hour1);
                    int min_int1 = atoi(min1);
                    int sec_int1 = atoi(sec1);
                    if(0 <= year_int1 && 4000 >= year_int1 && 1 <= month_int1 && 12 >= month_int1
                            && 0 < day_int1 && 31 >= day_int1 && 0 <= hour_int1 && 24 >= hour_int1
                            && 0 <= min_int1 && 60 >= min_int1 && 0 <= sec_int1 && 60 >= sec_int1)
                    {
                        if( 24 == hour_int && (0 <= min_int || 0 <= sec_int))
                        {
                            return 1;
                        }
                        input_type = 7;
                        return 0;  //没有进行时间的比较
                    }
                    else
                    {
                        return 1;
                    }
                }else
                {
                    return 1;
                }
            }else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }

}

//检查查询视频帧头的输入检查方法
int QueryHandle::check_input_2(string &input)
{
    if(':' == input[1] && 21 == input.size())
    {
        int aisle = atoi(&input[0]);
        if(0 > aisle || 3 < aisle)
            return 1;
        string temp = input.substr(2,19);
        cout << temp << endl;
        char year[10];
        char month[10];
        char day[10];
        char hour[10];
        char min[10];
        char sec[10];  //xxxx/xx/xx/xx:xx:xx
        sscanf((char*)temp.c_str(), "%[^/]/%[^/]/%[^/]/%[^:]:%[^:]:%s",year, month,day,hour,min,sec);
        int year_int = atoi(year);
        int month_int = atoi(month);
        int day_int = atoi(day);
        int hour_int = atoi(hour);
        int min_int = atoi(min);
        int sec_int = atoi(sec);
        if(0 <= year_int && 4000 >= year_int && 1 <= month_int && 12 >= month_int
                && 0 < day_int && 31 >= day_int && 0 <= hour_int && 24 >= hour_int
                && 0 <= min_int && 60 >= min_int && 0 <= sec_int && 60 >= sec_int)
        {
            if( 24 == hour_int && (0 <= min_int || 0 <= sec_int))
            {
                return 1;
            }
            else
            {
                input_type = 8;
                return 0;
            }
        }else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }

}

int QueryHandle::find_char(string &input, char fchar)
{
    int len = input.size();
    int count = 0;
    //cout << len << endl;
    for(int i = 0; i < len; i++)
    {
        if(fchar == input[i])
            count++;
    }
    return count;
}

int main()
{
    QueryHandle qh;
    qh.handle_msg();
//string input = "x,3:2018/05/26/24:23:10-2018/05/26/24:22:23";

   //string input = "2018/12/33";
//    char in[] = "1 3 4";
//   char year[10];
//   char month[10];
//    sscanf((char*)input.c_str(), "%[^/]/%s", year, month);

//    cout << year << endl;
//    cout << month << endl;

   // string input = "2014";

//    char buffer[] = "2423|dfgdfg";
//    char str1[20], str2[20], str3[20];
//    sscanf(buffer, "%[^|]|%s", str1, str2);  sscanf(buffer, "%[^|]|%[^|]|%s", str1, str2, str3);
//    cout << str1 << "\n" << str2 << "\n" << endl;
//                  01234567890123456789

    return 0;
}
