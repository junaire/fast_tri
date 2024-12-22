import math

step = 0.0001

code = f"""
inline double fast_sin(double x) {{
  int index = (int)(x * {int(1/step)});
  return FAST_TRI_SIN_VALS[index];
}}

inline double fast_cos(double x) {{
  return fast_sin(x + 1.57079632679489661923);
}}
"""


def gen_sin_vals():
    elems = ""
    i = 0.0
    j = 0
    while i <= 2.5 * math.pi:
        sin_val = math.sin(i)
        elems += f"    {sin_val:.10f},  // {i:.6f}\n"
        i += step
        j += 1
    return elems, j

the_license = """/*
* MIT License
*
* Copyright (c) 2024 Jun Zhang
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

"""

def generate_sin_table():
    with open("fast_tri.h", "w") as f:
        vals, num = gen_sin_vals()
        f.write(the_license)
        f.write("#pragma once\n\n")
        f.write(f"#define FAST_TRI_SIN_VALS_SIZE {num}\n\n")
        f.write("inline double FAST_TRI_SIN_VALS[FAST_TRI_SIN_VALS_SIZE] = {\n")
        f.write(vals)
        f.write("};\n\n")
        f.write(code)


generate_sin_table()
