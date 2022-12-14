#include "CSVReader.hpp"
#include "IGWriter.hpp"
#include "InterferenceGraph.hpp"
#include "proj6.hpp"
#include <vector>
#include <iostream>

void testCase(int x)
{
    switch (x) {
        case 1:
        {
            const auto &GRAPH = "/Users/cesarbelvedere/project6/project6/gtest/graphs/simple.csv";
            const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);

            assert(ig.numEdges() == 3);
            assert(ig.numVertices() == 3);

            const std::unordered_set<Variable> &expected_vertices = {"z", "x", "y"};
            assert(ig.vertices() == expected_vertices);

            std::unordered_set<Variable> expected_neighbors;
            expected_neighbors = {"y", "z"};
            assert(ig.neighbors("x") == expected_neighbors);
            expected_neighbors = {"x", "y"};
            assert(ig.neighbors("z") == expected_neighbors);
            expected_neighbors = {"z", "x"};
            assert(ig.neighbors("y") == expected_neighbors);
        } break;
        case 2:
        {
            const auto &GRAPH = "/Users/cesarbelvedere/project6/project6/gtest/graphs/simple.csv";
            const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);

            assert(ig.interferes("x", "y"));
            assert(ig.interferes("y", "x"));
            assert(ig.interferes("x", "z"));
            assert(ig.interferes("z", "x"));
            assert(ig.interferes("z", "y"));
            assert(ig.interferes("y", "z"));
        } break;
        case 3:
        {
            const auto &GRAPH = "/Users/cesarbelvedere/project6/project6/gtest/graphs/simple.csv";
            const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);

            assert(ig.degree("x") == 2);
            assert(ig.degree("y") == 2);
            assert(ig.degree("z") == 2);
        } break;
        case 4:{
            const auto &GRAPH = "/Users/cesarbelvedere/project6/project6/gtest/graphs/simple.csv";
            InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);

            ig.removeEdge("x", "y");
            assert(ig.numEdges() == 2);
            ig.removeEdge("x", "z");
            assert(ig.numEdges() == 1);
            ig.removeEdge("z", "y");
            assert(ig.numEdges() == 0);

            assert(ig.numVertices() == 3);
            ig.removeVertex("z");
            assert(ig.numVertices() == 2);
            ig.removeVertex("y");
            assert(ig.numVertices() == 1);
            ig.removeVertex("x");
            assert(ig.numVertices() == 0);
        } break;
        case 5:{
            const auto &GRAPH = "/Users/cesarbelvedere/project6/project6/gtest/graphs/simple.csv";
            const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);
            const std::unordered_set<Variable> &expected_neighbors = {"y", "z"};
            assert(ig.neighbors("x") == expected_neighbors);
        } break;
        case 6:{
            const auto &GRAPH = "/Users/cesarbelvedere/project6/project6/gtest/graphs/simple.csv";
            const auto NUM_REGS = 100;

            const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
//            for(auto x: allocation)
//                std::cout << x.first << " && " << x.second <<  std::endl;

        } break;
        case 7:{
            InterferenceGraph<Variable> ig;
            ig.addVertex("x");
            ig.addVertex("y");
            ig.addVertex("z");
            ig.addEdge("x", "y");
            ig.addEdge("x", "z");
            ig.addEdge("z", "y");
            ig.removeVertex("y");
//            ig.removeEdge("x", "y");
            std::cout << ig.numVertices() << std::endl;
            std::cout << ig.numEdges() << std::endl;
            std::unordered_set<std::string> s;
            s = ig.neighbors("x");
            for (auto& i : s)
            {
                std::cout << i << std::endl;
            }
        } break;
        case 8:{
            InterferenceGraph<Variable> ig;
            ig.addVertex("A");
            ig.addVertex("A");
            std::cout << ig.numVertices() << std::endl;
            try {
                ig.addEdge("A", "B");
            }
            catch (...)
            {
                std::cout << "catch the error" << std::endl;
            }
            std::cout << ig.numEdges() << std::endl;
        } break;
        default:
            break;
    }
}


int main()
{
//    for(int x = 1; x <= 5; x++)
        testCase(8);
}

