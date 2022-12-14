#ifndef __INTERFERENCE_GRAPH__HPP
#define __INTERFERENCE_GRAPH__HPP

#include <exception>
#include <string>
#include <unordered_set>
#include <map>

class UnknownVertexException : public std::runtime_error {
public:
  UnknownVertexException(const std::string &v)
      : std::runtime_error("Unknown vertex " + v) {}
};

class UnknownEdgeException : public std::runtime_error {
public:
  UnknownEdgeException(const std::string &v, const std::string &w)
      : std::runtime_error("Unknown edge " + v + " - " + w) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file.
template <typename T>
class InterferenceGraph {
public:
  // Custom type used to represent edges. This is mainly
  // used in the utility function for reading and writing
  // the graph structure to/from files.
  using EdgeTy = std::pair<T, T>;

  InterferenceGraph();

  ~InterferenceGraph();

  void addEdge(const T &v, const T &w);

  void addVertex(const T &vertex) noexcept;

  void removeEdge(const T &v, const T &w);

  void removeVertex(const T &vertex);

  std::unordered_set<T> vertices() const noexcept;

  std::unordered_set<T> neighbors(const T &vertex) const;

  unsigned numVertices() const noexcept;

  unsigned numEdges() const noexcept;

  bool interferes(const T &v, const T &w) const;

  unsigned degree(const T &v) const;

private:
  // Private member variables here.
    std::map<T, std::unordered_set<T>> graph;
    unsigned numVer = 0;
    unsigned numEdg = 0;
    
};

template <typename T> InterferenceGraph<T>::InterferenceGraph() {}

template <typename T> InterferenceGraph<T>::~InterferenceGraph() {}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const
{
    if(graph.find(vertex) == graph.end())
        throw UnknownVertexException(vertex);
    return graph.find(vertex)->second;
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept
{
    std::unordered_set<T> tmp;
    for(auto x: graph)
    {
        tmp.insert(x.first);
    }
    return tmp;
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept {
    return numVer;
}

template <typename T> unsigned InterferenceGraph<T>::numEdges() const noexcept {
    return numEdg;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &v, const T &w)
{
    if(graph.find(v) == graph.end())
        throw UnknownVertexException(v);
    if(graph.find(w) == graph.end())
        throw UnknownVertexException(w);
    
    auto it = graph.find(v);
    auto it2 = graph.find(w);
    
    if(it->second.find(w) == it->second.end()){
        it->second.insert(w);
        it2->second.insert(v);
        numEdg++;
    }
}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &v, const T &w)
{
    if(graph.find(v) == graph.end())
        throw UnknownVertexException(v);
    if(graph.find(w) == graph.end())
        throw UnknownVertexException(w);
    
    auto it = graph.find(v);
    auto it2 = graph.find(w);
    
    if(it->second.find(w) == it->second.end())
        throw UnknownEdgeException(v, w);
    if(it2->second.find(v) == it2->second.end())
        throw UnknownEdgeException(v, w);
    it->second.erase(w);
    it2->second.erase(v);
    numEdg--;
}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) noexcept
{
    if(graph.find(vertex) == graph.end())
    {
        graph.insert({vertex, {}});
        numVer++;
    }
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex)
{
    if(graph.find(vertex) == graph.end())
        throw UnknownVertexException(vertex);
    
    auto it = graph.find(vertex);
    auto set = it->second;
    for(auto x: set)
    {
        auto it2 = graph.find(x);
        it2->second.erase(vertex);
        numEdg--;
    }
    graph.erase(vertex);
    numVer--;
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &v, const T &w) const
{
    if(graph.find(v) == graph.end() || graph.find(w) == graph.end())
        throw UnknownVertexException(v);
    auto it = graph.find(v);
    if(it->second.find(w) == it->second.end())
        return false;
    return true;
}

template <typename T>
unsigned InterferenceGraph<T>::degree(const T &v) const
{
    if(graph.find(v) == graph.end())
        throw UnknownVertexException(v);
    return graph.find(v)->second.size();
}

#endif
