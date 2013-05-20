#include "types.h"

bool empty(ExploreStack & stack){
  return stack.top == 0;
};

void pop(ExploreStack & stack, Stub & stub){
  stub = stack.stubs[--stack.top];
}

void push(ExploreStack & stack, Stub & stub){
    stack.stubs[stack.top++] = stub;
}

void initStack(ExploreStack & stack){
  stack.top = 0;
}
