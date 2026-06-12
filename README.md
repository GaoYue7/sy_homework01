<<<<<<< HEAD
# 嵌入式系统作业1

## 实验说明
本仓库用于完成嵌入式系统课程第一次Git作业，包含两个版本的HelloWorld程序。

---

---

### 对应的完整Git命令（和前面步骤对应）
```bash
# 步骤1：拉取仓库
cd ~/Desktop/sy_homework01
git pull origin main

# 步骤2：新建lab01文件夹
mkdir lab01
mkdir lab01/src
mkdir lab01/results

# 步骤3：把实验代码放进lab01/src，截图放进lab01/results，然后更新README.md为上面的模板

# 步骤4：第一次add（添加代码和更新后的README）
git add lab01/src/
git add README.md

# 步骤5：第一次commit
git commit -m "lab01: 完成实验1代码与README更新"

# 步骤6：添加实验截图
git add lab01/results/

# 步骤7：第二次commit
git commit -m "lab01: 补充实验运行结果截图"

# 步骤8：推送到GitHub
git push origin main
