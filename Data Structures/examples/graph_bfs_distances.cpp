#include <iostream>
#include <vector>

#include "../queues/linked_queue.hpp"

/*
    Reads a positive integer from the user.

    Parameters:
    - message: message displayed before reading the value.

    Returns:
    - a positive integer.
*/
int read_positive_integer(const char* message) {
    int value = 0;

    do {
        std::cout << message;
        std::cin >> value;

        if (value < 1) {
            std::cout << "Error: the value must be greater than zero.\n";
        }
    } while (value < 1);

    return value;
}

/*
    Reads the origin vertex.

    The user enters vertices using one-based indexing:
    - first vertex: 1
    - last vertex: vertex_count

    Internally, the program converts the origin to zero-based indexing.
*/
int read_origin_vertex(int vertex_count) {
    int origin = 0;

    do {
        std::cout << "Origin vertex: ";
        std::cin >> origin;

        if (origin < 1 || origin > vertex_count) {
            std::cout << "Error: origin must be between 1 and "
                      << vertex_count << ".\n";
        }
    } while (origin < 1 || origin > vertex_count);

    return origin - 1;
}

/*
    Reads the edges of an undirected graph.

    The user must enter pairs of vertices:

        x y

    Example:

        1 2
        1 3
        2 4
        -1 -1

    The pair -1 -1 finishes the edge input.

    The user enters vertices using one-based indexing.
    Internally, they are converted to zero-based indexing.
*/
void read_edges(std::vector<std::vector<int>>& adjacency_matrix) {
    const int vertex_count = static_cast<int>(adjacency_matrix.size());

    std::cout << "Edges:\n";
    std::cout << "Enter pairs x y. Use -1 -1 to stop.\n";

    while (true) {
        int x = 0;
        int y = 0;

        std::cin >> x >> y;

        if (x == -1 && y == -1) {
            break;
        }

        if (
            x < 1 || x > vertex_count ||
            y < 1 || y > vertex_count
        ) {
            std::cout << "Error: invalid edge. Vertices must be between 1 and "
                      << vertex_count << ".\n";
            continue;
        }

        int source = x - 1;
        int destination = y - 1;

        adjacency_matrix[source][destination] = 1;
        adjacency_matrix[destination][source] = 1;
    }
}

/*
    Computes the shortest distance from the origin vertex to every other vertex.

    This function uses Breadth-First Search, also known as BFS.

    Since the graph is unweighted, BFS finds the minimum number of edges
    between the origin and every reachable vertex.

    Parameters:
    - adjacency_matrix: graph representation.
    - origin: origin vertex using zero-based indexing.

    Returns:
    - a vector with the distances from the origin.
    - distance -1 means the vertex is not reachable from the origin.
*/
std::vector<int> compute_bfs_distances(
    const std::vector<std::vector<int>>& adjacency_matrix,
    int origin
) {
    const int vertex_count = static_cast<int>(adjacency_matrix.size());

    std::vector<int> distance(vertex_count, -1);

    ds::LinkedQueue<int> vertices;
    ds::initialize(vertices);

    distance[origin] = 0;

    if (!ds::enqueue(vertices, origin)) {
        std::cout << "Error: not enough memory to initialize BFS queue.\n";
        return distance;
    }

    while (!ds::is_empty(vertices)) {
        int current_vertex = 0;

        if (!ds::dequeue(vertices, &current_vertex)) {
            break;
        }

        for (int neighbor = 0; neighbor < vertex_count; ++neighbor) {
            if (
                adjacency_matrix[current_vertex][neighbor] == 1 &&
                distance[neighbor] == -1
            ) {
                distance[neighbor] = distance[current_vertex] + 1;

                if (!ds::enqueue(vertices, neighbor)) {
                    std::cout << "Error: not enough memory during BFS.\n";
                    ds::destroy(vertices);
                    return distance;
                }
            }
        }
    }

    ds::destroy(vertices);

    return distance;
}

/*
    Prints the distance from the origin vertex to every vertex in the graph.

    The output uses one-based indexing because this is the format used
    by the user when entering the graph.
*/
void print_distances(
    const std::vector<int>& distance,
    int origin
) {
    std::cout << "\nDistances:\n\n";

    for (std::size_t i = 0; i < distance.size(); ++i) {
        std::cout << "From " << origin + 1
                  << " to " << i + 1
                  << ": " << distance[i] << '\n';
    }
}

int main() {
    int vertex_count = read_positive_integer("Number of vertices: ");

    std::vector<std::vector<int>> adjacency_matrix(
        vertex_count,
        std::vector<int>(vertex_count, 0)
    );

    read_edges(adjacency_matrix);

    int origin = read_origin_vertex(vertex_count);

    std::vector<int> distance =
        compute_bfs_distances(adjacency_matrix, origin);

    print_distances(distance, origin);

    return 0;
}