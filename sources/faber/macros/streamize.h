#pragma once

#include <faber/macros/expand.h>
#include <faber/macros/concat.h>
#include <faber/macros/count-params.h>

#define STREAMIZE1(mem1) #mem1 << ":" << mem1
#define STREAMIZE2(mem1, mem2) STREAMIZE1(mem1) << ", " << STREAMIZE1(mem2)
#define STREAMIZE3(mem1, mem2, mem3) STREAMIZE1(mem1) << ", " << STREAMIZE2(mem2, mem3)
#define STREAMIZE4(mem1, mem2, mem3, mem4) STREAMIZE1(mem1) << ", " << STREAMIZE3(mem2, mem3, mem4)
#define STREAMIZE5(mem1, mem2, mem3, mem4, mem5) STREAMIZE1(mem1) << ", " << STREAMIZE4(mem2, mem3, mem4, mem5)
#define STREAMIZE6(mem1, mem2, mem3, mem4, mem5, mem6) STREAMIZE1(mem1) << ", " << STREAMIZE5(mem2, mem3, mem4, mem5, mem6)
#define STREAMIZE7(mem1, mem2, mem3, mem4, mem5, mem6, mem7) STREAMIZE1(mem1) << ", " << STREAMIZE6(mem2, mem3, mem4, mem5, mem6, mem7)
#define STREAMIZE8(mem1, mem2, mem3, mem4, mem5, mem6, mem7, mem8) STREAMIZE1(mem1) << ", " << STREAMIZE7(mem2, mem3, mem4, mem5, mem6, mem7, mem8)


#define STREAMIZE(...) EXPAND(CAT(STREAMIZE, EXPAND(COUNT_PARAMS(__VA_ARGS__)))(__VA_ARGS__))