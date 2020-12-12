# AVL Trees: perfectly balanced(as all things should be)
## Introduction
AVL trees(named after inventors Adelson-Velsky and Landis), also known as height-balanced trees are a widely-used data structure when it comes to efficient read, write and search operations. 

Similar to a BST(binary search tree), an AVL tree also has basic operations:
 - add()
 - remove()
 - search()

But what makes an AVL tree efficient and fast
 - always height balanced
   - balance factor on any node is 0 or 1
 - always achieves minimum height
   - by rotations

## How is it perfect balanced(as all things should be)
At the time of insertions and deletions:
 - it finds the first node where one side becomes more heavy than the other
 - fix this by RR, RL, LR, LL rotations

## Comparision with RB trees
I have compared my implementation with the std::set which is implemented with [red-black trees](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) for different workloads.
Here are the results:

## How to use ?


## Contributors