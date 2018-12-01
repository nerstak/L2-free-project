#ifndef FREE_PROJECT_UTILS_ENHANCEDSWITCH_H
#define FREE_PROJECT_UTILS_ENHANCEDSWITCH_H

#define SWITCH(var) do { int __input = var;
#define CASE(value) if (__input == value) {
#define BREAK return; }
#define DEFAULT if (1) {
#define BREAK_DEFAULT }
#define ENDSWITCH } while(0);

#endif //FREE_PROJECT_UTILS_ENHANCEDSWITCH_H
