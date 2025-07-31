#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Patient
{
    string name;
    int id;
    int room, room_begin, room_end, bed, bed_begin, bed_end; // 分别记录病人的手术室，手术开始时间，手术结束时间，恢复室，恢复开始时间，恢复结束时间
    int room_time, bed_time;                                 // 手术和恢复时间

    Patient(string n, int i, int r_t, int b_t) // 带参数的构造函数
    {
        name = n;
        id = i;
        room_time = r_t;
        bed_time = b_t;
        // 其他成员默认初始化
        room = room_begin = room_end = bed = bed_begin = bed_end = 0;
    }
};

int n, m; // room count, bed count
int T;    // start time (24 - hour)
int t1, t2, t3;
int k;
vector<Patient> patients;

void initiate()
{
    patients.clear();
}

int main()
{
    while (cin >> n)
    {
        initiate();
        cin >> m >> T >> t1 >> t2 >> t3 >> k;

        for (int i = 0; i < k; i++)
        {
            string name;
            int r_t, b_t;
            cin >> name >> r_t >> b_t;
            Patient(name, i, r_t, b_t);

        }
    }

    return 0;
}
