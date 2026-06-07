#include "adjacency_list_graph.hpp"
#include "linked_queue.hpp"

#include <iostream>
#include <vector>

/*
    Reads the number of vertices from the user.

    Returns:
    - a positive integer representing the number of vertices.
*/
int read_vertex_count() {
    int vertex_count = 0;

    do {
        std::cout << "Number of vertices: ";
        std::cin >> vertex_count;

        if (vertex_count < 1) {
            std::cout << "Error: the graph must have at least one vertex.\n";
        }
    } while (vertex_count < 1);

    return vertex_count;
}

/*
    Checks whether a vertex is valid.

    The program uses zero-based indexing:
    - first vertex: 0
    - last vertex: vertex_count - 1
*/
bool is_valid_vertex(int vertex, int vertex_count) {
    return vertex >= 0 && vertex < vertex_count;
}

/*
    Reads the graph edges from the user.

    The user must enter edges in the following format:

        source destination

    Example:

        0 1
        0 2
        1 3
        -1 -1

    The pair -1 -1 finishes the input.

    The graph is directed, so the edge:

        0 1

    means:

        0 -> 1
*/
bool read_edges(ds::AdjacencyListGraph& graph) {
    const int exit_value = -1;
    const int vertex_count = static_cast<int>(ds::vertices(graph));

    std::cout << "\nGraph edges ";
    std::cout << "(vertices from 0 to " << vertex_count - 1 << "):\n";
    std::cout << "Enter -1 -1 to stop.\n";

    while (true) {
        int source = 0;
        int destination = 0;

        std::cout << "\nSource: ";
        std::cin >> source;

        std::cout << "Destination: ";
        std::cin >> destination;

        if (source == exit_value && destination == exit_value) {
            break;
        }

        if (
            !is_valid_vertex(source, vertex_count) ||
            !is_valid_vertex(destination, vertex_count)
        ) {
            std::cout << "Error: invalid vertex.\n";
            continue;
        }

        if (!ds::add_edge(
                graph,
                static_cast<std::size_t>(source),
                static_cast<std::size_t>(destination)
            )) {
            std::cout << "Warning: edge was not inserted. ";
            std::cout << "It may already exist or memory allocation may have failed.\n";
        }
    }

    return true;
}

/*
    Computes the in-degree of each vertex.

    The in-degree of a vertex is the number of edges that point to it.

    Example:

        0 -> 2
        1 -> 2

    Vertex 2 has in-degree 2.
*/
std::vector<int> compute_in_degrees(const ds::AdjacencyListGraph& graph) {
    std::vector<int> in_degree(ds::vertices(graph), 0);

    for (std::size_t source = 0; source < ds::vertices(graph); ++source) {
        ds::GraphNode* current = graph.adjacency[source];

        while (current != nullptr) {
            ++in_degree[current->vertex];
            current = current->next;
        }
    }

    return in_degree;
}

/*
    Computes a topological ordering using Kahn's algorithm.

    A topological ordering is possible only for directed acyclic graphs.

    Parameters:
    - graph: directed graph.
    - topological_order: output vector that receives the ordering.

    Returns:
    - true  if a valid topological ordering exists.
    - false if the graph has at least one cycle or memory allocation fails.
*/
bool topological_sort(
    const ds::AdjacencyListGraph& graph,
    std::vector<int>& topological_order
) {
    std::vector<int> in_degree = compute_in_degrees(graph);

    ds::LinkedQueue<int> zero_in_degree_vertices;
    ds::initialize(zero_in_degree_vertices);

    for (std::size_t vertex = 0; vertex < ds::vertices(graph); ++vertex) {
        if (in_degree[vertex] == 0) {
            if (!ds::enqueue(
                    zero_in_degree_vertices,
                    static_cast<int>(vertex)
                )) {
                ds::destroy(zero_in_degree_vertices);
                return false;
            }
        }
    }

    while (!ds::is_empty(zero_in_degree_vertices)) {
        int current_vertex = 0;

        if (!ds::dequeue(zero_in_degree_vertices, &current_vertex)) {
            ds::destroy(zero_in_degree_vertices);
            return false;
        }

        topological_order.push_back(current_vertex);

        ds::GraphNode* current =
            graph.adjacency[static_cast<std::size_t>(current_vertex)];

        while (current != nullptr) {
            int neighbor = static_cast<int>(current->vertex);

            --in_degree[neighbor];

            if (in_degree[neighbor] == 0) {
                if (!ds::enqueue(zero_in_degree_vertices, neighbor)) {
                    ds::destroy(zero_in_degree_vertices);
                    return false;
                }
            }

            current = current->next;
        }
    }

    ds::destroy(zero_in_degree_vertices);

    return topological_order.size() == ds::vertices(graph);
}

/*
    Prints the topological ordering.
*/
void print_topological_order(const std::vector<int>& topological_order) {
    std::cout << "\nTopological ordering:\n\n";

    for (std::size_t i = 0; i < topological_order.size(); ++i) {
        std::cout << topological_order[i];

        if (i + 1 < topological_order.size()) {
            std::cout << " -> ";
        }
    }

    std::cout << '\n';
}

int main() {
    int vertex_count = read_vertex_count();

    ds::AdjacencyListGraph graph;

    if (!ds::initialize(graph, static_cast<std::size_t>(vertex_count))) {
        std::cout << "\nError: not enough memory to initialize the graph.\n";
        return 1;
    }

    read_edges(graph);

    std::vector<int> topological_order;

    bool has_topological_order =
        topological_sort(graph, topological_order);

    if (has_topological_order) {
        print_topological_order(topological_order);
    } else {
        std::cout << "\nThe graph has a cycle.\n";
        std::cout << "Therefore, there is no valid topological ordering.\n";
    }

    ds::destroy(graph);

    return 0;
}