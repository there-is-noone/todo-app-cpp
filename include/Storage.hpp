#pragma once

#include <vector>
#include "Task.hpp"


class Storage {
public:
    virtual std::vector<Task> load()=0;
    virtual void save(const std::vector<Task>& Tasks)=0;

    virtual ~Storage()=default;
};
