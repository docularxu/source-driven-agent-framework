# Heartbeat - 项目巡检

## 当前项目
- 路径: （Phase 1 时由 Jarvis-Arch 填写实际项目路径）

## 巡检任务
1. 读 .blackboard/tasks-backlog.md，检查是否有任务停在 [Analyzing] 或 [Reviewing]
2. 对比 .blackboard/progress.md 最后一条记录的时间，如果超过 15 分钟无更新：
   - 重新发送通知给对应 agent
   - 在 .blackboard/a2a-comms-log.md 记录重发
3. 检查是否有 [Needs Re-evaluation] 任务未处理
4. 无异常则 HEARTBEAT_OK
