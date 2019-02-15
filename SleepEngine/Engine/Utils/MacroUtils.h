#pragma once

#define assertion(condition, message)\
assert((message, condition))

#define ForbidCopy(classname)\
classname(classname const&) = delete;\
classname& operator =(classname const&) = delete;

#define ForbidMove(classname)\
classname(classname&&) = delete;\
classname& operator =(classname&&) = delete;

#define ForbidCopyAndMove(classname)\
ForbidCopy(classname)\
ForbidMove(classname)
