#include "types.h"

bool empty(ExploreStack & stack){
  return stack.top == 0;
};

void pop(ExploreStack & stack, Stub & stub){
  stub.node = stack.stubs[--stack.top].node;
  stub.angle = stack.stubs[stack.top].angle;
}

void push(ExploreStack & stack, Stub & stub){
    stack.stubs[stack.top].node = stub.node;
    stack.stubs[stack.top++].angle = stub.angle;
}

void initStack(ExploreStack & stack){
  stack.top = 0;
}
