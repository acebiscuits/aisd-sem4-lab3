#pragma once
#include <stdio.h>
#include<Windows.h>
#include <vector>
#include <limits>
#include <queue>
using namespace std;

template<typename Vertex_t, typename Distance_t = double>
class Graph {

public:
    struct Edge {
        Distance_t dist;
        Vertex_t to;
        Edge(Distance_t new_dist, Vertex_t new_to) : dist(new_dist), to(new_to) {};
        Edge(const Edge& vert) : dist(vert.dist), to(vert.to) {};
    };

    struct Vertex_node {
        Vertex_t id;
        std::vector<Edge> edges;
        Vertex_t prev = -1;
        int color;
        Vertex_node(Vertex_t new_id) : id(new_id) {};
        Vertex_node(const Vertex_node& vert) : id(vert.id), edges(vert.edges) {};
    };

private:
    std::vector<Vertex_node> graph;
public:
    Graph() = default;
    ~Graph() = default;

    bool _empty()
    {
        return graph.begin() == graph.end();
    }
    void print() const
    {
        for (auto vert : graph)
        {
            cout << vert.id << "  ---> " << "[";
            for (auto ed = vert.edges.begin(); ed != vert.edges.end(); ed++)
            {
                cout << "{" << ed->to << ", " << ed->dist << "}";
                if (ed + 1 != vert.edges.end()) cout << ", ";
            }
            cout << "]" << endl;
        }
    };
    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex_t& v) const
    {
        for (auto vert : graph)
        {
            if(vert.id == v) return true;
        }
        return false;
    };
    void add_vertex(const Vertex_t& v)
    {
        try
        {
            if (!has_vertex(v))
            {
                graph.push_back(Vertex_node(v)); 
            }
            else
            {
                throw("this vertex already exist");
            }
        }
        catch (const char* a)
        {
            cout << a << endl;
        }
    };
    bool remove_vertex(const Vertex_t& v)////////////////////////////////////////////////////////////////////////////////////////////////////////////////look below u imbicile и ирэйз неправильно $*&^#
    {
        if (has_vertex(v))
        {
            for (auto it = graph.begin(); it != graph.end(); )
            {
                if (it->id == v)
                {
                    for (auto i = graph.begin(); i != graph.end(); i++)
                    {
                        if (i->id == v) continue;
                        while (has_edge(i->id, v)) remove_edge(i->id, v);
                    }
                    it = graph.erase(it);
                    break;
                }
                ++it;
            }
            return true;
        }
        else
        {
            return false;
        }
    };
    std::vector<Vertex_t> vertices() const
    {
        vector<Vertex_t> v;
        for (auto vert : graph)
        {
            v.push_back(vert.id);

        }
        return v;
    };


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex_t& from, const Vertex_t& to, const Distance_t& d)
    {
        if (!has_vertex(from) && !has_vertex(to))
        {
            Edge edge_to(d, to);
            Vertex_node v_from(from);
            v_from.edges.push_back(edge_to);
            graph.push_back(v_from);
            Vertex_node v_to(to);
            graph.push_back(v_to);
        }
        else if (!has_vertex(from) && has_vertex(to))
        {
            Edge edge_to(d, to);
            Vertex_node v_from(from);
            v_from.edges.push_back(edge_to);
            graph.push_back(v_from);
        }
        else if (has_vertex(from) && !has_vertex(to))
        {
            Edge edge_to(d, to);
            Vertex_node v_to(to);
            graph.push_back(v_to);
            auto it = graph.begin();
            auto it_e = graph.end();
            while ((*it).id != from && it != it_e)
            {
                it++;
            }
            it->edges.push_back(edge_to);
        }
        else
        {
            Edge edge_to(d, to);
            auto it = graph.begin();
            auto it_e = graph.end();
            while ((*it).id != from && it != it_e)
            {
                it++;
            }
            it->edges.push_back(edge_to);
        }
    };
    bool remove_edge(const Vertex_t& from, const Vertex_t& to)
    {
        if (graph.empty() || !has_vertex(to) || !has_vertex(from))throw("no vertexes or no vertex");
        try {
            auto it = graph.begin();
            auto it_e = graph.end();
            while ((*it).id != from && it != it_e)
            {
                it++;
            }
            if (it == it_e)return false;

            auto it_to = (*it).edges.begin();
            auto it_to_e = (*it).edges.end();
            while ((*it_to).to != to && it_to != it_to_e)
            {
                it_to++;
            }
            if (it_to == it_to_e)return false;
            (*it).edges.erase(it_to);

            return true;
        }
        catch (const char* e)
        {
            cout << e << endl;
        }
    };
    bool remove_edge(const Vertex_t& from, const Vertex_t& to, const Distance_t& d)
    {
        if (graph.empty() || !has_vertex(to) || !has_vertex(from))throw("no vertexes or no vertex");
        try {
            /*auto it = graph.begin();
            auto it_e = graph.end();
            while ((*it).id != from && it != it_e)
            {
                it++;
            }
            if (it == it_e)return false;

            auto it_to = (*it).edges.begin();
            auto it_to_e = (*it).edges.end();
            while ((*it_to).to != to && it_to != it_to_e)
            {
                it_to++;
            }
            if (it_to == it_to_e)return false;
            if (d == (*it_to).dist)
                (*it).edges.erase(it_to);

            return true;*/
            for (auto vert = graph.begin(); vert != graph.end(); vert++)
            {
                if (vert->id == from)
                {
                    for (auto edge = vert->edges.begin(); edge != vert->edges.end(); edge++)
                    {
                        if (edge->to == to && edge->dist == d)
                        {
                            vert->edges.erase(edge);
                            return true;
                        }
                        else
                        {
                            if (edge == vert->edges.end())
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        catch (const char* e)
        {
            cout << e << endl;
        }
    }; //c учетом расстояния
    bool has_edge(const Vertex_t& from, const Vertex_t& to) const
    {
        if (graph.empty() || !has_vertex(to) || !has_vertex(from))throw("no vertexes or no vertex");
        try {
            for (auto v_from : graph)
            {
                if (v_from.id == from)
                {
                    for (auto v_to : v_from.edges)
                    {
                        if (v_to.to == to)
                            return true;
                    }
                }
            }
            return false;
        }
        catch (const char* e)
        {
            cout << e << endl;
        }
    };
    bool has_edge(const Vertex_t& from, const Vertex_t& to, const Distance_t& d)
    {
        if (graph.empty() || !has_vertex(to) || !has_vertex(from))throw("no vertexes or no vertex");
        try {
            for (auto v_from : graph)
            {
                if (v_from.id == from)
                {
                    for (auto v_to : v_from.edges)
                    {
                        if (v_to.to == to && v_to.dist == d)
                            return true;
                    }
                }
            }
            return false;
        }
        catch (const char* e)
        {
            cout << e << endl;
        }
    }; //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex_t& vertex)
    {
        if (graph.empty() || !has_vertex(vertex))throw("no vertexes or no vertex");
        vector<Edge> res;
        try{
            for (auto vert : graph)
            {
                if (vert.id == vertex)
                {
                    res = vert.edges;
                }
            }
            return res;
        }
    catch (const char* e)
    {
        cout << e << endl;
    }
    };

    size_t order() const
    {
        return graph.size();
    }; //порядок
    size_t degree() const
    {
        if (graph.empty())throw("no vertexes");
        size_t degree = 0;
        try {
            for (auto vert : graph)
            {
                degree += vert.edges.size();
            }
            return degree;
        }
        catch (const char* e)
        {
            cout << e << endl;
        }
    }; //степень

    void set_prev(const Vertex_t& prev,const Vertex_t& vert)
        {
        auto start = graph.begin();
        auto end = graph.end();
        if (graph.empty() || !has_vertex(prev) || !has_vertex(vert))throw("no vertexes or no vertex");
        try {
            while (start != end)
            {
                if (start->id == vert)
                {
                    start->prev = prev;
                    break;
                }
                start++;
            }
        }
        catch (const char* e)
        {
            cout << e << endl;
        }
    }
    //поиск кратчайшего пути
    pair<pair<Distance_t, int>, vector<Vertex_t>> shortest_path(const Vertex_t& from, const Vertex_t& to, const bool& check)
    {
        pair<pair<Distance_t, int>, vector<Vertex_t>> vertexes_list;
        //pair<Distance_t, vector<Vertex_t>> vertexes_list_minus;
        vertexes_list.first.second = 0;
        vector<pair<Vertex_t, Distance_t>> Vertexes_dist;
        auto it = graph.begin();
        auto it_end = graph.end();
        pair<Vertex_t, Distance_t> one_vertex;

        if (graph.empty() || !has_vertex(from)||!has_vertex(to))throw("no vertexes or no vertex");
        try {
            for (int i = 0; i < graph.size(); i++)
            {
                (one_vertex).first = it->id;
                if (it->id == from)
                {
                    (one_vertex).second = Distance_t(0);
                    Vertexes_dist.push_back(one_vertex);
                }
                else
                {
                    (one_vertex).second = std::numeric_limits<Distance_t>::infinity();
                    Vertexes_dist.push_back(one_vertex);
                }
                it++;
            }
            for (int counter = 0; (counter) < graph.size() - 1;)//итерируем n-1 раз
            {
                for (auto i_arr = Vertexes_dist.begin(); i_arr != Vertexes_dist.end(); )//
                {                                                                       //перебор вершин с небесконечной дистанцией до них(в 1ой итерации это только исходная вершина)(пусть это вершина T)
                    if ((*i_arr).second != std::numeric_limits<Distance_t>::infinity())//
                    {
                        for (auto i_vert : graph)           //
                        {                                   //находим в графе эту вершину T с небесконечным расстоянием
                            if (i_vert.id == (*i_arr).first)//
                            {
                                for (auto i_edges_from : i_vert.edges)//залезаем в список исходящих ребер
                                {
                                    for (auto i_vert_to : graph)            //
                                    {                                       //перебираем вершины графа и ищем ту, в которую ведет ребро на данной итерации   
                                        if (i_edges_from.to == i_vert_to.id)//
                                        {
                                            for (auto found_v = Vertexes_dist.begin(); found_v != Vertexes_dist.end(); )//перебираем список вершин с их расстояниями чтобы обратиться к нужной вершине на данной итерациии
                                            {
                                                if ((*found_v).first == i_vert_to.id)//*обращаемся к ней*
                                                {
                                                    if ((*i_arr).second + i_edges_from.dist < (*found_v).second)//сравниваем расстояния
                                                    {
                                                        (*found_v).second = (*i_arr).second + i_edges_from.dist;
                                                        //i_vert_to.prev = i_vert.id;
                                                        set_prev(i_vert.id, i_vert_to.id);
                                                    }
                                                }
                                                found_v++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    i_arr++;
                }
                counter++;
            }
            Vertex_t neded = to;
            //Vertex_t neded2 = to;
            int flag = 0;
            int pushed = 0;
            while (true)
            {
                for (auto vert = graph.begin(); vert != graph.end(); )
                {
                    if (vert->id == neded)
                    {
                        for (auto minus_c = vertexes_list.second.begin(); minus_c != vertexes_list.second.end(); )
                        {
                            if (vert->id == (*minus_c))
                            {

                                flag = 2;
                            }
                            minus_c++;
                            //break;
                        }
                        if (flag != 2)
                        {
                            vertexes_list.second.push_back(vert->id);
                            pushed = 1;
                            neded = vert->prev;
                            if (neded == -1) { flag = 1; }
                            else { flag = 0; }
                        }
                        else
                            pushed = 0;
                        break;
                    }
                    if (flag == 2)
                        break;
                    if (neded == vert->id)
                    {
                    }
                    vert++;
                    if (vert == graph.end() && !pushed)
                        flag = 1;
                }
                if (flag == 2)
                    break;
                if (flag == 1)break;
            }
            if (flag == 2)
            {
                vertexes_list.first.second = -1;
                return vertexes_list;
            }
            for (auto inf_check = graph.begin(); inf_check != graph.end();)
            {
                if (inf_check->id == to)
                {
                    if (inf_check->prev == -1)
                    {
                        vertexes_list.first.second = 1;
                        return vertexes_list;
                    }
                }
                inf_check++;
            }
            reverse(vertexes_list.second.begin(), vertexes_list.second.end());
            Distance_t one_dist;
            Distance_t sev_dist = std::numeric_limits<Distance_t>::infinity();
            int dist_flag = 0;
            while (true)
            {
                for (auto vert_list = vertexes_list.second.begin(); vert_list != vertexes_list.second.end();)//идем по списку в прямом направлении
                {

                    for (auto vert = graph.begin(); vert != graph.end(); )  //
                    {                                                       //ищем в графе нужную вершину
                        if (*vert_list == vert->id)                         //
                        {
                            for (auto vert_to = vert->edges.begin(); vert_to != vert->edges.end();)
                            {

                                auto check = vert_list;
                                auto check2 = vert_list;
                                if ((++check) != vertexes_list.second.end())
                                {
                                    if (vert_to->to == (*(++check2)))
                                    {
                                        one_dist = vert_to->dist;
                                        if (one_dist < sev_dist && sev_dist != std::numeric_limits<Distance_t>::infinity())
                                        {
                                            vertexes_list.first.first -= sev_dist;
                                            vertexes_list.first.first += one_dist;
                                            sev_dist = one_dist;
                                        }
                                        else
                                        {
                                            sev_dist = one_dist;
                                            vertexes_list.first.first += one_dist;
                                        }
                                    }
                                }

                                vert_to++;
                            }

                        }
                        vert++;
                    }

                    vert_list++;
                    auto old_vert = vert_list;
                    //auto check3 = ++vert_list;
                    auto check3 = vert_list;
                    if (vert_list == vertexes_list.second.end())
                    {
                        check3 = vert_list;
                    }
                    else
                    {
                        check3 = ++vert_list;
                        vert_list = old_vert;
                    }
                    if (check3 == vertexes_list.second.end())
                    {
                        dist_flag = 1;
                    }
                }
                if (dist_flag)
                    break;
            }
            //if (check)
            //{
            //    for (auto i_arr = Vertexes_dist.begin(); i_arr != Vertexes_dist.end(); )//
            //    {                                                                       //перебор вершин с небесконечной дистанцией до них(в 1ой итерации это только исходная вершина)(пусть это вершина T)
            //        if ((*i_arr).second != std::numeric_limits<Distance_t>::infinity())//
            //        {
            //            for (auto i_vert : graph)           //
            //            {                                   //находим в графе эту вершину T с небесконечным расстоянием
            //                if (i_vert.id == (*i_arr).first)//
            //                {
            //                    for (auto i_edges_from : i_vert.edges)//залезаем в список исходящих ребер
            //                    {
            //                        for (auto i_vert_to : graph)            //
            //                        {                                       //перебираем вершины графа и ищем ту, в которую ведет ребро на данной итерации   
            //                            if (i_edges_from.to == i_vert_to.id)//
            //                            {
            //                                for (auto found_v = Vertexes_dist.begin(); found_v != Vertexes_dist.end(); )//перебираем список вершин с их расстояниями чтобы обратиться к нужной вершине на данной итерациии
            //                                {
            //                                    if ((*found_v).first == i_vert_to.id)//*обращаемся к ней*
            //                                    {
            //                                        if ((*i_arr).second + i_edges_from.dist < (*found_v).second)//сравниваем расстояния
            //                                        {
            //                                            (*found_v).second = (*i_arr).second + i_edges_from.dist;
            //                                            //i_vert_to.prev = i_vert.id;
            //                                            set_prev(i_vert.id, i_vert_to.id);
            //                                        }
            //                                    }
            //                                    found_v++;
            //                                }
            //                            }
            //                        }
            //                    }
            //                }
            //            }
            //        }
            //        i_arr++;
            //    }
            //    Vertex_t neded = to;
            //    int flag = 0;
            //    while (true)
            //    {
            //        for (auto vert = graph.begin(); vert != graph.end(); )
            //        {
            //            if (vert->id == neded)
            //            {
            //                vertexes_list_minus.second.push_back(vert->id);
            //                neded = vert->prev;
            //                if (neded == -1)flag = 1;
            //            }
            //            vert++;
            //        }

            //        if (flag)break;
            //    }
            //    reverse(vertexes_list_minus.second.begin(), vertexes_list_minus.second.end());
            //    Distance_t one_dist;
            //    Distance_t sev_dist = std::numeric_limits<Distance_t>::infinity();
            //    int dist_flag = 0;
            //    while (true)
            //    {
            //        for (auto vert_list = vertexes_list_minus.second.begin(); vert_list != vertexes_list_minus.second.end();)//идем по списку в прямом направлении
            //        {

            //            for (auto vert = graph.begin(); vert != graph.end(); )  //
            //            {                                                       //ищем в графе нужную вершину
            //                if (*vert_list == vert->id)                         //
            //                {
            //                    for (auto vert_to = vert->edges.begin(); vert_to != vert->edges.end();)
            //                    {

            //                        auto check = vert_list;
            //                        auto check2 = vert_list;
            //                        if ((++check) != vertexes_list_minus.second.end())
            //                        {
            //                            if (vert_to->to == (*(++check2)))
            //                            {
            //                                one_dist = vert_to->dist;
            //                                if (one_dist < sev_dist && sev_dist != std::numeric_limits<Distance_t>::infinity())
            //                                {
            //                                    vertexes_list_minus.first -= sev_dist;
            //                                    vertexes_list_minus.first += one_dist;
            //                                    sev_dist = one_dist;
            //                                }
            //                                else
            //                                {
            //                                    sev_dist = one_dist;
            //                                    vertexes_list_minus.first += one_dist;
            //                                }
            //                            }
            //                        }

            //                        vert_to++;
            //                    }

            //                }
            //                vert++;
            //            }

            //            vert_list++;
            //            auto old_vert = vert_list;
            //            //auto check3 = ++vert_list;
            //            auto check3 = vert_list;
            //            if (vert_list == vertexes_list_minus.second.end())
            //            {
            //                check3 = vert_list;
            //            }
            //            else
            //            {
            //                check3 = ++vert_list;
            //                vert_list = old_vert;
            //            }
            //            if (check3 == vertexes_list_minus.second.end())
            //            {
            //                dist_flag = 1;
            //            }
            //        }
            //        if (dist_flag)
            //            break;
            //    }
            //    return vertexes_list_minus;
            //}
            return vertexes_list;
        }
        catch (const char* e)
        {
            cout << e << endl;
        }

    };

    //обход
    std::vector<Vertex_t>  walk(const Vertex_t& start_vertex)// -1 - white
    {                                                             // 0 - grey    
        vector<Vertex_t> vertexes;                                // 1 - black
        queue<Vertex_t> queue;
        Vertex_t ptr;
        int flag = 0;
        if (graph.empty())throw("no vertexes");
        try {
            for (auto vert = graph.begin(); vert != graph.end();)
            {
                vert->color = -1;
                vert++;
            }
            queue.push(start_vertex);
            vertexes.push_back(start_vertex);
            for (auto vert = graph.begin(); vert != graph.end();)
            {
                if (vert->id == start_vertex)
                {
                    vert->color = 0;
                    while (!queue.empty())
                    {
                        ptr = queue.front();
                        queue.pop();

                        for (auto vert_pop = graph.begin(); vert_pop != graph.end();)
                        {
                            if (vert_pop->id == ptr)
                            {
                                for (auto vert_to = vert_pop->edges.begin(); vert_to != vert_pop->edges.end();)
                                {
                                    for (auto vert_found = graph.begin(); vert_found != graph.end();)
                                    {
                                        if (vert_found->id == vert_to->to)
                                        {
                                            if (vert_found->color == -1)
                                            {
                                                vert_found->color = 0;
                                                queue.push(vert_found->id);
                                                vertexes.push_back(vert_found->id);
                                                flag = 0;
                                            }

                                        }
                                        vert_found++;
                                    }
                                    vert_to++;
                                }

                            }

                            vert_pop++;
                            if (flag == 0)
                            {
                                flag = 1;
                                vert_pop = graph.begin();
                                vert_pop->color = 1;
                                ptr = queue.front();
                                queue.pop();
                            }

                        }
                    }
                }
                vert++;
            }
            return vertexes;
        }
        catch (const char* e)
        {
            cout << e << endl;
        }
    };
    
    pair<Vertex_t, Distance_t> task()//подобавляй проверок на то что например есть ли вершина в графе или на то что граф не пустой и тд....................
    {
       
        pair<Vertex_t, Distance_t> point;
        point.second = std::numeric_limits<Distance_t>::infinity();
        point.first = -1;
        Distance_t dist = (Distance_t)0;
        if (graph.empty())throw("no vertexes");
        try {
            for (auto vert = graph.begin(); vert != graph.end();)
            {

                for (auto edge = vert->edges.begin(); edge != vert->edges.end(); edge++)
                {
                    dist += edge->dist;

                }
                if (point.second > (dist / ((int)vert->edges.size())))
                {
                    point.second = (dist / ((int)vert->edges.size()));
                    point.first = vert->id;
                }
                vert++;
                dist = (Distance_t)0;
            }
            return point;
        }
        catch (const char* e)
        {
            cout << e << endl;
        }
    }
};

template Graph<int>;