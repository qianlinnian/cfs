# CPH 按比赛分类整理方案

## 背景

使用 CPH (Competitive Programming Helper) 插件在 VS Code 中刷 Codeforces 题目时，所有 `.cpp` 文件默认保存在根目录，没有按比赛分类。

## 实现方案

创建了 `organize.py` 脚本，配合 VS Code Task 一键整理。

### 核心原理

1. CPH 导入题目时，会在 `.cph/` 目录下生成 `.prob` 文件，格式为：
   ```
   .{文件名}_{MD5(完整路径)}.prob
   ```
2. `.prob` 文件内包含 `group` 字段（比赛名）和 `srcPath` 字段（源文件路径）
3. CPH 通过**文件完整路径的 MD5 哈希**来匹配 `.cpp` 和 `.prob` 文件

### 关键发现

- CPH 计算哈希时使用的路径格式：**小写盘符 + 反斜杠**（如 `d:\course_content\cfs\A.cpp`）
- 移动 `.cpp` 文件后，必须同时：
  1. 将 `.prob` 文件移动到新目录下的 `.cph/` 子目录
  2. 更新 `.prob` 内的 `srcPath` 为新路径
  3. **用新路径重新计算 MD5 并重命名 `.prob` 文件**（否则 CPH 找不到）

### 比赛名 → 文件夹名映射规则

| 比赛名 | 文件夹名 |
|--------|---------|
| `Codeforces Round 1079 (Div. 2)` | `1079-Div2` |
| `Educational Codeforces Round 178 (Rated for Div. 2)` | `Edu178-Div2` |
| `Kotlin Heroes: Episode 12` | `Kotlin-Heroes-Episode-12` |

### 使用方法

1. 用 Competitive Companion 浏览器插件导入题目（CPH 会在根目录创建 `.cpp`）
2. 按 `Ctrl+Shift+P` → `Run Task` → 选择 **Organize by Contest**
3. 根目录的 `.cpp` 文件自动移入对应比赛文件夹，CPH 测试/提交功能正常

### 相关文件

- `organize.py` — 整理脚本（支持 `--dry-run` 预览模式）
- `.vscode/tasks.json` — VS Code Task 配置
