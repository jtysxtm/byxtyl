#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os

# 输入文件夹和输出文件夹的路径
input_folder = r'F:\Compiler-Lab1\fib\中间代码生成\dot'
output_folder = r'F:\Compiler-Lab1\fib\中间代码生成\dot_png'

# 检查输入和输出文件夹是否存在
if not os.path.exists(input_folder):
    print("输入文件夹不存在")
    exit(1)

if  not os.path.exists(output_folder):
    print("输出文件夹不存在")
    exit(1)

# 获取输入文件夹中的所有.dot文件
dot_files = [f for f in os.listdir(input_folder) if f.endswith(".dot")]

# 遍历所有.dot文件并转换为.png文件
for dot_file in dot_files:
    base_name = os.path.splitext(dot_file)[0]
    input_path = os.path.join(input_folder, dot_file)
    output_path = os.path.join(output_folder, f"{base_name}.png")
    command = f"dot -Tpng {input_path} -o {output_path}"
    os.system(command)
    print(f"已生成 {output_path}")

print("批量转换完成")
