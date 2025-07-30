#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 20 + 5, maxm = 5 + 5;

struct Event
{
    int time, id;
    bool isRorC; // true: 需求到达； false: 需求完毕
    bool operator<(const Event &rhs) const { return time > rhs.time; }
    Event(int t, int i, bool isr = true) : time(t), id(i), isRorC(isr) {}
};

struct StaffInfo
{
    // last: 上一次开始处理请求的时间
    int tids[maxn], pid, k, idx, last;

    bool operator<(const StaffInfo &rhs) const
    {
        return last < rhs.last || (last == rhs.last && pid < rhs.pid);
    }
};

struct ReqInfo
{
    int tid, num, t0, t, dt;
};

int kase = 0;
int n, m;
priority_queue<Event> em; // 请求队列 + 空闲客服队列
ReqInfo requests[maxn];
StaffInfo staffs[maxm];

multiset<int> rQs; // 哪些主题的请求正在等待被客服处理
set<int> freeStaffs;

struct Comp
{
    bool operator()(int lhs, int rhs) const { return staffs[lhs] < staffs[rhs]; }
};

set<int, Comp> rt[maxn]; // rt[i] 存储能处理主题 i 的客服索引集合（自动按优先级排序了）

void test_print_staffs()
{
    cout << "=== Staff Information ===" << endl;
    for (int i = 0; i < m; i++)
    {
        StaffInfo &s = staffs[i];
        cout << "Staff " << i << ": pid=" << s.pid
             << ", k=" << s.k << ", last=" << s.last << endl;
        cout << "  Can handle topics: ";
        for (int j = 0; j < s.k; j++)
        {
            cout << s.tids[j] << " ";
        }
        cout << endl;
    }
    cout << "=========================" << endl;
}

void test_print_em()
{
    cout << "=== Event Queue ===" << endl;
    priority_queue<Event> temp = em;
    while (!temp.empty())
    {
        Event e = temp.top();
        temp.pop();
        cout << "Time: " << e.time << ", ID: " << e.id
             << ", Type: " << (e.isRorC ? "Request" : "Completion") << endl;
    }
    cout << "===================" << endl;
}

void solve()
{
    int Time = em.top().time;

    while (!em.empty() && em.top().time == Time) // 把队列头部的同一时间点的所有事件都处理了
    {
        Event e = em.top();
        if (em.top().isRorC)
        {
            rQs.insert(e.id); // 请求事件 -> 请求队列
        }
        else
        {
            freeStaffs.insert(e.id); // 空闲客服事件 -> 空闲客服集合
        }
        em.pop();
    }

    while (!rQs.empty() && !freeStaffs.empty()) // 尝试分配
    {
        for (int i = 0; i < n; i++)
        {
            rt[i].clear();
        }

        bool canAssign = false;
        for (int &i : freeStaffs)
        {
            auto &si = staffs[i];
            for (int j = 0; j < si.k; j++)
            {
                int tid = si.tids[j];
                if (!rQs.count(tid))
                    continue;
                canAssign = true;
                rt[tid].insert(si.idx);
                break;
            }
        }
        if (!canAssign)
            break;
        for (int i = 0; i < n; i++)
        {
            auto &ss = rt[i];
            while (rQs.count(i) && !ss.empty())
            {
                rQs.erase(rQs.find(i));
                int si = *(ss.begin());
                auto &s = staffs[si];
                s.last = Time;
                em.push(Event(Time + requests[i].t, s.idx, false));
                freeStaffs.erase(s.idx);
                ss.erase(si);
            }
        }
    }
    if (em.empty())
    {
        cout << "Scenario " << ++kase << ": All requests are serviced within " << Time << " minutes." << endl;
    }
}

int main()
{
    map<int, int> tids;

    while (cin >> n && n)
    {
        // 初始化
        rQs.clear();
        freeStaffs.clear();
        tids.clear();

        for (int i = 0; i < n; i++)
        {
            ReqInfo &r = requests[i]; // 是引用不是 拷贝
            cin >> r.tid >> r.num >> r.t0 >> r.t >> r.dt;
            tids[r.tid] = i; // 记录 tid 出现的先后顺序
            r.tid = i;
            for (int j = 0; j < r.num; j++)
            {
                em.push(Event(r.t0 + r.dt * j, i, true));
            }
        }
        cin >> m;
        for (int i = 0; i < m; i++)
        {
            StaffInfo &s = staffs[i];
            cin >> s.pid >> s.k;
            for (int j = 0; j < s.k; j++)
            {
                cin >> s.tids[j];
                s.tids[j] = tids[s.tids[j]];
            }
            s.last = 0;
            s.idx = i;
            em.push(Event(0, s.idx, false));
        }
        // test_print_em();
        // test_print_staffs();
        while (!em.empty())
        {
            solve();
        }
    }
    return 0;
}