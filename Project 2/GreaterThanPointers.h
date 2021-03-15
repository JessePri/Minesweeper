#pragma once

#include "TreeNode.h"

struct GreaterThanPointers {
    GreaterThanPointers() = default;
    bool operator()(TreeNode* lhs, TreeNode* rhs) {
        return lhs->prob > rhs->prob;
    }
};