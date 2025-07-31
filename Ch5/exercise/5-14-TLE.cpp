// answer correct, but TLE
#include <iostream>
#include <queue>
#include <set>

using namespace std;

struct OrderInfo
{
    int id, size, price;
    bool operator<(const OrderInfo &rhs) const // 默认认为 a < b 时 b 优先, BUY 最高买价优先
    {
        if (price != rhs.price)
            return price < rhs.price;
        return id > rhs.id;
    }
};

struct SellComparator // SELL 低价优先
{
    bool operator()(const OrderInfo &a, const OrderInfo &b)
    {
        if (a.price != b.price)
            return a.price > b.price;
        return a.id > b.id;
    }
};

priority_queue<OrderInfo> bids;                                    // BUY 高价优先
priority_queue<OrderInfo, vector<OrderInfo>, SellComparator> asks; // SELL 低价优先
int T;
set<int> canceled;

void test_display_all()
{
    cout << "======= Canceled id =======" << endl;
    for (int i : canceled)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << "======= Bids ==============" << endl;
    while (!bids.empty())
    {
        OrderInfo e = bids.top();
        bids.pop();
        cout << "Id: " << e.id << ", Size: " << e.size
             << ", Price: " << e.price << endl;
    }
    cout << "======= Asks ==============" << endl;
    while (!asks.empty())
    {
        OrderInfo e = asks.top();
        asks.pop();
        cout << "Id: " << e.id << ", Size: " << e.size
             << ", Price: " << e.price << endl;
    }
    cout << "===========================" << endl;
}

void initiate()
{
    canceled.clear();
    while (!bids.empty())
    {
        bids.pop();
    }
    while (!asks.empty())
    {
        asks.pop();
    }
}

void solve(bool isBuy)
{
    while (!bids.empty() && !asks.empty())
    {
        OrderInfo bid = bids.top();
        OrderInfo ask = asks.top();

        if (canceled.count(bid.id))
        {
            bids.pop();
            continue;
        }
        if (canceled.count(ask.id))
        {
            asks.pop();
            continue;
        }
        if (bid.price >= ask.price) // 存在成交
        {
            int trade_size = min(bid.size, ask.size);        // 成交数目
            int trade_price = isBuy ? ask.price : bid.price; // 成交价格
            // 打印成交数目和价格
            cout << "TRADE " << trade_size << " " << trade_price << endl;

            // bid 有剩余
            bids.pop();
            if (bid.size > trade_size)
            {
                bid.size -= trade_size;
                bids.push(bid); // 重新放回剩余部分
            }

            //  ask 有剩余
            asks.pop();
            if (ask.size > trade_size)
            {
                ask.size -= trade_size;
                asks.push(ask); // 重新放回剩余部分
            }
        }
        else
        {
            break;
        }
    }
}

void print_quote()
{
    int bid_size = 0, bid_price = 0, ask_size = 0, ask_price = 99999;

    auto bids_tmp = bids; // 局部临时拷贝导致 TLE
    while (!bids_tmp.empty())
    {
        OrderInfo order = bids_tmp.top();
        bids_tmp.pop();
        if (canceled.count(order.id))
        {
            continue;
        }
        if (bid_price == 0 || order.price > bid_price)
        {
            bid_price = order.price;
            bid_size = order.size;
        }
        else if (order.price == bid_price)
        {
            bid_size += order.size;
        }
        else
        {
            break;
        }
    }

    auto asks_tmp = asks;
    while (!asks_tmp.empty())
    {
        OrderInfo order = asks_tmp.top();
        asks_tmp.pop();
        if (canceled.count(order.id))
        {
            continue;
        }
        if ((ask_price == 99999 && ask_size == 0) || order.price < ask_price)
        {
            ask_price = order.price;
            ask_size = order.size;
        }
        else if (order.price == ask_price)
        {
            ask_size += order.size;
        }
        else
        {
            break;
        }
    }

    cout << "QUOTE " << bid_size << " " << bid_price << " - "
         << ask_size << " " << ask_price << endl;
}

int main()
{
    bool isFirst = 1;
    while (cin >> T)
    {
        getchar();
        initiate();

        if (!isFirst)
        {
            cout << endl;
        }
        isFirst = 0;

        for (int i = 0; i < T; i++)
        {
            string s;
            int q, p;
            cin >> s;
            if (s == "CANCEL")
            {
                cin >> q;
                canceled.insert(q);
            }
            else
            {
                cin >> q >> p;
                if (s == "BUY")
                {
                    bids.push({i + 1, q, p});
                    // 尝试匹配
                    solve(true);
                }
                else // SELL
                {
                    asks.push({i + 1, q, p});
                    solve(false);
                }
            }
            print_quote();
        }
        // test
        // test_display_all();
    }

    return 0;
}