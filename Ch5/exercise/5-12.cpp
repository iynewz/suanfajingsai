
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

struct MapInfo
{
    string name;
    double area, x1, y1, x2, y2, w, h, ratio, center_x, center_y;
    int detail_level = 0;

    MapInfo(const string &s) // 构造函数
    {
        size_t start = 0;
        size_t end = s.find(' ');
        name = s.substr(start, end);

        start = end + 1;
        end = s.find(' ', start);
        x1 = stod(s.substr(start, end));

        start = end + 1;
        end = s.find(' ', start);
        y1 = stod(s.substr(start, end));

        start = end + 1;
        end = s.find(' ', start);
        x2 = stod(s.substr(start, end));

        start = end + 1;
        end = s.find(' ', start);
        y2 = stod(s.substr(start, end));

        w = abs(x1 - x2);
        h = abs(y1 - y2);
        area = w * h;
        ratio = h / w;
        center_x = (x1 + x2) / 2;
        center_y = (y1 + y2) / 2;

        // 统一为 左下、右上 点
        if (x1 > x2)
        {
            double t = x1;
            x1 = x2;
            x2 = t;
        }
        if (y1 > y2)
        {
            double t = y1;
            y1 = y2;
            y2 = t;
        }
    }

    void display() const
    {
        cout << "Name: " << name << ", Area: " << area
             << ", x1: " << x1 << ", y1: " << y1
             << ", x2: " << x2 << ", y2: " << y2
             << ", w: " << w << ", h: " << h
             << ", Ratio: " << ratio << ", Detail level: " << detail_level << endl;
    }
};

vector<MapInfo> maps;
map<string, pair<double, double>> locations;
map<string, vector<MapInfo>> loc_mp;

string retrieve_map(const vector<MapInfo> &maps, const string &location, const int &level)
{
    vector<MapInfo> sorted_mp;
    double loc_x = locations[location].first;
    double loc_y = locations[location].second;
    for (const MapInfo mp : maps)
    {
        if (mp.detail_level == level)
        {
            sorted_mp.push_back(mp);
        }
    }
    sort(sorted_mp.begin(), sorted_mp.end(), [loc_x, loc_y](const MapInfo &a, MapInfo &b)
         {
             double distance_a = (a.center_x - loc_x) * (a.center_x - loc_x) + (a.center_y - loc_y) * (a.center_y - loc_y);
             double distance_b = (b.center_x - loc_x) * (b.center_x - loc_x) + (b.center_y - loc_y) * (b.center_y - loc_y);
             if (distance_a != distance_b)
             {
                 return distance_a < distance_b;
             }
             if (a.ratio != b.ratio)
             {
                 return (a.ratio - 0.75) < (b.ratio - 0.75);
             }
             if ((a.x2 - loc_x) != (b.x2 - loc_x))
             {
                 return (a.x2 - loc_x) > (b.x2 - loc_x);
             }
             return a.x1 < b.x1; });

    return sorted_mp[0].name;
}

int main()
{
    string s;
    cin >> s;
    getchar();
    while (1)
    {
        getline(cin, s);
        if (s == "LOCATIONS")
        {
            break;
        }
        else
        {
            MapInfo map(s); // 生成 map
            maps.push_back(map);
            // map.display();
        }
    }
    while (1)
    {
        getline(cin, s);
        if (s == "REQUESTS")
        {
            break;
        }
        else
        { // s 是每一个 location "Monterey -4.0 2.0"
            size_t start = 0;
            size_t end = s.find(' ');
            string loc = s.substr(start, end);

            start = end + 1;
            end = s.find(' ', start);
            double x = stod(s.substr(start, end));

            start = end + 1;
            end = s.find(' ', start);
            double y = stod(s.substr(start, end));

            vector<MapInfo> include_maps;

            for (MapInfo map : maps)
            {
                if (map.x1 <= x && x <= map.x2 && map.y1 <= y && y <= map.y2)
                {
                    include_maps.push_back(map);
                }
            }
            locations[loc] = {x, y};
            loc_mp[loc] = include_maps;
        }
    }

    while (1)
    {
        getline(cin, s);
        if (s == "END")
        {
            break;
        }
        else
        {
            size_t start = 0;
            size_t end = s.find(' ');
            string req_loc = s.substr(start, end);

            start = end + 1;
            end = s.find(' ', start);
            int req_level = stoi(s.substr(start, end));
            cout << req_loc << " at detail level " << req_level;
            if (!loc_mp.count(req_loc))
            {
                cout << " unknown location" << endl;
            }
            else
            {
                vector<MapInfo> maps = loc_mp[req_loc]; // all maps that contain the location
                if (maps.size() == 0)
                {
                    cout << " no map contains that location" << endl;
                    continue;
                }

                sort(maps.begin(), maps.end(), [](const MapInfo &a, MapInfo &b)
                     {
                         return a.area > b.area; // 降序排序
                     });

                double curr_area = 0.0;
                int k = 0;
                for (MapInfo &m : maps) // 必须引用
                {
                    if (m.area != curr_area)
                    {
                        k++;
                        curr_area = m.area;
                    }
                    m.detail_level = k; // calculate the max detail level k
                }

                if (req_level > k)
                {
                    string use_map = retrieve_map(maps, req_loc, k);
                    cout << " no map at that detail level; using " << use_map << endl;
                }
                else
                {
                    string use_map = retrieve_map(maps, req_loc, req_level);
                    cout << " using " << use_map << endl;
                }
            }
        }
    }
    return 0;
}