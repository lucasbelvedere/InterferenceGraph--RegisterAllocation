#include "proj6.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace proj6;

RegisterAssignment proj6::assignRegisters(const std::string &path_to_graph, int num_registers) noexcept
{
    InterferenceGraph<Variable> ig = CSVReader::load(path_to_graph);
    std::unordered_map<std::string, int> registers;

    // Welsh-Powell Graph Coloring
    // Part 1: sorting.
    std::vector<std::pair<int, Variable>> descendingVec;
    std::unordered_set<Variable> vertex = ig.vertices();
    for(auto x : vertex)
        descendingVec.push_back({ig.degree(x), x});
    
    std::sort(descendingVec.begin(), descendingVec.end(), [](std::pair<int, Variable> a, std::pair<int, Variable> b){
        return a.first > b.first;
    });
    
    // Part 2: creating coloring list.
    std::vector<int> c;
    int maxReg = descendingVec[0].first + 1; // d(g) + 1
    for(int i = 1; i <= maxReg; i++)
        c.push_back(i);
    
    // Part 3 and 4: start the coloring process.
    auto it = c.begin();
    auto it_d = descendingVec.begin();
    
    while(it_d != descendingVec.end())
    {
        std::unordered_set<std::string> tmp;
        if(registers.find(it_d->second) == registers.end())
        {
            if(*it > num_registers)
                return {};
            else if(it == c.end())
                return {};
            else if(it != c.end() && *it <= num_registers)
            {
                registers.insert({it_d->second , *it});
                tmp = ig.neighbors(it_d->second);
                tmp.insert(it_d->second);
                for(auto it_tmp = descendingVec.begin(); it_tmp != descendingVec.end(); it_tmp++)
                {
                    if(tmp.find(it_tmp->second) == tmp.end())
                        if(registers.find(it_tmp->second) == registers.end())
                        {
                            registers.insert({it_tmp->second , *it});
                            tmp.insert(ig.neighbors(it_tmp->second).begin(), ig.neighbors(it_tmp->second).end());
                            tmp.insert(it_tmp->second);
                        }
                }
                it++;
            }
        }
        it_d++;
    }
    return registers;
}
