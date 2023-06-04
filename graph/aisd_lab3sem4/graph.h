#pragma once
#include <stdio.h>
#include<Windows.h>
#include <vector>

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
    bool remove_vertex(const Vertex_t& v)////////////////////////////////////////////////////////////////////////////////////////////////////////////////look below u imbicile и ирэйз неправильно блять
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

    };
    bool remove_edge(const Vertex_t& from, const Vertex_t& to, const Distance_t& d)
    {
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
        if(d == (*it_to).dist)
        (*it).edges.erase(it_to);

        return true;
    }; //c учетом расстояния
    bool has_edge(const Vertex_t& from, const Vertex_t& to) const
    {
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
    };
    bool has_edge(const Vertex_t& from, const Vertex_t& to, const Distance_t& d)
    {
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
    }; //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex_t& vertex)
    {
        vector<Edge> res;
        for (auto vert : graph)
        {
            if (vert.id == vertex)
            {
                res = vert.edges;
            }
        }
        return res;
    };

    size_t order() const; //порядок
    size_t degree() const; //степень


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex_t& from, const Vertex_t& to) const;
    //обход
    std::vector<Vertex_t>  walk(const Vertex_t& start_vertex)const;
};

template Graph<int>;