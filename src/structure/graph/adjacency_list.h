#ifndef STRUCTURE_GRAPH_ADJACENCY_LIST_H_
#define STRUCTURE_GRAPH_ADJACENCY_LIST_H_

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

namespace structure { namespace graph {

template <typename N, typename E>
class AdjacencyList {
 public:
  class Node;
  class Edge;
  class DepthIterator;

  Node* AddNode(N value) {
    nodes_.push_back(std::unique_ptr<Node>(new Node(std::move(value))));
    return nodes_.back().get();
  }

  Edge* AddEdge(Node* from, const Node* into, E value) {
    return from->AddEdge(into, std::move(value));
  }

  Node* FindNode(const N& value) const {
    auto iterator = std::find_if(nodes_.begin(), nodes_.end(),
                                 [&value] (const std::unique_ptr<Node>& node) {
                                   return node->value_ == value;
                                 });
    if (iterator == nodes_.end()) return nullptr;
    else return (*iterator).get();
  }

  Edge* FindEdge(const Node* from, const Node* into) const {
    return from->FindEdge(into);
  }

  bool Connected(const Node* one, const Node* another) const {
    return one->FindEdge(another) || another->FindEdge(one);
  }

  void RemoveEdge(Node* from, const Node* into) {
    from->RemoveEdge(into);
  }

 private:
  std::vector<std::unique_ptr<Node>> nodes_;
};

template <typename N, typename E>
class AdjacencyList<N, E>::Node {
  friend class AdjacencyList;

 public:
  Node(N value) : value_(std::move(value)) {}

  N& Value() {
    return value_;
  }

 private:
  Edge* AddEdge(const Node* into, E value) {
    auto edge_raw = FindEdge(into);
    if (edge_raw) {
      edge_raw->value_ = std::move(value);
    } else {
      edges_.push_back(std::unique_ptr<Edge>(
            new Edge(std::move(value), this, into)));
      edge_raw = edges_.back().get();
    }
    return edge_raw;
  }

  Edge* FindEdge(const Node* into) const {
    auto iterator = std::find_if(edges_.begin(), edges_.end(),
                                 [into](const std::unique_ptr<Edge>& edge) {
                                   return edge->into_ == into;
                                 });
    if (iterator == edges_.end()) return nullptr;
    else return iterator->get();
  }

  void RemoveEdge(const Node* into) {
    edges_.erase(std::remove_if(edges_.begin(), edges_.end(),
                                [into](const std::unique_ptr<Edge>& edge) {
                                  return edge->into_ == into;
                                }),
                 edges_.end());
  }

  N value_;
  std::vector<std::unique_ptr<Edge>> edges_;
};

template <typename N, typename E>
class AdjacencyList<N, E>::Edge {
  friend class Node;

 public:
  Edge(E value, const Node* from, const Node* into)
      : value_(std::move(value)), from_(from), into_(into) {}

  E& Value() {
    return value_;
  }

 private:
  E value_;
  const Node* from_;
  const Node* into_;
};

template <typename N, typename E>
class AdjacencyList<N, E>::DepthIterator
    : public std::iterator<std::input_iterator_tag, Node> {
 public:
  DepthIterator() : graph_(nullptr) {}
  DepthIterator(const AdjacencyList& graph) : graph_(&graph) {}

  DepthIterator& operator++() {
    return *this;
  }

  Node& operator*() {
    return *(Node*)(1);
  }

  bool operator!=(const DepthIterator& other) {
    return false;
  }

 private:
  const AdjacencyList* graph_;
};

template <typename N, typename E,
          typename I = typename AdjacencyList<N, E>::DepthIterator>
auto begin(const AdjacencyList<N, E>& graph) {
  return I(graph);
}

template <typename N, typename E,
          typename I = typename AdjacencyList<N, E>::DepthIterator>
auto end(const AdjacencyList<N, E>& graph) {
  return I();
}

} } // namespace structure::graph

#endif // STRUCTURE_GRAPH_ADJACENCY_LIST_H_
