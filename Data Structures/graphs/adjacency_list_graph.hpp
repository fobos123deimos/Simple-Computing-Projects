#ifndef ADJACENCY_LIST_GRAPH_HPP
#define ADJACENCY_LIST_GRAPH_HPP

#include <cstddef>
#include <new>

namespace ds {

/*
    GraphNode

    Internal node used in the adjacency list.

    Each node stores:
    - vertex: the index of the adjacent vertex.
    - next: pointer to the next adjacent vertex in the list.
*/
struct GraphNode {
    std::size_t vertex = 0;
    GraphNode* next = nullptr;
};

/*
    AdjacencyListGraph

    This structure implements a graph using adjacency lists.

    Each position of the adjacency array represents one vertex.
    Each linked list stores the outgoing edges of that vertex.

    Example:

        adjacency[0] -> 1 -> 3

    This means that vertex 0 has edges to vertex 1 and vertex 3.

    By default, add_edge creates a directed edge:
        source -> destination

    For an undirected graph, use add_undirected_edge.
*/
struct AdjacencyListGraph {
    std::size_t vertex_count = 0;
    std::size_t edge_count = 0;
    GraphNode** adjacency = nullptr;
};

/*
    Checks whether a vertex index is valid.

    The graph uses zero-based indexing:
    - first vertex: 0
    - last vertex: vertex_count - 1
*/
inline bool is_valid_vertex(
    const AdjacencyListGraph& graph,
    std::size_t vertex
) {
    return vertex < graph.vertex_count;
}

/*
    Initializes the graph with a fixed number of vertices.

    Initially, the graph has no edges.

    Returns:
    - true  if the graph was initialized successfully.
    - false if memory allocation fails or number_of_vertices is zero.
*/
inline bool initialize(
    AdjacencyListGraph& graph,
    std::size_t number_of_vertices
) {
    if (number_of_vertices == 0) {
        graph.vertex_count = 0;
        graph.edge_count = 0;
        graph.adjacency = nullptr;
        return false;
    }

    graph.adjacency = new (std::nothrow) GraphNode*[number_of_vertices];

    if (graph.adjacency == nullptr) {
        graph.vertex_count = 0;
        graph.edge_count = 0;
        return false;
    }

    graph.vertex_count = number_of_vertices;
    graph.edge_count = 0;

    for (std::size_t i = 0; i < graph.vertex_count; ++i) {
        graph.adjacency[i] = nullptr;
    }

    return true;
}

/*
    Returns true if the graph has no vertices.
*/
inline bool has_no_vertices(const AdjacencyListGraph& graph) {
    return graph.vertex_count == 0;
}

/*
    Returns true if the graph has vertices but no edges.
*/
inline bool has_no_edges(const AdjacencyListGraph& graph) {
    return graph.edge_count == 0;
}

/*
    Returns true if the graph contains the edge:

        source -> destination
*/
inline bool has_edge(
    const AdjacencyListGraph& graph,
    std::size_t source,
    std::size_t destination
) {
    if (
        graph.adjacency == nullptr ||
        !is_valid_vertex(graph, source) ||
        !is_valid_vertex(graph, destination)
    ) {
        return false;
    }

    GraphNode* current = graph.adjacency[source];

    while (current != nullptr) {
        if (current->vertex == destination) {
            return true;
        }

        current = current->next;
    }

    return false;
}

/*
    Adds a directed edge:

        source -> destination

    The graph uses zero-based indexing.

    Returns:
    - true  if the edge was inserted.
    - false if the vertices are invalid, the edge already exists,
      or memory allocation fails.
*/
inline bool add_edge(
    AdjacencyListGraph& graph,
    std::size_t source,
    std::size_t destination
) {
    if (
        graph.adjacency == nullptr ||
        !is_valid_vertex(graph, source) ||
        !is_valid_vertex(graph, destination)
    ) {
        return false;
    }

    if (has_edge(graph, source, destination)) {
        return false;
    }

    GraphNode* new_node = new (std::nothrow) GraphNode;

    if (new_node == nullptr) {
        return false;
    }

    new_node->vertex = destination;
    new_node->next = graph.adjacency[source];

    graph.adjacency[source] = new_node;
    ++graph.edge_count;

    return true;
}

/*
    Adds an undirected edge between two vertices.

    Internally, this inserts two directed edges:

        first  -> second
        second -> first

    Returns:
    - true  if both edges were inserted.
    - false if one of the insertions fails.
*/
inline bool add_undirected_edge(
    AdjacencyListGraph& graph,
    std::size_t first,
    std::size_t second
) {
    if (first == second) {
        return add_edge(graph, first, second);
    }

    if (!add_edge(graph, first, second)) {
        return false;
    }

    if (!add_edge(graph, second, first)) {
        remove_edge(graph, first, second);
        return false;
    }

    return true;
}

/*
    Adds a directed edge using one-based indexing.

    This function exists to preserve the behavior of the original code,
    where vertices were passed as 1, 2, 3, ..., n.

    Example:
        add_edge_1_based(graph, 1, 3);

    inserts:
        0 -> 2
*/
inline bool add_edge_1_based(
    AdjacencyListGraph& graph,
    std::size_t source,
    std::size_t destination
) {
    if (source == 0 || destination == 0) {
        return false;
    }

    return add_edge(graph, source - 1, destination - 1);
}

/*
    Removes the directed edge:

        source -> destination

    Returns:
    - true  if the edge was removed.
    - false if the edge was not found or the vertices are invalid.
*/
inline bool remove_edge(
    AdjacencyListGraph& graph,
    std::size_t source,
    std::size_t destination
) {
    if (
        graph.adjacency == nullptr ||
        !is_valid_vertex(graph, source) ||
        !is_valid_vertex(graph, destination)
    ) {
        return false;
    }

    GraphNode* current = graph.adjacency[source];
    GraphNode* previous = nullptr;

    while (current != nullptr) {
        if (current->vertex == destination) {
            if (previous == nullptr) {
                graph.adjacency[source] = current->next;
            } else {
                previous->next = current->next;
            }

            delete current;
            --graph.edge_count;

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

/*
    Removes an undirected edge between two vertices.

    Internally, this removes:

        first  -> second
        second -> first

    Returns:
    - true  if at least one edge was removed.
    - false if no edge was found.
*/
inline bool remove_undirected_edge(
    AdjacencyListGraph& graph,
    std::size_t first,
    std::size_t second
) {
    bool removed_first = remove_edge(graph, first, second);

    if (first == second) {
        return removed_first;
    }

    bool removed_second = remove_edge(graph, second, first);

    return removed_first || removed_second;
}

/*
    Removes all edges from the graph, but keeps the vertices.

    After this function, the graph still has the same number of vertices,
    but every adjacency list becomes empty.
*/
inline void clear_edges(AdjacencyListGraph& graph) {
    if (graph.adjacency == nullptr) {
        return;
    }

    for (std::size_t i = 0; i < graph.vertex_count; ++i) {
        GraphNode* current = graph.adjacency[i];

        while (current != nullptr) {
            GraphNode* next = current->next;
            delete current;
            current = next;
        }

        graph.adjacency[i] = nullptr;
    }

    graph.edge_count = 0;
}

/*
    Releases all memory used by the graph.

    After this function, the graph returns to a safe empty state.
*/
inline void destroy(AdjacencyListGraph& graph) {
    clear_edges(graph);

    delete[] graph.adjacency;

    graph.adjacency = nullptr;
    graph.vertex_count = 0;
    graph.edge_count = 0;
}

/*
    Returns the number of vertices in the graph.
*/
inline std::size_t vertices(const AdjacencyListGraph& graph) {
    return graph.vertex_count;
}

/*
    Returns the number of edges in the graph.

    In a directed graph, each directed connection counts as one edge.

    In an undirected graph created with add_undirected_edge, each connection
    is stored as two directed edges.
*/
inline std::size_t edges(const AdjacencyListGraph& graph) {
    return graph.edge_count;
}

} // namespace ds

#endif // ADJACENCY_LIST_GRAPH_HPP