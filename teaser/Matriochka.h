#pragma once
#include <array>
#include <vector>
#include <list>
#include <limits>

struct Box {
  size_t height;
  size_t width;
  size_t depth;
  Box(size_t height, size_t width, size_t depth): height(height), width(width), depth(depth){}
};

struct Node {
  Box box;
  std::list<Node> children;
  Node(const Box& box) : box(box) {}
};

bool isChildren(const Box& father, const Box& child){
  if((father.height > child.height) && (father.width > child.width) && (father.depth > child.depth)){
    return true;
  };
  return false;
};

struct Tree {
  Node root;
  Tree(): root(Box(100, 100, 100)){}
  void insertBox(const Box& box){
    std::cout << "insertBox root " << std::endl;
    insertBox(box, root, root);
  }

  void insertBox(const Box& box, Node &node, Node &parent){
    std::cout << "insertBox box " << box.width << " node " << node.box.width << std::endl;
    if(isChildren(node.box, box)){
      std::cout << "isChildren" << std::endl;
      if(node.children.empty()){
        std::cout << "isChildren and leaf" << std::endl;
        node.children.push_back(box);
      } else {
        for(auto& child: node.children){
          std::cout << "isChildren and got children" << std::endl;
          insertBox(box, child, node);
        }
      }
    } else if (isChildren(box, node.box)){
      std::cout << "isParent" << std::endl;
      auto tempNode = node;
      Node nodeToAdd(box);
      nodeToAdd.children.push_back(tempNode);
      node = nodeToAdd;
    } else {
      std::cout << "sibling " << std::endl;
      parent.children.push_back(box);
    }
  }

  size_t maxDepth(){
    return depth(root) - 1;
  }

  size_t depth(const Node &node){
    size_t max = 0;
    std::cout << "depth #child " << node.children.size() << std::endl;
    for(const auto& child: node.children){
      max = std::max(depth(child), max);
    }
    std::cout << "max" << max << std::endl;
    return max + 1;
  }
};

size_t Matrioska(const std::vector<Box>& boxes){
  if(boxes.empty()){
    return 0;
  }
  else if(boxes.size() == 1){
    return 1;
  }

  Tree tree;

  for(const auto& box : boxes){
    std::cout << "next box " << box.height <<  " " << box.width <<  " " << box.depth << std::endl;
    tree.insertBox(box);
  }

  std::cout << std::endl;
  return tree.maxDepth();
}

